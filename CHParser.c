/*
 * CHParser.c
 *
 *  Created on: 2 בספט 2017
 *      Author: User
 */


#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "CHParser.h"

char columns[8] = {'A','B','C','D','E','F','G','H'};

/**
 * returns the length of the string arg
 */
int string_length(const char *s) {
   int c = 0;
   while(*(s+c))
      c++;

   return c;
}

/**
 * Checks if a specified string represents a valid integer. It is recommended
 * to use this function prior to calling the standard library function atoi.
 *
 * @return
 * true if the string represents a valid integer, and false otherwise.
 */
bool chParserIsOneInt(const char* str) {
	if ((str[0] < '0' || str[0] > '9')  || string_length(str)!=1 ) {
		return false;
	}

	return true;
	}

/**
 * gets a letter represents the column and returns the int value for the column
 * returns -1 otherwise
 */
int findColumn(char col){
	for (int i=0; i<8; i++){
		if (col==columns[i]){
			return i;
		}
	}
	return -1;
}

/**
 * gets an int represents the column and returns the char value for the column
 * returns -1 otherwise
 */
char intToCharCol(int col){
	char charCol = columns[col];
	return charCol;
}

//CHCommand
CHCommand chParserPraseLine(const char* str){
	CHCommand new;
	new.str_arg=NULL;
	new.str_path= NULL;
	CH_COMMAND camNames[12] = {CH_game_mode, CH_difficulty, CH_user_color, CH_load, CH_default,CH_print_setting, CH_quit, CH_start, CH_move,CH_reset,CH_undo, CH_save};
	char* camNamestr[12] = {"game_mode", "difficulty", "user_color", "load", "default", "print_setting", "quit", "start", "move", "reset", "undo", "save"};
	int len;
	len = string_length(str);
	char dst[len+1];
	strcpy(dst, str);
	strncpy(dst, str, sizeof dst - 1);
	dst[len] = '\0';
	char* pch;
	//char* pch = ((char*)malloc(sizeof(char)));
	pch = strtok(dst, " \n\t");
	 char*  check[5];
	for (int i = 0; i<5; i++){
		check[i] = NULL;
	}
	check[0] = pch;
	int i = 1;
	while (i<4)
	{
		if (pch == NULL){
			break;
		}
		pch = strtok (NULL,  " \n\t");
		check[i] = pch;
			i++;
			}
		int ind;
		int flag = 0;
	for(ind = 0; ind<12; ind ++){
		if (ind != 8 && check[2] != NULL){
			continue;
		}

		if(strcmp(camNamestr[ind], check[0])==0){
			flag = 1;
			if(ind ==0 && check[1]!= NULL ){
					if((check[1][0] == '1' || check[1][0] == '2') &&  chParserIsOneInt(check[1])){
						new.cmd = camNames[ind];
						new.validArg = 1;
						new.arg =  atoi(check[1]);
					}
					else{
						new.cmd = camNames[ind];
						new.validArg = 0;
						new.arg = -1;
						}
					}
			else if(ind ==1 && check[1]!= NULL){
						if((check[1][0] == '1' || check[1][0] == '2' || check[1][0] == '3' || check[1][0] == '4' || check[1][0] == '5')  &&  chParserIsOneInt(check[1])){
							new.cmd = camNames[ind];
							new.validArg = 1;
							new.arg = atoi(check[1]);
						}
						else{
							new.cmd = camNames[ind];
							new.validArg = 0;
							new.arg = -1;
							}
						}
				else if(ind ==2&& check[1]!= NULL){
						if((check[1][0] == '0' || check[1][0] == '1') &&  chParserIsOneInt(check[1]) ){
							new.cmd = camNames[ind];
							new.validArg = 1;
							new.arg = atoi(check[1]);
						}
						else{
							new.cmd = camNames[ind];
							new.validArg = 0;
							new.arg = -1;
							}
						}
				else if(ind ==3){
					if (check[1]!= NULL && check[2]==NULL){
						//char tmp[string_length(check[1]+1)];
						new.cmd = camNames[ind];
						new.validArg = 1;
						new.str_arg= (char *) malloc((string_length(check[1]))+1);
						strcpy(new.str_arg,check[1]);
					}
					else{
						new.cmd = camNames[ind];
						new.validArg = 0;
						new.arg = -1;
					}
				}
				else if(ind ==8){
					if ((check[4]== NULL)&& (check[3]!= NULL)&&(check[2]!= NULL)&&(check[1]!= NULL)&& (strcmp("to", check[2])==0)){
					new.cmd = camNames[ind];
					new.validArg = 1;
					new.fx= (check[1][1]- '0') -1; //convert index starting from 0
					new.fy = findColumn(check[1][3]); //returns -1 if the column isn't valid
					//new.fy= check[1][2]- '0';
					new.tx= (check[3][1]- '0') -1;
					new.ty= findColumn(check[3][3]);
					}
					else{
						new.cmd = camNames[ind];
						new.validArg = 0;
					}
				}
				else if(ind ==11){
					if (check[1]!= NULL && check[2]==NULL){
						//filepath = check[1];
						new.cmd = camNames[ind];
						new.validArg = 1;
						new.str_path=(char *) malloc((string_length(check[1]))+1);;
						strcpy( new.str_path, check[1]);
					}
					else{

					}
				}
				else{
					new.cmd = camNames[ind];
					new.validArg = 0;
					new.arg = -1;
					}
				break;
							}
	}
		if (flag ==0){
			new.cmd = CH_invalid_line;
			new.validArg = 0;
			new.arg = -1;
				}
		return new;
			}
