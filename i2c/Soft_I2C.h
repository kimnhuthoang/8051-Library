
#ifndef	_SOFT_I2C_H_
#define _SOFT_I2C_H_

sbit SCL=P3^0;
sbit SDA=P3^1;

// Init
void i2c_init();

// Master generate Start signal
void i2c_start();

// Master generate Stop signal
void i2c_stop();

// Write data to Slaver, and get ACK/NACK from Slaver
bit i2c_write(unsigned char dat);

// Read data from Slaver
unsigned char i2c_read(bit ack);

#endif
