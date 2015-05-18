/* ---------------------------------------------------------------------------------
 * Random test for testing the effectCouncilRoom() function
 * randomtestcard: randomtestcard.c dominion.o rngs.o
 *    gcc -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)
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
  printf("*-------\nBegin Council Room Card Random Testing\n-------*\n");

  //Set up the random number generator
  int seed = 12125;
  SelectStream(1);
  PutSeed((long)seed);

  for(i = 0; i < testCount; ++i)
  {
    int j, pos, err = 0;
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
    state->numBuys = floor((Random() * 4) + 1);

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

    //Randomly select a position, set that card to Council Room for our use
    pos = floor(Random() * state->handCount[state->whoseTurn]);
    state->hand[state->whoseTurn][pos] = council_room;

    printf("\nPre-State:\nhandCount: %i\ndeckCount: %i\ndiscardCount: %i\n",
      state->handCount[state->whoseTurn],
      state->deckCount[state->whoseTurn],
      state->discardCount[state->whoseTurn]);

    printf("Cardpos: %i\nPlayer: %i\nplayedCardCount: %i\nnumBuys: %i\n",
      pos,
      state->whoseTurn,
      state->playedCardCount,
      state->numBuys);

    //Copy the gamestate
    memcpy(prev, state, sizeof(struct gameState));

    //Call the adventurer card
    effectCouncilRoom(state, pos);

    //Check that each player has had their handCount incremented by 1
    for(j = 0; j < state->numPlayers; ++j)
    {
      if(j == state->whoseTurn)
      {
        if(state->handCount[j] != (prev->handCount[j] + 3))
        {
          printf("FAILURE: The current players hand was incorrectly incremented.\n");
          printf("Prev: %i, Post: %i, Seed: %i\n",
          prev->handCount[j],
          state->handCount[j],
          seed);
          err = 1;
        }
      }
      else if(state->handCount[j] != (prev->handCount[j] + 1))
      {
        printf("FAILURE: The other players hands were incorrectly incremented.\n");
        printf("Prev: %i, Post: %i, Seed: %i\n",
          prev->handCount[j],
          state->handCount[j],
          seed);
        err = 2;
      }
    }

    //Check that the player had his number of buys incremented
    if(state->numBuys != (prev->numBuys + 1))
    {
      printf("FAILURE: The number of buys was not properly incremented.\n");
      printf("Prev: %i, Post: %i, Seed: %i\n",
        prev->numBuys,
        state->numBuys,
        seed);
      err = 3;
    }

    if(err == 0)
    {
      printf("PASSED.\n");
    }
  }

  printf("*-------\nEnd Council Room Card Random Testing\n-------*\n");
  return 0;
}