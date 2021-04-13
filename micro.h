/* 
 * comenzi de baza
 */
#include "lista.h"

/* coordonatele <<pointerului>> de text */
int PX, PY;

/*
 * functie care sterge caracterul j de pe linia i, sau daca j = -1 sterge toata
 * linia i. returneaza primul nod al listei dublu inlantuite in care este tinut
 * textul.
*/
Node *del(Node *text, int i, int j)
{
    Node *p;
    int auxi, auxj;
    p = text;
    auxi = i;
    auxj = j - 1;
    while (auxi && p)
    {
        if (p->data == '\n')
            --auxi;
        p = p->next;
    }
    if (auxi >= 0 && p == NULL)
    {
        printf("Erroare: nu exista linia data pentru stergere!\n");
        return text;
    }
    if (j == -1)
    {
        if (i)
        {
            Node *aux = p->back;
            Node *paux = p;
            Node *auxx = NULL;
            while (auxj && p)
            {
                if (p->data == '\n')
                    auxj = 0;
                p = p->next;
                paux = p;
            }
            if (p != NULL)
            {
                auxx = aux;
                aux = aux->next;
                while (aux != p)
                {
                    paux = aux;
                    aux = aux->next;
                    free(paux);
                }
                auxx->next = p;
                p->back = auxx;
            }
            else
            {
                auxx = aux;
                aux = aux->next;
                while (aux)
                {
                    paux = aux;
                    aux = aux->next;
                    free(paux);
                }
                auxx->next = NULL;
            }
            return text;
        }
        else
        {
            Node *aux;
            while (auxj && p)
            {
                aux = p;
                if (p->data == '\n')
                    auxj = 0;
                p = p->next;
                free(aux);
            }
            return p;
        }
    }
    else
    {
        if (i == 0 && j == 0)
        {
            Node *aux = text;
            text = text->next;
            free(aux);
            return text;
        }
        while (auxj >= 0 && p)
        {
            Node *aux = p;
            p = p->next;
            auxj--;
        }
        if (auxj && p == NULL)
            return text;
        p->back->next = p->next;
        if (p->next)
            p->next->back = p->back;
        free(p);
        return text;
    }
}

/*
 * Functie care insereaza in text, dupa pozitia i,j caracterul transmis prin 
 * argumentul data. Returneaza capul listei dublu inlantuite.
*/
Node *ins(Node *text, int i, int j, char data)
{
    Node *p, *aux, *auxx;
    p = NULL;
    aux = NULL;
    auxx = NULL;

    int auxi, auxj;
    p = text;
    auxi = i;
    auxj = j;

    if (i == 0 && j == 0)
    {
        Node *toAdd = init_node(data);
        toAdd->back = NULL;
        toAdd->next = text;
        if (text != NULL)
            text->back = toAdd;
        return toAdd;
    }
    while (auxi && p)
    {
        if (p->data == '\n')
            --auxi;
        auxx = aux;
        aux = p;
        p = p->next;
    }
    // printf("first aux: %d\n", auxi);
    if (auxi > 0 && p == NULL)
    {
        printf("Nu se poate insera decat maxim o pozitie in plus in afara\
         textului existent! err 1\n");
        return text;
    }
    if (auxi == 0 && p == NULL)
    {
        if (auxj > 0)
        {
            printf("Nu se poate insera decat maxim o pozitie in plus in afara\
             textului existent! err 3\n");
            return text;
        }
        Node *toAdd = init_node(data);
        toAdd->back = aux;
        toAdd->next = NULL;
        aux->next = toAdd;
        return text;
    }
    else
    {
        short int ok = 1;
        while (auxj && p && ok)
        {
            auxx = aux;
            aux = p;
            p = p->next;
            if (p != NULL && p->data == '\n')
            {
                ok = 0;
            }
            auxj--;
        }
        // printf("%d\n", auxj);
        if (auxj > 0 && p == NULL)
        {
            printf("Nu se poate insera decat maxim o pozitie in plus in afara\
         textului existent! err 2\n");
            return text;
        }
        if (p != NULL && !ok)
        {
            // printf("this case!\n");
            Node *toAdd = init_node(data);
            toAdd->next = p;
            aux->next = toAdd;
            toAdd->back = aux;
            p->back = toAdd;
        }
        else if (p != NULL)
        {
            //printf("wtf?!");
            Node *toAdd = init_node(data);
            toAdd->next = p;
            toAdd->back = aux;
            if (aux != NULL)
                aux->next = toAdd;
            p->back = toAdd;
        }
        else
        {
            //if(aux == NULL) printf("wtf\n");
            //printf("wtf?!");
            Node *toAdd = init_node(data);
            toAdd->next = aux->next;
            aux->next = toAdd;
            toAdd->back = aux;
        }
    }
    return text;
}

/*
 * functie care schimba coordonatele pointerului de scriere text
*/
void chg(int i, int j)
{
    PX = i;
    PY = j;
}

/*
 * functie care salveaza o lista de caractere intr-un fisier
 */
void save(Node *text, char *filename)
{
    FILE *fout = fopen(filename, "w");
    Node *counter = text;
    while (counter != NULL)
    {
        fprintf(fout, "%c", counter->data);
        counter = counter->next;
    }
    fclose(fout);
}

Node *del_word(Node *text, char *cuvant)
{
    Node *i = text;
    int aux = PX;
    int auy = PY;
    while (i && auy)
    {
        if (i->data == '\n')
            --auy;
        i = i->next;
    }
    while (i && aux)
    {
        --aux;
        i = i->next;
    }
    if (i)
        printf("%c\n", i->data);
    int ok = 0;
    int k = 0;
    int sx, sy;
    aux = PX;
    while (!ok && i)
    {
        while (i && i->data != cuvant[k])
            i = i->next, aux++;
        sx = aux;
        sy = aux;
        while (i && i->data == cuvant[k] && k < strlen(cuvant))
        {
            ++k;
            i = i->next;
            sy++;
        }
        if (k == strlen(cuvant))
        {
            ok = 1;
            // printf("before:\n");
            // printList(text);
            // printf("traba sters intre %d si %d inclusiv\n", sx, sy-1);
            aux = k;
            while (aux)
            {
                del(text, PY, sx);
                --aux;
            }
            // printf("after:\n");
            // printList(text);
        }
        else
        {
            k = 0;
        }
    }
    return i;
}

Node *replaceWord(Node *text, char *find, char *replace)
{
    Node *i;
    int PPX, PPY;
    i = del_word(text, find);
    printf("L-am sters si acum py, px sunt: %d, %d\n", PY, PX);
    PX++;
    int j = 0;
    for (; j < strlen(replace); j++)
    {
        printf("Insert %c @ (%d, %d)\n", *(replace + j), PY, PX);
        ins(i, PY, PX, *(replace + j));
        if (*(replace + j) == '\n')
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
    }
    return i;
}