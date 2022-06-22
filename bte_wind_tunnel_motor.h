#ifndef BTE_WIND_TUNNEL_MOTOR_H_
  #define BTE_WIND_TUNNEL_MOTOR_H_

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>


class bte_wind_tunnel_motor{
  /**
   * \class bte_wind_tunnel_motor
   * \brief class used to instantiate one motor of the wind tunnel designed by Bladetips Energy
   */
   
  public:
  
	  bte_wind_tunnel_motor();
	  /**
       * \fn bte_wind_tunnel_motor()
	   * \brief Default constructor for the bte_wind_tunnel_motor class
       */
       
	  int8_t set_all_params(uint8_t motor_position, Adafruit_PWMServoDriver* pwm_driver,uint16_t min_motor,uint16_t max_motor);
	  /**
       * \fn set_all_params(uint8_t position_motor, Adafruit_PWMServoDriver pwm_driver,uint16_t min_motor,uint16_t max_motor)
	   * \brief Set all the params of the wind tunnel motors
	   * @param (uint8_t)motor_position motor plug position on the driver (0-15)
	   * @param (Adafruit_PWMServoDriver)pwm_driver Pwm driver on which the motor is plug
	   * @param (uint16_t)min_motor min PWM of the motor
	   * @param (uint16_t)max_motor max PWM of the motor
	   * @return -1 if the function fails, 0 otherwise
       */
       
	  int8_t set_range(uint16_t min_motor,uint16_t max_motor);
	  /**
       * \fn set_range(uint16_t min_motor,uint16_t max_motor)
	   * \brief Set all the PWM limits for the motor
	   * @param (uint16_t)min_motor min PWM of the motor
	   * @param (uint16_t)max_motor max PWM of the motors
	   * @return -1 if the function fails, 0 otherwise
       */
       
	  int8_t set_pwm(uint16_t pwm_int);
	  /**
       * \fn set_pwm(uint16_t pwm_int)
	   * \brief Set the pwm 
	   * @param (uint16_t)pwm_int pwm to set on the motor
	   * @return -1 if the function fails (motor off or pwm out of bounds), 0 otherwise
       */
       
	  int8_t set_thrust_level(float thrust_level);
	  /**
       * \fn set_thrust_level(float thrust_level)
	   * \brief Set the wind speed for the motor
	   * @param (float)thrust_level desired wind speed for the motor
	   * @return -1 if the function fails (motor off or pwm corresponding to the wind speed out of bounds), 0 otherwise
       */
       
       void power_off(void);
	  /**
       * \fn void power_off(void)
	   * \brief power off the motor without disabling it
       */
	   
      uint16_t get_current_pwm(void);
      /**
       * \fn get_current_pwm(void)
	   * \brief Get the current PWM of the motor
	   * @return the current PWM
       */
      
      float get_current_power(void);
      /**
       * \fn get_current_power(void)
	   * \brief Get the current power of the motor
	   * @return the current power (W)
       */
	  
	  void enable(void);
	  /**
       * \fn enable(void)
	   * \brief enable the motor (disabled by default)
       */
       
	  void disable(void);
	  /**
       * \fn disable(void)
	   * \brief power off and disable the motor (disabled by default). Use of enable will be required before applying pwm to the motor
       */
       
       uint16_t get_pwm_from_thrust_level(float thrust_level);
  

  private:
	  uint8_t _motor_position;
	  uint8_t _power_flag = 0;
	  Adafruit_PWMServoDriver* _pwm_driver;
	  uint16_t _min_motor;
	  uint16_t _max_motor;
	  uint16_t _pwm_int = 0;
  
  };
  
float get_power_from_pwm(uint16_t pwm_int);
	/**
	* \fn get_power_from_pwm(uint16_t pwm_int)
	* \brief convert the PWM into power (identification done on test bench). Does not apply the PWM.
	* @param (uint16_t)pwm_int pwm of the motor
	* @return the power corresponding to the PWM of the motor
	*/
       

#endif