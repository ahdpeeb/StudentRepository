//
//  ANSLinkedListEnumerator.c
//  LCHW
//
//  Created by Nikola Andriiev on 12.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
#include <assert.h>

#include "ANSLinkedListEnumerator.h"
#include "ANSLinkedListEnumeratorPrivate.h"
#include "ANSLinkedList.h"
#include "ANSLinkedLisetPrivate.h"
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
void ANSLinkedListEnumeratorSetMutationsCount(ANSLinkedListEnumerator *enumerator, uint64_t mutationsCount);

static
uint64_t ANSLinkedListEnumeratorGetMutationsCount(ANSLinkedListEnumerator *enumerator);

static
void ANSLinkedListEnumeratorSetValid(ANSLinkedListEnumerator *enumerator, bool isValid);

static
bool ANSLinkedListEnumeratorMutationsValidate(ANSLinkedListEnumerator *enumerator);

#pragma mark -
#pragma mark Public implementation 
 
void __ANSLinkedListEnumeratorDeallocate(void* object) {
    ANSLinkedListEnumeratorSetNode(object, NULL);
    ANSLinkedListEnumeratorSetList(object, NULL);
    
    __ANSObjectDeallocate(object);
}

ANSLinkedListEnumerator *ANSLinkedListEnumeratorCreateWithList(ANSLinkedList *list) {
    assert(list);
    
    ANSLinkedListEnumerator * enumerator = ANSObjectCreateWithType(ANSLinkedListEnumerator);
    ANSLinkedListEnumeratorSetList(enumerator, list);
    ANSLinkedListEnumeratorSetMutationsCount(enumerator, ANSLinkedListGetMutationsCount(list));
    ANSLinkedListEnumeratorSetValid(enumerator, true);
    
    return enumerator;
}

void *ANSLinkedListEnumeratorGetNextObject(ANSLinkedListEnumerator *enumerator) {
    assert(enumerator);
    
    if (ANSLinkedListEnumeratorMutationsValidate(enumerator)) {
        ANSLinkedListNode *node = ANSLinkedListEnumeratorGetNode(enumerator);
        ANSLinkedList *list = ANSLinkedListEnumeratorGetList(enumerator);
        if (!node) {
            node = ANSLinkedListGetHead(list);
        } else {
            node = ANSLinkedListNodeGetNextNode(node);
        }
        
        ANSLinkedListEnumeratorSetNode(enumerator, node);
        if(!node) {
            ANSLinkedListEnumeratorSetValid(enumerator, false);
            
            return NULL;
        }
        
        return ANSLinkedListNodeGetObject(node);
    }
        
    return NULL;
}

bool ANSLinkedListEnumeratorIsValid(ANSLinkedListEnumerator *enumerator) {
    assert(enumerator);
    
    return enumerator->_isValid;
}

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

void ANSLinkedListEnumeratorSetMutationsCount(ANSLinkedListEnumerator *enumerator, uint64_t mutationsCount){
    ANSAssignSetter(enumerator, _mutationsCount, mutationsCount);
}

uint64_t ANSLinkedListEnumeratorGetMutationsCount(ANSLinkedListEnumerator *enumerator) {
    assert(enumerator);
    
    return enumerator->_mutationsCount;
}

void ANSLinkedListEnumeratorSetValid(ANSLinkedListEnumerator *enumerator, bool isValid) {
    ANSAssignSetter(enumerator, _isValid, isValid);
}

bool ANSLinkedListEnumeratorMutationsValidate(ANSLinkedListEnumerator *enumerator) {
    if (ANSLinkedListEnumeratorIsValid(enumerator)) {
        ANSLinkedList *list = ANSLinkedListEnumeratorGetList(enumerator);
        assert(ANSLinkedListGetMutationsCount(list) == ANSLinkedListEnumeratorGetMutationsCount(enumerator));
        
        return true;
    }
    
    return false;
}
