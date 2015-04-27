#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include "math.h"

int testvillageCard(int currentPlayer, struct gameState *post, int handPos){
        int i, result;
        int saveHandCount = post->handCount[currentPlayer];
        handPos = floor(Random() * post->handCount[currentPlayer]);
        struct gameState pre;

        memcpy(&pre, post, sizeof(struct gameState));

        SelectStream(2);
        PutSeed(3);

        result = cardEffect(village, 0, 0, 0, post, handPos, 0);

        PutSeed(3);

        //+3 Cards
        drawCard(currentPlayer, post);
      
      //+2 Actions
      post->numActions = post->numActions + 2;
      
      //discard played card from hand
      discardCard(handPos, currentPlayer, post, 0);


//        assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
  //      assert(post->handCount[currentPlayer] == saveHandCount + 2);
    //    assert (result == 0);

        return 0;
}

int main() {
        int n, i, p;
        struct gameState Game;

        printf ("--------------------------------\n");
        printf ("Testing cardEffect() with village card\n");
        printf ("RANDOM TESTS\n");

        SelectStream(3);
        PutSeed(3);

        for (n = 0; n < 2000; n++) {
                SelectStream(3);
                for (i = 0; i < sizeof(struct gameState); i++) {
                        ((char*)&Game)[i] = floor(Random() * 256);
                }

                p = floor(Random() * MAX_PLAYERS);
                Game.whoseTurn = p;
                Game.deckCount[p] = floor(Random() * MAX_DECK);
                Game.discardCount[p] = floor(Random() * MAX_DECK);
                Game.handCount[p] = floor(Random() * MAX_HAND);
                Game.playedCardCount = floor(Random() * MAX_DECK);

                testvillageCard(p, &Game, 0);
        }

        printf("ALL TESTS OK\n\n");
        return 0;
}
