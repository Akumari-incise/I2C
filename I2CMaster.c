  /*
 * I2CMaster.c
 *
 * Created: 1/14/2017 1:04:23 PM
 *  Author: Anju Poonia
 */  

#include "I2CMaster.h"
#include <avr/io.h>

 #define F_CPU 16000000UL
 #include <util/delay.h>

int k=0;
int main(void){	
	start();
	send_address(0b11010011);                                  //7bit address+mode	 
}

void start(){	
	DDRC|=(1<<SDA);
	PORTC&=~(1<<SDA);
	_delay_ms(10);
}

void clk(int x)
{   
	DDRC|=(1<<SCL);
	if(x==1){
		PORTC|=(1<<SCL);
		_delay_ms(10);
	}
	else{
		PORTC&=~(1<<SCL);
		//_delay_ms(10);
	}
}
void send_address(uint8_t address){
	DDRC|=(1<<SCL);
	DDRC|=(1<<SDA);
	uint8_t mode=address;
	int i;
	for(i=1;i<=8;i++){
		if((address & 0x80)==128){
			clk(0);
			PORTC|= (1<<SDA);
			_delay_ms(10);
			clk(1);
		}
		else{
			clk(0);
			PORTC&=~(1<<SDA);
			_delay_ms(10);
			clk(1);
		}
		address=address<<1;
	}
	DDRC&=~(1<<SDA);
	clk(0);
	_delay_ms(10);
	
	while(((PINC & 0x02)==0)){
		clk(1); 
		if((mode & 0x01)==0x01){
			master_read();			
		}
		else{		
			master_write(0b11110000);
		}
	  
	}
	PORTC|=(1<<SDA);
	PORTC|=(1<<SCL);
}	 
void stop(){
	DDRC|=(1<<SCL);
	DDRC|=(1<<SDA);
	PORTC|=(1<<SCL);
	_delay_ms(10);
	PORTC|=(1<<SDA);
}
void master_write(uint8_t data){
	DDRC|=(1<<SCL);
	DDRC|=(1<<SDA);
		int i;
		for(i=1;i<=8;i++){
			if((data & 0x80)==128){
				clk(0);
				PORTC|= (1<<SDA);
				_delay_ms(10);
				clk(1);
			}
			else{
				clk(0);
				PORTC&=~(1<<SDA);
				_delay_ms(10);
				clk(1);
			}
			data=data<<1;
		}
		clk(0);
		_delay_ms(10);
		clk(1);
		if((PINB & 0x02)==0){
			clk(0);
			stop();
		}
		PORTC|=(1<<SCL);
		PORTC|=(1<<SDA);
}
void master_read(){
	DDRC|=(1<<SCL);
	DDRC&=~(1<<SDA);
	DDRD=0xff;
	uint8_t data =0b00000000;
	int i;
	for(i=1;i<=8;i++){
		clk(0);
		_delay_ms(10);
		
		if(i==8){
			if((PINC & (0x02))==2){
				data=(data|0x01);
				clk(1);
			}
			else{
				data=(data|0x00);
				clk(1);
			}
		}
		else{
			if((PINC & (0x02))==2){
				data=(data|0x01);
				clk(1);
			}
			else{
				data=(data|0x00);
				clk(1);
			}
			data=(data<<1);
		}
	}
	PORTD=data;              //to display output at PORTD
	DDRC|=(1<<SDA);
	clk(0);
	PORTC&=~(1<<SDA);
	_delay_ms(10);
	clk(1);
	stop();
	PORTC|=(1<<SCL);
	PORTC|=(1<<SDA);
}