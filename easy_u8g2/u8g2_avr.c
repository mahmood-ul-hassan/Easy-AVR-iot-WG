/*
 * 
 * Twitter: @ArduinoEasy
 */

#include "u8g2_avr.h"
#include "clock_config.h"
#include <util/delay.h>

/* Important to avoid Error: "__builtin_avr_delay_cycles expects a compile time integer constant"*/
static void delay_us(double __us){
	if (__us < 10)
	{
		while(0 < __us)
		{
			_delay_us(1);
			__us--;
		}
	}
	else
	{
		while(0 < __us)
		{
			_delay_us(10);
			__us-=10;
		}
	}
}

uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	switch(msg)
  {
    case U8X8_MSG_GPIO_AND_DELAY_INIT:	// called once during init phase of u8g2/u8x8
			delay_us(1000);
      break;							// can be used to setup pins
    case U8X8_MSG_DELAY_NANO:			// delay arg_int * 1 nano second
      break;    
    case U8X8_MSG_DELAY_100NANO:		// delay arg_int * 100 nano seconds
      break;
    case U8X8_MSG_DELAY_10MICRO:		// delay arg_int * 10 micro seconds
			delay_us(10);
			break;
    case U8X8_MSG_DELAY_MILLI:			// delay arg_int * 1 milli second
			delay_us(arg_int * 1000);
      break;
    case U8X8_MSG_DELAY_I2C:				// arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
			delay_us((unsigned long)(5/arg_int));
      break;							// arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
    default:
      break;
  }
  return 1;
}

uint8_t u8x8_byte_avr_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)  
{
  static uint8_t buffer[DATA_BUFFER_SIZE];		/* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
  static uint8_t buf_idx;
  uint8_t *data;

  switch(msg)  
  {  
    case U8X8_MSG_BYTE_SEND:
      data = (uint8_t *)arg_ptr;      
      while( arg_int > 0 )
      {
				buffer[buf_idx++] = *data;
				data++;
				arg_int--;
			}
			break;
			
    case U8X8_MSG_BYTE_INIT:
      break;

    case U8X8_MSG_BYTE_SET_DC:
      break;

    case U8X8_MSG_BYTE_START_TRANSFER:
			buf_idx = 0;
			break;

    case U8X8_MSG_BYTE_END_TRANSFER:
			I2C_0_writeNBytes(DEVICE_ADDRESS, buffer, buf_idx);

      break;

    default:
      return 0;
  }
  return 1;  
}

