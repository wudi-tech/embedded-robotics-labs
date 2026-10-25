#include "headfile.h"
#include "type.h"


int key_scan(){

    
		if(KEY0==0)
		{
			delay_ms(60);
			return 1;
		}
		if(KEY1==0)
		{
			delay_ms(60);
			return KEY1_PRESS;
		}
    if(KEY2==0)
		{
			delay_ms(60);
			return KEY2_PRESS;
		}
     if(KEY3==0)
		{
			delay_ms(60);
			return KEY3_PRESS;
		}
		return 0;
} 	   


void pwm_init_total(){
    pwm_init(PWM1P_P20, 500, 6000);//电机1 fl
    pwm_init(PWM2P_P22, 500, 6000);//电机2 fr
  	pwm_init(PWM3P_P24, 500, 6000);//电机3 bl
    pwm_init(PWM4P_P26, 500, 6000);//电机4 br
    
    pwm_init(PWM1N_P21, 500, 3000);
    pwm_init(PWM2N_P23, 500, 3000);   
    pwm_init(PWM3N_P25, 500, 3000);
    pwm_init(PWM4N_P27, 500, 3000);
	
	  pwm_duty(PWM1P_P20,5000);
    pwm_duty(PWM2P_P22,5000);
    pwm_duty(PWM3P_P24,5000);
    pwm_duty(PWM4P_P26,5000);
}

void adc_init_total(){
  adc_init(ADC_P00, ADC_SYSclk_DIV_2);
	adc_init(ADC_P01, ADC_SYSclk_DIV_2);
  adc_init(ADC_P02, ADC_SYSclk_DIV_2);
	adc_init(ADC_P03, ADC_SYSclk_DIV_2);
}
//dian ji xing wei
void goforward(int v){
    pwm_duty(fl,5000+v*1000);
    pwm_duty(fr,5000+v*1000);
    pwm_duty(bl,5000+v*1000);
    pwm_duty(br,5000+v*1000);
}
void rightslash(int v){
    pwm_duty(fl,5000+v*1000);
    pwm_duty(br,5000+v*1000);
}
void rightline(int v){
    pwm_duty(fl,5000+v*1000);
    pwm_duty(fr,5000-v*1000);
    pwm_duty(bl,5000-v*1000);
    pwm_duty(br,5000+v*1000);
}
void turnmiddle(int v){
    pwm_duty(fl,5000+v*1000);
    pwm_duty(fr,5000-v*1000);
    pwm_duty(bl,5000+v*1000);
    pwm_duty(br,5000-v*1000);
}
void turnbehind(int v){
    pwm_duty(fl,5000+v*1000);
    pwm_duty(fr,5000-v*1000);
}
void rightbehind(int v){
    pwm_duty(fl,5000+v*1000);
    pwm_duty(bl,5000+v*1000);
}
//cai dan
int MENU1(){
	int a = 1;
	oled_cls();
	oled_p6x8str(40,0,"MENU");//xian heng hou shu
	oled_p6x8str(10,1,"1.type1:test");
  oled_p6x8str(10,2,"2.type2:turn");
	oled_p6x8str(0,a,"*");
	while(1){
		
    if((key_scan() == KEY0_PRESS) && a > 1)
		{  
			oled_p6x8str(0,a," ");
			a--;
			oled_p6x8str(0,a,"*");
		}
    if((key_scan() == KEY3_PRESS) && a < 2)
		{
		  oled_p6x8str(0,a," ");
			a++;
			oled_p6x8str(0,a,"*");
		}  
    if(key_scan() == KEY2_PRESS)
			return a;
	}
}
int MENU2(){
	int a = 1;
	oled_cls();
	oled_p6x8str(40,0,"MENU");//xian heng hou shu
	oled_p6x8str(10,1,"1.type1:test");
  oled_p6x8str(10,2,"2.type2:turn");
	oled_p6x8str(0,a,"*");
	while(1){
		
    if((key_scan() == KEY0_PRESS) && a > 1)
		{  
			oled_p6x8str(0,a," ");
			a--;
			oled_p6x8str(0,a,"*");
		}
    if((key_scan() == KEY3_PRESS) && a < 2)
		{
		  oled_p6x8str(0,a," ");
			a++;
			oled_p6x8str(0,a,"*");
		}  
    if(key_scan() == KEY2_PRESS)
			return a;
	}
}
void getadcave(struct Adc*adc){
	long adcsum = 0;
	int j;
		for(j = 0;j<5;j++)
		{
      if(adc_once(8, ADC_12BIT) > adc->max[0])	
			{ j--; continue; }				
		   adcsum += (adc_once(8, ADC_12BIT) - adc->min[0])/(adc->max[0] - adc->min[0])*100;						
		}
		adc->adcave[0] = adcsum/5;
		adcsum = 0;
		for(j = 0;j<5;j++)
		{
      if(adc_once(9, ADC_12BIT) > adc->max[1])	
			{ j--; continue; }				
		   adcsum += (adc_once(9, ADC_12BIT) - adc->min[1])/(adc->max[1] - adc->min[1])*100;						
		}
		adc->adcave[1] = adcsum/5;
		adcsum = 0;
		for(j = 0;j<5;j++)
		{
      if(adc_once(10, ADC_12BIT) > adc->max[2])	
			{ j--; continue; }				
		   adcsum += (adc_once(10, ADC_12BIT) - adc->min[2])/(adc->max[2] - adc->min[2])*100;						
		}
		adc->adcave[2] = adcsum/5;
		adcsum = 0;
		for(j = 0;j<5;j++)
		{
      if(adc_once(11, ADC_12BIT) > adc->max[3])	
			{ j--; continue; }				
		   adcsum += (adc_once(11, ADC_12BIT) - adc->min[3])/(adc->max[3] - adc->min[3])*100;						
		}
		adc->adcave[3] = adcsum/5;
}
void vccla(struct Adc*adc,struct Can*can,struct Che*che){	//adc ji suan chu error
	adc->errorpre = adc->errornow;
	adc->errornow= can->a1* (adc->adcave[0] - adc->adcave[3]) + can->a2*(adc->adcave[1] - adc->adcave[2]);
	che->vc = can->kp*adc->errornow + can->kd*(adc->errornow - adc->errorpre);
	
}
void go(struct Che*che){
	if(che->vc > 0)
	{ 
		pwm_duty(fl,10000-che->vc*5);
    pwm_duty(fr,10000);
    pwm_duty(bl,10000-che->vc*5);
    pwm_duty(br,10000);
	}
	if(che->vc < 0)
	{
    pwm_duty(fl,10000);
    pwm_duty(fr,10000+che->vc*5);
    pwm_duty(bl,10000);
    pwm_duty(br,10000+che->vc*5);
	}
}
void ready(){
	oled_p6x8str(0,0,"press key2 ready");
  while(1){
	  if(key_scan() == KEY2_PRESS)
			break;
	}
}

