#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>

#define MAXCHOICES 4
#define NUM_PLAYERS 2
#define NUMRUNS 100
//#define MYDEBUG

int testDoSteward(struct gameState *state, int player, int handPos, int* choices)
{
    return doSteward(state, player, handPos, choices);
}

int main(int argc, char* argv[])
{
    int passedTests = 0;
    int failedTests = 0;
	struct gameState *m_state = newGame();
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
	int player = 0;
    int choices[3];
    int i;
    int j;
	srand(time(NULL));
    
    printf("\n\n************** BEGIN RANDOMCARDTEST 4: doSteward **************\n");

    for(i = 0; i < NUMRUNS; i++)
    {
        printf("\nTest number: %d\n", i+1);
        printf ("Steward State initialization.....");
        initializeGame(NUM_PLAYERS, k, 5, m_state);
		assert(m_state);
		assert(m_state->numPlayers == NUM_PLAYERS && "2 == 2");
		assert(m_state->whoseTurn == player && "0 == 0");
		assert(m_state->handCount[player] == 5 && "5 == 5");
		assert(m_state->deckCount[player] == 5 && "5 == 5");
		assert(m_state->playedCardCount == 0 && "0 == 0");
        printf("PASS\n");
        
        /*
        *  Gain or lose a random number of cards in hand, so the
        *  conditions for discarding can be rigorously evaluated
        *  Two cases exist:
        *   Gain: Cards are added to hand, from supply
        *       Note: This may eventually exhaust the whole deck
        *   Lose: Cards are removed from deck, to discard
        */
        int gain_or_lose = rand() % 2;
        if(gain_or_lose == 0) //gain case
        {
            int m_preHandCount = m_state->handCount[player]; //track start point
            int actualGainedCards = 0; //not every card is in play
            
            //we can gain 0 up to MAX_HAND, so long as value < current deck count
            int maxCardsGain = MAX_HAND - m_preHandCount; //most cards we can fit in hand
            if(maxCardsGain > MAX_DECK - m_state->deckCount[player]) //available cards from deck
                maxCardsGain = MAX_DECK - m_state->deckCount[player];
            //choose random value to gain based on our determined limit
            int numCardsGain = rand() % (1+ (maxCardsGain + 1));
            if(numCardsGain != 0)
                numCardsGain--; //protecting against divide by 0 above
            //some protecting asserts to make sure we didn't gain too much
            assert(numCardsGain + m_state->deckCount[player] <= MAX_DECK && 
                   numCardsGain + m_state->handCount[player] <= MAX_HAND);
            assert(numCardsGain + m_state->handCount[player] >= 0);
            //gain a random card
            for(j = 0; j < numCardsGain; j++)
            {
                if(gainCard((rand() % treasure_map + 1), m_state, 2, player) >= 0)
                {
                    //we only actually gain a card if it's in play
                    actualGainedCards++;
                }
            }
            assert(m_state->handCount[player] == m_preHandCount + actualGainedCards);
        }
        else //lose case
        {
            int m_preHandCount = m_state->handCount[player]; //track start point
            
            //we can lose 0 up to handCount cards
            int numCardsLose = rand() % (m_state->handCount[player] + 1);
            assert(numCardsLose <= m_state->handCount[player]);
            assert(numCardsLose >= 0);
            
            //lose a random card
            for(j = 0; j < numCardsLose; j++)
            {   
                //lose the card randomly from deck
                int losePos = rand() % m_state->handCount[player];
                discardCard(losePos, player, m_state, 1);
            }
            assert(m_state->handCount[player] == m_preHandCount - numCardsLose);
        }
        
        
        
        
        /*
		* randomize through each option for choices[0]
        * choices[0] == +2 cards
        * choices[1] == +2 coins
        * choices[<0 || >=3] == trash 2 cards in hand
		*/
        choices[0] = rand() % MAXCHOICES;
        
        //pre-test variables
        int preHandCount = m_state->handCount[player];
        int preCoinCount = m_state->coins;
        int preDeckCount = m_state->deckCount[player];
        int prePlayedCount = m_state->playedCardCount;
        int choice1 = 0;
        int choice2 = 0;
        
        int discardFlag = 0;
        //0= <2 cards
        //1= 2 cards
        //2= >2 cards
        
        int discardCards[3] = {-1, -1, -1};
        //0= discardCard always
        //1= possible trash card #1
        //2= possible trash card #2
		
		//randomize the card we'll discard
        int m_handPos = 0;
        if(preHandCount > 0)
            m_handPos = rand() % preHandCount;
        
        //save card type we will discard for comparison later
        discardCards[0] = handCard(m_handPos, m_state);
        
        //determine how we can set up other discard options
        if (preHandCount == 2) //case2, 1 other card
        {
            //get a card from hand, just not == handPos
            switch(m_handPos)
            {
            case 0:
                choice1 = 1;
                break;
            case 1:
                choice1 = 0;
                break;
            default:
                printf("Error: handPos index outside hand\n");
                break; //TODO, some other kind of error?
            }
            //save discard & trash card info for later
            discardFlag = 1;
            discardCards[1] = handCard(choice1, m_state);
            
        }
        else if (preHandCount > 2) //case 3, both choices can be populated randomly from hand
        {
            //pick choice1 randomly, just not the same as handPos
            choice1 = rand() % preHandCount;
            while(choice1 == m_handPos)
            {
                choice1 = rand() % preHandCount;
            }
            
            //pick choice2 randomly, just not the same as handPos or choice1
            choice2 = rand() % preHandCount;
            while(choice2 == m_handPos || choice2 == choice1)
            {
                choice2 = rand() % preHandCount;
            }
            //save discard & trash card info for later
            discardFlag = 2;
            discardCards[1] = handCard(choice1, m_state);
            discardCards[2] = handCard(choice2, m_state);
        }
        else
        {            
            //case 1, no other cards exist to discard
            //case 1a, we gain two cards in doSteward, we can discard one of them
            if(choices[0] == 1)
            {
                m_handPos = rand() % 2;
                discardCards[0] = handCard(m_handPos, m_state);
            }
            //save discard & trash card info for later
            discardFlag = 0;
        }
        
        //set discard choices to choices array for test call
        choices[1] = choice1;
        choices[2] = choice2;
        
        /* 
        *  we have to modify the handPos index because
        *  the trash occurs first in doSteward.
        *  We modify depending on where m_handPos is
        *  in our hand and whether the trash option
        *  is selected
        */
        switch(choices[0])
        {
        case 1:
        case 2:
            break;
        default:
            if(m_handPos == preHandCount - 1) //handPos is last card in hand
            {
                //if choices[1] is second to last, handPos moves twice
                if(choices[1] == preHandCount - 2)
                    m_handPos = choices[2];
                else
                //otherwise, handPos only moves once
                    m_handPos = choices[1];
            }
            //if handPos is 2nd to last, it moves once
            else if(m_handPos == preHandCount - 2) //handPos is 2nd to last
                m_handPos = choices[2];
            break;
        }
        
        
#ifdef MYDEBUG
        printf("\n*********** DEBUG **************\n");
        printf("PreHandCount: %d\n", preHandCount);
        printf("PreDeckCount: %d\n", preDeckCount);
        printf("PreCoinCount: %d\n", preCoinCount);
        printf("PrePlayedCount: %d\n", prePlayedCount);
        printf("m_handPos: %d\n", m_handPos);
        printf("DiscardFlag: %d\n", discardFlag);
        printf("DiscardCard: %d\n", discardCards[0]);
        printf("DiscardCard1: %d\n", discardCards[1]);
        printf("DiscardCard2: %d\n", discardCards[2]);
        printf("Choices0: %d\n", choices[0]);
        printf("Choices1: %d\n", choices[1]);
        printf("Choices2: %d\n", choices[2]);
        printf("*********** DEBUG **************\n");
#endif
        
        /*****************************************
        *   Generic test cases begin
        *****************************************/
        //test return succeeds without error
        printf("Steward returns 0.....");
        assert(testDoSteward(m_state, player, m_handPos, choices) == 0);
        printf("PASS\n");

        //test that only 1 card is discarded into playedCards ever
        //because discard case should trash cards
        printf("Steward single card discarded, others trashed.....");
        assert(prePlayedCount + 1 == m_state->playedCardCount);
        printf("PASS\n");

        //test discarded card matches the one picked
        printf("Steward Discard card match.....");
        //can only do this if we had a valid enum card to begin with, aka handCount > 0
        if(preHandCount > 0)
        {
#ifdef MYDEBUG
            printf("\n**************** DEBUG ***************\n");
            printf("discardCards enum: %d\n", discardCards[0]);
            printf("playedCards enum: %d\n", (enum CARD)m_state->playedCards[m_state->playedCardCount - 1]);
            printf("**************** DEBUG ***************\n");
#endif
            //assert(discardCards[0] == (enum CARD)m_state->playedCards[m_state->playedCardCount - 1]);
            if(discardCards[0] != (enum CARD)m_state->playedCards[m_state->playedCardCount - 1])
            {
                printf("FAIL\n");
                failedTests++;
            }
            else
            {
                printf("PASS\n");
            }
        }
        else
            printf("Not Applicable\n");
        /*****************************************
        *   Generic test cases end
        *****************************************/
        
        /*****************************************
        *   Choice[0] specific test cases begin
        *****************************************/
        switch(choices[0])
        {
        case 1:
            //test hand +2
            printf("Steward Draw 2 cards.....");
            assert(preHandCount + 1 == m_state->handCount[player]);
            printf("PASS\n");
            
            //test deck -2
            printf("Steward Deck -2 cards.....");
            assert(preDeckCount - 2 == m_state->deckCount[player]);
            printf("PASS\n");
            
            break;
        case 2:
            //test coins +2
            printf("Steward Coins +2.....");
            assert(preCoinCount + 2 == m_state->coins)  ;
            printf("PASS\n");  
            
            //test hand -1
            printf("Steward Hand -1 card.....");
            assert(preHandCount - 1 == m_state->handCount[player]);
            printf("PASS\n");
            
            break;
        default:
            //up to 3 cards removed from hand
            switch(discardFlag)
            {
            case 0:
                //only 1 card was in hand, only 1 card to discard
                //test hand -1
                printf("Steward Hand -1 card.....");
                //assert(preHandCount - 1 == m_state->handCount[player]);
                if(preHandCount - 1 != m_state->handCount[player])
                {
                    printf("FAIL\n");
                    failedTests++;
                }
                else
                    printf("PASS\n");
                break;
            case 1:
                //2 cards in hand: 1 trashed, 1 discarded
                //test hand -2
                printf("Steward Hand -2 cards.....");
                //assert(preHandCount - 2 == m_state->handCount[player]);
                if(preHandCount - 2 != m_state->handCount[player])
                {
                    printf("FAIL\n");
                    failedTests++;
                }
                else
                    printf("PASS\n");
                break;
            case 2:
                //>2 cards in hand: 2 trashed, 1 discarded
                //test hand -3
                printf("Steward Hand -3 cards.....");
                assert(preHandCount - 3 == m_state->handCount[player]);
                printf("PASS\n");
                break;
            }
            break;
        }
		/*****************************************
        *   Choice[0] specific test cases end
        *****************************************/
        passedTests++;
        usleep(10000); //allows randomization to occur better, ran too fast before
    }    
    printf("Completed %d of %d tests\n", passedTests, NUMRUNS);
    printf("Failed test count: %d\n", failedTests);
	printf("************** END RANDOMCARDTEST 2: doSteward **************\n");
    return 0;
}