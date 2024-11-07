#include<stdio.h>
#include<stdlib.h>
#include"node.h"
#include"list.h"

static node* getNode(node* head, int index){
    node * n = head;
    for (int i = 1 ; i < index ; i++){
        n = n->next;
    }
    return n;
}

node* createNode(int data){
    node* new_node= (node*) malloc(sizeof(node));
    if (new_node == NULL){
        printf("Failed to allocate memrory");
        exit(1);
    }
    new_node->el = data;
    new_node->next = NULL;
    return new_node;    
}
// void meny(){
//     printf("\n0: Avsluta\n");
//     printf("1: Skriv ut listan\n");
//     printf("2: Skriv ut listans storlek\n");
//     printf("3: Lägg till ett heltal sist i listan\n");
//     printf("4: Lägg till ett heltal (valfri plats)\n");
//     printf("5: Ta bort ett givet heltal\n");
//     printf("6: Ta bort ett heltal (valfri plats)\n");   
//     printf("7: Töm listan\n");
//     printf("8: Vänd på listan\n");
//     printf("9: Skifta listan ett steg åt vänster (och lägg första heltalet sist)\n");
//     printf("10: Skifta listan ett steg åt höger (och lägg sista heltalet först)\n");
//     printf("11: Sortera listan (lägsta heltalet först)\n");
//     printf("12: Skriv ut startadress för listan\n");
//     printf("\nGör ditt val: ");
// }
int list_is_empty(node *head){  // return 1, if empty
    return head == NULL;
}

int size (node* head){
    if (head == NULL){
        return 0;
    }
    
    node* temp = head;
    int count= 0;
    while (temp != NULL){
        count ++;
        temp = temp->next;
    }
    return count;
}
void insertEnd(node** head, int data){
    node* new_node = (node*) malloc (sizeof(node));
    if(new_node == NULL){
        exit(1);
    }
    new_node->el = data;
    new_node->next = NULL;
    // check if list is empty
    if (*head == NULL){
        *head = new_node;
        return;
    }
    
    node* last_node= *head;
    // travers the list and point to the last node and insert new node
    while (last_node->next != NULL){
        last_node = last_node->next;
    }
    last_node->next = new_node;   
}
void insertAtPosition(node** head, int value, int position){
    node* new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL){
        return;     // failed to allocate memory
    }
    new_node->el = value;
    new_node->next = NULL;
    if (position <= 0){
        return;
    }

    // if list is empty, inserting in first position
    if (*head == NULL && position ==1 ){
        *head = new_node;
        return;
    }

    int sizea = size(*head);
    if (position > sizea+1){       // +1 : to insert at the end
        return;
    }

    // Not empty list: 1. check input index ()    
    if (position == 1){
        new_node->next = *head;
        *head = new_node;
        return;
    }
    
    // find the node in position index-1
    node* prev= *head;
    int i =1;
    while (i != position-1){   
        prev = prev->next;
        i++;
    }

    new_node->next = prev->next;
    prev->next = new_node;
}
int removeValue(node** head, int value){
    if (*head == NULL){
        return 1;
    }

    if ((*head)->el == value){  // value in first place        
        node* temp = *head;
        *head = (*head)->next;
        free(temp);
        temp= NULL;
        return 2;
    }
    node* ptr = *head;
    while (ptr->next != NULL){          // value in other places
        if (ptr->next->el == value){
            node* temp = ptr->next;
            ptr->next = temp->next;
            free(temp);
            temp = NULL;
            return 3;
        }
        ptr = ptr->next;
    }
    return 4;
}
void removeAtPos(node** head, int pos){
    if (*head == NULL){
        return;
    }

    if (pos <= 0 || pos > size(*head)){
        printf("Invalid position or out of range\n");
        return;
    }

    node* ptr = *head;
    if (size(*head) == 1 && pos == 1){     // one el & remove pos 1
        free(ptr);
        free(*head);
        *head= NULL;
        ptr = NULL;
        // printf("haahaha hererereeee\n");
        return;
    }
    else       // more than one el
    {
        if (pos == 1){          // first pos
            *head = ptr->next;
            free(ptr);
            ptr = NULL;
        }
        else                    // other pos
        {
            node* prev = *head;
            int i = 1;
            while (i != pos)
            {
                prev= ptr;
                ptr= ptr->next;
                i++;
            }
            if (ptr->next == NULL && pos == size(*head)){           // last pos    
                prev->next = NULL;
                free(ptr);
                ptr = NULL;
            }
            else                                                    // other pos
            {
                prev->next = ptr->next;
                free(ptr);
                ptr == NULL;
            }
        }        
    }
    
    
    
}
void deallocate(node** head){
    node* ptr= *head;
    node* temp= *head;
    while (ptr!= NULL){
        temp= ptr;
        ptr = ptr->next;
        free(temp);
    }
    *head=NULL;    
}
node* reversList(node* head){
    if (head == NULL){
        printf("empty in revers");
        return head;
    }
    node* prev= NULL;
    node* n = NULL;
    while (head != NULL){
        n = head->next;
        head->next = prev;
        prev = head;
        head = n;
    }
    head = prev;
    return head;
}
void reversList2(node** head){
    if (*head == NULL){
        printf("empty in revers2");
        return;
    }

    node* h = *head;
    node* n = NULL;
    node* p = NULL;
    while (h != NULL){
        n = h->next;
        h->next = p;
        p = h;
        h = n;
    }
    *head = p;
}
void shiftLeft(node** head){
    if (*head == NULL || (*head)->next == NULL){
        printf("Empty or one element in SL");
        return;
    }

    node* last = *head;
    node* first= *head;
    node* sec = first->next;
    while (last->next != NULL){        
        last = last->next;
    }
    last->next = first;
    first->next = NULL;
    *head = sec;
}
void shiftRight(node** head){
    if (*head == NULL || (*head)->next == NULL){
        return;
    }
    node* first = *head;
    node* sec_last= *head;
    while (sec_last->next->next != NULL){   // stop on the sec last element
        sec_last = sec_last->next;
    }
    *head = sec_last->next ;                // *head = last element
    (*head)->next = first; 
    sec_last->next = NULL;

}
void sortAsc(node* head){
    if (head == NULL || head->next == NULL){
        return;
    }
    node* i= head;
    node* j= NULL;
    int temp;
    for (i = head ; i->next != NULL ; i = i->next){
        for (j = i->next ; j != NULL ; j = j->next){
            if (i->el > j->el)
            {   // swap                
                temp = i->el;
                i->el = j->el;
                j->el = temp;
            }            
        }        
    }
}
void headAddr(node** head){
    if (head == NULL){
        return;
    }

    
    printf("\nhead Address &head->next  : %d", (*head)->next);
    
    printf("\nhead Address **head       : %d", **head);

    // these two correct
    printf("\nhead Address *head        : %d", *head); 
    printf("\nhead Address (void*)*head : %d", (void*)*head);

    printf("\nhead Address (void*)head  : %d", (void*)head);
    printf("\nhead Address head         : %d", head);

    printf("\nhead Address (void*)&head : %d", (void*)&head);
    printf("\nhead Address &head        : %d", &head);
    
}

