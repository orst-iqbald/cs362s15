/*************************************************
* Author:						Eric Nelson
* Date Created:					4/23/15
* Last Modification Date:		4/23/15
* Filename:						unittest3.c
*
* Description: This is a unit test to test the GainCard function in dominion.c
*
*
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int testGainCard(int supplyPos, struct gameState *post, int toFlag, int player) {
        int result;
        struct gameState pre;

        memcpy(&pre, post, sizeof(struct gameState));

        if (supplyCount(supplyPos, &pre) < 1) {
                return -1;
        }

        //added card for [whoseTurn] current player:
        // toFlag = 0 : add to discard
        // toFlag = 1 : add to deck
        // toFlag = 2 : add to hand

        if (toFlag == 1) {
                pre.deck[player][pre.deckCount[player]] = supplyPos;
                pre.deckCount[player]++;
        }
        else if (toFlag == 2) {
                pre.hand[player][pre.handCount[player]] = supplyPos;
                pre.handCount[player]++;
        }
        else {
                pre.discard[player][pre.discardCount[player]] = supplyPos;
                pre.discardCount[player]++;
        }

        //decrease number in supply pile
        pre.supplyCount[supplyPos]--;

        result = gainCard(supplyPos, post, toFlag, player);

        assert(result == 0);

        assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);

        return 0;
}

int main() {
        int i, n, p, supplyPos, toFlag;
        struct gameState Game;

        printf ("--------------------------------\n");
        printf ("Testing gainCard()\n");
        printf ("RANDOM TESTS\n");

        SelectStream(2);
        PutSeed(3);

        for (n = 0; n < 2000; n++) {
                for (i = 0; i < sizeof(struct gameState); i++) {
                        ((char*)&Game)[i] = floor(Random() * 256);
                }

                p = floor(Random() * MAX_PLAYERS);
                Game.deckCount[p] = floor(Random() * MAX_DECK);
                Game.discardCount[p] = floor(Random() * MAX_DECK);
                Game.handCount[p] = floor(Random() * MAX_HAND);
                supplyPos = floor(Random() * 25);
                toFlag = floor(Random() * 3);
                testGainCard(supplyPos, &Game, toFlag, p);
        }

        printf ("ALL TESTS OK\n\n");

        exit(0);
}
