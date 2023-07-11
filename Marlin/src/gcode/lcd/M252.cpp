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
//include "../../module/servo.h"

#define NUM_PWMFAN 2

uint8_t fanspeed_org = 0;

/**
 * M252: Get or set Fan speed. P<index> [S<speed : 0~255>]
 */
void GcodeSuite::M252() {

  if (!parser.seen('P')) return;

  const int wfan_index = parser.value_int();
  if (WITHIN(wfan_index, 0, NUM_PWMFAN - 1)) {
    if (parser.seen('S')) {
      int fanspeed = parser.value_int();
      fanspeed_org = fanspeed;
      if (fanspeed >= 255)
        {fanspeed = 255;}
      else if (fanspeed <= 0)
        {fanspeed = 0;}
      char setFan[8] = {};
      setFan[0] = 's'; setFan[1] = 'F';  setFan[2] = 'A'; setFan[3] = 'N';
      setFan[4] = 48 + wfan_index;
      if(fanspeed >=100)  
      {
        setFan[5] = 48 + int(fanspeed/100);
        setFan[6] = 48 + int(fanspeed%100/10);
        setFan[7] = 48 + int(fanspeed%100%10);
      }
      else if(fanspeed >= 10 || fanspeed < 100) 
      {
        setFan[5] = 48;
        setFan[6] = 48 + int(fanspeed/10);
        setFan[7] = 48 + int(fanspeed%10);
      }
      else
      {
        setFan[5] = 48;
        setFan[6] = 48;
        setFan[7] = 48 + fanspeed;
      }
      LCD_SERIAL.print(setFan);
      //writeRS485(setFan);
    }
    else
    {
      SERIAL_ECHO_MSG(" Fan Speed ", wfan_index, "(0-255): ", fanspeed_org);
      //추후 개선 
      //현재는 명령값으로 return
      //속도는 gST에서 rpm으로 체크
      //char getFan[5] = {};
      //getFan[0] = 'g'; getFan[1] = 'F';  getFan[2] = 'A'; getFan[3] = 'N';
      //getFan[4] = 48 + wfan_index;
      //LCD_SERIAL.print(getFan);
    }
  }
  else
    SERIAL_ERROR_MSG("Fan Index ", wfan_index, " out of range");

}
