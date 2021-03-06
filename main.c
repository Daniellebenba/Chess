/*
 /*
 * main.c
 *
 *  Created on: 16 ����� 2017
 *      Author: User
 */



#include <SDL.h>
#include <SDL_video.h>
#include "CHessGame.h"
#include "graphics/CHessGUIManager.h"

int main(int argc, char** argv){
	  //Start SDL
	      SDL_Init( SDL_INIT_EVERYTHING );


	if (SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL2 INIT
			printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
			return 1;
		}

		SPGuiManager* manager = spManagerCreate();
		if (manager == NULL ) {
			SDL_Quit();
			return 0;
		}
		SDL_Event event;
		while (1) {
			while (SDL_PollEvent(&event)){
			if (spManagerHandleEvent(manager, &event) == SP_MANAGER_QUTT) {
				break;
			}
			spManagerDraw(manager);
			SDL_Delay(1000/60);
			}
		}
		spManagerDestroy(manager);
		SDL_Quit();
		return 0;
	}

