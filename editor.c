#include <stdio.h>
#include "micro.h"
#include "stiva.h"

/*
 * implement:
 * DONE q -> quit
 * DONE ::i -> switcher
 * insert chars
 * u
 * r
 * s
 * q
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
    Node *text;
    Node *brut_text;
    Stiva *comenzi;
    short int state = 1; /* 1 -> writing; 0 -> commands */

    chg(0, 0);
    
    while(running){
        scanf("%c", &c);
        if(c != 'q'){
            brut_text = pushList(brut_text, c);
        } else running = 0;
    }

    text = ins(text, 0, 0, 'a');
    text = ins(text, 0, 1, 'a');
    // printList(text);
    // printList(text);
    // printList(brut_text);
//     PX = PY = 0;
//     Node *counter = brut_text;
//     while (counter != NULL)
//     {
//         if(counter->next != NULL && counter->next->next && counter->data == ':' &&
//         counter->next->data == ':' && counter->next->next->data == 'i'){
//             state = !state;
//             counter = counter->next->next->next->next;
//         } else {
//             if(state){
//                 printf("insert %c @ %d %d\n", counter->data, PY, PX);
//                 text = ins(text, PY, PX, counter->data);
//                 if(c == '\n'){
//                     PX = 0;
//                     PY++;
//                 } else {
//                     PX++;
//                 }
//                 counter = counter->next;
//             } else {
//                 counter = counter->next;
//             }
//         }
//     }
//    return 0;
}
