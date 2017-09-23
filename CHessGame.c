/*
 * CHessGame.c
 *
 *  Created on: 19 בספט׳ 2017
 *      Author: User
 */

#include "CHessGame.h"


//board & pieces of the game
int board[64] ={0};
int testBoard[64] = {0}; //all elements are 0
int flip_board[64] = {0}; //the board is upside-down
int white[16][2];
int black[16][2];
int queen[2] = {19,29};
int knight[2] = {13,23};
int rook[2] = {15,25};
int bishop[2] = {14,24};
int pawn[2] = {11,21};

//game setting
int game_mode;
int game_difficulty;
int game_color; //1-white, 0-black

//game history & state
int current_player;
int last_move;
int moves[6][4]; //the last 6 moves of the game for the user and the computer: [x][0] = piece, [x][1] = before move,
//[x][2] = after move, [x][3] = -1/ the index in the opponent's array that was cut in the move
