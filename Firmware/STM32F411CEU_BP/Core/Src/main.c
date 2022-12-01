/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : JUMPSYSTEM
  ******************************************************************************
  * @SMLCK  = 16MHz
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "menu_module.h"
#include "Display_module.h"
#include "DisplayMessages.h"
#include "INICIAR_Component.h"
#include "IO_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include "menu_module.h"
#include "INICIAR_Component.h"
#include "Consulta_component.h"
#include "Configuracao_component.h"
#include "Exportar_component.h"
#include "Apagar_component.h"
#include "IO_interface.h"
#include "DataProcessing.h"
#include "SENSORHW.h"
#include "flash_v1.0.h"
#include "HIL_INTERFACE.h"
#include "fatfs_sd.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;

/* USER CODE BEGIN PV */
volatile char key = IDDLE;
volatile unsigned char sensorFlag = 1; //ESTADO INICIAL 1->FORA DO TAPETE 0> SOBRE O TAPETE
volatile char uartBuffer[2];
volatile char rxMSG[2];
volatile char uartFlagRx = FALSE;
volatile unsigned char samples = 0;
volatile unsigned char sensorState;
volatile unsigned int timer3Data = 0;
volatile unsigned int timer3Count = 0;
volatile unsigned int timeVooCount = 0;
volatile unsigned int timeSoloCount = 0;
volatile unsigned int timeInterval = 0;
volatile unsigned int totalTimeArray[SAMPLES];
volatile unsigned int timeVoo[SAMPLES];
volatile unsigned int timeSolo[SAMPLES];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

unsigned int getTimeInterval()
{
	return timeInterval;
}
void resetTimeInterval()
{
	timeInterval = 0;
}
unsigned int* getTotalTime()
{
	return &totalTimeArray;
}

unsigned int* getTimeVoo()
{
	return &timeVoo;
}

unsigned int* getTimeSolo()
{
	return &timeSolo;
}

unsigned char resetSamplesCount()
{
	return samples = 0;
}

unsigned char* getSamplesCount()
{
	return &samples;
}

unsigned char* getRxBuffer()
{
	return &rxMSG;
}

void resetRxFlag()
{
	uartFlagRx = FALSE;
}

unsigned char getRxFlag()
{
	return uartFlagRx;
}


void resetTimer3Variable()
{
	timer3Data = 0;
}

unsigned char getKeyPressed()
{
	return key;
}

void resetKeyPressed()
{
	key = IDDLE;
	HAL_Delay(200);
}

unsigned long int* getUARTInstance()
{
	return &huart2;
}

TIM_HandleTypeDef* getTimer2Instance()
{
	return &htim2;
}

TIM_HandleTypeDef* getTimer3Instance()
{
	return &htim3;
}

unsigned char getTimer2Variable()
{
	return sensorFlag;
}

unsigned char* getSensorFlag()
{
	return &sensorFlag;
}

unsigned int* getTimer3Variable()
{
	return &timer3Data;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  struct Menu{
  	  unsigned char menuNext;
  	  unsigned char menuSelect;
  	  unsigned char menuDisplay;
  	  unsigned char menuState;
    };

    struct Menu menuTesteMain = {IDDLE,IDDLE,IDDLE,IDDLE};
    struct Menu menuTesteSub = {IDDLE,IDDLE,IDDLE,IDDLE};
    unsigned char displayUpdateStatus = IDDLE;

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_SPI1_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);
  HAL_UARTEx_ReceiveToIdle_DMA(&huart2, (uint8_t *)uartBuffer, sizeof(uartBuffer));
  __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
  homeDataDisplay(appNameMsg,companyNameMsg,appVersionMsg);
#if _VI
  readyUserInterface(&displayUpdateStatus);
  updateUserMsg(0,USERMSG1,"LABVIEW",&displayUpdateStatus);
  HIL();
  readyUserInterface(&displayUpdateStatus);
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	  HAL_Delay(500);
  }
#endif
#if _HWVALIDATION
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	  HAL_Delay(1000);
  }
#endif

