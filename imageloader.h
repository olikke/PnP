#pragma once

#include <QObject>
#include <opencv2/opencv.hpp>

class ImageLoader : public QObject
{
    Q_OBJECT
public:
    explicit ImageLoader(QObject *parent = nullptr);

signals:

public slots:
};

