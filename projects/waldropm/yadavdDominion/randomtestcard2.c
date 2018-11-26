/* -----------------------------------------------------------------------
 *  Test villageRefactor() by using a random tester.
 *  Include the following lines in your makefile:
 *
 *  randomtestcard2: randomtestcard2.c dominion.o rngs.o
 *	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
 *
 * type "./randomtestcard2" to run
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

// find a target card in the hand
int findCardInHand(int player, struct gameState *state, int card) {
    int i;
    for (i = 0; i < state->deckCount[player]; i++){
        if(card == state->deck[player][i]){
            return i;
        }
    }
    return -1;
}

int checkVillageRefactor(int player, struct gameState *post) {
    struct gameState pre;
    int r, handPos;

    handPos = findCardInHand(player, post, village);
    
    if(handPos < 0){ // if did not have a village card, then get one
        post->hand[player][post->handCount[player]] = village; // player gets the village card
        post->handCount[player]++;
        handPos = post->handCount[player] - 1; // record the village card position
    }
    memcpy (&pre, post, sizeof(struct gameState)); // copy from post to pre

    // r = villageRefactor(&player, post, &handPos);//play the village card
    r = cardVillage(player, post, handPos);
    if(pre.deckCount[player] <= 0){ // if there are not enough cards in deck, pull all the cards to discard pile. 
        pre.deckCount[player] = pre.discardCount[player];
        pre.discardCount[player] = 0;
    }
    
    assert (r == 0);
    assert(pre.handCount[player] == post->handCount[player]);// get 1 new card in hand now but used village.
    assert(pre.deckCount[player] - 1 == post->deckCount[player]); // deck lost 1 card now.
    assert(pre.discardCount[player] == post->discardCount[player]);
    assert(pre.numActions + 2 == post->numActions); // gets 2 more actions
    assert(pre.playedCardCount + 1 == post->playedCardCount); // village card goes to playcards.
    return 0;
}


int main(int argc, char *argv[]){
    int i, n, p;

    struct gameState G;

    printf ("Testing villageRefactor() by using a random tester.\n");

    printf ("RANDOM TESTS.\n");

    SelectStream(2);
    PutSeed(3);

    for (n = 0; n < 2000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        p = floor(Random() * 2);
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = 3 + floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * MAX_HAND);

        checkVillageRefactor(p, &G);
        
        if((n + 1) % 500 == 0){
            printf ("Finished %d tests.\n", n + 1);
        }
    }

    printf ("ALL TESTS OK\n");
    return 0;
}

