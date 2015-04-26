/* -----------------------------------------------------------------------
* a unit test for fulldeck() in dominion.c
* Include the following lines in your makefile:
*
* unittest3: unittest3.c dominion.o rngs.o
*      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
* -----------------------------------------------------------------------
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1


int main() {
    
    int seed = 1000;
    int players[] = {2, 3, 4};
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    
    struct gameState play;
    
    #if (NOISY_TEST == 1)
        printf ("TESTING fulldeck():\n");
    #endif
    
    int fails=0;
    int passes=0;
    
    //couldnt get function to return -1, dont know how its possible

    int i;
    // testing game for all ranges of players
    for (i = 0; i <= 2; i++)
    {
        //clear game
        memset(&play, 23, sizeof(struct gameState));
        //initialize new game
        int start = initializeGame(players[i], k, seed, &play);
        
        //  no need to contine if this fails
        assert( start == 0);
        
        #if (NOISY_TEST == 1)
            printf("\nGame just initilized with %i players\n", players[i]);
         #endif
        
        int x;
        for( x=0; x < players[i]; x++)
        {
            
            if( x == 0 && play.deckCount[0] == 5 )
            {
                passes++;
                #if (NOISY_TEST == 1)
                    printf("player 1 has 5 cards in their deck: Pass\n");
                #endif
                
                    if( x == 0 && fullDeckCount(x,silver, &play) == 0)
                    {
                        passes++;
                        #if (NOISY_TEST == 1)
                            printf("player 1  has %i silver coins: Pass\n", fullDeckCount(x,silver, &play));
                         #endif
                    }
                    else
                    {
                        fails++;
                        #if (NOISY_TEST == 1)
                            printf("player 1  should not have any silver coins: Fail\n");
                        #endif
                    }
                
                //buy a silver coin
                buyCard(silver, &play);
                #if (NOISY_TEST == 1)
                    printf("Player 1 should have bought one silver coin: ");
                #endif
                if( x == 0 && fullDeckCount(x,silver, &play) == 1)
                {
                    passes++;
                    #if (NOISY_TEST == 1)
                        printf("Pass\n");
                    #endif
                }
                else
                {
                    fails++;
                    #if (NOISY_TEST == 1)
                        printf("Fail\n");
                    #endif
                }
            }
            else if ( x == 0 && play.deckCount[0] > 5)
            {
                fails++;
                #if (NOISY_TEST == 1)
                    printf("player 1 has 5 cards in their deck: Fail\n");
                #endif
            }
            
            if( x  > 0 && play.deckCount[x] > 5 )
            {
                #if (NOISY_TEST == 1)
                    printf("Player %i shoudl have %i cards: ", x+1, play.deckCount[x]);
                #endif

                if ( play.deckCount[x] == 10)
                {
                    passes++;
                     #if (NOISY_TEST == 1)
                        printf("Pass\n");
                    #endif
                }
                else
                {
                    fails++;
                     #if (NOISY_TEST == 1)
                        printf("Fail\n");
                    #endif
                }
                
                
                #if (NOISY_TEST == 1)
                    printf("Player %i has 7 copper coins cards: ", x+1);
                #endif
                
                int count = fullDeckCount(x,copper, &play);
                if ( count == 7)
                {
                    passes++;
                    #if (NOISY_TEST == 1)
                        printf("Pass\n");
                    #endif
                }
                else
                {
                    fails++;
                    #if (NOISY_TEST == 1)
                        printf("Fail\n");
                    #endif
                }

                #if (NOISY_TEST == 1)
                    printf("Player %i has 3 copper coins cards: ", x+1);
                #endif
                
                count = fullDeckCount(x,estate, &play);
                if ( count == 3)
                {
                    passes++;
                    #if (NOISY_TEST == 1)
                        printf("Pass\n");
                    #endif
                }
                else
                {
                    fails++;
                    #if (NOISY_TEST == 1)
                        printf("Fail\n");
                    #endif
                }
                
                #if (NOISY_TEST == 1)
                    printf("Player %i has 0 smithy cards: ", x+1);
                #endif
                
                count = fullDeckCount(x,smithy, &play);
                if ( count == 0)
                {
                    passes++;
                    #if (NOISY_TEST == 1)
                        printf("Pass\n");
                    #endif
                }
                else
                {
                    fails++;
                    #if (NOISY_TEST == 1)
                        printf("Fail\n");
                    #endif
                }
            }
        }
    }
    
    #if (NOISY_TEST == 1)
        printf("the # of fails = %i\n", fails);
        printf("the # of passes = %i\n", passes);
    #endif
    
    
    if (passes != 33)
    {
        #if (NOISY_TEST == 1)
            printf(" Program Failed");
        #endif
        
        return -1;
    }
    
    
    #if (NOISY_TEST == 1)
        printf("Program Passed");
    #endif
    
    
    return 0;
}

