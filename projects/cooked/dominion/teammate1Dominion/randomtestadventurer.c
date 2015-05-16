/* ---------------------------------------------------------------------------------
 * Random test for testing the effectAdventurer() function
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *    gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 *
 * ---------------------------------------------------------------------------------
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

int main()
{
  int i;
  int cards[10] = {adventurer, council_room, feast, gardens, mine,
   remodel, smithy, village, baron, great_hall};

  int testCount = 100;
  printf("*-------\nBegin Adventurer Card Random Testing\n-------*\n");

  //Set up the random number generator
  int seed = 12125;
  SelectStream(1);
  PutSeed((long)seed);

  for(i = 0; i < testCount; ++i)
  {
    int j, pos, preTreasure = 0, postTreasure = 0, err = 0;
    //Build a gamestate to test with
    struct gameState *state = malloc(sizeof(struct gameState));
    struct gameState *prev = malloc(sizeof(struct gameState));
    seed = floor((Random() * 12125) + 1);

    int numPlayer = floor((Random() * 3) + 2);
    initializeGame(numPlayer, cards, seed, state);

    state->whoseTurn = floor(Random() * numPlayer);
    state->handCount[state->whoseTurn] = floor(Random() * (MAX_HAND / 3));
    state->deckCount[state->whoseTurn] = floor(Random() * (MAX_DECK / 3));
    state->discardCount[state->whoseTurn] = floor(Random() * (MAX_DECK / 3));
    state->playedCardCount = floor(Random() * 5);

    //Fill the hand with random cards 0 - 17
    for(j = 0; j < state->handCount[state->whoseTurn]; ++j)
    {
      state->hand[state->whoseTurn][j] = floor(Random() * 17);
    }

    //Fill the deck with random cards 0 - 17
    for(j = 0; j < state->deckCount[state->whoseTurn]; ++j)
    {
      state->deck[state->whoseTurn][j] = floor(Random() * 17);
    }

    //Fill the discard pile with random cards 0 - 17
    for(j = 0; j < state->discardCount[state->whoseTurn]; ++j)
    {
      state->discard[state->whoseTurn][j] = floor(Random() * 17);
    }

    //Randomly select a position, set that card to adventurer for our use
    pos = floor(Random() * state->handCount[state->whoseTurn]);
    state->hand[state->whoseTurn][pos] = adventurer;

    printf("\nPre-State:\nhandCount: %i\ndeckCount: %i\ndiscardCount: %i\n",
      state->handCount[state->whoseTurn],
      state->deckCount[state->whoseTurn],
      state->discardCount[state->whoseTurn]);

    printf("Cardpos: %i\nPlayer: %i\nplayedCardCount: %i\n",
      pos,
      state->whoseTurn,
      state->playedCardCount);

    //Copy the gamestate
    memcpy(prev, state, sizeof(struct gameState));

    //Call the adventurer card
    pAdventurer(state, pos);

    //Count up the treasure cards in the players hand before playing the adventurer
    for(j = 0; j < prev->handCount[prev->whoseTurn]; ++j)
    {
      if(prev->hand[prev->whoseTurn][j] == copper ||
         prev->hand[prev->whoseTurn][j] == silver ||
         prev->hand[prev->whoseTurn][j] == gold)
      {
        ++preTreasure;
      }
    }

    //Count up the treasure cards in the players hand after playing the adventurer
    for(j = 0; j < state->handCount[state->whoseTurn]; ++j)
    {
      if(state->hand[state->whoseTurn][j] == copper ||
         state->hand[state->whoseTurn][j] == silver ||
         state->hand[state->whoseTurn][j] == gold)
      {
        ++postTreasure;
      }
    }

    if((prev->deckCount[prev->whoseTurn] + prev->discardCount[prev->whoseTurn] - 2) !=
     (state->deckCount[state->whoseTurn] + state->discardCount[state->whoseTurn]))
    {
      printf("FAILURE: The total number of cards in the deck and discard are incorrect.\n");
      printf("Prev: %i, Post: %i, Seed: %i\n",
        prev->deckCount[prev->whoseTurn] + prev->discardCount[prev->whoseTurn],
        state->deckCount[state->whoseTurn] + state->discardCount[state->whoseTurn],
        seed);
      err = 1;
    }

    if((prev->playedCardCount + 1) != state->playedCardCount)
    {
      printf("FAILURE: The total number of played cards was not properly incremented.\n");
      printf("Prev: %i, Post: %i, Seed: %i\n",
        prev->playedCardCount,
        state->playedCardCount,
        seed);
      err = 2;
    }

    if((preTreasure + 2) != postTreasure)
    {
      printf("FAILURE: The number of treasure cards in the players hand is incorrect.\n");
      printf("Prev: %i, Post: %i, Seed: %i\n",
        preTreasure + 2,
        postTreasure,
        seed);
      err = 3;
    }

    if(prev->handCount[prev->whoseTurn] + 2 != state->handCount[state->whoseTurn])
    {
      printf("FAILURE: The handCount was not properly incremented.\n");
      printf("Prev: %i, Post: %i, Seed: %i\n",
        prev->handCount[prev->whoseTurn],
        state->handCount[state->whoseTurn],
        seed);
      err = 4;
    }

    if(err == 0)
    {
      printf("PASSED.\n");
    }
  }

  printf("*-------\nEnd Adventurer Card Random Testing\n-------*\n");
  return 0;
}