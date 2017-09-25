/*
 * CHessPiece.h
 *
 *  Created on: 25 בספט 2017
 *      Author: User
 */

#ifndef GRAPHICS_CHESSPIECE_H_
#define GRAPHICS_CHESSPIECE_H_

//#include "Widget.h"
typedef enum {
	SP_Piece_BACK
} SP_PIECE_EVENT;

typedef struct {
	SDL_Texture* pieceTexture;
	SDL_Renderer* windowRender;
	SDL_Rect* location;
	int val; //value of piece
	int color;
	int boardLocation;
}Piece;


Piece* spPieceCreate(const char* image,SDL_Renderer* windowRender,SDL_Rect* location);
void spPieceDestroy(Piece* src);
void spPieceDraw(Piece* src);
void PieceHandleEvent(Piece* src, SDL_Event* event);


#endif /* CHESSPIECE_H_ */
