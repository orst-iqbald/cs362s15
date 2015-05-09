/*
* Random Tester for the Outpost Card
* Outpost Card: sets outpost flag and discards outpost card
*
* This test is going to cover the game state, examining it after the
* call to the outpost card to make sure it is operating correctly.
* It will do this a set number of times using randomly generated data
* each time.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"

#define EXTRA_INFO 1  //change to 0 to turn off extra print statements
#define NUMBER_OF_RANDOM_TESTS 10000

int initAndCopyGameState(struct gameState *post, struct gameState *pre);

int main(int argc, char* argv[]) {

    int fail_count = 0; //total number of failures
    int current_fail_count; //fail count for current loop

    printf("*************** RANDOM TESTER: OUTPOST CARD EFFECTS ***************");

    for (int i = 0; i < NUMBER_OF_RANDOM_TESTS; i++) {
        current_fail_count = 0;
        struct gameState *pre = malloc(sizeof(struct gameState));
        struct gameState *post = malloc(sizeof(struct gameState));
        int outpost_handpos = initAndCopyGameState(post, pre);
        //call the outpost card function
        int result = playOutpost(post, post->whoseTurn, outpost_handpos);

        printf("********* Begin Test %d **********\n\n", i+1);

        //check if function returned 0
        if (result != 0){
            current_fail_count++;
            if (EXTRA_INFO)
                printf("FAILURE - playAdventurer did NOT return 0 - Test %d\n",i+1);
        }

        //test outpost flag is set
        if (post->outpostPlayed <= pre->outpostPlayed){
            current_fail_count++;
            if (EXTRA_INFO)
                printf("FAILURE - outpostPlayed NOT incremented - Test %d\n", i+1);
        }

        //test discard
        if (post->hand[post->whoseTurn][outpost_handpos] == outpost){
            current_fail_count++;
            if (EXTRA_INFO)
                printf("FAILURE - outpost card not removed from hand - Test %d\n", i+1);
        }

        //test discardCount
        if (post->discardCount[post->whoseTurn] != pre->discardCount[post->whoseTurn]+1){
            current_fail_count++;
            if (EXTRA_INFO)
                printf("FAILURE - post discardCount not pre discardCount+1. Post: %d | Pre: %d - Test %d\n", post->discardCount[post->whoseTurn], pre->discardCount[post->whoseTurn], i+1);
        }

        //test other variables in gamestate
        //numActions in gamestate should be same, as it is decreased
        //in playCard function and not in playAdventurer
        if (post->numActions != pre->numActions){
            current_fail_count++;
            if (EXTRA_INFO)
                printf("FAILURE - numActions was changed, this should not occur in playAdventurer - Test %d\n", i+1);
        }

        if (post->whoseTurn != pre->whoseTurn){
            current_fail_count++;
            if (EXTRA_INFO)
                printf("FAILURE - turn was changed when it shouldn't be - Test %d\n", i+1);
        }

        if (post->coins != pre->coins){
            current_fail_count++;
            if(EXTRA_INFO)
                printf("FAILURE - coins changed when it shouldn't be - Test %d\n", i+1);
        }

        if (post->numBuys != pre->numBuys){
            current_fail_count++;
            if(EXTRA_INFO)
                printf("FAILURE - numBuys changed when it shouldn't be - Test %d\n", i+1);
        }

        if (post->numPlayers != pre->numPlayers){
            current_fail_count++;
            if (EXTRA_INFO)
                printf("EPIC FAILURE - numPlayers changed when it shouldn't be, what are you doing? - Test %d\n", i+1);
        }

        fail_count += current_fail_count;

        free(pre);
        free(post);
        printf("Test #%d resulted in %d failures.\n", i+1, current_fail_count);
        printf("********** End Test %d **********\n\n", i+1);
    }

    if (fail_count == 0)
        printf("All tests PASSED! Congratulations!\n");
    else
        printf("Tests reported %d FAILURES. Check the code carefully and enable EXTRA_INFO to pinpoint issues!\n", fail_count);

    printf("************* END RANDOM TESTER: OUTPOST CARD EFFECTS *************\n");
    return 0;
}

/*
* Initializes the GameState and copies it to a backup for later
* comparison.
* Returns: location of outpost card
*/
int initAndCopyGameState(struct gameState *post, struct gameState *pre){
    //set up random seed using rngs.c functions
    int init_seed = 272727;
    SelectStream(27);
    PutSeed((long)init_seed);

    const int NUMBER_PLAYABLE_CARDS = 16; //GAME_CARDS + money and property
    //just took the first 10 after money and property cards
    const int PLAYABLE_CARDS[16] = {copper, silver, gold, estate, duchy, province, adventurer, baron, council_room,gardens, great_hall, feast, mine, outpost, smithy, village};

    int GAME_CARDS[10] = {adventurer, baron, council_room, gardens, great_hall, feast, mine, outpost, smithy, village};
    int card_max = MAX_DECK / 2; //for use in random calls
    int players = 2;
    int j;
    //set up gamestate
    int seed = floor((Random() * init_seed + 1));
    initializeGame(players, GAME_CARDS, seed, post);
    //randomize some of it
    post->whoseTurn = floor(Random() * players);
    int turn = post->whoseTurn;
    //randomize deck
    post->deckCount[turn] = floor(Random() * card_max)+1;
    for (j = 0; j < post->deckCount[turn]; j++)
        post->deck[turn][j] = GAME_CARDS[(int)floor(Random()*NUMBER_PLAYABLE_CARDS)];
    //randomize discard
    post->discardCount[turn] = floor(Random() * card_max)+1;
    for (j = 0; j < post->discardCount[turn]; j++)
        post->discard[turn][j] = GAME_CARDS[(int)floor(Random()*NUMBER_PLAYABLE_CARDS)];
    //randomize hand
    post->handCount[turn] = floor(Random() * card_max)+1;
    for (j = 0; j < post->handCount[turn]; j++)
        post->hand[turn][j] = GAME_CARDS[(int)floor(Random()*NUMBER_PLAYABLE_CARDS)];
    //finally make sure outpost is in there somewhere
    int outpost_location = floor(Random()*post->handCount[turn]);
    post->hand[turn][outpost_location] = outpost;
    //copy it to another gamestate for later comparison
    memcpy(pre, post, sizeof(struct gameState));

    return outpost_location;
}
