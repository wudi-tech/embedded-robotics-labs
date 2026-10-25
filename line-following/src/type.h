#ifndef __TYPE_H_
#define __TYPE_H_

#define KEY0 P34
#define KEY1 P35
#define KEY2 P36
#define KEY3 P37
#define KEY0_PRESS 1
#define KEY1_PRESS 2
#define KEY2_PRESS 3
#define KEY3_PRESS 4
#define LED0 P70
#define LED1 P71
#define LED2 P72
#define LED3 P73
#define fl 0x02
#define fr 0x12
#define bl 0x22
#define br 0x32


struct Adc{
	float max[4];
	float min[4];
	float adcave[4];
	float errorpre;
	float errornow;
	float test;
};
struct Can{
	float a1;
  float a2;
	float kp;
	float kd;
};
struct Che{
	float vc;
};
void ready();
int key_scan();
void pwm_init_total();
void adc_init_total();
int MENU1();
int MENU2();

void adcinit(struct Adc*adc);
void getadcave(struct Adc*adc);
void vccla(struct Adc*adc,struct Can*can,struct Che*che);
void go(struct Che*che);
void choosekp(struct Can*can);
void choosekd(struct Can*can);
void choosea1(struct Can*can);
void choosea2(struct Can*can);
void getmax1(struct Adc*adc);
void getmax2();
void goforward(int v);
void rightslash(int v);
void rightline(int v);
void turnmiddle(int v);
void turnbehind(int v);
void rightbehind(int v);
void test();
int type1();
int type2();
int type3();
int type4();
int type5();

void turn(float r);

#endif