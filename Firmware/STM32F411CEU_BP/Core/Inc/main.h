/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE BEGIN EM */

/*Defines para validação
 *
 */
#define _VI	0
#define _HWVALIDATION	0
#define SAMPLES 10
#define _APPLICATION 0
#define _MEASUREVALIDATION 1

/*
 * Defines da solução
 */

#define TRUE            1
#define FALSE           0

#define FORA 	'0'
#define DENTRO 	'1'
#define REPOUSO '2'
#define CONTATO '3'
#define VOO     '4'
#define TIMEOUT	'5'
#define MAX_SERIE '6'
#define INTERVALO '7'

#define SUBMENU_SIZE    15
#define MAINMENU_SIZE   4
#define HOME            1

//MENU MACHINE STATE
#define IDDLE           0
#define START_TEST      1
#define CONSULT_DATA    2
#define CONFIG_SENSOR   3
#define EXPORT_DATA     4
#define ERASE_DATA      5
#define TESTE           6


//INICIAR MACHINE STATE
#define COMM_OFF        1
#define COMM_ON         2
#define TEMPO_READ      3
#define MASSA_READ      4
#define SOBREC_READ     5
#define START           6
#define READING         7
#define STOP            8
#define DISP_RESULTS    9
#define RESULTS         10
#define SAVE_DATA       11
#define CANCEL_SAVE     12

//CONSULTA MACHINE STATE
#define CONSULTA_TESTE  1
#define RESULT_TESTE    2
#define EXPORTAR        3

//CONFIGURACAO MACHINE STATE
#define CONFIG_SENSOR_1     1
#define CONFIG_SENSOR_2     2
#define SENSOR_ALTMIN       3
#define SENSOR_ALTMAX       4
#define SENSOR_SALTOS       5
#define SENSOR_INT_SALTOS   6
#define SENSOR_JMP_SELECT   7
#define SENSOR_ALTDJ        8
#define SENSOR_SERIES       9
#define SENSOR_INT_SERIES   10
#define TAPETE_ON           11
#define TAPETE_OFF          12
#define SAVE_CONFIGS        13

//EXPORTACAO MACHINE STATE
#define VERIFICA_COMM         1
#define EXPORTAR_UNITARIO     2
#define NUM_TESTE_EXPORT      3
#define PROCESS_UNITARIO      4
#define EXPORTAR_TODOS        5
#define PROCESS_TODOS         6

//APAGA DADOS MACHINE STATE
#define VERFICA_APAGAR      1
#define CONFIRMA_APAGAR     2
#define CONFIRMA            5
#define RET_MENU            2

//COMANDOS USU�?RIO
#define AVANCAR     'A'
#define CONFIRMAR   'C'
#define PARAR       'P'
#define MENU        'M'
#define INSERIR     'I'
#define AMOSTRA     ';'


//QUANTIDADE DE TESTES
#define TEST_SIZE   5
#define MEASUREMENT_SIZE   5

//READ FILE MATRIX
#define MAX_LINES 10
#define MAX_LEN 100

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/*Defines para validação
 *
 */
#define _VI	0
#define _HWVALIDATION	1
#define SAMPLES 10
#define _APPLICATION 0

/*
 * Defines da solução
 */

#define TRUE            1
#define FALSE           0

#define FORA 	'0'
#define DENTRO 	'1'
#define REPOUSO '2'
#define CONTATO '3'
#define VOO     '4'
#define TIMEOUT	'5'
#define MAX_SERIE '6'
#define INTERVALO '7'

#define SUBMENU_SIZE    15
#define MAINMENU_SIZE   4
#define HOME            1

//MENU MACHINE STATE
#define IDDLE           0
#define START_TEST      1
#define CONSULT_DATA    2
#define CONFIG_SENSOR   3
#define EXPORT_DATA     4
#define ERASE_DATA      5
#define TESTE           6


//INICIAR MACHINE STATE
#define COMM_OFF        1
#define COMM_ON         2
#define TEMPO_READ      3
#define MASSA_READ      4
#define SOBREC_READ     5
#define START           6
#define READING         7
#define STOP            8
#define DISP_RESULTS    9
#define RESULTS         10
#define SAVE_DATA       11
#define CANCEL_SAVE     12

//CONSULTA MACHINE STATE
#define CONSULTA_TESTE  1
#define RESULT_TESTE    2
#define EXPORTAR        3

//CONFIGURACAO MACHINE STATE
#define CONFIG_SENSOR_1     1
#define CONFIG_SENSOR_2     2
#define SENSOR_ALTMIN       3
#define SENSOR_ALTMAX       4
#define SENSOR_SALTOS       5
#define SENSOR_INT_SALTOS   6
#define SENSOR_JMP_SELECT   7
#define SENSOR_ALTDJ        8
#define SENSOR_SERIES       9
#define SENSOR_INT_SERIES   10
#define TAPETE_ON           11
#define TAPETE_OFF          12
#define SAVE_CONFIGS        13

