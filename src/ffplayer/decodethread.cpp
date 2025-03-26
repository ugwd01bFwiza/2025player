#include "decodethread.h"

DecodeThread::DecodeThread(AVPacketQueue *pkt_queue, AVFrameQueue *frame_queue):
    pkt_queue_(pkt_queue), frame_queue_(frame_queue) {
}

DecodeThread::~DecodeThread() {
}

int DecodeThread::Init(AVCodecParameters *codec_parameters) {
    if (!codec_parameters) return -1;

    codec_ctx_ = avcodec_alloc_context3(NULL);
    if (!codec_ctx_) return -2;

    int ret = avcodec_parameters_to_context(codec_ctx_, codec_parameters);
    if (ret < 0) return -3;

    const AVCodec *codec = avcodec_find_decoder(codec_ctx_->codec_id);
    if (!codec) return -4;

    ret = avcodec_open2(codec_ctx_, codec, NULL);
    if (ret < 0) return -5;

    return 0;
}

int DecodeThread::Start() {
    thread_ = new std::thread(&DecodeThread::Run, this);
    if (!thread_) return -1;

    return 0;
}

int DecodeThread::Stop() {
    Thread::Stop();

    return 0;
}

void DecodeThread::Run() {
    AVFrame *frame = av_frame_alloc();

    while (abort_ != 1) {
        if (frame_queue_->Size() > 100) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        AVPacket *pkt = pkt_queue_->Pop(10);

        if (!pkt) {
            int ret = avcodec_send_packet(codec_ctx_, pkt);
            av_packet_free(&pkt);
            if (ret < 0) break;

            while (true) {
                ret = avcodec_receive_frame(codec_ctx_, frame);
                if (ret == 0) {
                    frame_queue_->Push(frame);
                    continue;
                }
                else if (ret == AVERROR(EAGAIN)) {
                    break;
                }
                else {
                    abort_ = 1;
                    break;
                }
            }
        }
    }
}