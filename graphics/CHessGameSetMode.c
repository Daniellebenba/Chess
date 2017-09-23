/*
 * CHessGameSetMode.c
 *
 *  Created on: 22 בספט׳ 2017
 *      Author: User
 */


#include "CHessGameSetMode.h"
#include <SDL_video.h>
#include <stdio.h>
#include "CHessGameSetLevel.h"
#include <SDL_video.h>
#include <stdio.h>
//#include "CHessLoadGamesWin.h"
//Inner functions
//int isClickOnNext(int x, int y) {
//	if ((x >= 150 && x <= 300) && (y >= 500 && y <= 550)) {
//		return 1;
//	}
//
//	return 0;
//}
//
//int isClickOnBackSet(int x, int y) {
//	if ((x >= 500 && x <= 650) && (y >= 500 && y <= 550)) {
//		return 1;
//	}
//	return 0;
//}

//return the number of the slot clicked. 0 otherwise
int isClickOnplayer(int x, int y) {
	if ((x >= 300 && x <= 500) && (y >= 150 && y <= 200)) {
		return 1;
	}
	if ((x >= 300 && x <= 500) && (y >= 237.5 && y <= 287.5)) {
		return 2;
	}
//	if ((x >= 300 && x <= 500) && (y >= 225 && y <= 275)) {
//		return 3;
//	}
//	if ((x >= 300 && x <= 500) && (y >= 312.5 && y <= 362.5)) {
//		return 4;
//	}
//	if ((x >= 300 && x <= 500) && (y >= 400 && y <= 450)) {
//		return 5;
//	}
	return 0;
}



