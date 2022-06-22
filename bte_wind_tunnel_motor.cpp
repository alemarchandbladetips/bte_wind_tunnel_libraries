#include "bte_wind_tunnel_motor.h"

#define POWER_FROM_PWM_A0 -1500.0
#define POWER_FROM_PWM_A1 1.5
#define POWER_FROM_PWM_A2 0.0

#define PWM_DRIVER_MIN_POSITION 0
#define PWM_DRIVER_MAX_POSITION 15

bte_wind_tunnel_motor::bte_wind_tunnel_motor()
{
  	_power_flag = 0;
  	_pwm_int = 0;
}

int8_t bte_wind_tunnel_motor::set_all_params(uint8_t motor_position, Adafruit_PWMServoDriver* pwm_driver,uint16_t min_motor,uint16_t max_motor)
{
	// fails if max < min
	if( (min_motor > max_motor) || (motor_position < PWM_DRIVER_MIN_POSITION) || (motor_position > PWM_DRIVER_MAX_POSITION) ) 
	{
		return -1;
	}
	_motor_position = motor_position;
	_pwm_driver = pwm_driver;
	set_range(min_motor,max_motor);
	set_pwm(min_motor);
	
	return 0;
}

int8_t bte_wind_tunnel_motor::set_range(uint16_t min_motor,uint16_t max_motor)
{
	// fails if min < max
  	if ( min_motor > max_motor) 
	{
		return -1;
	}
	
  	_min_motor = min_motor;
  	_max_motor = max_motor;
  	
  	return 0;
}

int8_t bte_wind_tunnel_motor::set_pwm(uint16_t pwm_int)
{
	// fails if pwm > max or pwm > min or motor is off
	if (_power_flag == 0){
		return -3;
	}
  	if( (pwm_int>_max_motor) || (pwm_int<_min_motor) )
  	{
  		return -2;
  	}
  	
  	_pwm_int = pwm_int;
  	_pwm_driver->writeMicroseconds(_motor_position,_pwm_int);
  	
  	return 0;
}

int8_t bte_wind_tunnel_motor::set_thrust_level(float thrust_level)
{
	float pwm_tmp;
	
	if (_power_flag == 0){
		return -3;
	}
	if(thrust_level>1.0 || thrust_level<0.0)
	{
		return -2;
	}

	pwm_tmp = get_pwm_from_thrust_level(thrust_level);

  	return set_pwm((uint16_t)pwm_tmp);
}

uint16_t bte_wind_tunnel_motor::get_current_pwm(void)
{
	return _pwm_int;
}

      
float bte_wind_tunnel_motor::get_current_power(void)
{
	return get_power_from_pwm(get_current_pwm());
}

void bte_wind_tunnel_motor::power_off(void)
{
	//set min pwm the motor
	_pwm_int = _min_motor;
    _pwm_driver->writeMicroseconds(_motor_position,_pwm_int);
}

void bte_wind_tunnel_motor::enable(void)
{
	_power_flag = 1;
	_pwm_driver->writeMicroseconds(_motor_position,_min_motor);
}

void bte_wind_tunnel_motor::disable(void)
{
	power_off();
	_power_flag = 0;
}

uint16_t bte_wind_tunnel_motor::get_pwm_from_thrust_level(float thrust_level)
{
	float pwm_tmp;
	
	pwm_tmp = (float)_min_motor + thrust_level * ((float)_max_motor - (float)_min_motor);

  	return (uint16_t)pwm_tmp;
}

// Function outside of the class

float get_power_from_pwm(uint16_t pwm_int)
{
	// pwm casted in float for computation
	float pwm_tmp = (float)pwm_int;
  	float power = POWER_FROM_PWM_A0 + POWER_FROM_PWM_A1*pwm_tmp + POWER_FROM_PWM_A2*pwm_tmp*pwm_tmp;

  	return power;
}

