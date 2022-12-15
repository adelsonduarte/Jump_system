#ifndef HIL_INTERFACE_H_INCLUDED
#define HIL_INTERFACE_H_INCLUDED

unsigned int HIL();
void processApplication();
void measureValidation();
unsigned char SAVE_ARRAY(uint16_t* saveString, unsigned char* nameString);

#endif // HIL_INTERFACE_H_INCLUDED
