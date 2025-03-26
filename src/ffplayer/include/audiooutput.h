#ifndef AUDIOOUTPUT_H
#define AUDIOOUTPUT_H

#include <QThread>
#include <QAudioOutput>
#include <QMutex>
#include <QWaitCondition>
#include <memory>

#include "avframequeue.h"

class AudioOutput : public QThread {
    Q_OBJECT

public:
    AudioOutput(const AudioParams *audio_params, AVFrameQueue *audio_frame_queue);
    ~AudioOutput() override;

    void play();
    void stop();

protected:
    void run() override;

private:
    AudioParams m_audioParams;
    AVFrameQueue *m_audioFrameQueue;
    bool m_abort = false;
    QMutex m_mutex;
};

#endif // AUDIOOUTPUT_H