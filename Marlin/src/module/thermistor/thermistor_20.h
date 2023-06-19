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

#define REVERSE_TEMP_SENSOR_RANGE_20 1

// Pt100 with INA826 amp on Ultimaker v2.0 electronics
constexpr temp_entry_t temptable_20[] PROGMEM = {
  {OV(0),   0},
  {OV(344+5),   1},
  {OV(358+5),   10},
  {OV(371+5),   20},
  {OV(383+5),   30},
  {OV(397+5),   40},
  {OV(409+5),   50},
  {OV(423+5),   60},
  {OV(435+5),   70},
  {OV(447+5),   80},
  {OV(461+5),   90},
  {OV(473+5),   100},
  {OV(485+5),   110},
  {OV(498+5),   120},
  {OV(511+5),   130},
  {OV(523+5),   140},
  {OV(535+5),   150},
  {OV(547+5),   160},
  {OV(559+5),   170},
  {OV(571+5),   180},
  {OV(583+5),   190},
  {OV(595+5),   200},
  {OV(608+5),   210},
  {OV(620+5),   220},
  {OV(632+5),   230},
  {OV(642+5),   240},
  {OV(655+5),   250},
  {OV(667+5),   260},
  {OV(677+5),   270},
  {OV(689+5),   280},
  {OV(702+5),   290},
  {OV(712+5),   300},
  {OV(724+5),   310},
  {OV(735+5),   320},
  {OV(747+5),   330},
  {OV(758+5),   340},
  {OV(768+5),   350},
  {OV(780+5),   360},
  {OV(791+5),   370},
  {OV(802+5),   380},
  {OV(814+5),   390},
  {OV(824+5),   400},
  {OV(930+5),   500}
};
