/* -----------------------------------------------------------------------
 *  Test villageRefactor() by using a random tester.
 *  Include the following lines in your makefile:
 *
 *  randomtestcard3: randomtestcard3.c dominion.o rngs.o
 *	gcc -o randomtestcard3 -g  randomtestcard3.c dominion.o rngs.o $(CFLAGS)
 *
 * type "./randomtestcard3" to run
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

int checkCouncilRefactor(int player, struct gameState *post) {
    struct gameState pre;
    int r, handPos;
    int other_player = (player == 0 ? 1 : 0);  // check the other player
    // post->handCount[other_player] = 0;
    // post->deckCount[other_player] = 1;
    // printf("Other_player %d had %d card(s) in hand, and %d card(s) in deck.\n", player, post->handCount[other_player] , post->deckCount[other_player]);
    handPos = findCardInHand(player, post, council_room);
    
    if(handPos < 0){ // if did not have a council_room card, then get one
        post->hand[player][post->handCount[player]] = council_room; // player gets the council_room card
        post->handCount[player]++;
        handPos = post->handCount[player] - 1; // record the council_room card position
    }
    post->numBuys = 0;
    memcpy (&pre, post, sizeof(struct gameState)); // copy from post to pre

    
    r = cardCouncil(player, post, handPos); // play the council_room card
    
    assert (r == 0);
    printf("player %d had %d card(s) in hand before, and %d card(s) in hand after playing council_room.\n", player, pre.handCount[player] , post->handCount[player]);
    assert(pre.handCount[player] + 3 == post->handCount[player]);// get 4 new cards in hand now but used council.
    assert(pre.playedCardCount + 1 == post->playedCardCount); // council_room card goes to playcards.
    
    // printf("Test player %d had %d card(s) in hand before, and %d card(s) after playing council_room.\n", player, pre.handCount[other_player], post->handCount[other_player]);
    assert(pre.handCount[other_player] + 1 == post->handCount[other_player]);// get 1 new card in hand for other player.
    return 0;
}


int main(int argc, char *argv[]){
    int i, n, p;
    int numPlayers = 2;

    struct gameState G;

    printf ("Testing cardCouncil() by using a random tester.\n");

    printf ("RANDOM TESTS.\n");

    SelectStream(2);
    PutSeed(3);

    for (n = 0; n < 2000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        G.numPlayers = numPlayers;
        p = floor(Random() * numPlayers);
        for( int j = 0; j < 2; j++){
            G.deckCount[j] = floor(Random() * MAX_DECK);
            G.discardCount[j] = 3 + floor(Random() * MAX_DECK);
            G.handCount[j] = floor(Random() * MAX_HAND);
        }
        
        // G.deckCount[p] = floor(Random() * MAX_DECK);
        // G.discardCount[p] = 3 + floor(Random() * MAX_DECK);
        // G.handCount[p] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * MAX_HAND);

        checkCouncilRefactor(p, &G);
        
        if((n + 1) % 500 == 0){
            printf ("Finished %d tests.\n", n + 1);
        }
    }

    printf ("ALL TESTS OK\n");
    return 0;
}

