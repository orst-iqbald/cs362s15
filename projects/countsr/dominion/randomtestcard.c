//  Assignment 4
//  CS 362
//  Robin Counts
//  randomtestcard.c


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int testRandRemodel(int p, struct gameState *post, int handPos, int choice1, int choice2) {
    
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    
    int r;
    
    r = remodelFunc (post, p, handPos, choice1, choice2);
    
    if (r == 0) {
        assert(memcmp(&pre, post, sizeof(struct gameState)) != 0);
        if(post->handCount[p] == pre.handCount[p] || post->discardCount[p] == pre.discardCount[p]) {
            printf("FAILED\n\n");
            exit(0);
        }

    }
    
    else if (r == -1) {
        assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
    }
    return 0;
    
}

int setHand (int p, struct gameState *G, int size) {
    int it;
    for (it = 0; it < size; it++){
        drawCard(p, G);
    }
    return 0;
}

int setDeck2 (int p, struct gameState *G, int randDeckCnt) {
    int j;
    G->deckCount[p] = 0;
    
    for (j = 0; j < (randDeckCnt/2); j++){
        G->deck[p][j] = floor(Random() * 26);
        G->deckCount[p]++;
    }
    for (j = (randDeckCnt/2); j < randDeckCnt; j++){
        G->deck[p][j] = 4;
        G->deckCount[p]++;
    }
    
    if ( shuffle(p, G) < 0 ){
        return -1;
    }
    
    return 0;
}

int setSupply(int p, struct gameState *G) {
    int i;
    for (i = 0; i < 26; i++)
        G->supplyCount[i] = floor(Random() * (MAX_DECK-1) + 1);
    return 0;
}

int main(int argc, const char * argv[]){
    
    int n, p, i;
    int choice1, choice2, handPos;
    
    struct gameState G;
    
    printf ("Testing Remodel Card.\n");
    
    printf ("RANDOM TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    for (n = 0; n < 2000; n++) {
        
        p = floor(Random() * 2);
        G.playedCardCount = 10;
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        setSupply(p, &G);
        setDeck2(p, &G, G.deckCount[p]);
        setHand(p, &G, G.deckCount[p]);
        handPos = floor(Random() * G.handCount[p]);
        choice1 = floor(Random() * 26);
        choice2 = floor(Random() * 26);
        
        testRandRemodel(p, &G, handPos, choice1, choice2);
    }
    
    printf ("ALL TESTS OK\n\n");
    
    //exit(0);
    

    
    return 0;
}
