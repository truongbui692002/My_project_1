#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "main.h"
#include "usart.h"

#define UART_DEBUG  &huart1

#define DEBUG   1
#define PLOT    0

void Debug_Init(void);

void debug_callback(void);

void logPC(const char *fmt, ...);


// void log(char* message);

#endif /*_DEBUG_H_*/