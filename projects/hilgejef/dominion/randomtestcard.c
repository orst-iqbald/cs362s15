#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

void checkGreatHall(int handPos, int currentPlayer, struct gameState game) 
{
    struct gameState prev;
    memcpy(&prev, &game, sizeof(struct gameState));
    int cardReturn = cardEffect(great_hall, 0, 0, 0, &prev, handPos, 0);
  
    drawCard(currentPlayer, &game);

    game.numActions++;

    discardCard(handPos, currentPlayer, &game, 0);
  
    if (cardReturn != 0) {
        printf("Incorrect cardReturn value: %d\n", cardReturn);
    }

    if (prev.numBuys != game.numBuys) {
       printf("Incorrect numBuys value, prev: %d - post: %d\n", prev.numBuys, 
                                                           game.numBuys);
    }

    if (prev.discardCount[prev.whoseTurn] != game.discardCount[prev.whoseTurn]) {
        printf("Incorrect discard count, prev: %d - post: %d\n",
               prev.discardCount[prev.whoseTurn], 
               game.discardCount[prev.whoseTurn]);
    }

    if (prev.handCount[prev.whoseTurn] + 1 != game.handCount[prev.whoseTurn]) {
        printf("Incorrect hand count, prev: %d - post: %d\n", 
               prev.handCount[prev.whoseTurn],
               game.handCount[prev.whoseTurn]);
    }

    if (prev.deckCount[currentPlayer] + 1 != game.deckCount[currentPlayer]) {
        printf("Incorrect deck count, prev: %d - post: %d\n",
               prev.handCount[prev.whoseTurn],
               game.handCount[prev.whoseTurn]);
    }

}

int main() {
    int i, j;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
         remodel, smithy, village, baron, great_hall};

    struct gameState game;
  
    printf("Randomly testing Great Hall card\n");
  
    SelectStream(2);
    PutSeed(3);
  
    for (i = 0; i < 2000; i++) {
       for (j = 0; j < sizeof(struct gameState); j++) {
           ((char*)&game)[i] = floor(Random() * 255);
       }
    }

    game.numPlayers = 2 + floor(Random() * (MAX_PLAYERS - 1));
    int player = floor(Random() * game.numPlayers);
    game.whoseTurn = player;
    initializeGame(2, k, 1, &game);

    for (i = 0; i < game.numPlayers; i++) {
      game.deckCount[i] = floor(Random() * (MAX_DECK));
      game.handCount[i] = floor(Random() * (MAX_DECK - 4));
      game.discardCount[i] = floor(Random() * (MAX_DECK));
    }

    game.playedCardCount = floor(Random() * MAX_DECK);
    game.numBuys = 1;
    
    int handPos = floor(Random() * (game.handCount[player]));
 
    checkGreatHall(handPos, player, game);

    printf("Test cases completed\n");
  
    return 0;
}
