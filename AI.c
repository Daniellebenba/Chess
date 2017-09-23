/*
 * AI.c
 *
 *  Created on: 14 בספט׳ 2017
 *      Author: User
 */
#include "AI.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int compMove[3] ={0}; //[0]: from, [1]: to, [2]: the piece's val if there was a capture
int colorForScore;



//int queen[2] = {19,29};
//int knight[2] = {13,23};
//int rook[2] = {15,25};
//int bishop[2] = {14,24};
//int pawn[2] = {11,21};
//pawn = 1 , knight = 3 , bishop = 3 , rook = 5, queen = 9, king=100



/**
 * scoring function that evaluates the board's score
 */

void free2Dpointer( int** pointer, int len){
	for (int i=0; i<len; ++i) {
	  free(pointer[i]);
	}
	free(pointer);
}
int score_board(int board[], int turn){
	int score=0;
	for (int i=0; i<64; i++){
			if ((board[i]==11 && turn) || (board[i]==21 && !turn)){ //opponent's pawn
				score -= 1;
			}
			else if ((board[i]==13 && turn) || (board[i]==23 && !turn)){ //opponent's knight
				score -= 3;
			}
			else if ((board[i]==14 && turn) || (board[i]==24 && !turn)){ //opponent's bishop
				score -= 3;
			}
			else if ((board[i]==15 && turn) || (board[i]==25 && !turn)){ //opponent's rook
				score -= 5;
			}
			else if ((board[i]==19 && turn) || (board[i]==29 && !turn)){  //opponent's queen
				score -= 9;
			}
			else if ((board[i]==1000 && turn) || (board[i]==2000 && !turn)){ //opponent's king
				score -= 100;
			}
			if ((board[i]==11 && !turn) || (board[i]==21 && turn)){ //player's pawn
				score += 1;
			}
			else if ((board[i]==13 && !turn) || (board[i]==23 && turn)){ //player's knight
				score += 3;
			}
			else if ((board[i]==14 && !turn) || (board[i]==24 && turn)){ //player's bishop
				score += 3;
			}
			else if ((board[i]==15 && !turn) || (board[i]==25 && turn)){ //player's rook
				score += 5;
			}
			else if ((board[i]==19 && !turn) || (board[i]==29 && turn)){  //player's queen
				score += 9;
			}
			else if ((board[i]==1000 && !turn) || (board[i]==2000 && turn)){ //player's king
				score += 100;
			}
	}
	return score;
}

int max(int a, int b){
	if (a >= b){
		return a;
	}
	else{
		return b;
	}
}

int min(int a, int b){
	if (a >= b){
		return b;
	}
	else{
		return a;
	}
}

int minmax(int minmaxBoard[], int times, int color, int alpha, int beta, bool player){ // status = start (0), and (1)
	//printf(" times = %d, color is %d , game difficulty is %d ",times, color, game_difficulty);
		//printf("times is %d\n", times);
	if (times == game_difficulty){
		//printf(" times == game_difficulty, color is %d \n", color);
		colorForScore = color;
	}
	if (times==0){
		int score = score_board(minmaxBoard, colorForScore);
		//printf("times==0, score is: %d\n", score);
		return score;
	}
	int** array = options(color, minmaxBoard);
	//printf("finished options\n");
	int len = array[0][0];
	if (len == 0){ // add check winner?
		int score = score_board(minmaxBoard, colorForScore);
		//printf("len==0, score is: %d\n", score);
		free2Dpointer(array,1);
		return score;
	}
	int tmp_board[64];
	int tmp1;
	int tmp2;
	if (player){
		int valueMiniMax =  - INT_MAX;
			for (int i = 1; i<= len; i++){
				copyBoard(minmaxBoard, tmp_board);
				printf("move from %d to %d\n",array[i][1],array[i][2]);
				tmp_board[array[i][2]]=tmp_board[array[i][1]];
				tmp_board[array[i][1]]= 0;
				//printBoard(tmp_board); //for test
				tmp1 = valueMiniMax;
				valueMiniMax = max(valueMiniMax,minmax(tmp_board,  times-1 , 0-(color-1), alpha,beta, false) );
				//printf("if: value is %d in call #%d\n",valueMiniMax, times);
				if(valueMiniMax != tmp1 ){
					compMove[0] = array[i][1];
					compMove[1]= array[i][2];
					compMove[2] = array[i][0]; //the piece val if there was a cut. 0- otherwise
					array[0][2] =i;
					//printf("update in if: compMove[0]=%d,compMove[1]=%d\n",compMove[0],compMove[1]);
				}
				alpha = max(valueMiniMax, alpha);
				if(beta<=alpha){
					break;
				}

			}
			//printf("best move is from %d to %d\n",array[0][1],array[0][2]);
			compMove[0] = array[array[0][2]][1];
			compMove[1] = array[array[0][2]][2];
			compMove[2] = array[array[0][2]][0]; //the piece's val if there was a capture. 0- otherwise
			free2Dpointer(array, len+1 );
			return valueMiniMax;
	}
	else {
			int valueMiniMax = INT_MAX;
			for (int i = 1; i<=len; i++){
				copyBoard(minmaxBoard, tmp_board);
				//printf("move from %d to %d\n",array[i][1],array[i][2]);
				tmp_board[array[i][2]]=tmp_board[array[i][1]];
				tmp_board[array[i][1]]= 0;
				//printBoard(tmp_board);
				tmp2 = valueMiniMax;
				valueMiniMax = min(valueMiniMax,minmax(tmp_board,  times-1 , 0-(color-1),alpha,beta, true) );
				//printf("else: value is %d in call #%d\n",valueMiniMax, times);
				if(valueMiniMax != tmp2){
						compMove[0] = array[i][1];
						compMove[1] = array[i][2];
						compMove[2] = array[i][0]; //the piece val if there was a cut. 0- otherwise
						array[0][2] =i;
						//printf("update in else: compMove[0]=%d,compMove[1]=%d\n",compMove[0],compMove[1]);
				}
				beta = min(valueMiniMax, beta);
				if(beta<=alpha){
					break;
				}
			}
			//printf("best move is from %d to %d\n",array[0][1],array[0][2]);
			compMove[0] = array[array[0][2]][1];
			compMove[1] = array[array[0][2]][2];
			compMove[2] = array[array[0][2]][0]; //the piece's val if there was a capture. 0- otherwise
			free2Dpointer(array, len+1);
			return valueMiniMax;
		}
		return 0;
	}
