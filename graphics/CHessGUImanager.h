/*
 * CHessGUImanager.h
 *
 *  Created on: 19 בספט׳ 2017
 *      Author: User
 */

#ifndef GRAPHICS_CHESSGUIMANAGER_H_
#define GRAPHICS_CHESSGUIMANAGER_H_


#include <SDL.h>
#include "CHessGameWin.h"
#include "CHessMainWin.h"
#include "CHessLoadGamesWin.h"
#include "CHessGameSetLevel.h"
#include "CHessGameSetMode.h"
#include "CHessSetColor.h"

typedef enum{
	SP_MAIN_WINDOW_ACTIVE,
	SP_GAME_WINDOW_ACTIVE,
	SP_LOAD_WINDOW_ACTIVE,
	SP_SET_MODE_WINDOW_ACTIVE,
	SP_SET_LEVEL_WINDOW_ACTIVE,
	SP_SET_COLOR_WINDOW_ACTIVE

}ACTIVE_WINDOW;

typedef enum{
	SP_MANAGER_QUTT,
	SP_MANAGER_NONE,
}SP_MANAGER_EVENET;

typedef struct {
	SPGameWin* gameWin;
	SPMainWin* mainWin;
	SPLoadGamesWin* loadGamesWin;
	SPsetLevelWin* setLevelWin;
	SPModeWin*  setModeWin;
	SPsetColorWin* setColorWin;
	ACTIVE_WINDOW activeWin;
} SPGuiManager;

SPGuiManager* spManagerCreate();

void spManagerDestroy(SPGuiManager* src);

void spManagerDraw(SPGuiManager* src);

SP_MANAGER_EVENET spManagerHandleEvent(SPGuiManager* src, SDL_Event* event) ;




#endif /* GRAPHICS_CHESSGUIMANAGER_H_ */
