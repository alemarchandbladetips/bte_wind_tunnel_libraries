#include "bte_wind_tunnel_cell.h"


bte_wind_tunnel_cell::bte_wind_tunnel_cell(){
}

int8_t bte_wind_tunnel_cell::set_all_params(uint8_t offset, Adafruit_PWMServoDriver* pwm_driver,uint16_t min_motor,uint16_t max_motor, float max_power){
	uint8_t i;
	
	_max_power = max_power; // equiv to this->_max_power = max_power;
	
	for(i=0;i<6;i++)
	{
		_motor[i].set_all_params(i+offset, _pwm_driver, _min_motor, _max_motor);
		return 0;
	}
	
}

int8_t bte_wind_tunnel_cell::power_individual_motor(uint8_t motor_position,uint16_t pwm_int){
		
	if( (get_power_in_cell() - _motor[motor_position].get_current_power() + get_power_from_pwm(pwm_int)) < _max_power ){
		return _motor[motor_position].set_pwm(pwm_int);
	}
	else{
		return -1;
	}
	
}



int8_t bte_wind_tunnel_cell::get_power_in_cell(){
	float total_power = 0;
	uint8_t i;
	for(i=0;i<6;i++){
		total_power += _motor[i].get_current_power();
	}
	return total_power;
}


//powers the inner motor
int8_t bte_wind_tunnel_cell::power_rank0_motors(uint16_t pwm_int){
	
	if( (get_power_in_cell() - _motor[0].get_current_power() + get_power_from_pwm(pwm_int)) < _max_power ){
		return _motor[0].set_pwm(pwm_int);
	}
	else{
		return -1;
	}
};


//powers the inner and middle motors
int8_t bte_wind_tunnel_cell::power_rank1_motors(uint16_t pwm_int){
	float motor0_power = _motor[0].get_current_pwm();
	float motor1_power = _motor[1].get_current_pwm();
	float motor2_power = _motor[2].get_current_pwm();
	
	if( (get_power_in_cell() - _motor[0].get_current_power() - _motor[1].get_current_power() - _motor[2].get_current_power() + 3 * get_power_from_pwm(pwm_int)) < _max_power ){
		_motor[0].set_pwm(pwm_int);
		_motor[1].set_pwm(pwm_int);
		_motor[2].set_pwm(pwm_int);
		return 0;
	}
	else{
		return -1;
	}
};


//powers all the motors
int8_t bte_wind_tunnel_cell::power_rank2_motors(uint16_t pwm_int){
	
	if( 6 * get_power_from_pwm(pwm_int) < _max_power ){
		_motor[0].set_pwm(pwm_int);
		_motor[1].set_pwm(pwm_int);
		_motor[2].set_pwm(pwm_int);
		_motor[3].set_pwm(pwm_int);
		_motor[4].set_pwm(pwm_int);
		_motor[5].set_pwm(pwm_int);
		return 0;
	}
	else{
		return -1;
	}
};


int8_t bte_wind_tunnel_cell::power_individually(uint16_t pwm_int1, uint16_t pwm_int2, uint16_t pwm_int3, uint16_t pwm_int4, uint16_t pwm_int5, uint16_t pwm_int6){
	
	if (get_power_from_pwm(pwm_int1) + get_power_from_pwm(pwm_int2) + get_power_from_pwm(pwm_int3) + get_power_from_pwm(pwm_int4) + get_power_from_pwm(pwm_int5) + get_power_from_pwm(pwm_int6) < _max_power){
		_motor[0].set_pwm(pwm_int1);
		_motor[1].set_pwm(pwm_int2);
		_motor[2].set_pwm(pwm_int3);
		_motor[3].set_pwm(pwm_int4);
		_motor[4].set_pwm(pwm_int5);
		_motor[5].set_pwm(pwm_int6);
		return 0;
	}
	else{
		return -1;
	}
}

int8_t bte_wind_tunnel_cell::set_max_power(float max_power){
	_max_power = max_power;
}



void bte_wind_tunnel_cell::enable(){
	uint8_t i;
	
	for(i=0;i<6;i++)
	{
		_motor[i].enable();
	}
}


void bte_wind_tunnel_cell::disable(){
	uint8_t i;
	
	for(i=0;i<6;i++)
	{
		_motor[i].disable();
	}
}


int8_t power_off_all_motors(){
	
}
