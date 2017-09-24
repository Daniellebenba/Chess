/*
 * CHessGUImanager.c
 *
 *  Created on: 19 בספט׳ 2017
 *      Author: User
 */

#include "CHessGUImanager.h"

SPGuiManager* spManagerCreate() {
	SPGuiManager* res = (SPGuiManager*) malloc(sizeof(SPGuiManager));
	if (res == NULL ) {
		return NULL ;
	}
	res->mainWin = spMainWindowCreate();
	if (res->mainWin == NULL ) {
		free(res);
		return NULL ;
	}
//	res->loadGamesWin = spLoadGamesnWindowCreate();
//	if (res->loadGamesWin == NULL ) {
//		free(res);
//		return NULL ;
//	}
//	res->setModeWin = spGameModeWindowCreate();
//	if (res->setModeWin == NULL ) {
//		free(res);
//		return NULL ;
//	}

//	res->setLevelWin = spGameSetLevelWindowCreate();
//	if (res->setLevelWin == NULL ) {
//		free(res);
//		return NULL ;
//	}
	res->setModeWin = NULL;
	res->setLevelWin=NULL;
	res->loadGamesWin = NULL;
	res->gameWin = NULL;
	res->activeWin = SP_MAIN_WINDOW_ACTIVE;
	return res;
}

void spManagerDestroy(SPGuiManager* src) {
	if (!src) {
		return;
	}
	if (src->activeWin == SP_GAME_WINDOW_ACTIVE) {
		spGameWindowDestroy(src->gameWin);
	}
	else if (src->activeWin == SP_LOAD_WINDOW_ACTIVE) {
		spLoadGamesWindowDestroy(src->loadGamesWin);
	}
	else if (src->activeWin == SP_SET_MODE_WINDOW_ACTIVE) {
		spGameModeWindowDestroy(src->setModeWin);
	}
	spMainWindowDestroy(src->mainWin);
	free(src);
}
//void spManagerDraw(SPGuiManager* src) {
//	if (!src) {
//		return;
//	}
//	spGameSetLevelWindowDraw(src->setLevelWin);
//	if (src->activeWin == SP_MAIN_WINDOW_ACTIVE) {
//		spMainWindowDraw(src->mainWin);
//		spLoadGamesWindowDraw(src->loadGamesWin);
//	}
//	else if (src->activeWin == SP_LOAD_WINDOW_ACTIVE) {
//		//spMainWindowDraw(src->mainWin);
//		spLoadGamesWindowDraw(src->loadGamesWin);
//	}
//	else {
//		spGameWindowDraw(src->gameWin);
//	}
//}
void spManagerDraw(SPGuiManager* src) {
	if (!src) {
		return;
	}
	//spGameSetLevelWindowDraw(src->setLevelWin);
	//(src->setModeWin);
	if (src->activeWin == SP_MAIN_WINDOW_ACTIVE) {
		spMainWindowDraw(src->mainWin);
		//spLoadGamesWindowDraw(src->loadGamesWin);
	}
	else if (src->activeWin == SP_LOAD_WINDOW_ACTIVE) {
		//spMainWindowDraw(src->mainWin);
		spLoadGamesWindowDraw(src->loadGamesWin);
	}
	else if (src->activeWin == SP_SET_MODE_WINDOW_ACTIVE) {
		//spMainWindowDraw(src->mainWin);
		spGameModeWindowDraw(src->setModeWin);
	}
	else if (src->activeWin == SP_SET_LEVEL_WINDOW_ACTIVE) {
		//spMainWindowDraw(src->mainWin);
		spGameSetLevelWindowDraw(src->setLevelWin);
	}
	else if (src->activeWin == SP_SET_COLOR_WINDOW_ACTIVE) {
		//spMainWindowDraw(src->mainWin);
		spGameSetColorWindowDraw(src->setColorWin);
	}
	else {
		spGameWindowDraw(src->gameWin);
	}
}



SP_MANAGER_EVENET handleManagerDueToMainEvent(SPGuiManager* src,
		SP_MAIN_EVENT event) {
	if (src == NULL ) {
		return SP_MANAGER_NONE;
	}
	if (event == SP_MAIN_GAME_SET) {
		spMainWindowHide(src->mainWin);
//		src->gameWin = spGameWindowCreate();
//		if (src->gameWin == NULL ) {
//			printf("Couldn't create game window\n");
//			return SP_MANAGER_QUTT;
//		}
//		src->activeWin = SP_GAME_WINDOW_ACTIVE;
		src->setModeWin = spGameModeWindowCreate();
		if (src->setModeWin == NULL){
			printf("Couldn't create game mode window\n");
			return SP_MANAGER_QUTT;
			}
		src->activeWin = SP_SET_MODE_WINDOW_ACTIVE;

		}

	if (event == SP_MAIN_LOAD) { //need to implement load operation
			spMainWindowHide(src->mainWin);
			src->loadGamesWin = spLoadGamesnWindowCreate();
			if (src->loadGamesWin == NULL ) {
				printf("Couldn't create load window\n");
				return SP_MANAGER_QUTT;
			}
			src->activeWin = SP_LOAD_WINDOW_ACTIVE;
	}
	if (event == SP_MAIN_EXIT) {
		return SP_MANAGER_QUTT;
	}
	return SP_MANAGER_NONE;
}


