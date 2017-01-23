  /*
 * I2CSlave.c
 *
 * Created: 1/14/2017 1:06:02 PM
 *  Author: Anju
 */ 


#include <avr/io.h>
#include "I2CSlave.h"
#define F_CPU 16000000UL
#include <util/delay.h> 

int main(void)
{
	
   slave_read_address();
}
void slave_read_address(){
	DDRC&=~(1<<SCL);
	DDRC&=~(1<<SDA);
	DDRD=0xff;
	DDRB=0xff;
	uint8_t slaveaddress=0b1101001;
	uint8_t address=0b0000000;
	uint8_t mode=0b00000000;
		int i;
		for(i=1;i<=8;i++){
			_delay_ms(20);
			if(i==8){
				if((PINC & (0x02))==2){
					mode=(mode|0x01);
				}
				else{
					mode=(mode|0x00);
				}
			}
			else if(i==7){
				
				if((PINC & (0x02))==2){
					address=(address|0x01);
				}
				else{
					address=(address|0x00);
				}
				 
			}
			else{
					if((PINC & (0x02))==2){
					address=(address|0x01);
		
					
				}
				else{
					address=(address|0x00);
				}
				
				address=address<<1;
			}
		}
		PORTB=address;      //to display output at PORTD
     	DDRC|=(1<<SDA);
		DDRC&=~(1<<SCL);
		_delay_ms(20);
	     
	        if(((PINC & 0x01)==0)){
		     if(address==slaveaddress){
			  PORTC&=~(1<<SDA);
			  _delay_ms(10);
		     }
		     if(mode==0x01){
			  slave_write(0b10101010);
		     }
		    else
			 slave_read_data(); 
	       }	
	PORTC|=(1<<SDA);
}
     
void slave_read_data(){
	DDRC&=~(1<<SCL);
	DDRC&=~(1<<SDA);
	uint8_t data;
	int i;
	data =0b00000000;
	for(i=1;i<=8;i++){
		_delay_ms(19);
		if(i==8){
			if((PINC & (0x02))==2){
				data=(data|0x01);
			}
			else{
				data=(data|0x00);
			}
		}
		else{
			if((PINC & (0x02))==2){
				data=(data|0x01);
				
			}
			else{
				data=(data|0x00);
			}
			
			data=data<<1;
		}
	}
	PORTD=data;      //to display output at PORTD
	 DDRC|=(1<<SDA);
		PORTC&=~(1<<SDA);
		_delay_ms(10);
		PORTC|=(1<<SDA);
	 
}
void slave_write(uint8_t data){
	  DDRC&=~(1<<SCL);
	  DDRC|=(1<<SDA);
	 int i=1,flag=0,bitsend=0;
	 while(i<=8){
		 if(((PINC & (0x01))==1) && (flag==0)){
			 flag=1;
		 }
		 if(((PINC & (0x01))==0) && (flag==1)){
			 bitsend=1;
			 flag=0;
		 }
		 if(bitsend==1){
			 if((data & 0x80)==128){
				 PORTC|= (1<<SDA);
				 _delay_ms(10);
			 }
			 else{
				 PORTC&=~(1<<SDA);
				 _delay_ms(10);
			 }
			 data=data<<1;
			 bitsend=0;
			 i++;
		 }
	 }
	 PORTC|=(1<<SDA);
}
