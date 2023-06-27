#include "debug.h"
#include "stdio.h"
#include "stdbool.h"
#include <errno.h>
#include <sys/unistd.h>
#include <stdarg.h>
#include <string.h>

static uint8_t rx_debug = 0;
bool isNaize = false;

void Debug_Init(void)
{
    HAL_UART_Receive_IT(UART_DEBUG, &rx_debug, 1);
}

void debug_callback(void)
{
    if(rx_debug == '^')
    {
        HAL_NVIC_SystemReset();
    }
    else if (rx_debug == 'F')
    {
        isNaize = !isNaize;
    }
    HAL_UART_Receive_IT(UART_DEBUG, &rx_debug, 1);
}

#if DEBUG ==1
void vprint(const char *fmt, va_list argp)
{
    char string[200];
    if(0 < vsprintf(string, fmt, argp)) // build string
    {
        HAL_UART_Transmit(UART_DEBUG, (uint8_t*)string, strlen(string), 100); // send message via UART
    }
}

/**
    * @brief custom printf() function
    * 
    * @param fmt
    * @param ...
*/
void logPC(const char *fmt, ...)
{
    va_list argp;
    va_start(argp, fmt);
    vprint(fmt, argp);
    va_end(argp);
}
#else
void logPC(const char *fmt, ...)
{
    UNUSED(fmt);
}
#endif