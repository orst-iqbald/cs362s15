/*************************************************
* Author:						Eric Nelson
* Date Created:					4/23/15
* Last Modification Date:		4/23/15
* Filename:						unittest2.c
*
* Description: This is a unit test to test the isGameOver function in dominion.c
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

int testIsGameOver(struct gameState *Game) {
        int i;
        int j = 0;
        int result = isGameOver(Game);

        if (Game->supplyCount[province] == 0) {
                assert (result == 1);
                return result;
        }

        for (i = 0; i < 25; i++) {
                if (Game->supplyCount[i] == 0) {
                        j++;
                }
                if (j >= 3) {
                        assert(result == 1);
                        return result;
                }
        }

        assert(result == 0);
        return result;
}

int main() {
        int n, i, j;
        struct gameState Game;

        SelectStream(2);
        PutSeed(3);

        printf ("--------------------------------\n");
        printf ("Testing isGameOver()\n");
        printf ("RANDOM TESTS\n");

        for (n = 0; n < 2000; n++) {
                for (i = 0; i < sizeof(struct gameState); i++) {
                        ((char*)&Game)[i] = floor(Random() * 256);
                }
                for (j = 0; j < 25; j++) {
                        Game.supplyCount[j] = floor(Random() * (25 + 1));
                }

                testIsGameOver(&Game);
        }

        printf ("ALL TESTS OK\n\n");
        return 0;
}
