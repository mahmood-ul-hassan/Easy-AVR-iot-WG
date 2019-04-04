/*************************************************** 
  This is a library for the MCP23017 i2c port expander
  These displays use I2C to communicate, 2 pins are required to  
  interface
  Written by @ArduinoEasy.
 ****************************************************/

#ifndef _easy_MCP23017_H_
#define _easy_MCP23017_H_

#include <stdint.h>

// MCU specific I2C Header Files Start //
#include "i2c_simple_master.h"
// MCU specific I2C Header Files END //

#define HIGH 0x1
#define LOW 0x0

#define MCP_PORTA 0x0
#define MCP_PORTB 0x1

//GPIO FUNCTIONS
#define INPUT             0x00
#define INPUT_PULLUP      0x02	// Not used yet
#define OUTPUT            0x01
#define OUTPUT_OPEN_DRAIN 0x03	// Not used yet

//Interrupt Modes
#define RISING    0x01
#define FALLING   0x02
#define CHANGE    0x03
#define ONLOW     0x04
#define ONHIGH    0x05
#define ONLOW_WE  0x0C
#define ONHIGH_WE 0x0D

typedef struct
{
  uint8_t MCP23017_i2caddr;
}easy_MCP23017;

void MCP23017_init(easy_MCP23017 *mcp23017);

void MCP23017_pinMode(easy_MCP23017 *mcp23017, uint8_t pin, uint8_t d);
void MCP23017_digitalWrite(easy_MCP23017 *mcp23017, uint8_t pin, uint8_t d);
void MCP23017_pullUp(easy_MCP23017 *mcp23017, uint8_t pin, uint8_t d);
uint8_t MCP23017_digitalRead(easy_MCP23017 *mcp23017, uint8_t pin);

void MCP23017_portMode(easy_MCP23017 *mcp23017, uint8_t port, uint8_t mode);
void MCP23017_portWrite(easy_MCP23017 *mcp23017, uint8_t port, uint8_t val);
uint8_t MCP23017_portRead(easy_MCP23017 *mcp23017, uint8_t port);

void MCP23017_portABMode(easy_MCP23017 *mcp23017, uint8_t mode);
void MCP23017_portMode(easy_MCP23017 *mcp23017, uint8_t port, uint8_t mode);
void MCP23017_portABwrite(easy_MCP23017 *mcp23017, uint16_t d);
void MCP23017_portWrite(easy_MCP23017 *mcp23017, uint8_t port, uint8_t d);
uint16_t MCP23017_portABRead(easy_MCP23017 *mcp23017);
uint8_t MCP23017_portRead(easy_MCP23017 *mcp23017, uint8_t b);

void MCP23017_setupInterrupts(easy_MCP23017 *mcp23017, uint8_t mirroring, uint8_t openDrain, uint8_t polarity);
void MCP23017_setupInterruptPin(easy_MCP23017 *mcp23017, uint8_t pin, uint8_t mode);
uint8_t MCP23017_getLastInterruptPin(easy_MCP23017 *mcp23017);
uint8_t MCP23017_getLastInterruptPinValue(easy_MCP23017 *mcp23017);

#define MCP23017_ADDRESS 0x20	//default address of MCP23017 when A0=A1=A2=0

// registers
#define MCP23017_IODIRA 0x00
#define MCP23017_IPOLA 0x02
#define MCP23017_GPINTENA 0x04
#define MCP23017_DEFVALA 0x06
#define MCP23017_INTCONA 0x08
#define MCP23017_IOCONA 0x0A
#define MCP23017_GPPUA 0x0C
#define MCP23017_INTFA 0x0E
#define MCP23017_INTCAPA 0x10
#define MCP23017_GPIOA 0x12
#define MCP23017_OLATA 0x14


#define MCP23017_IODIRB 0x01
#define MCP23017_IPOLB 0x03
#define MCP23017_GPINTENB 0x05
#define MCP23017_DEFVALB 0x07
#define MCP23017_INTCONB 0x09
#define MCP23017_IOCONB 0x0B
#define MCP23017_GPPUB 0x0D
#define MCP23017_INTFB 0x0F
#define MCP23017_INTCAPB 0x11
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATB 0x15

#define MCP23017_INT_ERR 255

#endif