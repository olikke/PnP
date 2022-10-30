#include "matModel.h"

MatModel::MatModel(QObject *parent):
  QAbstractListModel(parent),
  m_mat(new cv::Mat())
{
    static bool registerMe=true;
    if (registerMe) {
        registerMe=false;
        qmlRegisterType<MatModel>("com.MatDisplayModel", 1, 0, "MatDisplayModel");
    }
}

MatModel::MatModel(cv::Mat* mat,QObject *parent) :
    QAbstractListModel(parent),
    m_mat(mat)
{
    static bool registerMe=true;
    if (registerMe) {
        registerMe=false;
        qmlRegisterType<MatModel>("com.MatDisplayModel", 1, 0, "MatDisplayModel");
    }
}

int MatModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_mat->rows*m_mat->cols;
}

int MatModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_mat->cols;
}


QVariant MatModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) return QVariant();
    return m_mat->at<qreal>(index.row());
}

void MatModel::updateMat()
{
    beginResetModel();
    endResetModel();
}

void MatModel::newMat(cv::Mat *mat)
{
    //https://stackoverflow.com/questions/21659496/deep-copy-of-opencv-cvmat
    лучше работай с маt без указателей
    cv::Mat m=mat->clone();
    m_mat=&m;
    updateMat();
}



