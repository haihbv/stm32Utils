/**
 * @file       ds3231.h
 * @brief      Driver for DS3231 RTC (Real Time Clock) module using I2C
 * @author     Hai
 * 
 * This header file provides function declarations and macros to
 * communicate with the DS3231 RTC module via I2C. It allows setting
 * and reading the current time (hour, minute, second).
 */

#ifndef __DS3231_H
#define __DS3231_H

#include <stdint.h>
#include "i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

// I2C address of DS3231 (7-bit format)
#define DS3231_ADDRESS        0x68

// DS3231 register address for seconds
#define DS3231_REG_SECONDS    0x00

/**
 * @brief Convert BCD format to decimal
 * @param bcd_val BCD value (0–99)
 * @return Decimal value
 */
static inline uint8_t Bcd_To_Dec(uint8_t bcd_val)
{
    return ((bcd_val >> 4) * 10 + (bcd_val & 0x0F));
}

/**
 * @brief Convert decimal to BCD format
 * @param dec_val Decimal value (0–99)
 * @return BCD value
 */
static inline uint8_t Dec_to_Bcd(uint8_t dec_val)
{
    return (uint8_t)(((dec_val / 10) << 4) | (dec_val % 10));
}

/**
 * @brief Set time to DS3231 (hour, minute, second)
 * @param hour   Hour (0–23)
 * @param minute Minute (0–59)
 * @param second Second (0–59)
 */
void DS3231_Set_Time(uint8_t hour, uint8_t minute, uint8_t second);

/**
 * @brief Read time from DS3231 (hour, minute, second)
 * @param hour   Pointer to save hour
 * @param minute Pointer to save minute
 * @param second Pointer to save second
 */
void DS3231_Get_Time(uint8_t *hour, uint8_t *minute, uint8_t *second);

#ifdef __cplusplus
}
#endif

#endif // __DS3231_H
