// #include"node.h"
// #include"list.h"
#include"drive.h"
#include<stdio.h>
#include<stdlib.h>
// #include"drive.c"

int main(){
    node* head = NULL;

    int val;
    do
    {        
        meny();
        scanf("%d", &val);
        printf("\n------------- Answer -------------\n\n");
        switch (val)
        {
            case 0: driveDeallocate(&head);
                break;        
            case 1: drivePrintList(head);
                break;
            case 2: drivePrintSize(head);
                break;
            case 3: driveInsertEnd(&head);
                break;
            case 4: driveInsertAtPosition(&head);
                break;
            case 5: driveRemoveValue(&head);
                break;
            case 6: driveRemoveAtPos(&head);
                break;
            case 7: driveDeallocate(&head);
                break;
            case 8: driveReversList2(&head);
                break;
            case 9: dirveShiftLeft(&head);
                break;
            case 10: dirveShiftRight(&head);
                break;
            case 11: driveSortAsc(head);
                break;
            case 12: driveHeadAddr(head);
                break;
            
            default: printf("\nInvalid choice!\n");
                break;
        }
        printf("----------------------------------\n\n");
        /* code */
    } while (val != 0);

    return 0;
}