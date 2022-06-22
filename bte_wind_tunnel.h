#ifndef BTE_WIND_TUNNEL_H_
  #define BTE_WIND_TUNNEL_H_
  
#include <Arduino.h>
#include "bte_wind_tunnel_cell.h"

#define THRUST_IDDLE 0.0
//0.46

class bte_wind_tunnel{
  /**
   * \class bte_wind_tunnel
   * \brief class used to instantiate the 37 motors wind tunnel designed by Bladetips Energy
   */
  
  public:
  
	  /**
       * \fn bte_wind_tunnel()
	   * \brief Constructor for the bte_wind_tunnel class
       */
	  bte_wind_tunnel();
	  
	  
	   /**
       * \fn int8_t set_max_cell_power(float max_cell_power)
	   * \brief Set the maximum power for all individual cells of the wind tunnel
       * @param (float)max_cell_power maximum power for all cells individually (W)
       * @return -1 if the function fails, 0 otherwise
       */
	  int8_t set_max_cell_power(float max_cell_power);
	  
	  
	  /**
	   * \fn int8_t power_individual_motor(uint8_t cell_number, uint8_t motor_number, float thrust_level)
       * \brief Set the thrust level for a particular motor
       * @param (uint8_t)cell_number 0 for the center motor 1 for the upper left cell, counting goes clockwise
	   * @param (uint8_t)motor_number (0 to 5) 0 for the motor closer to the center, 1 and 2 for the second line, 3, 4 and 5 for the 3rd line (counting clockwise)
	   * @param (float)thrust_level desired thrust level [0-1], 0 motor off, 1 motor at full speed.
       * @return -1 if the power exceed total or cell power, -2 if motor or cell doesn't exist, 0 otherwise
       */
	  int8_t power_individual_motor(uint8_t cell_number, uint8_t motor_number, float thrust_level);
	  
	  /**
	   * \fn  int8_t power_rank0_motors(float thrust_level)
       * \brief Set the thrust level for the motors (7 motors) of the inner circle of the wind tunnel
	   * @param (float)thrust_level desired thrust level [0-1], 0 motor off, 1 motor at full speed.
       * @return -1 if the power exceed total or cell power, 0 otherwise
       */
	  int8_t power_rank0_motors(float thrust_level);
	  
	  /**
	   * \fn int8_t power_rank1_motors(float thrust_level)
       * \brief Set the thrust level for the motors (13 motors) of the inner and second circle of the wind tunnel
	   * @param (float)thrust_level desired thrust level [0-1], 0 motor off, 1 motor at full speed.
       * @return -1 if the power exceed total or cell power, 0 otherwise
       */
	  int8_t power_rank1_motors(float thrust_level);
	  
	  /**
	   * \fn int8_t power_rank2_motors(float thrust_level)
       * \brief Set the thrust level for the motors (37 motors) of the inner and second and third circle of the wind tunnel
	   * @param (float)thrust_level desired thrust level [0-1], 0 motor off, 1 motor at full speed.
       * @return -1 if the power exceed total or cell power, 0 otherwise
       */
	  int8_t power_rank2_motors(float thrust_level);
	  
	  /**
	   * \fn void power_off_all_motors()
       * \brief power off all motors, do not disable the motors.
       */
	  void power_off_all_motors(void);
	  
	  /**
	   * \fn void enable()
       * \brief enable all motors. Must be called before using the wind tunnel (disable by default)
       */
	  void enable(void);
	  
	  /**
	   * \fn void disable()
       * \brief disable all motors. Enable must be called if you want to use motor after.
       */
	  void disable(void);
	  
	  /**
	   * \fn float get_current_cell_power(uint8_t cell_number)
       * \brief Get the current power of a particular cell
	   * @param (uint8_t)cell_number number of the cell we want the power returned
       * @return (float)power the current power of the cell (W)
       */
	  float get_current_cell_power(uint8_t cell_number);
	  
	  /**
	   * \fn float get_current_total_power()
       * \brief Set the thrust level for the motors (37 motors) of the inner and second and third circle of the wind tunnel
       * @return (float)power the current power of all the cells (W)
       */
	  float get_current_total_power(void);
  

  private:
	  Adafruit_PWMServoDriver _pwm_driver0 = Adafruit_PWMServoDriver(0x40);
	  Adafruit_PWMServoDriver _pwm_driver1 = Adafruit_PWMServoDriver(0x41);
	  Adafruit_PWMServoDriver _pwm_driver2 = Adafruit_PWMServoDriver(0x42);
	  bte_wind_tunnel_cell _cell[6];
	  bte_wind_tunnel_motor _central_motor;
	  uint8_t _enable_flag = 0;
  
  };

#endif