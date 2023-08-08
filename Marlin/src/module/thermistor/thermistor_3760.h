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

#define REVERSE_TEMP_SENSOR_RANGE_21 1

#undef OV_SCALE
#define OV_SCALE(N) (float((N) * 5) / 3.3f)

// Pt100 with INA826 amplifier board with 5v supply based on Thermistor 20, with 3v3 ADC reference on the mainboard.
// If the ADC reference and INA826 board supply voltage are identical, Thermistor 20 instead.
constexpr temp_entry_t temptable_3760[] PROGMEM = {
  
  { OV(  0),    0 },
  { OV(227),   21 },
  { OV(236),   30 },
  { OV(245),   40 },
  { OV(253),   50 },
  { OV(262),   60 },
  { OV(270),   70 },
  { OV(279),   80 },
  { OV(287),   90 },
  { OV(295),  100 },
  { OV(304),  110 },
  { OV(312),  120 },
  { OV(320),  130 },
  { OV(329),  140 },
  { OV(337),  150 },
  { OV(345),  160 },
  { OV(353),  170 },
  { OV(361),  180 },
  { OV(369),  190 },
  { OV(377),  200 },
  { OV(385),  210 },
  { OV(393),  220 },
  { OV(401),  230 },
  { OV(409),  240 },
  { OV(417),  250 },
  { OV(424),  260 },
  { OV(432),  270 },
  { OV(440),  280 },
  { OV(447),  290 },
  { OV(455),  300 },
  { OV(463),  310 },
  { OV(470),  310 },
  { OV(478),  320 },
  { OV(485),  330 },
  { OV(493),  340 },
  { OV(500),  350 },
  { OV(507),  360 },
  { OV(515),  370 },
  { OV(522),  380 },
  { OV(529),  390 },
  { OV(537),  400 },
  { OV(544),  410 },
  { OV(614),  500 }
};

#undef OV_SCALE
#define OV_SCALE(N) (N)
