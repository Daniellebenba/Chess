/*
 * CHessGame.h
 *
 *  Created on: 19 בספט׳ 2017
 *      Author: User
 */

#ifndef CHESSGAME_H_
#define CHESSGAME_H_
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "AI.h"

#define SP_N_ROWS 8
#define SP_N_COLUMNS 8

//board & pieces of the game
extern int board[64];
extern int testBoard[64]; //all elements are 0
extern int flip_board[64]; //the board is upside-down
extern int white[16][2];
extern int black[16][2];
extern int queen[2];
extern int knight[2];
extern int rook[2];
extern int bishop[2];
extern int pawn[2];

//game setting
extern int game_mode;
extern int game_difficulty;
extern int game_color; //1-white, 0-black

//game history & state
extern int current_player;
extern int last_move;
extern int moves[6][4]; //the last 6 moves of the game for the user and the computer: [x][0] = piece, [x][1] = before move,
//[x][2] = after move, [x][3] = -1/ the index in the opponent's array that was cut in the move


#endif /* CHESSGAME_H_ */
