/*
 * savedGames.h
 *
 *  Created on: 12 בספט׳ 2017
 *      Author: User
 */

#ifndef SAVEDGAMES_H_
#define SAVEDGAMES_H_
#include  "CHParser.h"

extern char* curr_turn_start;
extern char* curr_turn_end;
extern char* game_mode_start;
extern char* game_mode_end;
extern char* difficulty_start;
extern char* difficulty_end;
extern char* user_color_start;
extern char* user_color_end;
extern char* board_start;
extern char* board_end;
extern char* row_start;
extern char* row_end;


int saveFile(char *file_name, int current_turn, int mode, int difficulty, int color, int board[]);
char* getFileName(char* path);

#endif /* SAVEDGAMES_H_ */