SP_MANAGER_EVENET handleManagerDueToGameEvent(SPGuiManager* src,
		SP_GAME_EVENT event) {
	if (event == SP_GAME_EVENT_NONE || src == NULL ) {
		return SP_MANAGER_NONE;
	}
	if (event == SP_GAME_RESTART ) {
			//--------
	}
	if (event == SP_GAME_SAVE ) {
		//--------
	}
	if (event == SP_GAME_LOAD ) {
		spGameWindowHide(src->gameWin);
		src->loadGamesWin = spLoadGamesnWindowCreate();
		if (src->loadGamesWin == NULL ) {
			printf("Couldn't create load window\n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_LOAD_WINDOW_ACTIVE;
	}

	if (event == SP_GAME_UNDO ) {
				//----
	}
	if (event == SP_GAME_MAIN_M ) {
		spGameWindowHide(src->gameWin);
		src->mainWin = spMainWindowCreate();
		if (src->mainWin == NULL ) {
		printf("Couldn't create main window\n");
		return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_MAIN_WINDOW_ACTIVE;
	}
	if (event == SP_GAME_EVENT_QUIT) {
		return SP_MANAGER_QUTT;
	}
	if (event == SP_GAME_EVENT_X_WON) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "X won",
				NULL );
	} else if (event == SP_GAME_EVENT_O_WON) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "O won",
				NULL );
	} else if (event == SP_GAME_EVENT_TIE) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over",
				"it's a tie", NULL );
	}
	if (event == SP_GAME_EVENT_QUIT) {
		return SP_MANAGER_QUTT;
	}
//	spGameWindowDestroy(src->gameWin);
//	src->gameWin = NULL;
//	src->activeWin = SP_GAME_WINDOW_ACTIVE;
//	spMainWindowShow(src->mainWin);
	return SP_MANAGER_NONE;
}


