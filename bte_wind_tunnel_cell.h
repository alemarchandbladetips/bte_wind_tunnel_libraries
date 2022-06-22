#ifndef BTE_WIND_TUNNEL_CELL_H_
  #define BTE_WIND_TUNNEL_CELL_H_

#include "bte_wind_tunnel_motor.h"
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

class bte_wind_tunnel_cell{
public:
	bte_wind_tunnel_cell();
	int8_t set_all_params(uint8_t offset, Adafruit_PWMServoDriver* pwm_driver,uint16_t min_motor,uint16_t max_motor,float max_power);
	int8_t power_rank0_motors(float thrust_level);
	int8_t power_rank1_motors(float thrust_level);
	int8_t power_rank2_motors(float thrust_level);
	int8_t power_all(uint16_t pwm_int);
	int8_t set_max_power(float max_power);
	int8_t get_power_in_cell(void);
	int8_t get_current_power(void);
	int8_t power_individual_motor(uint8_t motor_position,float thrust_level);
	int8_t power_individually(uint16_t pwm_int1, uint16_t pwm_int2, uint16_t pwm_int3, uint16_t pwm_int4, uint16_t pwm_int5, uint16_t pwm_int6);
	void enable(void);
	void disable(void);
	void power_off_all_motors(void);
  
  
private:
	bte_wind_tunnel_motor _motor[6];
	float _max_power;
  };
  
#endif