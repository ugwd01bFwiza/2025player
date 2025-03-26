#include "demuxthread.h"
#include "avframequeue.h"
#include "decodethread.h"
#include "videooutput.h"
#include "audiooutput.h"
#include "ffvideosurface.h"

#include <QVideoSurfaceFormat>

extern "C" {
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}

int ffmain(char *argv) {
    int ret = 0;
    AVPacketQueue audio_pkt_queue;
    AVPacketQueue video_pkt_queue;

    AVFrameQueue audio_frame_queue;
    AVFrameQueue video_frame_queue;

    //解复用
    DemuxThread *demux_thread = new DemuxThread(&audio_pkt_queue, &video_pkt_queue);

    ret = demux_thread->Init(argv);
    if (ret < 0) return -1;
    ret = demux_thread->Start();
    if (ret < 0) return -2;

    //解码
    DecodeThread *audio_decode_thread = new DecodeThread(&audio_pkt_queue, &audio_frame_queue);

    ret = audio_decode_thread->Init(demux_thread->AudioCodecParameters());
    if (ret < 0) return -3;
    ret = audio_decode_thread->Start();
    if (ret < 0) return -4;

    DecodeThread *video_decode_thread = new DecodeThread(&video_pkt_queue, &video_frame_queue);

    ret = video_decode_thread->Init(demux_thread->VideoCodecParameters());
    if (ret < 0) return -5;
    ret = video_decode_thread->Start();
    if (ret < 0) return -6;

    //播放
    AudioParams audio_params;
    AVCodecContext *audio_ctx = audio_decode_thread->CodecContext();
    audio_params.channels = audio_ctx->channels;
    audio_params.fmreq = audio_ctx->sample_rate;
    audio_params.fmt = audio_ctx->sample_fmt;

    AudioOutput *audio_output = new AudioOutput(&audio_params, &audio_frame_queue);

    VideoOutput video_output(&video_frame_queue, video_decode_thread->CodecContext());
    
    audio_output->play();
    video_output.play();
    
    audio_output->stop();
    delete audio_output;

    demux_thread->Stop();
    delete demux_thread;
    audio_decode_thread->Stop();
    delete audio_decode_thread;
    video_decode_thread->Stop();
    delete video_decode_thread;

    return 0;
}
