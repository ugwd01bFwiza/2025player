#include "videooutput.h"
#include "ffvideosurface.h"

#include <QSize>
#include <QVideoSurfaceFormat>
#include <QThread>

extern "C" {
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavutil/frame.h>
}

VideoOutput::VideoOutput(AVFrameQueue *frameQueue, AVCodecContext *videoCtx):
    m_videoFrameQueue(frameQueue),
    m_videoCodecContext(videoCtx) {
}

VideoOutput::~VideoOutput() {
}

int VideoOutput::play() {

    int videoWidth = m_videoCodecContext->width;
    int videoHeight = m_videoCodecContext->height;

    struct SwsContext *swsCtx = sws_getContext(
        videoWidth, videoHeight, AV_PIX_FMT_YUV420P,
        videoWidth, videoHeight, AV_PIX_FMT_RGB32,
        SWS_BILINEAR, nullptr, nullptr, nullptr);
    if (!swsCtx) {
        return -1;
    }

    int dstBytesPerLine = videoWidth * 4;
    uint8_t *dstData[4];
    dstData[0] = (uint8_t *)av_malloc(videoHeight * dstBytesPerLine);
    if (!dstData[0]) {
        sws_freeContext(swsCtx);
        return -1;
    }
    for (int i = 1; i < 4; i++) {
        dstData[i] = nullptr;
    }

    FFVideoSurface *videoSurface = new FFVideoSurface();
    QVideoSurfaceFormat surfaceFormat(QSize(videoWidth, videoHeight), QVideoFrame::Format_RGB32);
    if (!videoSurface->start(surfaceFormat)) {
        av_free(dstData[0]);
        sws_freeContext(swsCtx);
        delete videoSurface;
        return -1;
    }

    QThread *playThread = QThread::create([=]() {
        
        // 此处建立视频显示窗口，并连接 videoSurface 的信号更新界面

        while (true) {
            AVFrame *avFrame = m_videoFrameQueue->Pop(10);
            if (!avFrame) {
                break;
            }

            sws_scale(swsCtx,
                avFrame->data, avFrame->linesize,
                0, videoHeight,
                dstData, &dstBytesPerLine);

            QImage image(dstData[0], videoWidth, videoHeight, dstBytesPerLine, QImage::Format_RGB32);
            if (image.isNull()) {
                break;
            } else {
                QVideoFrame videoFrame(image);
                videoSurface->present(videoFrame);
            }
        }

        sws_freeContext(swsCtx);
        av_free(dstData[0]);

        delete videoSurface;
    });

    QObject::connect(playThread, &QThread::finished, playThread, &QObject::deleteLater);
    playThread->start();

    return 0;
}