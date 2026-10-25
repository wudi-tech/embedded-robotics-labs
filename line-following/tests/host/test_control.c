#include "headfile.h"
#include "type.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int P34=1, P35=1, P36=1, P37=1;
static uint16_t duties[256], inputs[4];
static unsigned calls, adc_calls, adc_mode, per_channel[4], checks;
#define CHECK(expr) do { ++checks; if (!(expr)) { \
 fprintf(stderr,"FAIL line %d: %s\n",__LINE__,#expr); exit(1); } } while (0)
#define CLOSE(a,b) CHECK(fabs((double)(a)-(double)(b)) < 0.001)
void DisableGlobalIRQ(void) {}
void board_init(void) {}
void delay_ms(unsigned int ms) {(void)ms;}
void pwm_init(int c,uint32_t f,uint16_t d) {(void)c;(void)f;(void)d;}
void pwm_duty(int c,uint16_t d) {CHECK(c>=0 && c<256);duties[c]=d;++calls;}
void adc_init(int c,int s) {(void)c;(void)s;}
uint16_t adc_once(int c,int r) {
    unsigned index;
    CHECK(c>=8 && c<=11); CHECK(r==ADC_12BIT); index=(unsigned)(c-8);
    if (++adc_calls>256) { puts("EXPECTED: original sampling loop did not terminate after 256 reads"); exit(42); }
    if(adc_mode==2) return 1100;
    if(adc_mode==1) return (++per_channel[index]%2) ? 400 : 1200;
    return inputs[index];
}
void oled_init(void) {}
void oled_cls(void) {}
void oled_p6x8str(int x,int y,const char*s) {(void)x;(void)y;(void)s;}
void oled_p6x8num(int x,int y,int n) {(void)x;(void)y;(void)n;}
void oled_printf_int32(int x,int y,int n,int d) {(void)x;(void)y;(void)n;(void)d;}
void oled_printf_float(int x,int y,double n,int d,int p) {(void)x;(void)y;(void)n;(void)d;(void)p;}
static void wheels(unsigned a,unsigned b,unsigned c,unsigned d) {
 CHECK(duties[fl]==a);CHECK(duties[fr]==b);CHECK(duties[bl]==c);CHECK(duties[br]==d);
}
int main(int argc,char**argv) {
 struct Adc adc={0}; struct Can can={1,2,2,0.5f}; struct Che che={0}; unsigned i;
 for(i=0;i<4;++i) {adc.min[i]=0;adc.max[i]=1000;inputs[i]=333;}
 if(argc>1 && strcmp(argv[1],"--over-max")==0) {adc_mode=2;getadcave(&adc);return 1;}
 /* These call the archived functions directly. Tests describe historical behavior. */
 goforward(2); wheels(7000,7000,7000,7000);
 rightline(2); wheels(7000,3000,3000,7000);
 rightline(-2); wheels(3000,7000,7000,3000);
 turnmiddle(2); wheels(7000,3000,7000,3000);
 turnbehind(-2); wheels(3000,7000,7000,3000); /* rear wheels retain prior values */
 goforward(0); rightslash(2); wheels(7000,5000,5000,7000);
 goforward(0); rightbehind(2); wheels(7000,5000,7000,5000);
 goforward(6); wheels(11000,11000,11000,11000); /* historical input has no clamp */
 adc.adcave[0]=10;adc.adcave[1]=4;adc.adcave[2]=1;adc.adcave[3]=2;
 adc.errornow=3;vccla(&adc,&can,&che);CLOSE(adc.errorpre,3);CLOSE(adc.errornow,14);CLOSE(che.vc,33.5);
 vccla(&adc,&can,&che);CLOSE(adc.errorpre,14);CLOSE(che.vc,28);
 che.vc=100;go(&che);wheels(9500,10000,9500,10000);
 che.vc=-100;go(&che);wheels(10000,9500,10000,9500);
 i=calls;che.vc=0;go(&che);CHECK(calls==i);wheels(10000,9500,10000,9500);
 che.vc=2000;go(&che);wheels(0,10000,0,10000);
 getadcave(&adc);CHECK(adc_calls==40);for(i=0;i<4;++i) CLOSE(adc.adcave[i],33);
 adc_mode=1;adc_calls=0;getadcave(&adc);CHECK(adc_calls==40);
 for(i=0;i<4;++i) CLOSE(adc.adcave[i],120); /* guard and used sample differ */
 adc.errornow=17;adcinit(&adc);CLOSE(adc.errornow,17);
 for(i=0;i<4;++i) {CLOSE(adc.max[i],0);CLOSE(adc.min[i],4096);}
 P36=0;choosekp(&can);choosekd(&can);choosea1(&can);choosea2(&can);
 CLOSE(can.kp,20);CLOSE(can.kd,2);CLOSE(can.a1,10);CLOSE(can.a2,5);
 P36=1;CHECK(key_scan()==0);P34=0;P35=0;CHECK(key_scan()==KEY0_PRESS);
 printf("PASS: %u assertions; original motor, PD, sampling, calibration and key functions\n",checks);
 return 0;
}
