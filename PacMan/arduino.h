#ifndef ARDUINO_H
#define ARDUINO_H

#ifdef USE_QT

#include <QtSerialPort>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QMutex>

class Arduino:public QThread
{
    Q_OBJECT
private:
    QSerialPort serialPort;
    QJsonObject obj;
    QMutex mutex;
    void run();
#else
class Arduino
{
#endif
private:
    Arduino();
    static Arduino &getInstance();
    double getDoubleValueImp(const char* value);
public:
    static double getDoubleValue(const char* value);
};

#endif // ARDUINO_H
