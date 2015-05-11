#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testAdventurer(int currentPlayer, struct gameState *gs, int randomSeed) {
        int x = 0; // temphand counter
        int drawntreasure = 0;
        int cardDrawn;
        int temphand[MAX_HAND];
        struct gameState pre;
        int handPos = 0;
        int counter = 0;
        int result;
		
		SelectStream(2);
        PutSeed(randomSeed);

        memcpy(&pre, gs, sizeof(struct gameState));

        result = cardEffect(adventurer, 0, 0, 0, gs, 0, 0);
        PutSeed(randomSeed);

        while(drawntreasure < 2) {
                if (pre.deckCount[currentPlayer] < 1){//shuffle and add if empty deck
                        shuffle(currentPlayer, &pre);
                }

                if (drawCard(currentPlayer, &pre) == 0) {//nothing
                        counter++;
                }

                cardDrawn = pre.hand[currentPlayer][pre.handCount[currentPlayer] - 1];//top card of hand is most recently drawn card.

                if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
                        drawntreasure++;
                else {
                        temphand[x]=cardDrawn;
                        pre.handCount[currentPlayer]--; //remove most recently drawn card
                        counter--;
                        x++;
                }
        }

        while(x-1 >= 0) {
                pre.discard[currentPlayer][pre.discardCount[currentPlayer]++]=temphand[x-1]; // discard drawn cards
                x=x-1;
        }

        discardCard(handPos, currentPlayer, &pre, 0);

        assert(result == 0); //check base
        assert(memcmp(&pre, gs, sizeof(struct gameState)) == 0);//check new

        return 0;
}

int main() {
        int n, i, p;
		int dt = 0;
        struct gameState Game;
        srand(time(NULL));
        int randomSeed = rand();

        printf ("Adventurer random tests running....");
        
        SelectStream(2);
        PutSeed(randomSeed);

        for (n = 0; n < 1500; n++) {
                SelectStream(2);
                for (i = 0; i < sizeof(struct gameState); i++) {
                        ((char*)&Game)[i] = floor(Random() * 128);
                }

                p = floor(Random() * MAX_PLAYERS);
				Game.discardCount[p] = floor(Random() * MAX_DECK);
                Game.handCount[p] = floor(Random() * MAX_HAND);
                Game.playedCardCount = floor(Random() * MAX_DECK);
                Game.deckCount[p] = floor(Random() * MAX_DECK);
				Game.whoseTurn = p;
                
                for (i = 0; i < Game.handCount[p]; i++) {
                        Game.hand[p][i] = floor(Random() * (treasure_map + 1));
                }

                for (i = 0; i < Game.discardCount[p]; i++) {
                        Game.discard[p][i] = floor(Random() * (treasure_map + 1));
                }

                for (i = 0; i < Game.deckCount[p]; i++) {
                        Game.deck[p][i] = floor(Random() * (treasure_map + 1));
                }

                playAdventurer(dt, p, &Game, randomSeed);
        }

        printf("TESTS COMPLETE\n");
        return 0;
}