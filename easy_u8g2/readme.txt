Goto: https://github.com/olikraus/u8g2/

clone or download u8g2 repository.

Download and Copy "u8g2_avr.c" and "u8g2_avr.h" into "csrc" Folder.

Copy "csrc" into AVR iot WG project folder

Include header file into your project:
#include "u8g2_avr.h"

create new instance:
static u8g2_t u8g2;	// you can use any other unique name instead of "u8g2"

initialize the Oled module:

u8g2_Setup_ssd1306_i2c_128x64_noname_1(&u8g2, U8G2_R0, u8x8_byte_avr_hw_i2c, u8x8_gpio_and_delay); // "For SSD1306, 128, 64, I2C module"

OR you choose it accodring to your OLED module
for more details: https://github.com/olikraus/u8g2/wiki

To display anything on display always use:
u8g2_FirstPage(&u8g2);
do {
// Add your code here //

} while (u8g2_NextPage(&u8g2));
