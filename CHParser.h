/*
 * CHParser.h
 *
 *  Created on: 2 בספט 2017
 *      Author: User
 */

#ifndef CHPARSER_H_
#define CHPARSER_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STRING_MAX_SIZE 1024

typedef enum{
	CH_game_mode ,
	CH_difficulty,
	CH_user_color ,
	CH_load,
	CH_default,
	CH_print_setting,
	CH_quit,
	CH_start,
	CH_invalid_line,
	CH_move,
	CH_reset,
	CH_undo,
	CH_save
} CH_COMMAND;

//a new type that is used to encapsulate a parsed line
typedef struct command_t {
	CH_COMMAND cmd;
	int validArg; //is set to 1 if the line contains a valid argument
	int arg ;
	char* str_arg;
	char* str_path;
	int fx ;
	int fy ;
	int tx ;
	int ty ;
} CHCommand;

int string_length(const char *s);

CHCommand chParserPraseLine(const char* str);
char intToCharCol(int col);


#endif /* CHPARSER_H_ */
