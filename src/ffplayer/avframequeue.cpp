#include "avframequeue.h"

AVFrameQueue::AVFrameQueue() {
}

AVFrameQueue::~AVFrameQueue() {
}

void AVFrameQueue::Abort() {
    release();
    queue_.Abort();
}

int AVFrameQueue::Push(AVFrame *frame) {

}

AVFrame *AVFrameQueue::Pop(const int timeout) {

}

AVFrame *AVFrameQueue::Front() {

}

void AVFrameQueue::release() {
    while (true) {
        AVFrame *frame = nullptr;
        int ret = queue_.Pop(frame, 1);
        if (ret < 0) break;
    }
}