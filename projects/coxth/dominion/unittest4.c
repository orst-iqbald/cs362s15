/******************************
* unittest3.c 
* Thomas Cox
* discardCard - This program test the discardCard() function.
* 4/23/2015
******************************/

#include "dominion.h"
#include "interface.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

//tests discardCard()
int main() {
    struct gameState g;
    srand(time(NULL));
	int randomPlayer;
    int handPosition;
    int returnValue;    
    
	randomPlayer = (rand() % 4);
    g.handCount[randomPlayer] = (rand() % 5) + 3;  
    g.playedCardCount = 0;
   
    g.hand[randomPlayer][0] = copper;
    g.hand[randomPlayer][1] = silver;
	g.hand[randomPlayer][2] = gold;
    g.handCount[randomPlayer] = (rand() % 4) + 3;
    handPosition = 0;
    returnValue = discardCard(handPosition, randomPlayer, &g, 0);
    assert(returnValue == 0);
	handPosition = 1;
	returnValue = discardCard(handPosition, randomPlayer, &g, 0);
    assert(returnValue == 0);
	
    if(g.playedCardCount != 2){
	  printf("error played count does not = 2");
	}
    if(g.playedCards[0] != copper){
	   printf("error player card should be copper!\n");
	}
    if(g.playedCards[1] != silver){
	   printf("error player card should be silver!\n");
	}
    
    return 0;
}