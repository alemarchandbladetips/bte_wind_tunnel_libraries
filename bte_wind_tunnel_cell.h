#include "bte_wind_tunnel_motor.h"
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

//motor1_carte1 = bte_wind_tunnel_motor(0,pwm_driver1);

class bte_wind_tunnel_cell{
public:
	bte_wind_tunnel_cell();
	int8_t set_all_params(uint8_t offset, Adafruit_PWMServoDriver* pwm_driver,uint16_t min_motor,uint16_t max_motor,float max_power);
	int8_t power_rank0_motors(uint16_t pwm_int);
	int8_t power_rank1_motors(uint16_t pwm_int);
	int8_t power_rank2_motors(uint16_t pwm_int);
	int8_t power_all(uint16_t pwm_int);
	int8_t set_max_power(float max_power);
	int8_t get_power_in_cell();
	int8_t get_current_power();
	int8_t power_individual_motor(uint8_t motor_position,uint16_t pwm_int);
	int8_t power_individually(uint16_t pwm_int1, uint16_t pwm_int2, uint16_t pwm_int3, uint16_t pwm_int4, uint16_t pwm_int5, uint16_t pwm_int6);
	void enable();
	void disable();
	int8_t power_off_all_motors();
  
  
private:
	Adafruit_PWMServoDriver* _pwm_driver;
	bte_wind_tunnel_motor _motor[6];
	uint16_t _min_motor;
	uint16_t _max_motor;
	float _max_power;
  };