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
    assert(node);
    
    return node->_nextNode;
}

void ANSLinkedListNodeSetNextNode(ANSLinkedListNode *node, ANSLinkedListNode *nextNode) {
    assert(node);
    
    ANSRetainSetter(node, _nextNode, nextNode);
}

void *ANSLinkedListNodeGetObject(ANSLinkedListNode *node) {
    assert(node);
    
    return  node->_object;
}

void ANSLinkedListNodeSetObject(ANSLinkedListNode *node, void *object) {
    assert(node); //object can be NULL
    
    ANSRetainSetter(node, _object, object);
}
