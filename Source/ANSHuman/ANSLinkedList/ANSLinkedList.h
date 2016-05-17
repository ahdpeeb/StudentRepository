//
//  ANSLinkedList.h
//  LCHW
//
//  Created by Nikola Andriiev on 30.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#ifndef ANSLinkedList_h
#define ANSLinkedList_h

#include <stdbool.h>
#include "ANSObject.h"

typedef struct ANSLinkedListEnumerator ANSLinkedListEnumerator;
typedef struct ANSLinkedListNode ANSLinkedListNode;

typedef struct ANSLinkedList ANSLinkedList;
struct ANSLinkedList {
    ANSObject _super;
    
    ANSLinkedListNode *_head;
    uint64_t _mutationsCount;
    uint64_t count;
};

ANSLinkedListEnumerator *ANSLinkedListCreateEnumeratorFromList(ANSLinkedList *list);

//return pointer of firt object(any type of object)
extern
void *ANSLinkedListGetFirstObject(ANSLinkedList *list);

extern 
void ANSLinkedListRemoveFirstObject(ANSLinkedList *list);

//return pointer of previous object(any type of object)
extern
void *ANSLinkedListGetObjectBeforeObject(ANSLinkedList *list, void *object);

extern 
bool ANSLinkedListIsEmpty(ANSLinkedList *list);

extern
void ANSLinkedListAddObject(ANSLinkedList *list, void *object);

extern
void ANSLinkedListRemoveObject(ANSLinkedList *list, void *object);

extern
void ANSLinkedListRemoveAllObjects(ANSLinkedList *list);

extern
bool ANSLinkedListContainsObject(ANSLinkedList *list, void *object);

extern
uint64_t ANSLinkedListGetCount(ANSLinkedList *list);

extern
void __ANSLinkedListDeallocate(void *object);

#endif /* ANSLinkedList_h */
