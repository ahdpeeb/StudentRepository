//
//  ANSLinkedListEnumerator.c
//  LCHW
//
//  Created by Nikola Andriiev on 12.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
#include <assert.h>

#include "ANSLinkedListEnumerator.h"
#include "ANSLinkedList.h"
#include "ANSLinkedListNode.h"

#pragma mark -
#pragma mark Privat declaration

static
void ANSLinkedListEnumeratorSetList(ANSLinkedListEnumerator *enumerator, ANSLinkedList *list);

static
ANSLinkedList *ANSLinkedListEnumeratorGetList(ANSLinkedListEnumerator *enumerator);

static
void ANSLinkedListEnumeratorSetNode(ANSLinkedListEnumerator *enumerator, ANSLinkedListNode *node);

static
ANSLinkedListNode *ANSLinkedListEnumeratorGetNode(ANSLinkedListEnumerator *enumerator);

static
void ANSLinkedListEnumeratorSetMutationsCount(ANSLinkedListEnumerator *enumerator, uint64_t mutationCount);

static
uint64_t *ANSLinkedListEnumeratotGetMutationsCount(ANSLinkedListEnumerator *enumerator);

#pragma mark -
#pragma mark Privat implementation

void ANSLinkedListEnumeratorSetList(ANSLinkedListEnumerator *enumerator, ANSLinkedList *list) {
    ANSRetainSetter(enumerator, _list, list);
}

ANSLinkedList *ANSLinkedListEnumeratorGetList(ANSLinkedListEnumerator *enumerator) {
    assert(enumerator);
    
    return enumerator->_list;
}

void ANSLinkedListEnumeratorSetNode(ANSLinkedListEnumerator *enumerator, ANSLinkedListNode *node) {
    ANSRetainSetter(enumerator, _node, node);
}

ANSLinkedListNode *ANSLinkedListEnumeratorGetNode(ANSLinkedListEnumerator *enumerator) {
    assert(enumerator);
    
    return enumerator->_node;
}

void ANSLinkedListEnumeratorSetMutationsCount(ANSLinkedListEnumerator *enumerator, uint64_t mutationCount){
    ANSAssingSetter(enumerator, _mutationCount, mutationCount);
}

uint64_t *ANSLinkedListEnumeratotGetMutationsCount(ANSLinkedListEnumerator *enumerator) {
    return 0;
}

#pragma mark -
#pragma mark Public implementation 

extern
void __ANSLinkedListEnumeratorDeallocate(void* object) {
    ANSLinkedListEnumeratorSetNode(object, NULL);
    ANSLinkedListEnumeratorSetList(object, NULL);
    
    __ANSObjectDeallocate(object);
}

extern
ANSLinkedListEnumerator *ANSLinkedListEnumeratorCreateWithList(ANSLinkedList *list) {
    ANSLinkedListEnumerator * enumeratot = ANSObjectCreateWithType(ANSLinkedListEnumerator);
    ANSLinkedListEnumeratorSetList(enumeratot, list);
    ANSLinkedListEnumeratorSetMutationsCount(enumeratot, list->_mutationCount);
    
    return enumeratot;
}

ANSLinkedListNode *ANSLinkedListEnumeratorGetNextNode(ANSLinkedListEnumerator *enumerator) {
    assert(enumerator);
    //NOTFinished
    
    return 0;
}

bool ANSLinkedListEnumeratorIsValid(ANSLinkedListEnumerator *enumerator) {
    //NOTFinished
    return 0;
}


