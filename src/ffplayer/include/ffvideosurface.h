#ifndef FFVIDEOSURFACE_H
#define FFVIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include <QVideoFrame>
#include <QImage>

class FFVideoSurface : public QAbstractVideoSurface {
    Q_OBJECT
public:
    explicit FFVideoSurface(QObject *parent = nullptr)
        : QAbstractVideoSurface(parent) {}

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const override {
        Q_UNUSED(handleType);
        return { QVideoFrame::Format_RGB32, QVideoFrame::Format_ARGB32 };
    }

    bool start(const QVideoSurfaceFormat &format) override {
        return QAbstractVideoSurface::start(format);
    }

    bool present(const QVideoFrame &frame) override {
        if (!frame.isValid()) return false;
        QImage image = frame.image();
        emit frameAvailable(image);
        return true;
    }

signals:
    void frameAvailable(const QImage &frame);
};

#endif