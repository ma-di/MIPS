// #include<stdlib.h>
#ifndef LIST_H
#define LIST_H

#include "node.h"
// #include"list.c"

static node* getNode(node* head, int index);
node* createNode(int data);

int size(node*);
int list_is_empty(node*);
void printList (node* );
int size (node* );
void insertEnd(node** , int);
void insertAtPosition(node** head, int value, int index);
int removeValue(node** head, int value);
void removeAtPos(node** head, int pos);
void deallocate(node**);
node* reversList(node* head);
void reversList2(node** head);
void shiftLeft(node** head);
void shiftRight(node** head);
void sortAsc(node* head);
void headAddr(node** head);






#endif /* LIST_H */