SP_LOAD_GAMES_EVENT handleManagerDueToLoadEvent(SPGuiManager* src, //need to write
		SP_LOAD_GAMES_EVENT event) {
	if (src == NULL ) {
		return SP_MANAGER_NONE;
	}
	if (event == SP_LOAD_GAMES_LOAD) {
		spLoadGamesWindowHide(src->loadGamesWin);
		//src->gameWin = loadfile(); need to implement start a game by slot
		if (src->gameWin == NULL ) {
			printf("Couldn't create game window\n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_GAME_WINDOW_ACTIVE;
	}
	if (event == SP_LOAD_GAMES_BACK) { //need to implement load operation
			spLoadGamesWindowHide(src->loadGamesWin);
			src->mainWin = spMainWindowCreate();
			if (src->mainWin == NULL ) {
				printf("Couldn't create main window\n");
				return SP_MANAGER_QUTT;
			}
			src->activeWin = SP_MAIN_WINDOW_ACTIVE;
	}
	if (event == SP_LOAD_GAMES_SLOT_1) {

		//return SP_MANAGER_QUTT;
	}
	if (event == SP_LOAD_GAMES_EXIT) {
		return SP_MANAGER_QUTT;
	}
	return SP_MANAGER_NONE;}


SP_GAME_MODE_EVENT handleManagerDueToSetModeEvent(SPGuiManager* src, //need to write
		SP_GAME_MODE_EVENT event) {
	if (src == NULL ) {
		return SP_MANAGER_NONE;
	}
	if (src == SP_MODE_PLAYER_1){
		set_game_mode(1);
	}
	if (src == SP_MODE_PLAYER_2){
		set_game_mode(2);
	}
	if (event == SP_GAME_MODE_NEXT) {
		spGameModeWindowHide(src->setModeWin);
		src->setLevelWin = spGameSetLevelWindowCreate();
		//src->gameWin = loadfile(); need to implement start a game by slot
		if (src->setLevelWin == NULL ) {
			printf("Couldn't create setLevelWin \n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_SET_LEVEL_WINDOW_ACTIVE;

	}
	else if (event == SP_GAME_MODE_START) {
		spGameModeWindowHide(src->setModeWin);
		src->gameWin = spGameWindowCreate();
		//src->gameWin = loadfile(); need to implement start a game by slot
		if (src->gameWin == NULL ) {
			printf("Couldn't create setLevelWin \n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_GAME_WINDOW_ACTIVE;
	}
	else if (event == SP_GAME_MODE_BACK) { //need to implement load operation
		spGameModeWindowHide(src->setModeWin);
			src->mainWin = spMainWindowCreate();
			if (src->mainWin == NULL ) {
				printf("Couldn't create main window\n");
				return SP_MANAGER_QUTT;
			}
			src->activeWin = SP_MAIN_WINDOW_ACTIVE;
	}
	if (event == SP_MODE_PLAYER_1) {

		//return SP_MANAGER_QUTT;
	}
	if (event == SP_MODE_EXIT) {
		return SP_MANAGER_QUTT;
	}
	return SP_MANAGER_NONE;}


SP_GAME_MODE_EVENT handleManagerDueToSetLevelEvent(SPGuiManager* src, //need to write
		SP_LOAD_GAMES_EVENT event) {
	if (src == NULL ) {
		return SP_MANAGER_NONE;
	}
	if (event == SP_GAME_SET_LEVEL_1){
		set_level(1);
	}
	if (event == SP_GAME_SET_LEVEL_2){
		set_level(2);
	}
	if (event == SP_GAME_SET_LEVEL_3){
		set_level(3);
	}
	if (event == SP_GAME_SET_LEVEL_4){
		set_level(4);
	}
	if (event == SP_GAME_SET_LEVEL_NEXT) {
		spGameSetLevelWindowHide(src->setLevelWin);
		src->setColorWin = spGameSetColorWindowCreate();
		//src->gameWin = loadfile(); need to implement start a game by slot
		if (src->setColorWin == NULL ) {
			printf("Couldn't create setColorWin \n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_SET_COLOR_WINDOW_ACTIVE;

	}
	if (event == SP_GAME_SET_LEVEL_BACK) { //need to implement load operation
		spGameSetLevelWindowHide(src->setLevelWin);
			src->mainWin = spMainWindowCreate();
			if (src->mainWin == NULL ) {
				printf("Couldn't create main window\n");
				return SP_MANAGER_QUTT;
			}
			src->activeWin = SP_MAIN_WINDOW_ACTIVE;
	}
	if (event == SP_GAME_SET_LEVEL_EXIT) {
		return SP_MANAGER_QUTT;
	}
	return SP_MANAGER_NONE;}


SP_GAME_SET_COLOR_EVENT handleManagerDueToSetColorEvent(SPGuiManager* src, //need to write
		SP_GAME_SET_COLOR_EVENT event) {
	if (src == NULL ) {
		return SP_MANAGER_NONE;
	}
	if (event == SP_GAME_SET_COLOR_BLACK){
		set_color(1);
	}
	if (event == SP_GAME_SET_COLOR_WHITE){
		set_color(0);
	}
	if (event == SP_GAME_SET_COLOR_START) {
		spGameSetLevelWindowHide(src->setColorWin);
		src->gameWin = spGameWindowCreate();
		//src->gameWin = loadfile(); need to implement start a game by slot
		if (src->gameWin == NULL ) {
			printf("Couldn't create gameWin \n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_GAME_WINDOW_ACTIVE;

	}
	if (event == SP_GAME_SET_COLOR_BACK) { //need to implement load operation
		spGameSetLevelWindowHide(src->setColorWin);
			src->mainWin = spMainWindowCreate();
			if (src->mainWin == NULL ) {
				printf("Couldn't create main window\n");
				return SP_MANAGER_QUTT;
			}
			src->activeWin = SP_MAIN_WINDOW_ACTIVE;
	}
	if (event == SP_GAME_SET_COLOR_EXIT) {
		return SP_MANAGER_QUTT;
	}
	return SP_MANAGER_NONE;}


SP_MANAGER_EVENET spManagerHandleEvent(SPGuiManager* src, SDL_Event* event)
	{
		if (src == NULL || event == NULL ) {
			return SP_MANAGER_NONE;
		}
		if (src->activeWin == SP_MAIN_WINDOW_ACTIVE) {
			SP_MAIN_EVENT mainEvent = spMainWindowHandleEvent(src->mainWin, event);
			return handleManagerDueToMainEvent(src, mainEvent);
		}
		else if (src->activeWin== SP_LOAD_WINDOW_ACTIVE){
			SP_LOAD_GAMES_EVENT mainEvent = spLoadGamesWindowHandleEvent(src->loadGamesWin, event);
			return handleManagerDueToLoadEvent(src, mainEvent);

		}
		else if (src->activeWin== SP_SET_MODE_WINDOW_ACTIVE){
			SP_GAME_MODE_EVENT mainEvent = spModeWindowHandleEvent(src->setModeWin, event);
			return handleManagerDueToSetModeEvent(src, mainEvent);

		}
		else if (src->activeWin== SP_SET_LEVEL_WINDOW_ACTIVE){
			SP_GAME_SET_LEVEL_EVENT mainEvent = spGameSetLevellWindoHandleEvent(src->setLevelWin, event);
			return handleManagerDueToSetLevelEvent(src, mainEvent);
		}
		else if (src->activeWin== SP_SET_COLOR_WINDOW_ACTIVE){
			SP_GAME_SET_LEVEL_EVENT mainEvent = spGameSetColorlWindoHandleEvent(src->setColorWin, event);
			return handleManagerDueToSetColorEvent(src, mainEvent);
		}
		else {
			SP_GAME_EVENT gameEvent = spGameWindowHandleEvent(src->gameWin, event);
			//spManagerDraw(src);
			return handleManagerDueToGameEvent(src, gameEvent);
		}
		return SP_MANAGER_NONE;
	}
