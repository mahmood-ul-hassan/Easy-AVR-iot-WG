/*
 * easy_pwm.h
 *
 *  Author: @ArduinoEasy
 */ 


#ifndef EASY_PWM_H_
#define EASY_PWM_H_

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t sysclk_div;
typedef void (*easypwm_irq_cb_t)(void);

#define EASYPWM_INTERRUPT_CB_RATE 0

enum {
	SYSCLK_DIV_1	= TCA_SPLIT_CLKSEL_DIV1_gc,		// SYSCLK / 1
	SYSCLK_DIV_2	= TCA_SPLIT_CLKSEL_DIV2_gc,		// SYSCLK / 2
	SYSCLK_DIV_4	= TCA_SPLIT_CLKSEL_DIV4_gc,		// SYSCLK / 4
	SYSCLK_DIV_8	= TCA_SPLIT_CLKSEL_DIV8_gc,		// SYSCLK / 8
	SYSCLK_DIV_16	= TCA_SPLIT_CLKSEL_DIV16_gc,	// SYSCLK / 16
	SYSCLK_DIV_64	= TCA_SPLIT_CLKSEL_DIV64_gc,	// SYSCLK / 64
	SYSCLK_DIV_256	= TCA_SPLIT_CLKSEL_DIV256_gc,	// SYSCLK / 256
	SYSCLK_DIV_1024	= TCA_SPLIT_CLKSEL_DIV1024_gc,	// SYSCLK / 1024
};

// initialize TCA in split mode with clk clock
void easyPWM_init(sysclk_div clk);

void easyPWM_enable(void);
void easyPWM_disable(void);

void easyPWM_enable_DebugRun(void);
void easyPWM_disable_DebugRun(void);

void easyPWM_enable_output_ch0(void);
void easyPWM_disable_output_ch0(void);

void easyPWM_enable_output_ch1(void);
void easyPWM_disable_output_ch1(void);

void easyPWM_enable_output_ch2(void);
void easyPWM_disable_output_ch2(void);

void easyPWM_enable_output_ch3(void);
void easyPWM_disable_output_ch3(void);

void easyPWM_enable_output_ch4(void);
void easyPWM_disable_output_ch4(void);

void easyPWM_enable_output_ch5(void);
void easyPWM_disable_output_ch5(void);

void easyPWM_L_counter(uint8_t counter_value);
void easyPWM_H_counter(uint8_t counter_value);

void easyPWM_L_top(uint8_t top_value);
void easyPWM_H_top(uint8_t top_value);

void easyPWM_load_duty_cycle_ch0(uint8_t duty_value);
void easyPWM_load_duty_cycle_ch1(uint8_t duty_value);
void easyPWM_load_duty_cycle_ch2(uint8_t duty_value);
void easyPWM_load_duty_cycle_ch3(uint8_t duty_value);
void easyPWM_load_duty_cycle_ch4(uint8_t duty_value);
void easyPWM_load_duty_cycle_ch5(uint8_t duty_value);

void easyPWM_register_callback(easypwm_irq_cb_t f);



#ifdef __cplusplus
}
#endif

#endif /* EASY_PWM_H_ */