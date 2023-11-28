#define DRYRUN 1
#define DEBUG  0

#include <stdint.h>
#if DRYRUN || DEBUG
#include <stdio.h>
#endif
#include "pico/stdlib.h"
#include "hardware/spi.h"

uint8_t DEV_read(uint8_t);
void    DEV_write(uint8_t, uint8_t);
void    DEV_spiWrite(const uint8_t*);
void    DEV_delay(uint32_t);