#include "headfile.h"
#include <type.h>
int average(int i){
    long sum = 0;
	  int j;
	for(j = 0;j<20;j++)
   {
	    sum += adc_once(i+8, ADC_12BIT);
   }
	 return sum/20;
}

void main()
{
   float i = -1000;
	 struct Adc adc;
   struct Can can;
   struct Che che;
	 struct Adc * padc = &adc;
	 struct Can * pcan = &can;
	 struct Che * pche = &che;
   DisableGlobalIRQ();	//¹Ø±Õ×ÜÖĞ¶Ï
	 board_init();	
	 pwm_init_total();
 	 oled_init(); 
   adc_init_total();
	 oled_p6x8str(0,0,"init success");
	   oled_cls();
	   getmax1(padc);
		 choosekp(pcan);
		 choosekd(pcan);
		 choosea1(pcan);
		 choosea2(pcan);
		 oled_cls();
		// getmax2();
		 while(1)
		 {
			 getadcave(padc);
		   vccla(padc,pcan,pche);
			 go(pche);
			 
		 }
	 
	 
} 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 /*if(average(0) > 3*average(1))
			 {
			   turnmiddle(5);
				 delay_ms(500);
			 }
			 if(average(3) > 3*average(2))
			 {
			   turnmiddle(-5);
				 delay_ms(500);
			 }*/

