#include <stdio.h>
#include "micro.h"
#include "stiva.h"

/*
 * implement:
 * DONE q -> quit
 * DONE ::i -> switcher
 * insert chars -> done
 * u
 * r
 * s
 * b
 * dl [line]
 * gl line
 * gc char [line]
 * d [chars]
 * re old_word new_word
 * ra old_word new_word
 * dw word
 * da word  
 */

int main(){
    char c;
    short int running = 1;
    short int state = 1;
    Node *text = NULL;
    Node *brut_text = NULL;
    Stiva *comenzi;

    chg(0, 0);

    while(running){
        scanf("%c", &c);
        if(c != 'q'){
        	brut_text = pushList(brut_text, c);
        } else running = 0;
    }

    Node *counter = brut_text;
    while (counter != NULL)
    {
        if(counter->next != NULL && counter->next->next && counter->data == ':' &&
        counter->next->data == ':' && counter->next->next->data == 'i'){
            state = !state;
            counter = counter->next->next->next->next;
        } else {
            if(state){
                printf("insert %c @ %d %d\n", counter->data, PY, PX);
                text = ins(text, PY, PX, counter->data);
                if(counter->data == '\n'){
                    PX = 0;
                    PY++;
                } else {
                    PX++;
                }
                counter = counter->next;
            } else {
                counter = counter->next;
            }
        }
    }

    printList(text);
    return 0;
}
