#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <QCoreApplication>
#include <QDebug>
#include <QColor>
#include <opencv2/opencv.hpp>
#include <QQmlApplicationEngine>

class MatModel :  public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MatModel(cv::Mat* mat, QObject* parent=nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void update();

    void saveMat(QString fileName, QString matName);

    void highlightRow(int numb);
    void highlightColumn(int numb);
    void hightlightNo();
signals:

public slots:

private:
    cv::Mat* m_mat;
    bool m_highlightRow=false;
    bool m_highlightCol=false;
    int m_highlightNumb=0;
};
