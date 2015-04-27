/*
    Michael Rose
    rosem2
*/
/*
    Test for Smithy Card effect
    Expected: Hand has net +2 Cards.
    +2 from +3 cards and -1 from discarded Smithy
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main () {
    int seed = 1000;
    int playerCount = 2;
    int p;
    int startHandCount = 5;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    struct gameState *game = malloc(sizeof(struct gameState));
    initializeGame(playerCount, k, seed, game);

    printf ("TESTING newSmithy() card:\n");

    for(p = 0; p < playerCount; p++){
        game->whoseTurn = p;
        game->handCount[p] = startHandCount;
        game->hand[p][startHandCount-1] = smithy;
        newSmithy(p,startHandCount-1,game);
        if(game->handCount[p] == startHandCount +2){
            printf("TEST SUCCEEDED -- Smithy gives the player 3 cards.\n");
        }
        else{
            printf("TEST FAILED -- Hand count vs. expected = %d vs. %d\n", game->handCount[p], startHandCount + 2);
        }
    }
    printf("END TEST\n");
    return 0;
}



