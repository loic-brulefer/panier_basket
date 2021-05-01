/*
 * dfplayer_mini.h
 *
 *  Created on: Apr 3, 2021
 *      Author: Loic
 */

#ifndef INC_DFPLAYER_MINI_H_
#define INC_DFPLAYER_MINI_H_

#include "main.h"
#include "usart.h"
#include "project.h"

void dfp_init(void);
u8 dfp_get_volume(u8 *volume);
void dfp_set_volume(u8 volume);
void dfp_decrease_volume(void);
void dfp_play(void);
void dfp_play_next(void);
void dfp_pause(void);
void dfp_set_random_playback(void);
u8 dfp_get_response(u8 rx_frame[]);

#endif /* INC_DFPLAYER_MINI_H_ */
