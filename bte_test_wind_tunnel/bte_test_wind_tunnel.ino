#include "bte_wind_tunnel.h"

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


bte_wind_tunnel wind_tunnel;

int8_t ret_val;
uint16_t pwm_ret;
float power_ret;

void setup() {
  Serial.begin(115200);
  Serial.println("//////////////////////////////////////////");
  Serial.println("Test for the bte_wind_tunnel_motor");
  Serial.println("//////////////////////////////////////////");

  

  Serial.print("Don't exceed the max power in cell");
  ret_val = wind_tunnel.set_max_cell_power(10500);
  if(ret_val==-1)
  {
    Serial.println(" Test OK");
  } 
  else
  {
    Serial.println(" Test FAILED");
  }


  Serial.println("//////////////////////////////////////////");
  Serial.println("Test finished");
  Serial.println("//////////////////////////////////////////");
  
}

// You can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. It's not precise!


void loop() {

}
