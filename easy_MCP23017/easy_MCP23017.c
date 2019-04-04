/*************************************************** 
 This is a library for the MCP23017 i2c port expander
 These displays use I2C to communicate, 2 pins are required to
 interface
 Written by @ArduinoEasy.
 ****************************************************/

#include "easy_MCP23017.h"

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

static  uint8_t MCP23017_bitForPin(uint8_t pin);
static  uint8_t MCP23017_regForPin(uint8_t pin, uint8_t portAaddr, uint8_t portBaddr);

static  uint8_t MCP23017_readRegister(uint8_t i2caddr, uint8_t reg);
static  void MCP23017_writeRegister(uint8_t i2caddr, uint8_t reg, uint8_t value);

static void MCP23017_updateRegisterBit(easy_MCP23017 *mcp23017, uint8_t p, uint8_t pValue, uint8_t portAaddr, uint8_t portBaddr);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Bit number associated to a give Pin
 */
static uint8_t MCP23017_bitForPin(uint8_t pin){
	return pin%8;
}

/**
 * Register address, port dependent, for a given PIN
 */
static uint8_t MCP23017_regForPin(uint8_t pin, uint8_t portAaddr, uint8_t portBaddr){
	return(pin<8) ?portAaddr:portBaddr;
}

/**
 * Reads a given register
 */
static  uint8_t MCP23017_readRegister(uint8_t i2caddr, uint8_t reg){
	// MCU specific I2C code Start //
	return I2C_0_read1ByteRegister(i2caddr, reg);
	// MCU specific I2C code END //
}

/**
 * Writes a given register
 */
static void MCP23017_writeRegister(uint8_t i2caddr, uint8_t reg, uint8_t value){
	// MCU specific I2C code Start //
	I2C_0_write1ByteRegister(i2caddr, reg, value);
	// MCU specific I2C code END //
}

/**
 * Helper to update a single bit of an A/B register.
 * - Reads the current register value
 * - Writes the new register value
 */
static void MCP23017_updateRegisterBit(easy_MCP23017 *mcp23017, uint8_t pin, uint8_t pValue, uint8_t portAaddr, uint8_t portBaddr) {
	uint8_t regValue;
	uint8_t regAddr=MCP23017_regForPin(pin,portAaddr,portBaddr);
	uint8_t bit=MCP23017_bitForPin(pin);
	regValue = MCP23017_readRegister(mcp23017->MCP23017_i2caddr, regAddr);

	// set the value for the particular bit
	bitWrite(regValue,bit,pValue);
	MCP23017_writeRegister(mcp23017->MCP23017_i2caddr, regAddr,regValue);
}

////////////////////////////////////////////////////////////////////////////////

void MCP23017_init(easy_MCP23017 *mcp23017){
	MCP23017_writeRegister(mcp23017->MCP23017_i2caddr, MCP23017_IODIRA, 0xff);
	MCP23017_writeRegister(mcp23017->MCP23017_i2caddr, MCP23017_IODIRB, 0xff);
}

void MCP23017_pinMode(easy_MCP23017 *mcp23017, uint8_t pin, uint8_t d){
	MCP23017_updateRegisterBit(mcp23017, pin, (d==INPUT), MCP23017_IODIRA, MCP23017_IODIRB);
}
void MCP23017_digitalWrite(easy_MCP23017 *mcp23017, uint8_t pin, uint8_t d){
	uint8_t gpio;
	uint8_t bit=MCP23017_bitForPin(pin);

	// read the current GPIO output latches
	uint8_t regAddr=MCP23017_regForPin(pin,MCP23017_OLATA,MCP23017_OLATB);
	gpio = MCP23017_readRegister(mcp23017->MCP23017_i2caddr, regAddr);

	// set the pin and direction
	bitWrite(gpio,bit,d);

	// write the new GPIO
	regAddr=MCP23017_regForPin(pin,MCP23017_GPIOA,MCP23017_GPIOB);
	MCP23017_writeRegister(mcp23017->MCP23017_i2caddr, regAddr,gpio);
}
void MCP23017_pullUp(easy_MCP23017 *mcp23017, uint8_t pin, uint8_t d){
	MCP23017_updateRegisterBit(mcp23017, pin, d, MCP23017_GPPUA, MCP23017_GPPUB);
}
uint8_t MCP23017_digitalRead(easy_MCP23017 *mcp23017, uint8_t pin){
	uint8_t bit=MCP23017_bitForPin(pin);
	uint8_t regAddr=MCP23017_regForPin(pin,MCP23017_GPIOA,MCP23017_GPIOB);
	return (MCP23017_readRegister(mcp23017->MCP23017_i2caddr, regAddr) >> bit) & 0x1;
}

