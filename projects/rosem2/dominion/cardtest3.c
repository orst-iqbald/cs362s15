/*
    Michael Rose
    rosem2
*/
/*
    Test for Council Room Card effect
    Expected: All non-current players hand have net +1 cards.
            : Player has +3 net cards and +1 buy.
    +1 from +4 cards and -1 from discarded Council.
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
    int inner_p;
    int test_success = 1;
    int num_buys;
    int other_player_cards;
    int startHandCount = 5;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    struct gameState *game = malloc(sizeof(struct gameState));
    initializeGame(playerCount, k, seed, game);

    printf ("TESTING newCouncilRoom() card:\n");
    for(p = 0; p < playerCount; p++){
        game->whoseTurn = p;
        game->handCount[p] = startHandCount;
        game->hand[p][startHandCount-1] = council_room;
        num_buys = game->numBuys;
        other_player_cards = game->handCount[(p+1)%2];
        newCouncilRoom(p,startHandCount-1,game);
        for(inner_p = 0; inner_p< playerCount;inner_p++){
            if(inner_p == p){
                if(game->handCount[p] != startHandCount+3){
                    printf("TEST FAILED -- Hand count vs. expected = %d vs. %d\n", game->handCount[p], startHandCount + 3);
                    test_success = 0;
                }
                if(game->numBuys != num_buys+1){
                    printf("TEST FAILED -- Number buys vs. expected = %d vs. %d\n", game->numBuys, num_buys+1);
                    test_success = 0;
                }
            }else{
                if(game->handCount[inner_p] != other_player_cards+1){
                    printf("TEST FAILED -- Other player hand count vs. expected = %d vs. %d\n", game->handCount[inner_p], other_player_cards + 1);
                    test_success = 0;
                }
            }
        }
    }
    if(test_success == 1){
        printf("TEST SUCCEEDED -- Council Room works properly.\n");
    }
    printf("END TEST\n");
    return 0;
}
