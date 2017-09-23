/*
 * CHessGameSetLevel.h
 *
 *  Created on: 22 בספט׳ 2017
 *      Author: User
 */

#ifndef GRAPHICS_CHESSGAMESETLEVEL_H_
#define GRAPHICS_CHESSGAMESETLEVEL_H_


#include "CHessWin.h"
#include "../CHessGame.h"
#include <SDL.h>

typedef enum {
	SP_GAME_SET_LEVEL_BACK, SP_GAME_SET_LEVEL_NEXT, SP_GAME_SET_LEVEL_1, SP_GAME_SET_LEVEL_2, SP_GAME_SET_LEVEL_3, SP_GAME_SET_LEVEL_4,
	SP_GAME_SET_LEVEL_5, SP_GAME_SET_LEVEL_INVALID_ARGUMENT, SP_GAME_SET_LEVEL_NONE, SP_GAME_SET_LEVEL_EXIT
} SP_GAME_SET_LEVEL_EVENT;

typedef struct {
	//SDL_Window* window;
	SDL_Window* gameSetLevelWindow;
	SDL_Renderer* mainRenderer;
	SDL_Texture* nextTexture;
	SDL_Texture* backTexture;
	SDL_Texture* level1Texture;
	SDL_Texture* level2Texture;
	SDL_Texture* level3Texture;
	SDL_Texture* level4Texture;
	//SDL_Texture* level5Texture;
	int bold; //the number of the slot that was clicked. 0- otherwise
	SDL_Texture* windowTexture;
	int level;
} SPsetLevelWin;

int isClickOnNext(int x, int y);
int isClickOnBackSet(int x, int y);
SPsetLevelWin* spGameSetLevelWindowCreate();
void spGameSetLevelWindowDestroy(SPsetLevelWin* src);
void spGameSetLevelWindowDraw(SPsetLevelWin* src);
void spGameSetLevelWindowHide(SPsetLevelWin* src);
void spGameSetLevelWindowShow(SPsetLevelWin* src) ;
SP_GAME_SET_LEVEL_EVENT spGameSetLevelWindowHandleEvent(SPsetLevelWin* src, SDL_Event* event);


#endif /* GRAPHICS_CHESSGAMESETLEVEL_H_ */
