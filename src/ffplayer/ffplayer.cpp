#include "demuxthread.h"

int main(int argc, char *argv[]) {
    int ret = 0;
    AVPacketQueue audio_queue;
    AVPacketQueue video_queue;

    DemuxThread *demux_thread = new DemuxThread(&audio_queue, &video_queue);

    ret = demux_thread->Init(argv[1]);
    if (ret < 0) return -1;

    ret = demux_thread->Start();
    if (ret < 0) return -2;

    demux_thread->Stop();

    delete demux_thread;
}