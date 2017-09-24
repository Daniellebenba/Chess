/*
 * CHessGameWin.c
 *
 *  Created on: 19 בספט׳ 2017
 *      Author: User
 */

#include "CHessGameWin.h"
#include <assert.h>
#include <stdio.h>



int isClickOnRestart(int x, int y) {
	if ((x >= 625 && x <= 775) && (y >= 50 && y <= 100)) {
		return 1;
	}

	return 0;
}

int isClickOnSave(int x, int y) {
	if ((x >= 625 && x <= 775) && (y >= 125 && y <= 175)) {
		return 1;
	}

	return 0;
}

int isClickOnLoadG(int x, int y) {
	if ((x >= 625 && x <= 775) && (y >= 200 && y <= 250)) {
		return 1;
	}

	return 0;
}

int isClickOnUndo(int x, int y) {
	if ((x >= 625 && x <= 775) && (y >= 275 && y <= 325)) {
		return 1;
	}

	return 0;
}

int isClickOnMainMenu(int x, int y) {
	if ((x >= 625 && x <= 775) && (y >= 425 && y <= 475)) {
		return 1;
	}

	return 0;
}
int isClickOnExitG(int x, int y) {
	if ((x >= 625 && x <= 775) && (y >= 500 && y <= 550)) {
		return 1;
	}

	return 0;
}

 void setPiece(SPGameWin* src, int i, int j, SDL_Rect rec)
 {
 	if (board[63- (i*8+j)] == 2000) {
 		SDL_RenderCopy(src->renderer, src->kingbTexture, NULL, &rec);
 	}
 	else if (board[63 - (i*8+j)] == 1000) {
 		SDL_RenderCopy(src->renderer, src->kingwTexture, NULL, &rec);
 	}
 	if (board[63-(i*8+j)] == 24) {
 		SDL_RenderCopy(src->renderer, src->bishopbTexture, NULL, &rec);
 	}
 	else if (board[63 -(i*8+j)] == 14) {
 		SDL_RenderCopy(src->renderer, src->bishopwTexture, NULL, &rec);
 	}
 	if (board[63-(i*8+j)] == 29) {

 		SDL_RenderCopy(src->renderer, src->queenbTexture, NULL, &rec);
 	}
 	else if (board[63 -(i*8+j)] == 19) {
 		SDL_RenderCopy(src->renderer, src->queewTexture, NULL, &rec);
 	}
 	if (board[63-(i*8+j)] == 25) {

 		SDL_RenderCopy(src->renderer, src->rookbTexture, NULL, &rec);
 	}
 	else if (board[63 -(i*8+j)] == 15) {
 		SDL_RenderCopy(src->renderer, src->rookwTexture, NULL, &rec);
 	}
 	if (board[63-(i*8+j)] == 21) {

 		SDL_RenderCopy(src->renderer, src->pawnbTexture, NULL, &rec);
 	}
 	else if (board[63 -(i*8+j)] == 11) {
 		SDL_RenderCopy(src->renderer, src->pawnwTexture, NULL, &rec);
 	}
 	if (board[63-(i*8+j)] == 23) {

 		SDL_RenderCopy(src->renderer, src->knightbTexture, NULL, &rec);
 	}
 	else if (board[63 -(i*8+j)] == 13) {
 		SDL_RenderCopy(src->renderer, src->knightwTexture, NULL, &rec);
 	}
 	return;
 }

 SDL_Texture* setPic(SPGameWin* src, char* path){
	SDL_Surface* loadingSurface = NULL;
	loadingSurface = SDL_LoadBMP(path );
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(src);
		return NULL ;
	}
	if (loadingSurface != NULL){
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	 SDL_Texture* texture = SDL_CreateTextureFromSurface(src->renderer, loadingSurface);
	SDL_FreeSurface(loadingSurface);
	return texture;
	}
}

