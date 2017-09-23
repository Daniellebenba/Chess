/*
 * CHessWin.h
 *
 *  Created on: 19 בספט׳ 2017
 *      Author: User
 */

#ifndef GRAPHICS_CHESSWIN_H_
#define GRAPHICS_CHESSWIN_H_

#include <SDL.h>
#include <SDL_video.h>
/*
typedef enum {
//Add messages here
} SP_EVENT_MSG;
*/
typedef struct chess_window_t CHessWin;

struct chess_window_t {
	SDL_Window* window;
	SDL_Renderer* renderer;
	void (*destroyWindowFunc)(CHessWin*);
	void (*drawFunc)(CHessWin*);
	//SP_EVENT_MSG (*handleEventFunc)(SPTicTacToe*, SDL_Event*);
};

//int isClickOnBack(int x, int y);

#endif /* GRAPHICS_CHESSWIN_H_ */
