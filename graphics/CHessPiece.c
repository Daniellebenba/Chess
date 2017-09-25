/*
 * CHessPiece.c
 *
 *  Created on: 25 בספט 2017
 *      Author: User
 */

#include <SDL.h>
#include <assert.h>
#include <stdio.h>
#include "CHessPiece.h"

SDL_Texture* setPicForPiece(Piece* src, char* path){
	SDL_Surface* loadingSurface = NULL;
	loadingSurface = SDL_LoadBMP(path );
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spPieceDestroy(src);
		return NULL ;
	}
	if (loadingSurface != NULL){
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(src->windowRender, loadingSurface);
	SDL_FreeSurface(loadingSurface);
	return texture;
	}
	return NULL;
}
Piece* spPieceCreate(const char* image,SDL_Renderer* windowRender,SDL_Rect* location){
	Piece* res = (Piece*) calloc(sizeof(Piece), sizeof(char));;
	res->location = location;
	res->windowRender = windowRender;
	res->val=0; //value of piece
	res->color=0;
	res->boardLocation=0;

	//image
		res->pieceTexture = setPicForPiece( res, image);
		if (res->pieceTexture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			spPieceDestroy(res);
			return NULL ;
		}
		return res;


}
void spPieceDestroy(Piece* src){
	if (!src) {
		return;
	}
//	if (src->location != NULL ) {
//		free(src->location);
//	}
	if (src->pieceTexture != NULL ) {
		SDL_DestroyTexture(src->pieceTexture);
	}
	if (src->windowRender != NULL ) {
		SDL_DestroyRenderer(src->windowRender);
	}
	free(src);
}


void spPieceDraw(Piece* src){
	if(src == NULL){
			return;
		}
		//SDL_RenderClear(src->windowRender);
		SDL_RenderCopy(src->windowRender, src->pieceTexture, NULL, src->location);
//		//SDL_RenderPresent(src->windowRender);

}
void PieceHandleEvent(Piece* src, SDL_Event* event){};
