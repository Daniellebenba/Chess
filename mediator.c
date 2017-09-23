
/*
 * mediator.c
 *
 *  Created on: 26 баев„ 2017
 *      Author: User
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "mediator.h"
#include <stdbool.h>


////board & pieces of the game
//int board[64] ={0};
//int testBoard[64] = {0}; //all elements are 0
//int flip_board[64] = {0}; //the board is upside-down
//int white[16][2];
//int black[16][2];
//int queen[2] = {19,29};
//int knight[2] = {13,23};
//int rook[2] = {15,25};
//int bishop[2] = {14,24};
//int pawn[2] = {11,21};
//
////game setting
//int game_mode;
//int game_difficulty;
//int game_color; //1-white, 0-black
//
////game history & state
//int current_player;
//int last_move;
//int moves[6][4]; //the last 6 moves of the game for the user and the computer: [x][0] = piece, [x][1] = before move,
////[x][2] = after move, [x][3] = -1/ the index in the opponent's array that was cut in the move


//Initial position, first row: rook, knight, bishop, queen, king, bishop, knight, and rook; second row: pawns

void initialize(int board[]){

	//initialize the setting of the game- default setting
	game_mode=1;
	game_difficulty=2;
	game_color=1;

	//game state
	current_player=0;
	last_move=-1;



	//initialize the moves array of the game
	for (int i=0; i<6; i++){
		for (int j=0; j<4; j++){
			moves[i][j] = -1;
		}
	}
	//initialize the game board and the pieces arrays for black and for white.
	for (int i=0; i<8; i++){ //initialize the pawns
		board[8+i] = 11; // 2nd row: white pawns
		white[i][0] = 11;
		white[i][1] = 8+i; //set the position
		board[48+i] = 21; // 6 row: black pawns
		black[i][0] = 21;
		black[i][1] = 48+i; //set the position

	}
	for (int i=16; i<48; i++){ //setting 0 in the rest of the board
		board[i] = 0;
	}
	//white rook
	board[0] = board[7] = white[12][0] = white[13][0] = 15; //set the value in the right position on the board and in the array
	white[12][1] = 0; //the position
	white[13][1] = 7; //the position
	//black rook
	board[56] = board[63] = black[12][0] = black[13][0] =  25;
	black[12][1] = 56;
	black[13][1] = 63;
	//white knight
	board[1] = board[6] = white[8][0] = white[9][0] = 13;
	white[8][1] = 1;
	white[9][1] = 6;
	//black knight
	board[57] = board[62] = black[8][0] = black[9][0] = 23;
	black[8][1] = 57;
	black[9][1] = 62;
	//white bishop
	board[2] = board[5] = white[10][0] = white[11][0] = 14;
	white[10][1] = 2;
	white[11][1] = 5;
	//black bishop
	board[58] = board[61] = black[10][0] = black[11][0] = 24;
	black[10][1] = 58;
	black[11][1] = 61;
	//white king
	board[3] = white[15][0] = 1000;
	white[15][1] = 3;
	//black king
	board[59] = black[15][0] = 2000;
	black[15][1] = 59;
	//white queen
	board[4] = white[14][0] = 19;
	white[14][1] = 4;
	//black queen
	board[60] = black[14][0] = 29;
	black[14][1] = 60;
}







void copyBoard(int board[], int copyOf[]){
	for (int i=0; i<64; i++){
		copyOf[i] = board[i];
	}
	return;
}

void flipBoard(int board[], int copyOf[]){
	for (int i=0; i<64; i++){
		copyOf[i] = board[63-i];
	}
	return;
}

//void printBoard(int board[]){
//	for (int i=0; i<8; i++){
//		printf("|");
//		for (int j =0; j<8; j++){
//			printf("%d",board[i*8 + j]);
//			printf("|");
//		}
//		printf("\n");
//	}
//}



/**
 * taking a char array that has the board status and set the board of the game and the colors arrays with the same state
 */
void setGame(char pieces[]){
	int p_w=0; //pawn white
	int p_b=0;
	int r_w=0; //rook white
	int r_b=0;
	int b_w=0; //bishop white
	int b_b=0;
	int n_w=0; //knight white
	int n_b=0;
	for (int i =0; i<64; i++){
		switch (pieces[i]) {
		case 'k':
			board[i]=1000;
			white[15][0]=1000;
			white[15][1]= i;
			break;
		case 'K':
			board[i]=2000;
			black[15][0]=2000;
			black[15][1]= i;
			break;
		case 'p':
			board[i]=11;
			white[p_w][0]= 11;
			white[p_w][1]= i;
			p_w+=1;
			break;
		case 'P':
			board[i]=21;
			black[p_w][0]= 21;
			black[p_w][1]= i;
			p_b+=1;
			break;
		case 'n':
			board[i]=13;
			white[8+n_w][0]=13;
			white[8+n_w][1]=i;
			n_w+=1;
			break;
		case 'N':
			board[i]=23;
			black[8+n_b][0]=23;
			black[8+n_b][1]=i;
			n_b+=1;
			break;
		case 'b':
			board[i]=14;
			white[10+b_w][0]=14;
			white[10+b_w][1]=i;
			b_w+=1;
			break;
		case 'B':
			board[i]=24;
			black[10+b_b][0]=14;
			black[10+b_b][1]=i;
			b_b+=1;
			break;
		case 'r':
			board[i]=15;
			white[12+r_w][0]=15;
			white[12+r_w][1]=i;
			r_w+=1;
			break;
		case 'R':
			board[i]=25;
			black[12+r_b][0]=25;
			black[12+r_b][1]=i;
			r_b+=1;
			break;
		case 'q':
			board[i]=19;
			white[14][0] =19;
			white[14][1] =i;
			break;
		case 'Q':
			board[i]=29;
			black[14][0] =29;
			black[14][1] = i;
			break;
		default: //"_"
			board[i]=0;
			break;
		}
	}
}

/**
 * prints the game's board
 */
void printBoard(int board[]){
	for (int i=7; i>=0; i--){
			printf("%d| ",i+1);
		for (int j =0; j<8; j++){
			int piece = board[i*8 + j];
			switch ( piece ) {
			case 1000:
			printf("k ");
			break;
			case 2000:
			printf("K ");
			break;
			case 11:
			printf("p ");
			  break;
			case 21:
			printf("P ");
			  break;
			case 13:
			printf("n ");
			  break;
			case 23:
			printf("N ");
			  break;
			case 14:
			printf("b ");
			  break;
			case 24:
			printf("B ");
			  break;
			case 15:
			printf("r ");
			  break;
			case 25:
			printf("R ");
			  break;
			case 19:
			printf("q ");
			  break;
			case 29:
			printf("Q ");
			  break;
			default:
				printf("_ ");
			  break;
	}
}
		printf("|\n");

	}
	for(int j = 0; j<21 ;  j++){
		if (j == 0 || j ==1 || j==20||j==19){
				printf(" ");
				continue;
			}
		else{
				printf("-");
			}
		}
	printf("\n");
	for (int i =0; i<11; i++ ){
		if (i<3){
			printf(" ");
			continue;
		}
		char ch = 'A'-3+i;
		printf("%c ", ch);
	}
	printf("\n");
	return;
}




/**
 * args: a file name of a saved game
 * set the game state and setting by the file
 */
int loadFile( char *file_name) {
	//printf("here! fp=%c\n", *file_name);
	FILE *fp  = fopen(file_name, "r");
	printf("here! fp=%s\n", file_name);
	if (fp==NULL){
		printf(" fp == NULL");
		return 0;
	}
	char buffer[100];
	fseek(fp, 0, SEEK_SET);
	fgets(buffer,1000, fp);
	printf("%s",buffer);
	fgets(buffer,1000, fp);
	printf("%s",buffer);
	char* word;
	/* Read and display data */
	fgets(buffer,1000, fp);
	word = strtok(buffer, curr_turn_start);
	printf("arg1: %s\n", word);
	current_player = *word;
	fgets(buffer,1000, fp);
	word = strtok(buffer, game_mode_start);
	printf("arg2: %s\n", word);
	game_mode = *word;
	fgets(buffer,1000, fp);
	word = strtok(buffer, difficulty_start);
	printf("arg3: %s\n", word);
	game_difficulty= *word;
	fgets(buffer,1000, fp);
	word = strtok(buffer, user_color_start);
	printf("arg4: %s\n", word);
	game_color= *word;
	fgets(buffer,1000, fp);
	fgets(buffer,10, fp);
	char pieces[64];
	char c;
	for(int i=0; i<8;i++){
	    for (int j = 0; j<8; j++ ) {
	    	c = fgetc(fp);
	    	pieces[i*8+j]= c;
	    	printf("i= %d, j= %d,c is: %c\n",i,j ,c);
	    }
	    fgets(buffer,1000, fp);
	    fgets(buffer,10, fp);
	}
	setGame(pieces);
	printBoard(board);
	fclose(fp);
	return 1;
}

/**
 * check if the move for knight is valid
 * args: x- current position, y- wish position
 * return 1 if true. 0: otherwise
 */
int moveKnight(int x, int y){
	if (x%8 >1 && x<56){
		if (x + 6 == y){
			return 1;
		}
	}
	if (x%8 >1 && x>7){
		if (x-10 ==y){
			return 1;
		}
	}
	if (x%8 <6 && x>7){
		if (x-6==y){
			return 1;
		}
	}
	if (x%8 <6 && x<56){
		if (x+10==y){
			return 1;
		}
	}
	if (x>15 && x%8<7){ //2 steps down and one right
		if (x-15==y){
			return 1;
		}
	}
	if (x<48 && x%8 >0){ //2 steps up and one left
		if (x+15==y){
			return 1;
		}
	}
	if (x>15 && x%8>0){ //2 steps down and one left
		if (x-17==y){
			return 1;
		}
	}
	if (x<48 && x%8<7){ //2 steps up and one right
		if (x+17==y){
			return 1;
		}
	}
	return 0;
}


/**
 * check if the move for rook is valid
 * args: x- current position, y- wish position
 * return 1 if true. 0: otherwise
 */
