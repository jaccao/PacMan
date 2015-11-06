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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

char buf[256];

void loop() {
  sprintf(buf,"{\"scale\":1,\"analogX\":%i,\"analogY\":%i}",rand()%3-1,rand()%3-1);
  Serial.println(buf);
  delay(1000);
}
