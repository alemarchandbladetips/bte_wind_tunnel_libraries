#ifndef BTE_ARDUINO_TEST_FRAMEWORK_H_
  #define BTE_ARDUINO_TEST_FRAMEWORK_H_
  
  #include <Arduino.h>

void bte_run_test_int8_t(int8_t expected, int8_t result);

void bte_run_test_uint8_t(uint8_t expected, uint8_t result);

void bte_run_test_int16_t(int16_t expected, int16_t result);

void bte_run_test_uint16_t(uint16_t expected, uint16_t result);

void bte_run_test_int32_t(int32_t expected, int32_t result);

void bte_run_test_uint32_t(uint32_t expected, uint32_t result);

void bte_run_test_float(float expected, float tolerance, float result);

#endif