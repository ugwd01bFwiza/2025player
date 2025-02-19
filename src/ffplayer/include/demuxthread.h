#ifndef DEMUXTHREAD_H
#define DEMUXTHREAD_H

#include "thread.h"
#include "avpacketqueue.h"

// ffmpeg
extern "C" {
#include "libavutil/avutil.h"
#include "libavformat/avformat.h"
}

class DemuxThread : public Thread {
public:
    DemuxThread(AVPacketQueue *audio_queue, AVPacketQueue *video_queue);
    ~DemuxThread();
    int Init(const std::string &url);
    int Start();
    int Stop();
    void Run();

private:
    std::string url_; 

    AVPacketQueue *audio_queue_ = NULL;
    AVPacketQueue *video_queue_ = NULL;

    AVFormatContext *format_ctx_ = NULL;
    int audio_index_ = -1;
    int video_index_ = -1;
    int subtitle_index_ = -1;
};

#endif