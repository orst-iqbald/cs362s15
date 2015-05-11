#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "rngs.h"

void checkAdventurer(int currentPlayer, struct gameState game)
{
    int i = 0;
    struct gameState prev;
    int treasureCount = 0;
    int tempHand[MAX_HAND];
    int bonus[2] = {0, 1};
    int preCount = game.discardCount[currentPlayer] 
                       + game.deckCount[currentPlayer] 
                       + game.handCount[currentPlayer];

    memcpy(&prev, &game, sizeof(struct gameState));

    int cardReturn = cardEffect(adventurer, 0, 0, 0, &game, 0, bonus);

    int postCount = game.discardCount[currentPlayer] 
                    + game.deckCount[currentPlayer] 
                    + game.handCount[currentPlayer];

    if (preCount != postCount) {
        printf("Incorrect card count, pre: %d - post: %d\n", preCount, postCount);
    }
    if (cardReturn != 0) {
        printf("cardEffect returned incorrect value: %d\n", cardReturn);
    }
}

int main () {

    int i, j;
    int currentPlayer;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
           remodel, smithy, village, baron, great_hall};

    struct gameState game;

    SelectStream(2);
    PutSeed(3);

    printf("Randomly testing Adventurer card\n");

    for (i = 0; i < 2000; i++) {

        for (j = 0; j < sizeof(struct gameState); j++) {
            ((char*)&game)[j] = floor(Random() * 256);
        }

        initializeGame(2, k, 1, &game);

        game.whoseTurn = floor(Random() * (MAX_PLAYERS));

        currentPlayer = game.whoseTurn;

        game.deckCount[currentPlayer] = floor(Random() * MAX_DECK);

        game.handCount[currentPlayer] = floor(Random() * MAX_HAND);

        game.discardCount[currentPlayer] = MAX_DECK - 
            (game.deckCount[currentPlayer]+game.handCount[currentPlayer]);

        game.playedCardCount = floor(Random() * MAX_DECK);


        for (j = 0; j < game.deckCount[currentPlayer]; j++) {
            game.deck[currentPlayer][j] = floor(Random() * (treasure_map + 1));
        }

        for (j = 0; j < game.discardCount[currentPlayer]; j++) {
            game.discard[currentPlayer][j] = floor(Random() * (treasure_map + 1));
        }

        for (j = 0; j <game.handCount[currentPlayer]; j++){
            game.hand[currentPlayer][j] = floor(Random() * (treasure_map + 1));
        }

        checkAdventurer(currentPlayer, game);
    }

    printf ("Tests completed\n");

    return 0;
}
