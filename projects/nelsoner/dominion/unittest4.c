/*************************************************
* Author:						Eric Nelson
* Date Created:					4/23/15
* Last Modification Date:		4/23/15
* Filename:						unittest4.c
*
* Description: This is a unit test to test the scoreFor function in dominion.c
*
*
**************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int testScoreFor(int player, struct gameState *post) {
        int i;
        int result = 0;
        int score = 0;
        struct gameState pre;
        memcpy(&pre, post, sizeof(struct gameState));

        //score from hand
        for (i = 0; i < pre.handCount[player]; i++) {
                if (pre.hand[player][i] == curse) { score = score - 1; };
                if (pre.hand[player][i] == estate) { score = score + 1; };
                if (pre.hand[player][i] == duchy) { score = score + 3; };
                if (pre.hand[player][i] == province) { score = score + 6; };
                if (pre.hand[player][i] == great_hall) { score = score + 1; };
                if (pre.hand[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, &pre) / 10 ); };
        }

        //score from discard
        for (i = 0; i < pre.discardCount[player]; i++) {
                if (pre.discard[player][i] == curse) { score = score - 1; };
                if (pre.discard[player][i] == estate) { score = score + 1; };
                if (pre.discard[player][i] == duchy) { score = score + 3; };
                if (pre.discard[player][i] == province) { score = score + 6; };
                if (pre.discard[player][i] == great_hall) { score = score + 1; };
                if (pre.discard[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, &pre) / 10 ); };
        }

        //score from deck
        for (i = 0; i < pre.discardCount[player]; i++) {
                if (pre.deck[player][i] == curse) { score = score - 1; };
                if (pre.deck[player][i] == estate) { score = score + 1; };
                if (pre.deck[player][i] == duchy) { score = score + 3; };
                if (pre.deck[player][i] == province) { score = score + 6; };
                if (pre.deck[player][i] == great_hall) { score = score + 1; };
                if (pre.deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, &pre) / 10 ); };
        }

        result = scoreFor(player, post);

        assert(result == score);

        assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);

        return result;
}

int main() {
        int i, n, p;
        struct gameState Game;

        printf ("--------------------------------\n");
        printf ("Testing scoreFor()\n");
        printf ("RANDOM TESTS\n");

        SelectStream(2);
        PutSeed(3);

        for(n = 0; n < 2000; n++) {
                for(i = 0; i < sizeof(struct gameState); i++) {
                        ((char*)&Game)[i] = floor(Random() * 256);
                }

                p = floor(Random() * MAX_PLAYERS);
                Game.deckCount[p] = floor(Random() * MAX_DECK);
                Game.discardCount[p] = floor(Random() * MAX_DECK);
                Game.handCount[p] = floor(Random() * MAX_HAND);

                for (i = 0; i < Game.handCount[p]; i++) {
                        Game.hand[p][i] = floor(Random() * MAX_DECK);
                }

                for (i = 0; i < Game.discardCount[p]; i++) {
                        Game.discard[p][i] = floor(Random() * MAX_DECK);
                }

                for (i = 0; i < Game.discardCount[p]; i++) {
                        Game.deck[p][i] = floor(Random() * MAX_DECK);
                }

                testScoreFor(p, &Game);
        }

        printf ("ALL TESTS OK\n\n");

        exit(0);
}
