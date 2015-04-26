/*
    Michael Rose
    rosem2
*/
/*
    Test for supplyCount()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define CARD_TYPES 27
int main ()
{
    int seed = 1000;
    int playerCount = 2;
    int startHandCount = 5;
    int succ = 1;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall
                };
    char* cardNames[27] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room",
                                  "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute",
                                   "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"
                                  };
    struct gameState *game = malloc(sizeof(struct gameState));

    int i;
    //Keep cost + names in order loaded in dominion.c

    printf("supplyCount Test: \n");
    for(playerCount = 2; playerCount <= 4; playerCount++)
    {
        initializeGame(playerCount, k, seed, game);
        for(i = 0; i <= CARD_TYPES; i++)
        {



            if(i == 0)
            {
                //curse
                if(game->supplyCount[i] != (10*(playerCount-1)))
                {
                    printf("TEST FAILED -- %s Value Expected: %d, Actual: %d\n", cardNames[i],(10*(playerCount-1)), game->supplyCount[i]);
                    succ = 0;
                }


            }
            else if(i<=3)
            {
                //estate, duchy and province
                if(playerCount == 2 && game->supplyCount[i] != 8)
                {
                    printf("TEST FAILED -- %s Value Expected: 8, Actual: %d\n", cardNames[i], game->supplyCount[i]);
                    succ = 0;
                }
                if(playerCount != 2 && game->supplyCount[i] != 12)
                {
                    printf("TEST FAILED -- %s Value Expected: 12, Actual: %d\n", cardNames[i], game->supplyCount[i]);
                    succ = 0;
                }
            }

            else if(i == 4)
            {
                //copper
                if(game->supplyCount[i] != (60-(7*playerCount)))
                {
                    printf("TEST FAILED -- Copper value Expected: %d, Actual: %d\n",(60-(7*playerCount)), game->supplyCount[i]);
                    succ = 0;
                }
            }
            else if(i == 5)
            {
                //silver
                if(game->supplyCount[i] != 40)
                {
                    printf("TEST FAILED -- Silver value Expected: 40, Actual: %d\n", game->supplyCount[i]);
                    succ = 0;
                }
            }
            else if(i == 6)
            {
                //gold
                if(game->supplyCount[i] != 30)
                {
                    printf("TEST FAILED -- Gold value Expected: 30, Actual: %d\n", game->supplyCount[i]);
                    succ = 0;
                }
            }
            else if(i<=16)
            {
                if(i == 10 || i == 16)
                {
                    if(playerCount == 2 && game->supplyCount[i] != 8)
                    {
                        printf("TEST FAILED -- %s Value Expected: 8, Actual: %d\n", cardNames[i], game->supplyCount[i]);
                        succ = 0;
                    }
                    if(playerCount != 2 && game->supplyCount[i] != 12)
                    {
                        printf("TEST FAILED -- %s Value Expected: 12, Actual: %d\n", cardNames[i], game->supplyCount[i]);
                        succ = 0;
                    }
                }
                else{
                    if(game->supplyCount[i] != 10){
                        printf("TEST FAILED -- %s Value Expected: 10, Actual: %d\n", cardNames[i], game->supplyCount[i]);
                        succ = 0;
                    }
                }
            }
            else if(i<=26)
            {
                if(game->supplyCount[i] != -1)
                {
                    printf("TEST FAILED -- %s Value Expected: -1, Actual: %d\n", cardNames[i], game->supplyCount[i]);
                        succ = 0;
                }
            }
            else
            {
                if(game->supplyCount[i] != 0)
                {
                    printf("TEST FAILED -- %s Value Expected: 0, Actual: %d\n", cardNames[i], game->supplyCount[i]);
                        succ = 0;
                }
            }
        }
    }
    if(succ == 1){
        printf("TEST SUCCEEDED -- All tests passed.\n");
    }
    printf("END TEST\n");
    return 0;
}
