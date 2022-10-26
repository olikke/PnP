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

Task calc(const Task &task)
{
    cv::Mat frame=cv::imread(task.fileName.toLatin1().constData());
    //критерии поиска субпикселя кол-во итераций и точность
    const cv::TermCriteria critaria=cv::TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,30,0.1);
    cv::cvtColor(frame,frame,CV_BGR2GRAY);
    bool found=cv::findChessboardCorners(frame,task.boardSize,task.imagePoint);
    if (found) {
        //olikke cv::Size(11,11) зона поиска - изменение/производительность/точность
        // cv::Size(-1,-1) мёртвая зона
        cv::cornerSubPix(frame,task.imagePoint,cv::Size(11,11),cv::Size(-1,-1),critaria);
        cv::cvtColor(frame,frame,CV_GRAY2BGR);
        cv::drawChessboardCorners(frame,task.boardSize,task.imagePoint,found);
    }
    cv::imwrite(task.fileName.toLatin1().constData(),frame);
}

void CalibrateFolder::startParallel(QString url, QStringList fileName)
{
    std::chrono::high_resolution_clock::time_point time;
    getTime(time);
    QDir source(QUrl(url).toLocalFile());
    QStringList list = source.entryList(QDir::Files | QDir::AllEntries | QDir::NoDotAndDotDot);
    QList<Task> blank;
    for (QString fn: list) {
        if (!fileName.contains(fn)) continue;
        QFile::copy(QUrl(url).toLocalFile()+"/"+fn, tempDir+fn);
        Task task;
        task.fileName=tempDir+fn;
        cv::Size boardSize;
        cv::Mat imagePoint;
        bool success;
    }
    //тут заполнить blank
    QList<Task> result=QtConcurrent::blockingMapped(blank,calc);
    //тут собрать результаты
    qDebug()<<getMilliSecSince(time)<<"msec";
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
    qDebug()<<getMilliSecSince(time)<<"msec";
}

void CalibrateFolder::removeDir()
{
    QDir dir(tempDir);
    if (dir.exists()) dir.removeRecursively();
}
