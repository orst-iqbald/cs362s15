#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "rngs.h"
#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"

//Still need to dereference variables when they're used

int adventurer(int * drawntreasure, int * currentPlayer, int * cardDrawn, int * temphand, struct gameState * state){//Used variables are: drawntreasure, state, currentPlayer, cardDrawn, temphand, z 
	int z = 0;

	while((*drawntreasure)<2){
		if (state->deckCount[(*currentPlayer)] <1){//if the deck is empty we need to shuffle discard and add to deck
	  		shuffle(*currentPlayer, state);
		}
		drawCard(*currentPlayer, state);
		*cardDrawn = state->hand[(*currentPlayer)][state->handCount[(*currentPlayer)]-1];//top card of hand is most recently drawn card.
		if (*cardDrawn == copper || *cardDrawn == silver || *cardDrawn == gold)
	  		(*drawntreasure)++;
		else{
	  		temphand[z]=(*cardDrawn);
	  		state->handCount[(*currentPlayer)]--; //this should just remove the top card (the most recently drawn one).
	  		z++;
		}
    }
    
    while(z-1>=0){
		state->discard[(*currentPlayer)][state->discardCount[(*currentPlayer)]++]=temphand[z-1]; // discard all cards in play that have been drawn
		z=z-1;
    }
    
    return 0;
}

int smithy(int * currentPlayer, int * handPos, struct gameState * state){//Used variables are: currentPlayer, state, handPos, i
	int i;
	//+3 Cards
    for (i = 0; i < 3; i++){
	  	drawCard(*currentPlayer, state);
	}
			
    //discard card from hand
    discardCard(*handPos, *currentPlayer, state, 0);
    return 0;
}

int village(int * currentPlayer, int * handPos, struct gameState * state){//Used variables are: currentPlayer, state, handPos
	//+1 Card
    drawCard(*currentPlayer, state);
			
    //+2 Actions
    state->numActions = state->numActions + 2;
			
    //discard played card from hand
    discardCard(*handPos, *currentPlayer, state, 0);
    return 0;
}

int steward(int * currentPlayer, int * handPos, int * choice1, int * choice2, int * choice3, struct gameState * state){//Used variables are: choice1, currentPlayer, state, choice2, choice3, handPos
	if (*choice1 == 1)
	{
	  	//+2 cards
	  	drawCard(*currentPlayer, state);
	  	drawCard(*currentPlayer, state);
	}
    else if (*choice1 == 2)
	{
	  	//+2 coins
	  	state->coins = state->coins + 2;
	}
    else
	{
	  	//trash 2 cards in hand
	  	discardCard(*choice2, *currentPlayer, state, 1);
	  	discardCard(*choice3, *currentPlayer, state, 1);
	}
			
    //discard card from hand
    discardCard(*handPos, *currentPlayer, state, 0);

    return 0;
}

int mine(int * currentPlayer, int * handPos, int * choice1, int * choice2, struct gameState * state){//Used variables are: j, state, currentPlayer, choice1, choice2, handPos, i
	int i, j;

	j = state->hand[(*currentPlayer)][(*choice1)];  //store card we will trash

    if (state->hand[(*currentPlayer)][(*choice1)] < copper || state->hand[(*currentPlayer)][(*choice1)] > gold){
	  	return -1;
	}
		
    if ((*choice2) > treasure_map || (*choice2) < curse){
	  	return -1;
	}

    if ( (getCost(state->hand[(*currentPlayer)][(*choice1)]) + 3) > getCost(*choice2) ){
	  	return -1;
	}

    gainCard(*choice2, state, 2, *currentPlayer);

    //discard card from hand
    discardCard(*handPos, *currentPlayer, state, 0);

    //discard trashed card
    for (i = 0; i < state->handCount[(*currentPlayer)]; i++){
	  	if (state->hand[(*currentPlayer)][i] == j){
	      	discardCard(i, *currentPlayer, state, 0);			
	      	break;
	    }
	}
			
    return 0;
}

