/*
    Michael Rose
    rosem2
*/
/*
    Test for Adventurer Card effect
    Expected: Hand has net +1 cards.
            : Last 2 cards are both treasure cards.
    +1 from +2 treasure cards and -1 from discarded Adventurer.
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

    printf ("TESTING newAdventurer() card:\n");

    for(p = 0; p < playerCount; p++){
        game->whoseTurn = p;
        game->handCount[p] = startHandCount;
        game->hand[p][0] = adventurer;
        newAdventurer(p,0,game);
        if(game->handCount[p] == startHandCount +1){
                if((game->hand[p][startHandCount] == gold || game->hand[p][startHandCount] == silver || game->hand[p][startHandCount] == copper )
                   &&(game->hand[p][startHandCount-1] == gold || game->hand[p][startHandCount-1] == silver || game->hand[p][startHandCount-1] == copper )){
                    printf("TEST SUCCEEDED -- Adventurer gives the player 2 treasure cards.\n");
            }else{
                printf("TEST FAILED -- Cards added were not both treasure cards.\n");
            }
        }
        else{
            printf("TEST FAILED -- Proper amount of cards not added. Hand count vs. expected = %d vs. %d\n", game->handCount[p], startHandCount + 2);
        }
    }
    printf("END TEST\n");
    return 0;
}
