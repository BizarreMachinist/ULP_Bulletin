#include "DEV.hpp"

uint8_t DEV_read(uint8_t pin)
{
	#if DRYRUN || DEBUG
	printf("DEV_read, pin = %u\n", pin);
	#endif

	#if !DRYRUN
	return gpio_get(pin);
	#else
	return 0;
	#endif

}

void DEV_write(uint8_t pin, uint8_t value)
{
	#if DRYRUN || DEBUG
	printf("DEV_write, pin = %u, value = %u\n", pin, value);
	#endif

	#if !DRYRUN
	gpio_put(pin, value);
	#else
	return;
	#endif
}

void DEV_spiWrite(const uint8_t* data)
{
	#if DRYRUN || DEBUG
	printf("DEV_spiWrite, data (addr) = %p, data (val) = %X\n", data, *data);
	#endif

	#if !DRYRUN
	spi_write_blocking(spi_default, data, 1);
	#else
	return;
	#endif
}

void DEV_delay(uint32_t wait)
{
	// #if DRYRUN || DEBUG
	// printf("DEV_delay, wait = %u\n", wait);
	// #endif

	// #if !DRYRUN
	sleep_ms(wait);
	// #else
	// return;
	// #endif
}