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

#define maxPulse 32
unsigned char arrayPulse[maxPulse];
unsigned char posPulse;

#define maxSkin 64
unsigned int arraySkin[maxSkin];
unsigned char posSkin;

#define maxDistance 8
unsigned int arrayDistance[maxDistance];
unsigned char posDistance;

void setup()
{
  for(int i=0;i<maxPulse;i++) arrayPulse[i]=0;
  for(int i=0;i<maxSkin;i++) arraySkin[i]=0;
  for(int i=0;i<maxDistance;i++) arrayDistance[i]=0;
  Serial.begin(9600);
  pinMode(trigerPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
  int valueSkinRes = 1023;
  if(countSkin) valueSkinRes=sumSkin/countSkin;
  // Distance
  delay(delayTime);
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
  int valueDistance=0;
  if(countDistance) valueDistance=sumDistance/countDistance;
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
  int valuePulse=75;
  if(countPulse) valuePulse=sumPulse/countPulse;
  // Json
  sprintf(buf,"{\"temperature\":%i,\"analogX\":%i,\"analogY\":%i,\"skinResistence\":%i,\"distance\":%i,\"pulse\":%i}",valueTemperature,valueH-512,(valueV-512)*-1,valueSkinRes,valueDistance,valuePulse);
  Serial.println(buf);
}

