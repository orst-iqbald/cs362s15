/* -----------------------------------------------------------------------
 * Random testing the adventurer card
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

#define GAMES_TO_PLAY 21600000

// Counts the number of treasure cards in the player's hand
int numTreasureCards(struct gameState *state, int player);

// Checks if a player has any action cards left
int hasActionCards(struct gameState *state);

// Checks if player has an estate card in hand
int hasEstate(struct gameState *state);

// Counts the number of treasure map cards in hand
int treasureMapsInHand(struct gameState *state);

int main() {
    int i, j, n, res;
    int seed;
    int numPlayer = 2;
    int player;
    int numMapsBefore;
    int cardDrawn;
    int cardPos, supplyPos;
    int choice1, choice2, choice3;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, treasure_map};
    struct gameState state;

    printf ("RANDOM TESTING treasure map card:\n");
    printf("Playing %d games of Dominion\n\n", GAMES_TO_PLAY);


    for (i = 0; i < GAMES_TO_PLAY; i++) {
        seed = rand() % 1000 + 1;
        printf("Game %d\n", i + 1);
        initializeGame(numPlayer, k, seed, &state); // initialize a new game
        while (!isGameOver(&state)) {

            // Begin player's turn
            player = whoseTurn(&state);
            // Play action cards
            j = 0;
            while (state.numActions > 0) {
                j = j + 1;
                //printf("In action phase, round %d\n", j);
                // Choose the action card from the hand to play
                if (state.handCount[player] == 0) {
                    break;
                }
                cardPos = rand() % state.handCount[player];
                choice3 = -1;
                //printf("Playing card %d from pos %d\n", state.hand[player][cardPos], cardPos);

                if (state.hand[player][cardPos] == feast) {
                    // Find a card that costs up to 5 coins and is not ran out
                    do {
                        supplyPos = rand() % treasure_map + 1;
                    } while (getCost(supplyPos) > 5 &&
                             supplyCount(supplyPos, &state) < 1);
                    choice1 = supplyPos;
                } else if (state.hand[player][cardPos] == mine) {
                    // Check if there is a treasure card to trash
                    if (numTreasureCards(&state, player) == 0) break;
                    // Pick a treasure card to trash
                    do {
                        cardPos = rand() % state.handCount[player];
                    } while (state.hand[player][cardPos] < 4 ||
                             state.hand[player][cardPos] > 6);
                    choice1 = cardPos;
                    // Pick a treasure card to gain
                    supplyPos = rand() % 3 + 4;
                    choice2 = supplyPos;
                } else if (state.hand[player][cardPos] == baron) {
                    // Choose whether to discard estate
                    choice1 = rand() % 2;
                    if (!hasEstate(&state)) break;
                    if (supplyCount(estate, &state) == 0) break;
                } else if (state.hand[player][cardPos] == treasure_map) {
                    if (treasureMapsInHand(&state) < 2) break;
                    if (supplyCount(gold, &state) <= 4) break;
                    numMapsBefore = treasureMapsInHand(&state);
                }

                // Play the card, if the card is not an action card it will not
                // get played
                if (state.hand[player][cardPos] == feast) break;
                //if (state.hand[player][cardPos] == baron) break;
                //if (state.hand[player][cardPos] == mine) break;
                playCard(cardPos, choice1, choice2, choice3, &state);

                // Check the results of the treasure map card
                if (state.hand[player][cardPos] == treasure_map) {
                    // Make sure the two treasure maps were trashed
                    if (numMapsBefore != treasureMapsInHand(&state) + 2) {
                        printf("FAILED: treasure maps in hand is %d, should be %d\n", treasureMapsInHand(&state), numMapsBefore - 2);
                    }
                    // Make sure the next four cards drawn are gold
                    for (n = 0; n < 4; n++) {
                        drawCard(player, &state);
                        cardDrawn = state.hand[player][state.handCount[player] - 1];
                        if (cardDrawn != gold) {
                            printf("FAILED: did not draw gold card\n");
                        }
                    }
                }

                // If the player has no more action cards, go to next phase of
                // turn
                if (!hasActionCards(&state)) break;
            }

            // Buy cards phase
            j = 0;
            while (state.numBuys > 0) {
                //printf("In buy phase, round %d\n", j + 1);
                // Choose which card to buy
                supplyPos = rand() % treasure_map + 1;
                if (supplyCount(supplyPos, &state) == 0) break;
                // Buy card, if the card is not in the game or if it has ran out
                // or if the player does not have enough coins, nothing should
                // happen
                res = buyCard(supplyPos, &state);
                if (res) {
                    //printf("Bought card %d\n", supplyPos);
                }
                // Move on to next phase if the player has less than 2 coins
                if (state.coins < 2) break;
                j = j + 1;
            }
            // Everything has been done, so now it is the next player's turn
            endTurn(&state);
        }

    }
    printf("Done playing %d games\n\n", i);
    return 0;
}

int numTreasureCards(struct gameState *state, int player) {
    int i;
    int treasures = 0;
    for (i = 0; i < state->handCount[player]; i++) {
        if (state->hand[player][i] == copper) {
            treasures = treasures + 1;
        } else if (state->hand[player][i] == silver) {
            treasures = treasures + 1;
        } else if (state->hand[player][i] == gold) {
            treasures = treasures + 1;
        }
    }

    return treasures;
}

int hasActionCards(struct gameState *state) {
    int i;
    int player = whoseTurn(state);
    for (i = 0; i < state->handCount[player]; i++) {
        if (state->hand[player][i] >= adventurer &&
            state->hand[player][i] <= treasure_map &&
            state->hand[player][i] != gardens &&
            state->hand[player][i] != mine) {
                //printf("Card in hand is %d\n", state->hand[player][i]);
                return 1;
            }
    }
    return 0;
}

int hasEstate(struct gameState *state) {
    int i;
    int player = whoseTurn(state);
    for (i = 0; i < state->handCount[player]; i++) {
        if (state->hand[player][i] == estate) {
                return 1;
            }
    }
    return 0;
}

int treasureMapsInHand(struct gameState *state) {
    int i;
    int numMaps = 0;
    int player = whoseTurn(state);
    for (i = 0; i < state->handCount[player]; i++) {
        if (state->hand[player][i] == treasure_map) {
                numMaps = numMaps + 1;
            }
    }
    return numMaps;
}
