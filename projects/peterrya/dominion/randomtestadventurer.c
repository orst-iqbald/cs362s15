//testing the adventurer
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

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
    int z;
    int count;
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
        int numha = rand() % 500;
        addCardsToHand(state, numha, player);
        int numdi = rand() % 500;
        addCardsToDiscard(state, numdi, player);
        int fail = 0;
                        //run test
        count = 0;
        updateCoins(player, state,0);
        igold = state->coins;
        //printf("i:%d\n",igold);
        int shuf = 0;
        int dsz = state->deckCount[player];
        for(z = state->deckCount[player] - 1; z >= 0; z--){          //calculate correct final deck size and money
            if(count >= 2){
                shuf = 0;
                break;
            }else{
                shuf = 1;
            }
            int swit = state->deck[player][z];
            //printf("swit = %d\n", swit);
            if (swit == copper){
                igold += 1;
                count += 1;
            }
            else if(swit == silver){
                igold += 2;
                count += 1;
            }
            else if(swit == gold){
                igold += 3;
                count += 1;
            }

        }
        dsz -= z;
        dsz += state->discardCount[player];
        state->hand[player][0] = adventurer;
        adventurerEffect(state,0);
        if(shuf == 1){
                if(updateCoins(player, state,0) < igold){
                    printf("F| %d, %d, %d fails to get correct gold. ", numde, numha, numdi);
                    fail = 1;
                }
                else{
                     //printf("S| adventurer succeeds getting correct gold. ");
                }
        }
        else if(updateCoins(player, state,0) != igold){
            printf("F| %d, %d, %d fails to get correct gold. ", numde, numha, numdi);
            fail = 1;
        }
        else{
            //printf("S| adventurer succeeds getting correct gold. ");
        }
        if(state->deckCount[player] != z + 1){
            printf("F| %d, %d, %d fails to get correct deck size. ", numde, numha, numdi);
            fail = 1;
        }
        else{
            //printf("S| adventurer succeeds getting correct deck size.");
        }
        if(state->discardCount[player] != dsz){
            printf("F| %d, %d, %d fails to get correct discard size. ", numde, numha, numdi);
            fail = 1;
        }
        else{
            //printf("S| adventurer succeeds getting correct discard size.");
        }
        if(fail == 1){
            printf("\n");
        }
    }

    return 0;
}