//EXPORTACAO MACHINE STATE
#define VERIFICA_COMM         1
#define EXPORTAR_UNITARIO     2
#define NUM_TESTE_EXPORT      3
#define PROCESS_UNITARIO      4
#define EXPORTAR_TODOS        5
#define PROCESS_TODOS         6

//APAGA DADOS MACHINE STATE
#define VERFICA_APAGAR      1
#define CONFIRMA_APAGAR     2
#define CONFIRMA            5
#define RET_MENU            2

//COMANDOS USU�?RIO
#define AVANCAR     'A'
#define CONFIRMAR   'C'
#define PARAR       'P'
#define MENU        'M'
#define INSERIR     'I'
#define AMOSTRA     ';'


//QUANTIDADE DE TESTES
#define TEST_SIZE   5
#define MEASUREMENT_SIZE   5

//READ FILE MATRIX
#define MAX_LINES 10
#define MAX_LEN 100

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/*Defines para validação
 *
 */
#define _VI	0
#define _HWVALIDATION	0
#define SAMPLES 10
#define _APPLICATION 1

/*
 * Defines da solução
 */

#define TRUE            1
#define FALSE           0

#define FORA 	'0'
#define DENTRO 	'1'
#define REPOUSO '2'
#define CONTATO '3'
#define VOO     '4'
#define TIMEOUT	'5'
#define MAX_SERIE '6'
#define INTERVALO '7'

#define SUBMENU_SIZE    15
#define MAINMENU_SIZE   4
#define HOME            1

//MENU MACHINE STATE
#define IDDLE           0
#define START_TEST      1
#define CONSULT_DATA    2
#define CONFIG_SENSOR   3
#define EXPORT_DATA     4
#define ERASE_DATA      5
#define TESTE           6


//INICIAR MACHINE STATE
#define COMM_OFF        1
#define COMM_ON         2
#define TEMPO_READ      3
#define MASSA_READ      4
#define SOBREC_READ     5
#define START           6
#define READING         7
#define STOP            8
#define DISP_RESULTS    9
#define RESULTS         10
#define SAVE_DATA       11
#define CANCEL_SAVE     12

//CONSULTA MACHINE STATE
#define CONSULTA_TESTE  1
#define RESULT_TESTE    2
#define EXPORTAR        3

//CONFIGURACAO MACHINE STATE
#define CONFIG_SENSOR_1     1
#define CONFIG_SENSOR_2     2
#define SENSOR_ALTMIN       3
#define SENSOR_ALTMAX       4
#define SENSOR_SALTOS       5
#define SENSOR_INT_SALTOS   6
#define SENSOR_JMP_SELECT   7
#define SENSOR_ALTDJ        8
#define SENSOR_SERIES       9
#define SENSOR_INT_SERIES   10
#define TAPETE_ON           11
#define TAPETE_OFF          12
#define SAVE_CONFIGS        13

//EXPORTACAO MACHINE STATE
#define VERIFICA_COMM         1
#define EXPORTAR_UNITARIO     2
#define NUM_TESTE_EXPORT      3
#define PROCESS_UNITARIO      4
#define EXPORTAR_TODOS        5
#define PROCESS_TODOS         6

//APAGA DADOS MACHINE STATE
#define VERFICA_APAGAR      1
#define CONFIRMA_APAGAR     2
#define CONFIRMA            5
#define RET_MENU            2

//COMANDOS USU�?RIO
#define AVANCAR     'A'
#define CONFIRMAR   'C'
#define PARAR       'P'
#define MENU        'M'
#define INSERIR     'I'
#define AMOSTRA     ';'


//QUANTIDADE DE TESTES
#define TEST_SIZE   5
#define MEASUREMENT_SIZE   5

//READ FILE MATRIX
#define MAX_LINES 10
#define MAX_LEN 100

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/*Defines para validação
 *
 */
#define _VI	0
#define _HWVALIDATION	0
#define SAMPLES 10
#define _APPLICATION 1

/*
 * Defines da solução
 */

#define TRUE            1
#define FALSE           0

#define FORA 	'0'
#define DENTRO 	'1'
#define REPOUSO '2'
#define CONTATO '3'
#define VOO     '4'
#define TIMEOUT	'5'
#define MAX_SERIE '6'
#define INTERVALO '7'

#define SUBMENU_SIZE    15
#define MAINMENU_SIZE   4
#define HOME            1

