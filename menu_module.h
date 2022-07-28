#ifndef MENU_MODULE_H_INCLUDED
#define MENU_MODULE_H_INCLUDED
struct menuStruct
{
    unsigned char menuMainSelect;
    unsigned char menuSubSelect;
};

unsigned char menuStateMachine();

#endif // MENU_MODULE_H_INCLUDED
