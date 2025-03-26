#include "demuxthread.h"

DemuxThread::DemuxThread(AVPacketQueue *audio_queue, AVPacketQueue *video_queue):
    audio_queue_(audio_queue), video_queue_(video_queue) {

}

DemuxThread::~DemuxThread() {
    if (thread_) {
        Thread::Stop();
    }
}

int DemuxThread::Init(const std::string &url) {
    int ret = 0;
    url_ = url;

    format_ctx_ = avformat_alloc_context();

    ret = avformat_open_input(&format_ctx_, url_.c_str(), NULL, NULL);
    if (ret < 0) return -1;
    ret = avformat_find_stream_info(format_ctx_, NULL);
    if (ret < 0) return -2;

    av_dump_format(format_ctx_, 0, url_.c_str(), 0);

    audio_index_ = av_find_best_stream(format_ctx_, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
    video_index_ = av_find_best_stream(format_ctx_, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    subtitle_index_ = av_find_best_stream(format_ctx_, AVMEDIA_TYPE_SUBTITLE, -1, -1, NULL, 0);

    if (audio_index_ < 0 && video_index_ < 0) return -3;

    return 0;
}

int DemuxThread::Start() {
    thread_ = new std::thread(&DemuxThread::Run, this);
    if (!thread_) return -1;

    return 0;
}

int DemuxThread::Stop() {
    Thread::Stop();
    if (format_ctx_) {
        avformat_close_input(&format_ctx_);
        format_ctx_ = NULL;
    }
    return 0;
}

void DemuxThread::Run() {
    int ret = 0;
    AVPacket pkt;

    while (!abort_) {
        if (audio_queue_->Size() > 100 || video_queue_->Size() > 100) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        ret = av_read_frame(format_ctx_, &pkt);
        if (ret < 0) break;
    }

    if (pkt.stream_index == audio_index_) {
        audio_queue_->Push(&pkt);
    }
    else if (pkt.stream_index == video_index_) {
        video_queue_->Push(&pkt);
    }
    // else if (pkt.stream_index == subtitle_index_) {
    //  // subtitle
    // }
     else {
         av_packet_unref(&pkt);
    }

    av_packet_unref(&pkt);
}

AVCodecParameters *DemuxThread::AudioCodecParameters() {
    if (audio_index_ < 0) return NULL;
    return format_ctx_->streams[audio_index_]->codecpar;
}

AVCodecParameters *DemuxThread::VideoCodecParameters() {
    if (video_index_ < 0) return NULL;
    return format_ctx_->streams[video_index_]->codecpar;
}

AVCodecParameters *DemuxThread::SubtitleCodecParameters() {
    if (subtitle_index_ < 0) return NULL;
    return format_ctx_->streams[subtitle_index_]->codecpar;
}