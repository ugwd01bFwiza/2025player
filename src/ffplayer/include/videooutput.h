#ifndef VIDEOOUTPUT_H
#define VIDEOOUTPUT_H

#include "avframequeue.h"

class VideoOutput {
public:
    VideoOutput(VFrameQueue *frameQueue, AVCodecContext *videoCtx);
    ~VideoOutput();

    int play();

private:
    AVFrameQueue *m_videoFrameQueue;
    AVCodecContext *m_videoCodecContext;
};

#endif