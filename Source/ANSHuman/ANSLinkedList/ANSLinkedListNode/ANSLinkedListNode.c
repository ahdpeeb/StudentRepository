//
//  ANSLinkedListNode.c
//  LCHW
//
//  Created by Nikola Andriiev on 30.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
#include <assert.h>

#include "ANSLinkedListNode.h"

#pragma mark -
#pragma mark Public Implementation

void __ANSLinkedListNodeDeallocate(void *object) {
    ANSLinkedListNodeSetObject(object, NULL);
    ANSLinkedListNodeSetNextNode(object, NULL);
    
    __ANSObjectDeallocate(object);
}

ANSLinkedListNode *ANSLinkedListNodeCreateWithObject(void *object) {
    ANSLinkedListNode *result = ANSObjectCreateWithType(ANSLinkedListNode);
    ANSLinkedListNodeSetObject(result, object);
        
    return result;
}

ANSLinkedListNode *ANSLinkedListNodeGetNextNode(ANSLinkedListNode *node) {
    return node ? node->_nextNode : NULL;
}

void ANSLinkedListNodeSetNextNode(ANSLinkedListNode *node, ANSLinkedListNode *nextNode) {
    assert(node);
    
    if (node->_nextNode != node) {
        ANSObjectRetain(nextNode);
        ANSObjectRelease(node->_nextNode);
        node->_nextNode = nextNode;
        }
}

void *ANSLinkedListNodeGetObject(ANSLinkedListNode *node) {
    assert(node);
    
    return  node->_object;
}

void ANSLinkedListNodeSetObject(ANSLinkedListNode *node, void *object) {
    assert(node); //object can be NULL
    
    if (node->_object != object) {
        ANSObjectRetain(object);
        ANSObjectRelease(node->_object);
        node->_object = object;
    }

}