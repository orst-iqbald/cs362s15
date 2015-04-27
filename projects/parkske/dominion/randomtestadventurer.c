#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define NUM_PLAYERS 2
//#define MYDEBUG
#define NUMRUNS 10
#define STACK_DECK 10
#define GAINLOSECOUNT 10

//test wrapper for the actual doAdventurer call
int testDoAdventurer(struct gameState *state, int player, int* temphand, int drawntreasure, int cardDrawn, int z)
{
	return doAdventurer(state, player, temphand, drawntreasure, cardDrawn, z);
}

//simple procedure to count all treasure amount
int getTreasureCount(struct gameState *state, int player)
{
	int treasures = 0;
	int handCount = numHandCards(state);
    int deckCount = state->deckCount[player];
	int i;
	for(i = 0; i < handCount; i++)
	{
		int card = handCard(i, state);
		switch(card)
		{
			case gold:
			case silver:
			case copper:
				treasures++;
				break;
			default:
				break;
		}
	}
    for(i = 0; i < deckCount; i++)
	{
		int card = state->deck[player][i];
		switch(card)
		{
			case gold:
			case silver:
			case copper:
				treasures++;
				break;
			default:
				break;
		}
	}
	return treasures;
}

void printWholeDeck(struct gameState *state, int player)
{
    int i;
    for(i = 0; i < state->deckCount[player]; i++)
    {
        printf("Deckcard %d: %d\n", i+1, state->deck[player][i]);
    }
    for(i = 0; i < state->handCount[player]; i++)
    {
        printf("Handcard %d: %d\n", i+1, state->hand[player][i]);
    }
}

