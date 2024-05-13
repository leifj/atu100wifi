#ifndef _VDISP_H
#define _VDISP_H
#include <Arduino.h>

#define LCD_ADDRESS 0x27
#define LCD_LENGTH 80
#define DDRAM 0
#define CGRAM 1
#define PUBLISH_THRESHOLD 100

extern bool dirty;
extern unsigned long cleanTime;
extern bool published;

extern char ddram[LCD_LENGTH];
extern bool ramIndex;
extern uint8_t currentAddress;
extern bool entryModeIncrement;
extern bool entryModeShift;
extern bool nibbleIndex;
extern uint8_t loNibble;
extern uint8_t hiNibble;

void onReceive(int);
void handleCommand(bool, bool, uint8_t);
void clearDisplay();
void cursorHome();
void setEntryMode(bool, bool);
void setOnOff(bool, bool, bool);
void setShift(bool, bool);
void setFunction(bool, bool, bool);
void setCGAddress(uint8_t);
void setDDAddress(uint8_t);
void writeData(char);


#endif