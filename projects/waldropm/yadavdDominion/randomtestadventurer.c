/* -----------------------------------------------------------------------
 *  Test adventurerRefactor() by using a random tester.
 *  Include the following lines in your makefile:
 *
 *  randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 *
 * type "./randomtestadventurer" to run
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

int countHandTreasure(int player, struct gameState *state){
    int i, card, count = 0;
    for(i = 0; i < state->handCount[player]; i++){
        card = state->hand[player][i];
        if (card == copper || card == silver || card == gold){
            count++;
        }
    }
    return count;
}

int countDeckTreasure(int player, struct gameState *state){
    int i, card, count = 0;
    for(i = 0; i < state->deckCount[player]; i++){
        card = state->deck[player][i];
        if (card == copper || card == silver || card == gold){
            count++;
        }
    }
    return count;
}

int countDiscardTreasure(int player, struct gameState *state){
    int i, card, count = 0;
    for(i = 0; i < state->discardCount[player]; i++){
        card = state->discard[player][i];
        if (card == copper || card == silver || card == gold){
            count++;
        }
    }
    return count;
}

void printHand(int player, struct gameState *state){
    int i, card;
    
    for(i = 0; i < state->handCount[player]; i++){
        card = state->hand[player][i];
        printf("++++Test player %d has %dth card(s) %d in hand.\n", player, i, card);
    }
}

int checkAdventurerRefactor(int player, struct gameState *post) {
    struct gameState pre;
    int r, handPos;

    int temphand[MAX_HAND];// moved above the if statement
    int drawntreasure = 0;
    // int cardDrawn;
    int z = 0;// this is the counter for the temp hand

    handPos = findCardInHand(player, post, adventurer);
    if(handPos < 0){ // if did not have a smithy card, then get one
        post->hand[player][post->handCount[player]] = adventurer; // player gets the adventurer card
        post->handCount[player]++;
        handPos = post->handCount[player] - 1; // record the adventurer card position
    }

    if(countDeckTreasure(player, post) < 2){// make sure the deck has at least two treasure cards
            post->deck[player][post->deckCount[player]] = gold;
            post->deckCount[player]++;
            post->deck[player][post->deckCount[player]] = gold;
            post->deckCount[player]++;
    }

    memcpy (&pre, post, sizeof(struct gameState)); // copy from post to pre

    // r = adventurerRefactor(&drawntreasure, post, &player, &cardDrawn, temphand, &z); // play the adventurer card
    r = cardAdventurer(player, temphand, drawntreasure, z, post); // play the adventurer card

    assert (r == 0);
    assert(countHandTreasure(player, &pre) + 2 == countHandTreasure(player, post)); // get 2 new treasure cards in hand now.
    assert(countDeckTreasure(player, &pre) - 2 == countDeckTreasure(player, post)); // deck lost 2 treasure cards now.
    assert(countDiscardTreasure(player, &pre) == countDiscardTreasure(player, post)); // discard's treasure cards does not change.
    assert(pre.handCount[player] + 2 == post->handCount[player]); // get 2 new cards in hand now.
    assert(pre.discardCount[player]+ (pre.deckCount[player] - post->deckCount[player] - 2) == post->discardCount[player]); // the drawn non treasure cards from deck should go to discard

    return 0;
}

int main(int argc, char *argv[]){
    int i, n, p;

    struct gameState G;

    printf ("Testing adventurerRefactor() by using a random tester.\n");

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

        checkAdventurerRefactor(p, &G);
        
        if((n + 1) % 500 == 0){
            printf ("Finished %d tests.\n", n + 1);
        }
    }

    printf ("ALL TESTS OK\n");
    return 0;
}

