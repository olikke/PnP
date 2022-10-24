#include "imageprovider.h"

ImageProvider::ImageProvider(QObject *parent,QSize size) : QObject(parent),QQuickImageProvider(QQuickImageProvider::Image)
{
    image = QImage(size.width(),size.height(),QImage::Format_RGB32);
    image.fill(QColor("#2d2d2d"));
}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id)
    return image;
}

void ImageProvider::updateImage(const QImage im)
{
    if (!image.isNull())
    {
        image=im;
        emit imageChanged();
    }
}
