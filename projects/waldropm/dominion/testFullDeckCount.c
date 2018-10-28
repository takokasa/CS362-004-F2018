/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 * testFullDeckCount: testFullDeckCount.c dominion.o rngs.o
 *	gcc -o testFullDeckCount -g  testFullDeckCount.c dominion.o rngs.o $(CFLAGS)
 *
 * type "./testFullDeckCount" to run
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>

void setDeckCount(int player, int card, struct gameState *state) {
    
    int i;
    // printf("state->deckCount[player] = %d\n ", state->deckCount[player]);
    for (i = 0; i < state->deckCount[player]; i++){
        // printf("state->deck[player][i] = %d\n", state->deck[player][i]);
        state->deck[player][i] = card;
    }
    
    for (i = 0; i < state->handCount[player]; i++){
        state->hand[player][i] = card;
    }
    
    for (i = 0; i < state->discardCount[player]; i++){
        state->discard[player][i] = card;
    }
    
}

void testFullDeckCount(){

    int numPlayer = 2;
    int maxCardCount = 3;
    int p, cardCount;
    int cards[3] = {curse, estate, duchy}; // test for different cards
    struct gameState G;
    int i,j;
    for (i = 0; i < numPlayer; i++){ // initialize the cards of deck, hand, and discard
        G.deckCount[i] = 0;
        G.handCount[i] = 0;
        G.discardCount[i] = 0;
        for (j = 0; j < 3; j++){
            G.deck[i][j] = estate;
            G.deckCount[i]++;
            G.hand[i][j] = estate;
            G.handCount[i]++;
            G.discard[i][j] = estate;
            G.discardCount[i]++;
        }
        for (j = 3; j < 10; j++){
            G.deck[i][j] = copper;
            G.deckCount[i]++;
            G.hand[i][j] = copper;
            G.handCount[i]++;
            G.discard[i][j] = copper;
            G.discardCount[i]++;
        }
    }
    printf ("TESTING fullDeckCount():\n");
    assert(fullDeckCount(1, estate, &G) == 9);
    assert(fullDeckCount(0, copper, &G) == 21);
    assert(fullDeckCount(0, duchy, &G) == 0);
    
    for (p = 0; p < numPlayer; p++){// test for all players
        for (cardCount = 0; cardCount < maxCardCount; cardCount++){ // test for different cards
            setDeckCount(p, cards[cardCount], &G); // reset all the cards to the chosen card
            printf("fullDeckCount() = %d, expected = %d\n", fullDeckCount(p, cards[cardCount], &G) , 30);
            assert(fullDeckCount(p, cards[cardCount], &G) == 30);
        }
    }
    printf("All tests passed!\n");
            
}

int main(int argc, char *argv[]){
    testFullDeckCount();
    return 0;
}
