/**
 * @file    iic.h
 * @brief   I2C1 communication driver (software API using registers)
 */

#ifndef __IIC_H
#define __IIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32system.h"

/**
 * @brief  Initialize I2C1 peripheral (PB6 = SCL, PB7 = SDA)
 */
void I2C1_Init(void);

/**
 * @brief  Generate I2C START condition
 */
void I2C1_Start(void);

/**
 * @brief  Send slave address + R/W bit
 * @param  addr     7-bit I2C slave address
 * @param  is_read  1 for read, 0 for write
 */
void I2C1_WriteAddr(uint8_t addr, uint8_t is_read);

/**
 * @brief  Send one byte data to slave
 * @param  data  Data byte to send
 * @retval 0 if success, 1 if failed (NACK)
 */
uint8_t I2C1_WriteData(uint8_t data);

/**
 * @brief  Read one byte from slave
 * @param  ack  1 to send ACK, 0 to send NACK
 * @retval Data byte read
 */
uint8_t I2C1_ReadData(uint8_t ack);

/**
 * @brief  Generate I2C STOP condition
 */
void I2C1_Stop(void);

#ifdef __cplusplus
}
#endif

#endif // __IIC_H
