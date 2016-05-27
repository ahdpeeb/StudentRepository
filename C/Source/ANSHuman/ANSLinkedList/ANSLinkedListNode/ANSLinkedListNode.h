//
//  ANSLinkedListNode.h
//  LCHW
//
//  Created by Nikola Andriiev on 30.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#ifndef ANSLinkedListNode_h
#define ANSLinkedListNode_h

#include <stdio.h>
#include "ANSObject.h"

typedef struct ANSLinkedListNode ANSLinkedListNode;
struct ANSLinkedListNode {
    ANSObject _super;
     
    ANSLinkedListNode *_nextNode;
    void *_object;
};

extern
ANSLinkedListNode *ANSLinkedListNodeCreateWithObject(void *object);

extern
ANSLinkedListNode *ANSLinkedListNodeGetNextNode(ANSLinkedListNode *node);

extern
void ANSLinkedListNodeSetNextNode(ANSLinkedListNode *node, ANSLinkedListNode *nextNode);

extern
void *ANSLinkedListNodeGetObject(ANSLinkedListNode *node);

extern
void ANSLinkedListNodeSetObject(ANSLinkedListNode *node, void *object);

extern
void __ANSLinkedListNodeDeallocate(void *object);

#endif /* ANSLinkedListNode_h */
