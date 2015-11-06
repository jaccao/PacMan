/*
# Copyright (C) 2015, 2016 Luiz Fernando Jaccao <luizfernandojaccao@gmail.com>
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

#ifdef USE_QT

#include "arduinocontroller.h"

void ArduinoController::run()
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

ArduinoController::ArduinoController(QObject *parent) : QThread(parent)
{
    serialPort.moveToThread(this);
    start();
}

double ArduinoController::analogX()
{
    double r=0;
    mutex.lock();
    if(obj.contains("analogX")) r=obj["analogX"].toDouble()/obj["scale"].toDouble();
    mutex.unlock();
    return r;
}

double ArduinoController::analogY()
{
    double r=0;
    mutex.lock();
    if(obj.contains("analogY")) r=obj["analogY"].toDouble()/obj["scale"].toDouble();
    mutex.unlock();
    return r;
}

void ArduinoController::display(Game &game)
{
    (void)game;
}

void ArduinoController::keyboard(Game &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void ArduinoController::keyboardUp(Game &game, unsigned char c, int x, int y)
{
    (void)game;
    (void)c;
    (void)x;
    (void)y;
}

void ArduinoController::idle(Game &game)
{
    (void)game;
}

int ArduinoController::digitalX()
{
    return((int)(analogX()*1.9));
}

int ArduinoController::digitalY()
{
    return((int)(analogY()*1.9));
}

#endif
