#ifndef HIL_INTERFACE_H_INCLUDED
#define HIL_INTERFACE_H_INCLUDED

#define FORA 	'0'
#define DENTRO 	'1'
#define REPOUSO '2'
#define CONTATO '3'
#define VOO     '4'

#define AVANCAR     'A'
#define CONFIRMAR   'C'
#define PARAR       'P'
#define MENU        'M'
#define INSERIR     'I'
#define AMOSTRA     ';'

unsigned int HIL();
void processApplication();
void measureValidation();
unsigned char SAVE_ARRAY(uint16_t* saveString, unsigned char* nameString);

#endif // HIL_INTERFACE_H_INCLUDED