int main(int argc, char* argv[])
{
    int failedTests = 0;
    int player = 0;
	int tempHand[MAX_HAND];
	int drawntreasure = 0;
	int cardDrawn = 0;
	int z = 0;
	int i = 0;
    int color = 0;
    if(argc == 2 && strcmp(argv[1], "-c") == 0)
        color = 1;
    srand(time(NULL));    
    struct gameState *m_state = newGame();
    
    printf("\n\n************** BEGIN RANDOMCARDTEST 1: doAdventurer **************\n");
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
	printf ("randomAdventurer State initalization.....");
	initializeGame(NUM_PLAYERS, k, 5, m_state);
	printf("PASS\n");
    
    /*
    * At this point, each player has 5 cards in hand, 5 cards in deck. Of these 10 cards
    *  3 are victory cards and 7 are treasure cards
    */
    
	//confirm 7 treasure cards are present
    printf("randomAdventurer test 7 card precondition.....");
    int testTreasure = getTreasureCount(m_state, player);
    if (testTreasure != 7)
    {
        printf("FAIL: count: %d\n", testTreasure);
    }
    else
    {
        printf("PASS\n");
    }
    
    printWholeDeck(m_state, player);
    
    //gain or lose a random number of treasure cards, up to a full deck count
    int gain_or_lose = rand() % 2;
    if(gain_or_lose == 0) //gain case
    {
        int preDeckCount = m_state->deckCount[player]; //track start point
        int actualGainedCards = 0; //not every card is in play
        
        //we can gain 0 up to MAX_DECK - current deck count
        int numCardsGain = rand() % (MAX_DECK - m_state->deckCount[player] + 1);
        assert(numCardsGain + m_state->deckCount[player] <= MAX_DECK);
        assert(numCardsGain + m_state->deckCount[player] >= 0);
        //gain a random card
        for(i = 0; i < numCardsGain; i++)
        {
            if(gainCard((rand() % treasure_map + 1), m_state, 1, player) >= 0)
            {
                actualGainedCards++;
            }
        }
#ifdef MYDEBUG
        printf("Predeck count: %d\n", preDeckCount);
        printf("GainCards: %d\n", numCardsGain);
        printf("Actual gained: %d\n", actualGainedCards);
        printf("Deck count: %d\n", m_state->deckCount[player]);
#endif
        assert(m_state->deckCount[player] == preDeckCount + actualGainedCards);
    }
    else //lose case
    {
        int preHandCount = m_state->handCount[player]; //track start point
        
        //we can lose 0 up to handCount cards
        int numCardsLose = rand() % m_state->handCount[player] + 1;
        assert(numCardsLose <= m_state->handCount[player]);
        assert(numCardsLose >= 0);
        
        //lose a random card
        for(i = 0; i < numCardsLose; i++)
        {
            //lose the card randomly from hand
            int losePos = rand() % m_state->handCount[player];
            discardCard(losePos, player, m_state, 1);
        }
        assert(m_state->handCount[player] == preHandCount - numCardsLose);
    }
    
    printf("AFTER\n\n");
    printWholeDeck(m_state, player);
    /*
    //pre-test variables
	int m_handCount = numHandCards(m_state);
	int m_preTreasure = getTreasureCount(m_state, player);
	
	//stack the player's deck so we can run our tests
    //the deck will likely run out, but shuffle should give us more
	int d;
	for(d = 0; d < STACK_DECK; d++)
	{
		gainCard(copper, m_state, 1, player);
        gainCard(silver, m_state, 1, player);
        gainCard(gold, m_state, 1, player);
	}
	for(d = 0; d < STACK_DECK; d++)
	{
		gainCard(curse, m_state, 1, player);
	}
	
	for(i = 0; i < NUMRUNS; i++)
	{
		int doTempCompare = 0;
        int fakeDeckCounter = m_state->deckCount[player];//Create holder for the deck count
        int fakeHand[player][MAX_HAND]; //create fake hand
        int fakeHandCount = 0;
        int fakeDeck[player][MAX_DECK]; //create fake deck
        int fakeDeckCount = 0;
        int fakeDiscard[player][MAX_DECK]; //create fake discard
        int fakeDiscardCount = 0;
        int fakeTempHand[MAX_DECK];
        int fakeTempHandCounter = 0;
        int fakeStartDiscardCount = fakeDiscardCount;
        int fakeStartDeckCount = fakeDeckCount;
        
        //odd test case 1: deckCount is 0, force shuffle
		if(i == NUMRUNS - 1)
		{
			printf("***  Testing empty deck draw card case  ***\n");
			while(m_state->deckCount[player] > 0)
			{
				if(drawCard(player, m_state) >= 0)
					m_handCount++;
				m_state->discard[player][m_state->discardCount[player] ] = m_state->hand[player][m_handCount - 1];
				m_state->discardCount[player]++;
				m_handCount--;
			}
		}
		
		//normal use case, gain 2 treasure cards, return without error, discard all other cards
        
        //simulate the drawing process without a shuffle to track discarded cards for testing
        //if we have to shuffle, this becomes difficult to track, so don't
        if(m_state->deckCount[player] <= 0)
        {
            printf("Shuffle required, cannot track discard\n");
            doTempCompare = 1;
        }
        else
        {
            fakeDeckCounter = m_state->deckCount[player];//Create holder for the deck count
            fakeHandCount = 0;
            fakeDeckCount = 0;
            fakeDiscardCount = 0;
            fakeTempHandCounter = 0;
            //populate fake Hand to emulate actual hand
            int i;
            for(i = 0; i < m_state->handCount[player]; i++)
            {
                fakeHand[player][i] = handCard(i, m_state);
                fakeHandCount++;
            }
            //populate the fake Deck to emulate actual deck
            for(i = 0; i < m_state->deckCount[player]; i++)
            {
                fakeDeck[player][i] = m_state->deck[player][i];
                fakeDeckCount++;
            }
            //populate the fake Discard to emulate actual discard
            for(i = 0; i < m_state->discardCount[player]; i++)
            {
                fakeDiscard[player][i] = m_state->discard[player][i];
                fakeDiscardCount++;
            }
            //make sure the counts match
            if(fakeHandCount != m_state->handCount[player])
            {
                printf("fakeHandCount mismatch\n");
                doTempCompare = 1;
                break;
            }
            if(fakeDeckCount != m_state->deckCount[player])
            {
                printf("fakeDeckCount mismatch\n");
                doTempCompare = 1;
                break;
            }
            if(fakeDiscardCount != m_state->discardCount[player])
            {
                printf("fakeDiscardCount mismatch\n");
                doTempCompare = 1;
                break;
            }
            
            //simulate the adventurer
            i = 0;
            while(i < 2)
            {
                if(fakeDeckCount <= 0) //means we need to shuffle, abort test
                {
                    doTempCompare = 1;
                    break;
                }
                fakeHand[player][fakeHandCount] = fakeDeck[player][fakeDeckCount - 1];
                fakeDeckCount--;
                fakeHandCount++;
                int fakeCard = fakeHand[player][fakeHandCount - 1];
                switch(fakeCard)
                {
                    case copper:
                    case silver:
                    case gold:
                        i++;
                        break;
                    default:
                        fakeTempHand[fakeTempHandCounter] = fakeCard;
                        fakeHandCount--;
                        fakeTempHandCounter++;
                }
            }
            if(doTempCompare == 0)
            {
                while (fakeTempHandCounter - 1 > 0)
                {
                    fakeDiscard[player][fakeDiscardCount] = fakeTempHand[z - 1];
                    fakeDiscardCount++;
                    fakeTempHandCounter--;
                }
            }
        }
        
        //test cases
		printf("Adventurer Returns non-error.....");
		if(testDoAdventurer(m_state, player, tempHand, drawntreasure, cardDrawn, z) < 0)
		{
			printf("FAIL - returns negative\n");
            failedTests++;
			if(m_state->deckCount[player] <= 0)
            {
                if(m_state->discardCount[player] > 0)
                {
                    printf("Adventurer testing shuffle.....");
                    if(shuffle(player, m_state) != 0)
                    {
                        printf("FAIL - Cannot shuffle empty deck\n");
                        failedTests++;
                    }
                }
            }
			if(i == NUMRUNS - 1)
			{
				printf("*** END empty deck draw card case ***\n");
			}
			continue;
		}
		else
			printf("PASS\n");
		
		printf("Adventurer State is not null.....");
		if(m_state == NULL)
		{
			printf("FAIL - stateNull\n");
            failedTests++;
		}
		else
		{
			printf("PASS\n");
			printf("Adventurer Hand Count +2.....");
			m_handCount += 2;
			if(numHandCards(m_state) != m_handCount)
			{
				printf("FAIL - handCount\n");
                failedTests++;
			}
			else
				printf("PASS\n");
			printf("Adventurer Treasure +2.....");
			m_preTreasure += 2;
			if(m_preTreasure != getTreasureCount(m_state, player))
			{
				printf("FAIL - treasureCount\n");
                failedTests++;
			}
			else
				printf("PASS\n");
		}
        //compare simulated discards to actual
        if(doTempCompare == 0)
        {
            printf("Adventurer Discard test.....");
            if(m_state->deckCount[player] != fakeDeckCount - fakeStartDeckCount)
            {
                printf("FAIL - deckCount mismatch;");
                failedTests++;
            }
            if(m_state->discardCount[player] != fakeDiscardCount - fakeStartDiscardCount)
            {
                printf("FAIL - discardCount mismatch;");
                failedTests++;
            }
            else //test that the discarded cards match the simulation
            {
                int flag = 0;
                int j;
                for(j = fakeDiscardCount - 1; j >= 0; j--)
                {
                    if(m_state->discard[player][j] != fakeDiscard[player][j])
                        flag = 1;
                }
                if(flag != 0)
                {
                    printf("FAIL - discardCards mismatch");
                    failedTests++;
                }
                else
                    printf("PASS");
            }
            printf("\n");
        }
		if(i == NUMRUNS - 1)
		{
			printf("*** END empty deck draw card case ***\n");
		}
	}
	
    if(failedTests > 0)
        if(color)
            printf("\033[1;31mFailed %d tests\033[0m\n", failedTests);
        else
            printf("Failed %d tests\n", failedTests);
    else
        if(color)
            printf("\033[1;32mFailed %d tests\033[0m\n", failedTests);	
        else
            printf("Failed %d tests\n", failedTests);	*/
	printf("************** END CARDTEST 1: doAdventurer **************\n");
    return 0;
}