SPGameWin* spGameWindowCreate() {
	SPGameWin* res = (SPGameWin*) calloc(sizeof(SPGameWin), sizeof(char));
	SDL_Surface* loadingSurface = NULL; //Used as temp surface
	if (res == NULL ) {
		printf("Couldn't create SPGameWin struct\n");
		return NULL ;
	}
//	res->game = spTicTacToeCreate();
//	if (res->game == NULL ) {
//		printf("Couldn't create game\n");
//		spGameWindowDestroy(res);
//		return NULL ;
//	}
	// Create an application window with the following settings:
	res->window = SDL_CreateWindow("Chess", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			800,                               // width, in pixels
			600,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	// Check that the window was successfully created
	if (res->window == NULL ) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->renderer = SDL_CreateRenderer(res->window, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->renderer == NULL ) {
		printf("Could not create a renderer: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}

	//Create a background texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/board.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->bgTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->bgTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it
	//Create menu texture:
		loadingSurface = SDL_LoadBMP("./graphics/images/menu.bmp");
		if (loadingSurface == NULL ) {
			printf("Could not create a surface: %s\n", SDL_GetError());
			spGameWindowDestroy(res);
			return NULL ;
		}
		res->menuTexture = SDL_CreateTextureFromSurface(res->renderer,
				loadingSurface);
		if (res->menuTexture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			spGameWindowDestroy(res);
			return NULL ;
		}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it
	//Create restart:
			loadingSurface = SDL_LoadBMP("./graphics/images/restart.bmp");
			if (loadingSurface == NULL ) {
				printf("Could not create a surface: %s\n", SDL_GetError());
				spGameWindowDestroy(res);
				return NULL ;
			}
			res->restartTexture = SDL_CreateTextureFromSurface(res->renderer,
					loadingSurface);
			if (res->restartTexture == NULL ) {
				printf("Could not create a restart: %s\n", SDL_GetError());
				spGameWindowDestroy(res);
				return NULL ;
			}
		SDL_FreeSurface(loadingSurface);
		//Create load:
				loadingSurface = SDL_LoadBMP("./graphics/images/load.bmp");
				if (loadingSurface == NULL ) {
					printf("Could not create a surface: %s\n", SDL_GetError());
					spGameWindowDestroy(res);
					return NULL ;
				}
				res->loadTexture = SDL_CreateTextureFromSurface(res->renderer,
						loadingSurface);
				if (res->loadTexture == NULL ) {
					printf("Could not create a load: %s\n", SDL_GetError());
					spGameWindowDestroy(res);
					return NULL ;
				}
			SDL_FreeSurface(loadingSurface);

	//Create save:
	loadingSurface = SDL_LoadBMP("./graphics/images/save.bmp");
	if (loadingSurface == NULL ) {
	printf("Could not create a surface: %s\n", SDL_GetError());
	spGameWindowDestroy(res);
		return NULL ;
	}
	res->saveTexture = SDL_CreateTextureFromSurface(res->renderer,
	loadingSurface);
	if (res->saveTexture == NULL ) {
	printf("Could not create a save: %s\n", SDL_GetError());
	spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
				//Create undo:
	loadingSurface = SDL_LoadBMP("./graphics/images/undo.bmp");
	if (loadingSurface == NULL ) {
	printf("Could not create a surface: %s\n", SDL_GetError());
	spGameWindowDestroy(res);
	return NULL ;
	}
	res->undoTexture = SDL_CreateTextureFromSurface(res->renderer,
	loadingSurface);
	if (res->undoTexture == NULL ) {
		printf("Could not create a restart: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create main menu:
	loadingSurface = SDL_LoadBMP("./graphics/images/mainmenu.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->mainmTexture = SDL_CreateTextureFromSurface(res->renderer,
	loadingSurface);
	if (res->mainmTexture == NULL ) {
		printf("Could not create a mainmenu: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
	return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create exit:
	loadingSurface = SDL_LoadBMP("./graphics/images/exit.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->exitTexture = SDL_CreateTextureFromSurface(res->renderer,
	loadingSurface);
	if (res->exitTexture == NULL ) {
		printf("Could not create a exit: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
	return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	res->kingbTexture =  setPic(res, "./graphics/images/kingb.bmp");
		if (res->kingbTexture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			spGameWindowDestroy(res);
			return NULL ;
		}
	res->kingwTexture =  setPic(res, "./graphics/images/kingw.bmp");
		if (res->kingwTexture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			spGameWindowDestroy(res);
			return NULL ;
		}
	res->bishopbTexture =  setPic(res, "./graphics/images/bishopb.bmp");
		if (res->bishopbTexture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			spGameWindowDestroy(res);
			return NULL ;
		}
	res->bishopwTexture =  setPic(res, "./graphics/images/bishopw.bmp");
		if (res->bishopwTexture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			spGameWindowDestroy(res);
			return NULL ;
		}
	res->queenbTexture =  setPic(res, "./graphics/images/queenb.bmp");
		if (res->queenbTexture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			spGameWindowDestroy(res);
			return NULL ;
		}
	res->queewTexture =  setPic(res, "./graphics/images/queenw.bmp");
		if (res->queewTexture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			spGameWindowDestroy(res);
			return NULL ;
		}
	res->knightbTexture =  setPic(res, "./graphics/images/Chess_ndt60.bmp");
		if (res->knightbTexture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			spGameWindowDestroy(res);
			return NULL ;
		}
	res->knightwTexture =  setPic(res, "./graphics/images/Chess_nlt60.bmp");
		if (res->knightwTexture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			spGameWindowDestroy(res);
			return NULL ;
		}
	res->rookbTexture =  setPic(res, "./graphics/images/rookb.bmp");
		if (res->rookbTexture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			spGameWindowDestroy(res);
			return NULL ;
		}
	res->rookwTexture=  setPic(res, "./graphics/images/rookw.bmp");
		if (res->rookwTexture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			spGameWindowDestroy(res);
			return NULL ;
		}
	res->pawnbTexture=  setPic(res, "./graphics/images/pawn.bmp");
		if (res->pawnbTexture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			spGameWindowDestroy(res);
			return NULL ;
		}
	res->pawnwTexture=  setPic(res, "./graphics/images/pawnw.bmp");
		if (res->rookwTexture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			spGameWindowDestroy(res);
			return NULL ;
		}
	return res;
}

void spGameWindowDestroy(SPGameWin* src) {
	if (!src) {
		return;
	}
	//spTicTacToeDestroy(src->game);
	if (src->kingwTexture != NULL ) {
		SDL_DestroyTexture(src->kingwTexture);
	}
	if (src->kingbTexture != NULL ) {
		SDL_DestroyTexture(src->kingbTexture);
	}
	if (src->bishopwTexture != NULL ) {
		SDL_DestroyTexture(src->bishopwTexture);
	}
	if (src->bishopbTexture != NULL ) {
		SDL_DestroyTexture(src->bishopbTexture);
	}
	if (src->queewTexture != NULL ) {
		SDL_DestroyTexture(src->queewTexture);
	}
	if (src->queenbTexture != NULL ) {
		SDL_DestroyTexture(src->queenbTexture);
	}
	if (src->bgTexture != NULL ) {
		SDL_DestroyTexture(src->bgTexture);
	}
	if (src->menuTexture != NULL ) {
			SDL_DestroyTexture(src->bgTexture);
		}
	if (src->restartTexture != NULL ) {
		SDL_DestroyTexture(src->restartTexture);
	}
	if (src->saveTexture != NULL ) {
		SDL_DestroyTexture(src->saveTexture);
	}
	if (src->loadTexture != NULL ) {
		SDL_DestroyTexture(src->loadTexture);
	}
	if (src->mainmTexture != NULL ) {
		SDL_DestroyTexture(src->mainmTexture);
	}
	if (src->exitTexture != NULL ) {
		SDL_DestroyTexture(src->exitTexture);
	}
	if (src->undoTexture != NULL ) {
		SDL_DestroyTexture(src->undoTexture);
	}
	if (src->renderer != NULL ) {
		SDL_DestroyRenderer(src->renderer);
	}

	if (src->window != NULL ) {
		SDL_DestroyWindow(src->window);
	}
	free(src);
}

void spGameWindowDraw(SPGameWin* src) {
	if(src == NULL){
		return;
	}
	initialize(board);
	SDL_Rect rec = { .x = 0, .y = 0, .w = 600, .h = 600 };
	SDL_Rect menu= { .x = 600, .y = 0, .w = 200, .h = 600 };
	SDL_Rect restart = { .x = 625, .y = 50, .w = 150, .h = 50 };
	SDL_Rect save = { .x = 625, .y = 125, .w = 150, .h = 50 };
	SDL_Rect load = { .x = 625, .y = 200, .w = 150, .h = 50 };
	SDL_Rect undo = { .x = 625, .y = 275, .w = 150, .h = 50 };
	SDL_Rect mainm = { .x = 625, .y = 425, .w = 150, .h = 50 };
	SDL_Rect exit = { .x = 625, .y = 500, .w = 150, .h = 50 };
	SDL_SetRenderDrawColor(src->renderer, 255, 255, 255, 255);
	SDL_RenderClear(src->renderer);
	SDL_RenderCopy(src->renderer, src->menuTexture, NULL, &menu);
	SDL_RenderCopy(src->renderer, src->bgTexture, NULL, &rec);
	SDL_RenderCopy(src->renderer, src->restartTexture, NULL, &restart);
	SDL_RenderCopy(src->renderer, src->saveTexture, NULL, &save);
	SDL_RenderCopy(src->renderer, src->loadTexture, NULL, &load);
	SDL_RenderCopy(src->renderer, src->undoTexture, NULL, &undo);
	SDL_RenderCopy(src->renderer, src->mainmTexture, NULL, &mainm);
	SDL_RenderCopy(src->renderer, src->exitTexture, NULL, &exit);

	int i = 0, j = 0;
	for (j=0; j<SP_N_COLUMNS ; j++){
	for (i= 0; i< SP_N_ROWS  ; i++) {
			rec.x = j * 75;
			rec.y = i * 75;
			rec.h = 75;
			rec.w = 75;
			setPiece( src,  i,  j, rec);

//			if (board[63- (i*8+j)] == 2000) {
//				SDL_RenderCopy(src->renderer, src->kingbTexture, NULL, &rec);
//			}
//			else if (board[63 - (i*8+j)] == 1000) {
//				SDL_RenderCopy(src->renderer, src->kingwTexture, NULL, &rec);
//			}
//			if (board[63-(i*8+j)] == 24) {
//				SDL_RenderCopy(src->renderer, src->bishopbTexture, NULL, &rec);
//			}
//			else if (board[63 -(i*8+j)] == 14) {
//				SDL_RenderCopy(src->renderer, src->bishopwTexture, NULL, &rec);
//			}
	}
	}
	SDL_RenderPresent(src->renderer);
}

SP_GAME_EVENT spGameWindowHandleEvent(SPGameWin* src, SDL_Event* event) {
	if (event == NULL || src == NULL ) {
		return SP_GAME_EVENT_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
//		spTicTacToeSetMove(src->game, event->button.y / 200,
//				event->button.x / 200);
//		char winner = spTicTacToeCheckWinner(src->game);
//		if (winner == SP_PLAYER_1_SYMBOL) {
//			return SP_GAME_EVENT_X_WON;
//		} else if (winner == SP_PLAYER_2_SYMBOL) {
//			return SP_GAME_EVENT_O_WON;
//		} else if (spTicTacToeIsGameOver(src->game)) {
//			return SP_GAME_EVENT_TIE;
//		}
//		if (isMovePiece()){
//			if(get_move(event->button.x,event->button.y)){
//				updateWinBoard(event->button.x,event->button.y);
//				after_move();
//			}
//		}
		if (isClickOnRestart(event->button.x, event->button.y)){
			return SP_GAME_RESTART;
		}
		if (isClickOnSave(event->button.x, event->button.y)){
			return SP_GAME_SAVE;
		}
		if (isClickOnLoadG(event->button.x, event->button.y)){
			return SP_GAME_LOAD;
		}
		if (isClickOnUndo(event->button.x, event->button.y)){
			return SP_GAME_UNDO;
		}
		if (isClickOnMainMenu(event->button.x, event->button.y)){
			return SP_GAME_MAIN_M;
		}
		if (isClickOnExitG(event->button.x, event->button.y)){
			return SP_GAME_EVENT_QUIT;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_GAME_EVENT_QUIT;
		}
		break;
	default:
		return SP_GAME_EVENT_NONE;
	}
	return SP_GAME_EVENT_NONE;
}

void spGameWindowHide(SPGameWin* src) {
	SDL_HideWindow(src->window);
}
