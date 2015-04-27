/* -----------------------------------------------------------------------
 * a card test for seahag() in dominion.c
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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
    int players = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    
    struct gameState *play = newGame();
    
    int fails=0;
    int passes=0;
    
#if (NOISY_TEST == 1)
    printf ("TESTING sea hagCard():\n");
#endif
    
    
    //initialize new game
    int start = initializeGame(players, k, seed, play);
    
    //  no need to contine if this fails
    assert( start == 0);
    
    shuffle(0, play);
    
#if (NOISY_TEST == 1)
    printf("\nGame just initilized with %i players\n", players);
#endif
    
    
int curse=0;
#if (NOISY_TEST == 1)
    printf(" the amount of curses prior to sea had  in each hand is 0: ");
#endif
    
    if (curse == 0)
    {
        passes++;
        #if (NOISY_TEST == 1)
            printf("TRUE\n");
        #endif
    }
    else
    {
        fails++;
        #if (NOISY_TEST == 1)
            printf("False\n");
        #endif
    }
    
     #if (NOISY_TEST == 1)
    printf(" this si the amount of actions prior to sea hag 1 : ");
    #endif
    
    if (play->numActions == 1)
    {
        passes++;
        #if (NOISY_TEST == 1)
            printf("TRUE\n");
        #endif
    }
    else
    {
        fails++;
        #if (NOISY_TEST == 1)
            printf("False\n");
        #endif
    }
    
    printf("Total number of curses prior to see hag 10: ");
    
    
    if(play->supplyCount[curse] == 10)
    {
        passes++;
        #if (NOISY_TEST == 1)
            printf("TRUE\n");
        #endif
    }
    else
    {
        fails++;
        #if (NOISY_TEST == 1)
            printf("False\n");
        #endif

    }
    

    //sea hag card
     play->hand[whoseTurn(play)][0] = sea_hag;
     cardSea_hag(play, whoseTurn(play));
    
    int i;
    for (i = 0; i < play->handCount[0]; i++)
    {
        if ( play->hand[2][i] == curse)
        {
            curse++;
        }
    }
    
    printf("Total number of curses after see hag  total = 8: ", play->supplyCount[curse]);
    if(play->supplyCount[curse] == 8 )
    {
        passes++;
        #if (NOISY_TEST == 1)
            printf("TRUE\n");
        #endif
        
    }
    else
    {
        fails++;
        #if (NOISY_TEST == 1)
            printf("False\n");
        #endif

    }
    
    
    
    

    #if (NOISY_TEST == 1)
        printf(" this si the amount of curses after sea hag in hand 1  : ");
    #endif
    
    if (curse == 1)
    {
        passes++;
        #if (NOISY_TEST == 1)
            printf("TRUE\n");
        #endif
    }
    else
    {
        fails++;
        #if (NOISY_TEST == 1)
            printf("False\n");
        #endif
    }

    printf(" this is  the amount of action after a call to sea hag 1: ");
    if ( play->numActions == 1)
    {
        passes++;
        #if (NOISY_TEST == 1)
            printf("TRUE\n");
        #endif
    }
    else
    {
        fails++;
        #if (NOISY_TEST == 1)
            printf("False\n");
        #endif
    }


    if (passes != 6)
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
