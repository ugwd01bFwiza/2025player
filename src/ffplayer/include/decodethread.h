#ifndef DECODETHREAD_H
#define DECODETHREAD_H

#include "thread.h"
#include "avpacketqueue.h"
#include "avframequeue.h"

class DecodeThread : public Thread {
public:
    DecodeThread(AVPacketQueue *pkt_queue, AVFrameQueue *frame_queue);
    ~DecodeThread();
    int Init(AVCodecParameters *codec_parameters);
    int Start();
    int Stop();
    void Run();

private:
    AVCodecContext *codec_ctx_ = NULL;
    AVPacketQueue *pkt_queue_ = NULL;
    AVFrameQueue *frame_queue_ = NULL;
};

#endif