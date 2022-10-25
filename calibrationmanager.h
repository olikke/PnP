#pragma once

#include <QObject>

class CalibrationManager : public QObject
{
    Q_OBJECT
public:
    explicit CalibrationManager(QObject *parent = nullptr);

    Q_INVOKABLE void startCalibration(QString path, QStringList fileName);

signals:

public slots:
};
