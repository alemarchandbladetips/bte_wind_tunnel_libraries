
#include "bte_wind_tunnel.h"

#define DEFAULT_MAX_CELL_POWER 2750.0
#define POWER_SUPPLIER_MAX_POWER 3000.0

#define MAX_PWM 2000
#define MIN_PWM 1000

 
bte_wind_tunnel::bte_wind_tunnel()
{
	_cell[0].set_all_params(0,&_pwm_driver0,MIN_PWM,MAX_PWM,DEFAULT_MAX_CELL_POWER);
	_cell[1].set_all_params(8,&_pwm_driver0,MIN_PWM,MAX_PWM,DEFAULT_MAX_CELL_POWER);
	_cell[2].set_all_params(0,&_pwm_driver1,MIN_PWM,MAX_PWM,DEFAULT_MAX_CELL_POWER);
	_cell[3].set_all_params(8,&_pwm_driver1,MIN_PWM,MAX_PWM,DEFAULT_MAX_CELL_POWER);
	_cell[4].set_all_params(0,&_pwm_driver2,MIN_PWM,MAX_PWM,DEFAULT_MAX_CELL_POWER);
	_cell[5].set_all_params(8,&_pwm_driver2,MIN_PWM,MAX_PWM,DEFAULT_MAX_CELL_POWER);
	_central_motor.set_all_params(15,&_pwm_driver0,MIN_PWM,MAX_PWM);
	_enable_flag = 0;
}
	  
	 
int8_t bte_wind_tunnel::set_max_cell_power(float max_cell_power)
{
	uint8_t i;
	
	if(max_cell_power>POWER_SUPPLIER_MAX_POWER)
	{
		return -1;
	}
	
	for(i=0;i<6;i++)
	{
		_cell[i].set_max_power(max_cell_power);
	}
	
	return 0;
}
	  
	  
int8_t bte_wind_tunnel::power_individual_motor(uint8_t cell_number, uint8_t motor_number, float thrust_level)
{
	return _cell[cell_number].power_individual_motor(motor_number,thrust_level);
}
	  
int8_t bte_wind_tunnel::power_rank0_motors(float thrust_level)
{
	int8_t retval = 0;
	uint8_t i;
	
	for(i=0;i<6;i++)
	{
		retval += _cell[i].power_rank0_motors(thrust_level);
		if (retval != 0){
			return retval;
		}
	}
	retval += _central_motor.set_thrust_level(thrust_level);
	
	return retval;
}
	  
int8_t bte_wind_tunnel::power_rank1_motors(float thrust_level)
{
	int8_t retval = 0;
	uint8_t i;
	
	for(i=0;i<6;i++)
	{
		retval += _cell[i].power_rank1_motors(thrust_level);
		if (retval != 0){
			return retval;
		}
	}
	retval += _central_motor.set_thrust_level(thrust_level);
	
	return retval;
}

int8_t bte_wind_tunnel::power_rank2_motors(float thrust_level)
{
	int8_t retval = 0;
	uint8_t i;
	
	for(i=0;i<6;i++)
	{
		retval += _cell[i].power_rank2_motors(thrust_level);
		if (retval != 0){
			return retval;
		}
	}
	retval += _central_motor.set_thrust_level(thrust_level);
	
	return retval;
}
	  
void bte_wind_tunnel::power_off_all_motors()
{
	uint8_t i;

	for(i=0;i<6;i++)
	{
		_cell[i].power_off_all_motors();
	}
	_central_motor.power_off();
}
	  
void bte_wind_tunnel::enable()
{
	uint8_t i;
	
	for(i=0;i<6;i++)
	{
		_cell[i].enable();
	}
	_central_motor.enable();
}
	  
void bte_wind_tunnel::disable()
{
	uint8_t i;
	
	for(i=0;i<6;i++)
	{
		_cell[i].disable();
	}
	_central_motor.disable();
}
	  
float bte_wind_tunnel::get_current_cell_power(uint8_t cell_number)
{
	return _cell[cell_number].get_current_power();
}
	  
float bte_wind_tunnel::get_current_total_power()
{
	float total_power = 0;
	uint8_t i;
	
	for(i=0;i<6;i++)
	{
		total_power += _cell[i].get_current_power();
	}
	total_power += _central_motor.get_current_power();
	
	return total_power;
}