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
    if (!index.isValid() || role != Qt::DisplayRole) return QVariant();
    return m_mat->at<qreal>(index.row());
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


