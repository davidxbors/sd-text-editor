/*
	Librarie cu implementarile unor functii de baza pentru lucrul cu liste.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char data;
	struct node *next;
	struct node *back;
} Node;

typedef struct nodes {
	struct node data;
	struct nodes *next;
	struct nodes *back;
} Nodes;

Node *init_node(char data) {
	Node *node = (Node *)malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	node->back = NULL;

	return node;
}

Nodes *init_nodes(Node data) {
	Nodes *nodes = (Nodes *)malloc(sizeof(Nodes));
	nodes->data = data;
	nodes->next = NULL;
	nodes->back = NULL;

	return nodes;
}

void printList(Node *head) {
	if (head == NULL)
		return;
	else if (head->next == NULL) {
		printf("%c", head->data);
		return;
	} else {
		printf("%c", head->data);
		printList(head->next);
	}
}

void printNodes(Nodes *head){
	if(head == NULL)
		return;
	else if(head->next == NULL){
		printList(&head->data);
		return;
	} else {
		printList(&head->data);
		printNodes(head->next);
	}
}

Node *prependList(Node *head, char data) {
	Node *new_node = init_node(data);

	if (head == NULL)
		return new_node;
	else {
		new_node->next = head;
		head->back = new_node;
		return new_node;
	}
}

Nodes *prependNodes(Nodes *head, Node data) {
	Nodes *new_node = init_nodes(data);

	if (head == NULL)
		return new_node;
	else {
		new_node->next = head;
		head->back = new_node;
		return new_node;
	}
}

Node *pushList(Node *head, char data) {
	Node *new_node = init_node(data);
	Node *counter;

	if (head == NULL)
		return new_node;
	else {
		counter = head;
		while(counter->next != NULL)
			counter = counter->next;
		counter->next = new_node;
		new_node->back = counter;
		return head;
	}
}

Nodes *pushNodes(Nodes *head, Node data) {
	Nodes *new_nodes = init_nodes(data);
	Nodes *counter;

	if (head == NULL)
		return new_nodes;
	else {
		counter = head;
		while(counter->next != NULL)
			counter = counter->next;
		counter->next = new_nodes;
		new_nodes->back = counter;
		return head;
	}
}

Node *popList(Node *head) {
	if (head == NULL)
		return head;
	else if (head->next == NULL) {
		return NULL;
	} else {
		Node *ret = head->next;
		ret->back = NULL;
		free(head);
		return ret;
	}
}

Node *removeList(Node *head, char data) {
	if (head == NULL)
		return NULL;
	if (head->data == data) {
		head->next->back = NULL;
		return head->next;
	}
	Node *counter, *pcounter;
	short int ok = 0;
	pcounter = head;
	counter = head->next;
	while(counter != NULL && !ok){
		if(counter->data == data){
			pcounter->next = counter->next;
			counter->next->back = pcounter;
			free(counter);
			ok = 1;
		} else {
			pcounter = counter;
			counter = counter->next;
		}
	}
	return head;
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/* unused till now */

Node *lastNode(Node *head){
	Node *counter = head;
	counter = head;
	while(counter->next != NULL)
		counter = counter->next;
	return counter;
}

int lenList(Node *head){
	int counter = 1;
	while(head->next != NULL){
		++counter;
		head = head->next;
	}
	return counter;
}
