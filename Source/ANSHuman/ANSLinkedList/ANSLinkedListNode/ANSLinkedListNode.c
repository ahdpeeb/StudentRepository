//
//  ANSLinkedListNode.c
//  LCHW
//
//  Created by Nikola Andriiev on 30.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include "ANSLinkedListNode.h"

#pragma mark -
#pragma mark Public Implementation

void __ANSLinkedListNodeDeallocate(void *object) {
    ANSLinkedListNodeSetObject(object, NULL);
    ANSLinkedListNodeSetNextNode(object, NULL);
    
    __ANSObjectDeallocate(object);
}

ANSLinkedListNode *ANSLinkedListNodeCreateWithObject(ANSObject *object) {
    ANSLinkedListNode *result = ANSObjectCreateWithType(ANSLinkedListNode);
    ANSLinkedListNodeSetObject(result, object);
        
    return result;
}

ANSLinkedListNode *ANSLinkedListNodeGetNextNode(ANSLinkedListNode *node) {
    return NULL != node ? node->_nextNode : NULL;
}

void ANSLinkedListNodeSetNextNode(ANSLinkedListNode *node, ANSLinkedListNode *NexNode) {
    if (NULL != node && (node->_nextNode != node)) {
        ANSObjectRetain(NexNode);
        ANSObjectRelease(node->_nextNode);
        
        node->_nextNode = NexNode;
       
        }
}
// смотреть Session 11 - 1. Autorelease pool concept, linked list implementation
ANSObject *ANSLinkedListNodeGetObject(ANSLinkedListNode *node) {
    return NULL;
}

void ANSLinkedListNodeSetObject(ANSLinkedListNode *node, ANSObject *object) {

}