#pragma once

#include <stdio.h>

void uart_putchar(char c, FILE *stream);

#define NABTO_LOG_BASIC_PRINT(level, cmsg) do { printf cmsg; printf("\n"); } while (0)

#define NABTO_FATAL_EXIT

#include <modules/network/w5100/w5100_network.h>

typedef w5100_socket unabto_socket_t;

#define nabto_init_socket w5100_nabto_init_socket
#define nabto_close_socket w5100_nabto_close_socket
#define nabto_read w5100_nabto_read
#define nabto_write w5100_nabto_write


void platform_init(void);

void uart_init(void);

#if defined(UNO)
#  ifndef DDRMOSI
#    define DDRMOSI DDRB
#  endif
#  ifndef PORTMOSI
#    define PORTMOSI PORTB
#  endif
#  ifndef PINMOSI
#    define PINMOSI PORTB3
#  endif
#  ifndef DDRSCK
#    define DDRSCK DDRB
#  endif
#  ifndef PINSCK
#    define PINSCK PORTB5
#  endif
#  ifndef DDRMISO
#    define DDRMISO DDRB
#  endif
#  ifndef PORTMISO
#    define PORTMISO PORTB
#  endif
#  ifndef PINMISO
#    define PINMISO PORTB4
#  endif
#  define DDR_ETHERNET_SS DDRB
#  define PORT_ETHERNET_SS PORTB
#  define PIN_ETHERNET_SS PORTB2
#  define DDR_SD_SS DDRD
#  define PORT_SD_SS PORTD
#  define PIN_SD_SS PORTD4
#elif defined(MEGA)
#  ifndef DDRMOSI
#    define DDRMOSI DDRB
#  endif
#  ifndef PORTMOSI
#    define PORTMOSI PORTB
#  endif
#  ifndef PINMOSI
#    define PINMOSI PORTB2
#  endif
#  ifndef DDRSCK
#    define DDRSCK DDRB
#  endif
#  ifndef PINSCK
#    define PINSCK PORTB1
#  endif
#  ifndef DDRMISO
#    define DDRMISO DDRB
#  endif
#  ifndef PORTMISO
#    define PORTMISO PORTB
#  endif
#  ifndef PINMISO
#    define PINMISO PORTB3
#  endif
#  define DDR_ETHERNET_SS DDRB
#  define PORT_ETHERNET_SS PORTB 
#  define PIN_ETHERNET_SS PORTB4
#  define DDR_SD_SS DDRG
#  define PORT_SD_SS PORTG
#  define PIN_SD_SS PORTG5
#  define DDR_CHIP_SS DDRB
#  define PIN_CHIP_SS PORTB0
#  define PORT_CHIP_SS PORTB
#else
#  error missing board
#endif
