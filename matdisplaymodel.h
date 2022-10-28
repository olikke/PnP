#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <opencv2/opencv.hpp>
#include <QQmlApplicationEngine>
#include <QDebug>

class MatModel :  public QAbstractListModel
{
    Q_OBJECT
public:
    //explicit MatModel(QObject* parent=nullptr);
    MatModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void newMat(cv::Mat * mat);
    void updateMat(/*cv::Mat mat*/);
signals:

public slots:

private:
    cv::Mat *m_mat;
};