int moveRook(int x, int y){
	//printf("move rock\n");
	int ind =x;
	int flag = 1;
	if (y>x){ // up or right
		//printf("l\n");
		ind += 1;
		while (ind %8 !=0){ //search from right
			//printf("%d\n",ind);
			if (ind == y){
				if (flag){	//didn't leap over
					return 1;
				}
				else{  //did leap over
					return 0;
				}
			}
			if (board[ind] != 0){
				flag = 0;
			}
			ind += 1;
		}
		flag = 1;
		ind = x+8;
		while (ind < 64){ //search up
			if (ind == y){
				if (flag){ //didn't leap over
					return 1;
				}
				else{ //did leap over
					return 0;
				}
			}
			if (board[ind] != 0){
				flag = 0;
			}
			ind += 8;
		}
		return 0; //not horizontal or vertical move
	}
	else{ //(y<x)
		do {
			ind -= 1;
			if (ind == y){
				//printf("got gere in move rock and ind is %d\n", ind);
				if (flag){	//didn't leap over
					return 1;
				}
				else{  //did leap over
					return 0;
				}
			}
			if (board[ind] != 0){
				flag = 0;;
			}
		}
		while (ind %8 !=7); //search from left
		flag = 1;
		ind = x-8;
		while (ind >= 0){ //search down

			if (ind == y){
				if (flag){ //didn't leap over
					return 1;
				}
				else{ //did leap over
					return 0;
				}
			}
			if (board[ind] != 0){
				flag = 0;
			}
			ind -= 8;
		}
		return 0; //not horizontal or vertical move
	}
	return 0;
}



/**
 * check if the move for Bishop is valid
 * args: x- current position, y- wish position
 * return 1 if true. 0: otherwise
 */
