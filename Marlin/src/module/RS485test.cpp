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

#include "../inc/MarlinConfigPre.h"

#include "../core/serial.h"
#include "../MarlinCore.h"

#include "../gcode/gcode.h"

char rx_command[10] = {};
char rx_par[20] = {};
uint8_t command_len = 0;
uint8_t Count_Modbus_Status = 0;
uint8_t Count_All_Fan_Status = 0;
void writeRS485(char* msg485) {
  //WRITE(71, HIGH);

  strcat(msg485, "\r\n");
  SERIAL_ECHOLN("WRITING 485");
  LCD_SERIAL.print(msg485);
  // Serial2.print(msg485);

  while (Serial2.availableForWrite() < SERIAL_BUFFER_SIZE - 1) {
    gcode.dwell(1);
  }
  gcode.dwell(2);
  //WRITE(71, LOW);
  gcode.dwell(50);
  SERIAL_ECHOLN("reading");
  while (LCD_SERIAL.available()) {
    char in485 = LCD_SERIAL.read();
    if (in485 != '\r')
      SERIAL_CHAR(in485);
  }
}

void rx2_loop() {
  bool comm_end_sig = false;
  uint32_t cnt_temp = 0;
  uint8_t rx_num = 0;
  uint8_t rx1_cnt = 0;
  uint8_t rx1_i = 0;
  uint8_t rx1_endcnt =0;
  uint8_t SubCon_Status = 0;
  uint8_t Modbus_Status = 0;
  uint8_t All_Fan_Status = 0;
  uint16_t Current_sta = 0;
  uint16_t Blower_spd = 0;
  char rx1data = 0;
  char rx1_data[20] = {};
  //SERIAL_ECHOLN("RX2loopcall"); //eco test
  while(cnt_temp <= 1000){
    cnt_temp++;
  }
  cnt_temp = 0;
  while (LCD_SERIAL.available()){
    rx_command[command_len] = LCD_SERIAL.read();
    if(rx_command[command_len] > 0){
      rx1data = rx_command[command_len];

      if(rx1data == 10) {comm_end_sig = 1;  rx1_endcnt=rx1_cnt;}
      else                {comm_end_sig = 0;}

      if(!comm_end_sig)
      {
        rx_par[rx1_cnt] = rx1data;
        rx1_cnt++;
      }
      else
      {
        //Not in (comm_end_sig exit)
        for(rx1_i=0; rx1_i<20; rx1_i++)
        {
          if( rx1_i < rx1_cnt){rx1_data[rx1_i] = rx_par[rx1_i];}
          else{rx1_data[rx1_i] = 0x00; rx_par[rx1_i] = 0x00;}//NULL
        }
        rx1_cnt = 0;
      }
      //SERIAL_ECHOLN(rx_par[rx_num]);
      //SERIAL_ECHO("rx num : ");SERIAL_ECHOLN(rx1_data);
    }
    if((rx1_i == 19) && comm_end_sig){SERIAL_ECHOLN("endsig"); break;}
  }
  if(comm_end_sig){
    //SERIAL_ECHOLN("pars start"); //eco test
    //SERIAL_ECHOLN(rx1_data[0]);
    //SERIAL_ECHOLN(rx1_data[1]);
    //SERIAL_ECHOLN(rx1_data[2]);
    if(rx1_data[0] == 'g' && rx1_data[1] == 'S' && rx1_data[2] == 'T'){
      Modbus_Status = (rx1_data[3]-0x30);
      All_Fan_Status = (rx1_data[4]-0x30);
      SubCon_Status = ((rx1_data[3]-0x30)*10)+(rx1_data[4]-0x30);
      Current_sta = ((rx1_data[5]-0x30)*1000)+((rx1_data[6]-0x30)*100)+((rx1_data[7]-0x30)*10)+(rx1_data[8]-0x30);
      Blower_spd = ((rx1_data[9]-0x30)*1000)+((rx1_data[10]-0x30)*100)+((rx1_data[11]-0x30)*10)+(rx1_data[12]-0x30);

      SERIAL_ECHO("Sta_con:"); SERIAL_ECHO(SubCon_Status); SERIAL_ECHO(" Current_sta:"); SERIAL_ECHO(Current_sta);
      SERIAL_ECHO(" Blower_spd:"); SERIAL_ECHOLN(Blower_spd);

      if(Modbus_Status==2){
        Count_Modbus_Status++;
        if(Count_Modbus_Status>=2){
          host_action_cancel();
          host_action_prompt_begin(PROMPT_INFO, PSTR("Print Stop: [Cannot Check Chamber Fan Running]"));
          host_action_prompt_show();  
          Count_Modbus_Status = 0;
        }
        
      }
      if(All_Fan_Status==1){
        Count_All_Fan_Status++;
        if(Count_All_Fan_Status>=2){
          host_action_cancel();
          host_action_prompt_begin(PROMPT_INFO, PSTR("Print Stop: [Chamber Fan Not Running]"));
          host_action_prompt_show();
          Count_All_Fan_Status = 0;
        }
        
      }
    }
    //SERIAL_ECHOLN("pars end"); //eco test
  }
}