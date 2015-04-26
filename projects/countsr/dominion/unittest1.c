#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

// Unit test for isGameOver()

void testIsGameOver() {
	int i;
    struct gameState G;

    printf ("TESTING isGameOver():\n");
    //Test Province supply empty
    //all supply counts are set to 1
    for (i = 0; i < 25; i++) 
		G.supplyCount[i] = 1; 
	//Province supply set to 0 cards
	G.supplyCount[province] = 0;

	if (isGameOver(&G) == 1)
        printf("IsGameOver(): PASS when Province supply count has 0 cards\n");
    else
        printf("IsGameOver(): FAIL when Province supply count has 0 cards\n");

    //Province supply set to 1 cards
    for (i = 0; i < 25; i++) 
		G.supplyCount[i] = 1; 
    G.supplyCount[province] = 1;
	if (isGameOver(&G) == 0)
        printf("IsGameOver(): PASS when Province supply count has 1 cards\n");
    else
        printf("IsGameOver(): FAIL when Province supply count has 1 cards\n");

	//Test for at least 3 supplies empty
	//3 supply counts are set to 0
	for (i = 0; i < 3; i++)  {
		G.supplyCount[i] = 0; 
	}

	if (isGameOver(&G) == 1)
        printf("IsGameOver(): PASS when 3 supply counts have 0 cards\n");
    else
        printf("IsGameOver(): FAIL when 3 supply counts have 0 cards\n");

	//All supply counts are set to 1
	for (i = 0; i < 25; i++)  {
		G.supplyCount[i] = 1; //all supply counts are set to 1 (1 card in each supply pile)
	}

	if (isGameOver(&G) == 0)
        printf("IsGameOver(): PASS when all supply counts have 1 card\n");
    else
        printf("IsGameOver(): FAIL when all supply counts have 1 card\n");
        
}

int main(int argc, char *argv[])
{
    testIsGameOver();

    return 0;
}


