#include <stdio.h>
#include "lista.h"
// #include "stiva.h"

/* comenzi de baza */
// DONE: scrie descriere functie del
// TODO: scrie microinstructiune ins
// TODO: scrie microinstructiune chg + implementare <<pointer>> general
/*
 * functie care sterge caracterul j de pe linia i, sau daca j = -1 sterge toata
 * linia i. 
 * Coduri returnare:
 * ret -1 = linia ceruta(i) nu exista
 * ret -2 = caracterul cerut nu exista pe linia data
 * ret -3 = a sters linia i
 * altfel functia returneaza caracterul sters
*/
int del(Node *text, int i, int j){
    Node *p;
    int auxi, auxj;
    p = text;
    auxi = i;
    auxj = j;
    while(auxi && p){
        if(p->data == '\n') --auxi;
        p = p->next;
    }
    if(auxi && p == NULL)
        return -1;
    // printList(p);
    if(j == -1){
        Node *aux = p->back;
        while(auxj && p){
            if(p->data == '\n') auxj=0;
            p = p->next;
        }
        p->back = aux;
        aux->next = p;
        free(p->back);
        return -3;
    } else {
    while(auxj && p){
        p = p->next;
        auxj--;
    }
    if(auxj && p == NULL)
        return -2;
    p->back->next = p->next;
    p->next->back = p->back;
    int ret = p->data;
    free(p);
    return ret;
    }
}

/*
 * 
 * Coduri returnare:
 * ret -1 = linia ceruta(i) nu exista
 * ret -2 = caracterul cerut nu exista pe linia data
 * altfel functia returneaza caracterul adaugat
*/
int ins(Node *text, int i, int j, char data){
    Node *p;
    int auxi, auxj;
    p = text;
    auxi = i;
    auxj = j;
    while(auxi && p){
        if(p->data == '\n') --auxi;
        p = p->next;
    }
    if(auxi && p == NULL)
        return -1;
    while(auxj && p){
        p = p->next;
        auxj--;
    }
    if(auxj && p == NULL)
        return -2; 

    Node *n = p->next;
    printList(text);
    printf("[ins]> %c %c\n", p->data, n->data);

    Node *toAdd = init_node(data);

    printList(text);
    printf("got out \n");
    return data;
}


int main(){
    int err;
    Node *head = init_node('t');
    head = pushList(head, 'e');
    head = pushList(head, 's');
    head = pushList(head, 't');
    head = pushList(head, '1');
    head = pushList(head, '\n');
    head = pushList(head, 't');
    head = pushList(head, 'e');
    head = pushList(head, 's');
    head = pushList(head, 't');
    head = pushList(head, '2');
    head = pushList(head, '\n');
    head = prependList(head, '\n');
    head = prependList(head, '0');
    head = prependList(head, 't');
    head = prependList(head, 's');
    head = prependList(head, 'e');
    head = prependList(head, 't');

    printList(head);

    printf("Testing del function...\n");
    err = del(head, 1, -1);
    if(err == -1 || err == -2){
        printf("Eroare: %d\n", err);
        return 0;
    }
    printList(head);
    
    printf("Testing ins function...\n");
    err = ins(head, 1, 3, '0');
    if(err == -1 || err == -2){
        printf("Eroare: %d\n", err);
        return 0;
    }
    printList(head);
    
    return 0;
}