#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "EPD.hpp"

#define DEFAULT_WAIT 1*1000
#define LED PICO_DEFAULT_LED_PIN
#define POT_OUT
#define POT_IN
#define POT_ADC
#define LIGHT_OUT
#define LIGHT_IN
#define SCRN_PWR  12
#define SCRN_TX   19
#define SCRN_SCLK 18
#define SCRN_CS   17
#define SCRN_DC   20
#define SCRN_RST  21
#define SCRN_BUSY 22

typedef struct
{
	uint8_t  *image;
	uint16_t width;
	uint16_t height;
	uint8_t  color;
} PAINT;
PAINT paint;

void blink(uint8_t, uint32_t);
void EPD_pinInit(void);

void blink(uint8_t times, uint32_t wait)
{
	for(uint8_t i = 0; i < times; i++)
	{
		gpio_put(LED, 1);
		DEV_delay(wait);
		gpio_put(LED, 0);
		DEV_delay(wait);
	}
}

void EPD_pinInit(void)
{
	EPD_pins.scrn_pwr  = SCRN_PWR;
	EPD_pins.scrn_tx   = SCRN_TX;
	EPD_pins.scrn_sclk = SCRN_SCLK;
	EPD_pins.scrn_cs   = SCRN_CS;
	EPD_pins.scrn_dc   = SCRN_DC;
	EPD_pins.scrn_rst  = SCRN_RST;
	EPD_pins.scrn_busy = SCRN_BUSY;
}

int main()
{
	DEV_delay(3000);
	stdio_init_all();

	gpio_init(LED);
	gpio_set_dir(LED, GPIO_OUT);

	spi_init(spi_default, 1000*1000);
	gpio_set_function(SCRN_SCLK, GPIO_FUNC_SPI);
	gpio_set_function(SCRN_TX, GPIO_FUNC_SPI);
	gpio_set_function(SCRN_CS, GPIO_FUNC_SPI);
	gpio_init(SCRN_PWR);
	gpio_init(SCRN_DC);
	gpio_init(SCRN_RST);
	gpio_init(SCRN_BUSY);
	gpio_set_dir(SCRN_PWR, GPIO_OUT);
	gpio_set_dir(SCRN_DC, GPIO_OUT);
	gpio_set_dir(SCRN_RST, GPIO_OUT);
	gpio_set_dir(SCRN_BUSY, GPIO_OUT);
	EPD_pinInit();

	blink(3, 500);
	printf("Starting board\n");

	while (true) {
		blink(5, 200);
		printf("waiting\n");
		sleep_ms(3000);
	}
}