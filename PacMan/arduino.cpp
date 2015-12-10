#include "arduino.h"

#ifdef USE_QT
void Arduino::run()
{
    serialPort.setPortName("COM3");
    serialPort.setBaudRate(9600);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    if(!serialPort.open(QIODevice::ReadWrite))
    {
        qDebug()<<"ArduinoController::run: serial port not open";
        return;
    }
    QByteArray data;
    while(true)
    {
        if(serialPort.waitForReadyRead(2000))
        {
            data.append(serialPort.readLine());
            if(data.right(1)=="\n")
            {
                QJsonDocument doc=QJsonDocument::fromJson(data);
                if(!doc.isNull())
                {
                    mutex.lock();
                    obj=doc.object();
                    mutex.unlock();
                }
                data.clear();
            }
        }
        else
        {
            qDebug()<<"ArduinoController::run: serial port not read";
        }
    }
}

Arduino::Arduino()
{
    serialPort.moveToThread(this);
    start();
}

Arduino &Arduino::getInstance()
{
    static Arduino instance;
    return instance;
}

double Arduino::getDoubleValueImp(const char *value)
{
    double r=0;
    mutex.lock();
    if(obj.contains(value)) r=obj[value].toDouble();
    mutex.unlock();
    return r;
}

#else

Arduino::Arduino()
{
}

double Arduino::getDoubleValueImp(const char *value)
{
    return 0;
}

#endif

double Arduino::getDoubleValue(const char *value)
{
    return getInstance().getDoubleValueImp(value);
}
