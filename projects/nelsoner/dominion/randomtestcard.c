/*************************************************
* Author:						Eric Nelson
* Date Created:					5/6/15
* Last Modification Date:		5/6/15
* Filename:						randomtestcard.c
*
* Description: This is a unit test to test the Smithy card in dominion.c
*
*
**************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include "math.h"

int testSmithy(int currentPlayer, struct gameState *post) {
        int i, result;
        int saveHandCount = post->handCount[currentPlayer];
        int handPos = floor(Random() * post->handCount[currentPlayer]);
        struct gameState pre;

        memcpy(&pre, post, sizeof(struct gameState));

        SelectStream(2);
        PutSeed(3);

        result = cardEffect(smithy, 0, 0, 0, post, handPos, 0);

        PutSeed(3);

        //+3 Cards
        for (i = 0; i < 4; i++) {
                drawCard(currentPlayer, &pre);
        }
        //discard card from hand
        discardCard(handPos, currentPlayer, &pre, 0);


        assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
        assert(post->handCount[currentPlayer] == saveHandCount + 3);
        assert (result == 0);

        return 0;
}

int main() {
        int n, i, p;
        struct gameState Game;

        printf ("--------------------------------\n");
        printf ("Testing cardEffect() with Smithy card\n");
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

                testSmithy(p, &Game);
        }

        printf("ALL TESTS OK\n\n");
        return 0;
}
