#ifndef DisplayMessage_H_INCLUDED
#define DisplayMessage_H_INCLUDED

#define USERMSG1  0
#define USERMSG2  1
#define INSERTMSG 2
#define OPTIONMSG 3

//MENSAGEM DE BOAS VINDAS
extern unsigned char* appNameMsg;
extern unsigned char* companyNameMsg;
extern unsigned char* appVersionMsg;
//

//SUBMENU INICIAR
extern unsigned char* startUserMsg;
extern unsigned char* noTransmissionMsg;
extern unsigned char* yesTransmissionMsg;
extern unsigned char* waitTransmissionMsg;

extern unsigned char* timeUserMsg;
extern unsigned char* massUserMsg;
extern unsigned char* overmassUserMsg;

extern unsigned char* startreadUserMsg;
extern unsigned char* stopreadUserMsg;
extern unsigned char* medindoUserMsg;

extern unsigned char* resultsUserMsg;
extern unsigned char* amostraUserMsg;
extern unsigned char* alturaSaltoUserMsg;
extern unsigned char* potenciaUserMsg;
extern unsigned char* tempoVooUserMsg;
extern unsigned char* tempoSoloUserMsg;
extern unsigned char* potenciaUserMsg;
extern unsigned char* saveUserMsg;
extern unsigned char* savedUserMsg;
extern unsigned char* cancelUserMsg;
extern unsigned char* canceledUserMsg;

//SUBMENU CONSULTA
extern unsigned char* consultUserMsg;
extern unsigned char* consultTestUserMsg;
//VERIFICAR COMO COLOCAR OS PARAMETROS LIDOS
extern unsigned char* consultExportUserMsg;
extern unsigned char* exportedUserMsg; //aplicado para SUBMENU CONSULTA E EXPORTAR
//

//SUBMENU CONFIG
extern unsigned char* configUserMsg;
extern unsigned char* sensor1UserMsg;
extern unsigned char* sensor2UserMsg;
extern unsigned char* altminUserMsg;
extern unsigned char* altmaxUserMsg;
extern unsigned char* numsaltosUserMsg;
extern unsigned char* intersaltosUserMsg;
extern unsigned char* tiposaltoUserMsg;
extern unsigned char* altdjUserMsg;
extern unsigned char* numserieUserMsg;
extern unsigned char* interseriesUserMsg;
extern unsigned char* intapeteUserMsg;
extern unsigned char* outtapeteUserMsg;
//

//SUBMENU EXPORTACAO
extern unsigned char* exportUserMsg;
//MSG 4 DO SUBMENU INICIAR
extern unsigned char* exportunitUserMsg;
extern unsigned char* testunitUserMsg;
//MSG 2 DO SUBMENU CONSULTA
extern unsigned char* exportallUserMsg;
//MSG 4 DO SUBMENU CONSULTA

//SUBMENU APAGAR
extern unsigned char* eraseUserMsg;
extern unsigned char* eraseselectUserMsg;
extern unsigned char* erasingUserMsg;
extern unsigned char* erasedUserMsg;

extern unsigned char* testMsg;

extern unsigned char* avancarUserMsg;
extern unsigned char* inserirUserMsg;
extern unsigned char* menuUserMsg;
extern unsigned char* selecionarUserMsg;
extern unsigned char* pararUserMsg;
extern unsigned char* pularUserMsg;





#endif // DisplayMessage_H_INCLUDED

