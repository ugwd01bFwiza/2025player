#ifndef AVPACKETQUEUE_H
#define AVPACKETQUEUE_H

#include "queue.h"

extern "C" {
#include "libavutil/avutil.h"
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
}

class AVPacketQueue {
public:
    AVPacketQueue() {}
    ~AVPacketQueue() {}
    void Abort();
    int Size();
    int Push(AVPacket *pkt);
    AVPacket *Pop(const int timeout);

private:
    void release();
    Queue<AVPacket *> queue_;
};

#endif