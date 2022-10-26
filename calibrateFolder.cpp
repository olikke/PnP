#include "calibrateFolder.h"

CalibrateFolder::CalibrateFolder(QObject *parent) :
    QObject(parent),
    tempDir(QCoreApplication::applicationDirPath()+"/.temporary/"),
    calibration(new Calibration(this))
{

    removeDir();
    if (!QDir(tempDir).mkdir(tempDir)) qDebug()<<"Не удалось создать папку для временных файлов";
}

CalibrateFolder::~CalibrateFolder()
{
    removeDir();
}

void CalibrateFolder::start(QString url, QStringList fileName)
{
    std::chrono::high_resolution_clock::time_point time;
    getTime(time);
    QDir source(QUrl(url).toLocalFile());
    QStringList list = source.entryList(QDir::Files | QDir::AllEntries | QDir::NoDotAndDotDot);
    for (QString fn: list) {
        if (!fileName.contains(fn)) continue;
        QFile::copy(QUrl(url).toLocalFile()+"/"+fn, tempDir+fn);
        calibration->openFile(tempDir+fn);
    }
    qDebug()<<getMicroSecSince(time)/1000/1000<<"sec";
}

void CalibrateFolder::removeDir()
{
    QDir dir(tempDir);
    if (dir.exists()) dir.removeRecursively();
}
