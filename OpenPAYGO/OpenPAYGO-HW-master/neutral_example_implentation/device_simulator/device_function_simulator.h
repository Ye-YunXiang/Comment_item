#ifndef device_function_simulator_h
#define device_function_simulator_h

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

#define STAR_KEY -1
#define HASH_KEY -2

// Device parameters (to be stored in Flash/EEPROM)
extern uint16_t TokenCount;
extern bool PAYGEnabled;
extern uint32_t ActiveUntil;
extern uint32_t TokenEntryLockedUntil;
extern char SECRET_KEY[16];
extern uint32_t StartingCode;

void BlinkRedLED(int NumberOfBlinks);
void BlinkGreenLED(int NumberOfBlinks);
int GetKeyPressed(void);
void LoadActivationVariables(void);
void StoreActivationVariables(void);
uint32_t  GetTimeInSeconds(void);

#endif
