//testing buyCard
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

int main(){
    //build test objects
    int player1 = 0;

    struct gameState *state = newGame();
    int* kcards = kingdomCards(1,2,3,4,5,6,7,8,9,10);

    initializeGame(4 ,kcards , 321654, state);

    //begin tests
    state->coins = 8;
    buyCard(province, state);
    if(fullDeckCount(player1,province,state) != 1){
        printf("F| first buy fails\n");
    }
    else{
        printf("S| first buy succeeds\n");
    }

    //test numBuys
    state->coins = 8;
    if (buyCard(province, state) != -1){
        printf("F| buy check fails\n");
    }
    else{
        printf("S| buy check succeeds\n");
    }

    //test coins
    state->coins = 6;
    state->numBuys = 2;
    if (buyCard(province, state) != -1){
        printf("F| coins check fails\n");
    }
    else{
        printf("S| coins check succeeds\n");
    }

    //test supply
    state->supplyCount[province] = 0;
    state->coins = 9;
    if (buyCard(province, state) != -1){
        printf("F| supply check fails\n");
    }
    else{
        printf("S| supply check succeeds\n");
    }
    return 0;
}
