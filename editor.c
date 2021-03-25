#include <stdio.h>
#include "lista.h"
// #include "stiva.h"

/* comenzi de baza */
// DONE: scrie descriere functie del
// DONE: scrie microinstructiune ins
// DONE:scrie microinstructiune chg + implementare <<pointer>> general
// DONE:  update del: cazuri speciale de null
// DONE: update del: return head
// TODO: update ins: return head
// TODO: create micro.h

int PX, PY;
/*
 * functie care sterge caracterul j de pe linia i, sau daca j = -1 sterge toata
 * linia i. returneaza primul nod al listei dublu inlantuite in care este tinut
 * textul.
*/
Node *del(Node *text, int i, int j){
    Node *p;
    int auxi, auxj;
    p = text;
    auxi = i;
    auxj = j-1;
    while(auxi && p){
        if(p->data == '\n') --auxi;
        p = p->next;
    }
    if(auxi >= 0 && p == NULL){
        printf("Erroare: nu exista linia data pentru stergere!\n");
        return text;
    }
    if(j == -1){
        if(i){
        Node *aux = p->back;
        Node *paux = p;
        while(auxj && p){
            if(p->data == '\n') auxj=0;
            p = p->next;
            paux = p;
        }
        if(p!=NULL){
        p->back = aux;
        aux->next = p;
        } else aux->next = NULL;
        return text;
        } else {
        while(auxj && p){
            if(p->data == '\n') auxj=0;
            p = p->next;
        }   
        return p;
        }
    } else {
    if(i == 0 && j == 0)
        return text->next;
    while(auxj >= 0 && p){
        p = p->next;
        auxj--;
    }
    if(auxj && p == NULL)
        return text;
    p->back->next = p->next;
    if(p->next)
        p->next->back = p->back;
    free(p);
    return text;
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
    Node *p, *aux;
    int auxi, auxj;
    p = text;
    auxi = i;
    auxj = j;
    while(auxi && p){
        if(p->data == '\n') --auxi;
        aux = p;
        p = p->next;
    }
    if(auxi == 0 && p == NULL){
        Node *toAdd = init_node(data);
        toAdd->back = p->back;
        toAdd->next = p;
        p->back = toAdd;
        if(toAdd->back != NULL)
            toAdd->back->next = toAdd;
        return 0;
    }
    if(auxj == -1){
        Node *toAdd = init_node(data);
        toAdd->back = p->back;
        toAdd->next = p;
        p->back = toAdd;
        if(toAdd->back != NULL)
            toAdd->back->next = toAdd;
    } else {
    while(auxj && p){
        p = p->next;
        auxj--;
    }
    if(auxj >= 0 && p == NULL)
        return -2; 
    Node *toAdd = init_node(data);
    toAdd->next = p->next;
    toAdd->back = p;
    if(p->next != NULL)
        p->next->back = toAdd;
    p->next = toAdd;
    }
    return data;
}

/*
 * functie care schimba coordonatele pointerului de scriere text
*/
void chg(int i, int j){
    PX = i;
    PY = j;
}

int main(){
    PX = PY = 0;
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

    // printf("Testing del function...\n");
    // head = del(head, 2, 3);
    // printList(head);

    printf("Testing ins function...\n");
    err = ins(head, 0, -1, '0');
    err = ins(head, 3, 2, '0');
    printf("%d\n", err);
    head = getHead(head);
    printList(head);
    return 0;
}
