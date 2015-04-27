/*
    Michael Rose
    rosem2
*/
/*
    Test for Village Card effect
    Expected: Player gains 2 actions and hand size stays the same
    net 0 from +1 card and -1 from discarded Village.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main ()
{
    int seed = 1000;
    int playerCount = 2;
    int p;
    int test_success = 1;
    int num_actions;
    int startHandCount = 5;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall
                };
    struct gameState *game = malloc(sizeof(struct gameState));
    initializeGame(playerCount, k, seed, game);

    printf ("TESTING newCouncilRoom() card:\n");
    for(p = 0; p < playerCount; p++)
    {
        game->whoseTurn = p;
        game->handCount[p] = startHandCount;
        game->hand[p][startHandCount-1] = village;
        num_actions = game->numActions;
        newVillage(p,startHandCount-1,game);
        if(game->handCount[p] != startHandCount)
        {
            printf("TEST FAILED -- Hand count vs. expected = %d vs. %d\n", game->handCount[p], startHandCount);
            test_success = 0;
        }
        if(game->numActions != num_actions+2)
        {
            printf("TEST FAILED -- Number actions vs. expected = %d vs. %d\n", game->numActions, num_actions+2);
            test_success = 0;
        }
    }
    if(test_success == 1)
    {
        printf("TEST SUCCEEDED -- Village works properly.\n");
    }
printf("END TEST\n");
    return 0;
}
