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
 * DONE gc char [line] -> set cursor at char and even on a specific line number
 * DONE dw word
 * d [chars]
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
                } else if(counter->data == 'g' && counter->next->data == 'c'){
                    counter = counter->next->next->next;
                    char cauta = counter->data;
                    counter = counter->next;
                    // printf("wtf: %c %c\n", cauta, counter->data);
                    if(counter && counter->data == '\n'){
                        // se cauta pe linia curenta
                        Node *i = text;
                        int ax = PX;
                        int ay = PY;
                        int aux = PY;
                        PX = 0;
                        while(i && aux){
                            if(i->data == '\n') --aux;
                            i = i->next;
                        }
                        // printf("am primit gc simplu si caut caracterul %c!", cauta);
                        // printf("%c\n", i->data);
                        while(i && i->data != '\n' && i->data != cauta){
                            i = i->next;
                            PX++;
                        }
                        if(i == NULL || i->data == '\n'){
                            printf("Nu s-a gasit caracterul pe linia curenta!\n");
                            chg(ax, ay);
                        } else {
                        printf("Am gasit %c pe linia %d coloana %d!\n", cauta, PY, PX);
                        }
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
                        // se cauta pe linia x
                        Node *i = text;
                        int ax = PX;
                        int ay = PY;
                        int aux = x;
                        PX = 0;
                        while(i && aux){
                            if(i->data == '\n') --aux;
                            i = i->next;
                        }
                        PY = x;
                        // printf("am primit gc simplu si caut caracterul %c!", cauta);
                        // printf("%c\n", i->data);
                        while(i && i->data != '\n' && i->data != cauta){
                            i = i->next;
                            PX++;
                        }
                        if(i == NULL || i->data == '\n'){
                            printf("Nu s-a gasit caracterul pe linia curenta!\n");
                            chg(ax, ay);
                        } else {
                        printf("Am gasit %c pe linia %d coloana %d!\n", cauta, PY, PX);
                        }
                    }
                } else if(counter->data == 'd' && counter->next->data == 'w'){
                    counter = counter->next->next->next;
                    char *cuvant = (char *)malloc(100);
                    while (counter != NULL && counter->data != '\n')
                    {
                        // char str[2];
                        // str[0] = counter->data;
                        strcat(cuvant, &counter->data);                        
                        counter = counter->next;
                    }
                    printf("traba sters cuvantul %s\n", cuvant);
                    Node *i = text;
                    int aux = PX;
                    int auy = PY;
                    while(i && auy){
                        if(i->data == '\n') --auy;
                        i = i->next;
                    }
                    while (i && aux)
                    {
                        --aux;
                        i = i->next;
                    }
                    if(i)
                    printf("%c\n", i->data);
                    int ok = 0;
                    int k = 0;
                    int sx, sy;
                    aux = PX;
                    while(!ok && i){
                        while(i && i->data != cuvant[k]) i = i->next, aux++;
                        sx = aux;
                        sy = aux;
                        while(i && i->data == cuvant[k] && k < strlen(cuvant)){
                            ++k;
                            i = i->next;
                            sy++;
                        }
                        if(k == strlen(cuvant)){ 
                            ok = 1;
                            // printf("before:\n");
                            // printList(text);
                            // printf("traba sters intre %d si %d inclusiv\n", sx, sy-1);
                            aux = k;
                            while(aux){
                                del(text, PY, sx);
                                --aux;
                            }
                            // printf("after:\n");
                            // printList(text);
                        } else {
                            k = 0;
                        }
                    }
                } else if(counter->data == 'd' && counter->next->data == ' '){
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
                        printf("sterg %d caractere", x);
                        while(x){
                            del(text, PY, PX);
                            --x;
                        }
                } else if(counter->data == 'd' && counter->next->data == '\n'){
                    del(text, PY, PX);
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
