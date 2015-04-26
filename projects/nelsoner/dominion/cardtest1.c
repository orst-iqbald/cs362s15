/*************************************************
* Author:						Eric Nelson
* Date Created:					4/23/15
* Last Modification Date:		4/23/15
* Filename:						cardtest1.c
*
* Description: This is a unit test to test the Adventurer card in dominion.c
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

int testAdventurer(int currentPlayer, struct gameState *post) {
    int cardDrawn, i;
    int result;
    int temphand[MAX_HAND];
    int z = 0; //temp hand counter
    int drawntreasure = 0;
    int saveHandCount = post->handCount[currentPlayer];
    int handPos = floor(Random() * post->handCount[currentPlayer]);
    for (i = 0; i < post->handCount[currentPlayer]; i++)
    {
        post->hand[currentPlayer][i] = floor(Random() * (treasure_map+1));
    }
    post->hand[currentPlayer][0] = adventurer;
    struct gameState pre;

    memcpy(&pre, post, sizeof(struct gameState));

    result = cardEffect(adventurer, 0, 0, 0, post, handPos, 0);

    while(drawntreasure<2){
        if (pre.deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
            shuffle(currentPlayer, &pre);
        }
        drawCard(currentPlayer, &pre);
        cardDrawn = pre.hand[currentPlayer][pre.handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
        //printf("cardDrawn:%d\n", cardDrawn);
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            drawntreasure++;
        else{
            temphand[z]=cardDrawn;
            pre.handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
            z++;
        }
    }
    while(z-1>=0){
        pre.discard[currentPlayer][pre.discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
        z=z-1;
    }

    assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
    assert(post->handCount[currentPlayer] == saveHandCount + 2);
    assert(result == 0);

    return 0;
}

int main() {

        printf ("--------------------------------\n");
        printf ("Testing cardEffect() with Adventurer card\n");
        printf ("RANDOM TESTS\n");

	//Initialize game variables
	int numPlayer = 2;
	int seed = 100;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
	 remodel, smithy, village, baron, great_hall};
	int treasureCount = 0, i, card;
    struct gameState *Game = malloc(sizeof(struct gameState));

    initializeGame(numPlayer, k, seed, Game);

	Game->hand[whoseTurn(Game)][0] = adventurer;

	//Track the number of treasures in hand and number of adventurer cards
	for(i = 0; i < Game->handCount[whoseTurn(Game)]; ++i)
	{
		card = Game->hand[whoseTurn(Game)][i];
		if(card == copper ||
			card == silver ||
			card == gold)
		{
			++treasureCount;
		}
	}

	testAdventurer(0, Game);

        printf("ALL TESTS OK\n\n");
        return 0;
}
