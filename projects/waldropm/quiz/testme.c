#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


//random character generation
char inputChar(){
    // generate an ascii char from 32 to 126
    int min = 32;
    int max = 126;
    int r = (rand()%(max - min + 1)) + min;
    char c = (char) r;
    return c;
}

char *inputString(){
    // generate the string that contains 5 lower case letters
    char *str;
    int i, r, c;
    str = malloc (sizeof (char) * 6);
    char choice [4]= {'r','e','s','t'}; // only choose a random letter from these choices
    for(i = 0; i < 5; i++){
        //r = rand() % 26;   // generate a random char from a to z, but can be too slow to get "reset" and stop the loop
        //c = 'a' + r;
        c = choice[rand() % 4];
        str[i] = c;
    }
    str[5] = '\0';
    return str;
}

void testme(){
    int tcCount = 0;
    char *s;
    char c;
    int state = 0;
    while (1){
        tcCount++;
        c = inputChar();
        s = inputString();
        printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

        if (c == '[' && state == 0) state = 1;
        if (c == '(' && state == 1) state = 2;
        if (c == '{' && state == 2) state = 3;
        if (c == ' '&& state == 3) state = 4;
        if (c == 'a' && state == 4) state = 5;
        if (c == 'x' && state == 5) state = 6;
        if (c == '}' && state == 6) state = 7;
        if (c == ')' && state == 7) state = 8;
        if (c == ']' && state == 8) state = 9;
        if (s[0] == 'r' && s[1] == 'e'
            && s[2] == 's' && s[3] == 'e'
            && s[4] == 't' && s[5] == '\0'
            && state == 9){
            printf("error ");
            exit(200);
        }
    }
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    testme();
    return 0;
}
