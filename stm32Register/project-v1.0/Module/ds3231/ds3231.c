#include "ds3231.h"

#define I2C_WRITE_CHECKED(data)      \
    do {                             \
        if (I2C1_WriteData(data)) {  \
            I2C1_Stop();             \
            return;                  \
        }                            \
    } while (0)

void DS3231_Set_Time(uint8_t hour, uint8_t minute, uint8_t second)
{
    I2C1_Start();
    I2C1_WriteAddr(DS3231_ADDRESS, 0);

    I2C_WRITE_CHECKED(DS3231_REG_SECONDS);
    I2C_WRITE_CHECKED(Dec_to_Bcd(second));
    I2C_WRITE_CHECKED(Dec_to_Bcd(minute));
    I2C_WRITE_CHECKED(Dec_to_Bcd(hour));

    I2C1_Stop();
}

void DS3231_Get_Time(uint8_t *hour, uint8_t *minute, uint8_t *second)
{
    I2C1_Start();
    I2C1_WriteAddr(DS3231_ADDRESS, 0);
    I2C1_WriteData(DS3231_REG_SECONDS);

    I2C1_Start();
    I2C1_WriteAddr(DS3231_ADDRESS, 1);

    *second = Bcd_To_Dec(I2C1_ReadData(1));
    *minute = Bcd_To_Dec(I2C1_ReadData(1));
    *hour   = Bcd_To_Dec(I2C1_ReadData(0));

    I2C1_Stop();
}
