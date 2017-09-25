/*
 * CHessGameWin.h
 *
 *  Created on: 19 בספט׳ 2017
 *      Author: User
 */

#ifndef GRAPHICS_CHESSGAMEWIN_H_
#define GRAPHICS_CHESSGAMEWIN_H_
#include "CHessWin.h"
#include "CHessGameManager.h"
#include "../CHessGame.h"

typedef enum {
	SP_GAME_EVENT_X_WON,
	SP_GAME_EVENT_O_WON,
	SP_GAME_EVENT_TIE,
	SP_GAME_EVENT_QUIT,
	SP_GAME_MAIN_M,
	SP_GAME_RESTART,
	SP_GAME_SAVE,
	SP_GAME_LOAD,
	SP_GAME_UNDO,
	SP_GAME_EVENT_INVALID_ARGUMENT,
	SP_GAME_EVENT_NONE
} SP_GAME_EVENT;

typedef struct{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* bgTexture;
	SDL_Texture* menuTexture;
	SDL_Texture* kingbTexture;
	SDL_Texture* kingwTexture;
	SDL_Texture* queenbTexture;
	SDL_Texture* queenwTexture;
	SDL_Texture* rookbTexture;
	SDL_Texture* rookwTexture;
	SDL_Texture* knightbTexture;
	SDL_Texture* knightwTexture;
	SDL_Texture* bishopbTexture;
	SDL_Texture* bishopwTexture;
	SDL_Texture* pawnbTexture;
	SDL_Texture* pawnwTexture;
	SDL_Texture* restartTexture;
	SDL_Texture* saveTexture;
	SDL_Texture* loadTexture;
	SDL_Texture* undoTexture;
	SDL_Texture* mainmTexture;
	SDL_Texture* exitTexture;

	int stateMachine; //0 dragging, 1 released
	int from;
	int to;

	//chess* game;
}SPGameWin;

SPGameWin* spGameWindowCreate();
void spGameWindowDraw(SPGameWin*);
void spGameWindowDestroy(SPGameWin*);
SP_GAME_EVENT spGameWindowHandleEvent(SPGameWin* src, SDL_Event* event);
int isClickOnLoadG(int x, int y);
void spGameWindowHide(SPGameWin* src);

void updateWinBoard(SPGameWin* src, int piece, int fx, int fy,int tx, int ty);

#endif
