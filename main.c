#include <REGX52.H>
#include <INTRINS.H>
#include "LCD1602.H"
#include "sr04.h"
#include "function.h"

void main(){
	int num,t,i;
	char str[6];
	sr04_init();LCD_Init();
	
	LCD_ShowString(1,1,"length:");LCD_ShowString(2,6,"cm");
	while(1){
		num = (int)(Sr04_Measure()*10);
//		LCD_ShowNum(1,1,num,5);
		str[0] = num/1000+0x30; //百位数字
		str[1] = num%1000/100+0x30; //十位数字
		t = str[1]-0x30;
		str[2] = num%1000%100/10+0x30; //个位数字
		t = t*10+(str[2]-0x30);
		str[3] = '.';
		str[4] = num%10+0x30; //保留一位小数
		str[5] = '\0';
		LCD_ShowString(2,1,str);
		if(!(str[0]-0x30) && str[1]-0x30<8){
			Buzzer_Time(50);
			Delay(t*20);
		}
	}
}