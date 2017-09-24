/*
 * CHessSettingManager.h
 *
 *  Created on: 24 בספט׳ 2017
 *      Author: User
 */

#ifndef GRAPHICS_CHESSSETTINGMANAGER_H_
#define GRAPHICS_CHESSSETTINGMANAGER_H_

#include "CHessGUImanager.h"


/**
 * args: 1-for black. 0-for white
 * set the color in 1-player mode
 */
void set_color(int color);

/**
 * set the game's difficulty level
 */
void set_level(int level);

/**
 * set the game's mode. 1 or 2 players
 */
void set_game_mode(int mode);

#endif /* GRAPHICS_CHESSSETTINGMANAGER_H_ */
