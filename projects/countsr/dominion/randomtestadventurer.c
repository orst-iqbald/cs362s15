//  Assignment 4
//  CS 362
//  Robin Counts
//  randomtestadventurer.c


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

int testRandAdventurer(int p, struct gameState *post) {
    
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    
    int r, i;
    int preCoinCount = 0;
    int postCoinCount = 0;

    for(i=0; i < pre.handCount[p]; i++) {
        if(pre.hand[p][i] == gold || pre.hand[p][i] == silver || pre.hand[p][i] == copper){
            preCoinCount++;
        }
    }
    
    r = adventurerFunc (post, p); // call function
    
    for(i=0; i < post->handCount[p]; i++) {
        if(post->hand[p][i] == gold || post->hand[p][i] == silver || post->hand[p][i] == copper){
            postCoinCount++;
        }
    }
 
    
    if (pre.deckCount[p] > 0) {
        pre.handCount[p]++;
        pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];
        pre.deckCount[p]--;
    } else if (pre.discardCount[p] > 0) {
        memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
        memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
        pre.hand[p][post->handCount[p]-1] = post->hand[p][post->handCount[p]-1];
        pre.handCount[p]++;
        pre.deckCount[p] = pre.discardCount[p]-1;
        pre.discardCount[p] = 0;
    }
    
    assert (r == 0); //function returned OK
   
    if (preCoinCount != postCoinCount - 2) {
        return -1;
        
    }
    
    return 0;
    
    
}



int setDeck (int p, struct gameState *G, int randDeckCnt) {
    int j;
    G->deckCount[p] = 0;
    
    for (j = 0; j < (randDeckCnt/2); j++){
            G->deck[p][j] = smithy;
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


int main(void)
{
    int n, p;
    int retVal;
    int failCnt = 0;
    struct gameState G;
    
    printf ("Testing Adventurer Card.\n");
    
    printf ("RANDOM TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    for (n = 0; n < 2000; n++) {

        p = floor(Random() * 2);
        G.deckCount[p] = floor((Random() * (MAX_DECK-25)+25));
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        setDeck (p, &G, G.deckCount[p]);
        retVal = testRandAdventurer(p, &G);
        if(retVal == -1)
            failCnt++;
    }
    
    
    if(failCnt > 0)
        printf("Test FAILED %d out of 2000 times\n\n", failCnt);
    else
        printf ("ALL TESTS OK\n\n");

    return 0;
}

