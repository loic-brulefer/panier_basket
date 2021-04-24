/*
 * dfplayer_mini.c
 *
 *  Created on: Apr 3, 2021
 *      Author: Loic
 */


#include "dfplayer_mini.h"


/**
 *
 */
void dfp_init(void)
{
	u8 volume = 0u;

	if (dfp_get_volume(&volume) == 0u)
	{
		if (volume > 20)
		{
			dfp_decrease_volume();
		}
		dfp_get_volume(&volume);
	}
}

/**
 *
 */
u8 dfp_get_volume(u8 *volume)
{
	u8 i = 0u;
	u8 ret = 0u;

	// 7E FF 06 43 00 00 00 FE B8 EF
	u8 frame[10] = {0x7E, 0xFF, 0x06, 0x43, 0x00, 0x00, 0x00, 0xFE, 0xB8, 0xEF};

	new_line();
	print_string("S : ");
	for (i = 0u; i < 10u; i++)
	{
		print_u8(frame[i]); space();
	}
	new_line();

	HAL_UART_Transmit(&huart1, frame, 10, 1000);

	//
	// reset tab
	//
	for (i = 0u; i < 10u; i++)
	{
		frame[i] = 0u;
	}

	if (HAL_UART_Receive(&huart1, frame, 10, 1000) != HAL_OK) {
		print_string("Error");
		new_line();
		ret = 1u;
	}
	else {
		print_string("R : ");
		for (i = 0u; i < 10u; i++)
		{
			print_u8(frame[i]); space();
		}
		new_line();
		*volume = frame[6];
	}

	return ret;
}

/*
 *
 */
void dfp_set_volume(u8 volume)
{
	u8 i = 0u;

	// 7E FF 06 06 00 00 0F FF D5 EF
	u8 frame[10] = {0x7E, 0xFF, 0x06, 0x06, 0x00, 0x00, 0x0F, 0xFF, 0xD5, 0xEF};

	if (volume == 15u)
	{
		new_line();
		print_string("Send : \t");
		for (i = 0u; i < 10u; i++)
		{
			print_u8(frame[i]); space();
		}
		new_line();

		HAL_UART_Transmit(&huart1, frame, 10, 1000);

		//
		// reset tab
		//
		for (i = 0u; i < 10u; i++)
		{
			frame[i] = 0u;
		}

		if (HAL_UART_Receive(&huart1, frame, 10, 1000) != 0u) {
			print_string("Error");
			new_line();
		}
		else {
			print_string("Rcv : \t");
			for (i = 0u; i < 10u; i++)
			{
				print_u8(frame[i]); space();
			}
			new_line();
		}
	}
	else {
		// nothing
	}
}

/**
 *
 */
void dfp_decrease_volume(void)
{
#if 0
	u8 i = 0u;

	// 7E FF 06 06 00 00 0F FF D5 EF
	u8 frame[10] = {0x7E, 0xFF, 0x06, 0x06, 0x00, 0x00, 0x0F, 0xFF, 0xD5, 0xEF};

	for (i = 0u; i < 10u; i++)
	{
		print_u8(frame[i]); space();
	}
	new_line();

	HAL_UART_Transmit(&huart1, frame, 10, 1000);
#else
	HAL_GPIO_WritePin(VolumeDown_GPIO_Port, VolumeDown_Pin, GPIO_PIN_RESET);
	HAL_Delay(2500);
	HAL_GPIO_WritePin(VolumeDown_GPIO_Port, VolumeDown_Pin, GPIO_PIN_SET);
#endif
}

/**
 *
 */
void dfp_play(void)
{
	//
	u8 frame[] = {0x7E, 0xFF, 0x06, 0x0D, 0x00, 0x00, 0x00, 0xFE, 0xEE, 0xEF};
	HAL_UART_Transmit(&huart1, frame, sizeof(frame), 1000);
}

/**
 *
 */
void dfp_play_next(void)
{
	//
	u8 frame[] = {0x7E, 0xFF, 0x06, 0x0D, 0x00, 0x00, 0x00, 0xFE, 0xEE, 0xEF};	// \todo adjust
	HAL_UART_Transmit(&huart1, frame, sizeof(frame), 1000);
}

/**
 *
 */
void dfp_pause(void)
{
	// 7E FF 06 0E 00 00 00 FE ED EF
	u8 frame[] = {0x7E, 0xFF, 0x06, 0x0E, 0x00, 0x00, 0x00, 0xFE, 0xED, 0xEF};
	HAL_UART_Transmit(&huart1, frame, sizeof(frame), 1000);
}

/**
 * The first sound file conducted to be played is the first one in the device
 */
void dfp_set_random_playback(void)
{
	// 7E FF 06 18 00 00 00 FE E3 EF
	u8 frame[] = {0x7E, 0xFF, 0x06, 0x18, 0x00, 0x00, 0x00, 0xFE, 0xE3, 0xEF};
	HAL_UART_Transmit(&huart1, frame, sizeof(frame), 1000);
}
