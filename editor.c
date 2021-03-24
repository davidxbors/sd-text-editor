#include <stdio.h>
#include "lista.h"
#include "stiva.h"

/* comenzi de baza */

/*
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

// int del(Nodes *text, int i, int j){
//     Nodes *p;
//     int auxi, auxj;
//     auxi = i;
//     auxj = j;
//     p = text;
//     while(auxi){
//         p = p->next;
//         --auxi;
//     }
//     if(p == NULL)
//         return -1;
//     Node *h = &p->data;
//     while(auxj){
//         h = h->next;
//         --auxj;
//     }
//     if(h == NULL)
//         return -2;
//     printf("%c\n", h->data);
//     int ret = h->data;
//     printList(&p->data);
//     return ret;
// }



int main(){
    //////// test lista.h
    // Node *p = init_node('d');
    // p = pushList(p, 'a');
    // p = pushList(p, 'v');
    // p = pushList(p, 'i');
    // p = pushList(p, 'd');
    // printList(p);
    // p = prependList(p, '_');
    // printList(p);
    // p = popList(p);
    // printList(p);
    ///////// test stiva.h
    // Stiva *s = init_stiva('d');
    // s = pushStiva(s, 'a');
    // s = pushStiva(s, 'v');
    // printStiva(s);
    // s = popStiva(s);
    // printStiva(s);

    
    // Nodes *head = init_nodes(*p3);
    // head = pushNodes(head, *p2);
    // head = prependNodes(head, *p);
    // printNodes(head);

    // printf("Testing del function...\n");
    // del(head, 1, 1);
    // printNodes(head);

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
    del(head, 1, -1);
    printList(head);
    return 0;
}