//MENU MACHINE STATE
#define IDDLE           0
#define START_TEST      1
#define CONSULT_DATA    2
#define CONFIG_SENSOR   3
#define EXPORT_DATA     4
#define ERASE_DATA      5
#define TESTE           6


//INICIAR MACHINE STATE
#define COMM_OFF        1
#define COMM_ON         2
#define TEMPO_READ      3
#define MASSA_READ      4
#define SOBREC_READ     5
#define START           6
#define READING         7
#define STOP            8
#define DISP_RESULTS    9
#define RESULTS         10
#define SAVE_DATA       11
#define CANCEL_SAVE     12

//CONSULTA MACHINE STATE
#define CONSULTA_TESTE  1
#define RESULT_TESTE    2
#define EXPORTAR        3

//CONFIGURACAO MACHINE STATE
#define CONFIG_SENSOR_1     1
#define CONFIG_SENSOR_2     2
#define SENSOR_ALTMIN       3
#define SENSOR_ALTMAX       4
#define SENSOR_SALTOS       5
#define SENSOR_INT_SALTOS   6
#define SENSOR_JMP_SELECT   7
#define SENSOR_ALTDJ        8
#define SENSOR_SERIES       9
#define SENSOR_INT_SERIES   10
#define TAPETE_ON           11
#define TAPETE_OFF          12
#define SAVE_CONFIGS        13

//EXPORTACAO MACHINE STATE
#define VERIFICA_COMM         1
#define EXPORTAR_UNITARIO     2
#define NUM_TESTE_EXPORT      3
#define PROCESS_UNITARIO      4
#define EXPORTAR_TODOS        5
#define PROCESS_TODOS         6

//APAGA DADOS MACHINE STATE
#define VERFICA_APAGAR      1
#define CONFIRMA_APAGAR     2
#define CONFIRMA            5
#define RET_MENU            2

//COMANDOS USU�?RIO
#define AVANCAR     'A'
#define CONFIRMAR   'C'
#define PARAR       'P'
#define MENU        'M'
#define INSERIR     'I'
#define AMOSTRA     ';'


//QUANTIDADE DE TESTES
#define TEST_SIZE   5
#define MEASUREMENT_SIZE   5

//READ FILE MATRIX
#define MAX_LINES 10
#define MAX_LEN 100

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/*Defines para validação
 *
 */
#define _VI	0
#define _HWVALIDATION	0
#define SAMPLES 10
#define _APPLICATION 1

/*
 * Defines da solução
 */

#define TRUE            1
#define FALSE           0

#define FORA 	'0'
#define DENTRO 	'1'
#define REPOUSO '2'
#define CONTATO '3'
#define VOO     '4'
#define TIMEOUT	'5'
#define MAX_SERIE '6'
#define INTERVALO '7'

#define SUBMENU_SIZE    15
#define MAINMENU_SIZE   4
#define HOME            1

//MENU MACHINE STATE
#define IDDLE           0
#define START_TEST      1
#define CONSULT_DATA    2
#define CONFIG_SENSOR   3
#define EXPORT_DATA     4
#define ERASE_DATA      5
#define TESTE           6


//INICIAR MACHINE STATE
#define COMM_OFF        1
#define COMM_ON         2
#define TEMPO_READ      3
#define MASSA_READ      4
#define SOBREC_READ     5
#define START           6
#define READING         7
#define STOP            8
#define DISP_RESULTS    9
#define RESULTS         10
#define SAVE_DATA       11
#define CANCEL_SAVE     12

//CONSULTA MACHINE STATE
#define CONSULTA_TESTE  1
#define RESULT_TESTE    2
#define EXPORTAR        3

//CONFIGURACAO MACHINE STATE
#define CONFIG_SENSOR_1     1
#define CONFIG_SENSOR_2     2
#define SENSOR_ALTMIN       3
#define SENSOR_ALTMAX       4
#define SENSOR_SALTOS       5
#define SENSOR_INT_SALTOS   6
#define SENSOR_JMP_SELECT   7
#define SENSOR_ALTDJ        8
#define SENSOR_SERIES       9
#define SENSOR_INT_SERIES   10
#define TAPETE_ON           11
#define TAPETE_OFF          12
#define SAVE_CONFIGS        13

//EXPORTACAO MACHINE STATE
#define VERIFICA_COMM         1
#define EXPORTAR_UNITARIO     2
#define NUM_TESTE_EXPORT      3
#define PROCESS_UNITARIO      4
#define EXPORTAR_TODOS        5
#define PROCESS_TODOS         6

//APAGA DADOS MACHINE STATE
#define VERFICA_APAGAR      1
#define CONFIRMA_APAGAR     2
#define CONFIRMA            5
#define RET_MENU            2

