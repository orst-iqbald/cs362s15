#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define NUM_PLAYERS 2
//#define MYDEBUG

int calculateCoins(int cardNum, int card);
int testUpdateCoins(struct gameState *state, int player, int card, int bonus);
int createCoins(struct gameState *state, int player, int card);

int calculateCoins(int cardNum, int card)
{
    switch(card)
    {
        case copper:
            return cardNum;
        case silver:
            return cardNum * 2;
        case gold:
            return cardNum * 3;
        case curse:
            return 0;
        default:
            return -1;
    }
    return -1;
}

int testUpdateCoins(struct gameState *state, int player, int card, int bonus)
{
    if(createCoins(state, player, card) != 0)
        return -1;
    
    if(updateCoins(player, state, bonus) == 0)
        return state->coins;
    else
        return -1;
}

int createCoins(struct gameState *state, int player, int card)
{
    int i;
    for(i = 0; i < state->handCount[player]; i++)
    {
        state->hand[player][i] = card;
    }
    
    for(i = 0; i < state->handCount[player]; i++)
    {
        if(state->hand[player][i] != card)
            return -1;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    int color = 0;
    if(argc == 2 && strcmp(argv[1], "-c") == 0)
        color = 1;
    int failedTests = 0;
    printf("\n\n************** BEGIN UNITTEST 1: updateCoins **************\n");
    struct gameState state;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
    int i;
    int players[NUM_PLAYERS];
    for(i=0; i < NUM_PLAYERS; i++)
    {
        players[i] = i;
    }
    
    printf ("UpdateCoins State initalization.....");
    initializeGame(NUM_PLAYERS, k, 5, &state);
    printf("PASS\n");
    
    for(i=0; i < NUM_PLAYERS; i++)
    {
        printf ("UpdateCoins Player%d hand initalization.....", i+1);
        if(createCoins(&state, players[i], curse) == 0)
            printf("PASS\n");
        else
        {
            printf("FAIL\n");
            failedTests++;
        }
    
        printf("UpdateCoins Player%d test 0.....", i+1);
        if(testUpdateCoins(&state, players[i], curse, 0) == calculateCoins(state.handCount[players[i]], curse))
            printf("PASS\n");
        else
        {
            printf("FAIL\n");
            failedTests++;
        }
#ifdef MYDEBUG
        printf("UpdateCoins Player%d: %d\t CalcCoins: %d\n", i+1, testUpdateCoins(&state, players[i], curse, 0), calculateCoins(state.handCount[players[i]], curse));
#endif
        printf("UpdateCoins Player%d copper test.....", i+1);
        if(testUpdateCoins(&state, players[i], copper, 0) == calculateCoins(state.handCount[players[i]], copper))
            printf("PASS\n");
        else
        {
            printf("FAIL\n");
            failedTests++;
        }
#ifdef MYDEBUG
        printf("UpdateCoins Player%d: %d\t CalcCoins: %d\n", i+1, testUpdateCoins(&state, players[i], copper, 0), calculateCoins(state.handCount[players[i]], copper));
#endif
        printf("UpdateCoins Player%d silver test.....", i+1);
        if(testUpdateCoins(&state, players[i], silver, 0) == calculateCoins(state.handCount[players[i]], silver))
            printf("PASS\n");
        else
        {
            printf("FAIL\n");
            failedTests++;
        }
        
        printf("UpdateCoins Player%d gold test.....", i+1);
        if(testUpdateCoins(&state, players[i], gold, 0) == calculateCoins(state.handCount[players[i]], gold))
            printf("PASS\n");
        else
        {
            printf("FAIL\n");
            failedTests++;
        }
    }
    if(failedTests > 0)
        if(color)
            printf("\033[1;31mFailed %d tests\033[0m\n", failedTests);
        else
            printf("Failed %d tests\n", failedTests);
    else
        if(color)
            printf("\033[1;32mFailed %d tests\033[0m\n", failedTests);	
        else
            printf("Failed %d tests\n", failedTests);	
    printf("************** END UNITTEST 1: updateCoins **************\n");
    return 0;
}
