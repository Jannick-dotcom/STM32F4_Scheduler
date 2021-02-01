#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#include "StallardOSconfig.h"

// clock source is selected with CLOCK_SOURCE in json config
#define USE_PLL_HSE_EXTC 0x8 // Use external clock (ST Link MCO)
#define USE_PLL_HSE_XTAL 0x4 // Use external xtal (X3 on board - not provided by default)
#define USE_PLL_HSI 0x2      // Use HSI internal clock

uint8_t SetSysClock_PLL_HSE(uint8_t clockspeed, uint8_t bypass)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  //RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
       clocked below the maximum system frequency, to update the voltage scaling value
       regarding system frequency refer to product datasheet. */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Get the Clocks configuration according to the internal RCC registers */
  HAL_RCC_GetOscConfig(&RCC_OscInitStruct);

  /* PLL could be already configured by bootlader */
  if (RCC_OscInitStruct.PLL.PLLState != RCC_PLL_ON)
  {

    /* Enable HSE oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    if (bypass == 0)
    {
      RCC_OscInitStruct.HSEState = RCC_HSE_ON; /* External 8 MHz xtal on OSC_IN/OSC_OUT */
    }
    else
    {
      RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS; /* External 8 MHz clock on OSC_IN */
    }
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;             // VCO input clock = 1 MHz (8 MHz / 8)
    RCC_OscInitStruct.PLL.PLLN = clockspeed * 2;           // VCO output clock = 360 MHz (1 MHz * 360)
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2; // PLLCLK = 180 MHz (360 MHz / 2)
    RCC_OscInitStruct.PLL.PLLQ = 7;             //
    // RCC_OscInitStruct.PLL.PLLR = 2;             //
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      return 0; // FAIL
    }
  }

  // Activate the OverDrive to reach the 180 MHz Frequency
  // if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  // {
  //   return 0; // FAIL
  // }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; // 180 MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  //  45 MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  //  90 MHz
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    return 0; // FAIL
  }
  return 1;
}

uint8_t SetSysClock_PLL_HSI(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  //RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
       clocked below the maximum system frequency, to update the voltage scaling value
       regarding system frequency refer to product datasheet. */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSI oscillator and activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;            // VCO input clock = 1 MHz (16 MHz / 16)
  RCC_OscInitStruct.PLL.PLLN = 360;           // VCO output clock = 360 MHz (1 MHz * 360)
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2; // PLLCLK = 180 MHz (360 MHz / 2)
  RCC_OscInitStruct.PLL.PLLQ = 7;             //
  // RCC_OscInitStruct.PLL.PLLR = 6;             //
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    return 0; // FAIL
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; // 180 MHz
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;        // 180 MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;         //  45 MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;         //  90 MHz
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    return 0; // FAIL
  }

  return 1; // OK
}

void StallardOS_SetSysClock(uint8_t clockspeed)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  //RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
       clocked below the maximum system frequency, to update the voltage scaling value
       regarding system frequency refer to product datasheet. */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Get the Clocks configuration according to the internal RCC registers */
  HAL_RCC_GetOscConfig(&RCC_OscInitStruct);

  /* PLL could be already configured by bootlader */
  if (RCC_OscInitStruct.PLL.PLLState != RCC_PLL_ON)
  {

    /* Enable HSE oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    // if (bypass == 0)
    // {
      RCC_OscInitStruct.HSEState = RCC_HSE_ON; /* External 8 MHz xtal on OSC_IN/OSC_OUT */
    // }
    // else
    // {
    //   RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS; /* External 8 MHz clock on OSC_IN */
    // }
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = externalOszillator;             // VCO input clock = 1 MHz (8 MHz / 8)
    RCC_OscInitStruct.PLL.PLLN = clockspeed * 2;           // VCO output clock = 360 MHz (1 MHz * 360)
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2; // PLLCLK = 180 MHz (360 MHz / 2)
    RCC_OscInitStruct.PLL.PLLQ = 7;             //
    // RCC_OscInitStruct.PLL.PLLR = 2;             //
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      while(1);
    }
  }

  // Activate the OverDrive to reach the 180 MHz Frequency
  // if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  // {
  //   while(1);
  // }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; // 168 MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  //  42 MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  //  84 MHz
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    while(1);
  }
}