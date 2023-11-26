#include "sr04.h"
#include <INTRINS.H>
#include <REGX52.H>
sbit TRIG = P1^0;
sbit ECHO = P1^1;

void Delay20us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 52;
	while (--i);
}

void sr04_init(){
	//hc-sr04初始化
	TRIG = 0;
	ECHO = 1;	 
	//定时器初始化
	TMOD |= 0x01;
	TH0 = 0x00;
	TL0 = 0x00;
	TR0 = 0;//关掉定时器
}

float Sr04_Measure(){
	unsigned int temp_arr[10],temp_sum=0,t;
	unsigned int i,j;
	float temp_result;
	
	for(i=0; i<10; i++){
		TRIG = 1;
		Delay20us();
		TRIG = 0;
		
		while(ECHO == 0);
		TH0=0X00; TL0=0X00;
		TR0 = 1;
		while(ECHO == 1);
		temp_arr[i] = TH0*256+TL0;
		
		Delay20us();
		Delay20us();
		Delay20us();
		Delay20us();
		Delay20us();
	}
	for(i=0; i<9; i++){	//冒泡排序
		for(j=i+1; j<10; j++){
			if(temp_arr[i]>temp_arr[j]){
				t = temp_arr[i];
				temp_arr[i]=temp_arr[j];
				temp_arr[j]=t;
			}
		}
	}
	for(i=2; i<8; i++) temp_sum += temp_arr[i];
	temp_result = (float)temp_sum/6;
	
	return (float)(temp_result*0.00034/2)*100;
}