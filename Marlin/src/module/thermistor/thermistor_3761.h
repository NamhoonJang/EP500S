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
constexpr temp_entry_t temptable_3761[] PROGMEM = {
  
  { OV(  0),    0 },
  { OV(227),   31 },
  { OV(236),   40 },
  { OV(245),   50 },
  { OV(253),   60 },
  { OV(262),   70 },
  { OV(270),   80 },
  { OV(279),   90 },
  { OV(287),  100 },
  { OV(295),  110 },
  { OV(304),  120 },
  { OV(312),  130 },
  { OV(320),  140 },
  { OV(329),  150 },
  { OV(337),  160 },
  { OV(345),  170 },
  { OV(353),  180 },
  { OV(361),  190 },
  { OV(369),  200 },
  { OV(377),  210 },
  { OV(385),  220 },
  { OV(393),  230 },
  { OV(401),  240 },
  { OV(409),  250 },
  { OV(417),  260 },
  { OV(424),  270 },
  { OV(432),  280 },
  { OV(440),  290 },
  { OV(447),  300 },
  { OV(455),  310 },
  { OV(463),  320 },
  { OV(470),  330 },
  { OV(478),  340 },
  { OV(485),  350 },
  { OV(493),  360 },
  { OV(500),  370 },
  { OV(507),  380 },
  { OV(515),  390 },
  { OV(522),  400 },
  { OV(529),  410 },
  { OV(537),  420 },
  { OV(544),  430 },
  { OV(614),  500 }
};

#undef OV_SCALE
#define OV_SCALE(N) (N)