//COMANDOS USU�?RIO
#define AVANCAR     'A'
#define CONFIRMAR   'C'
#define PARAR       'P'
#define MENU        'M'
#define INSERIR     'I'
#define AMOSTRA     ';'


//QUANTIDADE DE TESTES
#define TEST_SIZE   5
#define MEASUREMENT_SIZE   5

//READ FILE MATRIX
#define MAX_LINES 10
#define MAX_LEN 100

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/*Defines para validação
 *
 */
#define _VI	0
#define _HWVALIDATION	0
#define SAMPLES 10
#define _APPLICATION 1

/*
 * Defines da solução
 */

#define TRUE            1
#define FALSE           0

#define FORA 	'0'
#define DENTRO 	'1'
#define REPOUSO '2'
#define CONTATO '3'
#define VOO     '4'
#define TIMEOUT	'5'
#define MAX_SERIE '6'
#define INTERVALO '7'

#define SUBMENU_SIZE    15
#define MAINMENU_SIZE   4
#define HOME            1

//MENU MACHINE STATE
#define IDDLE           0
#define START_TEST      1
#define CONSULT_DATA    2
#define CONFIG_SENSOR   3
#define EXPORT_DATA     4
#define ERASE_DATA      5
#define TESTE           6


//INICIAR MACHINE STATE
#define COMM_OFF        1
#define COMM_ON         2
#define TEMPO_READ      3
#define MASSA_READ      4
#define SOBREC_READ     5
#define START           6
#define READING         7
#define STOP            8
#define DISP_RESULTS    9
#define RESULTS         10
#define SAVE_DATA       11
#define CANCEL_SAVE     12

//CONSULTA MACHINE STATE
#define CONSULTA_TESTE  1
#define RESULT_TESTE    2
#define EXPORTAR        3

//CONFIGURACAO MACHINE STATE
#define CONFIG_SENSOR_1     1
#define CONFIG_SENSOR_2     2
#define SENSOR_ALTMIN       3
#define SENSOR_ALTMAX       4
#define SENSOR_SALTOS       5
#define SENSOR_INT_SALTOS   6
#define SENSOR_JMP_SELECT   7
#define SENSOR_ALTDJ        8
#define SENSOR_SERIES       9
#define SENSOR_INT_SERIES   10
#define TAPETE_ON           11
#define TAPETE_OFF          12
#define SAVE_CONFIGS        13

//EXPORTACAO MACHINE STATE
#define VERIFICA_COMM         1
#define EXPORTAR_UNITARIO     2
#define NUM_TESTE_EXPORT      3
#define PROCESS_UNITARIO      4
#define EXPORTAR_TODOS        5
#define PROCESS_TODOS         6

//APAGA DADOS MACHINE STATE
#define VERFICA_APAGAR      1
#define CONFIRMA_APAGAR     2
#define CONFIRMA            5
#define RET_MENU            2

//COMANDOS USU�?RIO
#define AVANCAR     'A'
#define CONFIRMAR   'C'
#define PARAR       'P'
#define MENU        'M'
#define INSERIR     'I'
#define AMOSTRA     ';'


//QUANTIDADE DE TESTES
#define TEST_SIZE   5
#define MEASUREMENT_SIZE   5

//READ FILE MATRIX
#define MAX_LINES 10
#define MAX_LEN 100

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/*Defines para validação
 *
 */
#define _VI	0
#define _HWVALIDATION	0
#define SAMPLES 10
#define _APPLICATION 1

/*
 * Defines da solução
 */

#define TRUE            1
#define FALSE           0

#define FORA 	'0'
#define DENTRO 	'1'
#define REPOUSO '2'
#define CONTATO '3'
#define VOO     '4'
#define TIMEOUT	'5'
#define MAX_SERIE '6'
#define INTERVALO '7'

#define SUBMENU_SIZE    15
#define MAINMENU_SIZE   4
#define HOME            1

//MENU MACHINE STATE
#define IDDLE           0
#define START_TEST      1
#define CONSULT_DATA    2
#define CONFIG_SENSOR   3
#define EXPORT_DATA     4
#define ERASE_DATA      5
#define TESTE           6


//INICIAR MACHINE STATE
#define COMM_OFF        1
#define COMM_ON         2
#define TEMPO_READ      3
#define MASSA_READ      4
#define SOBREC_READ     5
#define START           6
#define READING         7
#define STOP            8
#define DISP_RESULTS    9
#define RESULTS         10
#define SAVE_DATA       11
#define CANCEL_SAVE     12

//CONSULTA MACHINE STATE
#define CONSULTA_TESTE  1
#define RESULT_TESTE    2
#define EXPORTAR        3