void adcinit(struct Adc*adc){
	int i;
	for(i=0;i<4;i++)
  {
		adc->max[i] = 0;
		adc->min[i] = 4096;
  }

}
int type1(){
	  int v = 0;
	  oled_cls();
	  oled_p6x8str(10,0,"type1: goforward");
	  oled_p6x8str(10,1,"press key1 quit");
	  oled_p6x8str(10,3,"v :");
	  while(1){
			if((key_scan() == KEY0_PRESS) && v < 5)
			   v+=1;
			if((key_scan() == KEY3_PRESS) && v > -5)
			   v-=1;
      if(key_scan() == KEY1_PRESS)
			  return 0;
			oled_printf_int32(30,3,v,1);
      goforward(v);				
		}
}
int type2(){
	  int v = 0;
	  oled_cls();
	  oled_p6x8str(10,0,"type2: rightslash");
	  oled_p6x8str(10,1,"press key1 quit");
	  oled_p6x8str(10,3,"v :");
	  while(1){
			rightline(v);
			if((key_scan() == KEY0_PRESS) && v < 5)
			   v+=1;
			if((key_scan() == KEY3_PRESS) && v > -5)
			   v-=1;
      if(key_scan() == KEY1_PRESS)
			  return 0;
			oled_printf_int32(30,3,v,1);
      rightslash(v);			
		}
}
int type3(){
	  int v = 0;
	  oled_cls();
	  oled_p6x8str(10,0,"type3: rightline");
	  oled_p6x8str(10,1,"press key1 quit");
	  oled_p6x8str(10,3,"v :");
	  while(1){
			rightline(v);
			if((key_scan() == KEY0_PRESS) && v < 5)
			   v+=1;
			if((key_scan() == KEY3_PRESS) && v > -5)
			   v-=1;
      if(key_scan() == KEY1_PRESS)
			  return 0;
			oled_printf_int32(30,3,v,1);
      rightline(v);			
		}
}
int type4(){
	  int v = 0;
	  oled_cls();
	  oled_p6x8str(10,0,"type4: turnmiddle");
	  oled_p6x8str(10,1,"press key1 quit");
	  oled_p6x8str(10,3,"v :");
	  while(1){
			rightline(v);
			if((key_scan() == KEY0_PRESS) && v < 5)
			   v+=1;
			if((key_scan() == KEY3_PRESS) && v > -5)
			   v-=1;
      if(key_scan() == KEY1_PRESS)
			  return 0;
			oled_printf_int32(30,3,v,1);
      turnmiddle(v);			
		}
}
int type5(){
	  int v = 0;
	  oled_cls();
	  oled_p6x8str(10,0,"type5: turnbehind");
	  oled_p6x8str(10,1,"press key1 quit");
	  oled_p6x8str(10,3,"v :");
	  while(1){
			rightline(v);
			if((key_scan() == KEY0_PRESS) && v < 5)
			   v+=1;
			if((key_scan() == KEY3_PRESS) && v > -5)
			   v-=1;
      if(key_scan() == KEY1_PRESS)
			  return 0;
			oled_printf_int32(30,3,v,1);
      turnbehind(v);			
		}
}
void choosekp(struct Can*can){
	  can->kp = 20;
	  oled_cls();
    oled_p6x8str(0,0,"press key2 confirm");
	  oled_p6x8str(5,3,"kp :");
    while(1){
			if(key_scan() == KEY0_PRESS)
			   can->kp+=1;
			if(key_scan() == KEY3_PRESS)
			   can->kp-=1;
      if(key_scan() == KEY2_PRESS)
			  break;
			oled_printf_float(30,3,can->kp,3,1);
		}
}
void choosekd(struct Can*can){
	  can->kd = 2;
	  oled_cls();
    oled_p6x8str(0,0,"press key2 confirm");
	  oled_p6x8str(5,3,"kd :");
    while(1){
			if(key_scan() == KEY0_PRESS)
			   can->kd+=1;
			if(key_scan() == KEY3_PRESS)
			   can->kd-=1;
      if(key_scan() == KEY2_PRESS)
			  break;
			oled_printf_float(30,3,can->kd,3,1);
		}
}
void choosea1(struct Can*can){
	  can->a1 = 10;
	  oled_cls();
    oled_p6x8str(0,0,"press key2 confirm");
	  oled_p6x8str(5,3,"a1 :");
    while(1){
			if(key_scan() == KEY0_PRESS)
			   can->a1+=1;
			if(key_scan() == KEY3_PRESS)
			   can->a1-=1;
      if(key_scan() == KEY2_PRESS)
			  break;
			oled_printf_float(30,3,can->a1,2,1);
		}
}
void choosea2(struct Can*can){
	  can->a2 = 5;
	  oled_cls();
    oled_p6x8str(0,0,"press key2 confirm");
	  oled_p6x8str(5,3,"a2 :");
    while(1){
			if(key_scan() == KEY0_PRESS)
			   can->a2+=1;
			if(key_scan() == KEY3_PRESS)
			   can->a2-=1;
      if(key_scan() == KEY2_PRESS)
			  break;
			oled_printf_float(30,3,can->a2,2,1);
		}
}

