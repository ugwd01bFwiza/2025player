#include "avframequeue.h"

AVFrameQueue::AVFrameQueue() {
}

AVFrameQueue::~AVFrameQueue() {
}

void AVFrameQueue::Abort() {
    release();
    queue_.Abort();
}

int AVFrameQueue::Size() {
    return queue_.Size();
}

int AVFrameQueue::Push(AVFrame *frame) {
    AVFrame *tmp_frame = av_frame_alloc();
    av_frame_move_ref(tmp_frame, frame);

    return queue_.Push(tmp_frame);
}

AVFrame *AVFrameQueue::Pop(const int timeout) {
    AVFrame *tmp_frame = nullptr;
    int ret = queue_.Pop(tmp_frame, timeout);
    if (ret < 0) return nullptr;
    return tmp_frame;
}

AVFrame *AVFrameQueue::Front() {
    AVFrame *tmp_frame = nullptr;
    int ret = queue_.Front(tmp_frame);
    if (ret < 0) return nullptr;
    return tmp_frame;
}

void AVFrameQueue::release() {
    while (true) {
        AVFrame *frame = nullptr;
        int ret = queue_.Pop(frame, 1);
        if (ret < 0) break;
        else av_frame_free(&frame);
    }
}