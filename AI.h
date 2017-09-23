/*
 * AI.h
 *
 *  Created on: 14 בספט׳ 2017
 *      Author: User
 */

#ifndef AI_H_
#define AI_H_
#include <stdbool.h>
#include "mediator.h"

//for minmax algorithem;
extern int compMove[3];
int score_board(int board[], int turn);

int minmax(int minmaxBoard[], int times, int color, int alpha, int beta, bool player); // status = start (0), and (1)

#endif /* AI_H_ */
