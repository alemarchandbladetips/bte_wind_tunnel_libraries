#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "bte_wind_tunnel_cell.h"
#include "bte_arduino_test_framework.h"

//valeurs de retour
int8_t ret_val; 

bte_wind_tunnel_cell cell1;
Adafruit_PWMServoDriver pwm_driver1 = Adafruit_PWMServoDriver(0x40); //nothing

bte_wind_tunnel_motor motor1;

void setup() {
  Serial.begin(115200);
  Serial.println("//////////////////////////////////////////");
  Serial.println("Test for the bte_wind_tunnel_cell");
  Serial.println("//////////////////////////////////////////");

  cell1.set_all_params(0, pwm_driver1,1000,2000, 3000);

  Serial.print("parameters setting check"); 
  uint8_t i; 
  for(i=0;i<6;i++)
  {
    _motor[i].set_all_params(0, pwm_driver1,999,2000, 3000);
  }
    for(i=0;i<6;i++)
  {
    _motor[i].set_all_params(0, pwm_driver1,1000,2001, 3000);
  }
  

  Serial.print("Don't exceed the max power in a cell");
  ret_val = cell1.power_individual_motor(0,1200);
  bte_arduino_test_framework(ret_val, -1);



  Serial.print("Don't exceed the max power in rank0");
  ret_val = cell1.power_rank0_motors(2100);
  bte_arduino_test_framework(ret_val, -1);



  Serial.print("Don't exceed the max power in rank1");
  ret_val = cell1.power_rank1_motors(1100);
  bte_arduino_test_framework.h

  Serial.print("Don't exceed the max power in rank2");
  ret_val = cell1.power_rank1_motors(2001);
  bte_arduino_test_framework(ret_val, -1);


  Serial.print("Don't exceed the max power individually");
  ret_val = cell1.power_individually(2000,2000,2000,2000,2000,2000);
  bte_arduino_test_framework(ret_val, -1);


  
  Serial.println("//////////////////////////////////////////");
  Serial.println("Test finished");
  Serial.println("//////////////////////////////////////////");
  
}


void loop() {

}
