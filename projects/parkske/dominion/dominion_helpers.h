#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);
/* Card Effect Functions */
int doAdventurer(struct gameState *state, int currentPlayer, int* temphand,  int drawntreasure, int cardDrawn, int z);
int doSmithy(struct gameState *state, int currentPlayer, int handPos);
int doVillage(struct gameState *state, int currentPlayer, int handPos);
int doTreasureMap(struct gameState *state, int currentPlayer, int handPos, int gold);
int doSteward(struct gameState *state, int currentPlayer, int handPos, int* choices);
#endif
