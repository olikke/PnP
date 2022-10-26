#pragma once

#include <QObject>
#include <QStandardPaths>
#include <QDebug>
#include <QUrl>
#include <QDir>

class FolderModelBackend : public QObject
{
    Q_OBJECT
public:
    explicit FolderModelBackend(QObject *parent = nullptr);
    Q_PROPERTY(QString url READ getUrl WRITE setUrl NOTIFY urlChanged)
    void setUrl(QString url);
    QString getUrl();

    Q_PROPERTY(bool empty READ getEmpty NOTIFY emptyChanged)
    bool getEmpty();

    Q_INVOKABLE void deleteOne(QString fileName);

signals:
    void urlChanged();
    void emptyChanged();
public slots:

private:
    QString m_path;
    bool m_empty;
};
