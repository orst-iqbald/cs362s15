/* -----------------------------------------------------------------------
* a unit test for whoseturn() in dominion.c
* Include the following lines in your makefile:
*
* unittest4: unittest4.c dominion.o rngs.o
*      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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
    int fails=0;
    int passes=0;
    
    #if (NOISY_TEST == 1)
        printf ("TESTING whoesTurn():\n");
    #endif
    
    
    int i;
    for(i = 0; i<3; i++)
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
        
        char again = 'n';
        
        for( x=0; x < players[i]; x++)
        {
            
            int check = whoseTurn(&play);
            #if (NOISY_TEST == 1)
                printf(" is it player %i turn: ", x+1);
             #endif
            if(check == x )
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
            
            endTurn(&play);
            
            if ( x+1 == players[i])
            {
                if (again == 'n')
                {
                    again = 'y';
                    x = -1;
                    
                }
            }
        }
        
        
    }
    
        #if (NOISY_TEST == 1)
        printf("the # of fails = %i\n", fails);
        printf("the # of passes = %i\n", passes);
    #endif
    
    
    if (passes != 18)
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

