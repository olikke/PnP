#include "imageprovider.h"

ImageProvider::ImageProvider(QObject *parent,QSize size) : QObject(parent),QQuickImageProvider(QQuickImageProvider::Image)
{
    image = QImage(size.width(),size.height(),QImage::Format_Grayscale8);
    image.fill(QColor("#2d2d2d"));
}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id)
    return image;
}

void ImageProvider::updateImage(cv::Mat im)
{
    if (im.empty())
        return;
    if (im.channels()==1)
        image=QImage((uchar*) im.data, im.cols, im.rows, im.step, QImage::Format_Grayscale8);
    else {
    //    cv::Mat temp=cv::Mat(im.cols,im.rows,im.type());
     //   cvtColor(im, temp, CV_BGR2RGB);
        image=QImage((uchar*) im.data, im.cols,im.rows, im.step, QImage::Format_RGB888);
    }
    emit imageChanged();
}
