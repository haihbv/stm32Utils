/**
 * @file    spi.h
 * @brief   SPI driver configuration for STM32F1 using register-level access
 */
#ifndef __SPI_H
#define __SPI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32system.h"

#define NULL ((void *)0)
	
/*======================= SPI_CR1 register bits =======================*/
// CPHA: Clock phase
#define SPI_CR1_CPHA_1Edge 							(0U << 0)
#define SPI_CR1_CPHA_2Edge 							(1U << 0)

// CPOL: CLock polarity
#define SPI_CR1_CPOL_LOW 							(0U << 1)
#define SPI_CR1_CPOL_HIGH 							(1U << 1)

// *MSTR: Master selection
#define SPI_CR1_MSTR_SLAVE 							(0U << 2)
#define SPI_CR1_MSTR_MASTER 						(1U << 2)

// *BR: Baud rate control
#define SPI_CR1_BaudRate_2 							(0U << 3)
#define SPI_CR1_BaudRate_4 							(1U << 3)
#define SPI_CR1_BaudRate_8 							(2U << 3)
#define SPI_CR1_BaudRate_16 						(3U << 3)
#define SPI_CR1_BaudRate_32 						(4U << 3)
#define SPI_CR1_BaudRate_64 						(5U << 3)
#define SPI_CR1_BaudRate_128 						(6U << 3)
#define SPI_CR1_BaudRate_256 						(7U << 3)

// *SPE: SPI enable
#define SPI_CR1_SPE_DISABLE 						(0U << 6)
#define SPI_CR1_SPE_ENABLE 							(1U << 6)

// LSBFIRST: Frame format
#define SPI_CR1_FIRST_MSB 							(0U << 7)
#define SPI_CR1_FIRST_LSB 							(1U << 7)

// *SSI: Internal slave select
#define SPI_CR1_SSI_RESET 							(0U << 8)
#define SPI_CR1_SSI_SET 							(1U << 8)
  
// *SSM: Software slave management
#define SPI_CR1_SSM_DISABLE 						(0U << 9)
#define SPI_CR1_SSM_ENABLE 							(1U << 9)

#define SPI_SSM_SSI_ENABLE_MASK 					(SPI_CR1_SSI_SET | SPI_CR1_SSM_ENABLE)

// RXONLY: Receive only
#define SPI_CR1_FULL_DUPLEX 						(0U << 10)
#define SPI_CR1_OP_DISABLE 							(1U << 10)

// DFF: Data frame format
#define SPI_CR1_DFF_8bit 							(0U << 11)
#define SPI_CR1_DFF_16bit 							(1U << 11)

/*======================= SPI_CR2 register bits =======================*/
#define SPI_CR2_RXNEIE 								(1U << 6)
#define SPI_CR2_TXEIE 								(1U << 7)

/*======================= SPI_SR (Status register) flags =======================*/
#define SPI_SR_FLAG_RXNE             ((uint16_t)0x0001)  // Receive buffer not empty
#define SPI_SR_FLAG_TXE              ((uint16_t)0x0002)  // Transmit buffer empty
#define SPI_SR_FLAG_BSY              ((uint16_t)0x0080)  // Busy flag

// Chip select macros (adjust pin according to hardware)
#define CS_ON                        (GPIOB->BSRR.REG = GPIO_PIN_0)
#define CS_OFF                       (GPIOB->BRR.REG = GPIO_PIN_0)

/**
 * @brief  SPI configuration structure
 */
typedef struct
{
    uint16_t mode;        // Master or Slave mode
    uint16_t baud_rate;   // Baud rate prescaler
    uint16_t ss;          // Software NSS setting (SSI)
    uint16_t cpol;        // Clock polarity
    uint16_t cpha;        // Clock phase
    uint16_t first_bit;   // Bit order: MSB or LSB first
    uint16_t data_size;   // Data size: 8-bit or 16-bit
    uint16_t direction;   // Communication mode: full duplex or receive only
} SPI_InitTypeDef;


void SPI_Config(__IO SPI_TypeDef *SPIx);
void SPI_Init(__IO SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct);
void SPI_Cmd(__IO SPI_TypeDef *SPIx, FunctionalState state);
void SPI_Transmit(__IO SPI_TypeDef *SPIx, uint8_t data);
void SPI_Receive(__IO SPI_TypeDef *SPIx, uint8_t data);
uint8_t SPI_TransmitReceive(__IO SPI_TypeDef *SPIx, uint8_t data);
void SPI_SendCommand(__IO SPI_TypeDef *SPIx, uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H */
