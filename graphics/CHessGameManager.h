/*
 * gameMenager.h
 *
 *  Created on: 24 ����� 2017
 *      Author: User
 */

#ifndef GRAPHICS_CHESSGAMEMANAGER_H_
#define GRAPHICS_CHESSGAMEMANAGER_H_
#include "../CHessGame.h"
/**
 * arg: gets the position move that was made by user.
 * if the move is legal update the game board.
 * return 1 if the move is valid and 0 otherwise.
 */
int get_move(int fx, int fy, int tx, int ty);

void updateWinBoard(int fx, int fy,int tx, int ty);

int after_move();

#endif /* GRAPHICS_CHESSGAMEMANAGER_H_ */
