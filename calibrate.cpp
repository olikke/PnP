#include "calibrate.h"

Calibrate::Calibrate(QObject *parent, int boardWidth, int boardHeight, float squareSize) :
    QObject(parent),
    tempDir(QCoreApplication::applicationDirPath()+"/.temporary/")
{
    m_boardSize=cv::Size(boardWidth,boardHeight);
    if (!reloadDir()) qDebug()<<"Не удалось создать папку для временных файлов";
    for (int i=0; i<boardWidth; i++)  //какой порядок,
        for (int j=0; j<boardHeight; j++)
            objPointsConst.push_back(cv::Point3f(i*squareSize,j*squareSize,0));
}

Calibrate::~Calibrate()
{
    removeDir();
}

Task calc(const Task &task)
{
    Task newTask=task;
    cv::Mat frame=cv::imread(newTask.fileName.toLatin1().constData());
    cv::Size s=frame.size();
    const cv::TermCriteria criteria=cv::TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,task.app->getIterations(),task.app->getEpsilon());
    cv::cvtColor(frame,frame,CV_BGR2GRAY);
    newTask.success=cv::findChessboardCorners(frame,task.app->boardSize(),newTask.corners);
    if (newTask.success) {
        //olikke cv::Size(11,11) зона поиска - изменение/производительность/точность
        // cv::Size(-1,-1) мёртвая зона
        cv::cornerSubPix(frame,newTask.corners,cv::Size(11,11),cv::Size(-1,-1),criteria);
        cv::cvtColor(frame,frame,CV_GRAY2BGR);
        cv::drawChessboardCorners(frame,task.app->boardSize(),newTask.corners,newTask.success);
    }
    cv::imwrite(newTask.fileName.toLatin1().constData(),frame);
    return newTask;
}

void Calibrate::start(QString url, QStringList fileName)
{
    if (!reloadDir()) {
        m_timeFindCorners=0;
        emit timeFindCornersChanged();
    }
    std::chrono::high_resolution_clock::time_point time;
    getTime(time);
    QDir source(QUrl(url).toLocalFile());
    QStringList list = source.entryList(QDir::Files | QDir::AllEntries | QDir::NoDotAndDotDot);
    QList<Task> blank;
    for (QString fn: list) {
        if (!fileName.contains(fn)) continue;
        QFile::copy(QUrl(url).toLocalFile()+"/"+fn, tempDir+fn);
        Task task;
        task.app=this;
        task.fileName=tempDir+fn;
        blank.push_back(task);
    }
    QList<Task> result=QtConcurrent::blockingMapped(blank,calc);
    //посчитай и выведи кол-во верных кадров
    for (Task task:result) {
        if (!task.success) continue;
        objPoints.push_back(objPointsConst);
        imgPoints.push_back(task.corners);
    }
    cv::Mat cameraMatrix=cv::Mat(3,3,CV_32FC1);
    cv::Mat distCoeffs;//=cv::Mat(5,1,CV_32FC1);
    //https://stackoverflow-com.translate.goog/questions/53277597/fundamental-understanding-of-tvecs-rvecs-in-opencv-aruco?_x_tr_sl=en&_x_tr_tl=ru&_x_tr_hl=ru&_x_tr_pto=sc
    cv::_OutputArray rvecs;
    cv::_OutputArray tvecs;
    qDebug()<<cv::calibrateCamera(objPoints,imgPoints,cv::Size(1920,1200),cameraMatrix,distCoeffs,rvecs,tvecs,0,cv::TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,m_iterations,m_epsilon));
    qDebug()<<toString(cameraMatrix);
    qDebug()<<"";
    qDebug()<<toString(distCoeffs);
    m_timeFindCorners=getMilliSecSince(time);
    emit timeFindCornersChanged();
}

void Calibrate::removeDir()
{
    QDir dir(tempDir);
    if (dir.exists()) dir.removeRecursively();
}

bool Calibrate::reloadDir()
{
    removeDir();
    return QDir(tempDir).mkdir(tempDir);
}

QStringList Calibrate::toString(cv::Mat mat)
{
    QStringList result;
    for (int i=0; i<mat.rows; i++) {
        QString ss;
        for (int j=0; j<mat.cols; j++)
            ss+=" "+QString::number(mat.at<double>(i,j));
        result.push_back(ss);
    }
    return result;
}
