/*
 * CHessLoadGamesWin.c
 *
 *  Created on: 21 בספט׳ 2017
 *      Author: User
 */

#include "CHessLoadGamesWin.h"
#include <SDL_video.h>
#include <stdio.h>

//Inner functions
int isClickOnLoadGame(int x, int y) {
	if ((x >= 150 && x <= 300) && (y >= 500 && y <= 550)) {
		return 1;
	}

	return 0;
}

int isClickOnBack(int x, int y) {
	if ((x >= 500 && x <= 650) && (y >= 500 && y <= 550)) {
		return 1;
	}
	return 0;
}

//return the number of the slot clicked. 0 otherwise
int isClickOnSlot(int x, int y) {
	if ((x >= 300 && x <= 500) && (y >= 50 && y <= 100)) {
		return 1;
	}
	if ((x >= 300 && x <= 500) && (y >= 137.5 && y <= 187.5)) {
		return 2;
	}
	if ((x >= 300 && x <= 500) && (y >= 225 && y <= 275)) {
		return 3;
	}
	if ((x >= 300 && x <= 500) && (y >= 312.5 && y <= 362.5)) {
		return 4;
	}
	if ((x >= 300 && x <= 500) && (y >= 400 && y <= 450)) {
		return 5;
	}
	return 0;
}



