/*
 * Twitter: @ArduinoEasy
 */

#ifndef _U8G_AVR_H
#define _U8G_AVR_H

#include "u8g2.h"
#include "i2c_simple_master.h"

#define DATA_BUFFER_SIZE 32  
//#define OLED_I2C_TIMEOUT 10000
#define DEVICE_ADDRESS 0x3C //device address is written on back side of your display  
 
uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_byte_avr_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

#endif

