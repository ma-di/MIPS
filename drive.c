#include "drive.h"
#include "list.h"
#include <stdio.h>
#include"node.h"



void meny(){
        printf("\n#####################################\n");
        printf("\t\tMenu:");
        printf("\n#####################################\n");
        
        printf("0: Terminate\n");
        printf("1: Print the list\n");
        printf("2: Print the size of the list\n");
        printf("3: Add an integer to the end of the list\n");
        printf("4: Add an integer (any place)\n");
        printf("5: Remove a given integer\n");
        printf("6: Remove an integer (any place)\n");
        printf("7: Clear the list\n");
        printf("8: Reverse the list\n");
        printf("9: Shift the list left\n");
        printf("10: Shift the list right\n");
        printf("11: Sort the list\n");
        printf("12: Print starting address of the list\n\n");
        printf("Make your choice: ");
}

void drivePrintSize(node* head){
    printf("Size: %d\n", size(head));
}

void drivePrintList (node* head){
    if (head == NULL){
        printf("The list is empty.\n");
        return;
    }
    
    node* temp= head;    
    while (temp != NULL)
    {
        printf("%d ", temp->el);
        temp = temp->next;
    }printf("\n");
}

void driveInsertEnd(node** head){
    int data;
    printf("Enter the integer: ");
    scanf("%d", &data);
    // int position = list_size(*head); // end position
    insertEnd(head, data);
}

void driveInsertAtPosition(node** head){
    int data;
    printf("Enter the integer: ");
    scanf("%d", &data);

    int position;
    printf("Enter the position: ");
    scanf("%d", &position);

    if (position <= 0){
        printf("\nInvalid position nr %d ", position);
        return;
    }
    int max = size(*head);
    if (position > max+1){       // +1 : to insert at the end
        printf("\nPosition %d is out of range.", position);
        return;
    }

    insertAtPosition(head, data, position);    
}

void driveRemoveValue(node** head){
    if (*head == NULL){
        printf("\nList is empyt.\n");
        return;
    }
    int data;
    printf("Enter the integer: ");
    scanf("%d", &data);
    int res = removeValue(head, data);
    if (res == 4){
        printf("Value NOT found!\n");
        return;
    }
    printf("Value is removed!\n");     
}

void driveRemoveAtPos(node** head){
    if (*head == NULL){
        printf("The list is empty. Not able to remove\n");
        return;
    }
    int pos;
    printf("Enter the position: ");
    scanf("%d", &pos);

    if (pos <= 0 || pos > size(*head)){
        printf("Invalid position or out of range\n");
        return;
    }
    removeAtPos(head, pos);
    printf("Value is removed!\n");
}

void driveDeallocate(node** head){
    if (*head == NULL){
        printf("The List is already empty!\n");
        return;
    }

    deallocate(head);
    printf("The List is cleared!\n");
}

void driveReversList2(node** head){
    if (*head == NULL || (*head)->next == NULL){
        printf("The list is empty or one element. Not able to reverse\n");
        return;
    }    
    reversList2(head);
    printf("List is revered.\n");
}

void dirveShiftLeft(node** head){
    if (*head == NULL || (*head)->next == NULL){
        printf("The list is empty or one element. Not able to shift left.\n");
        return;
    } 
    shiftLeft(head);
    printf("List is left shifted\n");
}

void dirveShiftRight(node** head){
    if (*head == NULL || (*head)->next == NULL){
        printf("The list is empty or one element. Not able to shift right.\n");
        return;
    } 
    shiftRight(head);
    printf("List is right shifted\n");
}

void driveSortAsc(node* head){
    if (head == NULL || head->next == NULL){
        printf("The list is empty or one element. Not able to sort.\n");
        return;
    }
    sortAsc(head);
    printf("List is sorted.\n");
}

void driveHeadAddr(node* head){
    if (head == NULL){
        printf("The list is empty. Address NULL.\n");
        return;
    }
    printf("\nHead Address: %p", head);
}