//CONFIGURACAO MACHINE STATE
#define CONFIG_SENSOR_1     1
#define CONFIG_SENSOR_2     2
#define SENSOR_ALTMIN       3
#define SENSOR_ALTMAX       4
#define SENSOR_SALTOS       5
#define SENSOR_INT_SALTOS   6
#define SENSOR_JMP_SELECT   7
#define SENSOR_ALTDJ        8
#define SENSOR_SERIES       9
#define SENSOR_INT_SERIES   10
#define TAPETE_ON           11
#define TAPETE_OFF          12
#define SAVE_CONFIGS        13

//EXPORTACAO MACHINE STATE
#define VERIFICA_COMM         1
#define EXPORTAR_UNITARIO     2
#define NUM_TESTE_EXPORT      3
#define PROCESS_UNITARIO      4
#define EXPORTAR_TODOS        5
#define PROCESS_TODOS         6

//APAGA DADOS MACHINE STATE
#define VERFICA_APAGAR      1
#define CONFIRMA_APAGAR     2
#define CONFIRMA            5
#define RET_MENU            2

//COMANDOS USU�?RIO
#define AVANCAR     'A'
#define CONFIRMAR   'C'
#define PARAR       'P'
#define MENU        'M'
#define INSERIR     'I'
#define AMOSTRA     ';'


//QUANTIDADE DE TESTES
#define TEST_SIZE   5
#define MEASUREMENT_SIZE   5

//READ FILE MATRIX
#define MAX_LINES 10
#define MAX_LEN 100

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/*Defines para validação
 *
 */
#define _VI	0
#define _HWVALIDATION	0
#define SAMPLES 10
#define _APPLICATION 1

/*
 * Defines da solução
 */

#define TRUE            1
#define FALSE           0

#define FORA 	'0'
#define DENTRO 	'1'
#define REPOUSO '2'
#define CONTATO '3'
#define VOO     '4'
#define TIMEOUT	'5'
#define MAX_SERIE '6'
#define INTERVALO '7'

#define SUBMENU_SIZE    15
#define MAINMENU_SIZE   4
#define HOME            1

//MENU MACHINE STATE
#define IDDLE           0
#define START_TEST      1
#define CONSULT_DATA    2
#define CONFIG_SENSOR   3
#define EXPORT_DATA     4
#define ERASE_DATA      5
#define TESTE           6


//INICIAR MACHINE STATE
#define COMM_OFF        1
#define COMM_ON         2
#define TEMPO_READ      3
#define MASSA_READ      4
#define SOBREC_READ     5
#define START           6
#define READING         7
#define STOP            8
#define DISP_RESULTS    9
#define RESULTS         10
#define SAVE_DATA       11
#define CANCEL_SAVE     12

//CONSULTA MACHINE STATE
#define CONSULTA_TESTE  1
#define RESULT_TESTE    2
#define EXPORTAR        3

//CONFIGURACAO MACHINE STATE
#define CONFIG_SENSOR_1     1
#define CONFIG_SENSOR_2     2
#define SENSOR_ALTMIN       3
#define SENSOR_ALTMAX       4
#define SENSOR_SALTOS       5
#define SENSOR_INT_SALTOS   6
#define SENSOR_JMP_SELECT   7
#define SENSOR_ALTDJ        8
#define SENSOR_SERIES       9
#define SENSOR_INT_SERIES   10
#define TAPETE_ON           11
#define TAPETE_OFF          12
#define SAVE_CONFIGS        13

//EXPORTACAO MACHINE STATE
#define VERIFICA_COMM         1
#define EXPORTAR_UNITARIO     2
#define NUM_TESTE_EXPORT      3
#define PROCESS_UNITARIO      4
#define EXPORTAR_TODOS        5
#define PROCESS_TODOS         6

//APAGA DADOS MACHINE STATE
#define VERFICA_APAGAR      1
#define CONFIRMA_APAGAR     2
#define CONFIRMA            5
#define RET_MENU            2

//COMANDOS USU�?RIO
#define AVANCAR     'A'
#define CONFIRMAR   'C'
#define PARAR       'P'
#define MENU        'M'
#define INSERIR     'I'
#define AMOSTRA     ';'


//QUANTIDADE DE TESTES
#define TEST_SIZE   5
#define MEASUREMENT_SIZE   5

//READ FILE MATRIX
#define MAX_LINES 10
#define MAX_LEN 100

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/*Defines para validação
 *
 */
#define _VI	0
#define _HWVALIDATION	0
#define SAMPLES 10
#define _APPLICATION 1

/*
 * Defines da solução
 */

#define TRUE            1
#define FALSE           0