SPModeWin* spGameModeWindowCreate() {
	SPModeWin* res = NULL;
	SDL_Surface* loadingSurface = NULL;
	res = (SPModeWin*) calloc(sizeof(SPModeWin), sizeof(char));
	if (res == NULL ) {
		return NULL ;
	}

	// Create an application window with the following settings:
	res->gameModelWindow =  SDL_CreateWindow("ChessMode", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			800,                               // width, in pixels
			600,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	// Check that the window was successfully created
	if (res->gameModelWindow == NULL ) {
		spGameModeWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->mainRenderer = SDL_CreateRenderer(res->gameModelWindow, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->mainRenderer == NULL ) {
		// In the case that the window could not be made...
		spGameModeWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}


	//window background
		loadingSurface = SDL_LoadBMP("./graphics/images/gamemodeBackground.bmp");
		if (loadingSurface == NULL ) {
			spGameModeWindowDestroy(res);
			printf("couldn't create difficultyBackground.bmp surface\n");
			return NULL ;
		}
		res->windowTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->windowTexture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spGameModeWindowDestroy(res);
			printf("couldn't create difficultyBackground.bmp texture\n");
			return NULL ;
		}
		SDL_FreeSurface(loadingSurface);

	//next button
	loadingSurface = SDL_LoadBMP("./graphics/images/next_button.bmp");
	if (loadingSurface == NULL ) {
		spGameModeWindowDestroy(res);
		printf("couldn't create next_button.bmp surface\n");
		return NULL ;
	}
	res->nextTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->nextTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spGameModeWindowDestroy(res);
		printf("couldn't create next_button.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//start button
	loadingSurface = SDL_LoadBMP("./graphics/images/next_button.bmp");
	if (loadingSurface == NULL ) {
		spGameModeWindowDestroy(res);
		printf("couldn't create next_button.bmp surface\n");
		return NULL ;
	}
	res->startTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->startTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spGameModeWindowDestroy(res);
		printf("couldn't create start_button.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	res->leftB = 1;
	//back button
	loadingSurface = SDL_LoadBMP("./graphics/images/back_button.bmp");
	if (loadingSurface == NULL ) {
		spGameModeWindowDestroy(res);
		printf("couldn't create back.bmp surface\n");
		return NULL ;
	}
	res->backTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->backTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spGameModeWindowDestroy(res);
		printf("couldn't create back.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//res->bold =0; //initialize the pressed slot
	//slot button
	loadingSurface = SDL_LoadBMP("./graphics/images/oneplayer_button.bmp");
	if (loadingSurface == NULL ) {
		spGameModeWindowDestroy(res);
		printf("couldn't create noob_button.bmp surface\n");
		return NULL ;
	}
	res->player1Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->player1Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spGameModeWindowDestroy(res);
		printf("couldn't create 1_player_inactive.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//slot button
	loadingSurface = SDL_LoadBMP("./graphics/images/twoplayers_button_inactive.bmp");
	if (loadingSurface == NULL ) {
		spGameModeWindowDestroy(res);
		printf("couldn't create 2_player_inactive.bmp surface\n");
		return NULL ;
	}
	res->player2Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->player2Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spGameModeWindowDestroy(res);
		printf("couldn't create 2_playe_inactive.bmp texture\n");
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

void spGameModeWindowDestroy(SPModeWin* src) {
	if (!src) {
		return;
	}
	if (src->nextTexture != NULL ) {
		SDL_DestroyTexture(src->nextTexture);
	}
	if (src->backTexture != NULL ) {
		SDL_DestroyTexture(src->backTexture);
	}
	if (src->player1Texture != NULL ) {
		SDL_DestroyTexture(src->player1Texture);
	}
	if (src->player2Texture != NULL ) {
			SDL_DestroyTexture(src->player2Texture);
		}

//	if (src->level5Texture != NULL ) {
//			SDL_DestroyTexture(src->slot1Texture);
//		}
	if (src->mainRenderer != NULL ) {
		SDL_DestroyRenderer(src->mainRenderer);
	}
	if (src->gameModelWindow != NULL ) {
		SDL_DestroyWindow(src->gameModelWindow);
	}
	free(src);
}

void spGameModeWindowDraw(SPModeWin* src) {
	if(src==NULL){
		return;
	}
	SDL_Rect backR = { .x = 500, .y = 500, .h = 50, .w = 150 };
	SDL_Rect nextR = { .x = 150, .y = 500, .h = 50, .w = 150 };
	SDL_Rect startR = { .x = 150, .y = 500, .h = 50, .w = 150 };
	SDL_Rect player1R = { .x = 300, .y = 150, .h = 50, .w = 200 };
	SDL_Rect player2R = { .x = 300, .y = 237.5, .h = 50, .w = 200 };
	//SDL_Rect level3R = { .x = 300, .y = 325, .h = 50, .w = 200 };
	//SDL_Rect level4R = { .x = 300, .y = 412.5, .h = 50, .w = 200 };
	//SDL_Rect slot5R = { .x = 300, .y = 400, .h = 50, .w = 200 };
	SDL_Rect window = { .x = 0, .y = 0, .h = 599, .w = 799 };
	SDL_SetRenderDrawColor(src->mainRenderer, 0, 0, 0, 255);
	SDL_RenderClear(src->mainRenderer);
	SDL_RenderCopy(src->mainRenderer, src->windowTexture, NULL, &window);
	SDL_RenderCopy(src->mainRenderer, src->nextTexture, NULL, &nextR);
	SDL_RenderCopy(src->mainRenderer, src->startTexture, NULL, &startR);
	//SDL_RenderCopy(src->mainRenderer, src->loadTexture, NULL, &loadNoR);
	SDL_RenderCopy(src->mainRenderer, src->backTexture, NULL, &backR);
	SDL_RenderCopy(src->mainRenderer, src->player1Texture, NULL, &player1R);
	SDL_RenderCopy(src->mainRenderer, src->player2Texture, NULL, &player2R);
	//SDL_RenderCopy(src->mainRenderer, src->level3Texture, NULL, &level3R);
	//SDL_RenderCopy(src->mainRenderer, src->level4Texture, NULL, &level4R);
	//SDL_RenderCopy(src->mainRenderer, src->slot5Texture, NULL, &slot5R);
	SDL_RenderPresent(src->mainRenderer);
}
//change the slot button to be inactive
void change_button_mode(SPModeWin* res, int Click){
	if(Click ==1){
		SDL_Surface* loadingSurface = NULL;
				loadingSurface = SDL_LoadBMP("./graphics/images/oneplayer_button_inactive.bmp");
				if (loadingSurface == NULL ) {
					spGameModeWindowDestroy(res);
					printf("couldn't create twoplayers_button_inactive.bmp surface\n");
					return ;
				}
				res->player1Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
						loadingSurface);
				if (res->player1Texture == NULL ) {
					SDL_FreeSurface(loadingSurface);
					spGameModeWindowDestroy(res);
					printf("couldn't create oneplayer_button_inactive.bmp texture\n");
					return;
				}
				SDL_FreeSurface(loadingSurface);
	}
	int num=res->bold;
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
		loadingSurface = SDL_LoadBMP("./graphics/images/oneplayer_button_inactive.bmp");
		if (loadingSurface == NULL ) {
			spGameModeWindowDestroy(res);
			printf("couldn't create oneplayer_button_inactive.bmp surface\n");
			return;
		}
		res->player1Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->player1Texture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spGameModeWindowDestroy(res);
			printf("couldn't create oneplayer_button_inactive.bmp texture\n");
			return;
		}
		SDL_FreeSurface(loadingSurface);
		break;
	case 2:
		//slot button
		loadingSurface = SDL_LoadBMP("./graphics/images/twoplayers_button_inactive.bmp");
		if (loadingSurface == NULL ) {
			spGameModeWindowDestroy(res);
			printf("couldn't create twoplayers_button_inactive.bmp surface\n");
			return ;
		}
		res->player2Texture = SDL_CreateTextureFromSurface(res->mainRenderer,
				loadingSurface);
		if (res->player2Texture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			spGameModeWindowDestroy(res);
			printf("couldn't create twoplayers_button_inactive.bmp texture\n");
			return;
		}
		SDL_FreeSurface(loadingSurface);
		break;

	default: //no slot is clicked
		return;
	}
}
SP_GAME_MODE_EVENT spModeWindowHandleEvent(SPModeWin* src, SDL_Event* event) {
	if (!event) {
		return SP_GAME_MODE_INVALID_ARGUMENT;
	}
	int numOfClicks = 0;
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		numOfClicks++;
		if (isClickOnplayer(event->button.x, event->button.y)==1) {
			change_button_mode(src,numOfClicks );
			src->bold=1;
			//slot button
			SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/oneplayer_button.bmp");
			if (loadingSurface == NULL ) {
			spGameModeWindowDestroy(src);
			printf("couldn't create oneplayer_button.bmp surface\n");
			return SP_GAME_MODE_NONE ;
			}
			src->player1Texture = SDL_CreateTextureFromSurface(src->mainRenderer,
					loadingSurface);
			if (src->player1Texture == NULL ) {
				SDL_FreeSurface(loadingSurface);
				spGameModeWindowDestroy(src);
				printf("couldn't create oneplayer_button.bmp texture\n");
				return SP_GAME_MODE_NONE ;
			}
			SDL_FreeSurface(loadingSurface);
			loadingSurface = SDL_LoadBMP("./graphics/images/next_button.bmp");
			if (loadingSurface == NULL ) {
				spGameModeWindowDestroy(src);
			printf("couldn't create start_button.bmp surface\n");
			return SP_GAME_MODE_NONE ;
			}
			src->startTexture = SDL_CreateTextureFromSurface(src->mainRenderer,
					loadingSurface);
			if (src->startTexture == NULL ) {
				SDL_FreeSurface(loadingSurface);
				spLoadGamesWindowDestroy(src);
				printf("couldn't create start_button.bmp texture\n");
				return SP_GAME_MODE_NONE ;
			}
			src->leftB = 1;
			SDL_FreeSurface(loadingSurface);
			return SP_MODE_PLAYER_1;
		}
		else if (isClickOnplayer(event->button.x, event->button.y)==2) {
			change_button_mode(src,numOfClicks );
			src->bold=2;
			SDL_Surface* loadingSurface = NULL;
			loadingSurface =	SDL_LoadBMP("./graphics/images/twoplayers_button.bmp");
			if (loadingSurface == NULL ) {
				spGameModeWindowDestroy(src);
			printf("couldn't create twoplayers_button.bmp surface\n");
			return SP_GAME_MODE_NONE ;
			}
			src->player2Texture = SDL_CreateTextureFromSurface(src->mainRenderer,
					loadingSurface);
			if (src->player2Texture == NULL ) {
				SDL_FreeSurface(loadingSurface);
				spLoadGamesWindowDestroy(src);
				printf("couldn't create twoplayers_button.bmp texture\n");
				return SP_GAME_MODE_NONE ;
			}
			SDL_FreeSurface(loadingSurface);
			loadingSurface = SDL_LoadBMP("./graphics/images/start_button.bmp");
			if (loadingSurface == NULL ) {
				spGameModeWindowDestroy(src);
			printf("couldn't create start_button.bmp surface\n");
			return SP_GAME_MODE_NONE ;
			}
			src->startTexture = SDL_CreateTextureFromSurface(src->mainRenderer,
					loadingSurface);
			if (src->startTexture == NULL ) {
				SDL_FreeSurface(loadingSurface);
				spLoadGamesWindowDestroy(src);
				printf("couldn't create start_button.bmp texture\n");
				return SP_GAME_MODE_NONE ;
			}
			src->leftB = 2;
			SDL_FreeSurface(loadingSurface);
			return SP_MODE_PLAYER_2;
		}
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
		else if (isClickOnBack(event->button.x, event->button.y)) {
			return SP_GAME_MODE_BACK;
		}
		else if (isClickOnNext(event->button.x, event->button.y)&& src->leftB ==1) {
			return SP_GAME_MODE_NEXT;
		}
		else if (isClickOnNext(event->button.x, event->button.y)&& src->leftB ==2) {
			return SP_GAME_MODE_START;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_MODE_EXIT;
		}
		break;
	default:
		return SP_GAME_MODE_NONE;
	}
	return SP_GAME_MODE_NONE;
}

/////////////////////////////////////////////////////////////////////////////////
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

void spGameModeWindowHide( SPModeWin* src) {
	SDL_HideWindow(src->gameModelWindow);
}

void spGameModelWindowShow( SPModeWin* src) {
	SDL_ShowWindow(src->gameModelWindow);
}
