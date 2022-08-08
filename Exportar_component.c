#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "Exportar_component.h"
#include "SubMenu.h"

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
    unsigned char userSelectSensorChannel;
};
struct Menu{
        unsigned char menuNext;
        unsigned char menuSelect;
        unsigned char menuDisplay;
        unsigned char menuState;
        struct dataInsert menuInsert;
    };

//toda maquina de estado deve ter um loop - > LEMBRAR LABVIEW
unsigned char exportStateMachine(struct Menu* subMenu)
{
    struct Menu* subMenuExport = subMenu;
    unsigned char key = 0;
    while(key != MENU)
    {
        switch(subMenuExport->menuState)
        {
            case IDDLE:
                subMenuExport->menuState = getNextSub(VERIFICA_COMM);
            break;

            case VERIFICA_COMM:
                //funcao para habilitar comunicacao
                printf("Resultado da funcao para habilitar comunicacao\n");
                printf("Pareando...\n");
                subMenuExport->menuState = getNextSub(EXPORTAR_UNITARIO);
            break;

            case EXPORTAR_UNITARIO:
                printf("EXPORTAR_UNITARIO\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR) subMenuExport->menuState = getNextSub(EXPORTAR_TODOS);
                else if(key == CONFIRMAR)
                {
                    subMenuExport->menuSelect = setSelectSub(&subMenuExport->menuState);
                    subMenuExport->menuState = getNextSub(NUM_TESTE_EXPORT);
                }
                break;

            case EXPORTAR_TODOS:
                printf("EXPORTAR_TODOS\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR) subMenuExport->menuState = getNextSub(EXPORTAR_UNITARIO);
                else if(key == CONFIRMAR)
                {
                    subMenuExport->menuSelect = setSelectSub(&subMenuExport->menuState);
                    subMenuExport->menuState = getNextSub(EXPORTAR_PROC);
                }
                break;


            case NUM_TESTE_EXPORT:
                printf("NUM_TESTE_EXPORT: %d\n",subMenuExport->menuInsert.userConsultTest);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    subMenuExport->menuInsert.userConsultTest++;
                    subMenuExport->menuState = getNextSub(NUM_TESTE_EXPORT);
                }
                else if(key == CONFIRMAR)
                {
                    printf("NUM_TESTE_EXPORT: %d\n",subMenuExport->menuInsert.userConsultTest);
                    subMenuExport->menuState = getNextSub(EXPORTAR_PROC);
                    subMenuExport->menuSelect = setSelectSub(&subMenuExport->menuState);
                }

                break;



                case EXPORTAR_PROC:
                printf("EXPORTANDO\n");
                subMenuExport->menuState = getNextSub(IDDLE);
                key = MENU; // ta errado mas coloquei aqui pra teste
                if(subMenuExport->menuState == EXPORTAR_TODOS)
                {
                    printf("Exporta TODOS\n");
                    //Acessa os dados referente ao Teste e envia todos por BT
                }
                else if(subMenuExport->menuState == EXPORTAR_UNITARIO)
                {
                    printf("Exporta unitario\n");
                    //Acessa os dados referente ao Teste e envia apenas o selecionado por BT
                }
                break;
        }
    }
}
