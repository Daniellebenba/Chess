/*
 * CHessGameSetLevel.c
 *
 *  Created on: 22 בספט׳ 2017
 *      Author: User
 */



/*
 * CHessGameSetMode.c
 *
 *  Created on: 22 בספט׳ 2017
 *      Author: User
 */


#include "CHessGameSetLevel.h"
#include <SDL_video.h>
#include <stdio.h>
//#include "CHessLoadGamesWin.h"
//Inner functions
int isClickOnNext(int x, int y) {
	if ((x >= 150 && x <= 300) && (y >= 500 && y <= 550)) {
		return 1;
	}

	return 0;
}

int isClickOnBackSet(int x, int y) {
	if ((x >= 500 && x <= 650) && (y >= 500 && y <= 550)) {
		return 1;
	}
	return 0;
}

//return the number of the slot clicked. 0 otherwise
int isClickOnLevel(int x, int y) {
	if ((x >= 300 && x <= 500) && (y >= 150 && y <= 200)) {
		return 1;
	}
	if ((x >= 300 && x <= 500) && (y >= 237.5 && y <= 287.5)) {
		return 2;
	}
	if ((x >= 300 && x <= 500) && (y >= 325 && y <= 375)) {
		return 3;
	}
	if ((x >= 300 && x <= 500) && (y >= 412.5 && y <= 462.5)) {
		return 4;
	}
//	if ((x >= 300 && x <= 500) && (y >= 400 && y <= 450)) {
//		return 5;
//	}
	return 0;
}



