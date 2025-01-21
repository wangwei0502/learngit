/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LED1_Pin|LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE2 PE3 PE4 PE0
                           PE1 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_0
                          |GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PEPin PEPin */
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = BEEP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BEEP_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 15, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 15, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 15, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 15, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 15, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

}

/* USER CODE BEGIN 2 */

/**
  * 函数功能: 设置板载LED灯的状态
  * 输入参数: LEDx:其中x可甚至为(1,2,3)用来选择对应的LED灯
  * 输入参数：state:设置LED灯的输出状态。
  *             可选值：LED_OFF：LED灯灭；
  *                     LED_ON： LED灯亮。
  *                     LED_TOGGLE：反转LED
  * 返 回 值: 无
  * 说    明：该函数使用类似标准库函数的编程方法，方便理解标准库函数编程思想。
  */
void LEDx_StateSet(uint8_t LEDx,LEDState_TypeDef state)
{
  /* 检查输入参数是否合法 */
  assert_param(IS_LED_TYPEDEF(LEDx));
  assert_param(IS_LED_STATE(state));
  
  /* 判断设置的LED灯状态，如果设置为LED灯灭 */
  if(state==LED_OFF)
  {
    if(LEDx & LED1)            
      LED1_OFF;/* LED1灭 */
    
    if(LEDx & LED2)
      LED2_OFF;/* LED2灭 */
    
    if(LEDx & LED3)
      LED3_OFF;/* LED3灭 */    
  }
  else if(state==LED_ON) /* 设置LED灯为亮 */
  {
    if(LEDx & LED1)
      LED1_ON;/* LED1亮 */
    
    if(LEDx & LED2)
      LED2_ON;/* LED2亮 */
    
    if(LEDx & LED3)
      LED3_ON;/* LED3亮 */ 
  }
  else
  {
    if(LEDx & LED1)
      LED1_TOGGLE;/* 设置引脚输出反转 */
    
    if(LEDx & LED2)
      LED2_TOGGLE;/* 设置引脚输出反转 */
    
    if(LEDx & LED3)
      LED3_TOGGLE;/* 设置引脚输出反转 */ 
  }
}

/**
  * 函数功能: 设置板载蜂鸣器的状态
  * 输入参数：state:设置蜂鸣器的状态。
  *             可选值：BEEPState_OFF：蜂鸣器不响；
  *             可选值：BEEPState_ON： 蜂鸣器响。
  * 返 回 值: 无
  * 说    明：该函数使用类似HALA库函数的编程方法，方便理解HAL库函数编程思想。
  */
void BEEP_StateSet(BEEPState_TypeDef state)
{
  /* 检查输入参数是否合法 */
  assert_param(BEEPState_TypeDef(state));
  
  /* 判断设置的蜂鸣器状态，如果设置为蜂鸣器响 */
  if(state==BEEPState_ON)
  {    
    BEEP_ON;/* 蜂鸣器响 */
  }
  else /* state=BEEPState_OFF：设置蜂鸣器不响 */
  {    
    BEEP_OFF;/* 蜂鸣器不响 */
  }
}

/**
  * 函数功能: 按键外部中断服务函数
  * 输入参数: GPIO_Pin：中断引脚
  * 返 回 值: 无
  * 说    明: 无
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin==KEY1_GPIO_PIN)
  {
    HAL_Delay(20);/* 延时一小段时间，消除抖动 */
    if(HAL_GPIO_ReadPin(KEY1_GPIO,KEY1_GPIO_PIN)==KEY1_DOWN_LEVEL)
    {
      BEEP_TOGGLE;
      LED1_ON;
    }
    __HAL_GPIO_EXTI_CLEAR_IT(KEY1_GPIO_PIN);
  }
  else if(GPIO_Pin==KEY2_GPIO_PIN)
  {
    HAL_Delay(20);/* 延时一小段时间，消除抖动 */
    if(HAL_GPIO_ReadPin(KEY2_GPIO,KEY2_GPIO_PIN)==KEY2_DOWN_LEVEL)
    {
      BEEP_TOGGLE;
      LED2_ON;
    }
    __HAL_GPIO_EXTI_CLEAR_IT(KEY2_GPIO_PIN);
  }
  else if(GPIO_Pin==KEY3_GPIO_PIN)
  {
    HAL_Delay(20);/* 延时一小段时间，消除抖动 */
    if(HAL_GPIO_ReadPin(KEY3_GPIO,KEY3_GPIO_PIN)==KEY3_DOWN_LEVEL)
    {
      BEEP_TOGGLE;
      LED3_ON;
    }
    __HAL_GPIO_EXTI_CLEAR_IT(KEY3_GPIO_PIN);
  }
  else if(GPIO_Pin==KEY4_GPIO_PIN)
  {
    HAL_Delay(20);/* 延时一小段时间，消除抖动 */
    if(HAL_GPIO_ReadPin(KEY4_GPIO,KEY4_GPIO_PIN)==KEY4_DOWN_LEVEL)
    {
      BEEP_TOGGLE;
      LED1_OFF;
      LED2_OFF;
      LED3_OFF;
    }
    __HAL_GPIO_EXTI_CLEAR_IT(KEY4_GPIO_PIN);
  }
  else if(GPIO_Pin==KEY5_GPIO_PIN)
  {
    HAL_Delay(20);/* 延时一小段时间，消除抖动 */
    if(HAL_GPIO_ReadPin(KEY5_GPIO,KEY5_GPIO_PIN)==KEY5_DOWN_LEVEL)
    {
      BEEP_TOGGLE;
      LED1_ON;  
      LED2_ON;
      LED3_ON;
    }
    __HAL_GPIO_EXTI_CLEAR_IT(KEY5_GPIO_PIN);
  }  
}
/* USER CODE END 2 */
