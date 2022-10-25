#include "camfinder.h"

CamFinder::CamFinder(QObject *parent) : QObject(parent)
{
    QObject::connect(&timer,&QTimer::timeout,this,&CamFinder::timeOut);
    timer.start(500);
}

void CamFinder::timeOut()
{
    bool update=false;
    for (int i=0; i<10;i++){
        QString name="/dev/video"+QString::number(i);
        if (QFile(name).exists())
            if (!videoDevices.contains(name)) {
                update=true;
                videoDevices.push_back(name);
            }
    }
    if (update) emit modelChanged();
}