//	startTM3();// teste1
//  HW_EXT_MEMORY_WRITE("adelson","teste.txt");
  HAL_Delay(100);
#if _APPLICATION
  while (1)
  {
	  switch(menuTesteMain.menuState)
	  	  {
	  		  case IDDLE:
	  			  menuTesteMain.menuState = getNextMain(IDDLE);
	  			  if(key == AVANCAR)
	  			  {
//	  				  stopTM3();// teste1
	  				  resetKeyPressed();
	  				  readyUserInterface(&displayUpdateStatus);
	  				  menuTesteMain.menuState = getNextMain(START_TEST);
	  			  }
	  		  break;

	  		  case START_TEST:
	  			  updateUserMsg(0,USERMSG1,startUserMsg,&displayUpdateStatus);
	  			  HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
	  			  HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
	  			  if(key == AVANCAR)
	  			  {
	  				  resetKeyPressed();
	  				  readyUserInterface(&displayUpdateStatus);
	  				  menuTesteMain.menuState = getNextMain(CONSULT_DATA);
	  			  }
	  			  else if(key == CONFIRMAR)
	  			  {
//	  				  HW_EXT_MEMORY_WRITE("adelson","teste.txt"); // teste1
	  				  resetKeyPressed();
	  				  readyUserInterface(&displayUpdateStatus);
	  				  menuTesteMain.menuSelect = menuTesteMain.menuState;
	  				  initStateMachine(&menuTesteSub);
	  				  readyUserInterface(&displayUpdateStatus);

	  				  menuTesteSub.menuState = IDDLE;
	  			  }
	  		  break;

	  		  case CONSULT_DATA:
	  			  updateUserMsg(0,0,consultUserMsg,&displayUpdateStatus);
	  			  HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
	  			  HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
	  			  if(key == AVANCAR)
	  			  {
	  				  resetKeyPressed();
	  				                      readyUserInterface(&displayUpdateStatus);
	  				  menuTesteMain.menuState = getNextMain(CONFIG_SENSOR);
	  			  }

	  			  else if(key == CONFIRMAR)
	  			  {
	  				  resetKeyPressed();
	  				  readyUserInterface(&displayUpdateStatus);
	  				 consultStateMachine(&menuTesteSub);
	  				  readyUserInterface(&displayUpdateStatus);
	  				 menuTesteMain.menuState = getNextMain(START_TEST);
	  				 menuTesteSub.menuState = IDDLE;
	  			  }
	  		  break;

	  		  case CONFIG_SENSOR:
	  			  updateUserMsg(0,0,configUserMsg,&displayUpdateStatus);
	  			  HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
	  			  HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
	  			  if(key == AVANCAR)
	  			  {
	  				  resetKeyPressed();
	  				  readyUserInterface(&displayUpdateStatus);
	  				  menuTesteMain.menuState = getNextMain(EXPORT_DATA);
	  			  }
	  			  else if(key == CONFIRMAR)
	  			  {
	  				  resetKeyPressed();
	  				  readyUserInterface(&displayUpdateStatus);
	  				  configStateMachine(&menuTesteSub);
	  				  readyUserInterface(&displayUpdateStatus);
	  				  menuTesteSub.menuState = IDDLE;
	  				  menuTesteMain.menuState = getNextMain(START_TEST);
	  			  }
	  		  break;

	  		  case EXPORT_DATA:
	  			  updateUserMsg(0,0,exportUserMsg,&displayUpdateStatus);
	  			  HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
	  			  HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
	  			  if(key == AVANCAR)
	  			  {
	  				  resetKeyPressed();
	  				  readyUserInterface(&displayUpdateStatus);
	  				  menuTesteMain.menuState = getNextMain(ERASE_DATA);
	  			  }
	  			  else if(key == CONFIRMAR)
	  			  {
	  				  resetKeyPressed();
	  				  readyUserInterface(&displayUpdateStatus);
	  				  exportStateMachine(&menuTesteSub);
	  				  readyUserInterface(&displayUpdateStatus);

	  				  menuTesteSub.menuState = IDDLE;
	  				  menuTesteMain.menuState = getNextMain(START_TEST);
	  			  }
	  		  break;

	  		  case ERASE_DATA:
	  			  updateUserMsg(0,0,eraseUserMsg,&displayUpdateStatus);
	  			  HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
	  			  HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
	  			  if(key == AVANCAR)
	  			  {
	  				  resetKeyPressed();
	  				  readyUserInterface(&displayUpdateStatus);
	  				  menuTesteMain.menuState = getNextMain(START_TEST);
	  			  }

	  			  else if(key == CONFIRMAR)
	  			  {
	  				  resetKeyPressed();
	  				  readyUserInterface(&displayUpdateStatus);
	  				  eraseStateMachine(&menuTesteSub);
	  				  readyUserInterface(&displayUpdateStatus);

	  				  menuTesteSub.menuState = IDDLE;
	  				  menuTesteMain.menuState = getNextMain(START_TEST);
	  			  }
	  		  break;
	  	  }
	    }
