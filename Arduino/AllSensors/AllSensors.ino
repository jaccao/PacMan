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
#define DHTPIN 4
// Joystick
#define joyPinV 0
#define joyPinH 1
#define buttonPin 4
// Skin
#define skinPin 2
// Distance
#define echoPin 7
#define trigerPin 8
// Hearth
#define pulsePin 3
// Delay
#define delayTime 1

// these variables are volatile because they are used during the interrupt service routine!
volatile int BPM;
volatile int Signal;
volatile int IBI = 600;
volatile boolean Pulse = false;
volatile boolean QS = false;

int maximumRange = 100;
int minimumRange = 0;
long duration, distance;

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#define maxPulse 32
unsigned char arrayPulse[maxPulse];
unsigned char posPulse;

#define maxSkin 64
unsigned int arraySkin[maxSkin];
unsigned char posSkin;

#define maxDistance 8
unsigned int arrayDistance[maxDistance];
unsigned char posDistance;

#define keyD 13

void setup()
{
  for(int i=0;i<maxPulse;i++) arrayPulse[i]=0;
  for(int i=0;i<maxSkin;i++) arraySkin[i]=0;
  for(int i=0;i<maxDistance;i++) arrayDistance[i]=0;
  pinMode(keyD, OUTPUT);
  pinMode(trigerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(keyD, HIGH);
  Serial.begin(38400);
  Serial.print("AT\r\n");
  delay(1000);
  Serial.print("AT+UART=38400,1,0\r\n");
  delay(1000);
  digitalWrite(keyD, LOW);
  interruptSetup();
  dht.begin();
}

char buf[256];

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

int count=0;
int valueTemperature;
int valueH;
int valueV;
int valueButton;
int valueSkinRes;
int valueDistance;
int valuePulse;
#define lowPriority 50
#define mediumPriority 25
#define highPriority 12
#define realPriority 5

#define debug 0

void loop()
{
  int haveChange;
  int tmp;
  haveChange=0;
  if(count%lowPriority==0)
  {
    // Temperature
    float temperature = dht.readTemperature();
    if(isnan(temperature))
    {
      temperature=0;
    }
    tmp=temperature;
    if(valueTemperature!=tmp)
    {
      if(debug) Serial.println("Changed by valueTemperature");
      valueTemperature=tmp;
      haveChange=1;
     }
  }
  // Joystick
  if(count%realPriority==0)
  {
    tmp = analogRead(joyPinH) & 0b1111111111111000;
    tmp-=512;
    if(valueH!=tmp)
    {
      if(debug) Serial.println("Changed by valueH");
      valueH=tmp;
      haveChange=1;
     }
  }
  if(count%realPriority==1)
  {
    tmp = analogRead(joyPinV) & 0b1111111111111000;
    tmp-=512;
    tmp*=-1;
    if(valueV!=tmp)
    {
      if(debug) Serial.println("Changed by valueV");
      valueV=tmp;
      haveChange=1;
    }
  }
  if(count%realPriority==2)
  {
    tmp = analogRead(buttonPin);
    tmp = (tmp<128?1:0);
    if(valueButton!=tmp)
    {
      if(debug) Serial.println("Changed by valueButton");
      valueButton=tmp;
      haveChange=1;
    }
  }
  // Skin
  if(count%mediumPriority==0)
  {
    if(posSkin>=maxSkin) posSkin=0;
    arraySkin[posSkin]=analogRead(skinPin);
    posSkin++;
    unsigned long sumSkin=0;
    int countSkin=0;
    for(int i=0;i<maxSkin;i++)
    {
      if(arraySkin[i])
      {
        sumSkin+=arraySkin[i];
        countSkin++;
      }
    }
    if(countSkin)
    {
      tmp=sumSkin/countSkin;
      if(valueSkinRes!=tmp)
      {
        if(debug) Serial.println("Changed by valueSkin");
        valueSkinRes=tmp;
        haveChange=1;
      }
    }
  }
  if(count%mediumPriority==0)
  {
    // Distance
    if(posDistance>=maxDistance) posDistance=0;
    int readDistance=getDistance(trigerPin,echoPin);
    if(readDistance>=5) if(readDistance<=90)
    {
      arrayDistance[posDistance]=readDistance;
      posDistance++;
    }
    unsigned long sumDistance=0;
    int countDistance=0;
    for(int i=0;i<maxDistance;i++)
    {
      if(arrayDistance[i])
      {
        sumDistance+=arrayDistance[i];
        countDistance++;
      }
    }
    if(countDistance)
    {
      tmp=(sumDistance/countDistance) & 0b1111111111111100;
      if(valueDistance!=tmp)
      {
        if(debug) Serial.println("Changed by valueDist");
        valueDistance=tmp;
        haveChange=1;
      }
    }
  }
  if(count%highPriority==0)
  {
    // Hearth
    // average of last maxPulse reads
    if(posPulse>=maxPulse) posPulse=0;
    // only valid pulses!
    if(BPM>=75) if(BPM<=200)
    {
      arrayPulse[posPulse]=BPM;
      posPulse++;
    }
    int sumPulse=0;
    int countPulse=0;
    for(int i=0;i<maxPulse;i++)
    {
      if(arrayPulse[i])
      {
        sumPulse+=arrayPulse[i];
        countPulse++;
      }
    }
    if (QS == true) QS = false;
    if(countPulse)
    {
      tmp=(sumPulse/countPulse) & 0b1111111111111100;
      if(valuePulse!=tmp)
      {
        if(debug) Serial.println("Changed by valuePulse");
        valuePulse=tmp;
        haveChange=1;
      }
    }
  }
  if(haveChange==1)
  {
    // Json
    sprintf(buf,"{\"temperature\":%i,\"analogX\":%i,\"analogY\":%i,\"button\":%i,\"skinResistence\":%i,\"distance\":%i,\"pulse\":%i}",valueTemperature,valueH,valueV,valueButton,valueSkinRes,valueDistance,valuePulse);
    Serial.println(buf);
  }
  count++;
}

