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
void ANSLinkedListCountAddValue(ANSLinkedList *list, short value);

static
void ANSLinkedListSetHead(ANSLinkedList *list, ANSLinkedListNode *head);

static
ANSLinkedListNode *ANSLinkedListGetHead(ANSLinkedList *list);

#pragma mark -
#pragma mark Private Implementation

static
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
    while (NULL != currentNode) {
        
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
    list->count = 0;
}

bool ANSLinkedListContainsObject(ANSLinkedList *list, void *object) {
    assert(list);
    
    ANSLinkedListNode *currentNode = ANSLinkedListGetHead(list);
    while (NULL != currentNode) {
      
        void *currentObject = ANSLinkedListNodeGetObject(currentNode);
        if (object == currentObject) {
            return true;
        }
        
        currentNode = ANSLinkedListNodeGetNextNode(currentNode);
    }
    
    return false;
}

uint64_t ANSLinkedListGetCount(ANSLinkedList *list) {
    assert(list);
    
    return list->count;
}









