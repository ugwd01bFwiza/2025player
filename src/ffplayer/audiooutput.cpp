#include "audiooutput.h"

#include <QAudioOutput>
#include <QAudioFormat>
#include <QIODevice>

extern "C" {
#include <libavutil/frame.h>
#include <libavutil/samplefmt.h>
#include <libavutil/avutil.h>
#include <libavutil/mem.h>
}

AudioOutput::AudioOutput(const AudioParams *audio_params, AVFrameQueue *audio_frame_queue):
    m_audioFrameQueue(audio_frame_queue) {
    m_audioParams = *audio_params;
    m_abort = false;
}

AudioOutput::~AudioOutput() {
    stop();
    wait();
}

void AudioOutput::play()
{
    QMutexLocker locker(&m_mutex);
    m_abort = false;
    
    if (!isRunning()) {
        start(QThread::Priority::HighPriority);
    }
}

void AudioOutput::stop()
{
    QMutexLocker locker(&m_mutex);
    m_abort = true;
}

void AudioOutput::run()
{
    QAudioFormat format;
    format.setSampleRate(m_audioParams.fmreq);
    format.setChannelCount(m_audioParams.channels);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioOutput audioOutput(format);
    QIODevice *audioDevice = audioOutput.start();
    if (!audioDevice) {
        return;
    }

    while (!m_abort) {
        AVFrame *frame = m_audioFrameQueue->Pop(10);
        if (!frame) {
            continue;
        }

        int dataSize = av_samples_get_buffer_size(nullptr, m_audioParams.channels, frame->nb_samples, m_audioParams.fmt, 1);
        if (dataSize < 0) {
            av_frame_free(&frame);
            continue;
        }

        qint64 bytesWritten = audioDevice->write(reinterpret_cast<const char *>(frame->data[0]), dataSize);
        
        av_frame_free(&frame);
    }

    audioOutput.stop();
}