#define FORA 	'0'
#define DENTRO 	'1'
#define REPOUSO '2'
#define CONTATO '3'
#define VOO     '4'
#define TIMEOUT	'5'
#define MAX_SERIE '6'
#define INTERVALO '7'

#define SUBMENU_SIZE    15
#define MAINMENU_SIZE   4
#define HOME            1

//MENU MACHINE STATE
#define IDDLE           0
#define START_TEST      1
#define CONSULT_DATA    2
#define CONFIG_SENSOR   3
#define EXPORT_DATA     4
#define ERASE_DATA      5
#define TESTE           6


//INICIAR MACHINE STATE
#define COMM_OFF        1
#define COMM_ON         2
#define TEMPO_READ      3
#define MASSA_READ      4
#define SOBREC_READ     5
#define START           6
#define READING         7
#define STOP            8
#define DISP_RESULTS    9
#define RESULTS         10
#define SAVE_DATA       11
#define CANCEL_SAVE     12

//CONSULTA MACHINE STATE
#define CONSULTA_TESTE  1
#define RESULT_TESTE    2
#define EXPORTAR        3

//CONFIGURACAO MACHINE STATE
#define CONFIG_SENSOR_1     1
#define CONFIG_SENSOR_2     2
#define SENSOR_ALTMIN       3
#define SENSOR_ALTMAX       4
#define SENSOR_SALTOS       5
#define SENSOR_INT_SALTOS   6
#define SENSOR_JMP_SELECT   7
#define SENSOR_ALTDJ        8
#define SENSOR_SERIES       9
#define SENSOR_INT_SERIES   10
#define TAPETE_ON           11
#define TAPETE_OFF          12
#define SAVE_CONFIGS        13

//EXPORTACAO MACHINE STATE
#define VERIFICA_COMM         1
#define EXPORTAR_UNITARIO     2
#define NUM_TESTE_EXPORT      3
#define PROCESS_UNITARIO      4
#define EXPORTAR_TODOS        5
#define PROCESS_TODOS         6

//APAGA DADOS MACHINE STATE
#define VERFICA_APAGAR      1
#define CONFIRMA_APAGAR     2
#define CONFIRMA            5
#define RET_MENU            2

//COMANDOS USU�?RIO
#define AVANCAR     'A'
#define CONFIRMAR   'C'
#define PARAR       'P'
#define MENU        'M'
#define INSERIR     'I'
#define AMOSTRA     ';'


//QUANTIDADE DE TESTES
#define TEST_SIZE   5
#define MEASUREMENT_SIZE   5

//READ FILE MATRIX
#define MAX_LINES 10
#define MAX_LEN 100

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/*Defines para validação
 *
 */
#define _VI	0
#define _HWVALIDATION	0
#define SAMPLES 10
#define _APPLICATION 1

/*
 * Defines da solução
 */

#define TRUE            1
#define FALSE           0

#define FORA 	'0'
#define DENTRO 	'1'
#define REPOUSO '2'
#define CONTATO '3'
#define VOO     '4'
#define TIMEOUT	'5'
#define MAX_SERIE '6'
#define INTERVALO '7'

#define SUBMENU_SIZE    15
#define MAINMENU_SIZE   4
#define HOME            1

//MENU MACHINE STATE
#define IDDLE           0
#define START_TEST      1
#define CONSULT_DATA    2
#define CONFIG_SENSOR   3
#define EXPORT_DATA     4
#define ERASE_DATA      5
#define TESTE           6


//INICIAR MACHINE STATE
#define COMM_OFF        1
#define COMM_ON         2
#define TEMPO_READ      3
#define MASSA_READ      4
#define SOBREC_READ     5
#define START           6
#define READING         7
#define STOP            8
#define DISP_RESULTS    9
#define RESULTS         10
#define SAVE_DATA       11
#define CANCEL_SAVE     12

//CONSULTA MACHINE STATE
#define CONSULTA_TESTE  1
#define RESULT_TESTE    2
#define EXPORTAR        3

//CONFIGURACAO MACHINE STATE
#define CONFIG_SENSOR_1     1
#define CONFIG_SENSOR_2     2
#define SENSOR_ALTMIN       3
#define SENSOR_ALTMAX       4
#define SENSOR_SALTOS       5
#define SENSOR_INT_SALTOS   6
#define SENSOR_JMP_SELECT   7
#define SENSOR_ALTDJ        8
#define SENSOR_SERIES       9
#define SENSOR_INT_SERIES   10
#define TAPETE_ON           11
#define TAPETE_OFF          12
#define SAVE_CONFIGS        13

//EXPORTACAO MACHINE STATE
#define VERIFICA_COMM         1
#define EXPORTAR_UNITARIO     2
#define NUM_TESTE_EXPORT      3
#define PROCESS_UNITARIO      4
#define EXPORTAR_TODOS        5
#define PROCESS_TODOS         6

