#pragma once

#include <QObject>
#include <QImage>
#include <QAbstractListModel>
#include <QDir>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <opencv2/opencv.hpp>

struct FrameStruct{
    FrameStruct(QString fn);
    QString fileName;
    QImage frame;
    QSize size;
    bool enable;
    bool checked;
    int uid;
};

class FrameModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FrameModel(QObject *parent = nullptr);

    enum Roles {
        FileNameRole = Qt::UserRole + 1,
        FrameRole,
        SizeRole,
        EnableRole,
        UIDRole
    };

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void reload(QString filePath);

signals:

private:
    QList<FrameStruct> m_data;

};


