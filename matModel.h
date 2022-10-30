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
    explicit MatModel(QObject* parent=nullptr);
    //explicit MatModel(QObject* parent=nullptr);
    MatModel(cv::Mat* mat,QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void updateMat();
    void newMat(cv::Mat* mat);
signals:

public slots:

private:
    cv::Mat *m_mat;
};
