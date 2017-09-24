/*
 * CHessSetColor.c
 *
 *  Created on: 23 בספט׳ 2017
 *      Author: User
 */


#include "CHessSetColor.h"
#include <SDL_video.h>
#include <stdio.h>
//#include "CHessLoadGamesWin.h"
//Inner functions
int isClickOnStart(int x, int y) {
	if ((x >= 150 && x <= 300) && (y >= 500 && y <= 550)) {
		return 1;
	}

	return 0;
}


int isClickOnBackColor(int x, int y) {
	if ((x >= 500 && x <= 650) && (y >= 500 && y <= 550)) {
		return 1;
	}
	return 0;
}

//return the color that was clicked. 0 otherwise
int isClickOnColor(int x, int y) {
	if ((x >= 125 && x <= 325) && (y >= 200 && y <= 300)) { //black
		return 1;
	}
	if ((x >= 475 && x <= 675) &&  (y >= 200 && y <= 300)) {
		return 2;
	}
	return 0;
}



SPsetColorWin* spGameSetColorWindowCreate() {
	SPsetColorWin* res = NULL;
	SDL_Surface* loadingSurface = NULL;
	res = (SPsetColorWin*) calloc(sizeof(SPsetColorWin), sizeof(char));
	if (res == NULL ) {
		return NULL ;
	}

	// Create an application window with the following settings:
	res->gameSetColorWindow = SDL_CreateWindow("ChessSetColor", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			800,                               // width, in pixels
			600,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	// Check that the window was successfully created
	if (res->gameSetColorWindow == NULL ) {
		spGameSetColorWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->mainRenderer = SDL_CreateRenderer(res->gameSetColorWindow, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->mainRenderer == NULL ) {
		// In the case that the window could not be made...
		spGameSetColorWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}

	//window background
		loadingSurface = SDL_LoadBMP("./graphics/images/colorBackground.bmp");
		if (loadingSurface == NULL ) {
			spGameSetColorWindowDestroy(res);
			printf("couldn't create difficultyBackground.bmp surface\n");
			return NULL ;
		}
		res->windowTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->windowTexture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spGameSetColorWindowDestroy(res);
			printf("couldn't create colorBackground.bmp texture\n");
			return NULL ;
		}
		SDL_FreeSurface(loadingSurface);

	//next button
	loadingSurface = SDL_LoadBMP("./graphics/images/start_button.bmp");
	if (loadingSurface == NULL ) {
		spGameSetColorWindowDestroy(res);
		printf("couldn't create start_button.bmp surface\n");
		return NULL ;
	}
	res->startTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->startTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spGameSetColorWindowDestroy(res);
		printf("couldn't create start_button.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);


	//back button
	loadingSurface = SDL_LoadBMP("./graphics/images/back_button.bmp");
	if (loadingSurface == NULL ) {
		spGameSetColorWindowDestroy(res);
		printf("couldn't create back.bmp surface\n");
		return NULL ;
	}
	res->backTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->backTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spGameSetColorWindowDestroy(res);
		printf("couldn't create back.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//res->bold =0; //initialize the pressed slot
	//slot button
	loadingSurface = SDL_LoadBMP("./graphics/images/black.bmp");
	if (loadingSurface == NULL ) {
		spGameSetColorWindowDestroy(res);
		printf("couldn't create black.bmp surface\n");
		return NULL ;
	}
	res->blackTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->blackTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spGameSetColorWindowDestroy(res);
		printf("couldn't create black.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//slot button
	res->bold = 2;
	loadingSurface = SDL_LoadBMP("./graphics/images/white_active.bmp");
	if (loadingSurface == NULL ) {
		spGameSetColorWindowDestroy(res);
		printf("couldn't create white_active.bmp surface\n");
		return NULL ;
	}
	res->whiteTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->whiteTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spGameSetColorWindowDestroy(res);
		printf("couldn't create white_active.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	return res;
}

void spGameSetColorWindowDestroy(SPsetColorWin* src) {
	if (!src) {
		return;
	}
	if (src->startTexture != NULL ) {
		SDL_DestroyTexture(src->startTexture);
	}
	if (src->backTexture != NULL ) {
		SDL_DestroyTexture(src->backTexture);
	}
	if (src->blackTexture != NULL ) {
		SDL_DestroyTexture(src->blackTexture);
	}
	if (src->whiteTexture != NULL ) {
			SDL_DestroyTexture(src->whiteTexture);
		}

//	if (src->Color5Texture != NULL ) {
//			SDL_DestroyTexture(src->slot1Texture);
//		}
	if (src->mainRenderer != NULL ) {
		SDL_DestroyRenderer(src->mainRenderer);
	}
	if (src->gameSetColorWindow != NULL ) {
		SDL_DestroyWindow(src->gameSetColorWindow);
	}
	free(src);
}

void spGameSetColorWindowDraw(SPsetColorWin* src) {
	if(src==NULL){
		return;
	}
	SDL_Rect backR = { .x = 500, .y = 500, .h = 50, .w = 150 };
	SDL_Rect nextR = { .x = 150, .y = 500, .h = 50, .w = 150 };
	SDL_Rect Color1R = { .x =125, .y = 200, .h = 100, .w = 200 }; //black
	SDL_Rect Color2R = { .x = 475, .y = 200, .h = 100, .w = 200 }; //white
	//SDL_Rect slot5R = { .x = 300, .y = 400, .h = 50, .w = 200 };
	SDL_Rect window = { .x = 0, .y = 0, .h = 599, .w = 799 };
	SDL_SetRenderDrawColor(src->mainRenderer, 0, 0, 0, 255);
	SDL_RenderClear(src->mainRenderer);
	SDL_RenderCopy(src->mainRenderer, src->windowTexture, NULL, &window);
	SDL_RenderCopy(src->mainRenderer, src->startTexture, NULL, &nextR);
	SDL_RenderCopy(src->mainRenderer, src->backTexture, NULL, &backR);
	SDL_RenderCopy(src->mainRenderer, src->blackTexture, NULL, &Color1R);
	SDL_RenderCopy(src->mainRenderer, src->whiteTexture, NULL, &Color2R);

	SDL_RenderPresent(src->mainRenderer);
}

//change the slot button to be inactive
void inactive_color(SPsetColorWin* res){
	int num=res->bold;
	if (num==1){
		//load unpressed button
		SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/black.bmp");
		if (loadingSurface == NULL ) {
			spGameSetColorWindowDestroy(res);
			printf("couldn't create black.bmp surface\n");
			return  ;
		}
		res->blackTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->blackTexture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spGameSetColorWindowDestroy(res);
			printf("couldn't create black.bmp texture\n");
			return  ;
		}
		SDL_FreeSurface(loadingSurface);
	}
	if (num==2){
		//load unpressed button
		SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/white.bmp");
		if (loadingSurface == NULL ) {
			spGameSetColorWindowDestroy(res);
			printf("couldn't create white.bmp surface\n");
			return  ;
		}
		res->whiteTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->whiteTexture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spGameSetColorWindowDestroy(res);
			printf("couldn't create white.bmp texture\n");
			return  ;
		}
		SDL_FreeSurface(loadingSurface);
	}
}

SP_GAME_SET_COLOR_EVENT spGameSetColorlWindoHandleEvent(SPsetColorWin* src, SDL_Event* event) {
	if (!event) {
		return SP_GAME_SET_COLOR_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if ((isClickOnColor(event->button.x, event->button.y)==1)&&(src->bold!=1)) { //black
			inactive_color(src);
			src->bold=1;
			SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/black_active.bmp");
			if (loadingSurface == NULL ) {
			spGameSetColorWindowDestroy(src);
			printf("couldn't create black_active.bmp surface\n");
			return SP_GAME_SET_COLOR_NONE ;
			}
			src->blackTexture = SDL_CreateTextureFromSurface(src->mainRenderer,
					loadingSurface);
			if (src->blackTexture == NULL ) {
				SDL_FreeSurface(loadingSurface);
				spGameSetColorWindowDestroy(src);
				printf("couldn't create black_active.bmp texture\n");
				return SP_GAME_SET_COLOR_NONE ;
			}
			SDL_FreeSurface(loadingSurface);
			return SP_GAME_SET_COLOR_BLACK;
		}
		else if ((isClickOnColor(event->button.x, event->button.y)==2)&&(src->bold!=2)){
			inactive_color(src);
			src->bold=2;
			SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/white_active.bmp");
			if (loadingSurface == NULL ) {
				spGameSetColorWindowDestroy(src);
			printf("couldn't create white_active.bmp surface\n");
			return SP_GAME_SET_COLOR_NONE ;
			}
			src->whiteTexture = SDL_CreateTextureFromSurface(src->mainRenderer,
					loadingSurface);
			if (src->whiteTexture == NULL ) {
				SDL_FreeSurface(loadingSurface);
				spGameSetColorWindowDestroy(src);
				printf("couldn't create white_active.bmp texture\n");
				return SP_GAME_SET_COLOR_NONE ;
			}
			SDL_FreeSurface(loadingSurface);
			return SP_GAME_SET_COLOR_WHITE;
		}
		else if (isClickOnBackColor(event->button.x, event->button.y)) {
			return SP_GAME_SET_COLOR_BACK;
		}
		else if (isClickOnStart(event->button.x, event->button.y)) {
			return SP_GAME_SET_COLOR_START;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_GAME_SET_COLOR_EXIT;
		}
		break;
	default:
		return SP_GAME_SET_COLOR_NONE;
	}
	return SP_GAME_SET_COLOR_NONE;
}

void spGameSetColorWindowHide( SPsetColorWin* src) {
	SDL_HideWindow(src->gameSetColorWindow);
}

void spGameSetColorWindowShow(SPsetColorWin* src) {
	SDL_ShowWindow(src->gameSetColorWindow);
}

