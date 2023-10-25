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


#include "../../../inc/MarlinConfig.h"
#include "../Marlin/src/module/probe.h"
// 핀 사용을 위한 헤더파일 추가
#include "../../../pins/sam/pins_RADDS.h"
#include "../Marlin/src/core/language.h"
#include "../Marlin/src/core/serial.h"
#include "../Marlin/src/module/planner.h"
#include "../Marlin/src/module/stepper.h"
#include "../Marlin/src/module/planner.h"
#include "../Marlin/src/module/tool_change.h"
#include "../Marlin/src/module/temperature.h"
#include "../Marlin/src/lcd/marlinui.h"
#include "../Marlin/src/module/motion.h"
#include "../Marlin/src/libs/nozzle.h"
#include "Wire.h"

bool T2_First_Move = false;
bool T2_Moved_CW = false;
bool T2_Moved_CCW = false;
bool IS_E2_Homed = false;
const float Tool_UpDown_Dist = 9.18; //10.2
float probePosX = Z_SAFE_HOMING_X_POINT;
float probePosY = Z_SAFE_HOMING_Y_POINT; 

const bool Check_E2Home()
    {
        if(digitalRead(LINC_E2_ENDSTOP_PIN)==HIGH) return false;
        else if(digitalRead(LINC_E2_ENDSTOP_PIN)==LOW) return true;
    }

