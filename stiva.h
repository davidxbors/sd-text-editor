/*
	Librarie cu implementarile unor functii de baza pentru lucrul cu stiva.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct stiva {
	char *data;
	struct stiva *next;
	struct stiva *back;
} Stiva;

Stiva *init_stiva(char *data) {
	Stiva *stiva = (Stiva *)malloc(sizeof(Stiva));
	stiva->data = data;
	stiva->next = NULL;
	stiva->back = NULL;

	return stiva;
}

void printStiva(Stiva *head) {
	if (head == NULL)
		return;
	else if (head->next == NULL) {
		printf("%s\n", head->data);
		return;
	} else {
		printf("%s ", head->data);
		printStiva(head->next);
	}
}

Stiva *pushStiva(Stiva *head, char *data) {
	Stiva *new_stiva = init_stiva(data);
	Stiva *counter;

	if (head == NULL)
		return new_stiva;
	else {
		counter = head;
		while(counter->next != NULL)
			counter = counter->next;
		counter->next = new_stiva;
		new_stiva->back = counter;
		return head;
	}
}

Stiva *peek(Stiva *head){
	Stiva *counter = head;
	counter = head;
	while(counter->next != NULL)
		counter = counter->next;
	return counter;
}


Stiva *popStiva(Stiva *head) {
	if (head == NULL)
		return head;
	else if (head->next == NULL) {
		return NULL;
	} else {
		Stiva *counter = head;
		while(counter->next->next) counter = counter->next;
		free(counter->next);
		counter->next = NULL;
		return head;
	}
}

int lenStiva(Stiva *head){
	int counter = 1;
	while(head->next != NULL){
		++counter;
		head = head->next;
	}
	return counter;
}
