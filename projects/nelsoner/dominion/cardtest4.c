/*************************************************
* Author:						Eric Nelson
* Date Created:					4/23/15
* Last Modification Date:		4/23/15
* Filename:						cardtest4.c
*
* Description: This is a unit test to test the Great Hall card in dominion.c
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

int testGreatHall(int currentPlayer, struct gameState *post) {
        int result;
        int saveHandCount = post->handCount[currentPlayer];
        int saveActionCount = post->numActions;
        int handPos = floor(Random() * post->handCount[currentPlayer]);
        struct gameState pre;

        memcpy(&pre, post, sizeof(struct gameState));

        SelectStream(2);
        PutSeed(3);

        result = cardEffect(great_hall, 0, 0, 0, post, handPos, 0);

        PutSeed(3);

        //+1 Card
        drawCard(currentPlayer, &pre);
        //+1 Actions
        pre.numActions++;
        //discard card from hand
        discardCard(handPos, currentPlayer, &pre, 0);


        assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
        assert(post->handCount[currentPlayer] == saveHandCount);
        assert(post->numActions == saveActionCount + 1);
        assert (result == 0);

        return 0;
}

int main() {
        int n, i, p;
        struct gameState Game;

        printf ("--------------------------------\n");
        printf ("Testing cardEffect() with Great Hall card\n");
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

                testGreatHall(p, &Game);
        }

        printf("ALL TESTS OK\n\n");
        return 0;
}