//APAGA DADOS MACHINE STATE
#define VERFICA_APAGAR      1
#define CONFIRMA_APAGAR     2
#define CONFIRMA            5
#define RET_MENU            2

//COMANDOS USU�?RIO
#define AVANCAR     'A'
#define CONFIRMAR   'C'
#define PARAR       'P'
#define MENU        'M'
#define INSERIR     'I'
#define AMOSTRA     ';'


//QUANTIDADE DE TESTES
#define TEST_SIZE   5
#define MEASUREMENT_SIZE   5

//READ FILE MATRIX
#define MAX_LINES 10
#define MAX_LEN 100

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/*Defines para validação
 *
 */
#define _VI	0
#define _HWVALIDATION	0
#define SAMPLES 10
#define _APPLICATION 0

/*
 * Defines da solução
 */

#define TRUE            1
#define FALSE           0

#define FORA 	'0'
#define DENTRO 	'1'
#define REPOUSO '2'
#define CONTATO '3'
#define VOO     '4'
#define TIMEOUT	'5'
#define MAX_SERIE '6'
#define INTERVALO '7'

#define SUBMENU_SIZE    15
#define MAINMENU_SIZE   4
#define HOME            1

//MENU MACHINE STATE
#define IDDLE           0
#define START_TEST      1
#define CONSULT_DATA    2
#define CONFIG_SENSOR   3
#define EXPORT_DATA     4
#define ERASE_DATA      5
#define TESTE           6


//INICIAR MACHINE STATE
#define COMM_OFF        1
#define COMM_ON         2
#define TEMPO_READ      3
#define MASSA_READ      4
#define SOBREC_READ     5
#define START           6
#define READING         7
#define STOP            8
#define DISP_RESULTS    9
#define RESULTS         10
#define SAVE_DATA       11
#define CANCEL_SAVE     12

//CONSULTA MACHINE STATE
#define CONSULTA_TESTE  1
#define RESULT_TESTE    2
#define EXPORTAR        3

//CONFIGURACAO MACHINE STATE
#define CONFIG_SENSOR_1     1
#define CONFIG_SENSOR_2     2
#define SENSOR_ALTMIN       3
#define SENSOR_ALTMAX       4
#define SENSOR_SALTOS       5
#define SENSOR_INT_SALTOS   6
#define SENSOR_JMP_SELECT   7
#define SENSOR_ALTDJ        8
#define SENSOR_SERIES       9
#define SENSOR_INT_SERIES   10
#define TAPETE_ON           11
#define TAPETE_OFF          12
#define SAVE_CONFIGS        13

//EXPORTACAO MACHINE STATE
#define VERIFICA_COMM         1
#define EXPORTAR_UNITARIO     2
#define NUM_TESTE_EXPORT      3
#define PROCESS_UNITARIO      4
#define EXPORTAR_TODOS        5
#define PROCESS_TODOS         6

//APAGA DADOS MACHINE STATE
#define VERFICA_APAGAR      1
#define CONFIRMA_APAGAR     2
#define CONFIRMA            5
#define RET_MENU            2

//COMANDOS USU�?RIO
#define AVANCAR     'A'
#define CONFIRMAR   'C'
#define PARAR       'P'
#define MENU        'M'
#define INSERIR     'I'
#define AMOSTRA     ';'


//QUANTIDADE DE TESTES
#define TEST_SIZE   5
#define MEASUREMENT_SIZE   5

//READ FILE MATRIX
#define MAX_LINES 10
#define MAX_LEN 100

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/*Defines para validação
 *
 */
#define _VI	0
#define _HWVALIDATION	0
#define SAMPLES 10
#define _APPLICATION 0

/*
 * Defines da solução
 */

#define TRUE            1
#define FALSE           0

#define FORA 	'0'
#define DENTRO 	'1'
#define REPOUSO '2'
#define CONTATO '3'
#define VOO     '4'
#define TIMEOUT	'5'
#define MAX_SERIE '6'
#define INTERVALO '7'
#define INTERVALO_SALTOS '8'

#define SUBMENU_SIZE    15
#define MAINMENU_SIZE   4
#define HOME            1

//MENU MACHINE STATE
#define IDDLE           0
#define START_TEST      1
#define CONSULT_DATA    2
#define CONFIG_SENSOR   3
#define EXPORT_DATA     4
#define ERASE_DATA      5
#define TESTE           6


//INICIAR MACHINE STATE
#define COMM_OFF        1
#define COMM_ON         2
#define TEMPO_READ      3
#define MASSA_READ      4
#define SOBREC_READ     5
#define START           6
#define READING         7
#define STOP            8
#define DISP_RESULTS    9
#define RESULTS         10
#define SAVE_DATA       11
#define CANCEL_SAVE     12

