#ifndef AVFRAMEQUEUE_H
#define AVFRAMEQUEUE_H

#include "queue.h"

extern "C" {
#include "libavutil/avutil.h"
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
}

class AVFrameQueue {
public:
    AVFrameQueue();
    ~AVFrameQueue();
    void Abort();
    int Size();
    int Push(AVFrame *frame);
    AVFrame *Pop(const int timeout);
    AVFrame *Front();

private:
    void release();
    Queue<AVFrame *> queue_;

};

#endif