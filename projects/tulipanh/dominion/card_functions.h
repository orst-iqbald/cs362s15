#ifndef _CARD_FUNCTIONS_H
#define _CARD_FUNCTIONS_H

int adventurer(int * drawntreasure, int * currentPlayer, int * cardDrawn, int * temphand, struct gameState * state);
int smithy(int * currentPlayer, int * handPos, struct gameState * state);
int village(int * currentPlayer, int * handPos, struct gameState * state);
int steward(int * currentPlayer, int * handPos, int * choice1, int * choice2, int * choice3, struct gameState * state);
int mine(int * currentPlayer, int * handPos, int * choice1, int * choice2, int * i, int * j, struct gameState * state);

#endif