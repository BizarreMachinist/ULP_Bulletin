#include "EPD.hpp"

uint8_t EPD_pinCheck(void)
{
	#if DRYRUN || DEBUG
	printf("EPD_pinCheck\n");
	#endif

	if(EPD_pins.scrn_pwr  == 255) return 1;
	if(EPD_pins.scrn_tx   == 255) return 2;
	if(EPD_pins.scrn_sclk == 255) return 3;
	if(EPD_pins.scrn_cs   == 255) return 4;
	if(EPD_pins.scrn_dc   == 255) return 5;
	if(EPD_pins.scrn_rst  == 255) return 6;
	if(EPD_pins.scrn_busy == 255) return 7;
	return 0;
}

void EPD_init(void)
{
	#if DRYRUN || DEBUG
	printf("EPD_init\n");
	#endif

	const uint8_t payload[] =
	{
		0x04,
		0x00, 0x0F, 0x89,
		0x61, 0x68, 0x00, 0xD4,
		0x50, 0x77
	};
	uint8_t payloadI = 0;

	EPD_reset();
	DEV_delay(10);
	EPD_readBusy();

	EPD_sendCommand(&payload[payloadI++]);
	EPD_readBusy();

	EPD_sendCommand(&payload[payloadI++]);
	EPD_sendData(&payload[payloadI++]);
	EPD_sendData(&payload[payloadI++]);

	EPD_sendCommand(&payload[payloadI++]);
	EPD_sendData(&payload[payloadI++]);
	EPD_sendData(&payload[payloadI++]);
	EPD_sendData(&payload[payloadI++]);

	EPD_sendCommand(&payload[payloadI++]);
	EPD_sendData(&payload[payloadI]);

	return;
}

void EPD_reset(void)
{
	#if DRYRUN || DEBUG
	printf("EPD_reset\n");
	#endif

	// DEV_write(SCRN_CS, 1);
	DEV_write(EPD_pins.scrn_rst, 1);
	DEV_delay(200);
	DEV_write(EPD_pins.scrn_rst, 0);
	DEV_delay(1);
	DEV_write(EPD_pins.scrn_rst, 1);
	DEV_delay(200);

	return;
}

void EPD_sendCommand(const uint8_t* reg)
{
	#if DRYRUN || DEBUG
	printf("EPD_sendCommand\n");
	#endif

	DEV_write(EPD_pins.scrn_dc, 0);
	DEV_write(EPD_pins.scrn_cs, 0);
	DEV_spiWrite(reg);
	DEV_write(EPD_pins.scrn_cs, 1);

	return;
}

void EPD_sendData(const uint8_t* data)
{
	#if DRYRUN || DEBUG
	printf("EPD_sendData\n");
	#endif

	DEV_write(EPD_pins.scrn_dc, 1);
	DEV_write(EPD_pins.scrn_cs, 0);
	DEV_spiWrite(data);
	DEV_write(EPD_pins.scrn_cs, 1);

	return;
}

void EPD_readBusy(void)
{
	#if DRYRUN || DEBUG
	printf("EPD_readBusy\n");
	#endif

	uint8_t busy = 1;

	do
	{
		DEV_delay(50);
		busy = DEV_read(EPD_pins.scrn_busy);
		busy =! (busy & 0x01);
	} while(busy);

	return;
}

void EPD_turnOnDisplay(void)
{
	#if DRYRUN || DEBUG
	printf("EPD_turnOnDisplay\n");
	#endif

	const uint8_t payload = 0x12;

	EPD_sendCommand(&payload);
	DEV_delay(100);
	EPD_readBusy();

	return;
}

void EPD_clear(void)
{
	#if DRYRUN || DEBUG
	printf("EPD_clear\n");
	#endif

	uint16_t width  = EPD_WIDTH / 8;
	uint16_t height = EPD_HEIGHT;
	const uint8_t payload[] = 
	{
		0x10, WHITE,
		0x13, WHITE
	};
	uint8_t payloadI = 0;


	EPD_sendCommand(&payload[payloadI++]);
	for(uint16_t j = 0; j < height; j++)
	{
		for(uint16_t i = 0; i < width; i++)
		{
			EPD_sendData(&payload[payloadI]);
		}
	}

	payloadI++;

	EPD_sendCommand(&payload[payloadI++]);
	for(uint16_t j = 0; j < height; j++)
	{
		for(uint16_t i = 0; i < width; i++)
		{
			EPD_sendData(&payload[payloadI]);
		}
	}

	EPD_turnOnDisplay();

	return;
}

void EPD_display(const uint8_t* blackImage, const uint8_t* redImage)
{
	#if DRYRUN || DEBUG
	printf("EPD_display\n");
	#endif

	uint16_t width  = EPD_WIDTH / 8;
	uint16_t height = EPD_HEIGHT;
	const uint8_t payload[] = 
	{
		0x10,
		0x13
	};
	uint8_t payloadI = 0;


	EPD_sendCommand(&payload[payloadI++]);
	for(uint16_t j = 0; j < height; j++)
	{
		for(uint16_t i = 0; i < width; i++)
		{
			EPD_sendData(&blackImage[i + j*width]);
		}
	}

	EPD_sendCommand(&payload[payloadI]);
	for(uint16_t j = 0; j < height; j++)
	{
		for(uint16_t i = 0; i < width; i++)
		{
			EPD_sendData(&blackImage[i + j*width]);
		}
	}

	EPD_turnOnDisplay();

	return;
}

void EPD_sleep(void)
{
	#if DRYRUN || DEBUG
	printf("EPD_sleep\n");
	#endif

	const uint8_t payload[] = 
	{
		0x50, 0xF7,
		0x02,
		0x07, 0xA5
	};
	uint8_t payloadI = 0;

	EPD_sendCommand(&payload[payloadI++]);
	EPD_sendData(&payload[payloadI++]);

	EPD_sendCommand(&payload[payloadI++]);
	EPD_readBusy();
	EPD_sendCommand(&payload[payloadI++]);
	EPD_sendData(&payload[payloadI++]);

	return;
}

void EPD_exit(void)
{
	#if DRYRUN || DEBUG
	printf("EPD_exit\n");
	#endif

	DEV_write(EPD_pins.scrn_cs, 0);
	DEV_write(EPD_pins.scrn_pwr, 0);
	DEV_write(EPD_pins.scrn_dc, 0);
	DEV_write(EPD_pins.scrn_rst, 0);

	return;
}

#if DRYRUN || DEBUG
void EPD_pinsDump(void)
{
	printf("\
		scrn_pwr  = %u\n\
		scrn_tx   = %u\n\
		scrn_sclk = %u\n\
		scrn_cs   = %u\n\
		scrn_dc   = %u\n\
		scrn_rst  = %u\n\
		scrn_busy = %u\n",
		EPD_pins.scrn_pwr,
		EPD_pins.scrn_tx,
		EPD_pins.scrn_sclk,
		EPD_pins.scrn_cs,
		EPD_pins.scrn_dc,
		EPD_pins.scrn_rst,
		EPD_pins.scrn_busy
	);

	return;
}
#endif