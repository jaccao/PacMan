/*
# Copyright (C) 2015, 2016
# Luiz Fernando Jaccao <luizfernandojaccao@gmail.com>
# William Malheiros Evangelista <williammalheiros_2@hotmail.com>
# Jose David Oliveira Nunes <david.nunes.co@hotmail.com>
# This file is part of PacMan Project - UdL/FACENS Sem Fronteira.
#
# PacMan is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# PacMan is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
*/

#include "arduino.h"

#ifdef USE_QT
void Arduino::run()
{
    serialPort.setPortName(QSettings("../arduino.ini",QSettings::IniFormat).value("Serial","COM1").toString());
    serialPort.setBaudRate(QSettings("../arduino.ini",QSettings::IniFormat).value("Baud",9600).toInt());
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    if(!serialPort.open(QIODevice::ReadWrite))
    {
        qDebug()<<"ArduinoController::run: serial port not open";
        return;
    }
    connected=true;
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
    connected=false;
    serialPort.moveToThread(this);
    start();
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
    connected=false;
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

bool Arduino::isConnect()
{
    return getInstance().connected;
}

Arduino &Arduino::getInstance()
{
    static Arduino instance;
    return instance;
}
