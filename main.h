#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

extern unsigned char key;
extern unsigned char* ptr_key;
#define TRUE            1
#define FALSE           0

//MENU MACHINE STATE
#define IDDLE           0
#define START_TEST      1
#define CONSULT_DATA    2
#define CONFIG_SENSOR   3
#define EXPORT_DATA     4
#define ERASE_DATA      5


//INICIAR MACHINE STATE
#define COMMCONFIG      11
#define PARAMCONFIG     12
#define USERCONFIG      13
#define READ            14
#define STOP            15
#define RESULTS         16
#define SAVE_DATA       17

#define COMM_ON         111
#define COMM_OFF        112

#define TEMPO           121
#define MASSA           122
#define SOBRECARGA      123

#define START           131
#define READING         132


//COMANDOS USUÁRIO
#define AVANCAR     'A'
#define CONFIRMAR   'C'
#define PARAR       'P'
#define MENU        'M'
#define INSERIR     'I'


#endif // MAIN_H_INCLUDED
