/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TIM_HandleTypeDef htim1;

/* TIM1 init function */
void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 168-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_CENTERALIGNED1;
  htim1.Init.Period = 100-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 50;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_ENABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_ENABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0x22;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspInit 0 */

  /* USER CODE END TIM1_MspInit 0 */
    /* TIM1 clock enable */
    __HAL_RCC_TIM1_CLK_ENABLE();

    /* TIM1 interrupt Init */
    HAL_NVIC_SetPriority(TIM1_CC_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);
  /* USER CODE BEGIN TIM1_MspInit 1 */

  /* USER CODE END TIM1_MspInit 1 */
  }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(timHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspPostInit 0 */

  /* USER CODE END TIM1_MspPostInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM1 GPIO Configuration
    PB13     ------> TIM1_CH1N
    PB14     ------> TIM1_CH2N
    PB15     ------> TIM1_CH3N
    PA8     ------> TIM1_CH1
    PA9     ------> TIM1_CH2
    PA10     ------> TIM1_CH3
    */
    GPIO_InitStruct.Pin = U_L_Pin|V_L_Pin|W_L_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = U_Pin|V_Pin|W_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM1_MspPostInit 1 */

  /* USER CODE END TIM1_MspPostInit 1 */
  }

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspDeInit 0 */

  /* USER CODE END TIM1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM1_CLK_DISABLE();

    /* TIM1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM1_CC_IRQn);
  /* USER CODE BEGIN TIM1_MspDeInit 1 */

  /* USER CODE END TIM1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void BLDCMotor_PhaseCtrl(void)
{
	static uint8_t phase_step = 0;
	
	if(phase_step>A1C0)
	  phase_step = A1B0;

   switch(phase_step++)
   {
	   case A1B0:  	
		   HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
		   HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);	
	   
	       MOTOR_TIM_CHx_MODE(&htim1, TIM_OCMODE_PWM1, TIM_CHANNEL_1);// PWM1 模式	+    
		   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		   HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);	 
	   
	       MOTOR_TIM_CHx_MODE(&htim1, TIM_OCMODE_PWM2, TIM_CHANNEL_2);// PWM2 模式  -
		   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
		   HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);	   	   
		   break;
	   case C1B0:
		   HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
		   HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);	
	   
	       MOTOR_TIM_CHx_MODE(&htim1, TIM_OCMODE_PWM1, TIM_CHANNEL_3);// PWM1 模式	+    
		   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
		   HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);	 
	   
	       MOTOR_TIM_CHx_MODE(&htim1, TIM_OCMODE_PWM2, TIM_CHANNEL_2);// PWM2 模式  -
		   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
		   HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2); 		
		   break;
	   case C1A0:
		   HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
		   HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);	
	   
	       MOTOR_TIM_CHx_MODE(&htim1, TIM_OCMODE_PWM1, TIM_CHANNEL_3);// PWM1 模式	+    
		   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
		   HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);	 
	   
	       MOTOR_TIM_CHx_MODE(&htim1, TIM_OCMODE_PWM2, TIM_CHANNEL_1);// PWM2 模式  -
		   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		   HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);	     	
		   break;
	   case B1A0:
		   HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
		   HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);	
	   
	       MOTOR_TIM_CHx_MODE(&htim1, TIM_OCMODE_PWM1, TIM_CHANNEL_2);// PWM1 模式	+    
		   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
		   HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);	 
	   
	       MOTOR_TIM_CHx_MODE(&htim1, TIM_OCMODE_PWM2, TIM_CHANNEL_1);// PWM2 模式  -
		   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		   HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);	  	   	
		   break;
	   case B1C0:
		   HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
		   HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);	
	   
	       MOTOR_TIM_CHx_MODE(&htim1, TIM_OCMODE_PWM1, TIM_CHANNEL_2);// PWM1 模式	+    
		   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
		   HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);	 
	   
	       MOTOR_TIM_CHx_MODE(&htim1, TIM_OCMODE_PWM2, TIM_CHANNEL_3);// PWM2 模式  -
		   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
		   HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);	     	
		   break;
	   case A1C0:
		   HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
		   HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);	
	   
	       MOTOR_TIM_CHx_MODE(&htim1, TIM_OCMODE_PWM1, TIM_CHANNEL_1);// PWM1 模式	+    
		   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		   HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);	 
	   
	       MOTOR_TIM_CHx_MODE(&htim1, TIM_OCMODE_PWM2, TIM_CHANNEL_3);// PWM2 模式  -
		   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
		   HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);	     	
		   break;	   
   }
}

/**
  * 函数功能: 配置定时器输出通道的输出模式
  * 输入参数: @htim 定时器控制句柄, @OCMode 输出模式 @CHx 输出通道
  * 返 回 值: 无
  * 说    明: 修改PWM输出通道的输出模式,OC1M:输出模式选择,CC2S:输出模式或者输入模式
  */
void MOTOR_TIM_CHx_MODE(TIM_HandleTypeDef *htim, uint32_t OCMode, uint32_t CHx)
{
  uint32_t tmpccmrx = 0;
  TIM_TypeDef *TIMx = htim->Instance;
  
  switch(CHx)
  {
    case TIM_CHANNEL_1:
      /* Get the TIMx CCMR1 register value */
      tmpccmrx = TIMx->CCMR1;
    /* Reset the Output Compare mode and Capture/Compare selection Bits */
      tmpccmrx &= ~TIM_CCMR1_OC1M;// 清空对应的位
      tmpccmrx &= ~TIM_CCMR1_CC1S;// 清空对应的位
      tmpccmrx |= OCMode;         // 配置输出模式//PWM2/PWM1模式
      TIMx->CCMR1 = tmpccmrx;     // 赋值寄存器
      break;
    
    case TIM_CHANNEL_2:
      tmpccmrx = TIMx->CCMR1;
      tmpccmrx &= ~TIM_CCMR1_OC2M;
      tmpccmrx &= ~TIM_CCMR1_CC2S;
      tmpccmrx |= (OCMode<<8);
      TIMx->CCMR1 = tmpccmrx;
      break;
    case TIM_CHANNEL_3:
      tmpccmrx = TIMx->CCMR2;
      tmpccmrx &= ~TIM_CCMR2_OC3M;
      tmpccmrx &= ~TIM_CCMR2_CC3S;
      tmpccmrx |= OCMode;
      TIMx->CCMR2 = tmpccmrx;
      break;
  }
}
/* USER CODE END 1 */