void getmax1(struct Adc*adc){
	float i;
	int adc1,adc2,adc3,adc4;
	adcinit(adc);
	oled_p6x8str(0,0,"get max and min");
	while(1){
		adc1 = adc_once(8, ADC_12BIT);
		adc2 = adc_once(9, ADC_12BIT);
		adc3 = adc_once(10, ADC_12BIT);
		adc4 = adc_once(11, ADC_12BIT);
		if(adc1 > adc->max[0])		
		   adc->max[0] = adc1;	
		if(adc1 < adc->min[0])		
		   adc->min[0] = adc1;	
	  if(adc2 > adc->max[1])		
		   adc->max[1] = adc2;	
		if(adc2 < adc->min[1])		
		   adc->min[1] = adc2;	
		if(adc3 > adc->max[2])		
		   adc->max[2] = adc3;	
		if(adc3 < adc->min[2])		
		   adc->min[2] = adc3;	
		if(adc4 > adc->max[3])		
		   adc->max[3] = adc4;	
		if(adc4 < adc->min[3])		
		   adc->min[3] = adc4;	
		oled_p6x8num(0,1,adc->max[0]);
		oled_p6x8num(70,1,adc->min[0]);
		oled_p6x8num(0,2,adc->max[1]);
		oled_p6x8num(70,2,adc->min[1]);
		oled_p6x8num(0,3,adc->max[2]);
		oled_p6x8num(70,3,adc->min[2]);
		oled_p6x8num(0,4,adc->max[3]);
		oled_p6x8num(70,4,adc->min[3]);
		if(key_scan()  == KEY2_PRESS)
			break;
  	}
	goforward(0);
}
void getmax2(){
	int i;
		for(i = 0;i<510;i+=0.6)
	{
		turnmiddle(1);
	}
}

void test(){
    int v = 3;
	  oled_cls();
	  oled_p6x8str(0,0,"test");
	while(1){
    goforward(v);
		delay_ms(3000);
		rightline(-v);
		delay_ms(3000);
    rightline(v);
		delay_ms(3000);
    turnmiddle(v);
		delay_ms(3000);
	}
}