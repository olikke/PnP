#include "framemodel.h"

FrameModel::FrameModel(QObject *parent) : QAbstractListModel(parent)
{
    static bool registerMe=true;
    if (registerMe) {
        registerMe=false;
        qmlRegisterType<FrameModel>("com.FrameModel", 1, 0, "FrameModel");
    }
}

int FrameModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.size();
}

QVariant FrameModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
          return QVariant();
      }
      switch (role) {
      case FileNameRole:
          return m_data.at(index.row()).fileName;
      case FrameRole:
          return m_data.at(index.row()).frame;
      case SizeRole:
          return m_data.at(index.row()).size;
      case EnableRole:
          return m_data.at(index.row()).enable;
      case UIDRole:
          return m_data.at(index.row()).uid;
      default:
          return QVariant();
      }
}

https://stackoverflow.com/questions/33793346/qt-create-a-time-based-uuid

QHash<int, QByteArray> FrameModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[FileNameRole] = "fileName";
    roles[FrameRole] = "frame";
    roles[SizeRole] = "size";
    roles[EnableRole] = "enable";
    roles[UIDRole] = "uid";
    return roles;
}

void FrameModel::reload(QString filePath)
{
    beginResetModel();
    if (filePath.contains("file:///"))
    {
        filePath.remove(0,7);
    }
    QDir dir(filePath);
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.bmp"<<"*.jpeg";
    QStringList list = dir.entryList(filters,QDir::Files | QDir::NoDotAndDotDot);
    for (QString f: list ) {
        FrameStruct frameStruct(filePath+f);
        m_data.push_back(frameStruct);
    }
    endResetModel();
}



FrameStruct::FrameStruct(QString fn)
{
    fileName=fn;
    frame=QImage(fn);
    enable=!frame.isNull();
    size=frame.size();
    checked=false;
    static int numb=0;
    uid=numb++;
}
