#ifndef _SPI_H_
#define _SPI_H_

#include <unabto/unabto_env_base.h>

#ifdef __cplusplus
extern "C" {
#endif

void spi_initialize();
uint8_t spi_transfer(uint8_t value);
void spi_transfer_buffer(uint8_t* buffer, uint16_t length);

#ifdef __cplusplus
} //extern "C"
#endif

#endif
