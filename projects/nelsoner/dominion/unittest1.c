/*************************************************
* Author:						Eric Nelson
* Date Created:					4/23/15
* Last Modification Date:		4/23/15
* Filename:						unittest1.c
*
* Description: This is a unit test to test the getWinners function in dominion.c
*
*
**************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int testGetWinners(int players[MAX_PLAYERS], struct gameState *post) {
        int i;
        int j;
        int highScore;
        int currentPlayer;
        int playerNum;
        int preResult;
        int postResult;

        struct gameState pre;
        memcpy(&pre, post, sizeof(struct gameState));

        //get score for each player
        for (i = 0; i < MAX_PLAYERS; i++) {
                //set unused player scores to -9999
                if (i >= pre.numPlayers) {
                        players[i] = -9999;
                }
                else {
                        players[i] = scoreFor(i, &pre);
                }
        }

        //find highest score
        j = 0;
        for (i = 0; i < MAX_PLAYERS; i++) {
                if (players[i] > players[j]) {
                        j = i;
                }
        }
        highScore = players[j];

        //add 1 to players who had less turns
        currentPlayer = whoseTurn(&pre);
        for (i = 0; i < MAX_PLAYERS; i++) {
                if ( players[i] == highScore && i > currentPlayer ) {
                        players[i]++;
                }
        }

        //find new highest score
        j = 0;
        for (i = 0; i < MAX_PLAYERS; i++) {
                if ( players[i] > players[j] ) {
                        j = i;
                }
        }
        highScore = players[j];

        //set winners in array to 1 and rest to 0
        for (i = 0; i < MAX_PLAYERS; i++) {
                if ( players[i] == highScore ) {
                        players[i] = 1;
                }
                else {
                        players[i] = 0;
                }
        }

        for(playerNum = 0; playerNum < pre.numPlayers; playerNum++) {
                if (players[playerNum] == 1) {
                        preResult = playerNum;
                }
        }

        for(playerNum = 0; playerNum < pre.numPlayers; playerNum++) {
                players[playerNum] = 0;
        }

        getWinners(players, post);

        for(playerNum = 0; playerNum < pre.numPlayers; playerNum++) {
                if (players[playerNum] == 1) {
                        postResult = playerNum;
                }
        }

        assert(preResult == postResult);

        return 0;
}

int main() {
        int i, n, p;
        int players[MAX_PLAYERS];
        struct gameState Game;

        printf ("--------------------------------\n");
        printf ("Testing getWinners()\n");
        printf ("RANDOM TESTS\n");

        SelectStream(2);
        PutSeed(3);

        for(n = 0; n < 2000; n++) {
                for(i = 0; i < sizeof(struct gameState); i++) {
                        ((char*)&Game)[i] = floor(Random() * 256);
                }

                int numPlayers = 0;

                while (numPlayers < 2) {
                        numPlayers = floor(Random() * (MAX_PLAYERS+1));
                }

                Game.numPlayers = numPlayers;

                for (p = 0; p < numPlayers; p++) {
                        Game.deckCount[p] = floor(Random() * MAX_DECK);
                        Game.discardCount[p] = floor(Random() * MAX_DECK);
                        Game.handCount[p] = floor(Random() * MAX_HAND);

                        for (i = 0; i < Game.handCount[p]; i++) {
                                Game.hand[p][i] = floor(Random() * MAX_DECK);
                        }

                        for (i = 0; i < Game.discardCount[p]; i++) {
                                Game.discard[p][i] = floor(Random() * MAX_DECK);
                        }

                        for (i = 0; i < Game.discardCount[p]; i++) {
                                Game.deck[p][i] = floor(Random() * MAX_DECK);
                        }
                }

                testGetWinners(players, &Game);
        }

        printf ("ALL TESTS OK\n\n");

        exit(0);
}
