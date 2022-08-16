/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "menu_module.h"
#include "Display_module.h"
#include "DisplayMessages.h"
#include "INICIAR_Component.h"
#include "IO_interface.h"

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
 TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;

unsigned char key = IDDLE;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
unsigned char getKeyPressed()
{
	return key;
}

unsigned char resetKeyPressed()
{
	key = IDDLE;
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

  struct dataInsert{
      unsigned char userTime;
      unsigned char userMass;
      unsigned char userOverMass;
      unsigned char userConsultTest;
      unsigned char userAlturaMin;
      unsigned char userAlturaMax;
      unsigned char userNumSaltos;
      unsigned char userIntervalSaltos;
      unsigned char userCMJ;
      unsigned char userAlturaDJ;
      unsigned char userNumSeries;
      unsigned char userIntervalSeries;
      unsigned char userCommConfig;
      unsigned char userSelectTapete;

  };
  struct Menu{
	  unsigned char menuNext;
	  unsigned char menuSelect;
	  unsigned char menuDisplay;
	  unsigned char menuState;
	  struct dataInsert menuInsert;
  };

  struct Menu menuTesteMain = {IDDLE,IDDLE,IDDLE,IDDLE};
  struct Menu menuTesteSub = {IDDLE,IDDLE,IDDLE,IDDLE};
  unsigned char* mainMenuArray;
  unsigned char* subMenuArray;
  unsigned char displayUpdateStatus = IDDLE;
  unsigned char cursorPosition[1] = {0,0};

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
  /* USER CODE BEGIN 2 */


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //PAREI AQUI
  menuTesteMain.menuDisplay = startUserInterface(appNameMsg,companyNameMsg,appVersionMsg);
  while (1)
  {
	  switch(menuTesteMain.menuState)
	  {
		  case IDDLE:
			  if(key == AVANCAR)
			  {
				  IOStatus(&displayUpdateStatus,&cursorPosition);
				  menuTesteMain.menuState = getNextMain(START_TEST);
			  }
//			  else if(key == CONFIRMAR)  menuTesteMain.menuState = setSelectMain(&menuTesteMain.menuState);
		  break;

		  case START_TEST:
			  updateUserMsg(3,2,startUserMsg,&displayUpdateStatus);
			  if(key == AVANCAR)
			  {
				  IOStatus(&displayUpdateStatus,&cursorPosition);
				  menuTesteMain.menuState = getNextMain(CONSULT_DATA);
			  }
			  else if(key == CONFIRMAR)
			  {
				  IOStatus(&displayUpdateStatus,&cursorPosition);
				  menuTesteMain.menuState = setSelectMain(&menuTesteMain.menuState);
				  menuTesteMain.menuSelect = menuTesteMain.menuState;
				  initStateMachine(&menuTesteSub);
				  menuTesteSub.menuState = IDDLE;
				  menuTesteSub.menuSelect = IDDLE;
			  }
		  break;

		  case CONSULT_DATA:
			  updateUserMsg(3,2,consultUserMsg,&displayUpdateStatus);
			  if(key == AVANCAR)
			  {
				  IOStatus(&displayUpdateStatus,&cursorPosition);
				  menuTesteMain.menuState = getNextMain(CONFIG_SENSOR);
			  }

			  else if(key == CONFIRMAR)
			  {
				 IOStatus(&displayUpdateStatus,&cursorPosition);
				 menuTesteMain.menuState = setSelectMain(&menuTesteMain.menuState);
//				 consultStateMachine(&menuTesteSub);
				 menuTesteMain.menuState = getNextMain(START_TEST);
				 menuTesteSub.menuState = IDDLE;
				 menuTesteSub.menuSelect = IDDLE;
			  }
		  break;

		  case CONFIG_SENSOR:
			  updateUserMsg(3,2,configUserMsg,&displayUpdateStatus);
			  if(key == AVANCAR)
			  {
				  IOStatus(&displayUpdateStatus,&cursorPosition);
				  menuTesteMain.menuState = getNextMain(EXPORT_DATA);
			  }
			  else if(key == CONFIRMAR)
			  {
				  IOStatus(&displayUpdateStatus,&cursorPosition);
				  menuTesteMain.menuState = setSelectMain(&menuTesteMain.menuState);
//				  configStateMachine(&menuTesteSub);
				  menuTesteSub.menuState = IDDLE;
				  menuTesteSub.menuSelect = IDDLE;
				  menuTesteMain.menuState = getNextMain(START_TEST);
			  }
		  break;

		  case EXPORT_DATA:
			  updateUserMsg(3,2,exportUserMsg,&displayUpdateStatus);
			  if(key == AVANCAR)
			  {
				  IOStatus(&displayUpdateStatus,&cursorPosition);
				  displayUpdateStatus = IDDLE;
				  menuTesteMain.menuState = getNextMain(ERASE_DATA);
			  }
			  else if(key == CONFIRMAR)
			  {
				  IOStatus(&displayUpdateStatus,&cursorPosition);
				  menuTesteMain.menuState = setSelectMain(&menuTesteMain.menuState);
//				  exportStateMachine(&menuTesteSub);
				  menuTesteSub.menuState = IDDLE;
				  menuTesteSub.menuSelect = IDDLE;
				  menuTesteMain.menuState = getNextMain(START_TEST);
			  }
		  break;

		  case ERASE_DATA:
			  updateUserMsg(3,2,eraseUserMsg,&displayUpdateStatus);
			  if(key == AVANCAR)
			  {
				  IOStatus(&displayUpdateStatus,&cursorPosition);
				  displayUpdateStatus = IDDLE;
				  menuTesteMain.menuState = getNextMain(START_TEST);
			  }
			  else if(key == CONFIRMAR)
			  {
				  IOStatus(&displayUpdateStatus,&cursorPosition);
				  menuTesteMain.menuState = setSelectMain(&menuTesteMain.menuState);
//				  eraseStateMachine(&menuTesteSub);
				  menuTesteSub.menuState = IDDLE;
				  menuTesteSub.menuSelect = IDDLE;
				  menuTesteMain.menuState = getNextMain(START_TEST);
			  }
		  break;
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
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
  htim3.Init.Prescaler = 72-1;
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
  /* DMA1_Channel6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_D7_Pin|LCD_D6_Pin|LCD_D5_Pin|LCD_D4_Pin
                          |LCD_RS_Pin|RELAY_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_D3_Pin|LCD_D2_Pin|LCD_D1_Pin|LCD_D0_Pin
                          |LCD_EN_Pin|LCD_RW_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_D7_Pin LCD_D6_Pin LCD_D5_Pin LCD_D4_Pin
                           LCD_RS_Pin RELAY_Pin */
  GPIO_InitStruct.Pin = LCD_D7_Pin|LCD_D6_Pin|LCD_D5_Pin|LCD_D4_Pin
                          |LCD_RS_Pin|RELAY_Pin;
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

  /*Configure GPIO pins : BT_MENU_Pin BT_AVANCA_Pin BT_SELECT_Pin BT_STOP_Pin
                           BT_INSERT_Pin */
  GPIO_InitStruct.Pin = BT_MENU_Pin|BT_AVANCA_Pin|BT_SELECT_Pin|BT_STOP_Pin
                          |BT_INSERT_Pin;
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

}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{

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
