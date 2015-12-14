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

#include "DHT.h"

// Temperature
#define DHTPIN 2
// Joystick
#define joyPinV 0
#define joyPinH 1
// Skin
#define skinPin 2
// Distance
#define echoPin 7
#define trigerPin 8
// Hearth
#define pulsePin 3
// Delay
#define delayTime 5

// these variables are volatile because they are used during the interrupt service routine!
volatile int BPM;
volatile int Signal;
volatile int IBI = 600;
volatile boolean Pulse = false;
volatile boolean QS = false;

int maximumRange = 100;
int minimumRange = 0;
long duration, distance;

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  pinMode(trigerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  interruptSetup();
  dht.begin();
}

char buf[1024];

int getDistance(int trigP,int echoP)
{
 digitalWrite(trigP, LOW); 
 delayMicroseconds(2);
 digitalWrite(trigP, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigP, LOW);
 duration = pulseIn(echoP, HIGH);
 distance = duration/58.2;
 if (distance >= maximumRange || distance <= minimumRange) return 100;
 return(distance);
}

void loop()
{
  // Temperature
  delay(delayTime);             
  float temperature = dht.readTemperature();
  if(isnan(temperature))
  {
    temperature=0;
  }
  int valueTemperature=temperature;
  // Joystick
  delay(delayTime);             
  int valueH = analogRead(joyPinH);
  delay(delayTime);
  int valueV = analogRead(joyPinV);
  // Skin
  delay(delayTime);
  int valueSkinRes = analogRead(skinPin);
  // Distance
  delay(delayTime);
  int valueDistance=getDistance(trigerPin,echoPin);
  // Hearth
  if (QS == true) QS = false;
  int valuePulse=BPM;
  // Json
  sprintf(buf,"{\"temperature\":%i,\"analogX\":%i,\"analogY\":%i,\"skinResistence\":%i,\"distance\":%i,\"pulse\":%i}",valueTemperature,valueH-512,(valueV-512)*-1,valueSkinRes,valueDistance,valuePulse);
  Serial.println(buf);
}

