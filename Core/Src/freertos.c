/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "tim.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gpio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
    struct student{
        int num;
        char* name;
        char sex;
        int age;
        struct student * next;
    };
    //结构体数据
    struct student stu1={1,"张三",'N',18,NULL};
    struct student stu2={2,"李四",'V',19,NULL};
    struct student stu3={3,"王五",'N',20,NULL};
    struct student stu4={4,"赵六",'V',21,NULL};
	volatile struct student * p= NULL; //定义一个指向第一个元素的指针
	
extern  volatile uint16_t KEY_VALUE;	
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
osThreadId task1Handle;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId TxRxHandle;
osThreadId PrintfHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void Task1(void const * argument);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void TxRxTask(void const * argument);
void PrintfTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of TxRx */
  osThreadDef(TxRx, TxRxTask, osPriorityRealtime, 0, 256);
  TxRxHandle = osThreadCreate(osThread(TxRx), NULL);

  /* definition and creation of Printf */
  osThreadDef(Printf, PrintfTask, osPriorityIdle, 0, 256);
  PrintfHandle = osThreadCreate(osThread(Printf), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
    /* definition and creation of Printf */
  osThreadDef(task1, Task1, osPriorityIdle, 0, 256);
  task1Handle = osThreadCreate(osThread(task1), NULL);
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	//把数据串起来
    stu1.next=&stu2;
    stu2.next=&stu3;
    stu3.next=&stu4; 
	p=&stu1; //定义一个指向第一个元素的指针
    osDelay(1000);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_TxRxTask */
/**
* @brief Function implementing the TxRx thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TxRxTask */
void TxRxTask(void const * argument)
{
  /* USER CODE BEGIN TxRxTask */
  uint8_t databuff[PC_TxRx_SIZE] = {0};
  static uint8_t datalength = 0;
  /* Infinite loop */
  for(;;)
  {
	if(Ringbuf_pc_rx.trans_len > 0)
	{
	  HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
	  datalength = Ringbuf_pc_rx.trans_len;
	 //读取数据
      if(Ringbuff_Read_multi_data(&Ringbuf_pc_rx, databuff, Ringbuf_pc_rx.trans_len) != 0)
      {
      }

      // 发送数据
      if(McuSendData(databuff, datalength, &huart1) != 0)
      {
      }
	}
    osDelay(1);
  }
  /* USER CODE END TxRxTask */
}

/* USER CODE BEGIN Header_PrintfTask */
/**
* @brief Function implementing the Printf thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_PrintfTask */
void PrintfTask(void const * argument)
{
  /* USER CODE BEGIN PrintfTask */
  /* Infinite loop */
  for(;;)
  {
    if(KEY_VALUE == KEY1_GPIO_PIN)
	{
	  vTaskSuspend(TxRxHandle);
	  KEY_VALUE = 0;
	}
	else if(KEY_VALUE == KEY2_GPIO_PIN)
	{
	  vTaskResume(TxRxHandle);
	  KEY_VALUE = 0;
	}
	else;
	
	BLDCMotor_PhaseCtrl();
	
    osDelay(5);
  }
  /* USER CODE END PrintfTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/**
* @brief Function implementing the Printf thread.
* @param argument: Not used
* @retval None
*/

void Task1(void const * argument)
{
  /* USER CODE BEGIN PrintfTask */	
  /* Infinite loop */
  for(;;)
  {
	printf("编号\t姓名\t性别\t年龄\n");
    //打印结果可以通过判断next是否为空来结束循环
	while(p!=NULL){
		printf("%d\t%s\t%s\t%d\n",p->num,p->name,p->sex=='N'?"男":"女",p->age);
		p=p->next;//把指针移到下一个元素
	}
	vTaskDelete(NULL);
    osDelay(10);
  }
}

/* USER CODE END Application */
