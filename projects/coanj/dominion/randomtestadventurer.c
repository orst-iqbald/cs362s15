/*
	Program: 
	Created on: 
	Author: 
	
	Use: 

	Description: 
*/
 
#include "dominion.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int main () {
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState *g = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, g);

	return 0;
}