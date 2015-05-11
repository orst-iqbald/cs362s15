/*	Student: Philip Lewallen
	Class: CS362-400 Software Engineering II
	Assignment: Assignment 4
*/

#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <assert.h>

int main(int argc, char **argv)
{
	srand(time(NULL));

	struct gameState *game = newGame();
	int gameStatus;
 	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int players = ((rand() % 3) + 2);
	int seed = rand() % 62000;
	int currentPlayer = ((rand() % players);

	gameStatus = initializeGame(players, k, seed, game);


	adventurerTest(game, currentPlayer, z);

	return 0;
}

/*
What I need to do.

First I have to initialize the game state state 

then I need to create some random variables which include and go slightly out of the range
of the stated acceptable ranges for each variable.


Write a function which encapuslates this so it can be called multiple times.
	Think about why the professor did not encapsulate his tests in another function.
	Was this done to be illustrate the tests or to rate the code coverage in a different way? 
	I think it was done for simplicity of understanding of the function as my code coverage results
	showed the code in the functions was being called as expected.

	Decide what my next card should be.  Smithy?  Not gardens.
*/