void MCP23017_portABMode(easy_MCP23017 *mcp23017, uint8_t mode){
	uint8_t regValue = ((mode==INPUT) ? 0xff : 0x00);
	I2C_0_write2ByteRegister(mcp23017->MCP23017_i2caddr, MCP23017_IODIRA,regValue);
	I2C_0_write2ByteRegister(mcp23017->MCP23017_i2caddr, MCP23017_IODIRB,regValue);
}
void MCP23017_portMode(easy_MCP23017 *mcp23017, uint8_t port, uint8_t mode){
	uint8_t regAddr = (port ? MCP23017_IODIRB : MCP23017_IODIRA);
	uint8_t regValue = ((mode==INPUT) ? 0xff : 0x00);
	MCP23017_writeRegister(mcp23017->MCP23017_i2caddr, regAddr,regValue);
}
void MCP23017_portABWrite(easy_MCP23017 *mcp23017, uint16_t d){
	I2C_0_write2ByteRegister(mcp23017->MCP23017_i2caddr, MCP23017_GPIOA, d);
}
void MCP23017_portWrite(easy_MCP23017 *mcp23017, uint8_t port, uint8_t d){
	uint8_t regAddr = (port ? MCP23017_GPIOB : MCP23017_GPIOA);
	MCP23017_writeRegister(mcp23017->MCP23017_i2caddr, regAddr, d);
}
uint16_t MCP23017_portABRead(easy_MCP23017 *mcp23017){
	// MCU specific I2C code Start //
	return I2C_0_read2ByteRegister(mcp23017->MCP23017_i2caddr, MCP23017_GPIOA);
	// MCU specific I2C code END //
}
uint8_t MCP23017_portRead(easy_MCP23017 *mcp23017, uint8_t b){
	// MCU specific I2C code Start //
	return MCP23017_readRegister(mcp23017->MCP23017_i2caddr, ((b)?MCP23017_GPIOB:MCP23017_GPIOA));
	// MCU specific I2C code END //
}

void MCP23017_setupInterrupts(easy_MCP23017 *mcp23017, uint8_t mirroring, uint8_t openDrain, uint8_t polarity){
	// configure the port A
	uint8_t ioconfValue=MCP23017_readRegister(mcp23017->MCP23017_i2caddr, MCP23017_IOCONA);
	bitWrite(ioconfValue,6,mirroring);
	bitWrite(ioconfValue,2,openDrain);
	bitWrite(ioconfValue,1,polarity);
	MCP23017_writeRegister(mcp23017->MCP23017_i2caddr, MCP23017_IOCONA,ioconfValue);

	// Configure the port B
	ioconfValue=MCP23017_readRegister(mcp23017->MCP23017_i2caddr, MCP23017_IOCONB);
	bitWrite(ioconfValue,6,mirroring);
	bitWrite(ioconfValue,2,openDrain);
	bitWrite(ioconfValue,1,polarity);
	MCP23017_writeRegister(mcp23017->MCP23017_i2caddr, MCP23017_IOCONB,ioconfValue);
}
void MCP23017_setupInterruptPin(easy_MCP23017 *mcp23017, uint8_t pin, uint8_t mode){
	// set the pin interrupt control (0 means change, 1 means compare against given value);
	MCP23017_updateRegisterBit(mcp23017, pin, (mode!=CHANGE), MCP23017_INTCONA, MCP23017_INTCONB);
	// if the mode is not CHANGE, we need to set up a default value, different value triggers interrupt

	// In a RISING interrupt the default value is 0, interrupt is triggered when the pin goes to 1.
	// In a FALLING interrupt the default value is 1, interrupt is triggered when pin goes to 0.
	MCP23017_updateRegisterBit(mcp23017, pin, (mode==FALLING), MCP23017_DEFVALA, MCP23017_DEFVALB);

	// enable the pin for interrupt
	MCP23017_updateRegisterBit(mcp23017, pin, HIGH, MCP23017_GPINTENA, MCP23017_GPINTENB);
}
uint8_t MCP23017_getLastInterruptPin(easy_MCP23017 *mcp23017){
	uint8_t intf;

	// try port A
	intf=MCP23017_readRegister(mcp23017->MCP23017_i2caddr, MCP23017_INTFA);
	for(int i=0;i<8;i++) if (bitRead(intf,i)) return i;

	// try port B
	intf=MCP23017_readRegister(mcp23017->MCP23017_i2caddr, MCP23017_INTFB);
	for(int i=0;i<8;i++) if (bitRead(intf,i)) return i+8;

	return MCP23017_INT_ERR;
}
uint8_t MCP23017_getLastInterruptPinValue(easy_MCP23017 *mcp23017){
	uint8_t intPin=MCP23017_getLastInterruptPin(mcp23017);
	if(intPin!=MCP23017_INT_ERR){
		uint8_t intcapreg=MCP23017_regForPin(intPin,MCP23017_INTCAPA,MCP23017_INTCAPB);
		uint8_t bit=MCP23017_bitForPin(intPin);
		return (MCP23017_readRegister(mcp23017->MCP23017_i2caddr, intcapreg)>>bit) & (0x01);
	}

	return MCP23017_INT_ERR;
}


