/*
    Michael Rose
    rosem2
*/
/*
    Test for drawCard()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DRAWCOUNT 30
int main ()
{
    int i;
    int seed = 1000;
    int playerCount = 2;
    int cardsNotInHand = DRAWCOUNT;
    int cardsInHand;
    int succ = 1;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    struct gameState *game = malloc(sizeof(struct gameState));
    printf("drawCard test: \n");
    initializeGame(playerCount, k, seed, game);
    game->deckCount[0] = 5;
    game->discardCount[0] = DRAWCOUNT-5;
    for(i = 0;i<DRAWCOUNT-5;i++){
        game->discard[0][i] = copper;
    }
    cardsInHand = game->handCount[0];
    for(i = 0;i<DRAWCOUNT;i++){
        drawCard(0,game);
        if(cardsInHand == game->handCount[0]-1){
            cardsInHand++;
        }
        else{
            printf("TEST FAILED -- Hand Size Expected: %d vs. Actual: %d\n",cardsInHand+1,game->handCount[0]);
            succ = 0;
        }
    }
    drawCard(0,game);
    if(cardsInHand == game->handCount[0]){
            cardsInHand;
        }
        else{
            printf("TEST FAILED -- Empty Deck: Hand Size Expected: %d vs. Actual: %d\n",cardsInHand,game->handCount[0]);
            succ = 0;
        }
    if(succ == 1){
        printf("TEST SUCCEEDED -- All tests passed.");
    }
    printf("END TEST\n");
    return 0;
}
