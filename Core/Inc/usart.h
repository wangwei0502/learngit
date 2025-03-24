/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

#define EM_PRODUCT_VERSION         "EM_MotorMusic_V0.0.1"
#define PC_TxRx_SIZE 256

extern UART_HandleTypeDef huart1;
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */
typedef struct
{
	uint16_t	in_pos;        
	uint16_t	out_pos;       
	uint16_t	trans_len;     
	uint16_t    max_len;       
	uint8_t	    *data_save;
}RING_BUFF_t;

extern RING_BUFF_t Ringbuf_pc_rx; 
extern RING_BUFF_t Ringbuf_tx_pc;

extern uint8_t RingBuf_PC_Rx[PC_TxRx_SIZE];
extern uint8_t RingBuf_Tx_PC[PC_TxRx_SIZE];

extern uint8_t DMA_PC_Rx[PC_TxRx_SIZE];
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void Ringbuff_init(void);
void Function_init(void);
void Ringbuff_config(RING_BUFF_t* ringBuff, uint16_t bufferLen, uint8_t *data_get);

bool Ringbuff_Write_multi_data(RING_BUFF_t *rbuf, uint8_t *buf, int len);
bool Ringbuff_Read_multi_data(RING_BUFF_t *rbuf, uint8_t *buf, int len) ;

bool McuSendData(uint8_t *pdata, uint8_t len,UART_HandleTypeDef* huartx);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

