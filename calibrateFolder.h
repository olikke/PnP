#pragma once

#include <QObject>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QUrl>
#include <QFile>
#include <calibration.h>
#include <QtConcurrent/QtConcurrent>
#include <opencv2/opencv.hpp>
#include "global.h"

struct Task {
    QString fileName;
    cv::Size boardSize;
    cv::Mat imagePoint;
    bool success;
};

class CalibrateFolder : public QObject
{
    Q_OBJECT
public:
    explicit CalibrateFolder(QObject *parent = nullptr);
    ~CalibrateFolder();

    Q_INVOKABLE void start(QString url, QStringList fileName);
    Q_INVOKABLE void startParallel(QString url, QStringList fileName);
signals:

public slots:

private:
    QString tempDir;
    Calibration* calibration;
    void removeDir();
};
