Simply Download and Copy "easy_MCP23017.c" and "easy_MCP23017.h" into Project Folder. Modify the MCU Specific I2C header file in "easy_MCP23017.h" and Code in "easy_MCP23017.c" IF REQUIRED. 

twitter: @ArduinoEasy

/* Button Example */

/* MCU Specific Header Files */
// Include header file into your project
#include "easy_MCP23017.h"

// create new instance
static easy_MCP23017 mcp;	// you can use any other unique name instead of "mcp"


/* MCU main function */

// initialize the MCP23017 module
mcp.MCP23017_i2caddr = MCP23017_ADDRESS;	// Default MCP address when A0=A1=A2=GND
MCP23017_init(&mcp);


MCP23017_pinMode(&mcp, 8, INPUT);	// PORTB-0 as Input
MCP23017_pullUp(&mcp, 8, HIGH); 	// turn on a 100K pullup internally

MCP23017_pinMode(&mcp, 0, OUTPUT);	// PORTA-0 as output

while (1)
{
	if (MCP23017_digitalRead(&mcp, 8)) {		// HIGH input due to PULLUP config
		MCP23017_digitalWrite(&mcp, 0, LOW);	// Output LOW when button is open
		} else {								// LOW input when button is pressed
		MCP23017_digitalWrite(&mcp, 0, HIGH);	// Output HIGH when button is pressed
	}
}

