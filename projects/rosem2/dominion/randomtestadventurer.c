#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "rngs.h"

#define NUMTESTS 500

int minimum(int first, int second){
    if (first<second)
        return first;
    return second;
}

void effectIsCorrect(int currPlayer, int card, struct gameState *state){

    struct gameState original;
    int temphand[MAX_HAND];
    int bonusValues[2] = {0, 1};
    int ret, lastDrawn, originalCount, postCount,tempHandPos, treasure, bool,i,min;


    memcpy(&original, state, sizeof(struct gameState));
    //input for random numbers
    originalCount = original.discardCount[currPlayer] + original.deckCount[currPlayer] + original.handCount[currPlayer];
    postCount = state->discardCount[currPlayer] + state->deckCount[currPlayer] + state->handCount[currPlayer];
    //call card effect and make sure pre and post state are the same
    ret = cardEffect(card, 1, 1, 1, state, 1, bonusValues);
    if(ret != 0)
        printf("cardEffect returns non-zero: %d\n",ret);
    if(originalCount != postCount)
        printf("Original and post card count is not the same. Original vs post: %d vs %d\n",originalCount, postCount);
    tempHandPos = 0;
    treasure = 0;
    while(treasure<=1){
        drawCard(currPlayer, &original);
        //last drawn = top card of player hand
        lastDrawn = original.hand[currPlayer][original.handCount[currPlayer]-1];
        //check if card is a treasure card
        if (lastDrawn == gold || lastDrawn == silver || lastDrawn == copper)
            treasure++;
        else{
            //add last drawn card to temp hand if it is not treasure
            temphand[tempHandPos]=lastDrawn;
            //remove the non-treasure card
            original.handCount[currPlayer]--;
            tempHandPos++;
        }
    }
    //discard all cards in temporary hand
    while(0<tempHandPos){
        tempHandPos--;
        original.discard[currPlayer][original.discardCount[currPlayer]++]=temphand[tempHandPos]; // discard all cards in play that have been drawn
    }
    //confirm that the 2 states are still the same
    while(0<tempHandPos){
        tempHandPos--;
        original.discard[currPlayer][original.discardCount[currPlayer]++]=temphand[tempHandPos]; // discard all cards in play that have been drawn
    }
    //confirm that the 2 states are still the same
    if(!(original.discardCount[currPlayer] == state->discardCount[currPlayer]))
        printf("Discard expected vs actual: %d vs %d\n",original.discardCount[currPlayer], state->discardCount[currPlayer]);
    bool = 0;
    min = minimum(original.discardCount[currPlayer], state->discardCount[currPlayer]);
    for(i = 0;i<min;i++){
        if(original.discard[currPlayer][i] != state->discard[currPlayer][i]){
            if(bool == 0){
            printf("Discard cards at these positions are not the same:");
            bool = 1;
            }
            printf("%d,",i);
        }
    }
    if (bool == 1){
        printf("\n");
    }
    if(!(original.deckCount[currPlayer] == state->deckCount[currPlayer]))
        printf("Deck expected vs actual: %d vs %d\n",original.deckCount[currPlayer], state->deckCount[currPlayer]);
    min = minimum(original.deckCount[currPlayer], state->deckCount[currPlayer]);
    bool = 0;
    for(i = 0;i<min;i++){
        if(original.deck[currPlayer][i] != state->deck[currPlayer][i]){
            if(bool == 0){
            printf("Deck cards at these positions are not the same:");
            bool = 1;
            }
            printf("%d,",i);
        }
    }
    if (bool == 1){
        printf("\n");
    }
    if(!(original.handCount[currPlayer] == state->handCount[currPlayer]))
        printf("Hand expected vs actual: %d vs %d\n",original.handCount[currPlayer], state->handCount[currPlayer]);
    min = minimum(original.handCount[currPlayer], state->handCount[currPlayer]);
    bool = 0;
    for(i = 0;i<min;i++){
        if(original.hand[currPlayer][i] != state->hand[currPlayer][i]){
            if(bool == 0){
            printf("Hand cards at these positions are not the same:");
            bool = 1;
            }
            printf("%d,",i);
        }
    }
    if (bool == 1){
        printf("\n");
    }
}

int main () 
{
    int j, cardCounter, i, currPlayer;
    struct gameState game;
    printf ("Adventurer Card Effect Testing.\n");
    printf ("RANDOM TESTS.\n");
    SelectStream(13);
    PutSeed(711);
    for (i = 0; i < NUMTESTS; i++) {
        for (j = 0; j < sizeof(struct gameState); j++) 
        {
            ((char*)&game)[j] = floor(Random() * 256);
        }
        //set info about game state
        game.whoseTurn = (int)(Random()*MAX_PLAYERS);
        currPlayer = game.whoseTurn;
        game.deckCount[currPlayer] = (int)(Random() * MAX_DECK);
        game.handCount[currPlayer] = (int)(Random() * MAX_HAND);
        game.discardCount[currPlayer] = MAX_DECK - game.deckCount[currPlayer] - game.handCount[currPlayer];
        game.playedCardCount = (int)(Random() * MAX_DECK);
        //set random cards to the deck
        for (cardCounter=0; cardCounter<game.deckCount[currPlayer]; cardCounter++)
        {
            game.deck[currPlayer][cardCounter] =  floor(Random() *(treasure_map+1));
        }
        //set random cards to the discard
        for (cardCounter=0; cardCounter<game.discardCount[currPlayer]; cardCounter++)
        {
            game.discard[currPlayer][cardCounter] =  floor(Random() *(treasure_map+1));
        }
        //set random cards to the hand
        for (cardCounter=0; cardCounter<game.handCount[currPlayer]; cardCounter++){
            game.hand[currPlayer][cardCounter] = floor(Random() *(treasure_map+1));
        }
        //check that the effect is correct
        effectIsCorrect(currPlayer, adventurer, &game);
    }
    printf ("ALL TESTS SUCCEEDED.\n");
    return 0;
}

