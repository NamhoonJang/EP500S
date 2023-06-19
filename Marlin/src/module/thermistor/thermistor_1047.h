/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#define REVERSE_TEMP_SENSOR_RANGE_1047 1

// Pt1000 with 4k7 pullup
constexpr temp_entry_t temptable_1047[] PROGMEM = {
  // only a few values are needed as the curve is very flat
  PtLine(  0, 1000, 4700),
  PtLine( 10, 1000, 4700),
  PtLine( 20, 1000, 4700),
  PtLine( 30, 1000, 4700),
  PtLine( 40, 1000, 4700),
  PtLine( 50, 1000, 4700),
  PtLine( 60, 1000, 4700),
  PtLine( 70, 1000, 4700),
  PtLine( 80, 1000, 4700),
  PtLine( 90, 1000, 4700),
  PtLine(100, 1000, 4700),
  PtLine(110, 1000, 4700),
  PtLine(120, 1000, 4700),
  PtLine(130, 1000, 4700),
  PtLine(140, 1000, 4700),
  PtLine(150, 1000, 4700),
  PtLine(160, 1000, 4700),
  PtLine(170, 1000, 4700),
  PtLine(180, 1000, 4700),
  PtLine(190, 1000, 4700),
  PtLine(200, 1000, 4700),
  PtLine(210, 1000, 4700),
  PtLine(220, 1000, 4700),
  PtLine(230, 1000, 4700),
  PtLine(240, 1000, 4700),
  PtLine(250, 1000, 4700),
  PtLine(260, 1000, 4700),
  PtLine(270, 1000, 4700),
  PtLine(280, 1000, 4700),
  PtLine(290, 1000, 4700),
  PtLine(300, 1000, 4700),
  PtLine(310, 1000, 4700),
  PtLine(320, 1000, 4700),
  PtLine(330, 1000, 4700),
  PtLine(340, 1000, 4700),
  PtLine(350, 1000, 4700),
  PtLine(360, 1000, 4700),
  PtLine(370, 1000, 4700),
  PtLine(380, 1000, 4700),
  PtLine(390, 1000, 4700),
  PtLine(400, 1000, 4700),
  PtLine(410, 1000, 4700),
  PtLine(420, 1000, 4700),
  PtLine(430, 1000, 4700),
  PtLine(440, 1000, 4700),
  PtLine(450, 1000, 4700),
  PtLine(460, 1000, 4700),
  PtLine(470, 1000, 4700),
  PtLine(480, 1000, 4700),
  PtLine(490, 1000, 4700),
  PtLine(500, 1000, 4700)
};
