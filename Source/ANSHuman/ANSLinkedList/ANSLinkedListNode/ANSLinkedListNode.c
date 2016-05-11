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

void ANSLinkedListNodeSetNextNode(ANSLinkedListNode *node, ANSLinkedListNode *NexNode) {
    assert(node);
    
    if  (node->_nextNode != node) {
        ANSObjectRelease(node->_nextNode);
        node->_nextNode = NexNode;
        ANSObjectRetain(NexNode);
        }
}

void *ANSLinkedListNodeGetObject(ANSLinkedListNode *node) {
    assert(node);
    
    return  node->_object;
}

void ANSLinkedListNodeSetObject(ANSLinkedListNode *node, void *object) {
    assert(node && object);
    assert(node != object);
    
    if (node->_object != object) {
        ANSObjectRelease(node->_object);
        node->_object = object;
        ANSObjectRetain(object);
    }

}