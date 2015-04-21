/*----------------------------------------------
* testing initializeGame
*
* testInit: unittest3.c dominion.o rngs.o
*      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
*
*-----------------------------------------------
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main () {
    struct gameState *G = malloc(sizeof(struct gameState));
    int i, r, j;
    int numTests = 10;
    int numPlayer = 2;

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    

    for(i = 0; i < numTests; i++){
            for(j = 0; j < MAX_PLAYERS; j++){
            int seed = 1000+i;
            // initialize a new game
            r = initializeGame(numPlayer, k, seed, G);
            assert(r == 0);

            assert(G->numPlayers == numPlayer);

            // set some default number of cards
            int curse_num = 30;
            int estate_num = 12;
            int duchy_num = 12;
            int province_num = 12;  

            // change defaults based on number of players
            if(numPlayer == 2){
                curse_num = 10;
                estate_num = 8;
                duchy_num = 8;
                province_num = 8;
            } else if (numPlayer == 3){
                curse_num = 20;
            }  

            // check game state
            assert(G->supplyCount[curse] == curse_num);
            assert(G->supplyCount[estate] == estate_num);
            assert(G->supplyCount[duchy] == duchy_num);
            assert(G->supplyCount[province] == province_num);
            assert(G->supplyCount[copper] == 60 - (7 * numPlayer));
            assert(G->supplyCount[silver] == 40);
            assert(G->supplyCount[gold] == 30);
            assert(G->outpostPlayed == 0);
            assert(G->phase == 0);
            assert(G->numActions == 1);
            assert(G->numBuys = 1);
            assert(G->playedCardCount == 0);
            assert(G->whoseTurn == 0);
            // player should have 5 cards drawn
            assert(G->handCount[G->whoseTurn] == 5);

        }
    }

    printf("All tests passed!\n");

  return 0;
}