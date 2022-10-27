#include "DisplayMessages.h"

/*LAYOUT DISPLAY

0----------------16
|				  |    USERMSG1
|				  |	   USERMSG2 (CASO PRECISE)
|				  |	   INSERTMSG
|  				  |	   OPTIONMSG
3----------------16
*/



// O CORRETO AQUI É FAZER UMA FUNÇÃO QUE RETORNE CADA UMA DAS MSGS. FAZER DEPOIS.
//MENSAGEM DE BOAS VINDAS
unsigned char* appNameMsg = "Jump System NG";
unsigned char* companyNameMsg = "CEFISE";
unsigned char* appVersionMsg = "Versao 0.1 2.1";
//

//SUBMENU INICIAR
unsigned char* startUserMsg  = "INICIAR TESTE"; //13
unsigned char* noTransmissionMsg = "TRANSMISSAO OFF"; //15
unsigned char* yesTransmissionMsg = "TRANSMISSAO ON"; //14
unsigned char* waitTransmissionMsg = "PAREANDO"; //8

unsigned char* timeUserMsg = "TEMPO (HH:MM:SS)"; //17
unsigned char* massUserMsg = "MASSA CORPORAL"; //14
unsigned char* overmassUserMsg = "SOBRECARGA"; //10

unsigned char* startreadUserMsg = "INICIAR MEDIDA"; //15
unsigned char* medindoUserMsg = "MEDINDO...";
unsigned char* stopreadUserMsg = "PARAR MEDIDA";//12

unsigned char* amostraUserMsg = "AMOSTRA:";
unsigned char* tempoVooUserMsg = "Tvoo:";
unsigned char* tempoSoloUserMsg = "Tsolo:";
unsigned char* potenciaUserMsg = "Pot.:";

unsigned char* resultsUserMsg = "VER RESULTADOS?"; //16
unsigned char* showResults = "SALTO"; //5
unsigned char* saveUserMsg = "SALVAR DADOS?";//13
unsigned char* savedUserMsg = "SALVANDO...";//11
unsigned char* cancelUserMsg = "CANCELAR?";//9
unsigned char* canceledUserMsg = "CANCELANDO";//11

//SUBMENU CONSULTA
unsigned char* consultUserMsg = "CONSULTAR TESTES";//16
unsigned char* consultTestUserMsg = "N TESTE";//7
//VERIFICAR COMO COLOCAR OS PARAMETROS LIDOS
unsigned char* consultExportUserMsg = "EXPORTAR TESTES";//16
unsigned char* exportedUserMsg = "EXPORTANDO"; //10
//

//SUBMENU CONFIG
unsigned char* configUserMsg = "CONFIGURACAO";//12
unsigned char* sensor1UserMsg = "SENSOR 1";//8
unsigned char* sensor2UserMsg = "SENSOR 2";//8
unsigned char* altminUserMsg = "ALT. MIN.:";//14
unsigned char* altmaxUserMsg = "ALT. MAX.:";//14
unsigned char* numsaltosUserMsg = "NUM. SALTOS:";//16
unsigned char* intersaltosUserMsg = "INTERV. SALTOS:";//13
unsigned char* tiposaltoUserMsg = "CMJ=1 SJ=2 DJ=3";//15
unsigned char* altdjUserMsg = "ALT. DJ:";//9
unsigned char* numserieUserMsg = "NUM. SERIES:";//16
unsigned char* interseriesUserMsg = "INTERV. SERIES";//16
unsigned char* intapeteUserMsg = "TAPETE ON";//9
unsigned char* outtapeteUserMsg = "TAPETE OFF";//10
//

//SUBMENU EXPORTACAO
unsigned char* exportUserMsg = "EXPORTACAO";//19
//MSG 4 DO SUBMENU INICIAR
unsigned char* exportunitUserMsg = "SEL. LEITURA";//18
//MSG 2 DO SUBMENU CONSULTA
unsigned char* exportallUserMsg = "EXPORTAR TODAS";//14
//MSG 4 DO SUBMENU CONSULTA

//SUBMENU APAGAR
unsigned char* eraseUserMsg = "APAGAR DADOS";//12
unsigned char* eraseselectUserMsg = "(5) CONFIRMA (2) VOLTA";//20
unsigned char* erasingUserMsg = "APAGANDO";//8
unsigned char* erasedUserMsg = "DADOS APAGADOS";//14

//OPCOES
unsigned char* avancarUserMsg = "(A)vanc."; //9
unsigned char* inserirUserMsg = "(I)nser."; //9
unsigned char* menuUserMsg = "(M)enu"; //6
unsigned char* selecionarUserMsg = "(C)onf.";//11
unsigned char* pararUserMsg = "(P)arar";//7
unsigned char* pularUserMsg = "(P)ular";

//(A)vanç.(I)nser.
//(C)onf.

