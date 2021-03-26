#include <stdio.h>
#include "micro.h"
#include "stiva.h"

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

    printf("Testing del function...\n");
    head = del(head, 2, 4);
    printList(head);

    printf("Testing ins function...\n");
    head = ins(head, 4, 0, '0');
    head = getHead(head);
    printList(head);
    printf("\n");
    return 0;
}
