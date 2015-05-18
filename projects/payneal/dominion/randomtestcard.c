/* -----------------------------------------------------------------------
 *Ali Payne
 * SE2 Assignmnet 4
 * randomtestadventurer.c
 * - random tester for smithy card
 *
 *compile:
 *      gcc -g -Wall -std=c99 -fpic coverage -lm randomtestcard.c dominion.o rngs.o -o randomtestcard
 * -----------------------------------------------------------------------
 */

#include <stdlib.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#include <time.h>
#include <math.h>

#define TEST_COUNT 1000

// set NOISY_TEST to 0 to remove prints from output
#define NOISY_TEST 1


//function descriptions
//int testrandomAdventureCard(int )

int main() {
   
    //set up the random number
    srand(time(NULL));
    
    // set seed
    int seed = rand();
    
    //set number of players
    int players = 2;
    
    //left over not really necessary
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    
    // start the new game
    struct gameState play;
    
    //created to loop as many test cases as defined fro test count
    int loopAlltest;
    
    //holds the amount of failures and passes
    int fails=0;
    int passes=0;
    
    #if (NOISY_TEST == 1)
        printf ("________RANDOM TESTING Mind________\n");
    #endif

    
    for (loopAlltest = 0; loopAlltest < TEST_COUNT; loopAlltest++)
    {
        
        // clear the game
        memset(&play, 23, sizeof( struct gameState));
        
        //initialize new game
        int start = initializeGame(players, k, seed, &play);
       
        //no need to contine if this fails
        assert( start == 0);
        
        //shuffle cards
        shuffle(0,&play);
        
        //hold value of treasures originally in hand
        int treasuresbefore =0;
        int treasuresbeforeAmount=0;
        
        
        //set random number or cards in hand
        //should of used rand generator in rngs.c
        int cardsinHand1= play.handCount[0] = (rand() % MAX_HAND +1);

        
        //make one card in the hand a mine card
        play.hand[0][0] = mine;
        
        // there are 25 cards but this card only effecrs gold, silver copper
        //printf(" gold= %i, silver = %i, copper= %i\n", gold, silver, copper);
        
        //for loop
        int i;
        //go through all cards in hand and put a card
        for(i = 1; i < play.handCount[0]; i++)
        {
            //filled entire hand with copper
            //instead could of filled with any type of card 0-25
            //but would of needed to make sure one card was mine and one card was copper
            play.hand[0][i] = copper;
        }
        
        
        // store the number of treasures originally in hand
        for (i = 0; i < play.handCount[0]; i++)
        {
            if ( play.hand[0][i] == gold || play.hand[0][i] == silver || play.hand[0][i] == copper )
            {
                treasuresbefore++;
            }
        }
 
        
        // store the value of tresures
        for (i = 0; i < play.handCount[0]; i++)
        {
            if ( play.hand[0][i] == gold)
            {
                treasuresbeforeAmount += 6;
            }
                
            if (play.hand[0][i] == silver)
            {
                treasuresbeforeAmount += 3;
            }
                
            if (play.hand[0][i] == copper )
            {
                treasuresbeforeAmount +=0;
            }
        }
        
        #if (NOISY_TEST == 1)
            printf(" this is the number of cards in player ones hand %i\n", cardsinHand1);
        
            printf(" this si the amount of treasures before mine was called %i\n", treasuresbefore );
        
            printf(" this is the value of all the tresures in the players hand %i\n\n", treasuresbeforeAmount);
        
        
        #endif
        
        
        // this is only testing when you want to excange copper with silver
        //calling the mine card
        cardMine(&play,0, 0, copper, silver);
      
        //hold value of treasures originally in hand
        int treasuresafter =0;
        int treasuresafterAmount=0;
    
        // store the number of treasures originally in hand
        for (i = 0; i < play.handCount[0]; i++)
        {
            if ( play.hand[0][i] == gold || play.hand[0][i] == silver || play.hand[0][i] == copper )
            {
                treasuresafter++;
            }
        }
        
        // store the value of tresures
        for (i = 0; i < play.handCount[0]; i++)
        {
            if ( play.hand[0][i] == gold)
            {
                treasuresafterAmount += 6;
            }
            
            if (play.hand[0][i] == silver)
            {
                treasuresafterAmount += 3;
            }
            
            if (play.hand[0][i] == copper )
            {
                // has no value
            }
        }

        int cardsinHand2 = play.handCount[0];
        
        #if (NOISY_TEST == 1)
            printf(" this is the number of cards in player ones hand %i\n", cardsinHand2);
        
            printf(" this si the amount of treasures after mine was called %i\n", treasuresafter );
        
            printf(" this is the value of all the tresures in the players hand %i\n\n", treasuresafterAmount);
        
        
        #endif
        
        
        if ( cardsinHand1-1 == cardsinHand2 && treasuresbefore == treasuresafter && treasuresbeforeAmount < treasuresafterAmount )
        {
            passes++;
        }
        else
        {
            fails++;
            printf("***********************FAILED HERE***********************\n" );
        }
        
        
    
    }
    #if (NOISY_TEST == 1)
        printf("Passed = %i\n", passes);
        printf("fails = %i\n", fails);
    
        if ( passes == 1000)
        {
            printf("Program is coreccect");
        }
        else
        {
            printf("there are logical errors in this program");
        }
    
    #endif
    

    return 0;
}