//CONSULTA MACHINE STATE
#define CONSULTA_TESTE  1
#define RESULT_TESTE    2
#define EXPORTAR        3

//CONFIGURACAO MACHINE STATE
#define CONFIG_SENSOR_1     1
#define CONFIG_SENSOR_2     2
#define SENSOR_ALTMIN       3
#define SENSOR_ALTMAX       4
#define SENSOR_SALTOS       5
#define SENSOR_INT_SALTOS   6
#define SENSOR_JMP_SELECT   7
#define SENSOR_ALTDJ        8
#define SENSOR_SERIES       9
#define SENSOR_INT_SERIES   10
#define TAPETE_ON           11
#define TAPETE_OFF          12
#define SAVE_CONFIGS        13

//EXPORTACAO MACHINE STATE
#define VERIFICA_COMM         1
#define EXPORTAR_UNITARIO     2
#define NUM_TESTE_EXPORT      3
#define PROCESS_UNITARIO      4
#define EXPORTAR_TODOS        5
#define PROCESS_TODOS         6

//APAGA DADOS MACHINE STATE
#define VERFICA_APAGAR      1
#define CONFIRMA_APAGAR     2
#define CONFIRMA            5
#define RET_MENU            2

//COMANDOS USU�?RIO
#define AVANCAR     'A'
#define CONFIRMAR   'C'
#define PARAR       'P'
#define MENU        'M'
#define INSERIR     'I'
#define DOWN     	'B'
#define LEFT     	'D'
#define RIGHT		'E'


//QUANTIDADE DE TESTES
#define TEST_SIZE   5
#define MEASUREMENT_SIZE   5

//READ FILE MATRIX
#define MAX_LINES 10
#define MAX_LEN 100

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */


/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */


/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */


/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define BT_DOWN_Pin GPIO_PIN_0
#define BT_DOWN_GPIO_Port GPIOB
#define BT_DOWN_EXTI_IRQn EXTI0_IRQn
#define BT_LEFT_Pin GPIO_PIN_1
#define BT_LEFT_GPIO_Port GPIOB
#define BT_LEFT_EXTI_IRQn EXTI1_IRQn
#define BT__RIGHT_Pin GPIO_PIN_2
#define BT__RIGHT_GPIO_Port GPIOB
#define BT__RIGHT_EXTI_IRQn EXTI2_IRQn
#define LCD_D7_Pin GPIO_PIN_12
#define LCD_D7_GPIO_Port GPIOB
#define LCD_D6_Pin GPIO_PIN_13
#define LCD_D6_GPIO_Port GPIOB
#define LCD_D5_Pin GPIO_PIN_14
#define LCD_D5_GPIO_Port GPIOB
#define LCD_D4_Pin GPIO_PIN_15
#define LCD_D4_GPIO_Port GPIOB
#define LCD_D3_Pin GPIO_PIN_8
#define LCD_D3_GPIO_Port GPIOA
#define LCD_D2_Pin GPIO_PIN_9
#define LCD_D2_GPIO_Port GPIOA
#define LCD_D1_Pin GPIO_PIN_10
#define LCD_D1_GPIO_Port GPIOA
#define LCD_D0_Pin GPIO_PIN_11
#define LCD_D0_GPIO_Port GPIOA
#define LCD_EN_Pin GPIO_PIN_12
#define LCD_EN_GPIO_Port GPIOA
#define LCD_RW_Pin GPIO_PIN_15
#define LCD_RW_GPIO_Port GPIOA
#define LCD_RS_Pin GPIO_PIN_3
#define LCD_RS_GPIO_Port GPIOB
#define BT_MENU_Pin GPIO_PIN_4
#define BT_MENU_GPIO_Port GPIOB
#define BT_MENU_EXTI_IRQn EXTI4_IRQn
#define BT_AVANCA_Pin GPIO_PIN_5
#define BT_AVANCA_GPIO_Port GPIOB
#define BT_AVANCA_EXTI_IRQn EXTI9_5_IRQn
#define BT_SELECT_Pin GPIO_PIN_6
#define BT_SELECT_GPIO_Port GPIOB
#define BT_SELECT_EXTI_IRQn EXTI9_5_IRQn
#define BT_STOP_Pin GPIO_PIN_7
#define BT_STOP_GPIO_Port GPIOB
#define BT_STOP_EXTI_IRQn EXTI9_5_IRQn
#define BT_INSERT_Pin GPIO_PIN_8
#define BT_INSERT_GPIO_Port GPIOB
#define BT_INSERT_EXTI_IRQn EXTI9_5_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
