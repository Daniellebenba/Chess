/*
 * CHessGameManager.c
 *
 *  Created on: 24 בספט׳ 2017
 *      Author: User
 */

#include "CHessGameManager.h"
//wtf21:13
/**
 * arg: gets the position move that was made by user.
 * if the move is legal update the game board.
 * return 1 if the move is valid and 0 otherwise.
 */
int get_move(int fx, int fy, int tx, int ty){
	int piece = board[fx*8+fy]; //take the piece's val from the game board
	move = manage_move(current_player,comb_x,comb_y,piece);
	if (move == 0){
		return 0;
	}
	return 1;
}

/**
 * args starting position and next position
 * update the board in gameWin
 */
void updateWinBoard(int fx, int fy,int tx, int ty);

/**
 * after move was made by user check if the game is over. calls the computers move in 1-player mode.
 */
int after_move(){
	if (CheckMateOrTie(!current_player)==1){ //a checkmate
			if (current_player==0){ //white
				printf("Checkmate! white player wins the game\n");
				//need to open window message
				return 0;
			}
			else{ //black
				printf("Checkmate! black player wins the game\n");
				//need to open window message
				return 0;
			}
		return 0;
	}
	else if (CheckMateOrTie(!current_player)==0){ //a tie
			printf("The game is tied\n");
			//need to open window message
			return 0;
	}
	if (current_player==0 && game_mode==2){ //was white's turn in 2-players mode
		if (checkBoard(current_player, white[15][1],board)){ //there is a check
		printf("Check: black King is threatend!\n");
		//need to open window message
		}
	}
	else if (current_player==1 && game_mode==2){ //was black's turn in 2-players mode
		if (checkBoard(current_player, black[15][1], board)){ //there is a check
			printf("Check: white King is threatend!\n");
			//need to open window message
		}
	}
	else if (current_player==0 && game_mode==1 && game_color==0){ //1-player mode and it was the computer turn that has white color
		if (checkBoard(current_player, white[15][1],board)){ //there is a check
			printf("Check!\n");
			//need to open window message
		}
	}
	else if (current_player==1 && game_mode==1 && game_color==1){ //1-player mode and it was the computer turn that has black color
		if (checkBoard(current_player, black[15][1],board)){ //there is a check
			printf("Check!\n");
			//need to open window message
		}
	}
	current_player = !current_player;
		if ((current_player==0 && game_mode==1 && game_color==0) || (current_player==1 && game_mode==1 && game_color==1)){ //1-player and it's
			printf("computer_move call\n");
			computer_move(current_player);
			int position = moves[last_move][1]; //old position
			int new_pos = moves[last_move][2];	//new position
			int fx = position/8 +1;
			int fy = position%8;
			int tx = new_pos/8 +1;
			int ty = new_pos%8;
			updateWinBoard(fx, fy,tx, ty);
			current_player = !current_player;
		}
	return 0;
}


