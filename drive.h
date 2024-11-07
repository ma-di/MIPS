
#ifndef DRIVE_H
#define DRIVE_H

// #include<stdlib.h>
#include"node.h"
// #include"drive.c"
// #include"list.h"


void meny();
void drivePrintSize(node*);
void drivePrintList (node*);

void driveInsertEnd(node**);

void driveInsertAtPosition(node** );
void driveRemoveValue(node** head);
void driveRemoveAtPos(node** head);
void driveDeallocate(node**);
node* reversList(node* head);
void driveReversList2(node** head);
void dirveShiftLeft(node** head);
void dirveShiftRight(node** head);
void driveSortAsc(node* head);
void driveHeadAddr(node* head);



#endif /* DRIVE_H */