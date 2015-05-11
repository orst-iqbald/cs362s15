#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

#include <limits.h>

/*
 struct gameState {
 int numPlayers; //number of players
 int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
 int embargoTokens[treasure_map+1];
 int outpostPlayed;
 int outpostTurn;
 int whoseTurn;
 int phase;
 int numActions; // Starts at 1 each turn
 int coins; // Use as you see fit!
 int numBuys; // Starts at 1 each turn
 int hand[MAX_PLAYERS][MAX_HAND];
 int handCount[MAX_PLAYERS];
 int deck[MAX_PLAYERS][MAX_DECK];
 int deckCount[MAX_PLAYERS];
 int discard[MAX_PLAYERS][MAX_DECK];
 int discardCount[MAX_PLAYERS];
 int playedCards[MAX_DECK];
 int playedCardCount;
};
*/

int getRandomDeck(int *deck, struct gameState *state)
{
    for(int i = 0; i < 10; ++i)
    {
        deck[i] = rand() % 26;
    }
    
    /* Randommize handcount  -- below 10 */
    //state->handCount = rand(time(NULL)) % 10;
    
    /* randomize deckcount -- below 10 */
    state->deckCount[whoseTurn(state)] = rand() % 10;
    return 0;
}

int main(){
    /* 
        1) To hit all the branches we need to have an empty deck
        2) Draw treasure
        3)
     */
    
    /*
        We can accomplish this by
     
     */
    int deck[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int seed = 500;
    int player = 2;
    int deckCount = 0;
    int prevhand = 0;
    int curhand = 0;

    
    //int handPos;
    int trashFlag = 0;
    
    struct gameState state;
    /*
     
     */
    //int deck[10] = {adventurer, council_room, feast, gardens, mine,
    //    remodel, smithy, village, baron, great_hall};
    
    /* lots of loops here */
    for( int i = 0; i < INT_MAX ;++i)
    {
        getRandomDeck(deck, &state);
        initializeGame(player, deck, seed, &state);
        do {
            gameState.whoseTurn = 0; // Always set to player 1
            prevhand = state.deckCount[0]; //Get deck count
            prevhand += state.discardCount[0];  // get discard count
            cardEffect(adventurer, 0, 0, 0, &state, 1, 0);
            curhand = state.deckCount[0]; //Get deck count
            curhand += state.discardCount[0];  // get discard count
            if (prevhand == curhand)
                printf("All cards were successfully transferred from hand to discard deck.\n");
            else
                printf("Mismatch between discard and hand. Somecards went missing when discarding!\n");
            
        } while (state.deckCount);
        printf("Deck is empty!\n Let's start again with a random deck! . . .");
    }
    
    return 0;
    
    
}