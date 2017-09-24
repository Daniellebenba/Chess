/*
 * CHessSettingManager.c
 *
 *  Created on: 24 בספט׳ 2017
 *      Author: User
 */

#include "CHessSettingManager.h"


/**
 * args: 1-for black. 0-for white
 * set the color in 1-player mode
 */
void set_color(int color){
	game_color = color;
}

/**
 * set the game's difficulty level
 */
void set_level(int level){
	game_difficulty = level;
}

/**
 * set the game's mode. 1 or 2 players
 */
void set_game_mode(int mode){
	game_mode = mode;
}
