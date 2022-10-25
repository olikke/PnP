#pragma once

#include <QObject>
#include <QImage>
#include <QQuickImageProvider>
#include <opencv2/opencv.hpp>



class ImageProvider : public QObject,public QQuickImageProvider
{
    Q_OBJECT
public:
    ImageProvider(QObject *parent = nullptr,QSize size =QSize(720,576));

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

public slots:
    void updateImage(const cv::Mat im);
signals:
    void imageChanged();
private:
    QImage image;
};
