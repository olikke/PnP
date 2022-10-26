#include "folderBackend.h"

FolderBackend::FolderBackend(QObject *parent) :
    QObject(parent),
    m_path(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation))
{
}

void FolderBackend::setUrl(QString url)
{
    m_path=QUrl(url).toLocalFile();
    emit urlChanged();

}

QString FolderBackend::getUrl()
{
    return QUrl::fromLocalFile(m_path).toString();
}

void FolderBackend::deleteOne(QString fileName)
{
    QFile::remove(m_path+fileName);
}