int moveBishop(int x, int y){

	if (((y-x)%7 == 0) && (y>x) && ((x%8)>(y%8))){ //diagonal left and up
		if (((y-(x+7))%7) != 0){
			return 0;
		}
		if ((((y-(x-7))%7) != 0)&&(x>7)&&(x%8>0)){
			return 0;
		}
		for (int i=1; i < (y-x)/7; i++){
			if (board[x+7*i] != 0){
				return 0;
			}
		}
		return 1;
	}
	if (((x-y)%7 == 0) && (y<x) && ((x%8)<(y%8))){ //diagonal right and down
		if ((((y-(x+7))%7) != 0) && (x%8>0)&&(x<56)){
			return 0;
		}
		if (((y-(x-7))%7) != 0){
			return 0;
		}
		for (int i=1; i < (x-y)/7; i++){
			if (board[x-7*i] != 0){
				return 0;
			}
		}
		return 1;
	}
	if (((y-x)%9 == 0) && (y>x)&& ((x%8)<(y%8))){ //diagonal right and up
		if (((y-(x+9))%9) != 0){
			return 0;
		}
		if ((((y-(x-9))%9) != 0)&&(x>7)&&(x%8>0)){
			return 0;
		}
		for (int i=1; i < (y-x)/9; i++){
			if (board[x+9*i] != 0){
				return 0;
			}
		}
		return 1;
	}
	if (((x-y)%9 == 0) && (y<x) && ((x%8)>(y%8))){ //diagonal left and down
		//int y2 = (y-(x+9))%9;
		if ((((y-(x+9))%9) != 0)&&(x%8>0)&&(x<56)){
			return 0;
		}
		if (((y-(x-9))%9) != 0){
			return 0;
		}
		for (int i=1; i < (x-y)/9; i++){
			if (board[x-9*i] != 0){
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

/**
 * check if the move for Queen is valid: combination of rook and bishop moves and also can't leap over
 * args: x- current position, y- wish position
 * return 1 if true. 0: otherwise
 */
int moveQueen(int x, int y){
	//printf("queen move %d to %d\n", x,y);
	int val = moveBishop(x,y);
	//printf("val is-%d\n",val);
	if (val){
		printf("bishop %d %d\n", x, y);
		return 1;
	}
	val = moveRook(x,y);
	if (val){
		printf("rook %d %d\n", x, y);
		return 1;
	}
	return 0;
}



/**
 * check if the move for the king is valid
 * args: x- current position, y- wish position
 * return 1 if true. 0: otherwise
 */
int moveKing(int x, int y){
	if (x<56){ //up
		if (x+8==y){
			return 1;
		}
	}
	if (x>7){ //down
		if (x-8==y){
			return 1;
		}
	}
	if (x%8>0){ //left
		if (x-1==y){
			return 1;
		}
		if ((x+7==y)&&(x<56)){ //and up
			return 1;
		}
		if ((x-9==y)&&(x>7)){ //and down
			return 1;
		}
	}
	if (x%8<7){ //right
		if (x+1==y){
			return 1;
		}
		if ((x-7==y)&&(x>7)){  //and down
			return 1;
		}
		if ((x+9==y)&&(x<56)){ //and up
			return 1;
		}
	}
	return 0;
}

/**
 * check if the king is threatened from horizontal. if true, return 1
 */
int checkHorizontal(int turn, int kingP, int board[]){ // 0 checkW 1 checkB
	for (int i = kingP+1; i<64 ;i++){ //checks horizontal to the right
		if ((i)%8 == 0){
			break;
		}
		else{
			if (board[i]== queen[turn]|| board[i] == knight[turn] || board[i] == pawn[turn] || board[i] == rook[turn]|| board[i] == bishop[turn]){
				break;
			}
			if (board[i]== queen[0-(turn-1)] && moveMonitor(board, 0-(turn-1), queen[0-(turn-1)], i, kingP)){
				return 1;

			}
			if ( board[i]== rook[0-(turn-1)] && moveMonitor(board, 0-(turn-1), rook[0-(turn-1)], i, kingP)){
				return 1;
			}
		}
	}
	for (int i = kingP-1; i>=0 ;i--){ //checks horizontal to the left
		if ((i)%8 == 7){
			break;
		}
		else{
			if (board[i]== queen[turn]|| board[i] == knight[turn] || board[i] == pawn[turn] || board[i] == rook[turn]|| board[i] == bishop[turn]){
				break;				}

			if (board[i]== queen[0-(turn-1)] && moveMonitor(board, 0-(turn-1), queen[0-(turn-1)], i, kingP)){
				return 1;

			}

			if ( board[i]== rook[0-(turn-1)] && moveMonitor(board, 0-(turn-1), rook[0-(turn-1)], i, kingP)){
				return 1;
			}
		}
	}
	return 0;
}



/**
 * check if the king is threatened from vertical. if true, return 1. otherwise return 0.
 */
int checkVertical(int turn, int kingP, int board[]){ // 0 checkW 1 checkB
	for (int i = kingP; i<64 ;i+=8){ //checks vertical up
		if (board[i]== queen[turn]|| board[i] == knight[turn] || board[i] == pawn[turn] || board[i] == rook[turn]|| board[i] == bishop[turn]){
			break;
		}

		if (board[i]== queen[0-(turn-1)] && moveMonitor(board, 0-(turn-1), queen[0-(turn-1)], i, kingP)){
			return 1;

		}
		if ( board[i]== rook[0-(turn-1)] && moveMonitor(board, 0-(turn-1), rook[0-(turn-1)], i, kingP)){
			return 1;
		}
	}
	for (int i = kingP; i>=0 ;i-=8){ //checks vertical down
		if (board[i]== queen[turn]|| board[i] == knight[turn] || board[i] == pawn[turn] || board[i] == rook[turn]|| board[i] == bishop[turn]){
			break;
		}
		if (board[i]== queen[0-(turn-1)] && moveMonitor(board, 0-(turn-1), queen[0-(turn-1)], i, kingP)){
			return 1;

		}
		if ( board[i]== rook[0-(turn-1)] && moveMonitor(board, 0-(turn-1), rook[0-(turn-1)], i, kingP)){
			return 1;
		}
	}
	return 0;
}


/**
 * check if the king is threatened from diagonal. if true, return 1. otherwise return 0.
 */


int checkDiagonal(int turn, int kingP, int board[]){ // 0 checkW 1 checkB
	if (kingP<56 && kingP%8<7){
	for (int i = kingP+9; i<64 && i%8!=0 ;i+=9){ //checks Diagonal up & right
		if (board[i]== queen[turn]|| board[i] == knight[turn] || board[i] == pawn[turn] || board[i] == rook[turn]|| board[i] == bishop[turn]){
			break;
		}
		if (board[i]== queen[0-(turn-1)] && moveMonitor(board, 0-(turn-1), queen[0-(turn-1)], i, kingP)){
			return 1;

		}
		if ( board[i]== bishop[0-(turn-1)] && moveMonitor(board, 0-(turn-1), bishop[0-(turn-1)], i, kingP)){
			return 1;
		}
	}
	}
	if (kingP>7 && kingP%8>0){
	for (int i = kingP-9; i>=0 && i%8!=7 ;i-=9){ //checks Diagonal down & left
		if (board[i]== queen[turn]|| board[i] == knight[turn] || board[i] == pawn[turn] || board[i] == rook[turn]|| board[i] == bishop[turn]){
			break;
		}

		if (board[i]== queen[0-(turn-1)] && moveMonitor(board, 0-(turn-1), queen[0-(turn-1)], i, kingP)){
			return 1;

		}
		if ( board[i]== bishop[0-(turn-1)] && moveMonitor(board, 0-(turn-1), bishop[0-(turn-1)], i, kingP)){
			return 1;
		}
	}
	}
	if (kingP<56 && kingP%8>0){
	for (int i = kingP+7; i<64 && i%8!=7 ;i+=7){ //checks Diagonal up & left
		if (board[i]== queen[turn]|| board[i] == knight[turn] || board[i] == pawn[turn] || board[i] == rook[turn]|| board[i] == bishop[turn]){
			break;
				}
		if (board[i]== queen[0-(turn-1)] && moveMonitor(board, 0-(turn-1), queen[0-(turn-1)], i, kingP)){
			return 1;

		}
		if ( board[i]== bishop[0-(turn-1)] && moveMonitor(board, 0-(turn-1), bishop[0-(turn-1)], i, kingP)){
			return 1;
		}
	}
	}
	if (kingP>7 && kingP%8>0){
	for (int i = kingP-7; i>=0 && i%8!=0 ;i-=7){ //checks Diagonal down & right
		if (board[i]== queen[turn]|| board[i] == knight[turn] || board[i] == pawn[turn] || board[i] == rook[turn]|| board[i] == bishop[turn]){
			break;
				}
		if (board[i]== queen[0-(turn-1)] && moveMonitor(board, 0-(turn-1), queen[0-(turn-1)], i, kingP)){
			return 1;

		}
		if ( board[i]== bishop[0-(turn-1)] && moveMonitor(board, 0-(turn-1), bishop[0-(turn-1)], i, kingP)){
			return 1;
		}
	}
	}
	return 0;
}


/**
 * check if the king is threatened from the opponent's knight. if true, return 1. otherwise return 0.
 */
int checkKnight(int turn, int kingP, int board[]){
	//printf("checkinKnight\n");
	if (kingP <48 && kingP%8<7 && board[kingP+17] == knight[0-(turn-1)]){
		return 1;
	}
	if (kingP <56 && kingP%8<6 && board[kingP+10] == knight[0-(turn-1)]){
		return 1;
	}
	if (kingP <48 && kingP%8>0 && board[kingP+15] == knight[0-(turn-1)]){
		return 1;
	}
	if (kingP <56 && kingP%8>1 && board[kingP+6] == knight[0-(turn-1)]){
		return 1;
	}
	if (kingP >7 && kingP%8<6 && board[kingP-6] == knight[0-(turn-1)]){
		return 1;
	}
	if (kingP >7 && kingP%8>1 && board[kingP-10] == knight[0-(turn-1)]){
		return 1;
	}
	if (kingP >15 && kingP%8<7 && board[kingP-15] == knight[0-(turn-1)]){
		return 1;
	}
	if (kingP >15 && kingP%8>0 && board[kingP-17] == knight[0-(turn-1)]){
		return 1;
	}
	//printf("no check\n");
	return 0;
}


/**
 * check if the king is threatened from one of the opponent's pawns. if true, return 1. otherwise return 0.
 */
int checkPawn(int turn, int kingP, int board[]){
	if ((turn==0 && kingP<56 && kingP%8<7 && board[kingP+9] == pawn[1]) ||(turn==1 && kingP>7 && kingP%8>0 && board[kingP-9] == pawn[0])){
		return 1;
	}
	if ((turn==0 && kingP<56 && kingP%8>0 && board[kingP+7] == pawn[1]) || (turn==1 && kingP>7 && kingP%8<7 && board[kingP-7]==pawn[0])){
		return 1;
	}
	return 0;
}
/**
 * input: current player, king's position and the board to check
 * returns 1 if there's a check and 0 otherwise.
 */
int checkBoard(int turn, int kingP, int board[]){ //check if there is a check
	int flag = 0;
	//printf("king is in %d\n", flag);
	flag = checkHorizontal(turn, kingP, board ) || flag;
	//printf("flag horizontal is in %d\n", flag);
	flag = checkVertical(turn, kingP, board) || flag ;
	//printf("flag vertical is in %d\n", flag);
	flag = checkDiagonal( turn, kingP, board)|| flag;
	//printf("flag diagonal is in %d\n", flag);
	flag = checkKnight( turn,  kingP, board)|| flag;
	//printf("flag knight is in %d\n", flag);
	flag = checkPawn(turn, kingP, board)|| flag;
	//printf("flag pawn is in %d\n", flag);
	//printf("**********************\n");
return flag;
}


//finds the index in the pieces array by the position and the piece value
int findPiece(int turn, int piece, int pos){
	printf("called me with turn: %d\n", turn);
	if (turn){ //black
		for (int i=0; i<16; i++){
			printf("black[%d][0]= %d, black[%d][1]= %d\n", i,black[i][0],i,black[i][1]);
			if (black[i][0] == piece && black[i][1] == pos){
				return i;
			}
		}
	}
	else{ //white
		for (int i=0; i<16; i++){
			printf("white[%d][0]= %d, white[%d][1]= %d\n", i,white[i][0],i,white[i][1]);
			if (white[i][0] == piece && white[i][1] == pos){
				return i;
			}
		}
	}
	return -1; //didn't find any. error
}

/**
 * update the moves array with the last move
 */
void updateMoves(int piece, int x, int y, int cut){
	printf("updating moves\n");
	if (last_move<5){
		last_move++;
		moves[last_move][0] = piece;
		moves[last_move][1] = x;
		moves[last_move][2] = y;
		moves[last_move][3] = cut;

	}
	else{ //moves list is full, need to push the least recent move
		for (int i=0; i<5; i++){
			for (int j=0; j<4; j++){
				moves[i][j] = moves[i+1][j];
			}
		}
		moves[5][0] = piece;
		moves[5][1] = x;
		moves[5][2] = y;
		moves[5][3] = cut;
	}
	return;
}

/**
 * make the move for the players. update the board the arrays and etc.
 */
int move(int board[],int turn, int x, int y, int piece){ //return 0 if move is not valid, make move if possible **updated by DB
	copyBoard(board,testBoard);
	//printBoard(board);
	printf("------\n");
	int flag = moveMonitor(board, turn, piece, x,y );
	//printBoard(board);
	printf("flag in monitor: %d\n",flag);
	if (flag == 1){
		//printf("x is %d\n", x);
		board[x]=0;
		int indP = findPiece(turn, piece, x);
		int index = -1;
		//printf("indP is: %d, turn= %d, piece= %d, x=%d\n", indP, turn, piece,x);
		//printf("!turn is %d\n", !turn);
		if (board[y]!=0){ //cutting the other opponent's piece
			index = findPiece(!turn, board[y], y);
			//printf("index is: %d, board[y] = %d, y= %d\n", index, board[y], y);

			if (turn){ //black- cutting white piece
				white[index][1] = -1; //not in the board anymore
			}
			else{ //white
				black[index][1] = -1;
			}
		}
		if (turn){ //black- cutting white piece
			black[indP][1] = y; //updates the new position in the array
		}
		else{ //white
			white[indP][1] = y;
		}
		board[y]=piece;

		if (game_mode == 1){
			updateMoves(piece, x, y,index);
		}
		printf("after move\n");
		printBoard(board);
		return flag;
	}
	return flag;
}

/**
 * search for the current opponent if he has any legal moves to do. return 1 if he has. otherwise- 0.
 */
int legalMove(int turn){
	//finding legal move if exists return 0. else- keep searching till you find or check id there is a tie.
	copyBoard(board,testBoard);
	int index=0;
	int b = 0;
	if (turn){ //black
		b = 10;
	}
	for (int i=0; i<8; i++){ //pawns
		if (turn){ //black
			index = black[i][1];
		}
		else{ //white
			index = white[i][1];
		}
		if((index>-1)&&(moveMonitor(board, turn,11+b,index,index+1)||moveMonitor(board, turn,11+b,index,index+2))){
			return 1;
		}
		if (!turn){ //white
			if ((index>-1)&&(moveMonitor(board, turn,11+b,index,index+9)||moveMonitor(board, turn,11+b,index,index+7))){
				return 1;
			}
		}
		if (turn){ //black
			if ((index>-1)&&(moveMonitor(board,turn,11+b,index,index-9)||moveMonitor(board, turn,11+b,index,index-7))){
				return 1;
			}
		}
	}
	for (int num=0; num<2; num++){ //knight
		if (turn){
			index = black[8+num][1];
		}
		else{ //white
			index = white[8+num][1];
		}
		if (index >-1){
			if (moveMonitor(board, turn, 13+b, index, index-6)||moveMonitor(board,turn, 13+b, index, index+6)||moveMonitor(board,turn, 13+b, index, index-10)||
					moveMonitor(board,turn, 13+b, index, index+10)||moveMonitor(board,turn, 13+b, index, index-15)||moveMonitor(board,turn, 13+b, index, index+15)||
					moveMonitor(board,turn, 13+b, index, index-17)||moveMonitor(board,turn, 13+b, index, index+17)){
				return 1;
			}
		}
	}
	for (int num=0; num<2; num++){ //bishop
		if (turn){ //black
			index = black[12+num][1];
		}
		else{ //white
			index = white[12+num][1];
		}
		if (index >-1){
			for (int ind=black[12+num][1]; ind<8; ind++){
				if (moveMonitor(board,turn, 14+b, index, index + 9*ind) || moveMonitor(board,turn,14+b, index, index - 9*ind)){
					return 1;
				}
				if (moveMonitor(board,turn, 14+b, index, index + 7*ind) || moveMonitor(board,turn, 14+b, index, index - 7*ind)){
					return 1;
				}
			}
		}
	}
	for (int num=0; num<2; num++){ //rook
		if (turn){ //black
			index = black[10+num][1];
		}
		else{ //white
			index = white[10+num][1];
		}
		if (index >-1){
			for (int ind=index; ind<8; ind++){
				if (moveMonitor(board,turn, 15+b, index, index + 8*ind) || moveMonitor(board,turn, 15+b, index, index - 8*ind)){ //horizontal
					return 1;
				}
				if (moveMonitor(board,turn, 15+b, index, index + ind) || moveMonitor(board,turn, 15+b, index, index - ind)){ //vertical
					return 1;
				}
			}
		}
	}
	//queen
	if (turn){ //black
		index = black[14][1];
	}
	else{ //white
		index = white[14][1];
	}
	if (index >-1){
		for (int ind=index; ind<8; ind++){
			if (moveMonitor(board,turn, 19+b, index, index + 8*ind) || moveMonitor(board,turn,19+b, index, index - 8*ind)){ //horizontal
				return 1;
			}
			if (moveMonitor(board,turn,19+b, index, index + ind) || moveMonitor(board,turn, 19+b, index, index - ind)){ //vertical
				return 1;
			}
			if (moveMonitor(board,turn, 19+b, index, index + 9*ind) || moveMonitor(board,turn, 19+b, index, index - 9*ind)){ //diagonal
				return 1;
			}
			if (moveMonitor(board,turn, 19+b, index, index + 7*ind) || moveMonitor(board,turn, 19+b, index, index - 7*ind)){ //diagonal
				return 1;
			}
		}
	}
	//king
	if (turn){ //black
		b = 1000;
		index = black[15][1];
		printf("king's pos is- %d\n",index);
	}
	else{ //white
		index = white[15][1];
	}
	if (index >-1){
		if (index+1<64){
			if (moveMonitor(board,turn, 1000+b, index, index + 1)){
				return 1;
			}
		}
		if (index-1>-1){
			if (moveMonitor(board,turn, 1000+b, index, index - 1)){
				return 1;
			}
		}
		if (index<56){
			if (moveMonitor(board,turn, 1000+b, index, index + 8)){
				return 1;
			}
		}
		if (index>7){
			if (moveMonitor(board,turn, 1000+b, index, index - 8)){
				return 1;
			}
		}
		if (index<56 && index%8 < 7){ //diagonal from right
			if (moveMonitor(board,turn, 1000+b, index, index + 9) || moveMonitor(board,turn, 1000+b, index, index - 7)){
				return 1;
			}
		}
		if (index>7 && index%8 > 0){ //diagonal from left
			if (moveMonitor(board,turn, 1000+b, index, index - 9) || moveMonitor(board,turn, 1000+b, index, index + 7)){
				return 1;
			}
		}
	}
	return 0; //no legal moves at all
}

///**
// * checks if it's a tie. when the player doesn't have any legal moves, but the king is not threatened by the opponent (no "check").
// * return 1 if true.
// */
//int isTie(int turn){
//	if (legalMove(turn)){
//		return 0; //there is legal - no tie
//	}
//	if (checkBoard(turn)){
//		return 0;
//	}
//	return 1;
//}
//
///**
// * checks if it's a checkmate. the king is threatened by the opponent ("check") and it king cannot be saved (there are no legal moves).
// * return 1 if true.
// */
//int isCheckMate(int turn){
//	if (legalMove(turn)){
//		return 0; //there is legal move- no tie
//	}
//	if (checkBoard(turn)){
//		return 1;
//	}
//	return 0;
//}

//int kingLegalMove(int turn,int index){
//	int b =0;
//	if (turn){ //black
//		b = 1000;
//	}
//	if (moveMonitor(testBoard,turn, 1000+b, index, index + 1)||moveMonitor(testBoard,turn, 1000+b, index, index - 1)){
//		printf("709\n");
//		return 1;
//	}
//	if (moveMonitor(testBoard,turn, 1000+b, index, index + 8)||moveMonitor(testBoard,turn, 1000+b, index, index - 8)){
//		printf("713\n");
//		return 1;
//	}
//	if (moveMonitor(testBoard,turn, 1000+b, index, index + 9)||moveMonitor(testBoard,turn, 1000+b, index, index - 9)){
//		printf("717\n");
//		return 1;
//	}
//	if (moveMonitor(testBoard,turn, 1000+b, index, index + 7)||moveMonitor(testBoard,turn, 1000+b, index, index - 7)){
//		return 1;
//	}
//	return 0;
//}



/**
 * checks if it's a checkmate. the king is threatened by the opponent ("check") and it king cannot be saved (there are no legal moves).
 * return 1 if true.
 * checks if it's a tie. when the player doesn't have any legal moves, but the king is not threatened by the opponent (no "check").
 * return 0 if true.
 * otherwise return -1
 */
int CheckMateOrTie(int turn){
	int pos = 0;
	int state = 0;
	if (turn == 0){
		pos = white[15][1]; //king's position
	}
	else {
		pos = black[15][1]; //king's position
	}
	state = checkBoard(turn, pos, board); //there's a check
	if (legalMove(turn)){ //there is legal move
		return -1;
	}
	if (state && !legalMove(turn)){ //check and there is'nt any legal move- checkmate
		return 1;
	}
	else{ //no check and there isn't any legal move- a tie
		return 0;
	}
}


int computer_move(int color){
	//calculating the best move
	minmax(board,game_difficulty,color, -INT_MAX, + INT_MAX, true);
	int index;
	//if there is a capture
	if (compMove[2]!=0){ //there is a capture
		if (color==1){ //user is white
				index = findPiece(0, compMove[2], compMove[1]); //white array
				white[index][1]=-1; //updates the array
		}
		else{ //user is black
			index = findPiece(1, compMove[2], compMove[1]); //black array
			black[index][1]=-1; //updates the array
		}
	}

	//update last moves array
	updateMoves(board[compMove[0]], compMove[0], compMove[1], index);

	//update the board
	board[compMove[1]] = board[compMove[0]];
	board[compMove[0]]= 0;

	//update the computer's array
	if (color==1){ //black
		index = findPiece(1, board[compMove[1]], compMove[0]); //black array
		black[index][1]=compMove[1]; //updates the array
	}
	else{ //white
		index = findPiece(0, board[compMove[1]], compMove[0]); //white array
		white[index][1]=compMove[1]; //updates the array
	}

	//printing the message move
	char* piece;
	int piece_val = moves[last_move][0]; //take the piece's val by the moves array the last_move that was made by computer
	if (piece_val%10==1){ //pawn
		piece = "pawn";
	}
	else if (piece_val%10==4){ //bishop
		piece = "bishop";
	}
	else if (piece_val%10==5){ //rook
		piece = "rook";
	}
	else if (piece_val%10==3){ //knight
		piece = "knight";
	}
	else if (piece_val%10==9){ //queen
		piece = "queen";
	}
	else if (piece_val%10==0){ //king
		piece = "king";
	}
	int position = moves[last_move][1]; //old position
	int new_pos = moves[last_move][2];	//new position
	int fx = position/8 +1;
	int fy = position%8;
	char char_fy = intToCharCol(fy);
	int tx = new_pos/8 +1;
	int ty = new_pos%8;
	char char_ty = intToCharCol(ty);
	printf("Computer: move %s at <%d,%c> to <%d,%c>\n", piece, fx, char_fy, tx, char_ty);
	if (color==0 && game_mode==1){ //&& game_color==0){ //1-player mode and it was the computer turn that has white color
		if (checkBoard(1, black[15][1],board)){ //there is a check
			printf("Check!\n");
		}
	}
	else if (color==1 && game_mode==1){ //&& game_color==1){ //1-player mode and it was the computer turn that has black color
		if (checkBoard(0, white[15][1],board)){ //there is a check
			printf("Check!\n");
		}
	}
	if (CheckMateOrTie(!color)==1){ //a checkmate
		if (color==0){ //white
			printf("Checkmate! white player wins the game\n");
		}
		else{ //black
			printf("Checkmate! black player wins the game\n");
		}
		return 0;
	}
	else if (CheckMateOrTie(!color)==0){ //a tie
		printf("The game is tied\n");
		return 0;
	}
	return 1;
	}






/**
 * calls the move function
 */
int manage_move(int turn, int x,int y,int piece)
{
	copyBoard(board, testBoard);
	//printBoard(testBoard);
	int flag = move(board,turn,x,y,piece);
	return flag;
}


/**
 * finds the king's position on the board by the color
 */
int findKing(int color, int board[]){
	for (int i=0; i<64; i++){
		if (color){ //black
			if (board[i]==2000){
				return i;
			}
		}
		else{ //white
			if (board[i]==1000){
				return i;
			}
		}
	}
	return -1; //if didn't find the king in the board- error
}



/**
 * check if it's legal move.
 * args: who's turn, which piece, the current position, the wish position
 * return 1: if true. 0: otherwise.
 */
int moveMonitor(int board[] ,int turn, int piece, int x, int y){ //check what if x==y?????
	if (y < 0 || y > 63){ //no need this check?
		return 0;
	}
	//printf("move start is\n");
	//printBoard(board);
	int kingPos;
	if (!turn){ //white. check if there isn't a piece in the desire position with the same color
		if (piece == 1000){ //check moving the king
			kingPos = y;
		}
		else{
			kingPos = findKing(0,board);
		}
		if ((board[y] > 10 && board[y] < 20) || (board[y]==1000)){ //no need this check?
			return 0;
		}

	}
	else{ //black
		if (piece == 2000){
			kingPos = y;
		}
		else{
			kingPos = findKing(1,board);
		}
		if ((board[y] > 20 && board[y] < 30) || (board[y]==2000)){ //no need this check?
			return 0;
		}
	}
	//printf("moveMonitor try the move: %d\n",y);
	copyBoard(board,testBoard);
	//printf("after copy:\n");
	//printBoard(board);
	testBoard[y] = piece;
	testBoard[x] = 0;
	//printf("test board:\n");
	//printBoard(testBoard); //for test
	//printf("the board:\n");
	//printBoard(board);
	int checkb=checkBoard(turn,kingPos, testBoard);
	//printf("checkBoard is %d\n",checkb);
	if (checkb==1){ //need to check if the move is legal and does't bring to check
		copyBoard(board,testBoard); //copy and reset the testBoard
		return 0;
	}
	copyBoard(board,testBoard);
		if ((piece == 11 && !turn) || (piece == 21 && turn)){ //pawn
			//printf("wtf turn is %d and board[y] is %d y is %d x is %d\n", turn,board[y],y,x);
			if ((x+8==y) &&(!turn) &&(board[y]==0)){
				return 1;
			}
			if ((x-8==y) &&(turn)&&(board[y]==0)){ //no cutting
				return 1;
			}
			if (((x-16==y)&&(turn))||((x+16==y)&&(!turn))){
				if(((x<=15)&&(x>=8)&&(!turn)&&(board[y]==0))||((x<=55)&&(x>=48)&&(turn)&&(board[y]==0))) { //starting position
					if (((board[x+8]==0)&&(!turn))||((board[x-8]==0)&&(turn))){
						return 1;
					}
				}
			}
			if (((((x+9==y)&&(x%8<7)&&(x<56))||((x+7==y)&&(x%8>0)&&(x<56)))&&(!turn))||((((x-9==y)&&(x%8>0)&&(x>7))||((x-7==y)&&(x%8<7)&&(x>7)))&&(turn))){ //Capturing: one diagonal step forward
				if (((((board[y]>=21 && board[y]<=29)||(board[y]==2000)))&&(!turn))||((((board[y]>=11 && board[y]<=19)||(board[y]==1000)))&&(turn)))
				{
					return 1;
				}
			}
			return 0;
	}
	if ((piece == 13 && !turn)|| (piece == 23 && turn)){ //knight
		if (moveKnight(x,y)){
			return 1;
		}
		return 0;
	}
	if ((piece == 14 && !turn) || (piece == 24 && turn)){ //bishop
		if (moveBishop(x,y)){
			return 1;
		}
		return 0;
	}
	if ((piece == 15 && !turn) || (piece == 25 && turn)){ //rook
		if (moveRook(x,y)){
			return 1;
		}
		return 0;
	}
	if ((piece == 19 && !turn) || (piece == 29 && turn)){ //queen
		if (moveQueen(x,y)){
			return 1;
		}
		return 0;
	}
	if ((piece == 1000 && !turn) || (piece == 2000 && turn)){ //rook
		if (moveKing(x,y)){
			return 1;
		}
		return 0;
	}
	return 0;
}



///**
// * check if it's legal move.
// * args: who's turn, which piece, the current position, the wish position
// * return 1: if true. 0: otherwise.
// */
//int moveMonitor(int board[] ,int turn, int piece, int x, int y){ //check what if x==y?????
//	if (y < 0 || y > 63){ //no need this check?
//		return 0;
//	}
//	int kingPos;
//	if (!turn){ //white. check if there isn't a piece in the desire position with the same color
//		if (piece == 1000){ //check moving the king
//			kingPos = y;
//		}
//		else{
//			kingPos = findKing(0,board);
//		}
//		if ((board[y] > 10 && board[y] < 20) || (board[y]==1000)){ //no need this check?
//			return 0;
//		}
//
//	}
//	else{ //black
//		if (piece == 2000){
//			kingPos = y;
//		}
//		else{
//			kingPos = findKing(1,board);
//		}
//		if ((board[y] > 20 && board[y] < 30) || (board[y]==2000)){ //no need this check?
//			return 0;
//		}
//	}
//	//printf("moveMonitor try the move: %d\n",y);
//	copyBoard(board,testBoard);
//	testBoard[y] = piece;
//	testBoard[x] = 0;
//	//printBoard(testBoard); //for test
//	int checkb=checkBoard(turn,kingPos, testBoard);
//	//printf("checkBoard is %d\n",checkb);
//	if (checkb==1){ //need to check if the move is legal and does't bring to check
//		copyBoard(board,testBoard); //copy and reset the testBoard
//		return 0;
//	}
//	copyBoard(board,testBoard);
//	printf("&********\n");
//	printBoard(board);
//	if ((piece == 11 && !turn) || (piece == 21 && turn)){ //pawn
//		printf("wtf turn is %d and board[y] is %d y is %d x is %d\n", turn,board[y],y,x);
//		if ((x+8==y) &&(!turn) &&(board[y]==0)){
//			return 1;
//		}
//		if ((x-8==y) &&(turn)&&(board[y]==0)){ //no cutting
//			return 1;
//		}
//		if (((x-16==y)&&(turn))||((x+16==y)&&(!turn))){
//			if(((x<=15)&&(x>=8)&&(!turn)&&(board[y]==0))||((x<=55)&&(x>=48)&&(turn)&&(board[y]==0))) { //starting position
//				if (((board[x+8]==0)&&(!turn))||((board[x-8]==0)&&(turn))){
//					return 1;
//				}
//			}
//		}
//		if (((((x+9==y)&&(x%8<7))||((x+7==y)&&(x%8>0)))&&(!turn))||((((x-9==y)&&(x%8>0))||((x-7==y)&&(x%8<7)))&&(turn))){ //Capturing: one diagonal step forward
//			if (((((board[y]>=21 && board[y]<=29)||(board[y]==2000)))&&(!turn))||((((board[y]>=11 && board[y]<=19)||(board[y]==1000)))&&(turn)))
//			{
//				return 1;
//			}
//		}
//		return 0;
//	}
//	if ((piece == 13 && !turn)|| (piece == 23 && turn)){ //knight
//		if (moveKnight(x,y)){
//			return 1;
//		}
//		return 0;
//	}
//	if ((piece == 14 && !turn) || (piece == 24 && turn)){ //bishop
//		if (moveBishop(x,y)){
//			return 1;
//		}
//		return 0;
//	}
//	if ((piece == 15 && !turn) || (piece == 25 && turn)){ //rook
//		if (moveRook(x,y)){
//			return 1;
//		}
//		return 0;
//	}
//	if ((piece == 19 && !turn) || (piece == 29 && turn)){ //queen
//		if (moveQueen(x,y)){
//			return 1;
//		}
//		return 0;
//	}
//	if ((piece == 1000 && !turn) || (piece == 2000 && turn)){ //rook
//		if (moveKing(x,y)){
//			return 1;
//		}
//		return 0;
//	}
//	return 0;
//}




/**
 * undo the last move of the game.
 */
void undo(int turn){
	int piece =	moves[last_move][0];
	int after = moves[last_move][2];
	int index = findPiece(turn, piece, moves[last_move][2]);
	printf("undo turn is %d. last move is for %d from %d to %d cut was %d\n",turn,moves[last_move][0],moves[last_move][2],moves[last_move][1],moves[last_move][3]);
	printBoard(board);

	if (turn){ //black
		black[index][1] = moves[last_move][1];
		printf("black[%d][%d]= %d\n", moves[last_move][3],1, black[index][1]);
	}
	else{ //white
		white[index][1] = moves[last_move][1];
		printf("white[%d][%d]= %d\n", moves[last_move][3],1, white[index][1]);
	}
	board[(moves[last_move][1])] = piece; //return to last position
	int cut = moves[last_move][3];
	if (cut > -1){ //the last move included cutting
		if (turn){ //black
			white[cut][1] = after;
			board[after] = white[cut][0]; //update the board with the piece that was cut
		}
		else{ //white
			black[cut][1] = after;
			board[after] = black[cut][0];
		}
	}
	else{ //no cut
		board[after]=0;
	}
	printBoard(board);
	int tx = after/8 +1;
	int fx = (moves[last_move][1])/8 +1;
	int ty = (after)%8;
	int fy = (moves[last_move][1])%8;
	char char_ty = intToCharCol(ty);
	char char_fy = intToCharCol(fy);
	if (turn){ //black
		printf("Undo move for player black : <%d,%c> -> <%d,%c>\n", tx, char_ty, fx,char_fy);
	}
	else{ //white
		printf("Undo move for player white : <%d,%c> -> <%d,%c>\n", tx, char_ty, fx,char_fy);
	}
	//delete the last move
	for (int i=0; i<4; i++){
		moves[last_move][i] = -1;
	}
	last_move -= 1;
	return;
}



int game(){
	int cnt=-1;
//	int one_player=1;
//	if (game_mode==2){
//		one_player=0; //2-players mode
//	}
	//int endgame=0;
	int turn=0; //starts always with white color (notice that 1 suppose represent white color.)
	int move=0;
	int error=0;
	char moveComm[1024];
	//initialize(board);
	do{
		//printBoard(board); //for test
		cnt++;
		//printf("\n");
		//printEnterMove(turn);
		if (!error){
			printBoard(board);
		}
		if((turn==0 && game_mode==2) || (turn==0 && game_mode==1 && game_color==1)){ //white: 2-players or 1-player and
			printf("white player - enter your move:\n");						//the user has white color and it his turn.
		}
		else if ((turn==1 && game_mode==2) || (turn==1 && game_mode==1 && game_color==0)){ //black: 2-players or 1-player and
			printf("white player - enter your move:\n");						//the user has black color and it his turn.
			printf("black player - enter your move:\n");
		}
		else if ((turn==0 && game_mode==1 && game_color==0) || (turn==1 && game_mode==1 && game_color==1)){ //1-player and it's
			printf("computer_move call\n");
			computer_move(turn);							//white's turn and the computer has white color or it's black's
			turn = !turn;									//turn and the computer has black color.
			continue;
		}
		fflush(stdout);
		fgets(moveComm,sizeof(moveComm),stdin);
		printf("%s\n",moveComm ); //for test
		CHCommand command = chParserPraseLine(moveComm);
		if (command.cmd == CH_quit){ //quit
			printf("Exiting...\n");
			return 0;
		}
		else if (command.cmd == CH_invalid_line){
			printf("invalid command\n");
			error=1;
			continue;
		}
		else if (command.cmd == CH_save &&( command.validArg =1)){
			saveFile(getFileName(command.str_path), turn,  game_mode,  game_difficulty,  game_color,  board);
		}
		else if (command.cmd == CH_reset){
			printf("Restarting...\n");
			initialize(board);
			//need to return to setting state
			setting_state();
			return 0;
		}
		else if (command.cmd == CH_undo){
			if (game_mode == 2){
				printf("Undo command not avaialbe in 2 players mode\n");
				error=1;
				continue;
			}
			else if (moves[0][0] == -1){ //empty list and 1 player
				printf("Empty history, move cannot be undone\n");
				error=1;
				continue;
			}
			undo(!turn);
			undo(turn);

		}
		else if (command.cmd == CH_move){ //move
			int x1 = command.fx;
			int y1 = command.fy;
			int x2 = command.tx;
			int y2 = command.ty;
			if (x1<0 || x1>7 || x2<0 || x2>7 || y1==-1|| y2==-1){
				printf("Invalid position on the board\n");
				error=1;
				continue;
			}
			int comb_x =8*x1+y1;
			int comb_y =8*x2+y2;
			printf("x1: %d, x2: %d, y1: %d, y2: %d\n", x1,x2,y1,y2);
			if (turn==0 ){ //white
				if(board[comb_x]==0||board[comb_x]==2000||(int)(board[comb_x]/10)==2){
					printf("The specified position does not contain your piece\n");
					error=1;
					continue;
				}
			}
			else { //black
				if(board[comb_x]==0||board[comb_x]==1000||(int)(board[comb_x]/10)==1){
					printf("The specified position does not contain your piece\n");
					error=1;
					continue;
				}
			}
			int piece=board[comb_x];
				printf("from: %d\n",comb_x);
				printf("to: %d\n",comb_y);
			move = manage_move(turn,comb_x,comb_y,piece);
			if (move == 0){
				printf("Illegal move\n");
				error=1;
				continue;
			}
			if (CheckMateOrTie(!turn)==1){ //a checkmate
				if (turn==0){ //white
					printf("Checkmate! white player wins the game\n");
					return 0;

				}
				else{ //black
					printf("Checkmate! black player wins the game\n");
					return 0;
				}
				return 0;
			}
			else if (CheckMateOrTie(!turn)==0){ //a tie
				printf("The game is tied\n");
				return 0;
			}
			if (turn==0 && game_mode==2){ //was white's turn in 2-players mode
				if (checkBoard(turn, white[15][1],board)){ //there is a check
					printf("Check: black King is threatend!\n");
				}
			}
			else if (turn==1 && game_mode==2){ //was black's turn in 2-players mode
				if (checkBoard(turn, black[15][1], board)){ //there is a check
					printf("Check: white King is threatend!\n");
				}
			}
			else if (turn==0 && game_mode==1 && game_color==0){ //1-player mode and it was the computer turn that has white color
				if (checkBoard(turn, white[15][1],board)){ //there is a check
					printf("Check!\n");
				}
			}
			else if (turn==1 && game_mode==1 && game_color==1){ //1-player mode and it was the computer turn that has black color
				if (checkBoard(turn, black[15][1],board)){ //there is a check
					printf("Check!\n");
				}
			}
			printf("moves[%d][0]=%d,moves[%d][1]=%d,moves[%d][2]=%d,moves[%d][3]=%d\n",cnt,moves[cnt][0],cnt,moves[cnt][1],cnt,moves[cnt][2],cnt,moves[cnt][3]);//test
			turn = !turn;
			printf("turn now is: %d\n", turn); //for test
			error=0;
			}
		}
	while(1);
	//while(endgame==0 && (strcmp(moveComm, "end")==0));
return 0;
}



/**
 * gets the color and a board and returns an 3D array with all the legal moves for the color.
 * options[0][0]== #legal moves that was found
 * for (i>0) : options[i][0] = the val of the piece that suppose to be capture if exists. 0- otherwise
 * options[i][1] = origin position
 * options[i][2] = the new position
 */
int** options(int turn, int board[]){
	//copyBoard(board,testBoard);
	int index=0;
	int b = 0;
	int cnt = 1; //pointer to the leagal_moves's index
	int** legal_moves = (int**)malloc(sizeof(int*)*2);
	legal_moves[0] = (int*)malloc(3 * sizeof(int)); //for the length of the array
	legal_moves[1] = (int*)malloc(3 * sizeof(int));
//	if (turn){ //black
//		flipBoard(board, flip_board);
//		board = flip_board;
//		printBoard(board);
//	}
	for (int i=0; i< 64; i++){
		if (turn==1){ //black
			b = 10;
			//printf("b is %d\n", b);
		}
		//printf("board[%d]== %d\n",i, board[i]);
		index = i;
		if (board[i] ==0){
			continue;
		}
		//printf("@ b is %d\n", b);
		//printf("val is %d\n", b+11);
		if ((board[i])==((11+b))) {  //pawn
			//printf("pawn is %d\n", i);
				if(((moveMonitor(board, turn,11+b,index,index-8))&&turn) || ((moveMonitor(board, turn,11+b,index,index+8))&&!turn)){
					legal_moves[cnt][1] = index;
					if (!turn){ //white
						legal_moves[cnt][0] = board[index+8];
						legal_moves[cnt][2] = index+8;
					}
					else{ //black
						legal_moves[cnt][0] = board[index-8];
						legal_moves[cnt][2] = index-8;
					}
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
				if ((moveMonitor(board, turn,11+b,index,index-16)&&turn)||(moveMonitor(board, turn,11+b,index,index+16)&&!turn)){
					legal_moves[cnt][1] = index;
					if (!turn){ //white pawn
						legal_moves[cnt][0] = board[index+16];
						legal_moves[cnt][2] = index+16;
					}
					else{ //black pawn
						legal_moves[cnt][0] = board[index-16];
						legal_moves[cnt][2] = index-16;
					}
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
				if (!turn){ //white- capturing
					if (moveMonitor(board, turn,11+b,index,index+9)){
						legal_moves[cnt][1] = index;
						legal_moves[cnt][2] = index+9;
						legal_moves[cnt][0] = board[index+9];
						cnt+=1;
						legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
						legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
					}
					if ((moveMonitor(board, turn,11+b,index,index+7))){
						legal_moves[cnt][1] = index;
						legal_moves[cnt][2] = index+7;
						legal_moves[cnt][0] = board[index+7];
						cnt+=1;
						legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
						legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
					}
				}
				if (turn){ //black- capturing
					if (moveMonitor(board, turn,11+b,index,index-9)){
						legal_moves[cnt][1] = index;
						legal_moves[cnt][2] = index-9;
						legal_moves[cnt][0] = board[index-9];
						cnt+=1;
						legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
						legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
					}
					if ((moveMonitor(board, turn,11+b,index,index-7))){
						legal_moves[cnt][1] = index;
						legal_moves[cnt][2] = index-7;
						legal_moves[cnt][0] = board[index-7];
						cnt+=1;
						legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
						legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
					}
				}
				continue;
		}
		if (board[i]==(13+b)){ //knight
			//printf("knight is %d\n", i);
//				if (index%8 >1 && index<56){
				if (moveMonitor(board,turn, 13+b, index, index+6)){
					legal_moves[cnt][0] = board[index+6];
					legal_moves[cnt][1] = index;
					legal_moves[cnt][2] = index+6;
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
//				}
//				if (index%8 >1 && index>7){
				if(moveMonitor(board,turn, 13+b, index, index-10)){
					legal_moves[cnt][0] = board[index-10];
					legal_moves[cnt][1] = index;
					legal_moves[cnt][2] = index-10;
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
//				}
//				if (index%8 <6 && index>7){
					if (moveMonitor(board, turn, 13+b, index, index-6)){
							legal_moves[cnt][0] = board[index-6];
							legal_moves[cnt][1] = index;
							legal_moves[cnt][2] = index-6;
							cnt+=1;
							legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
							legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
					}
//				}
//				if (index%8 <6 && index<56){
					if (moveMonitor(board,turn, 13+b, index, index+10)){
							legal_moves[cnt][0] = board[index+10];
							legal_moves[cnt][1] = index;
							legal_moves[cnt][2] = index+10;
							cnt+=1;
							legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
							legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
					}
//				}
//				if (index>15 && index%8<7){
				if (moveMonitor(board,turn, 13+b, index, index-15)){
					legal_moves[cnt][0] = board[index-15];
					legal_moves[cnt][1] = index;
					legal_moves[cnt][2] = index-15;
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
//				}
//				if (index<48 && index%8 >0){
				if (moveMonitor(board,turn, 13+b, index, index+15)){
					legal_moves[cnt][0] = board[index+15];
					legal_moves[cnt][1] = index;
					legal_moves[cnt][2] = index+15;
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
//				}
//				if (index>15 && index%8>0){
				if (moveMonitor(board,turn, 13+b, index, index-17)){
					legal_moves[cnt][0] = board[index-17];
					legal_moves[cnt][1] = index;
					legal_moves[cnt][2] = index-17;
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
//				}
//				if (index<48 && index%8<7){
				if (moveMonitor(board,turn, 13+b, index, index+17)){
					legal_moves[cnt][0] = board[index+17];
					legal_moves[cnt][1] = index;
					legal_moves[cnt][2] = index+17;
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
//				}
		continue;
		}
		 if (board[i]==(14+b)){ //bishop
			 //printf("bishop is %d\n", i);
			 for (int ind = i+9; ind<64 && ind%8!=0 ;ind+=9){ //checks Diagonal up & right
			 		if (moveMonitor(board,turn, 14+b, index, ind)){
			 			legal_moves[cnt][0] = board[ind];
			 			legal_moves[cnt][1] = index;
			 			legal_moves[cnt][2] = ind;
			 			cnt+=1;
			 			legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
			 			legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
			 			}
			 	}
			 	for (int ind = i-9; ind>=0 && ind%8!=7 ;ind-=9){ //checks Diagonal down & left
			 			if (moveMonitor(board,turn, 14+b, index, ind)){
			 				legal_moves[cnt][0] = board[ind];
			 				legal_moves[cnt][1] = index;
			 				legal_moves[cnt][2] = ind;
			 				cnt+=1;
			 				legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
			 				legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
			 						}
			 			}
			 			for (int ind = i+7; ind<64 && ind%8!=7 ;ind+=7){ //checks Diagonal up & left
			 				if (moveMonitor(board,turn, 14+b, index, ind)){
			 						legal_moves[cnt][0] = board[ind];
			 						legal_moves[cnt][1] = index;
			 						legal_moves[cnt][2] = ind;
			 						cnt+=1;
			 						legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
			 						legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
			 										}
			 			}
			 			for (int ind = i-7; ind>=0 && ind%8!=0 ;ind-=7){ //checks Diagonal down & right
			 				if (moveMonitor(board,turn, 14+b, index, ind)){
			 						legal_moves[cnt][0] = board[ind];
			 						legal_moves[cnt][1] = index;
			 						legal_moves[cnt][2] = ind;
			 						cnt+=1;
			 						legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
			 						legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
			 				}
			 			}
//
			continue;
		 }
		if (board[i]==(15+b)){ //rook
			// printf("rook is %d\n", i);
			 for (int ind = i+8; ind<64 ;ind+=8){ //checks vertical up
				 if (moveMonitor(board,turn, 15+b, index, ind)){
				 	//printf("########1");
				 	legal_moves[cnt][0] = board[ind];
				 	legal_moves[cnt][1] = index;
				 	legal_moves[cnt][2] = ind;
				 	cnt+=1;
				 	legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
				 	legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				 	}
			 }
			for (int ind = i-8; ind>=0 ;ind-=8){ //checks vertical down
				//printf("ind is %d\n", ind);
				if (moveMonitor(board,turn, 15+b, index, ind)){
					legal_moves[cnt][0] = board[ind];
					legal_moves[cnt][1] = index;
					legal_moves[cnt][2] = ind;
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
			}
			for (int ind  = i+1; ind <64 ;ind ++){ //checks horizontal to the right
				if ((ind)%8 == 0){
					break;
				}
				if (moveMonitor(board,turn, 15+b, index, ind)){
					printf(" index is %d, ind is %d\n",index,ind  );
					legal_moves[cnt][0] = board[ind];
					legal_moves[cnt][1] = index;
					legal_moves[cnt][2] = ind;
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
			}
			for (int ind = i-1; ind>=0 ;ind--){ //checks horizontal to the left
				if ((ind)%8 == 7){
					break;
				}
				if (moveMonitor(board,turn, 15+b, index, ind)){
					legal_moves[cnt][0] = board[ind];
					legal_moves[cnt][1] = index;
					legal_moves[cnt][2] = ind;
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
			}
				continue;
			}
		 if (board[i]==(19+b)){ //queen
			// printf("queen is %d\n", i);
			 for (int ind = i+8; ind<64 ;ind+=8){ //checks vertical up
				 if (moveMonitor(board,turn, 19+b, index, ind)){
				 	legal_moves[cnt][0] = board[ind];
				 	legal_moves[cnt][1] = index;
				 	legal_moves[cnt][2] = ind;
				 	cnt+=1;
				 	legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
				 	legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				 	}
			 }
			for (int ind = i-8; ind>=0 ;ind-=8){ //checks vertical down
				//printf("ind is %d\n", ind);
				if (moveMonitor(board,turn, 19+b, index, ind)){
					legal_moves[cnt][0] = board[ind];
					legal_moves[cnt][1] = index;
					legal_moves[cnt][2] = ind;
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
			}
			for (int ind  = i+1; ind <64 ;ind ++){ //checks horizontal to the right
				if ((ind)%8 == 0){
					break;
				}
				if (moveMonitor(board,turn, 19+b, index, ind)){
					legal_moves[cnt][0] = board[ind];
					legal_moves[cnt][1] = index;
					legal_moves[cnt][2] = ind;
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
			}
			for (int ind = i-1; ind>=0 ;ind--){ //checks horizontal to the left
				if ((ind)%8 == 7){
					break;
				}
				if (moveMonitor(board,turn, 19+b, index, ind)){
					legal_moves[cnt][0] = board[ind];
					legal_moves[cnt][1] = index;
					legal_moves[cnt][2] = ind;
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
			}
			for (int ind = i+9; ind<64 && ind%8!=0 ;ind+=9){ //checks Diagonal up & right
				if (moveMonitor(board,turn, 19+b, index, ind)){
						legal_moves[cnt][0] = board[ind];
						legal_moves[cnt][1] = index;
						legal_moves[cnt][2] = ind;
						cnt+=1;
						legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
						legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
			}
			}
			for (int ind = i-9; ind>=0 && ind%8!=7 ;ind-=9){ //checks Diagonal down & left
				if (moveMonitor(board,turn, 19+b, index, ind)){
						legal_moves[cnt][0] = board[ind];
						legal_moves[cnt][1] = index;
						legal_moves[cnt][2] = ind;
						cnt+=1;
						legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
						legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
						}
			}
			for (int ind = i+7; ind<64 && ind%8!=7 ;ind+=7){ //checks Diagonal up & left
				if (moveMonitor(board,turn, 19+b, index, ind)){
						legal_moves[cnt][0] = board[ind];
						legal_moves[cnt][1] = index;
						legal_moves[cnt][2] = ind;
						cnt+=1;
						legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
						legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
										}
			}
			for (int ind = i-7; ind>=0 && ind%8!=0 ;ind-=7){ //checks Diagonal down & right
				if (moveMonitor(board,turn, 19+b, index, ind)){
						legal_moves[cnt][0] = board[ind];
						legal_moves[cnt][1] = index;
						legal_moves[cnt][2] = ind;
						cnt+=1;
						legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
						legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
										}
			}
			continue;
			}
		if (turn){
			b = 1000;
		}
		if (board[i]==(1000+b)){ //king
			//printf("king is %d\n", i);
			if (index+1<64){
				if (moveMonitor(board,turn, 1000+b, index, index + 1)){
						legal_moves[cnt][0] = board[index + 1];
						legal_moves[cnt][1] = index;
						legal_moves[cnt][2] = index + 1;
						cnt+=1;
						legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
						legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
					}
			}
			if (index-1>-1){
				if (moveMonitor(board,turn, 1000+b, index, index - 1)){
					legal_moves[cnt][0] = board[index - 1];
					legal_moves[cnt][1] = index;
					legal_moves[cnt][2] = index - 1;
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
			}
			if (index<56){
				if (moveMonitor(board,turn, 1000+b, index, index + 8)){
					legal_moves[cnt][0] = board[index - 8];
					legal_moves[cnt][1] = index;
					legal_moves[cnt][2] = index + 8;
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
			}
			if (index>7){
				if (moveMonitor(board,turn, 1000+b, index, index - 8)){
					legal_moves[cnt][0] = board[index - 8];
					legal_moves[cnt][1] = index;
					legal_moves[cnt][2] = index - 8;
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
			}
			if (index<56 && index%8 < 7){ //diagonal from right
				if (moveMonitor(board,turn, 1000+b, index, index + 9)){
					legal_moves[cnt][0] = board[index + 9];
					legal_moves[cnt][1] = index;
					legal_moves[cnt][2] = index + 9;
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
				if (moveMonitor(board,turn, 1000+b, index, index - 7)){
					legal_moves[cnt][0] = board[index -7];
					legal_moves[cnt][1] = index;
					legal_moves[cnt][2] = index - 7;
					cnt+=1;
					legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
					legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
				}
				}
				if (index>7 && index%8 > 0){ //diagonal from left
					if (moveMonitor(board,turn, 1000+b, index, index - 9)){
						legal_moves[cnt][0] = board[index - 9];
						legal_moves[cnt][1] = index;
						legal_moves[cnt][2] = index - 9;
						cnt+=1;
						legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
						legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
					}
					if (moveMonitor(board,turn, 1000+b, index, index + 7)){
						legal_moves[cnt][0] = board[index + 7];
						legal_moves[cnt][1] = index;
						legal_moves[cnt][2] = index + 7;
						cnt+=1;
						legal_moves = (int**)realloc(legal_moves,(cnt+1)*sizeof(int*));
						legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
					}
				}
				continue;
			}
	}
	free(legal_moves[cnt]); //was a extra realloc that need to be free.
//		for (int j=0;j<cnt;j++ ){
//			for (int ind=0; ind<3; ind++){
//				printf("legal_moves[%d][%d]== %d\n",j,ind,legal_moves[j][ind]);
//		}
//
//	}
	if ( (cnt-1) == 0){
		legal_moves[0][0] = 0;
	}
	else{
		legal_moves[0][0] = (cnt-1); //the actual number of legal moves
	}
	legal_moves[0][1] = turn;
	printf("num of legal moves: %d\n",legal_moves[0][0]);
	return legal_moves;

}





//
//
//void options(int turn, int board[]){
//	//finding legal move if exists return 0. else- keep searching till you find or check id there is a tie.
//	copyBoard(board,testBoard);
//	int index=0;
//	int b = 0;
//	int cnt = 0; //pointer to the leagal_moves's index
//	int** legal_moves = (int**)malloc(sizeof(int*));
//	*legal_moves = (int*)malloc(3 * sizeof(int));
//	if (turn){ //black
//		b = 10;
//	}
//	for (int i=0; i<8; i++){ //pawns
//		if (turn){ //black
//			index = black[i][1];
//		}
//		else{ //white
//			index = white[i][1];
//		}
//		if((index>-1)&&(moveMonitor(board, turn,11+b,index,index+1))){
//			cnt++;
//			legal_moves = (int**)realloc(legal_moves,cnt*sizeof(int*));
//			legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
//			legal_moves[cnt][0] = turn;
//			legal_moves[cnt][1] = index;
//			legal_moves[cnt][2] = index+1;
//		}
//		if (moveMonitor(board, turn,11+b,index,index+2)){
//			cnt++;
//			legal_moves = (int**)realloc(legal_moves,cnt);
//			legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
//			legal_moves[cnt][0] = turn;
//			legal_moves[cnt][1] = index;
//			legal_moves[cnt][2] = index+2;
//		}
//	}
//	for (int num=0; num<2; num++){ //knight
//		if (turn){
//			index = black[8+num][1];
//		}
//		else{ //white
//			index = white[8+num][1];
//		}
//		if (index >-1){
//			if (moveMonitor(board, turn, 13+b, index, index-6)){
//				cnt++;
//				legal_moves = (int**)realloc(legal_moves,cnt);
//				legal_moves[cnt] = (int*)malloc(3 * sizeof(int));
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index-6;
//
//			}
//			if (moveMonitor(board,turn, 13+b, index, index+6)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index+6;
//				cnt++;
//			}
//
//			if(moveMonitor(board,turn, 13+b, index, index-10)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index-10;
//				cnt++;
//			}
//			if (moveMonitor(board,turn, 13+b, index, index+10)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index+10;
//				cnt++;
//			}
//			if (moveMonitor(board,turn, 13+b, index, index-15)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index-15;
//				cnt++;
//			}
//			if (moveMonitor(board,turn, 13+b, index, index+15)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index+15;
//				cnt++;
//			}
//			if (moveMonitor(board,turn, 13+b, index, index-17)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index-17;
//				cnt++;
//			}
//			if (moveMonitor(board,turn, 13+b, index, index+17)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index+17;
//				cnt++;
//			}
//
//			}
//		}
//	for (int num=0; num<2; num++){ //bishop
//		if (turn){ //black
//			index = black[12+num][1];
//		}
//		else{ //white
//			index = white[12+num][1];
//		}
//		if (index >-1){
//			for (int ind=black[12+num][1]; ind<8; ind++){
//				if (moveMonitor(board,turn, 14+b, index, index + 9*ind)){
//					legal_moves[cnt][0] = turn;
//					legal_moves[cnt][1] = index;
//					legal_moves[cnt][2] = index + 9*ind;
//					cnt++;
//				}
//				if (moveMonitor(board,turn,14+b, index, index - 9*ind)){
//					legal_moves[cnt][0] = turn;
//					legal_moves[cnt][1] = index;
//					legal_moves[cnt][2] = index - 9*ind;
//					cnt++;
//				}
//				if (moveMonitor(board,turn, 14+b, index, index + 7*ind)){
//					legal_moves[cnt][0] = turn;
//					legal_moves[cnt][1] = index;
//					legal_moves[cnt][2] = index + 7*ind;
//					cnt++;
//				}
//				if (moveMonitor(board,turn, 14+b, index, index - 7*ind)){
//					legal_moves[cnt][0] = turn;
//					legal_moves[cnt][1] = index;
//					legal_moves[cnt][2] = index - 7*ind;
//					cnt++;
//				}
//			}
//		}
//	}
//	for (int num=0; num<2; num++){ //rook
//		if (turn){ //black
//			index = black[10+num][1];
//		}
//		else{ //white
//			index = white[10+num][1];
//		}
//		if (index >-1){
//			for (int ind=index; ind<8; ind++){
//				if (moveMonitor(board,turn, 15+b, index, index + 8*ind)){
//					legal_moves[cnt][0] = turn;
//					legal_moves[cnt][1] = index;
//					legal_moves[cnt][2] = index + 8*ind;
//					cnt++;
//				}
//				if (moveMonitor(board,turn, 15+b, index, index - 8*ind)){ //horizontal
//					legal_moves[cnt][0] = turn;
//					legal_moves[cnt][1] = index;
//					legal_moves[cnt][2] = index - 8*ind;
//					cnt++;
//				}
//				if (moveMonitor(board,turn, 15+b, index, index + ind)){
//					legal_moves[cnt][0] = turn;
//					legal_moves[cnt][1] = index;
//					legal_moves[cnt][2] = index + ind;
//					cnt++;
//				}
//				if (moveMonitor(board,turn, 15+b, index, index - ind)){ //vertical
//					legal_moves[cnt][0] = turn;
//					legal_moves[cnt][1] = index;
//					legal_moves[cnt][2] = index - ind;
//					cnt++;
//				}
//			}
//		}
//	}
//	//queen
//	if (turn){ //black
//		index = black[14][1];
//	}
//	else{ //white
//		index = white[14][1];
//	}
//	if (index >-1){
//		for (int ind=index; ind<8; ind++){
//			if (moveMonitor(board,turn, 19+b, index, index + 8*ind)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index + 8*ind;
//				cnt++;
//			}
//			if (moveMonitor(board,turn,19+b, index, index - 8*ind)){ //horizontal
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index - 8*ind;
//				cnt++;
//			}
//			if (moveMonitor(board,turn,19+b, index, index + ind)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index + ind;
//				cnt++;
//			}
//			if (moveMonitor(board,turn, 19+b, index, index - ind)){ //vertical
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index - ind;
//				cnt++;
//			}
//			if (moveMonitor(board,turn, 19+b, index, index + 9*ind)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index + 9*ind;
//				cnt++;
//			}
//			if (moveMonitor(board,turn, 19+b, index, index - 9*ind)){ //diagonal
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index - 9*ind;
//				cnt++;
//			}
//			if (moveMonitor(board,turn, 19+b, index, index + 7*ind)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index + 7*ind;
//				cnt++;
//			}
//			if (moveMonitor(board,turn, 19+b, index, index - 7*ind)){ //diagonal
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index - 7*ind;
//				cnt++;
//			}
//		}
//	}
//	//king
//	if (turn){ //black
//		b = 1000;
//		index = black[15][1];
//		printf("king's pos is- %d\n",index);
//	}
//	else{ //white
//		index = white[15][1];
//	}
//	if (index >-1){
//		if (index+1<64){
//			if (moveMonitor(board,turn, 1000+b, index, index + 1)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index + 1;
//				cnt++;
//			}
//		}
//		if (index-1>-1){
//			if (moveMonitor(board,turn, 1000+b, index, index - 1)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index - 1;
//				cnt++;
//			}
//		}
//		if (index<56){
//			if (moveMonitor(board,turn, 1000+b, index, index + 8)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index + 8;
//				cnt++;
//			}
//		}
//		if (index>7){
//			if (moveMonitor(board,turn, 1000+b, index, index - 8)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index - 8;
//				cnt++;
//			}
//		}
//		if (index<56 && index%8 < 7){ //diagonal from right
//			if (moveMonitor(board,turn, 1000+b, index, index + 9)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index + 9;
//				cnt++;
//			}
//			if (moveMonitor(board,turn, 1000+b, index, index - 7)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index - 7;
//				cnt++;
//			}
//		}
//		if (index>7 && index%8 > 0){ //diagonal from left
//			if (moveMonitor(board,turn, 1000+b, index, index - 9)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index - 9;
//				cnt++;
//			}
//			if (moveMonitor(board,turn, 1000+b, index, index + 7)){
//				legal_moves[cnt][0] = turn;
//				legal_moves[cnt][1] = index;
//				legal_moves[cnt][2] = index + 7;
//				cnt++;
//			}
//		}
//	}
//}
//


/**
 *
 */
void setting_state(){
	initialize(board); //initialize all the game states and reset the game setting.
	char comm[1024];
	int valid;
	do{
	printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
	fflush(stdout);
	fgets(comm,sizeof(comm),stdin);
	CHCommand command = chParserPraseLine(comm);
	if (command.cmd == CH_start){ //start the game
		game();
	}
	else if (command.cmd == CH_game_mode){
		if (command.arg == 1){
			game_mode = 1;
			printf("Game mode is set to 1 player\n");
		}
		else if (command.arg == 2){
			game_mode = 2;
			printf("Game mode is set to 2 players\n");
		}
		else{
			printf("Wrong game mode\n");
		}
		continue;

	}
	else if (command.cmd == CH_print_setting){
				printf("SEETINGS:\nGAME_MODE: %d\nDIFFICULRT_LVL: %d\nUSER_CLR: %d\n", game_mode, game_difficulty, game_color);
	}
	else if (command.cmd == CH_difficulty){
		if (game_mode != 1){
			printf("invalid command\n");
			continue;
		}
		else {
			if (command.validArg){
				if (command.arg == 5){
					printf("Expert level not supported, please choose a value between 1 to 4:\n");
					continue;
				}
				game_difficulty = command.arg;
			}
			else{
				printf("Wrong difficulty level. The value should be between 1 to 5\n");
			}
			continue;
		}
	}
	else if (command.cmd == CH_user_color){
		if (game_mode != 1){
			printf("invalid command\n");
			continue;
		}
		else{
			if (command.validArg){
				game_color = command.arg;
				continue;
			}
			else{
				printf("invalid command\n");
				continue;
			}
		}
	}
	else if (command.cmd == CH_load){
		if (command.validArg == -1){
			printf("invalid command\n");
		}
		else{
			valid =loadFile(getFileName(command.str_arg));
			if(valid){ //succeed open thest file
				continue;
			}
			else{ // couldn't succeed open the file
				printf("Eror: File doesn't exist or cannot be opened\n");
				continue;
			}
		}
	}
	else if (command.cmd == CH_default){
		initialize(board);
	}
	else if (command.cmd == CH_quit){ //quit
		printf("Exiting...\n");
		return ;
	}
	//need to add default command and print setting command
	}
	while(1);
}




//
//int game()
//{
//int endgame=0;
//int turn=0;
//int move=0;
//int error=0;
//char moveComm[1024];
//initialize(board);
//	do{
//		//printf("\n");
//		//printEnterMove(turn);
//		if (!error){
//			printBoard(board);
//		}
//		if(turn==0) //white
//		{
//			printf("white player - enter your move:\n");
//			fflush(stdout);
//			gets(moveComm);
//			printf("%s\n",moveComm );
//			CHCommand command = chParserPraseLine(moveComm);
//			if (command.cmd == CH_quit){ //quit
//				printf("Exiting...\n");
//				return 0;
//			}
//			else if (command.cmd == CH_move){
//				int x1 = command.fx;
//				int y1 = command.fy;
//				int x2 = command.tx;
//				int y2 = command.ty;
//				if (x1<0 || x1>7 || x2<0 || x2>7 || y1==-1|| y2==-1){
//					printf("Invalid position on the board\n");
//					error=1;
//					continue;
//				}
//				int comb_x =8*x1+y1;
//				int comb_y =8*x2+y2;
//				printf("x1: %d, x2: %d, y1: %d, y2: %d\n", x1,x2,y1,y2);
//				if(board[comb_x]==0||board[comb_x]==2000||(int)(board[comb_x]/10)==2)
//				{
//					printf("The specified position does not contain your piece\n");
//					error=1;
//					continue;
//				}
//				int piece=board[comb_x];
//
//				printf("from: %d\n",comb_x);
//				printf("to: %d\n",comb_y);
//				move = manage_move(0,comb_x,comb_y,piece);
//				if (move == 0){
//					printf("Illegal move\n");
//					error=1;
//					continue;
//				}
//				if (CheckMateOrTie(turn)==1){ //a checkmate
//					printf("Checkmate! white player wins the game\n");
//					endgame =1;
//					return 0;
//				}
//				else if (CheckMateOrTie(turn)==0){ //a tie
//					printf("The game is tied\n");
//					endgame =1;
//					return 0;
//				}
//				else if (checkBoard(turn, white[15][1],board)){ //there is a check
//					printf("Check: black King is threatend!\n");
//				}
//				printBoard(board);
//				turn =1;
//				error=0;
//			}
//		}
//		else
//		{
//			printf("black player - enter your move:\n");
//			fflush(stdout);
//			gets(moveComm);
//			//scanf("%s",moveComm);
//			printf("%s\n",moveComm );
//			CHCommand command = chParserPraseLine(moveComm); //need to handle if invalid command
//			if (command.cmd == CH_quit){ //quit
//				printf("Exiting...\n");
//				return 0;
//			}
//			else if (command.cmd == CH_move){
//				int x1 = command.fx;
//				int y1 = command.fy;
//				int x2 = command.tx;
//				int y2 = command.ty;
//				if (x1<0 || x1>7 || x2<0 || x2>7 || y1==-1|| y2==-1){
//					printf("Invalid position on the board\n");
//					error=1;
//					continue;
//				}
//				int comb_x= 8*x1+y1;
//				int comb_y= 8*x2+y2;
//				printf("x1: %d, x2: %d, y1: %d, y2: %d\n", x1,x2,y1,y2);
//				if(board[comb_x]==0||board[comb_x]==1000||(int)(board[comb_x]/10)==1)
//				{
//					printf("The specified position does not contain your piece\n");
//					error=1;
//					continue;
//				}
//				int piece=board[comb_x];
//				move = manage_move(1,comb_x,comb_y,piece);
//				if (move == 0){
//					printf("Illegal move\n");
//					error=1;
//					continue;
//				}
//				if (CheckMateOrTie(turn)==1){ //a checkmate
//					printf("Checkmate! black player wins the game\n");
//					endgame =1;
//					return 0;
//				}
//				else if (CheckMateOrTie(turn)==0){ //a tie
//					printf("The game is tied\n");
//					endgame =1;
//					return 0;
//				}
//				else if (checkBoard(turn, black[15][1],board)){ //there is a check
//					printf("Check: white King is threatend!\n");
//				}
//				printBoard(board);
//				turn =0;
//				error=0;
//			}
//
//		}
//	}while(1);
//	//while(endgame==0 && (strcmp(moveComm, "end")==0));
//return 0;
//}
