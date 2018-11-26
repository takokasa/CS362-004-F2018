/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 *  cardtest2: cardtest2.c dominion.o rngs.o
 *	gcc -o cardtest2 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 *
 * type "./cardtest2" to run
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

void testAdventurerRefactor(){
    int numPlayer = 2;
    struct gameState G;
    int player, before_hand_treasure, before_discard_treasure, before_deck_treasure, after_hand_treasure, after_discard_treasure, after_deck_treasure, before_hand, before_discard, before_deck;
    
    
    int k[12] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward};
    
    printf("+++++adventurerRefactor() tests begin+++++\n");
    
    initializeGame(numPlayer, k, 2, &G); // init a game
        // test playing adventure card for each player
    for (player = 0; player < numPlayer; player++){
        int temphand[MAX_HAND];// moved above the if statement
        int drawntreasure=0;
        //int cardDrawn;
        int z = 0, r = 0;// this is the counter for the temp hand
        G.hand[player][G.handCount[player]] = adventurer; // player gets the adventurer card
        G.handCount[player]++;
        if(countDeckTreasure(player, &G) < 2){// make sure the deck has at least two treasure cards
            G.deck[player][G.deckCount[player]] = gold;
            G.deckCount[player]++;
            G.deck[player][G.deckCount[player]] = gold;
            G.deckCount[player]++;
        }
        //printHand(player, &G);
        printf("-------------Test player %d----------------.\n", player);
        printf("Test player %d had %d treasure card(s) in deck, and total %d cards in deck before.\n", player, countDeckTreasure(player, &G), G.deckCount[player]);
        
        before_hand = G.handCount[player]; // record the total cards number in hand
        before_deck = G.deckCount[player]; // record the total cards number in deck
        before_discard = G.discardCount[player]; // record the total cards number in discard

        before_hand_treasure = countHandTreasure(player, &G); // record the treasure cards number in hand
        before_deck_treasure = countDeckTreasure(player, &G); // record the treasure cards number in deck
        before_discard_treasure = countDiscardTreasure(player, &G); // record the treasure cards number in discard
        // adventurerRefactor(&drawntreasure, &G, &player, &cardDrawn, temphand, &z);//play the adventure card
        r = cardAdventurer(player, temphand, drawntreasure, z, &G); // play the adventurer card

        after_hand_treasure = countHandTreasure(player, &G); // record the treasure cards number in hand
        after_deck_treasure = countDeckTreasure(player, &G); // record the treasure cards number in deck
        after_discard_treasure = countDiscardTreasure(player, &G); // record the treasure cards number in discard
        //printHand(player, &G);

        printf("Test player %d had %d card(s) in deck after playing adventure.\n", player, G.deckCount[player]);
        printf("Test player %d had %d treasure card(s) in hand before, but now has %d treasure cards after playing adventure.\n", player, before_hand_treasure, after_hand_treasure);
        
        assert(before_hand_treasure + 2 == after_hand_treasure); // get 2 new treasure cards in hand now.
        assert(before_deck_treasure - 2 == after_deck_treasure); // deck lost 2 treasure cards now.
        assert(before_discard_treasure == after_discard_treasure); // discard's treasure cards does not change.
        assert(before_hand + 2 == G.handCount[player]); // get 2 new cards in hand now.
        assert(before_discard + (before_deck - G.deckCount[player] - 2) == G.discardCount[player]); // the drawn non treasure cards from deck should go to discard
    }

    printf("+++++adventurerRefactor() test passed+++++\n");
    
}

int main(int argc, char *argv[]){
    testAdventurerRefactor();
    return 0;
}

