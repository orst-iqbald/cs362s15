#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define NUM_PLAYERS 2
//#define MYDEBUG
#define NUMRUNS 100
#define STACK_DECK 10
#define GAINLOSECOUNT 10

//test wrapper for the actual doAdventurer call
int testDoAdventurer(struct gameState *state, int player, int* temphand, int drawntreasure, int cardDrawn, int z)
{
	return doAdventurer(state, player, temphand, drawntreasure, cardDrawn, z);
}

//simple procedure to count all treasure amount
int getHandTreasureCount(struct gameState *state, int player)
{
	int treasures = 0;
	int handCount = numHandCards(state);
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
    return treasures;
}

//simple procedure to count all treasure amount
int getTreasureCount(struct gameState *state, int player)
{
	int treasures = 0;
	int handCount = numHandCards(state);
    int deckCount = state->deckCount[player];
    int discardCount = state->discardCount[player];
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
    
    for(i = 0; i < discardCount; i++)
	{
		int card = state->discard[player][i];
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
    for(i = 0; i < state->discardCount[player]; i++)
    {
        printf("Discard %d: %d\n", i+1, state->discard[player][i]);
    }
}

int main(int argc, char* argv[])
{
    int passedTests = 0;
    int player = 0;
	int tempHand[MAX_HAND];
	int drawntreasure = 0;
	int cardDrawn = 0;
	int z = 0;
	int i = 0;
    int j = 0;
    int color = 0;
    if(argc == 2 && strcmp(argv[1], "-c") == 0)
        color = 1;
    srand(time(NULL));    
    
    /*
    * gameState initialization test
    */
    printf("\n\n************** BEGIN RANDOMCARDTEST 1: doAdventurer **************\n");
    struct gameState *m_state = newGame();
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
	printf ("randomAdventurer State initalization.....");
	initializeGame(NUM_PLAYERS, k, 5, m_state);
	assert(m_state);
    assert(m_state->numPlayers == NUM_PLAYERS && "2 == 2");
    assert(m_state->whoseTurn == player && "0 == 0");
    assert(m_state->handCount[player] == 5 && "5 == 5");
    assert(m_state->deckCount[player] == 5 && "5 == 5");
    assert(m_state->playedCardCount == 0 && "0 == 0");
    printf("PASS\n");
    
    /*
    * At this point, each player has 5 cards in hand, 5 cards in deck. Of these 10 cards
    *  3 are victory cards and 7 are treasure cards
    */
	//confirm 7 treasure cards are present
    printf("randomAdventurer test 7 card precondition.....");
    int testTreasure = getTreasureCount(m_state, player);
    assert(testTreasure == 7 && "7 == 7");
    printf("PASS\n");
    
#ifdef MYDEBUG
    printf("BEFORE\n\n");
    printWholeDeck(m_state, player);
    printf("\n");
#endif
    /*
    * Primary test loop, does randomization of Deck and
    * then runs adventurer test, checks treasure output
    * values at the end of each test.
    */
    for(i=0; i<NUMRUNS; i++)
    {
        /*
        * Random test setup for Deck
        * gain or lose a random number of cards. Two cases exist:
        *   Gain: Cards are added to deck, from supply
        *       Note: This may eventually exhaust the whole deck
        *   Lose: Cards are removed from deck, to discard
        */
        int gain_or_lose = rand() % 2;
        if(gain_or_lose == 0) //gain case
        {
            int preDeckCount = m_state->deckCount[player]; //track start point
            int actualGainedCards = 0; //not every card is in play
            
            //we can gain 0 up to MAX_DECK - current deck count
            int numCardsGain = rand() % (1+ (MAX_DECK - m_state->deckCount[player] + 1));
            if(numCardsGain != 0)
                numCardsGain--; //protecting against divide by 0 above
            assert(numCardsGain + m_state->deckCount[player] <= MAX_DECK && "too many");
            assert(numCardsGain + m_state->deckCount[player] >= 0 && "too few");
            //gain a random card
            for(j = 0; j < numCardsGain; j++)
            {
                if(gainCard((rand() % treasure_map + 1), m_state, 1, player) >= 0)
                {
                    //we only actually gain a card if it's in play
                    actualGainedCards++;
                }
            }
    #ifdef MYDEBUG
            printWholeDeck(m_state, player);
            printf("Predeck count: %d\n", preDeckCount);
            printf("GainCards: %d\n", numCardsGain);
            printf("Actual gained: %d\n", actualGainedCards);
            printf("Deck count: %d\n", m_state->deckCount[player]);
    #endif
            assert(m_state->deckCount[player] == preDeckCount + actualGainedCards);
        }
        else //lose case
        {
            int preDeckCount = m_state->deckCount[player]; //track start point
            int preDiscardCount = m_state->discardCount[player];
            
            //we can lose 0 up to deckCount cards
            int numCardsLose = rand() % (m_state->deckCount[player] + 1);
            assert(numCardsLose <= m_state->deckCount[player]);
            assert(numCardsLose >= 0);
            
            //lose a random card
            for(j = 0; j < numCardsLose; j++)
            {
                int m_deckCount = m_state->deckCount[player];
                int m_discardCount = m_state->discardCount[player];
                
                //lose the card randomly from deck
                int losePos = rand() % m_state->deckCount[player];
                //move the card to the top of discard
                m_state->discard[player][m_discardCount] = m_state->deck[player][losePos];
                // printf("Set discard %d to %d\n", m_discardCount, m_state->deck[player][losePos]);
                // printf("losePos: %d card: %d\n", losePos, m_state->deck[player][losePos]);
                //move the last card in deck into spot occupied by losePos, if it's not last card
                if(m_discardCount - 1 > 0 || losePos != m_state->deckCount[player] - 1)
                {
                    m_state->deck[player][losePos] = m_state->deck[player][m_deckCount - 1];
                    // printf("Set %d to %d\n", losePos, m_state->deck[player][m_deckCount - 1]);
                    //set the card slot we just moved from to -1
                    m_state->deck[player][m_deckCount - 1] = -1;
                    // printf("Set %d to -1\n", m_deckCount - 1);
                }
                //realign the counts
                m_state->deckCount[player]--;
                m_state->discardCount[player]++;
            }
    #ifdef MYDEBUG
            printWholeDeck(m_state, player);
            printf("Predeck count: %d\n", preDeckCount);
            printf("Prediscard count: %d\n", preDiscardCount);
            printf("LoseCards: %d\n", numCardsLose);
            printf("Deck count: %d\n", m_state->deckCount[player]);
            printf("Discard count: %d\n", m_state->discardCount[player]);
    #endif
            assert(m_state->deckCount[player] == preDeckCount - numCardsLose);
            assert(m_state->discardCount[player] == preDiscardCount + numCardsLose);
        }
        
        /*
        *   Now that the deck has been randomized, we can use adventurer and test
        */
            testTreasure = getTreasureCount(m_state, player); //total treasures in deck
            int h_treasure = getHandTreasureCount(m_state, player); //ttl treasure in hand
            int test = testDoAdventurer(m_state, player, tempHand, drawntreasure, cardDrawn, z);
    #ifdef MYDEBUG
            printf("Total treasure: %d\n", testTreasure);
            printf("h_Treasure: %d\n", h_treasure);
            printf("test = %d\n", test);
    #endif
            if(test < 0)
            {
                int failTreasure = (getHandTreasureCount(m_state, player) - h_treasure);
    #ifdef MYDEBUG
                printf("Fail treasure: %d\n", failTreasure);
                printf("New h_treasure: %d\n", h_treasure + failTreasure);
    #endif
                assert(h_treasure <= h_treasure + failTreasure);
                assert(h_treasure + failTreasure < 3 + h_treasure);
            }
            else
            {
    #ifdef MYDEBUG
                assert(h_treasure + 2 == getHandTreasureCount(m_state, player));
    #endif
            }
        printf("Random Test %d......PASS\n", i);
        passedTests++;
    }
    printf("Passed %d of %d tests\n", passedTests, NUMRUNS);
	printf("************** END RANDOMCARDTEST 1: doAdventurer **************\n");
    return 0;
}