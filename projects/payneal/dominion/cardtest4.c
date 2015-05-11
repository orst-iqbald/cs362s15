/* -----------------------------------------------------------------------
 * a card test for mine() in dominion.c
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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
    printf ("TESTING mine():\n");
#endif
    
    
    //initialize new game
    int start = initializeGame(players, k, seed, play);
    
    //  no need to contine if this fails
    assert( start == 0);
    
    shuffle(0, play);
    
#if (NOISY_TEST == 1)
    printf("\nGame just initilized with %i players\n", players);
#endif
    
    
    // store the number of treasures originally in hand
    int i;
    int treasuresbefore =0;
    for (i = 0; i < play->handCount[0]; i++)
    {
        if ( play->hand[0][i] == gold || play->hand[0][i] == silver || play->hand[0][i] == copper )
        {
            treasuresbefore++;
        }
    }
    
    
    
#if (NOISY_TEST == 1)
    printf(" this is the  inititial amount of treasures %i\n", treasuresbefore );
#endif
    
    //minfd card
     play->hand[whoseTurn(play)][0] = mine;
    cardMine(play, whoseTurn(play) ,0,  copper, copper);
    
    // store the number of treasures originally in hand
  
    int treasuresafter =0;
    for (i = 0; i < play->handCount[0]; i++)
    {
        if ( play->hand[0][i] == gold || play->hand[0][i] == silver || play->hand[0][i] == copper )
        {
            treasuresafter++;
        }
    }
    
    // this is a card inculded in refactor so teh result is explained there
    
    
#if (NOISY_TEST == 1)
    printf(" this si the  amount of treasures  after using mine %i\n", treasuresafter );
#endif

    
    if ( treasuresafter < treasuresbefore)
    {
        fails++;
        #if (NOISY_TEST == 1)
            printf(" Test failed gold mine is functioning incorrectly");
        #endif
    }
    else
    {
        passes++;
        #if (NOISY_TEST == 1)
            printf(" Test Passed - gold mind works ");
        #endif
    }
    

    if (passes != 1)
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
