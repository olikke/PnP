#include "matModel.h"

MatModel::MatModel(cv::Mat* mat, QObject *parent):
  QAbstractListModel(parent),
  m_mat(mat)
{
    static bool registerMe=true;
    if (registerMe) {
        registerMe=false;
        qRegisterMetaType<MatModel*>("MatModel*");
    }
}

//in Qt5.11 we dont have qml TableView. So we use GridView with some bike
int MatModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(m_mat->total());
}

int MatModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_mat->cols;
}

QVariant MatModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    switch (role) {
    case Qt::DisplayRole: {
        if (m_mat->type()==CV_32FC1)  return m_mat->at<float>(index.row());
        if (m_mat->type()==CV_64FC1) return m_mat->at<double>(index.row());
        qDebug()<<"UNKNOWN DATA TYPE"<<m_mat->type();
        return -1;
    }
    case Qt::DecorationRole: {
        return (m_highlightCol && index.row()%m_mat->cols==m_highlightNumb) ||
               (m_highlightRow && index.row()/m_mat->cols==m_highlightNumb);
    }
    default:
        return QVariant();
    }
}

void MatModel::update()
{
    beginResetModel();
    endResetModel();
}

void MatModel::saveMat(QString fileName,QString matName)
{
    cv::FileStorage fs(fileName.toLatin1().constData(), cv::FileStorage::WRITE);
    fs<<matName.toLatin1().constData()<<*m_mat;
}

void MatModel::highlightRow(int numb)
{
    m_highlightCol=false;
    m_highlightNumb=numb;
    m_highlightRow=numb>=0 & numb<m_mat->rows;
    update();
}

void MatModel::highlightColumn(int numb)
{
    m_highlightRow=false;
    m_highlightNumb=numb;
    m_highlightCol=numb>=0 & m_highlightNumb<m_mat->cols;
    update();
}

void MatModel::hightlightNo()
{
    m_highlightCol=false;
    m_highlightRow=false;
    update();
}



