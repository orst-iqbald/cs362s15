#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"

//tests updateCoins()
int main() {
    int player = 0;
    struct gameState* state = malloc(sizeof(struct gameState));
    int bonus;
    
    //no cards in hand and no bonus
    state->handCount[player] = 0;
    bonus = 0;
    updateCoins(player, state, bonus);
    assert(state->coins == 0);
    
    //no cards in hand and a bonus of 3
    state->handCount[player] = 0;
    bonus = 3;
    updateCoins(player, state, bonus);
    assert(state->coins == bonus);
    
    //1 non-treasure card in hand and no bonus
    state->handCount[player] = 1;
    state->hand[player][0] = adventurer;
    bonus = 0;
    updateCoins(player, state, bonus);
    assert(state->coins == 0);
    
    //1 treasure card in hand and no bonus
    state->handCount[player] = 1;
    state->hand[player][0] = silver;
    bonus = 0;
    updateCoins(player, state, bonus);
    assert(state->coins == 2);
    
    //1 treasure card in hand and a bonus of 1
    state->handCount[player] = 1;
    state->hand[player][0] = silver;
    bonus = 1;
    updateCoins(player, state, bonus);
    assert(state->coins == (2 + bonus));
    
    //2 non-treasure cards in hand and no bonus
    state->handCount[player] = 2;
    state->hand[player][0] = province;
    state->hand[player][1] = adventurer;
    bonus = 0;
    updateCoins(player, state, bonus);
    assert(state->coins == 0);
    
    //2 treasure cards and 1 non-treasure card in hand and no bonus
    state->handCount[player] = 3;
    state->hand[player][0] = gold;
    state->hand[player][1] = adventurer;
    state->hand[player][2] = copper;
    bonus = 0;
    updateCoins(player, state, bonus);
    assert(state->coins == 4);
    
    return 0;
}