SPsetLevelWin* spGameSetLevelWindowCreate() {
	SPsetLevelWin* res = NULL;
	SDL_Surface* loadingSurface = NULL;
	res = (SPsetLevelWin*) calloc(sizeof(SPsetLevelWin), sizeof(char));
	if (res == NULL ) {
		return NULL ;
	}

	// Create an application window with the following settings:
	res->gameSetLevelWindow = SDL_CreateWindow("ChessSetLevel", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			800,                               // width, in pixels
			600,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	// Check that the window was successfully created
	if (res->gameSetLevelWindow == NULL ) {
		spGameSetLevelWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->mainRenderer = SDL_CreateRenderer(res->gameSetLevelWindow, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->mainRenderer == NULL ) {
		// In the case that the window could not be made...
		spGameSetLevelWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}

	//window background
		loadingSurface = SDL_LoadBMP("./graphics/images/difficultyBackground.bmp");
		if (loadingSurface == NULL ) {
			spGameSetLevelWindowDestroy(res);
			printf("couldn't create difficultyBackground.bmp surface\n");
			return NULL ;
		}
		res->windowTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->windowTexture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spGameSetLevelWindowDestroy(res);
			printf("couldn't create difficultyBackground.bmp texture\n");
			return NULL ;
		}
		SDL_FreeSurface(loadingSurface);

	//next button
	loadingSurface = SDL_LoadBMP("./graphics/images/next_button.bmp");
	if (loadingSurface == NULL ) {
		spGameSetLevelWindowDestroy(res);
		printf("couldn't create next_button.bmp surface\n");
		return NULL ;
	}
	res->nextTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->nextTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spGameSetLevelWindowDestroy(res);
		printf("couldn't create next_button.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);


	//back button
	loadingSurface = SDL_LoadBMP("./graphics/images/back_button.bmp");
	if (loadingSurface == NULL ) {
		spGameSetLevelWindowDestroy(res);
		printf("couldn't create back.bmp surface\n");
		return NULL ;
	}
	res->backTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->backTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spGameSetLevelWindowDestroy(res);
		printf("couldn't create back.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//res->bold =0; //initialize the pressed slot
	//slot button
	loadingSurface = SDL_LoadBMP("./graphics/images/noob_button_inactive.bmp");
	if (loadingSurface == NULL ) {
		spGameSetLevelWindowDestroy(res);
		printf("couldn't create noob_button_inactive.bmp surface\n");
		return NULL ;
	}
	res->level1Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->level1Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spGameSetLevelWindowDestroy(res);
		printf("couldn't create noob_button.bmp texture\n");
		return NULL ;
	}

	SDL_FreeSurface(loadingSurface);
	//slot button
	loadingSurface = SDL_LoadBMP("./graphics/images/easy_button.bmp");
	if (loadingSurface == NULL ) {
		spGameSetLevelWindowDestroy(res);
		printf("couldn't create easy_button.bmp surface\n");
		return NULL ;
	}
	res->level2Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->level2Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spGameSetLevelWindowDestroy(res);
		printf("couldn't create easy_button.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	res->level=2;
	//slot button
	loadingSurface = SDL_LoadBMP("./graphics/images/moderate_button_inactive.bmp");
	if (loadingSurface == NULL ) {
		spGameSetLevelWindowDestroy(res);
		printf("couldn't create moderate_button_inactive.bmp surface\n");
		return NULL ;
	}
	res->level3Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->level3Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spGameSetLevelWindowDestroy(res);
		printf("couldn't create moderate_button_inactive.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//slot button
	loadingSurface = SDL_LoadBMP("./graphics/images/hard_button_inactive.bmp");
	if (loadingSurface == NULL ) {
		spGameSetLevelWindowDestroy(res);
		printf("couldn't create hard_button_inactive.bmp surface\n");
		return NULL ;
	}
	res->level4Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->level4Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spGameSetLevelWindowDestroy(res);
		printf("couldn't create hard_button_inactive.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//slot button
//	loadingSurface = SDL_LoadBMP("./graphics/images/slot5.bmp");
//	if (loadingSurface == NULL ) {
//		spGameSetLevelWindowDestroy(res);
//		printf("couldn't create slot5.bmp surface\n");
//		return NULL ;
//	}
//	res->slot5Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
//			loadingSurface);
//	if (res->slot5Texture == NULL ) {
//		SDL_FreeSurface(loadingSurface);
//		spGameSetLevelWindowDestroy(res);
//		printf("couldn't create slot5.bmp texture\n");
//		return NULL ;
//	}
//	SDL_FreeSurface(loadingSurface);
	return res;
}

void spGameSetLevelWindowDestroy(SPsetLevelWin* src) {
	if (!src) {
		return;
	}
	if (src->nextTexture != NULL ) {
		SDL_DestroyTexture(src->nextTexture);
	}
	if (src->backTexture != NULL ) {
		SDL_DestroyTexture(src->backTexture);
	}
	if (src->level1Texture != NULL ) {
		SDL_DestroyTexture(src->level1Texture);
	}
	if (src->level2Texture != NULL ) {
			SDL_DestroyTexture(src->level2Texture);
		}
	if (src->level3Texture != NULL ) {
			SDL_DestroyTexture(src->level3Texture);
		}
	if (src->level4Texture != NULL ) {
			SDL_DestroyTexture(src->level4Texture);
		}
//	if (src->level5Texture != NULL ) {
//			SDL_DestroyTexture(src->slot1Texture);
//		}
	if (src->mainRenderer != NULL ) {
		SDL_DestroyRenderer(src->mainRenderer);
	}
	if (src->gameSetLevelWindow != NULL ) {
		SDL_DestroyWindow(src->gameSetLevelWindow);
	}
	free(src);
}

void spGameSetLevelWindowDraw(SPsetLevelWin* src) {
	if(src==NULL){
		return;
	}
	SDL_Rect backR = { .x = 500, .y = 500, .h = 50, .w = 150 };
	SDL_Rect nextR = { .x = 150, .y = 500, .h = 50, .w = 150 };
	SDL_Rect level1R = { .x = 300, .y = 150, .h = 50, .w = 200 };
	SDL_Rect level2R = { .x = 300, .y = 237.5, .h = 50, .w = 200 };
	SDL_Rect level3R = { .x = 300, .y = 325, .h = 50, .w = 200 };
	SDL_Rect level4R = { .x = 300, .y = 412.5, .h = 50, .w = 200 };
	//SDL_Rect slot5R = { .x = 300, .y = 400, .h = 50, .w = 200 };
	SDL_Rect window = { .x = 0, .y = 0, .h = 599, .w = 799 };
	SDL_SetRenderDrawColor(src->mainRenderer, 0, 0, 0, 255);
	SDL_RenderClear(src->mainRenderer);
	SDL_RenderCopy(src->mainRenderer, src->windowTexture, NULL, &window);
	SDL_RenderCopy(src->mainRenderer, src->nextTexture, NULL, &nextR);
	//SDL_RenderCopy(src->mainRenderer, src->loadTexture, NULL, &loadNoR);
	SDL_RenderCopy(src->mainRenderer, src->backTexture, NULL, &backR);
	SDL_RenderCopy(src->mainRenderer, src->level1Texture, NULL, &level1R);
	SDL_RenderCopy(src->mainRenderer, src->level2Texture, NULL, &level2R);
	SDL_RenderCopy(src->mainRenderer, src->level3Texture, NULL, &level3R);
	SDL_RenderCopy(src->mainRenderer, src->level4Texture, NULL, &level4R);
	//SDL_RenderCopy(src->mainRenderer, src->slot5Texture, NULL, &slot5R);
	SDL_RenderPresent(src->mainRenderer);
}
void change_button_level(SPsetLevelWin* res, int click){
	int num=res->bold;
	if (click ==1){
		SDL_Surface* loadingSurface;
		//slot button
			loadingSurface = SDL_LoadBMP("./graphics/images/easy_button_inactive.bmp");
			if (loadingSurface == NULL ) {
				spGameSetLevelWindowDestroy(res);
				printf("couldn't create easy_button_inactive.bmp surface\n");
				return;
			}
			res->level2Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
					loadingSurface);
			if (res->level2Texture == NULL ) {
				SDL_FreeSurface(loadingSurface);
				spGameSetLevelWindowDestroy(res);
				printf("couldn't create easy_button_inactive.bmp texture\n");
				return;
			}
			SDL_FreeSurface(loadingSurface);
	}
	if (num==0){
//		//load unpressed button
//		SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/loadgame_button.bmp");
//		if (loadingSurface == NULL ) {
//			spLoadGamesWindowDestroy(res);
//			printf("couldn't create loadgame_button.bmp surface\n");
//			return  ;
//		}
//		res->loadTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
//				loadingSurface);
//		if (res->loadTexture == NULL ) {
//			SDL_FreeSurface(loadingSurface);
//			spLoadGamesWindowDestroy(res);
//			printf("couldn't create loadgame_button.bmp texture\n");
//			return  ;
//		}
//		SDL_FreeSurface(loadingSurface);
	}
	SDL_Surface* loadingSurface;
	switch(num){
	case 1:
		//slot button
		loadingSurface = SDL_LoadBMP("./graphics/images/noob_button_inactive.bmp");
		if (loadingSurface == NULL ) {
			spGameSetLevelWindowDestroy(res);
			printf("couldn't create noob_button_inactive.bmp surface\n");
			return;
		}
		res->level1Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->level1Texture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spGameSetLevelWindowDestroy(res);
			printf("couldn't create level1Texture.bmp texture\n");
			return;
		}
		SDL_FreeSurface(loadingSurface);
		break;
	case 2:
		//slot button
		loadingSurface = SDL_LoadBMP("./graphics/images/easy_button_inactive.bmp");
		if (loadingSurface == NULL ) {
			spGameSetLevelWindowDestroy(res);
			printf("couldn't create easy_button_inactive.bmp surface\n");
			return ;
		}
		res->level2Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->level2Texture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spGameSetLevelWindowDestroy(res);
			printf("couldn't create easy_button_inactive.bmp texture\n");
			return;
		}
		SDL_FreeSurface(loadingSurface);
		break;
	case 3:
		//slot button
		loadingSurface = SDL_LoadBMP("./graphics/images/moderate_button_inactive.bmp");
		if (loadingSurface == NULL ) {
			spGameSetLevelWindowDestroy(res);
			printf("couldn't create moderate_button_inactive.bmp surface\n");
			return;
		}
		res->level3Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->level3Texture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spGameSetLevelWindowDestroy(res);
			printf("couldn't create moderate_button_inactive.bmp texture\n");
			return;
		}
		SDL_FreeSurface(loadingSurface);
		break;
	case 4:
		//slot button
		loadingSurface = SDL_LoadBMP("./graphics/images/hard_button_inactive.bmp");
		if (loadingSurface == NULL ) {
			spGameSetLevelWindowDestroy(res);
			printf("couldn't create hard_button_inactive.bmp surface\n");
			return  ;
		}
		res->level4Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->level4Texture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spGameSetLevelWindowDestroy(res);
			printf("couldn't create hard_button_inactive.bmp texture\n");
			return  ;
		}
		SDL_FreeSurface(loadingSurface);
		break;
//	case 5:
//		//slot button
//		loadingSurface = SDL_LoadBMP("./graphics/images/slot5.bmp");
//		if (loadingSurface == NULL ) {
//			spLoadGamesWindowDestroy(res);
//			printf("couldn't create slot5.bmp surface\n");
//			return  ;
//		}
//		res->slot5Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
//				loadingSurface);
//		if (res->slot5Texture == NULL ) {
//			SDL_FreeSurface(loadingSurface);
//			spLoadGamesWindowDestroy(res);
//			printf("couldn't create slot5.bmp texture\n");
//			return  ;
//		}
//		break;
	default: //no slot is clicked
		return;
	}
}
//
////change the slot button to be inactive
//void change_button(SPsetLevelWin* res){
//	int num=res->bold;
//	if (num==0){
//		//load unpressed button
//		SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/loadgame_button.bmp");
//		if (loadingSurface == NULL ) {
//			spLoadGamesWindowDestroy(res);
//			printf("couldn't create loadgame_button.bmp surface\n");
//			return  ;
//		}
//		res->loadTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
//				loadingSurface);
//		if (res->loadTexture == NULL ) {
//			SDL_FreeSurface(loadingSurface);
//			spLoadGamesWindowDestroy(res);
//			printf("couldn't create loadgame_button.bmp texture\n");
//			return  ;
//		}
//		SDL_FreeSurface(loadingSurface);
//	}
//	SDL_Surface* loadingSurface;
//	switch(num){
//	case 1:
//		//slot button
//		loadingSurface = SDL_LoadBMP("./graphics/images/slot11.bmp");
//		if (loadingSurface == NULL ) {
//			spLoadGamesWindowDestroy(res);
//			printf("couldn't create slot11.bmp surface\n");
//			return;
//		}
//		res->slot1Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
//				loadingSurface);
//		if (res->slot1Texture == NULL ) {
//			SDL_FreeSurface(loadingSurface);
//			spLoadGamesWindowDestroy(res);
//			printf("couldn't create slot11.bmp texture\n");
//			return;
//		}
//		SDL_FreeSurface(loadingSurface);
//		break;
//	case 2:
//		//slot button
//		loadingSurface = SDL_LoadBMP("./graphics/images/slot2.bmp");
//		if (loadingSurface == NULL ) {
//			spLoadGamesWindowDestroy(res);
//			printf("couldn't create slot2.bmp surface\n");
//			return ;
//		}
//		res->slot2Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
//				loadingSurface);
//		if (res->slot2Texture == NULL ) {
//			SDL_FreeSurface(loadingSurface);
//			spLoadGamesWindowDestroy(res);
//			printf("couldn't create slot2.bmp texture\n");
//			return;
//		}
//		SDL_FreeSurface(loadingSurface);
//		break;
//	case 3:
//		//slot button
//		loadingSurface = SDL_LoadBMP("./graphics/images/slot3.bmp");
//		if (loadingSurface == NULL ) {
//			spLoadGamesWindowDestroy(res);
//			printf("couldn't create slot3.bmp surface\n");
//			return;
//		}
//		res->slot3Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
//				loadingSurface);
//		if (res->slot3Texture == NULL ) {
//			SDL_FreeSurface(loadingSurface);
//			spLoadGamesWindowDestroy(res);
//			printf("couldn't create slot3.bmp texture\n");
//			return;
//		}
//		SDL_FreeSurface(loadingSurface);
//		break;
//	case 4:
//		//slot button
//		loadingSurface = SDL_LoadBMP("./graphics/images/slot4.bmp");
//		if (loadingSurface == NULL ) {
//			spLoadGamesWindowDestroy(res);
//			printf("couldn't create slot4.bmp surface\n");
//			return  ;
//		}
//		res->slot4Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
//				loadingSurface);
//		if (res->slot4Texture == NULL ) {
//			SDL_FreeSurface(loadingSurface);
//			spLoadGamesWindowDestroy(res);
//			printf("couldn't create slot4.bmp texture\n");
//			return  ;
//		}
//		SDL_FreeSurface(loadingSurface);
//		break;
//	case 5:
//		//slot button
//		loadingSurface = SDL_LoadBMP("./graphics/images/slot5.bmp");
//		if (loadingSurface == NULL ) {
//			spLoadGamesWindowDestroy(res);
//			printf("couldn't create slot5.bmp surface\n");
//			return  ;
//		}
//		res->slot5Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
//				loadingSurface);
//		if (res->slot5Texture == NULL ) {
//			SDL_FreeSurface(loadingSurface);
//			spLoadGamesWindowDestroy(res);
//			printf("couldn't create slot5.bmp texture\n");
//			return  ;
//		}
//		break;
//	default: //no slot is clicked
//		return;
//	}
//}
//
//SP_LOAD_GAMES_EVENT spGameSetLevellWindoHandleEvent(SPsetLevelWin* src, SDL_Event* event) {
//	if (!event) {
//		return SP_LOAD_GAMES_INVALID_ARGUMENT;
//	}
//	switch (event->type) {
//	case SDL_MOUSEBUTTONUP:
//		change_button(src);
//		if (isClickOnSlot(event->button.x, event->button.y)==1) {
//			src->bold=1;
//			//slot button
//			SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/slot11bold.bmp");
//			if (loadingSurface == NULL ) {
//			spLoadGamesWindowDestroy(src);
//			printf("couldn't create slot11bold.bmp surface\n");
//			return SP_LOAD_GAMES_NONE ;
//			}
//			src->slot1Texture = SDL_CreateTextureFromSurface(src->mainRenderer,
//					loadingSurface);
//			if (src->slot1Texture == NULL ) {
//				SDL_FreeSurface(loadingSurface);
//				spLoadGamesWindowDestroy(src);
//				printf("couldn't create slot11bold.bmp texture\n");
//				return SP_LOAD_GAMES_NONE ;
//			}
//			SDL_FreeSurface(loadingSurface);
//			return SP_LOAD_GAMES_SLOT_1;
//		}
//		else if (isClickOnSlot(event->button.x, event->button.y)==2) {
//			src->bold=2;
//			SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/slot2bold.bmp");
//			if (loadingSurface == NULL ) {
//			spLoadGamesWindowDestroy(src);
//			printf("couldn't create slot2bold.bmp surface\n");
//			return SP_LOAD_GAMES_NONE ;
//			}
//			src->slot2Texture = SDL_CreateTextureFromSurface(src->mainRenderer,
//					loadingSurface);
//			if (src->slot2Texture == NULL ) {
//				SDL_FreeSurface(loadingSurface);
//				spLoadGamesWindowDestroy(src);
//				printf("couldn't create slot2bold.bmp texture\n");
//				return SP_LOAD_GAMES_NONE ;
//			}
//			SDL_FreeSurface(loadingSurface);
//			return SP_LOAD_GAMES_SLOT_2;
//		}
//		else if (isClickOnSlot(event->button.x, event->button.y)==3) {
//			src->bold=3;
//			SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/slot3bold.bmp");
//			if (loadingSurface == NULL ) {
//			spLoadGamesWindowDestroy(src);
//			printf("couldn't create slot3bold.bmp surface\n");
//			return SP_LOAD_GAMES_NONE ;
//			}
//			src->slot3Texture = SDL_CreateTextureFromSurface(src->mainRenderer,
//					loadingSurface);
//			if (src->slot3Texture == NULL ) {
//				SDL_FreeSurface(loadingSurface);
//				spLoadGamesWindowDestroy(src);
//				printf("couldn't create slot3bold.bmp texture\n");
//				return SP_LOAD_GAMES_NONE ;
//			}
//			SDL_FreeSurface(loadingSurface);
//			return SP_LOAD_GAMES_SLOT_3;
//		}
//		else if (isClickOnSlot(event->button.x, event->button.y)==4) {
//			src->bold=4;
//			SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/slot4bold.bmp");
//			if (loadingSurface == NULL ) {
//			spLoadGamesWindowDestroy(src);
//			printf("couldn't create slot4bold.bmp surface\n");
//			return SP_LOAD_GAMES_NONE ;
//			}
//			src->slot4Texture = SDL_CreateTextureFromSurface(src->mainRenderer,
//					loadingSurface);
//			if (src->slot4Texture == NULL ) {
//				SDL_FreeSurface(loadingSurface);
//				spLoadGamesWindowDestroy(src);
//				printf("couldn't create slot4bold.bmp texture\n");
//				return SP_LOAD_GAMES_NONE ;
//			}
//			SDL_FreeSurface(loadingSurface);
//			return SP_LOAD_GAMES_SLOT_4;
//		}
//		else if (isClickOnSlot(event->button.x, event->button.y)==5) {
//			src->bold=5;
//			SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/slot5bold.bmp");
//			if (loadingSurface == NULL ) {
//			spLoadGamesWindowDestroy(src);
//			printf("couldn't create slot5bold.bmp surface\n");
//			return SP_LOAD_GAMES_NONE ;
//			}
//			src->slot5Texture = SDL_CreateTextureFromSurface(src->mainRenderer,
//					loadingSurface);
//			if (src->slot5Texture == NULL ) {
//				SDL_FreeSurface(loadingSurface);
//				spLoadGamesWindowDestroy(src);
//				printf("couldn't create slot5bold.bmp texture\n");
//				return SP_LOAD_GAMES_NONE ;
//			}
//			SDL_FreeSurface(loadingSurface);
//			return SP_LOAD_GAMES_SLOT_5;
//		}
//		else if (isClickOnBack(event->button.x, event->button.y)) {
//			return SP_LOAD_GAMES_BACK;
//		}
//		else if (isClickOnLoadGame(event->button.x, event->button.y)) {
//			return SP_LOAD_GAMES_LOAD;
//		}
//
//		break;
//	case SDL_WINDOWEVENT:
//		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
//			return SP_LOAD_GAMES_EXIT;
//		}
//		break;
//	default:
//		return SP_LOAD_GAMES_NONE;
//	}
//	return SP_LOAD_GAMES_NONE;
//}
SP_GAME_SET_LEVEL_EVENT spGameSetLevellWindoHandleEvent(SPsetLevelWin* src, SDL_Event* event) {
	if (!event) {
		return SP_GAME_SET_LEVEL_INVALID_ARGUMENT;
	}
	int clickNum = 0;
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		 clickNum++;
		 if (isClickOnLevel(event->button.x, event->button.y)==1) {
			change_button_level(src, clickNum);
			src->bold=1;
			//slot button
			SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/noob_button.bmp");
			if (loadingSurface == NULL ) {
				spGameSetLevelWindowDestroy(src);
			printf("couldn't create noob_button.bmp surface\n");
			return SP_GAME_SET_LEVEL_NONE ;
			}
			src->level1Texture = SDL_CreateTextureFromSurface(src->mainRenderer,
					loadingSurface);
			if (src->level1Texture == NULL ) {
				SDL_FreeSurface(loadingSurface);
				spGameSetLevelWindowDestroy(src);
				printf("couldn't create noob_button.bmp texture\n");
				return SP_GAME_SET_LEVEL_NONE ;
			}
			SDL_FreeSurface(loadingSurface);
			return SP_GAME_SET_LEVEL_1;
		}
		else if (isClickOnLevel(event->button.x, event->button.y)==2) {
			change_button_level(src, clickNum);

			src->bold=2;
			//slot button
			SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/easy_button.bmp");
			if (loadingSurface == NULL ) {
				spGameSetLevelWindowDestroy(src);
			printf("couldn't create easy_button.bmp surface\n");
			return SP_GAME_SET_LEVEL_NONE ;
			}
			src->level2Texture = SDL_CreateTextureFromSurface(src->mainRenderer,
					loadingSurface);
			if (src->level2Texture == NULL ) {
				SDL_FreeSurface(loadingSurface);
				spGameSetLevelWindowDestroy(src);
				printf("couldn't create easy_button.bmp texture\n");
				return SP_GAME_SET_LEVEL_NONE ;
			}
			SDL_FreeSurface(loadingSurface);
			return SP_GAME_SET_LEVEL_2;
		}
		else if (isClickOnLevel(event->button.x, event->button.y)==3) {
			change_button_level(src, clickNum);

			src->bold=3;
			//slot button
			SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/moderate_button.bmp");
			if (loadingSurface == NULL ) {
				spGameSetLevelWindowDestroy(src);
			printf("couldn't create moderate_button.bmp surface\n");
			return SP_GAME_SET_LEVEL_NONE ;
			}
			src->level3Texture = SDL_CreateTextureFromSurface(src->mainRenderer,
					loadingSurface);
			if (src->level3Texture == NULL ) {
				SDL_FreeSurface(loadingSurface);
				spGameSetLevelWindowDestroy(src);
				printf("couldn't create easy_button.bmp texture\n");
				return SP_GAME_SET_LEVEL_NONE ;
			}
			SDL_FreeSurface(loadingSurface);
			return SP_GAME_SET_LEVEL_3;
		}

		else if (isClickOnLevel(event->button.x, event->button.y)==4) {
			change_button_level(src, clickNum);

			src->bold=4;
			//slot button
			SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/hard_button.bmp");
			if (loadingSurface == NULL ) {
				spGameSetLevelWindowDestroy(src);
			printf("couldn't create hard_button.bmp surface\n");
			return SP_GAME_SET_LEVEL_NONE ;
			}
			src->level4Texture = SDL_CreateTextureFromSurface(src->mainRenderer,
					loadingSurface);
			if (src->level4Texture == NULL ) {
				SDL_FreeSurface(loadingSurface);
				spGameSetLevelWindowDestroy(src);
				printf("couldn't create easy_button.bmp texture\n");
				return SP_GAME_SET_LEVEL_NONE ;
			}
			SDL_FreeSurface(loadingSurface);
			return SP_GAME_SET_LEVEL_4;
		}
		else if (isClickOnBackSet(event->button.x, event->button.y)) {
			return SP_GAME_SET_LEVEL_BACK;
		}
		else if (isClickOnNext(event->button.x, event->button.y)) {
			return SP_GAME_SET_LEVEL_NEXT;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_GAME_SET_LEVEL_EXIT;
		}
		break;
	default:
		return SP_GAME_SET_LEVEL_NONE;
	}
	return SP_GAME_SET_LEVEL_NONE;
}
void spGameSetLevelWindowHide( SPsetLevelWin* src) {
	SDL_HideWindow(src->gameSetLevelWindow);
}

void spGameSetLevelWindowShow( SPsetLevelWin* src) {
	SDL_ShowWindow(src->gameSetLevelWindow);
}
