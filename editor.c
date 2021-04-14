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
 * DONE d [chars]
 * DONE dw word
 * DONE da word  
 * DONE re old_word new_word + reformat code;
 * ra old_word new_word
 * u
 * r
 */

void freeList(Node *list){
	while(list)
		list = del(list, 0, 0);
}

int main()
{
    char c;
    short int running = 1;
    short int state = 1;
    int PPX, PPY;
    Node *text = NULL;
    Node *brut_text = NULL;
    Stiva *comenzi;

    FILE *in;
    in = fopen("editor.in", "r");

    chg(0, 0);

    while (running && !feof(in))
    {
        fscanf(in, "%c", &c);
        if (c != 'q')
        {
            brut_text = pushList(brut_text, c);
        }
        else
            running = 0;
    }

    Node *counter = brut_text;
    while (counter != NULL)
    {
        if (counter->next != NULL && counter->next->next && counter->data == ':' &&
            counter->next->data == ':' && counter->next->next->data == 'i')
        {
            if (counter->next->next->next != NULL)
            {
                // printf("test.\n");
                counter = counter->next->next->next->next;
            }
            else
                counter = counter->next->next->next;
            // if (state)
            // {
            //     Node *tail = lastNode(text);
            //     tail->back->next = NULL;
            //     chg(PPX - 1, PPY);
            // }
            state = !state;
        }
        else
        {
            if (state)
            {
                printf("insert %c @ %d %d\n", counter->data, PY, PX);
                text = ins(text, PY, PX, counter->data);
                if (counter->data == '\n')
                {
                    PPX = PX;
                    PPY = PY;
                    PX = 0;
                    PY++;
                }
                else
                {
                    PPX = PX;
                    PPY = PY;
                    PX++;
                }
                counter = counter->next;
            }
            else
            {
                if (counter->data == 's')
                {
                    save(text, "editor.out");
                    counter = counter->next;
                }
                else if (counter->data == 'b')
                {
                    // printf("%d %d\n", PX, PY);
                    text = del(text, PY, PX );
                    counter = counter->next;
                }
                else if (counter->data == '\n')
                {
                    printf("ok.\n");
                }
                else if (counter->data == 'd' && counter->next->data == 'l')
                {
                    counter = counter->next->next;
                    if (counter && counter->data == '\n')
                    {
                        // se sterge linia
                        text = del(text, PY, -1);
                    }
                    else if (counter && counter->data == ' ')
                    {
                        Node *cc;
                        cc = counter->next;
                        int x = 0;
                        int p = 1;
                        while (cc && cc->data != '\n')
                        {
                            printf("haha: %d ; %d\n", atoi(&cc->data), x);
                            x = x * p + atoi(&cc->data);
                            p *= 10;
                            cc = cc->next;
                        }
                        text = del(text, x-1, -1);
                    }
                }
                else if (counter->data == 'g' && counter->next->data == 'l' &&
                         counter->next->next->data == ' ')
                {
                    Node *cc;
                    cc = counter->next;
                    int x = 0;
                    int p = 1;
                    while (cc && cc->data != '\n')
                    {
                        printf("haha: %d ; %d\n", atoi(&cc->data), x);
                        x = x * p + atoi(&cc->data);
                        p *= 10;
                        cc = cc->next;
                    }
                    printf("%d\n", x);
                    chg(0, x - 1);
                }
                else if (counter->data == 'g' && counter->next->data == 'c')
                {
                    counter = counter->next->next->next;
                    int cauta = atoi(&counter->data);
                    counter = counter->next;
                    if (counter && counter->data == '\n')
                    {
                        // se cauta pe linia curenta
                        chg(cauta-1, PY);
                    }
                    else if (counter && counter->data == ' ')
                    {
                        // se va cauta pe linia x
                        Node *cc;
                        cc = counter->next;
                        int x = 0;
                        int p = 1;
                        while (cc && cc->data != '\n')
                        {
                            printf("haha: %d ; %d\n", atoi(&cc->data), x);
                            x = x * p + atoi(&cc->data);
                            p *= 10;
                            cc = cc->next;
                        }
                        printf("%d %d\n", cauta-1, x-1);
                        chg(cauta-1, x-1);
                    }
                }
                else if (counter->data == 'd' && counter->next->data == 'w')
                {
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
                    del_word(text, cuvant);
                }
                else if (counter->data == 'd' && counter->next->data == ' ')
                {
                    Node *cc;
                    cc = counter->next;
                    int x = 0;
                    int p = 1;
                    while (cc && cc->data != '\n')
                    {
                        printf("haha: %d ; %d\n", atoi(&cc->data), x);
                        x = x * p + atoi(&cc->data);
                        p *= 10;
                        cc = cc->next;
                    }
                    printf("sterg %d caractere", x);
                    while (x)
                    {
                        del(text, PY, PX);
                        --x;
                    }
                }
                else if (counter->data == 'd' && counter->next->data == '\n')
                {
                    del(text, PY, PX);
                }
                else if (counter->data == 'd' && counter->next->data == 'a')
                {
                    counter = counter->next->next->next;
                    char *cuvant = (char *)malloc(100);
                    while (counter != NULL && counter->data != '\n')
                    {
                        strcat(cuvant, &counter->data);
                        counter = counter->next;
                    }
                    printf("traba sters cuvantul %s\n", cuvant);
                    Node *i;
                    i = del_word(text, cuvant);
                    while (i != NULL)
                    {
                        i = del_word(text, cuvant);
                    }
                }
                else if (counter->data == 'r' && counter->next->data == 'e')
                {
                    counter = counter->next->next->next;
                    char *find = (char *)malloc(100);
                    char *replace = (char *)malloc(100);
                    while (counter != NULL && counter->data != ' ')
                    {
                        strcat(find, &counter->data);
                        counter = counter->next;
                    }
                    printf("traba sters cuvantul %s\n", find);
                    counter = counter->next;
                    while (counter != NULL && counter->data != '\n')
                    {
                        strcat(replace, &counter->data);
                        counter = counter->next;
                    }
                    printf("si inlocuit cu: %s\n", replace);
                    replaceWord(text, find, replace);
                }
                else if(counter->data == 'r' && counter->next->data == 'a'){
                    counter = counter->next->next->next;
                    char *find = (char *)malloc(100);
                    char *replace = (char *)malloc(100);
                    while (counter != NULL && counter->data != ' ')
                    {
                        strcat(find, &counter->data);
                        counter = counter->next;
                    }
                    printf("traba sters cuvantul %s\n", find);
                    counter = counter->next;
                    while (counter != NULL && counter->data != '\n')
                    {
                        strcat(replace, &counter->data);
                        counter = counter->next;
                    }
                    printf("si inlocuit cu: %s\n", replace);
                    int auxX = PX;
                    int auxY = PY;

                    chg(0,0);

                    // do work
                    Node *i = replaceWord(text, find, replace);
                    while(i != NULL){
                        i = replaceWord(i, find, replace);
                    }

                    chg(auxX, auxY);
                }
                if (counter != NULL)
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
    fclose(in);
    freeList(brut_text);
    freeList(text);
    return 0;
}
