#include "bte_wind_tunnel_cell.h"


bte_wind_tunnel_cell::bte_wind_tunnel_cell(){
}

int8_t bte_wind_tunnel_cell::set_all_params(uint8_t offset, Adafruit_PWMServoDriver* pwm_driver,uint16_t min_motor,uint16_t max_motor, float max_power)
{
	uint8_t i;
	
	_max_power = max_power; // equiv to this->_max_power = max_power;
	
	for(i=0;i<6;i++)
	{
		_motor[i].set_all_params(i+offset, pwm_driver, min_motor, max_motor);
		// TDB : handle error return
	}
	return 0;
}

int8_t bte_wind_tunnel_cell::power_individual_motor(uint8_t motor_position, float thrust_level)
{

	if( (get_power_in_cell() - _motor[motor_position].get_current_power() + get_power_from_pwm(_motor[motor_position].get_pwm_from_thrust_level(thrust_level))) < _max_power )
	{
		return _motor[motor_position].set_thrust_level(thrust_level);
	}
	else
	{
		return -1;
	}
	
}



int8_t bte_wind_tunnel_cell::get_power_in_cell(void)
{
	float total_power = 0;
	uint8_t i;
	for(i=0;i<6;i++){
		total_power += _motor[i].get_current_power();
	}
	return total_power;
}


//powers the inner motor
int8_t bte_wind_tunnel_cell::power_rank0_motors(float thrust_level)
{
	
	if( (get_power_in_cell() - _motor[0].get_current_power() + get_power_from_pwm(_motor[0].get_pwm_from_thrust_level(thrust_level))) < _max_power )
	{
		return _motor[0].set_thrust_level(thrust_level);
	}
	else
	{
		return -1;
	}
}


//powers the inner and middle motors
int8_t bte_wind_tunnel_cell::power_rank1_motors(float thrust_level)
{
	
	if((get_power_in_cell() - _motor[0].get_current_power() - _motor[1].get_current_power() - _motor[2].get_current_power() + 3 * get_power_from_pwm(_motor[2].get_pwm_from_thrust_level(thrust_level))) < _max_power )
	{
		_motor[0].set_thrust_level(thrust_level);
		_motor[1].set_thrust_level(thrust_level);
		_motor[2].set_thrust_level(thrust_level);
		return 0;
	}
	else
	{
		return -1;
	}
}


//powers all the motors
int8_t bte_wind_tunnel_cell::power_rank2_motors(float thrust_level)
{
	if( 6 * get_power_from_pwm(_motor[2].get_pwm_from_thrust_level(thrust_level)) < _max_power )
	{
		_motor[0].set_thrust_level(thrust_level);
		_motor[1].set_thrust_level(thrust_level);
		_motor[2].set_thrust_level(thrust_level);
		_motor[3].set_thrust_level(thrust_level);
		_motor[4].set_thrust_level(thrust_level);
		_motor[5].set_thrust_level(thrust_level);
		return 0;
	}
	else
	{
		return -1;
	}
}

int8_t bte_wind_tunnel_cell::set_max_power(float max_power)
{
	_max_power = max_power;
	
	return 0;
}



void bte_wind_tunnel_cell::enable(void)
{
	uint8_t i;

	for(i=0;i<6;i++)
	{
		_motor[i].enable();
	}
}


void bte_wind_tunnel_cell::disable(void)
{
	uint8_t i;
	
	for(i=0;i<6;i++)
	{
		_motor[i].disable();
	}
}


void bte_wind_tunnel_cell::power_off_all_motors(void)
{
	uint8_t i;
	
	for(i=0;i<6;i++)
	{
		_motor[i].power_off();
	}
}
