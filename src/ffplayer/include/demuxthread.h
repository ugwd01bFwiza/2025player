#ifndef DEMUXTHREAD_H
#define DEMUXTHREAD_H

#include "thread.h"

//ffmpeg
#include "libavutil/avutil.h"
#include "libavformat/avformat.h"


class DemuxThread {
public:
    DemuxThread();

    int Start();
    int Stop();
    void Run();
private:
    std::string url_;

    // AVPacketQueue *audio_queue_ = NULL;
    // AVPacketQueue *video_queue_ = NULL;

    AVFormatContext *format_ctx_ = NULL;
};

#endif