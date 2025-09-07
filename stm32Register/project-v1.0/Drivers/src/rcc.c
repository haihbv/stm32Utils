#include "rcc.h"

void RCC_Clock(RCC_ClockPreset_t preset)
{
	switch (preset)
	{
	case RCC_CLOCK_CFG_72MHZ:
		RCC_ClockConfig(&(RCC_ClockConfig_t){
			.source = RCC_CLOCK_HSE,
			.pll_mul = 9, // 8MHz x 9 = 72MHz
			.ahb_div = 0,
			.apb1_div = 4,
			.apb2_div = 0,
			.flash_latency = 2});
		break;
	case RCC_CLOCK_CFG_56MHZ:
		RCC_ClockConfig(&(RCC_ClockConfig_t){
			.source = RCC_CLOCK_HSE,
			.pll_mul = 7, // 8MHz x 7 = 56MHz
			.ahb_div = 0,
			.apb1_div = 4,
			.apb2_div = 0,
			.flash_latency = 2});
		break;
	case RCC_CLOCK_CFG_48MHZ:
		RCC_ClockConfig(&(RCC_ClockConfig_t){
			.source = RCC_CLOCK_HSE,
			.pll_mul = 6, // 8MHz x 6 = 48MHz
			.ahb_div = 0,
			.apb1_div = 4,
			.apb2_div = 0,
			.flash_latency = 1});
		break;
	case RCC_CLOCK_CFG_36MHZ:
		RCC_ClockConfig(&(RCC_ClockConfig_t){
			.source = RCC_CLOCK_HSE,
			.pll_mul = 9, // 8MHz x 9 = 72MHz, chia AHB/2 = 36MHz
			.ahb_div = 8, // 0b1000: SYSCLK/2
			.apb1_div = 4,
			.apb2_div = 0,
			.flash_latency = 1});
		break;
	case RCC_CLOCK_CFG_24MHZ:
		RCC_ClockConfig(&(RCC_ClockConfig_t){
			.source = RCC_CLOCK_HSE,
			.pll_mul = 6, // 8MHz x 6 = 48MHz, chia AHB/2 = 24MHz
			.ahb_div = 8, // 0b1000: SYSCLK/2
			.apb1_div = 4,
			.apb2_div = 0,
			.flash_latency = 0});
		break;
	default:
		break;
	}
}

void RCC_ClockConfig(const RCC_ClockConfig_t *config)
{
	if (!config)
		return;
	if (config->source == RCC_CLOCK_HSE)
	{
		RCC->CR.BITS.HSEON = 1;
		while (!RCC->CR.BITS.HSERDY)
			;
	}
	else
	{
		RCC->CR.BITS.HSION = 1;
		while (!RCC->CR.BITS.HSIRDY)
			;
	}

	FLASH->ACR.BITS.LATENCY = config->flash_latency;

	RCC->CFGR.BITS.PLLSRC = (config->source == RCC_CLOCK_HSE) ? 1 : 0;
	RCC->CFGR.BITS.PLLMUL = config->pll_mul - 2; // PLLMUL = x => x+2

	RCC->CR.BITS.PLLON = 1;
	while (!RCC->CR.BITS.PLLRDY)
		;

	RCC->CFGR.BITS.HPRE = config->ahb_div;
	RCC->CFGR.BITS.PPRE1 = config->apb1_div;
	RCC->CFGR.BITS.PPRE2 = config->apb2_div;

	RCC->CFGR.BITS.SW = 2; // PLL as SYSCLK
	while (RCC->CFGR.BITS.SWS != 2)
		;
}

void RCC_APB1ClockCmd(uint32_t periph_mask, FunctionalState state)
{
	if (state == ENABLE)
	{
		RCC->APB1ENR.REG |= periph_mask;
	}
	else
	{
		RCC->APB1ENR.REG &= ~periph_mask;
	}
}
void RCC_APB2ClockCmd(uint32_t periph_mask, FunctionalState state)
{
	if (state == ENABLE)
	{
		RCC->APB2ENR.REG |= periph_mask;
	}
	else
	{
		RCC->APB2ENR.REG &= ~periph_mask;
	}
}
