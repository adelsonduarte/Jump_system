#ifndef SUBMENU_H_INCLUDED
#define SUBMENU_H_INCLUDED
struct results;
struct Menu;
struct dataInsert;
unsigned char getNextSub(unsigned char nextState);
unsigned char setSelectSub(unsigned char *selectedState);
unsigned char setInsertData(struct dataInsert* dataToInsert);
unsigned char getInsertSub(struct dataInsert* dataToGet);
unsigned char getDisplaySub(unsigned char *data);
unsigned char getStateSub(unsigned char *currentState);
unsigned char setStateSub(unsigned char *currentState);


#endif // SUBMENU_H_INCLUDED
