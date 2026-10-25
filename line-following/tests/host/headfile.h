#ifndef ARCHIVE_HOST_HEADFILE_H
#define ARCHIVE_HOST_HEADFILE_H
/* Archive-only API stubs. No register access, SDK code, timers or hardware IO. */
#include <stdint.h>
extern int P34, P35, P36, P37;
enum { ADC_P00=8, ADC_P01=9, ADC_P02=10, ADC_P03=11 };
enum { ADC_SYSclk_DIV_2=0, ADC_12BIT=0 };
enum { PWM1P_P20=0x02, PWM1N_P21=0x03,
       PWM2P_P22=0x12, PWM2N_P23=0x13,
       PWM3P_P24=0x22, PWM3N_P25=0x23,
       PWM4P_P26=0x32, PWM4N_P27=0x33 };
void DisableGlobalIRQ(void);
void board_init(void);
void delay_ms(unsigned int ms);
void pwm_init(int channel, uint32_t frequency, uint16_t duty);
void pwm_duty(int channel, uint16_t duty);
void adc_init(int channel, int speed);
uint16_t adc_once(int channel, int resolution);
void oled_init(void);
void oled_cls(void);
void oled_p6x8str(int x, int y, const char *s);
void oled_p6x8num(int x, int y, int n);
void oled_printf_int32(int x, int y, int n, int digits);
void oled_printf_float(int x, int y, double n, int digits, int decimals);
#endif
