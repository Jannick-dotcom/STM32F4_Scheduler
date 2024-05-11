#include "StallardOSconfig.h"
#include "StallardOSHelpers.h"

void StallardOS_SetSysClock(uint8_t clockspeed, oscillatorType oscType, uint8_t usePLL)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

#ifdef STM32F4xxxx
  if(clockspeed*2 < 100 && usePLL)
  {
    DEBUGGER_BREAK(); //clockspeed not possible
    return;
  }
  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
       clocked below the maximum system frequency, to update the voltage scaling value
       regarding system frequency refer to product datasheet. */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
#endif

  /* Get the Clocks configuration according to the internal RCC registers */
  // HAL_RCC_GetOscConfig(&RCC_OscInitStruct);

  if (oscType == internal)
  {
    /* Enable HSE oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSEState = RCC_HSE_OFF; /* External xtal on OSC_IN/OSC_OUT */
    if(usePLL)
    {
      RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
      #ifdef STM32F4xxxx
      RCC_OscInitStruct.HSIState = RCC_HSI_ON;
      RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
      RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
      RCC_OscInitStruct.PLL.PLLM = (HSI_VALUE / 1000000); // VCO input clock = 1 MHz (8 MHz / 8)
      RCC_OscInitStruct.PLL.PLLN = clockspeed * 2;        // VCO output clock = 360 MHz (1 MHz * 360)
      RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;         // PLLCLK = 180 MHz (360 MHz / 2)
      RCC_OscInitStruct.PLL.PLLQ = (clockspeed*2)/48;
      #elif defined(STM32F446ZE)
      RCC_OscInitStruct.PLL.PLLR = 2; //
      #elif defined STM32F1xxxx
      RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
      RCC_OscInitStruct.PLL.PLLMUL = ((clockspeed * 2) / (HSI_VALUE / 1000000)); // VCO input clock = 1 MHz (8 MHz / 8)
      #endif
    }
    else
      RCC_OscInitStruct.PLL.PLLState = RCC_PLL_OFF;
  }
  else if (oscType == external)
  {
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON; /* External xtal on OSC_IN/OSC_OUT */
    /* Enable HSE oscillator and activate PLL with HSE as source */
    if(usePLL)
    {
      #ifdef STM32F4xxxx
      RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
      RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
      RCC_OscInitStruct.PLL.PLLM = (HSE_VALUE / 1000000); // VCO input clock = 1 MHz (8 MHz / 8)
      RCC_OscInitStruct.PLL.PLLN = clockspeed * 2;        // VCO output clock = 360 MHz (1 MHz * 360)
      RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;         // PLLCLK = 180 MHz (360 MHz / 2)
      RCC_OscInitStruct.PLL.PLLQ = (clockspeed*2)/48;                     //
      #elif defined STM32F1xxxx
      /* Enable HSE oscillator and activate PLL with HSE as source */
      RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
      RCC_OscInitStruct.HSIState = RCC_HSI_ON;
      RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
      RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
      RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
      #elif defined(STM32F446ZE)
      RCC_OscInitStruct.PLL.PLLR = 2; //
      #endif
    }
  }
  HAL_RCC_EnableCSS();
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    DEBUGGER_BREAK();
    while (1)
      ;
  }

/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
#ifdef STM32F4xxxx
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; // 168 MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV8;  //  21 MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  //  84 MHz
#elif defined STM32F1xxxx
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; // 72 MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  // 36 MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  // 72 MHz
#endif
#ifdef STM32F4xxxx
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
#elif defined(STM32F1xxxx)
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
#endif
  {
    DEBUGGER_BREAK();
    while (1)
      ;
  }
}