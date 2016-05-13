//
//  ANSLinkedListEnumerator.h
//  LCHW
//
//  Created by Nikola Andriiev on 12.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.


#ifndef ANSLinkedListEnumerator_h
#define ANSLinkedListEnumerator_h

#include <stdbool.h>

#include "ANSObject.h"

typedef struct ANSLinkedList ANSLinkedList;
typedef struct ANSLinkedListNode ANSLinkedListNode;

typedef struct ANSLinkedListEnumerator ANSLinkedListEnumerator;
struct ANSLinkedListEnumerator {
    ANSObject _super;
    
    ANSLinkedList *_list;
    ANSLinkedListNode *_node;
    uint64_t _mutationsCount;
    bool _isValid;
};

extern
ANSLinkedListEnumerator *ANSLinkedListEnumeratorCreateWithList(ANSLinkedList *list);

extern
ANSLinkedListNode *ANSLinkedListEnumeratorGetNextNode(ANSLinkedListEnumerator *enumerator);

extern
bool ANSLinkedListEnumeratorIsValid(ANSLinkedListEnumerator *enumerator);

extern
void __ANSLinkedListEnumeratorDeallocate(void* object);

#endif /* ANSLinkedListEnumerator_h */
