#pragma once

#include <QObject>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QUrl>
#include <QFile>
#include <calibration.h>
#include "global.h"

class CalibrateFolder : public QObject
{
    Q_OBJECT
public:
    explicit CalibrateFolder(QObject *parent = nullptr);
    ~CalibrateFolder();

    Q_INVOKABLE void start(QString url, QStringList fileName);

signals:

public slots:

private:
    QString tempDir;
    Calibration* calibration;
    void removeDir();
};
