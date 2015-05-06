/* -----------------------------------------------------------------------
* a unit test for isGameOver() in dominion.c
* Include the following lines in your makefile:
*
* unittest2: unittest2.c dominion.o rngs.o
*      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
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
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    
    struct gameState play;
    
    #if (NOISY_TEST == 1)
        printf ("TESTING isGameOver():\n");
    #endif
    
    int fails=0;
    int passes=0;
    
    int i;
    // testing game for all ranges of players
    for (i =2; i <= MAX_PLAYERS; i++)
    {
        //clear game
        memset(&play, 23, sizeof(struct gameState));
        //initialize new game
        initializeGame(i, k, seed, &play);
        
        #if (NOISY_TEST == 1)
            printf("Game just initilized with %i players: ", i);
         #endif
        
        //  no need to contine if this fails
        assert(isGameOver(&play) == 0);
        
        //make sure game is not over
        if ( isGameOver(&play) == 0 )
        {
            passes++;
            #if (NOISY_TEST == 1)
                printf("Passed\n");
            #endif
        }
        else
        {
            fails++;
            #if (NOISY_TEST == 1)
                printf("Failed\n");
             #endif
        }
        
        // game is over:
        //1.)when providence is at 0
                //if two players 8 providences
                // if more than 2 players 12 providences
        
        int x=0; // for loop
        int provs; // number of providences
        
        if( i == 2) //checking when game is only 2 players
        {
                // two playes so run test on 8 provs
                for( x= 0; x< 9; x++ )
                {
                     #if (NOISY_TEST == 1)
                        printf("Players = %i ", i);
                     #endif
                    
                    provs = x;
                    play.supplyCount[province] = provs;
                    int check = isGameOver(&play);
                    
                    if(provs>= 1) // check prov = 0-7 that game is not over
                     {
                         #if (NOISY_TEST == 1)
                            printf("Providens = %i  game is alive: ", provs);
                         #endif
           
                         if(check == 0 ) // game is not over
                         {
                             passes++;
                              #if (NOISY_TEST == 1)
                                printf(":PASSED\n");
                             #endif
                         }
                         else // game is over but it shouldnt be
                         {
                             fails++;
                              #if (NOISY_TEST == 1)
                                printf(":Failed(game over but shouldnt be)\n");
                             #endif
                         }
                         
                     }
                     else   //check on prov =8 that game is over
                     {
                        #if (NOISY_TEST == 1)
                            printf("Providens = %i  game is over: ", provs);
                         #endif
                         
                        if(check == 1)
                        {
                            passes++;
                            #if (NOISY_TEST == 1)
                                printf("PASSED\n");
                            #endif
                            
                        }
                        else
                        {
                            fails++;
                            #if (NOISY_TEST == 1)
                                printf("Failed (game not over but should be)\n");
                            #endif
                        }
                     }
                }
            }
        else // checking when game is more than 2 players
        {
                //more than 2 plays so run test on 12 provs
                for( x= 0; x< 13; x++ )
                {
                    #if (NOISY_TEST == 1)
                        printf("Players = %i ", i);
                    #endif
                    
                    provs = x;
                    play.supplyCount[province] = provs;
                    int check = isGameOver(&play);
                    
                    if(provs>= 1) // check prov = 0-7 that game is not over
                    {
                        #if (NOISY_TEST == 1)
                            printf("Providens = %i  game is alive: ", provs);
                        #endif
                        
                        if(check == 0 ) // game is not over
                        {
                            passes++;
                            #if (NOISY_TEST == 1)
                                printf(":PASSED\n");
                            #endif
                        }
                        else // game is over but it shouldnt be
                        {
                            fails++;
                            #if (NOISY_TEST == 1)
                                printf(":Failed(game over but shouldnt be)\n");
                             #endif
                        }
                        
                    }
                    else   //check on prov =8 that game is over
                    {
                        #if (NOISY_TEST == 1)
                            printf("Providens = %i  game is over: ", provs);
                         #endif
                        
                        if(check == 1)
                        {
                            #if (NOISY_TEST == 1)
                                printf("PASSED\n");
                             #endif
                            
                        }
                        else
                        {
                            #if (NOISY_TEST == 1)
                                printf("Failed (game not over but should be)\n");
                            #endif
                            
                        }
                    }
                }
            }
        
    }
    
    // 2.)or 3 supply piles are at 0 , there are 27 supply piles
    for (i =0; i< 4; i++)
    {
        //clear game
        memset(&play, 23, sizeof(struct gameState));
        //initialize new game
        initializeGame(i, k, seed, &play);
        
        
        //check 0 supply pile filled
        if ( i ==  0)
        {
            #if (NOISY_TEST == 1)
                printf("there are 0 supply piles with 0 item, game not over\n");
            #endif
            
            if (isGameOver(&play) == 1)
            {
                //game over option
                fails++;
                #if (NOISY_TEST == 1)
                    printf("Fail game not over till 3 supply piles with 0 items\n");
                #endif
            }
            else
            {
                //not game over
                passes++;
                #if (NOISY_TEST == 1)
                    printf("Pass game still playable\n");
                #endif
            }
        }
    
        // check 1 supply piles filled
        if ( i ==  1)
        {
            play.supplyCount[1] = 0;
            #if (NOISY_TEST == 1)
                printf("there is 1 supply piles with 0 items, game not over\n");
            #endif
            
            
            if (isGameOver(&play) == 1)
            {
                //game over option
                fails++;
                #if (NOISY_TEST == 1)
                    printf("Fail game not over till 3 supply piles with 0 items game not over\n");
                #endif
            }
            else
            {
                //not game over
                passes++;
                #if (NOISY_TEST == 1)
                    printf("Pass game still playable\n");
                #endif
            }
        }
        
        //check 2 supply piles filled
        if ( i  ==  2)
        {
            play.supplyCount[1] = 0;
            play.supplyCount[2] = 0;
            #if (NOISY_TEST == 1)
                printf("there are 2 supply piles with 0 items game not over\n");
            #endif
            
            
            if (isGameOver(&play) == 1)
            {
                //game over option
                fails++;
                #if (NOISY_TEST == 1)
                    printf("Fail game not over till 3 supply piles with 0 items\n");
                #endif
            }
            else
            {
                //not game over
                passes++;
                #if (NOISY_TEST == 1)
                    printf("Pass game still playable\n");
                #endif
            }
        }
        
        //check 3 supply piles filled
        if ( i ==  3)
        {
            play.supplyCount[1] = 0;
            play.supplyCount[2] = 0;
            play.supplyCount[3] = 0;
            #if (NOISY_TEST == 1)
                printf("there are 3 supply piles with 0 items game should be over\n");
            #endif
            
            if (isGameOver(&play) == 1)
            {
                //game over option
                passes++;
                #if (NOISY_TEST == 1)
                    printf("Pass game is over \n");
                #endif
            }
            else
            {
                //not game over
                fails++;
                #if (NOISY_TEST == 1)
                    printf("fail game not over \n");
                #endif
            }

        }
        
    }

    #if (NOISY_TEST == 1)
        printf(" the # of fails = %i\n", fails);
        printf(" the # of passes = %i\n", passes);
    #endif
    
    
    if (passes != 40)
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

