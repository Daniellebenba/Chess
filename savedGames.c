/*
 * savedGames.c
 *
 *  Created on: 12 בספט׳ 2017
 *      Author: User
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "savedGames.h"
#include  "CHParser.h"

char* curr_turn_start = "\n\t<current_turn>";
char* curr_turn_end = "</current_turn>";
char* game_mode_start = "\n\t<game_mode>";
char* game_mode_end = "</game_mode>";
char* difficulty_start = "\n\t<difficulty>";
char* difficulty_end = "</difficulty>";
char* user_color_start = "\n\t<user_color>";
char* user_color_end = "</user_color>";
char* board_start = "\n\t<board>";
char* board_end = "\n\t</board>";
char* row_start = "\n\t\t<row_";
char* row_end = "</row_";

int saveFile(char *file_name, int current_turn, int mode, int difficulty, int color, int board[]) {
	printf("file name is %s\n", file_name);

	FILE * file = fopen(file_name, "w");
	if (file==NULL){
		printf("File cannot be created or modified\n");
		return 0;
	}
	int val = 0; //need to check error writing with val
	fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"); //write first line
	fprintf(file,"<game>");
	val = fputs(curr_turn_start, file);
	fprintf(file,"%d",current_turn);
	val = fputs(curr_turn_end, file);
	val = fputs(game_mode_start, file);
	fprintf(file,"%d",mode);
	val = fputs(game_mode_end, file);
	val = fputs(difficulty_start, file);
	fprintf(file,"%d",difficulty);
	val = fputs(difficulty_end, file);
	val = fputs(user_color_start, file);
	fprintf(file,"%d",color);
	val = fputs(user_color_end, file);
	val = fputs(board_start, file);
	int piece;
	for (int i=0; i<8; i++){
		val = fputs(row_start, file);
		val = fprintf(file,"%d>",i);
		for (int j=0; j<8; j++){ //write the row
			piece = board[i*8 + j];
				switch ( piece ) {
				case 1000:
					fprintf(file,"k");
					break;
				case 2000:
					fprintf(file,"K");
					break;
				case 11:
					fprintf(file,"p");
					break;
				case 21:
					fprintf(file,"P");
					break;
				case 13:
					fprintf(file,"n");
					break;
				case 23:
					fprintf(file,"N");
					break;
				case 14:
					fprintf(file,"b");
					break;
				case 24:
					fprintf(file,"B");
					break;
				case 15:
					fprintf(file,"r");
					break;
				case 25:
					fprintf(file,"R");
					break;
				case 19:
					fprintf(file,"q");
					break;
				case 29:
					fprintf(file,"Q");
					break;
				default:
					fprintf(file,"_");
					break;
				}
		}
		val = fputs(row_end, file);
		val = fprintf(file,"%d>",i);
	}
	fputs(board_end, file);
	fprintf(file,"\n</game>");
	fclose(file);
	return 0;
}



char* getFileName(char* path){ // flag is used for save or load. for save flag = 0 and for load flag =1
	const char ch = '\\';
	char* ret;
	ret = strrchr(path, ch);
	if (ret==NULL){
		ret = path;
	}
	else{
	ret++;
	}
	printf("ret is %s\n", ret);
	return ret;
 }



