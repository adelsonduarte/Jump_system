#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define TRUE            1
#define FALSE           0

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

//COMANDOS USUÁRIO
#define AVANCAR     'A'
#define CONFIRMAR   'C'
#define PARAR       'P'
#define MENU        'M'
#define INSERIR     'I'
#define AMOSTRA     ';'


//QUANTIDADE DE TESTES
#define TEST_SIZE   5
#define MEASUREMENT_SIZE   5


#endif // MAIN_H_INCLUDED
