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
#include "../../module/RS485test.h"
#include "../gcode.h"

/**
 * M253: Get Sub Controller Status
 */
void GcodeSuite::M253() {
  char getStatus[3] = {};
  getStatus[0] = 'g'; getStatus[1] = 'S';  getStatus[2] = 'T';
  LCD_SERIAL.print(getStatus);
  rx2_loop();
  //writeRS485(getStatus);
  //writeRS485("FAN", wfan_index, ": ", servo[servo_index].read());
}
