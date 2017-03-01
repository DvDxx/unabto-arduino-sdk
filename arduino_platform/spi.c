#define NABTO_LOG_MODULE_CURRENT NABTO_LOG_MODULE_PERIPHERAL

#include "spi.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void spi_initialize()
{
    // set SS as high SS is located on PB2
    DDRMOSI |= _BV(PINMOSI);
    PORTMOSI |= _BV(PINMOSI);

    // set MISO as input
    DDRMISO &= ~(_BV(PINMISO));

    
    PORT_ETHERNET_SS |= _BV(PIN_ETHERNET_SS);
    DDR_ETHERNET_SS |= _BV(PIN_ETHERNET_SS);

    // set board
#if defined(DDR_CHIP_SS)
    DDR_CHIP_SS |= _BV(PIN_CHIP_SS);
    PORT_CHIP_SS |= _BV(PIN_CHIP_SS);
#endif
    
    // Warning: if the SS pin ever becomes a LOW INPUT then SPI
    // automatically switches to Slave, so the data direction of the
    // SS pin MUST be kept as OUTPUT. On mega boards the SS output is
    // different from the actually used SS pin
    SPCR = 0;
    SPCR |= _BV(SPE);
    SPCR |= _BV(MSTR);
//    SPCR |= _BV(SPR0);

    // Set direction register for SCK and MOSI pin.
    // set SCK and MOSI as outputs.
    DDRSCK |= _BV(PINSCK);
    DDRMOSI |= _BV(PINMOSI);
}

uint8_t spi_transfer(uint8_t value)
{
    SPDR = value;
    while (!(SPSR & _BV(SPIF)));
    return SPDR;
}

void spi_transfer_buffer(uint8_t* buffer, uint16_t length)
{
    while(length > 0)
    {
        SPDR = *buffer;
        while (!(SPSR & _BV(SPIF))) { }
        *buffer = SPDR;
        buffer++;
        length--;
    }
}
