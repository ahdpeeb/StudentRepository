//
//  ANSLinkedList.c
//  LCHW
//
//  Created by Nikola Andriiev on 30.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include <assert.h>

#include "ANSLinkedList.h"
#include "ANSLinkedLisetPrivate.h"
#include "ANSLinkedListNode.h"
#include "ANSLinkedListEnumerator.h"
#include "ANSLinkedListEnumeratorPrivate.h"

#pragma mark -
#pragma mark Private Declaration

static
void ANSLinkedListCountAddValue(ANSLinkedList *list, short value);

static
void ANSLinkedListSetCount(ANSLinkedList *list, uint64_t value);

#pragma mark -
#pragma mark Public Implementation 

ANSLinkedListEnumerator *ANSLinkedListEnumeratorFromList(ANSLinkedList *list) {
    return ANSLinkedListEnumeratorCreateWithList(list);
}

void __ANSLinkedListDeallocate(void *object) {
    ANSLinkedListSetHead(object, NULL);
    
    __ANSObjectDeallocate(object);
}

void *ANSLinkedListGetFirstObject(ANSLinkedList *list) {
    ANSLinkedListNode *node = ANSLinkedListGetHead(list);
    
    return ANSLinkedListNodeGetObject(node);
}

void ANSLinkedListRemoveFirstObject(ANSLinkedList *list) {
    ANSLinkedListNode *firstNode = ANSLinkedListGetHead(list);
    ANSLinkedListNode *nextNode = ANSLinkedListNodeGetNextNode(firstNode);
    
    ANSLinkedListSetHead(list, nextNode);
    ANSLinkedListCountAddValue(list, -1);
}

void *ANSLinkedListGetObjectBeforeObject(ANSLinkedList *list, void *object) {
    assert(list);
    
    void *previousObject = NULL;
    if (ANSLinkedListContainsObject(list, object)) {   // check for truth (if false)
        ANSLinkedListNode *previousNode = NULL;
        ANSLinkedListNode *currentNode = ANSLinkedListGetHead(list);
        
        do {
            void* currentObject = ANSLinkedListNodeGetObject(currentNode);
            if (object == currentObject) {
                return previousObject;
            }
            
            previousNode = currentNode;
            currentNode = ANSLinkedListNodeGetNextNode(currentNode);
            previousObject = ANSLinkedListNodeGetObject(previousNode);
        } while (currentNode);
    }
    
    return previousObject;
}

bool ANSLinkedListIsEmpty(ANSLinkedList *list) {
    assert(list);
    
    return !ANSLinkedListGetHead(list); // if it has one object+ => if (object = NULL) = truth
}

void ANSLinkedListAddObject(ANSLinkedList *list, void *object) {
    assert(list);
    
    ANSLinkedListNode *newNode = ANSLinkedListNodeCreateWithObject(object);
    
    ANSLinkedListNode *headNode = ANSLinkedListGetHead(list);
    ANSLinkedListNodeSetNextNode(newNode, headNode);
    ANSLinkedListSetHead(list, newNode);
    ANSLinkedListCountAddValue(list, 1);
    
    ANSObjectRelease(headNode);
}


void ANSLinkedListRemoveObject(ANSLinkedList *list, void *object) {
    ANSLinkedListNode *previousNode = NULL;
    ANSLinkedListNode *currentNode = ANSLinkedListGetHead(list);
    ANSLinkedListNode *nextNode = ANSLinkedListNodeGetNextNode(currentNode);
    while (currentNode) {
        void *currentObject = ANSLinkedListNodeGetObject(currentNode);
        if (object == currentObject) {
            if (previousNode) {
                ANSLinkedListNodeSetNextNode(previousNode, nextNode);
            } else {
                ANSLinkedListSetHead(list, nextNode);
            }
            
            ANSLinkedListCountAddValue(list, -1);
            break;
        }
        
        previousNode = currentNode;
        currentNode = nextNode;
        nextNode = ANSLinkedListNodeGetNextNode(currentNode);
    }
}

void ANSLinkedListRemoveAllObjects(ANSLinkedList *list) {
    assert(list);
    
    ANSLinkedListSetHead(list, NULL);
    ANSLinkedListSetCount(list, 0);
}

bool ANSLinkedListContainsObject(ANSLinkedList *list, void *object) {
    assert(list);
    
    ANSLinkedListContext *context = calloc(1, sizeof(context));
    context->object = object;
    ANSLinkedListNode *node = ANSLinkedListGetNodeWithContext(list, ANSLinkedListNodeContainsObject, context);
    bool value = node;
    free(context);
    
    return value;
}

uint64_t ANSLinkedListGetCount(ANSLinkedList *list) {
    assert(list);
    
    return list->count;
}

uint64_t ANSLinkedListGetMutationsCount(ANSLinkedList *list) {
    assert(list);
    
    return list->_mutationsCount;
}

#pragma mark -
#pragma mark Private Implementation

void ANSLinkedListSetCount(ANSLinkedList *list, uint64_t value) {
    assert(list);
    
    if (0 == value) {
        ANSLinkedListSetHead(list, NULL);
    }
    
    list->count = value;
    ANSLinkedListMutationsCountAddValue(list, +1);
}

void ANSLinkedListCountAddValue(ANSLinkedList *list, short value) {
    assert(list);
    
    list->count += value;
}

void ANSLinkedListSetHead(ANSLinkedList *list, ANSLinkedListNode *head) {
    assert(list);
    
    if (ANSLinkedListGetHead(list) != head) {
        ANSObjectRelease(list->_head);
        list->_head = head;
        
        ANSObjectRetain(head);
    }
}

ANSLinkedListNode *ANSLinkedListGetHead(ANSLinkedList *list) {
    assert(list);
    
    return list->_head;
}

void ANSLinkedListSetMutationsCount(ANSLinkedList *list, uint64_t count) {
    ANSAssignSetter(list, _mutationsCount, count);
}

void ANSLinkedListMutationsCountAddValue(ANSLinkedList *list, uint64_t value) {
    list->_mutationsCount += value;
}

ANSLinkedListNode *ANSLinkedListGetNodeWithContext(ANSLinkedList *list,
                                                   ANSLinkedListNodeComparisonFunction comparator,
                                                   ANSLinkedListContext *context) {
    ANSLinkedListNode *result = NULL;
    if (list) {
        ANSLinkedListEnumerator *enumerator = ANSLinkedListEnumeratorCreateWithList(list);
        while (ANSLinkedListEnumeratorIsValid(enumerator) && ANSLinkedListEnumeratorGetNextObject(enumerator))  {
            ANSLinkedListNode *node = ANSLinkedListEnumeratorGetNode(enumerator);
            context->node = node;
            
            if (comparator) {
                result = node;
                break;
            }
            
            context->previousNode = node;
        }
        
        
        ANSObjectRelease(enumerator);
    }
    
    return result;
}
// comparator function
bool ANSLinkedListNodeContainsObject(ANSLinkedListNode *node, ANSLinkedListContext *context) {
    bool result = false;
    if (node) {
       return result = context->object == ANSLinkedListNodeGetObject(node);
    }
    
    return result;
}

