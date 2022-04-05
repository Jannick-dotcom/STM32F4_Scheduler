#include "StallardOSconfig.h"
#include "StallardOSHelpers.h"

void StallardOS_SetSysClock(uint8_t clockspeed, oscillatorType oscType)
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
    if(oscType == internal)
    {
      #ifdef STM32F4xxxx
      /* Enable HSE oscillator and activate PLL with HSE as source */
      RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
      RCC_OscInitStruct.HSEState = RCC_HSE_OFF; /* External xtal on OSC_IN/OSC_OUT */
      RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
      RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
      RCC_OscInitStruct.PLL.PLLM = (HSE_VALUE / 1000000);             // VCO input clock = 1 MHz (8 MHz / 8)
      RCC_OscInitStruct.PLL.PLLN = clockspeed * 2;           // VCO output clock = 360 MHz (1 MHz * 360)
      RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2; // PLLCLK = 180 MHz (360 MHz / 2)
      RCC_OscInitStruct.PLL.PLLQ = 7;             //
      #elif defined STM32F1xxxx
      /* Enable HSE oscillator and activate PLL with HSE as source */
      RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
      RCC_OscInitStruct.HSEState = RCC_HSE_OFF; /* External xtal on OSC_IN/OSC_OUT */
      RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
      RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
      RCC_OscInitStruct.PLL.PLLMUL = ((72000000 * 2) / HSI_VALUE);             // VCO input clock = 1 MHz (8 MHz / 8)
      #endif
    }
    else if(oscType == external)
    {
      #ifdef STM32F4xxxx
      /* Enable HSE oscillator and activate PLL with HSE as source */
      RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
      RCC_OscInitStruct.HSEState = RCC_HSE_ON; /* External xtal on OSC_IN/OSC_OUT */
      RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
      RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
      RCC_OscInitStruct.PLL.PLLM = (HSE_VALUE / 1000000);             // VCO input clock = 1 MHz (8 MHz / 8)
      RCC_OscInitStruct.PLL.PLLN = clockspeed * 2;           // VCO output clock = 360 MHz (1 MHz * 360)
      RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2; // PLLCLK = 180 MHz (360 MHz / 2)
      RCC_OscInitStruct.PLL.PLLQ = 7;             //
      #elif defined STM32F1xxxx
      /* Enable HSE oscillator and activate PLL with HSE as source */
      RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
      RCC_OscInitStruct.HSEState = RCC_HSE_ON; /* External xtal on OSC_IN/OSC_OUT */
      RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
      RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
      RCC_OscInitStruct.PLL.PLLMUL = ((72000000 * 2) / HSE_VALUE);             // VCO input clock = 1 MHz (8 MHz / 8)
      #endif
    #if defined(stm32f446ze)
    RCC_OscInitStruct.PLL.PLLR = 2;             //
    #endif
    }
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV8;  //  21 MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  //  84 MHz
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    while(1);
  }
}