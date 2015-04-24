#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define NUM_PLAYERS 2
#define MYDEBUG
#define NUMRUNS 10

int testGameOver(struct gameState *state)
{
	return isGameOver(state);
}

int main(int argc, char* argv[])
{
    printf("\n\n****BEGIN UNITTEST4: isGameOver****\n");
	struct gameState *m_state = newGame();
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
    int runs;
	int i;
	
	srand(time(NULL));
	
	for(runs = NUMRUNS; runs > 0; runs--)
	{
		printf ("State initalization.....");
		initializeGame(NUM_PLAYERS, k, 5, m_state);
		printf("PASS\n");
		
		printf("ProvCountTest.....");
		int flag = 0;
		int setProvs = rand() % 2;
		
		if(setProvs < 0)
			setProvs *= -1;
		m_state->supplyCount[province] = setProvs;
		if(setProvs == 0)
		{
			if(testGameOver(m_state) != 1)
			{
				printf("FAIL - shouldBeGameOver;");
				flag = 1;
			}
		}
		else
		{
			if(testGameOver(m_state) != 0)
			{
				printf("FAIL - shouldNotBeGameOver;");
				flag = 1;
			}
		}
		if(flag == 0)
			printf("PASS");
		printf("\n");
	}
	for(runs = NUMRUNS; runs > 0; runs--)
	{
		printf ("State initalization.....");
		initializeGame(NUM_PLAYERS, k, 5, m_state);
		printf("PASS\n");
		
		printf("SupplyCountTest.....");
		int flag = 0;
		int supplyCount = 0;
		for(i = 0; i < 25; i++)
		{
			int setSupply = rand() % 7;
			if(setSupply < 0)
				setSupply *= -1;
			m_state->supplyCount[i] = setSupply;
			if(setSupply == 0)
				supplyCount++;
		}
		
		if(supplyCount >= 3 && testGameOver(m_state) != 1)
		{
			printf("FAIL - shouldBeGameOver;");
			flag = 1;
		}
		else if(supplyCount < 3 && testGameOver(m_state) != 0)
		{
			printf("FAIL - shouldNotBeGameOver;");
			flag = 1;
		}
		if(flag == 0)
			printf("PASS");
		printf("\n");
	}
	
	printf("****END UNITTEST 4****\n");
    return 0;
}
