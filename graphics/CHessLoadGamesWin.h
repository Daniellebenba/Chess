/*
 * CHessLoadGamesWin.h
 *
 *  Created on: 21 בספט׳ 2017
 *      Author: User
 */

#ifndef GRAPHICS_CHESSLOADGAMESWIN_H_
#define GRAPHICS_CHESSLOADGAMESWIN_H_

#include "CHessWin.h"
#include "../CHessGame.h"
#include <SDL.h>

typedef enum {
	SP_LOAD_GAMES_BACK, SP_LOAD_GAMES_LOAD, SP_LOAD_GAMES_SLOT_1, SP_LOAD_GAMES_SLOT_2, SP_LOAD_GAMES_SLOT_3, SP_LOAD_GAMES_SLOT_4,
	SP_LOAD_GAMES_SLOT_5, SP_LOAD_GAMES_INVALID_ARGUMENT, SP_LOAD_GAMES_NONE, SP_LOAD_GAMES_EXIT //?need all 5 slots or only one?
} SP_LOAD_GAMES_EVENT;

typedef struct {
	//SDL_Window* window;
	SDL_Window* loadGamesWindow;
	SDL_Renderer* mainRenderer;
	SDL_Texture* loadTexture;
	SDL_Texture* backTexture;
	SDL_Texture* slot1Texture;
	SDL_Texture* slot2Texture;
	SDL_Texture* slot3Texture;
	SDL_Texture* slot4Texture;
	SDL_Texture* slot5Texture;
	int bold; //the number of the slot that was clicked. 0- otherwise
	SDL_Texture* windowTexture;
} SPLoadGamesWin;

SPLoadGamesWin* spLoadGamesnWindowCreate();
void spLoadGamesWindowDestroy(SPLoadGamesWin* src);
void spLoadGamesWindowDraw(SPLoadGamesWin* src);
void spLoadGamesWindowHide(SPLoadGamesWin* src);
void spLoadGamesWindowShow(SPLoadGamesWin* src) ;
SP_LOAD_GAMES_EVENT spLoadGamesWindowHandleEvent(SPLoadGamesWin* src, SDL_Event* event);


#endif /* GRAPHICS_CHESSLOADGAMESWIN_H_ */