SPLoadGamesWin* spLoadGamesnWindowCreate() {
	SPLoadGamesWin* res = NULL;
	SDL_Surface* loadingSurface = NULL;
	res = (SPLoadGamesWin*) calloc(sizeof(SPLoadGamesWin), sizeof(char));
	if (res == NULL ) {
		return NULL ;
	}

	// Create an application window with the following settings:
	res->loadGamesWindow = SDL_CreateWindow("ChessLoadGames", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			800,                               // width, in pixels
			600,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	// Check that the window was successfully created
	if (res->loadGamesWindow == NULL ) {
		spLoadGamesWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->mainRenderer = SDL_CreateRenderer(res->loadGamesWindow, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->mainRenderer == NULL ) {
		// In the case that the window could not be made...
		spLoadGamesWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}

	//window background
		loadingSurface = SDL_LoadBMP("./graphics/images/background.bmp");
		if (loadingSurface == NULL ) {
			spLoadGamesWindowDestroy(res);
			printf("couldn't create background.bmp surface\n");
			return NULL ;
		}
		res->windowTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->windowTexture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spLoadGamesWindowDestroy(res);
			printf("couldn't create background.bmp texture\n");
			return NULL ;
		}
		SDL_FreeSurface(loadingSurface);

	//load button
	loadingSurface = SDL_LoadBMP("./graphics/images/loadgame_button_inactive.bmp");
	if (loadingSurface == NULL ) {
		spLoadGamesWindowDestroy(res);
		printf("couldn't create loadgame_button_inactive.bmp surface\n");
		return NULL ;
	}
	res->loadTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->loadTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spLoadGamesWindowDestroy(res);
		printf("couldn't create loadgame_button_inactive.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);


	//back button
	loadingSurface = SDL_LoadBMP("./graphics/images/back_button.bmp");
	if (loadingSurface == NULL ) {
		spLoadGamesWindowDestroy(res);
		printf("couldn't create back.bmp surface\n");
		return NULL ;
	}
	res->backTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->backTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spLoadGamesWindowDestroy(res);
		printf("couldn't create back.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	res->bold =0; //initialize the pressed slot
	//slot button
	loadingSurface = SDL_LoadBMP("./graphics/images/slot11.bmp");
	if (loadingSurface == NULL ) {
		spLoadGamesWindowDestroy(res);
		printf("couldn't create slot11.bmp surface\n");
		return NULL ;
	}
	res->slot1Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->slot1Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spLoadGamesWindowDestroy(res);
		printf("couldn't create slot11.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//slot button
	loadingSurface = SDL_LoadBMP("./graphics/images/slot2.bmp");
	if (loadingSurface == NULL ) {
		spLoadGamesWindowDestroy(res);
		printf("couldn't create slot2.bmp surface\n");
		return NULL ;
	}
	res->slot2Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->slot2Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spLoadGamesWindowDestroy(res);
		printf("couldn't create slot2.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//slot button
	loadingSurface = SDL_LoadBMP("./graphics/images/slot3.bmp");
	if (loadingSurface == NULL ) {
		spLoadGamesWindowDestroy(res);
		printf("couldn't create slot3.bmp surface\n");
		return NULL ;
	}
	res->slot3Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->slot3Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spLoadGamesWindowDestroy(res);
		printf("couldn't create slot3.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//slot button
	loadingSurface = SDL_LoadBMP("./graphics/images/slot4.bmp");
	if (loadingSurface == NULL ) {
		spLoadGamesWindowDestroy(res);
		printf("couldn't create slot4.bmp surface\n");
		return NULL ;
	}
	res->slot4Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->slot4Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spLoadGamesWindowDestroy(res);
		printf("couldn't create slot4.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//slot button
	loadingSurface = SDL_LoadBMP("./graphics/images/slot5.bmp");
	if (loadingSurface == NULL ) {
		spLoadGamesWindowDestroy(res);
		printf("couldn't create slot5.bmp surface\n");
		return NULL ;
	}
	res->slot5Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->slot5Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spLoadGamesWindowDestroy(res);
		printf("couldn't create slot5.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	return res;
}

void spLoadGamesWindowDestroy(SPLoadGamesWin* src) {
	if (!src) {
		return;
	}
	if (src->loadTexture != NULL ) {
		SDL_DestroyTexture(src->loadTexture);
	}
	if (src->backTexture != NULL ) {
		SDL_DestroyTexture(src->backTexture);
	}
	if (src->slot1Texture != NULL ) {
		SDL_DestroyTexture(src->slot1Texture);
	}
	if (src->slot2Texture != NULL ) {
			SDL_DestroyTexture(src->slot1Texture);
		}
	if (src->slot3Texture != NULL ) {
			SDL_DestroyTexture(src->slot1Texture);
		}
	if (src->slot4Texture != NULL ) {
			SDL_DestroyTexture(src->slot1Texture);
		}
	if (src->slot5Texture != NULL ) {
			SDL_DestroyTexture(src->slot1Texture);
		}
	if (src->mainRenderer != NULL ) {
		SDL_DestroyRenderer(src->mainRenderer);
	}
	if (src->loadGamesWindow != NULL ) {
		SDL_DestroyWindow(src->loadGamesWindow);
	}
	free(src);
}

void spLoadGamesWindowDraw(SPLoadGamesWin* src) {
	if(src==NULL){
		return;
	}
	SDL_Rect backR = { .x = 500, .y = 500, .h = 50, .w = 150 };
	SDL_Rect loadR = { .x = 150, .y = 500, .h = 50, .w = 150 };
	SDL_Rect loadNoR = { .x = 150, .y = 500, .h = 50, .w = 130 };
	SDL_Rect slot1R = { .x = 300, .y = 50, .h = 50, .w = 200 };
	SDL_Rect slot2R = { .x = 300, .y = 137.5, .h = 50, .w = 200 };
	SDL_Rect slot3R = { .x = 300, .y = 225, .h = 50, .w = 200 };
	SDL_Rect slot4R = { .x = 300, .y = 312.5, .h = 50, .w = 200 };
	SDL_Rect slot5R = { .x = 300, .y = 400, .h = 50, .w = 200 };
	SDL_Rect window = { .x = 0, .y = 0, .h = 599, .w = 799 };
	SDL_SetRenderDrawColor(src->mainRenderer, 0, 0, 0, 255);
	SDL_RenderClear(src->mainRenderer);
	SDL_RenderCopy(src->mainRenderer, src->windowTexture, NULL, &window);
	SDL_RenderCopy(src->mainRenderer, src->loadTexture, NULL, &loadR);
	//SDL_RenderCopy(src->mainRenderer, src->loadTexture, NULL, &loadNoR);
	SDL_RenderCopy(src->mainRenderer, src->backTexture, NULL, &backR);
	SDL_RenderCopy(src->mainRenderer, src->slot1Texture, NULL, &slot1R);
	SDL_RenderCopy(src->mainRenderer, src->slot2Texture, NULL, &slot2R);
	SDL_RenderCopy(src->mainRenderer, src->slot3Texture, NULL, &slot3R);
	SDL_RenderCopy(src->mainRenderer, src->slot4Texture, NULL, &slot4R);
	SDL_RenderCopy(src->mainRenderer, src->slot5Texture, NULL, &slot5R);
	SDL_RenderPresent(src->mainRenderer);
}

//change the slot button to be inactive
void change_button(SPLoadGamesWin* res){
	int num=res->bold;
	if (num==0){
		//load unpressed button
		SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/loadgame_button.bmp");
		if (loadingSurface == NULL ) {
			spLoadGamesWindowDestroy(res);
			printf("couldn't create loadgame_button.bmp surface\n");
			return  ;
		}
		res->loadTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->loadTexture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spLoadGamesWindowDestroy(res);
			printf("couldn't create loadgame_button.bmp texture\n");
			return  ;
		}
		SDL_FreeSurface(loadingSurface);
	}
	SDL_Surface* loadingSurface;
	switch(num){
	case 1:
		//slot button
		loadingSurface = SDL_LoadBMP("./graphics/images/slot11.bmp");
		if (loadingSurface == NULL ) {
			spLoadGamesWindowDestroy(res);
			printf("couldn't create slot11.bmp surface\n");
			return;
		}
		res->slot1Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->slot1Texture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spLoadGamesWindowDestroy(res);
			printf("couldn't create slot11.bmp texture\n");
			return;
		}
		SDL_FreeSurface(loadingSurface);
		break;
	case 2:
		//slot button
		loadingSurface = SDL_LoadBMP("./graphics/images/slot2.bmp");
		if (loadingSurface == NULL ) {
			spLoadGamesWindowDestroy(res);
			printf("couldn't create slot2.bmp surface\n");
			return ;
		}
		res->slot2Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->slot2Texture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spLoadGamesWindowDestroy(res);
			printf("couldn't create slot2.bmp texture\n");
			return;
		}
		SDL_FreeSurface(loadingSurface);
		break;
	case 3:
		//slot button
		loadingSurface = SDL_LoadBMP("./graphics/images/slot3.bmp");
		if (loadingSurface == NULL ) {
			spLoadGamesWindowDestroy(res);
			printf("couldn't create slot3.bmp surface\n");
			return;
		}
		res->slot3Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->slot3Texture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spLoadGamesWindowDestroy(res);
			printf("couldn't create slot3.bmp texture\n");
			return;
		}
		SDL_FreeSurface(loadingSurface);
		break;
	case 4:
		//slot button
		loadingSurface = SDL_LoadBMP("./graphics/images/slot4.bmp");
		if (loadingSurface == NULL ) {
			spLoadGamesWindowDestroy(res);
			printf("couldn't create slot4.bmp surface\n");
			return  ;
		}
		res->slot4Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->slot4Texture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spLoadGamesWindowDestroy(res);
			printf("couldn't create slot4.bmp texture\n");
			return  ;
		}
		SDL_FreeSurface(loadingSurface);
		break;
	case 5:
		//slot button
		loadingSurface = SDL_LoadBMP("./graphics/images/slot5.bmp");
		if (loadingSurface == NULL ) {
			spLoadGamesWindowDestroy(res);
			printf("couldn't create slot5.bmp surface\n");
			return  ;
		}
		res->slot5Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->slot5Texture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spLoadGamesWindowDestroy(res);
			printf("couldn't create slot5.bmp texture\n");
			return  ;
		}
		break;
	default: //no slot is clicked
		return;
	}
}

SP_LOAD_GAMES_EVENT spLoadGamesWindowHandleEvent(SPLoadGamesWin* src, SDL_Event* event) {
	if (!event) {
		return SP_LOAD_GAMES_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnSlot(event->button.x, event->button.y)==1) {
			change_button(src);
			src->bold=1;
			//slot button
			SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/slot11bold.bmp");
			if (loadingSurface == NULL ) {
			spLoadGamesWindowDestroy(src);
			printf("couldn't create slot11bold.bmp surface\n");
			return SP_LOAD_GAMES_NONE ;
			}
			src->slot1Texture = SDL_CreateTextureFromSurface(src->mainRenderer,
					loadingSurface);
			if (src->slot1Texture == NULL ) {
				SDL_FreeSurface(loadingSurface);
				spLoadGamesWindowDestroy(src);
				printf("couldn't create slot11bold.bmp texture\n");
				return SP_LOAD_GAMES_NONE ;
			}
			SDL_FreeSurface(loadingSurface);
			return SP_LOAD_GAMES_SLOT_1;
		}
		else if (isClickOnSlot(event->button.x, event->button.y)==2) {
			change_button(src);
			src->bold=2;
			SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/slot2bold.bmp");
			if (loadingSurface == NULL ) {
			spLoadGamesWindowDestroy(src);
			printf("couldn't create slot2bold.bmp surface\n");
			return SP_LOAD_GAMES_NONE ;
			}
			src->slot2Texture = SDL_CreateTextureFromSurface(src->mainRenderer,
					loadingSurface);
			if (src->slot2Texture == NULL ) {
				SDL_FreeSurface(loadingSurface);
				spLoadGamesWindowDestroy(src);
				printf("couldn't create slot2bold.bmp texture\n");
				return SP_LOAD_GAMES_NONE ;
			}
			SDL_FreeSurface(loadingSurface);
			return SP_LOAD_GAMES_SLOT_2;
		}
		else if (isClickOnSlot(event->button.x, event->button.y)==3) {
			change_button(src);
			src->bold=3;
			SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/slot3bold.bmp");
			if (loadingSurface == NULL ) {
			spLoadGamesWindowDestroy(src);
			printf("couldn't create slot3bold.bmp surface\n");
			return SP_LOAD_GAMES_NONE ;
			}
			src->slot3Texture = SDL_CreateTextureFromSurface(src->mainRenderer,
					loadingSurface);
			if (src->slot3Texture == NULL ) {
				SDL_FreeSurface(loadingSurface);
				spLoadGamesWindowDestroy(src);
				printf("couldn't create slot3bold.bmp texture\n");
				return SP_LOAD_GAMES_NONE ;
			}
			SDL_FreeSurface(loadingSurface);
			return SP_LOAD_GAMES_SLOT_3;
		}
		else if (isClickOnSlot(event->button.x, event->button.y)==4) {
			change_button(src);
			src->bold=4;
			SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/slot4bold.bmp");
			if (loadingSurface == NULL ) {
			spLoadGamesWindowDestroy(src);
			printf("couldn't create slot4bold.bmp surface\n");
			return SP_LOAD_GAMES_NONE ;
			}
			src->slot4Texture = SDL_CreateTextureFromSurface(src->mainRenderer,
					loadingSurface);
			if (src->slot4Texture == NULL ) {
				SDL_FreeSurface(loadingSurface);
				spLoadGamesWindowDestroy(src);
				printf("couldn't create slot4bold.bmp texture\n");
				return SP_LOAD_GAMES_NONE ;
			}
			SDL_FreeSurface(loadingSurface);
			return SP_LOAD_GAMES_SLOT_4;
		}
		else if (isClickOnSlot(event->button.x, event->button.y)==5) {
			change_button(src);
			src->bold=5;
			SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/slot5bold.bmp");
			if (loadingSurface == NULL ) {
			spLoadGamesWindowDestroy(src);
			printf("couldn't create slot5bold.bmp surface\n");
			return SP_LOAD_GAMES_NONE ;
			}
			src->slot5Texture = SDL_CreateTextureFromSurface(src->mainRenderer,
					loadingSurface);
			if (src->slot5Texture == NULL ) {
				SDL_FreeSurface(loadingSurface);
				spLoadGamesWindowDestroy(src);
				printf("couldn't create slot5bold.bmp texture\n");
				return SP_LOAD_GAMES_NONE ;
			}
			SDL_FreeSurface(loadingSurface);
			return SP_LOAD_GAMES_SLOT_5;
		}
		else if (isClickOnBack(event->button.x, event->button.y)) {
			return SP_LOAD_GAMES_BACK;
		}
		else if (isClickOnLoadGame(event->button.x, event->button.y)) {
			return SP_LOAD_GAMES_LOAD;
		}

		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_LOAD_GAMES_EXIT;
		}
		break;
	default:
		return SP_LOAD_GAMES_NONE;
	}
	return SP_LOAD_GAMES_NONE;
}

void spLoadGamesWindowHide(SPLoadGamesWin* src) {
	SDL_HideWindow(src->loadGamesWindow);
}

void spLoadGamesWindowShow(SPLoadGamesWin* src) {
	SDL_ShowWindow(src->loadGamesWindow);
}
