#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "INICIAR_Component.h"

extern unsigned char botaoAvancar;
extern unsigned char botaoConfirmar;
extern unsigned char botaoParar;
extern unsigned char botaoMenu;
extern unsigned char botaoInserir;
//toda maquina de estado deve ter um loop - > LEMBRAR LABVIEW

unsigned char initStateMachine(unsigned char* currentMenuSub)
{
//    static unsigned char key = 0;
    *ptr_key = 0;
    unsigned char statusComm = COMM_OFF;
    *currentMenuSub = IDDLE;
    while(*ptr_key  != MENU)
    {
        switch(*currentMenuSub)
        {
            case IDDLE:
                *currentMenuSub = COMMCONFIG;
            break;

            case COMMCONFIG:
                statusComm = setCommunication();
                *currentMenuSub = USERCONFIG;
                printf("*ptr_key = %d\n",*ptr_key);
            break;

            case USERCONFIG:
                printf("USERCONFIG\n");
                setParameters();
                break;

            case READ:
                printf("READING\n");
                startReading();
                break;

            case STOP:
                break;

            case RESULTS:
                break;

            case SAVE_DATA:
            break;
        }
    }
    return START_TEST;
}

//colocar no BLUETOOTH.c
unsigned char setCommunication()
{
//    static unsigned char key = 0;
    *ptr_key = 0;
    unsigned char statusComm = COMM_OFF;
    unsigned char stateComm = COMM_OFF;

    while(*ptr_key != CONFIRMAR && *ptr_key !=MENU)
    {
        switch(stateComm)
        {
            case COMM_OFF:
                printf("Sem transmissao bluetooth\n");
                *ptr_key = getchar();
                while( getchar() != '\n' );
                if(*ptr_key == AVANCAR) stateComm = COMM_ON;
                else if(*ptr_key==CONFIRMAR) statusComm = COMM_OFF;
            break;

            case COMM_ON:
                printf("com transmissao bluetooth\n");
                *ptr_key = getchar();
                while( getchar() != '\n' );
                if(*ptr_key == AVANCAR) stateComm = COMM_OFF;
                else if(*ptr_key==CONFIRMAR) statusComm = COMM_ON;
                break;
        }
    }
    return statusComm;
}

//DATA.c
unsigned char setParameters()
{
//    unsigned char key = 0;
    *ptr_key = 0;
    unsigned char stateParameters = TEMPO;
    //MONTAR UMA ESTRUTURA DE PARAMETROS COM TEMPO, MASSA E SOBRECARGA
    //VERIFICAR NO CÓDIGO DO ENCODER
    unsigned char exemploStruct = 0; //APENAS PARA TESTE, VERIFICAR OS COMENTÁRIOS ACIMA

    while(*ptr_key != MENU)
    {
        switch(stateParameters)
        {
            case TEMPO:
                printf("setar tempo de leitura\n");
                *ptr_key = getchar();
                while( getchar() != '\n' );
                if(*ptr_key == INSERIR)
                {
                   printf("incrementa contador de tempo\n");
                   stateParameters = TEMPO;
                }
                else if(*ptr_key == CONFIRMAR)
                {
                    printf("Guarda o valor do tempo\n");
                    stateParameters = MASSA;
                }
            break;

            case MASSA:
                printf("Massa corporal\n");
                *ptr_key = getchar();
                while( getchar() != '\n' );
                if(*ptr_key == INSERIR)
                {
                   printf("incrementa contador de massa\n");
                   stateParameters = MASSA;
                }
                else if(*ptr_key == CONFIRMAR)
                {
                    printf("Guarda o valor do massa\n");
                    stateParameters = SOBRECARGA;
                }
            break;

            case SOBRECARGA:
                printf("Sobrecarga\n");
                *ptr_key = getchar();
                while( getchar() != '\n' );
                if(*ptr_key == INSERIR)
                {
                   printf("incrementa contador de sobrecarga\n");
                   stateParameters = SOBRECARGA;
                }
                else if(*ptr_key == CONFIRMAR)
                {
                    printf("Guarda o valor do sobrecarga\n");
                    stateParameters = IDDLE;
                }
            break;
        }
    }
    return exemploStruct;
}

unsigned char startReading()
{
//    unsigned char key = 0;
    *ptr_key = 0;
    while(*ptr_key != MENU)
    {
        printf("Aguardando confirmacao para iniciar leitura\n");
        *ptr_key = getchar();
        while( getchar() != '\n' );
        if(*ptr_key == CONFIRMAR)
        {
            printf("Leitura iniciada\n");
        }
    }
}









