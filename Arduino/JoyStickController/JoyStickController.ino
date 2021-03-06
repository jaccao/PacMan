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

int joyPinH = 0;
int joyPinV = 1;

void setup() {
  Serial.begin(9600);
}

char buf[256];

void loop() {
  int valueH = analogRead(joyPinH);   
  delay(100);             
  int valueV = analogRead(joyPinV);   
  sprintf(buf,"{\"scale\":512,\"analogX\":%i,\"analogY\":%i}",valueH-512,(valueV-512)*-1);
  Serial.println(buf);
  delay(100);             
}

