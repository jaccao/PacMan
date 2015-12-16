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
    bool connected;
    Arduino();
    static Arduino &getInstance();
    double getDoubleValueImp(const char* value);
public:
    static double getDoubleValue(const char* value);
    static bool isConnect();
};

#endif // ARDUINO_H
