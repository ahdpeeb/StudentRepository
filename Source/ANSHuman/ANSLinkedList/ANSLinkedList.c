//
//  ANSLinkedList.c
//  LCHW
//
//  Created by Nikola Andriiev on 30.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include <assert.h>

#include "ANSLinkedList.h"
#include "ANSLinkedListNode.h"

#pragma mark -
#pragma mark Private Declaration

static
void ANSLinkedListCountAddValue(ANSLinkedList *list, uint8_t value);

static
void ANSLinkedListSetHead(ANSLinkedList *list, ANSLinkedListNode *head);

static
ANSLinkedListNode *ANSLinkedListGetHead(ANSLinkedList *list);

#pragma mark -
#pragma mark Private Implementation

static
void ANSLinkedListCountAddValue(ANSLinkedList *list, uint8_t value) {
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

#pragma mark -
#pragma mark Public Implementation 

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
}

void *ANSLinkedListGetObjectBeforeObject(ANSLinkedList *list, void *object) {
    assert(list);
    
    void *previousObject = NULL;
    if (!ANSLinkedListIsEmpty(list)) {   // check for truth (if false)
        ANSLinkedListNode *currentNode = ANSLinkedListGetHead(list);
        ANSLinkedListNode *nextNode = ANSLinkedListNodeGetNextNode(currentNode);
        void *currentObject = ANSLinkedListNodeGetObject(currentNode);
        do {
            if (object == currentObject) {
                
                return previousObject;
            }
            
            previousObject = ANSLinkedListNodeGetObject(currentObject);
            ANSLinkedListNodeSetNextNode(currentObject, nextNode);
        } while (NULL != nextNode);
    }
    
    return NULL;
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
    ANSLinkedListNode *currentNode = ANSLinkedListGetHead(list);
    ANSLinkedListNode *nextNode = ANSLinkedListNodeGetNextNode(currentNode);
    while (NULL != currentNode) {
        void *currentObject = ANSLinkedListNodeGetObject(currentNode);
        if (object == currentObject) {
            ANSLinkedListNodeSetNextNode(currentNode, nextNode);
            ANSLinkedListCountAddValue(list, -1);
            
            break;
        }
        currentNode = ANSLinkedListNodeGetNextNode(currentNode);
    }
}

void ANSLinkedListRemoveAllObjects(ANSLinkedList *list) {
    assert(list);
    
    ANSLinkedListSetHead(list, NULL);
    list->count = 0;
}

extern
bool ANSLinkedListContainsObject(ANSLinkedList *list, void *object) {
    assert(list);
    
    ANSLinkedListNode *currentNode = ANSLinkedListGetHead(list);
    ANSLinkedListNode *nexNode = ANSLinkedListNodeGetNextNode(currentNode);
    while (NULL != currentNode) {
        void *currentObject = ANSLinkedListNodeGetObject(currentNode);
        if (object == currentObject) {
            return true;
        }
        
        currentNode = ANSLinkedListNodeGetNextNode(nexNode);
    }
    
    return false;
}

extern
uint64_t ANSLinkedListGetCount(ANSLinkedList *list) {
    assert(list);
    
    return list->count;
}









