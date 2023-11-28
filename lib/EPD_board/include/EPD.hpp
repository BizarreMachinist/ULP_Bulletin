#define DRYRUN     1
#define DEBUG      0

#include <stdint.h>
#if DRYRUN || DEBUG
#include <stdio.h>
#endif
#include "DEV.hpp"

#define WHITE      0xFF
#define BLACK      0x00
#define EPD_WIDTH  104
#define EPD_HEIGHT 212

typedef struct
{
	uint8_t scrn_pwr  = 255;
	uint8_t scrn_tx   = 255;
	uint8_t scrn_sclk = 255;
	uint8_t scrn_cs   = 255;
	uint8_t scrn_dc   = 255;
	uint8_t scrn_rst  = 255;
	uint8_t scrn_busy = 255;
} EPD_PINS;
EPD_PINS EPD_pins;

uint8_t EPD_pinCheck(void);
void    EPD_init(void);
void    EPD_reset(void);
void    EPD_sendCommand(const uint8_t*);
void    EPD_sendData(const uint8_t*);
void    EPD_readBusy(void);
void    EPD_turnOnDisplay(void);
void    EPD_clear(void);
void    EPD_display(const uint8_t*, const uint8_t*);
void    EPD_sleep(void);
void    EPD_exit(void);

#if DRYRUN || DEBUG
void EPD_pinsDump(void);
#endif