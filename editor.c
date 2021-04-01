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
 * DONE s -> save the document
 * DONE b -> del the last char before pointer
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
    int PPX, PPY;
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
            if(counter->next->next->next != NULL){
                // printf("test.\n");
                counter = counter->next->next->next->next;
            }
            else
                counter = counter->next->next->next;
            if(state){
            Node *tail = lastNode(text);
            tail->back->next = NULL;
            chg(PPX-1, PPY);
            }
            state = !state;
            
        } else {
            if(state){
                // printf("insert %c @ %d %d\n", counter->data, PY, PX);
                text = ins(text, PY, PX, counter->data);
                if(counter->data == '\n'){
                    PPX = PX;
                    PPY = PY;
                    PX = 0;
                    PY++;
                } else {
                    PPX = PX;
                    PPY = PY;
                    PX++;
                }
                counter = counter->next;
            } else {
                if(counter->data == 's'){
                    save(text, "editor.out");
                    counter = counter->next;
                }
                else if(counter->data == 'b'){
                    // printf("%d %d\n", PX, PY);
                    text = del(text, PY, PX-1);
                    counter = counter->next;
                }
                else if(counter->data == '\n'){
                    printf("ok.\n");
                }
                if(counter != NULL)
                    counter = counter->next;
            }
        }
    }

    printList(text);
    return 0;
}
