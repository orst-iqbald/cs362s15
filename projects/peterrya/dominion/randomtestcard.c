//testing the salvager
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include <time.h>

void addCardsToDeck(struct gameState* state, int num, int pnum){
    int x;
    int ran;
    int pushCard;
    srand(time(NULL));
    for(x = 0; x < num; x++){
        ran = (rand() % 5);
        switch(ran){
        case 0:
            pushCard = estate;
            break;
        case 1:
            pushCard = duchy;
            break;
        case 2:
            pushCard = copper;
            break;
        case 3:
            pushCard = silver;
            break;
        case 4:
            pushCard = gold;
            break;
        case 5:
            pushCard = province;
            break;
        }
        state->deck[pnum][state->deckCount[pnum]] = pushCard;
        state->deckCount[pnum]++;
    }
}

int addCardsToHand(struct gameState *state, int numcar, int pnum){
    int x;
    for(x = 0; x < numcar; x++){
        if(state->deckCount[pnum] == 0 && state->discardCount[pnum] == 0){
            return 0;
        }
        drawCard(pnum,state);
    }
    return 0;
}

int addCardsToDiscard(struct gameState *state, int numcar, int pnum){
    srand(time(NULL));
    int x;
    int ran;
    for(x = 0; x < numcar; x++){
        //printf("%d\n",x);
        ran = rand() % 2;
        if(ran == 0){
                if(state->deckCount[pnum] > 0){
                    state->discard[pnum][state->discardCount[pnum]] = state->deck[pnum][state->deckCount[pnum] - 1];
                    state->deck[pnum][state->deckCount[pnum] - 1] = 0;
                    state->deckCount[pnum]--;
                    state->discardCount[pnum]++;
                }
        }
        else{
                if(state->handCount[pnum] > 0){
                    state->discard[pnum][state->discardCount[pnum]] = state->hand[pnum][state->handCount[pnum] - 1];
                    state->hand[pnum][state->handCount[pnum] - 1] = 0;
                    state->handCount[pnum]--;
                    state->discardCount[pnum]++;
                }
        }
    }
    return 0;
}

int main(){
	//build test objects
    int x;
    int count;
    int tcard;
    int igold = 0;
    struct gameState *state = newGame();
    int* kcards = kingdomCards(1,2,3,4,5,6,7,8,9,10);

    srand(time(NULL));
    printf("test results are given in the format \"F| deck count, hand count, discard count fails to...\" where the three counts are the number of randomly generated values put in at the start\n");
    //begin tests
    for(x = 0; x < 100; x++){
    initializeGame(4 ,kcards , 321654, state);
                    //set random variables
    int player = rand() % 4;
    int numde = rand() % 500;
    addCardsToDeck(state, numde, player);
    int numha = rand() % 405 + 5;
    addCardsToHand(state, numha, player);
    int numdi = rand() % 500;
    addCardsToDiscard(state, numdi, player);

                        //run test
        count = 0;
        igold = 0;
        int buys = state->numBuys;

        tcard = state->hand[player][1];
        state->hand[player][0] = salvager;
        int ccoin = updateCoins(player,state,getCost(tcard));

        int chand = state->handCount[player] - 1;

        cardEffect(salvager,tcard,0,0,state,0,0);
        if(state->numBuys != buys + 1){
            printf("F| %d, %d, %d fails to get correct numBuys. ", numde, numha, numdi);
        }
        else{
            //printf("S| salvager succeeds getting correct numBuys. ");
        }
        if(updateCoins(player,state,0) != ccoin){
        printf("F| %d, %d, %d fails to get correct coins. ", numde, numha, numdi);
        }
        else{
            //printf("S| salvager succeeds getting correct coins. ");
        }
        if(state->handCount[player] != chand){
            printf("F| %d, %d, %d fails to get correct discard. ", numde, numha, numdi);
        }
        else{
            //printf("S| salvager succeeds getting correct discard. ");
        }
        printf("\n");
    }

    return 0;
}
