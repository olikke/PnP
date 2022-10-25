#pragma once

#include <QObject>
#include <QTimer>
#include <QFile>
#include <QDebug>

class CamFinder : public QObject
{
    Q_OBJECT
public:
    explicit CamFinder(QObject *parent = nullptr);

    Q_PROPERTY(QStringList model READ getModel NOTIFY modelChanged)
    QStringList getModel() {return videoDevices;}


signals:
    void modelChanged();
private:
    QStringList videoDevices;
    QTimer timer;
    void timeOut();
};

