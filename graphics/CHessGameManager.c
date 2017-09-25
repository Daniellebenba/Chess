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
int get_move(int from, int to){

	int piece = board[to]; //take the piece's val from the game board
	int move = manage_move(current_player,from,to,piece);
	if (move == 0){
		return 0;
	}
	return 1;

}


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

			current_player = !current_player;
		}
	return 0;
}


