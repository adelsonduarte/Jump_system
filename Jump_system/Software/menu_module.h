#ifndef MENU_MODULE_H_INCLUDED
#define MENU_MODULE_H_INCLUDED

struct Menu;
unsigned char getNextMain(unsigned char nextState);
unsigned char setSelectMain(unsigned char *selectedState);
unsigned char getDisplayMain(unsigned char *data);
unsigned char getStateMain(unsigned char *currentState);
unsigned char setStateMain(unsigned char *currentState);

#endif // MENU_MODULE_H_INCLUDED
