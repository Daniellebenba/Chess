/*
 * CHessGameSetMode.h
 *
 *  Created on: 22 בספט׳ 2017
 *      Author: User
 */

#ifndef GRAPHICS_CHESSGAMESETMODE_H_
#define GRAPHICS_CHESSGAMESETMODE_H_

#include "CHessWin.h"
#include "../CHessGame.h"
#include <SDL.h>

typedef enum {
	SP_GAME_MODE_BACK, SP_GAME_MODE_NEXT, SP_GAME_MODE_START, SP_MODE_PLAYER_1, SP_MODE_PLAYER_2,
	 SP_GAME_MODE_INVALID_ARGUMENT, SP_GAME_MODE_NONE, SP_MODE_EXIT
} SP_GAME_MODE_EVENT;

typedef struct {
	//SDL_Window* window;
	SDL_Window* gameModelWindow;
	SDL_Renderer* mainRenderer;
	SDL_Texture* nextTexture;
	SDL_Texture* startTexture;
	SDL_Texture* backTexture;
	SDL_Texture* player1Texture;
	SDL_Texture* player2Texture;
	int leftB; //2 = start, 1 = next

	//SDL_Texture* level5Texture;
	int bold; //the number of the slot that was clicked. 0- otherwise
	SDL_Texture* windowTexture;
} SPModeWin;

SPModeWin* spGameModelWindowCreate();
void spGameModeWindowDestroy(SPModeWin* src);
void spGameModeWindowDraw(SPModeWin* src);
void spGameModeWindowHide(SPModeWin* src);
void spGameModeWindowShow(SPModeWin* src) ;
SP_GAME_MODE_EVENT spGameModeWindowHandleEvent(SPModeWin* src, SDL_Event* event);


#endif /* GRAPHICS_CHESSGAMESETMODE_H_ */
