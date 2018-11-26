/* -----------------------------------------------------------------------
 *  Test simthyRefactor() by using a random tester.
 *  Include the following lines in your makefile:
 *
 *  randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 *
 * type "./randomtestcard1" to run
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
int checkSmithyRefactor(int player, struct gameState *post) {
    struct gameState pre;
    int r, handPos;
    handPos = findCardInHand(player, post, smithy);
    if(handPos < 0){ // if did not have a smithy card, then get one
        post->hand[player][post->handCount[player]] = smithy; // player gets the smithy card
        post->handCount[player]++;
        handPos = post->handCount[player] - 1; // record the smithy card position
    }
    memcpy (&pre, post, sizeof(struct gameState)); // copy from post to pre
    //r = smithyRefactor (&player, post, &handPos); // play the smithy card
    r = cardSmithy (player, post, handPos); // play the smithy card
    
    pre.handCount[player] += 2; // get 3 new cards and played smithy card, so user has 3 - 1 = 2 more cards in hand now.
    if(pre.deckCount[player] <= 2){ // if there are not enough cards in deck, pull all the cards to discard pile. 
        pre.deckCount[player] = pre.discardCount[player] + pre.deckCount[player] - 3;
        pre.discardCount[player] = 0;
    }else{
        pre.deckCount[player] -= 3; // deck lost 3 card now.
    }
    pre.playedCardCount++; // smithy card goes to playcards.
    assert (r == 0);
    assert(pre.handCount[player] == post->handCount[player]);
    assert(pre.deckCount[player] == post->deckCount[player]);
    assert(pre.discardCount[player] == post->discardCount[player]);
    assert(pre.playedCardCount == post->playedCardCount);
    return 0;
}
int main(int argc, char *argv[]){
    int i, n, p;
    int player_num = 10;
    struct gameState G;
    printf ("Testing cardSmithy() with a random tester.\n");
    printf ("RANDOM TESTS.\n");
    SelectStream(2);
    PutSeed(3);
    for (n = 0; n < 2000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        p = floor(Random() * 4);
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = 3 + floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * MAX_HAND);

        checkSmithyRefactor(p, &G);

        if((n + 1) % 500 == 0){
            printf ("Finished %d tests.\n", n + 1);
        }
    }
    printf ("ALL TESTS OK\n");
    return 0;
}
