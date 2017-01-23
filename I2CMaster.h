/*
 * I2CMaster.h
 *
 * Created: 1/14/2017 1:04:58 PM
 *  Author: Anju Poonia
 */ 


#ifndef I2CMASTER_H_
#define I2CMASTER_H_
#include <avr/io.h>

#define SCL 0
#define SDA 1

void init();
void start();
void stop();
void clk();
void send_address(uint8_t address);
void master_read_ack();
void master_write(uint8_t data);
void master_read();

#endif /* I2CMASTER_H_ */