#if ENABLED(LINCSOLUTION_CUSTOM_CODES)
    
    #include "../../gcode.h"
    //#include "../../../feature/lincsolution_custom_codes.h"
    float T0_Z, T1_Z;
    float e_move=0;
    
    /**
   * M130: IO(FET4, 5, 6) ON Control
   */
  void GcodeSuite::M130()
    {
        uint16_t VACCUM_ON_OFF = 0;
        uint16_t DOOR_CLOSE_OPEN = 0;
        uint16_t LAMP_ON_OFF = 0;
        uint16_t LED_RED_RATE = 0;
        uint16_t LED_GREEN_RATE = 0;
        uint16_t LED_BLUE_RATE = 0;
        
        if(parser.seenval('V')){
            VACCUM_ON_OFF = parser.value_ushort();
            analogWrite(LINC_VACCUM_PIN, VACCUM_ON_OFF);
        }
        if(parser.seenval('D')){
            DOOR_CLOSE_OPEN = parser.value_ushort();
            analogWrite(LINC_DOOR_SWITCH_PIN, DOOR_CLOSE_OPEN);
        }
        if(parser.seenval('L')){
            LAMP_ON_OFF = parser.value_ushort();
            analogWrite(LINC_LAMP_PIN, LAMP_ON_OFF);
        }
        if(parser.seenval('R')){
            LED_RED_RATE = parser.value_ushort();
            analogWrite(LINC_3LED_RED, LED_RED_RATE);
        }
        if(parser.seenval('G')){
            LED_GREEN_RATE = parser.value_ushort();
            analogWrite(LINC_3LED_GREEN, LED_GREEN_RATE);
        }
        if(parser.seenval('B')){
            LED_BLUE_RATE = parser.value_ushort();
            analogWrite(LINC_3LED_BLUE, LED_BLUE_RATE);
        }
        if(parser.seen('E')){
            if(digitalRead(LINC_E2_ENDSTOP_PIN)==HIGH) SERIAL_ECHOLNPAIR("E2 ENDSTOP STATE: HIGH");
            else if(digitalRead(LINC_E2_ENDSTOP_PIN)==LOW) SERIAL_ECHOLNPAIR("E2 ENDSTOP STATE: LOW");
            
        }
    }

    /**
    * M131: IO(FET4, 5, 6) OFF Control
    */
    void GcodeSuite::M131()
    {
        M134();
        M132();
        M133();
    }


    /**
    * M132: Calculate the height of Tool0 & Tool1 
    */
    void GcodeSuite::M132()///?
    {   
        //Calibrate Tool 0
        tool_change(0,false);   //T0, position change active. Help -> tool_change.h -> void tool_change(const uint8_t tmp_extruder, bool no_move=false);
        const xy_pos_t pos = {probePosX, probePosY}; //set the probing XY positions.
        //if (!probe.can_reach(pos)) return;        
        // HOME POSITION IS SETTED BY MINUS COORDINATE.. WITHIN(N,L,H) IS NOT WORKING PROPERLY.. 
        TERN_(HAS_LEVELING, set_bed_leveling_enabled(false));
        remember_feedrate_scaling_off();
        T0_Z = probe.probe_at_point(pos, PROBE_PT_STOW, 1);
        if (!isnan(T0_Z)) {
        SERIAL_ECHOLNPAIR("TOOL0 X: ", pos.x, " Y: ", pos.y, " Z: ", T0_Z);     //If T0_Z is measurable, echo the position of XYZ
        }
        restore_feedrate_and_scaling();
        probe.move_z_after_probing();
        report_current_position();
        
        //Calibrate Tool 1
        tool_change(1, false);   //tool change to T1
        //if (!probe.can_reach(pos)) return;
        TERN_(HAS_LEVELING, set_bed_leveling_enabled(false));
        remember_feedrate_scaling_off();
        T1_Z = probe.probe_at_point(pos, PROBE_PT_STOW, 1);
        if (!isnan(T1_Z)){
            SERIAL_ECHOLNPAIR("TOOL1 X: ", pos.x, " Y: ", pos.y, " Z: ", T1_Z);
        }
        else if(isnan(T1_Z)){
            SERIAL_ECHOLNPAIR("T1_Z: ",  T1_Z);
            tool_change(2, false);
            unscaled_e_move(5,5);
            tool_change(1, false);
        }
        restore_feedrate_and_scaling();
        probe.move_z_after_probing();
        report_current_position();

        tool_change(0, false);
        
        
    }

    /**
    * M133: Rotate E2 axis for calibrating the height difference of two extruders.
    */
    void GcodeSuite::M133()
    {
        float E2 = 5.1*(T0_Z-T1_Z);
        tool_change(2, false);
        SERIAL_ECHOLNPAIR("TOOL DIFFERENCE: ", E2);
        unscaled_e_move(E2, 5); //1st parameter: moving distance, 2nd parameter: moving speed.
        tool_change(0, false);
        SERIAL_ECHOLNPAIR("Calibration End");
    }

    /**
    * M134: Set home of E2 axis
    */
    void GcodeSuite::M134()//M134은 E2축 Homing 기능을 수행할 예정.
    {
        IS_E2_Homed = false;
        tool_change(2, false);   //tool change to T2
        unscaled_e_move(-15, 10);
        Check_E2Home();
        if(Check_E2Home()){
            SERIAL_ECHOLNPAIR("Moving Finished. Set T1 to Zero Position.");
            unscaled_e_move(16.1, 10); //Set E2 position at T1 Tool Offset(T1+1mm position) position.
            //unscaled_e_move(5.1, 10);
            SERIAL_ECHOLNPAIR("Calibration Finished.");
            tool_change(0, false);
            IS_E2_Homed = true;     //Set E2 has homed.
            T2_First_Move = true;   //After E2 homing, T2 movement for M136 code will recognize the 1st movement of T2.
            return;
        } 
        while(!Check_E2Home())
        {
            e_move-=0.01;
            unscaled_e_move(e_move,1);  
            e_move = 0;
            Check_E2Home();
        }
        SERIAL_ECHOLNPAIR("Moving Finished. Set T1 to Zero Position.");
        unscaled_e_move(16.1, 10); //Set E2 position at T1 Tool Offset(T1+2mm position) position.
        //unscaled_e_move(5.1, 10);
        SERIAL_ECHOLNPAIR("Calibration Finished.");
        tool_change(0, false);
        IS_E2_Homed = true;
        T2_First_Move = true;
    }

    /****
     * LINCSOLUTION CUSTOM CODE
     * M135: Post-Processing with chamber heating
     * [Parameters]
     * S: Target temperature for heating 2(or more/less) hours. Units are seconds.
     * P: Post-Processing time for Target temperature(Parameter S).
     * T: Decreasing ratio for Target temperature to Room termperature.

    ****/
    void GcodeSuite::M135()         
    {
        millis_t dwell_ms = 0;      //Dwelling time for the for loop -> related to the Decreasing ratio.
        millis_t dwell_hour = 0;    //Maintaining time at the target temperature: Parameter P
        celsius_t tempStart = 0;    //Target temperature: Parameter S
        int16_t tempPar = 0;        //Decreasing ratio for target temperature: Parameter T -> Unit: ºC/h = ºC/3600s
        int16_t tempLoop = 0;       //Temperature variable for the loop 
        
        if (parser.seenval('S')) tempStart = parser.value_celsius();
        if (parser.seenval('P')) dwell_hour = parser.value_millis_from_seconds();
        planner.synchronize();
        if (parser.seenval('T')) tempPar = parser.value_int();
        SERIAL_ECHOLNPAIR("S: ", tempStart, " P: ", dwell_hour/1000, " T: ", tempPar);
        dwell_ms = (3600/tempPar)*1000;
        SERIAL_ECHOLNPAIR("dwell_ms: ", dwell_ms);
        if(tempStart!=0 && dwell_hour!=0 && tempPar!=0){
            thermalManager.setTargetBed(tempStart);
            SERIAL_ECHOLNPAIR("Wait for Bed Temperature..");
            thermalManager.wait_for_bed_heating();
            SERIAL_ECHOLNPAIR("Waiting Time: ", dwell_hour/1000);
            dwell(dwell_hour);
            tempLoop = tempStart-1;
            for(int count=0; count <= tempStart; count++){
                if(tempLoop==100) {
                    thermalManager.setTargetBed(0); 
                    break;;
                    }
                SERIAL_ECHOLNPAIR("count:", count);
                thermalManager.setTargetBed(tempLoop);
                SERIAL_ECHOLNPAIR("SET TEMP: ", tempLoop);
                tempLoop--;
                dwell(dwell_ms);
            }
        }
        else {
            SERIAL_ECHOLNPAIR("Wrong usage");
            return;
        }
       
    }
    /****
     * LINCSOLUTION CUSTOM CODE
     * M136: T1 Extruder Tool Height Up-Down Script when Changing Tool.
     * This Script is written for the tool height up and down event when occurs on before the tool change.

    ****/
    void GcodeSuite::M136() {
        
        if(IS_E2_Homed){
            if(active_extruder == 0 && T2_First_Move){  //Only if this is the T2's first movement.
                do_blocking_move_to_z(current_position.z+5, 5); // added
                tool_change(2, true);   //edited from false
                unscaled_e_move(-Tool_UpDown_Dist, 30);
                T2_Moved_CW = true;
                T2_Moved_CCW = false;
                T2_First_Move = false;
                do_blocking_move_to_z(current_position.z-5, 5); // added
                tool_change(0, true); //edited from false
            }
            else if(active_extruder == 0 && !T2_Moved_CW && T2_Moved_CCW){  //If T2 moved down, Go Up.
                do_blocking_move_to_z(current_position.z+5, 5); // added
                tool_change(2, true);
                unscaled_e_move(-Tool_UpDown_Dist, 30);
                T2_Moved_CW = true;
                T2_Moved_CCW = false;
                do_blocking_move_to_z(current_position.z-5, 5); // added
                tool_change(0, true);
            }
            else if(active_extruder == 1 && !T2_Moved_CCW && T2_Moved_CW){  //If T2 moved up, Go Down.
                do_blocking_move_to_z(current_position.z+5, 5); // added
                tool_change(2, true);
                unscaled_e_move(Tool_UpDown_Dist, 30);
                T2_Moved_CCW = true;
                T2_Moved_CW = false;
                do_blocking_move_to_z(current_position.z-5, 5); // added
                tool_change(1, true);
            }
        }
        else SERIAL_ECHOLNPAIR("*****E2 is not Homed*****");
        
    }

   void GcodeSuite::M137(){
    
    bool VACCUM_PIN_ISHIGH = false;
    bool MOTOR_ALARM_ISHIGH = false;

    if(digitalRead(LINC_VACCUM_PASS_FAIL_PIN)==HIGH) VACCUM_PIN_ISHIGH = true;
    else if(digitalRead(LINC_VACCUM_PASS_FAIL_PIN)==LOW) VACCUM_PIN_ISHIGH = false;

    if(digitalRead(LINC_MOTOR_ALARM_READ_PIN)==LOW) MOTOR_ALARM_ISHIGH =true;
    else if(digitalRead(LINC_MOTOR_ALARM_READ_PIN)==HIGH) MOTOR_ALARM_ISHIGH = false;
    
    if(VACCUM_PIN_ISHIGH && MOTOR_ALARM_ISHIGH){
        SERIAL_ECHOLN("Vaccum Pressure is too LOW & MOTOR ALARM IS HIGH");
    }
    else if(VACCUM_PIN_ISHIGH && !MOTOR_ALARM_ISHIGH){
        SERIAL_ECHOLN("Vaccum Pressure is too LOW");
    }
    else if(!VACCUM_PIN_ISHIGH && MOTOR_ALARM_ISHIGH){
        SERIAL_ECHOLN("MOTOR ALARM IS HIGH");
    }
    else SERIAL_ECHOLN("Vaccum & Motor both Normal");
   }
    
    void GcodeSuite::M138(){
        uint16_t LED_RED_RATE = 0;
        uint16_t LED_GREEN_RATE = 0;
        uint16_t LED_BLUE_RATE = 0;

        if(parser.seenval('R')){
            LED_RED_RATE = parser.value_ushort();
            analogWrite(LINC_3LED_RED, LED_RED_RATE);
        }
        if(parser.seenval('G')){
            LED_GREEN_RATE = parser.value_ushort();
            analogWrite(LINC_3LED_GREEN, LED_GREEN_RATE);
        }
        if(parser.seenval('B')){
            LED_BLUE_RATE = parser.value_ushort();
            analogWrite(LINC_3LED_BLUE, LED_BLUE_RATE);
        }
    }   

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
#include "../Marlin/src/inc/MarlinConfig.h"
#include "../Marlin/src/gcode/feature/lincsolution_custom_codes/RS485test.h"
#include "../Marlin/src/gcode/gcode.h"
#include "../Marlin/src/lcd/marlinui.h"
/**
 * M251
 */
bool Flag_M251 = 0;
#define NUM_PWMFAN 2

uint8_t fanspeed_org = 0;

void GcodeSuite::M251() {
  Flag_M251 = 1;
  LCD_SERIAL.begin(LCD_BAUDRATE);

  const millis_t serial_connect_timeout = millis() + 1000UL;
  while (!LCD_SERIAL.connected() && PENDING(millis(), serial_connect_timeout)) { /*nada*/ }
  SERIAL_ECHOLN("Serial1 begin 9600bps");
}


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
      writeRS485(setFan);
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


/**
 * M253: Get Sub Controller Status
 */
void GcodeSuite::M253() {
  char getStatus[3] = {};
  getStatus[0] = 'g'; getStatus[1] = 'S';  getStatus[2] = 'T';
  LCD_SERIAL.print(getStatus);
  rx2_loop();
  writeRS485(getStatus);
  //writeRS485("FAN", wfan_index, ": ", servo[servo_index].read());
}

#endif
