#include "foldermodelbackend.h"

FolderModelBackend::FolderModelBackend(QObject *parent) :
    QObject(parent),
    m_path(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation))
{
        m_empty=QDir(m_path).isEmpty();
}

void FolderModelBackend::setUrl(QString url)
{
    m_path=QUrl(url).toLocalFile();
    m_empty=QDir(m_path).isEmpty();
    emit emptyChanged();
    emit urlChanged();

}

QString FolderModelBackend::getUrl()
{
    return QUrl::fromLocalFile(m_path).toString();
}

bool FolderModelBackend::getEmpty()
{
    return m_empty;
}

void FolderModelBackend::deleteOne(QString fileName)
{
    QFile::remove(m_path+fileName);
}
