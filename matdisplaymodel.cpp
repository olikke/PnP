#include "matdisplaymodel.h"

MatModel::MatModel(QObject *parent) :
    QAbstractListModel(parent)//,
  //  m_mat(mat)
{
    static bool registerMe=true;
    if (registerMe) {
        registerMe=false;
        qmlRegisterType<MatModel>("com.MatDisplayModel", 1, 0, "MatDisplayModel");
    }
}

//MatModel::MatModel(QObject *parent):
//    QAbstractListModel(parent),
//    m_mat(cv::Mat(3,3,CV_32FC1))
//{
//    static bool registerMe=true;
//    if (registerMe) {
//        registerMe=false;
//        qmlRegisterType<MatModel>("com.MatDisplayModel", 1, 0, "MatDisplayModel");
//    }
//}

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
    qDebug()<<index.row()<<m_mat->at<float>(index.row());
    return m_mat->at<float>(index.row());
}

void MatModel::newMat(cv::Mat *mat)
{
    beginResetModel();
    m_mat=mat;
    endResetModel();
}

//QStringList toString(cv::Mat mat)
//{
//    QStringList result;
//    for (int i=0; i<mat.rows; i++) {
//        QString ss;
//        for (int j=0; j<mat.cols; j++)
//            ss+=" "+QString::number(mat.at<float>(i,j));
//        result.push_back(ss);
//    }
//    return result;
//}

void MatModel::updateMat(/*cv::Mat mat*/)
{
//    qDebug()<<toString(mat);
//    qDebug()<<toString(m_mat);
    beginResetModel();
  //  mat.copyTo(m_mat);
    endResetModel();
 //   qDebug()<<toString(m_mat);
}