#endif
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_FALLING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 15;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 15;
  if (HAL_TIM_Encoder_Init(&htim2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 100-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1000-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SPI1_CS_Pin|LCD_D3_Pin|LCD_D2_Pin|LCD_D1_Pin
                          |LCD_D0_Pin|LCD_EN_Pin|LCD_RW_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_D7_Pin|LCD_D6_Pin|LCD_D5_Pin|LCD_D4_Pin
                          |LCD_RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI1_CS_Pin */
  GPIO_InitStruct.Pin = SPI1_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI1_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_D7_Pin LCD_D6_Pin LCD_D5_Pin LCD_D4_Pin
                           LCD_RS_Pin */
  GPIO_InitStruct.Pin = LCD_D7_Pin|LCD_D6_Pin|LCD_D5_Pin|LCD_D4_Pin
                          |LCD_RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_D3_Pin LCD_D2_Pin LCD_D1_Pin LCD_D0_Pin
                           LCD_EN_Pin LCD_RW_Pin */
  GPIO_InitStruct.Pin = LCD_D3_Pin|LCD_D2_Pin|LCD_D1_Pin|LCD_D0_Pin
                          |LCD_EN_Pin|LCD_RW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BT_MENU_Pin */
  GPIO_InitStruct.Pin = BT_MENU_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BT_MENU_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BT_AVANCA_Pin BT_SELECT_Pin BT_STOP_Pin BT_INSERT_Pin */
  GPIO_InitStruct.Pin = BT_AVANCA_Pin|BT_SELECT_Pin|BT_STOP_Pin|BT_INSERT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if(htim == &htim3) //VERIFICAR O CLOCK PARA CALCULAR O NOVO TIMER
	{
		timer3Count+=1;  //1ms
		if(timer3Count == 10)
		{
			timer3Data += timer3Count;
			timer3Count = 0;
			samples++;
		}
//
//		else if(sensorState == INTERVALO)
//		{
//			if(timer3Count == 10)
//			{
//				timeInterval +=10;
//				timer3Count = 0;
//			}
//		}

	}

}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{

	uartFlagRx = TRUE;
//	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
  HAL_UARTEx_ReceiveToIdle_DMA(&huart2, (uint8_t *)uartBuffer, sizeof(uartBuffer));
  for(unsigned char i=0;i<Size;i++)  rxMSG[i] = uartBuffer[i];
  for(unsigned char i=0;i<Size;i++)  uartBuffer[i] = '0';
  __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);

}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim2)
	{
		if(htim->Channel == 2)
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);
			sensorFlag = 1;
		}
		else if(htim->Channel == 1)
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);
			sensorFlag = 0;
		}
	}

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
		case BT_AVANCA_Pin:
			key = AVANCAR;
		break;
		case BT_INSERT_Pin:
			key = INSERIR;
		break;
		case BT_MENU_Pin:
			key = MENU;
		break;
		case BT_SELECT_Pin:
			key = CONFIRMAR;
		break;
		case BT_STOP_Pin:
			key = PARAR;
		break;
	}

}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
