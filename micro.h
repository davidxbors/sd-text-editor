/* 
 * comenzi de baza
 */
#include "lista.h"

// DONE: scrie descriere functie del
// DONE: scrie microinstructiune ins
// DONE:scrie microinstructiune chg + implementare <<pointer>> general
// DONE:  update del: cazuri speciale de null
// DONE: update del: return head
// DONE: update ins: return head
// DONE: create micro.h

/* coordonatele <<pointerului>> de text */
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
 * Functie care insereaza in text, dupa pozitia i,j caracterul transmis prin 
 * argumentul data. Returneaza capul listei dublu inlantuite.
*/
Node *ins(Node *text, int i, int j, char data){
    Node *p, *aux;
    int auxi, auxj;
    p = text;
    auxi = i;
    auxj = j;
    if(i == 0 && j == 0){
        Node *toAdd = init_node(data);
        toAdd->back = NULL;
        toAdd->next = text;
        text->back = toAdd;
        return toAdd;
    }
    while(auxi && p){
        if(p->data == '\n') --auxi;
        aux = p;
        p = p->next;
    }
    if(auxi > 1 && p == NULL){
        printf("Nu se poate insera decat maxim o pozitie in plus in afara textului existent! err 1\n");
        return text; 

    }
    if(auxi == 1 && p == NULL){
        Node *toAdd = init_node(data);
        toAdd->back = aux;
        toAdd->next = p;
        aux->next = toAdd;
        return text;
    } else {
    while(auxj && p){
        p = p->next;
        if(p->data == '\n')
            p = NULL;
        auxj--;
    }
    if(auxj >= 0 && p == NULL){
        printf("Nu se poate insera decat maxim o pozitie in plus in afara textului existent! err 2\n");
        return text; 
    }
    Node *toAdd = init_node(data);
    toAdd->next = p->next;
    toAdd->back = p;
    if(p->next != NULL)
        p->next->back = toAdd;
    p->next = toAdd;
    }
    return text; 
}

/*
 * functie care schimba coordonatele pointerului de scriere text
*/
void chg(int i, int j){
    PX = i;
    PY = j;
}