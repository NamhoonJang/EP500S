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

//*** LINCSOLUTION CUSTOM CODES
#include "../../inc/MarlinConfig.h"

#include "../gcode.h"
#include "../../lcd/marlinui.h"

/**
 * Mxxx
 */
bool Flag_M251 = 0;
void GcodeSuite::M251() {
  Flag_M251 = 1;
  LCD_SERIAL.begin(LCD_BAUDRATE);

  const millis_t serial_connect_timeout = millis() + 1000UL;
  while (!LCD_SERIAL.connected() && PENDING(millis(), serial_connect_timeout)) { /*nada*/ }
  SERIAL_ECHOLN("Serial1 begin 9600bps");
}




