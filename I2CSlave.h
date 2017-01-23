/*
 * I2CSlave.h
 *
 * Created: 1/14/2017 1:06:31 PM
 *  Author: Anju
 */ 


#ifndef I2CSLAVE_H_
#define I2CSLAVE_H_
#include <avr/io.h>

#define SCL 0
#define SDA 1

void slave_read_address();
void slave_read_data();
void slave_write(uint8_t data);
void slave_read_ack();
void write_ack();

#endif /* I2CSLAVE_H_ */