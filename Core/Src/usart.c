/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
RING_BUFF_t Ringbuf_pc_rx; 
RING_BUFF_t Ringbuf_tx_pc;

uint8_t RingBuf_PC_Rx[PC_TxRx_SIZE];
uint8_t RingBuf_Tx_PC[PC_TxRx_SIZE];

uint8_t DMA_PC_Rx[PC_TxRx_SIZE];
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PB6     ------> USART1_TX
    PB7     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA2_Stream2;
    hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_CIRCULAR;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1_TX Init */
    hdma_usart1_tx.Instance = DMA2_Stream7;
    hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart1_tx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PB6     ------> USART1_TX
    PB7     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

 /**
  * @brief  初始化环形缓冲区
  * @param	无
  * @retval 无
  */
void Ringbuff_init(void)
{
	Ringbuff_config(&Ringbuf_pc_rx,sizeof(RingBuf_PC_Rx),RingBuf_PC_Rx);
    Ringbuff_config(&Ringbuf_tx_pc,sizeof(RingBuf_Tx_PC),RingBuf_Tx_PC);
}

 /**
  * @brief  开启所需功能
  * @param	无
  * @retval 无
  */
void Function_init(void)
{
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart1, DMA_PC_Rx, PC_TxRx_SIZE);
}

 /**
  * @brief  环形缓冲区配置
  * @param	ringBuff   : 缓冲区结构体指针
  * @param	bufferLen : 缓冲区大小
  * @param	pArray : 缓冲区指针
  * @retval 无
  */
void Ringbuff_config(RING_BUFF_t* ringBuff, uint16_t bufferLen, uint8_t *pArray)
{
    if((ringBuff == NULL) || (pArray == NULL))
	{
		return;
	}
	//初始化相关信息
	ringBuff->in_pos = 0;
	ringBuff->out_pos = 0;
	ringBuff->trans_len = 0;
	ringBuff->max_len = bufferLen;
	ringBuff->data_save = pArray;
}

/**
  * @brief  向缓冲区连续写入多个数据
  * @param	rbuf : 缓冲区结构体指针
  * @param	buf : 写入的数据
  * @param	len : 写入的数据长度
  * @retval true:写入成功，false:写入失败
  */
bool Ringbuff_Write_multi_data(RING_BUFF_t *rbuf, uint8_t *buf, int len)
{
    if((rbuf == NULL) || (buf == NULL) || (rbuf->data_save == NULL))
	{
		return false;
	}
    
	if(len <= 0)
		return false;
	if(len > (rbuf->max_len-rbuf->trans_len))		//余量不足
		return false;
 
	if(len <= (rbuf->max_len-rbuf->in_pos))
	{
		memcpy(rbuf->data_save + rbuf->in_pos, buf, len);
		rbuf->in_pos = (rbuf->in_pos + len) % rbuf->max_len;
	}
	else
	{
		memcpy(rbuf->data_save + rbuf->in_pos, buf, rbuf->max_len - rbuf->in_pos);
		memcpy(rbuf->data_save, buf + rbuf->max_len - rbuf->in_pos, len-(rbuf->max_len-rbuf->in_pos));
		rbuf->in_pos = len - (rbuf->max_len-rbuf->in_pos);
	}
	rbuf->trans_len += len;
	return true;
}

 /**
  * @brief  从缓冲区连续读出多个数据
  * @param	rbuf : 缓冲区结构体指针
  * @param	buf : 读出的数据
  * @param	len : 读出的数据长度
  * @retval true:读出成功，false:读出失败
  */
bool Ringbuff_Read_multi_data(RING_BUFF_t *rbuf, uint8_t *buf, int len) 
{
    if((rbuf == NULL) || (buf == NULL) || (rbuf->data_save == NULL))
	{
		return false;
	}
    
	if(len <= 0)
		return false;
 
	if(len > rbuf->trans_len)
		return false;
	if(len <= (rbuf->max_len - rbuf->out_pos))
	{
		memcpy(buf, rbuf->data_save + rbuf->out_pos, len);
		rbuf->out_pos = (rbuf->out_pos + len) % rbuf->max_len;
	}	
	else
	{
		memcpy(buf, rbuf->data_save + rbuf->out_pos, rbuf->max_len - rbuf->out_pos);
		memcpy(buf + (rbuf->max_len - rbuf->out_pos), rbuf->data_save, len - (rbuf->max_len - rbuf->out_pos));
		rbuf->out_pos = len - (rbuf->max_len - rbuf->out_pos);
	}
	rbuf->trans_len -= len;
	return true;
}

/**
 * @brief  单片机发送数据至上位机
 * @param  pdata   : 发送的数据
 * @param  len     : 发送的数据长度
 * @retval 
 */
void McuSendData(uint8_t *pdata, uint8_t len,UART_HandleTypeDef* huartx)
{
	static uint8_t TxBuf[128];
	
    for(uint8_t i=0;i<len;i++){
		TxBuf[i] = pdata[i];
	 }
	
	HAL_UART_Transmit_DMA(huartx,TxBuf,len);
}

/* USER CODE END 1 */
