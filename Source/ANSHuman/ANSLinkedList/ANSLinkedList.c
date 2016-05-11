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
    
    void *result = NULL;
    // доделать
    // взять объект, у которого count - 1;
    return result;
}

bool ANSLinkedListIsEmpty(ANSLinkedList *list) {
    assert(list);
    
    return ANSLinkedListGetHead(list);
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
    //find node with object
}

extern
void ANSLinkedListRemoveAllObjects(ANSLinkedList *list) {
    assert(list);
    
    ANSLinkedListSetHead(list, NULL);
    list->count = 0;
}

extern
bool ANSLinkedListContainsObject(ANSLinkedList *list, void *object) {
    assert(list);
    
    bool result = false;
    //enumerate all nodes to find node with with object
    return result;
}

extern
uint64_t ANSLinkedListGetCount(ANSLinkedList *list) {
    assert(list);
    
    return list->count;
}









