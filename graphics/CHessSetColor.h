/*
 * CHessSetColor.h
 *
 *  Created on: 23 בספט׳ 2017
 *      Author: User
 */

#ifndef GRAPHICS_CHESSSETCOLOR_H_
#define GRAPHICS_CHESSSETCOLOR_H_

#include "CHessWin.h"
#include "../CHessGame.h"
#include <SDL.h>

typedef enum {
	SP_GAME_SET_COLOR_BACK, SP_GAME_SET_COLOR_START, SP_GAME_SET_COLOR_BLACK, SP_GAME_SET_COLOR_WHITE,SP_GAME_SET_COLOR_INVALID_ARGUMENT, SP_GAME_SET_COLOR_NONE, SP_GAME_SET_COLOR_EXIT
} SP_GAME_SET_COLOR_EVENT;

typedef struct {
	//SDL_Window* window;
	SDL_Window* gameSetColorWindow;
	SDL_Renderer* mainRenderer;
	SDL_Texture* startTexture;
	SDL_Texture* backTexture;
	SDL_Texture* whiteTexture;
	SDL_Texture* blackTexture;
	int bold; //the color's button that is clicked
	SDL_Texture* windowTexture;
} SPsetColorWin;

SPsetColorWin* spGameSetColorWindowCreate();
void spGameSetColorWindowDestroy(SPsetColorWin* src);
void spGameSetColorWindowDraw(SPsetColorWin* src);
void spGameSetColorlWindowHide(SPsetColorWin* src);
void spGameSetColorWindowShow(SPsetColorWin* src) ;
SP_GAME_SET_COLOR_EVENT spGameSetColorWindowHandleEvent(SPsetColorWin* src, SDL_Event* event);




#endif /* GRAPHICS_CHESSSETCOLOR_H_ */
