#include <unabto/unabto_external_environment.h>
#include "unabto_platform.h"
#include "arduino_time.h"
#include <avr/io.h>
#include <stdio.h>
#include "spi.h"

#include <modules/network/dhcp/dhcp_client.h>

#include <device_drivers/w5100/w5100_platform.h>

dhcp_client_information dhcpClientInformation;

void platform_init(void)
{
    spi_initialize();
    uart_init();
    arduino_timer1_setup();

    // disable ethernet module sd card by setting pin4 high.
    
    DDR_SD_SS |= _BV(PIN_SD_SS);
    PORT_SD_SS |= _BV(PIN_SD_SS);
}

nabto_stamp_diff_t nabtoStampDiff(nabto_stamp_t * newest, nabto_stamp_t *oldest)
{
    return *newest - *oldest;
}


int nabtoStampDiff2ms(nabto_stamp_diff_t diff)
{
    return diff;
}

void nabto_random(uint8_t* data, size_t size)
{
    
}


void w5100_spi_transfer_buffer(uint8_t* data, uint16_t size)
{
    // set pin low
    PORT_ETHERNET_SS &= ~(_BV(PIN_ETHERNET_SS));

    spi_transfer_buffer(data, size);

    // set pin high
    PORT_ETHERNET_SS |= _BV(PIN_ETHERNET_SS);
}

void w5100_init_chip_select_pin()
{
    PORT_ETHERNET_SS |= _BV(PIN_ETHERNET_SS);
    DDR_ETHERNET_SS |= _BV(PIN_ETHERNET_SS);
}

void w5100_reset_chip_select() {
    
}

void uart_putchar(char c, FILE *stream) {
    if (c == '\n') {
        uart_putchar('\r', stream);
    }
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}

static FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void uart_init(void) {
#undef BAUD  // avoid compiler warning
#define BAUD 115200
#include <util/setbaud.h>
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */

    stdout = &uart_output;
    printf("foo\n");
}

