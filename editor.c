#include <stdio.h>
#include <string.h>
#include "micro.h"
#include "stiva.h"

/*
 * implement:
 * DONE q -> quit
 * DONE ::i -> switcher
 * insert chars -> done
 * DONE s -> save the document
 * DONE b -> del the last char before pointer
 * DONE dl [line] -> del either the current line or line number [line]
 * DONE gl line -> set cursor on line
 * gc char [line]
 * d [chars]
 * dw word
 * da word  
 * re old_word new_word
 * ra old_word new_word
 * u
 * r
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
                printf("insert %c @ %d %d\n", counter->data, PY, PX);
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
                } else if(counter->data == 'd' && counter->next->data == 'l') {
                    counter = counter->next->next;
                    if(counter && counter->data == '\n'){
                        // se sterge linia
                        text = del(text, PY, -1);
                    } else if(counter && counter->data == ' '){
                        Node *cc;
                        cc = counter->next;
                        int x = 0;
                        int p = 1;
                        while(cc && cc->data != '\n'){
                            printf("haha: %d ; %d\n", atoi(&cc->data), x);
                            x = x * p + atoi(&cc->data);
                            p *= 10;
                            cc = cc->next;
                        }
                        text = del(text, x, -1);
                    }
                } else if(counter->data == 'g' && counter->next->data == 'l' &&
                    counter->next->next->data == ' '){
                        Node *cc;
                        cc = counter->next;
                        int x = 0;
                        int p = 1;
                        while(cc && cc->data != '\n'){
                            printf("haha: %d ; %d\n", atoi(&cc->data), x);
                            x = x * p + atoi(&cc->data);
                            p *= 10;
                            cc = cc->next;
                        }
                        printf("%d\n", x);
                        chg(0, x-1);
                    }
                if(counter != NULL)
                    counter = counter->next;
            }
        }
    }

    printList(text);

    // text = ins(text, 0, 0, 'a');
    // text = ins(text, 0, 1, 'a');
    // text = ins(text, 0, 2, 'a');
    // text = ins(text, 0, 3, '\n');
    // text = ins(text, 1, 0, 'b');
    // text = ins(text, 1, 1, 'b');
    // text = ins(text, 1, 2, 'b');
    // text = ins(text, 1, 3, '\n');
    // text = ins(text, 2, 0, 'c');
    // text = ins(text, 2, 1, 'c');
    // text = ins(text, 2, 2, 'c');
    // text = ins(text, 2, 3, '\n');

    // printList(text);

    // text = ins(text, 1, 3, 't');
    // text = ins(text, 1, 4, 'e');
    // text = ins(text, 1, 5, 's');
    // text = ins(text, 1, 6, 't');
    // printList(text);
    return 0;
}
