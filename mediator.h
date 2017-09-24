/*
 * mediator.h
 *
 *  Created on: 26 ׀�׀®׀•׀‘׀² 2017
 *      Author: User
 */
#include "CHessGame.h"
#include "savedGames.h"
#include "CHParser.h"

#ifndef MEDIATOR_H_
#define MEDIATOR_H_
#define SP_N_ROWS 8
#define SP_N_COLUMNS 8
#define SP_PLAYER_1_SYMBOL 11 || 13 || 14 || 15 ||19|| 1000
#define SP_PLAYER_2_SYMBOL 21 || 23 || 24 || 25 ||29 ||2000


//board & pieces of the game
extern int board[64];
extern int testBoard[64]; //all elements are 0
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
extern int game_color;

//game history & state
extern int current_player;
extern int last_move;
extern int moves[6][4]; //the last 6 moves of the game for the user and the computer: [x][0] = piece, [x][1] = before move,
//[x][2] = after move, [x][3] = -1/ the index in the opponent's array that was cut in the move


void initialize(int board[]);

int moveMonitor(int board[] ,int turn, int piece, int x, int y);

void flipBoard(int board[], int copyOf[]);
void setGame(char pieces[]);

int loadFile( char *file_name);

int moveKnight(int x, int y);
int moveKing(int x, int y);
int moveQueen(int x, int y);
int moveBishop(int x, int y);
int moveRook(int x, int y);
int computer_move();
void setting_state();

int CheckMateOrTie(int turn);

int** options(int turn, int board[]);
void copyBoard(int board[], int copyOf[]);


void printBoard(int board[]);

#endif /* MEDIATOR_H_ */
