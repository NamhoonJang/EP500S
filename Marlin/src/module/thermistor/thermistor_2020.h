/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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

// R25 = 100 KOhm, beta25 = 4550 K, 4.7 kOhm pull-up, TDK NTCG104LH104KT1 https://product.tdk.com/en/search/sensor/ntc/chip-ntc-thermistor/info?part_no=NTCG104LH104KT1
constexpr temp_entry_t temptable_2020[] PROGMEM = {
{ OV(922),-20},
{ OV(961),-10},
{ OV(1000),0},
{ OV(1039),10},
{ OV(1078),20},
{ OV(1097),25},
{ OV(1117),30},
{ OV(1155),40},
{ OV(1194),50},
{ OV(1232),60},
{ OV(1271),70},
{ OV(1309),80},
{ OV(1328),85},
{ OV(1347),90},
{ OV(1385),100},
{ OV(1423),110},
{ OV(1461),120},
{ OV(1498),130},
{ OV(1536),140},
{ OV(1573),150},
{ OV(1611),160},
{ OV(1648),170},
{ OV(1685),180},
{ OV(1722),190},
{ OV(1759),200},
{ OV(1795),210},
{ OV(1832),220},
{ OV(1868),230},
{ OV(1905),240},
{ OV(1941),250},
{ OV(1977),260},
{ OV(2013),270},
{ OV(2049),280},
{ OV(2085),290},
{ OV(2121),300},
{ OV(2156),310},
{ OV(2192),320},
{ OV(2227),330},
{ OV(2262),340},
{ OV(2297),350},
{ OV(2332),360},
{ OV(2367),370},
{ OV(2402),380},
{ OV(2436),390},
{ OV(2471),400},
{ OV(2505),410},
{ OV(2540),420},
{ OV(2574),430},
{ OV(2608),440},
{ OV(2642),450},
{ OV(2676),460},
{ OV(2709),470},
{ OV(2743),480},
{ OV(2776),490},
{ OV(2810),500}
};