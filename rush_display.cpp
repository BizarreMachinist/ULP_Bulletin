#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

#define DELAY 250
#define LED_PIN 25

#define DEFAULT_WAIT 1*1000
#define POT_OUT
#define POT_IN
#define POT_ADC
#define LIGHT_OUT
#define LIGHT_IN
#define SCRN_PWR
#define SCRN_TX
#define SCRN_SCLK
#define SCRN_CS
#define SCRN_DC
#define SCRN_RST
#define SCRN_BUSY
#define GPIO_FUNC_SPI 1
#define EPD_WIDTH 104
#define EPD_HEIGHT 212
#define WHITE 0xFF
#define BLACK 0x00

typedef struct
{
	uint8_t *image;
	uint16_t width;
	uint16_t height;
	uint16_t color;
	uint16_t rotate;
	uint16_t mirror;
} PAINT;
PAINT paint;

int main()
{
	bi_decl(bi_program_description("This is a test binary"));
	bi_decl(bi_1pin_with_name(LED_PIN, "on board led"));

	stdio_init_all();

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	while(1)
	{
		gpio_put(LED_PIN, 0);
		sleep_ms(DELAY);
		gpio_put(LED_PIN, 1);
		sleep_ms(DELAY);
		puts("hello world\n");
		sleep_ms(DELAY);
	}
}