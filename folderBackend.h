#pragma once

#include <QObject>
#include <QStandardPaths>
#include <QDebug>
#include <QUrl>
#include <QDir>

class FolderBackend : public QObject
{
    Q_OBJECT
public:
    explicit FolderBackend(QObject *parent = nullptr);
    Q_PROPERTY(QString url READ getUrl WRITE setUrl NOTIFY urlChanged)
    void setUrl(QString url);
    QString getUrl();

    Q_INVOKABLE void deleteOne(QString fileName);

signals:
    void urlChanged();
public slots:

private:
    QString m_path;
};
