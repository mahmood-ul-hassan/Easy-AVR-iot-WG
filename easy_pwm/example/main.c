#include <atmel_start.h>
#include "easy_pwm.h"

#define PD3 3	// blue led (WIFI)
#define PD4 4	// pwm pin on mikroBUS header

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	PORTD_set_pin_dir(PD3, PORT_DIR_OUT);
	PORTD_set_pin_level(PD3, false);
	PORTMUX.TCAROUTEA |= (PORTMUX_TCA00_bm | PORTMUX_TCA01_bm);

	PORTD_set_pin_dir(PD4, PORT_DIR_OUT);
	PORTD_set_pin_level(PD4, false);
	PORTMUX.TCAROUTEA |= (PORTMUX_TCA00_bm | PORTMUX_TCA01_bm);


	/* Replace with your application code */
	easyPWM_init(SYSCLK_DIV_64);
	easyPWM_load_duty_cycle_ch3(0x80);
	easyPWM_load_duty_cycle_ch4(0x80);
	easyPWM_enable_output_ch3();
	easyPWM_enable_output_ch4();
	uint16_t duty_cycle = 0x00;

	while (1) {
		for (int i=0; i<1000; i++)
		for (int j=0; j<100; j++);
		easyPWM_load_duty_cycle_ch3(duty_cycle);
		easyPWM_load_duty_cycle_ch4(duty_cycle);
		duty_cycle += 0x10;
	}
}
