/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 * testCompare: testCompare.c dominion.o rngs.o
 *	gcc -o testCompare -g  testCompare.c dominion.o rngs.o $(CFLAGS)
 *  
 * type "./testCompare" to run
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

int compare(const void* a, const void* b);

char compareArray(int a[],int b[],int size)	{
    int i;
    for(i = 0; i < size; i++){
        if(a[i] != b[i]){
            return 1;
        }
    }
    return 0;
}

void testCompare() {
    int a = 1, b = 2, c = 1;
    assert(compare(&a, &b) == -1);
    assert(compare(&b, &a) == 1);
    assert(compare(&a, &c) == 0);

    int values[6] = { 40, 10, 100, 90, 20, 25 };
    int desired_values[6] = { 10, 20, 25, 40, 90, 100 };
    qsort (values, 6, sizeof(int), compare);
    assert(compareArray(values, desired_values, 6) == 0);
    printf("testCompare(): PASS when test sorting an array\n");
}

int main(int argc, char *argv[]){
    testCompare();
    return 0;
}
