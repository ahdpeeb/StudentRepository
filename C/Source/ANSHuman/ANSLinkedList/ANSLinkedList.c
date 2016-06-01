//
//  ANSLinkedList.c
//  LCHW
//
//  Created by Nikola Andriiev on 30.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include <assert.h>
#include <string.h>

#include "ANSLinkedList.h"
#include "ANSLinkedListPrivate.h"
#include "ANSLinkedListEnumerator.h"
#include "ANSLinkedListEnumeratorPrivate.h"
#include "ANSLinkedListNode.h"

#pragma mark -
#pragma mark Private Declaration

typedef struct ANSNodeToObjectContext ANSNodeToObjectContext;
struct ANSNodeToObjectContext {
    ANSLinkedListNodeComparisonFunction compare;
    ANSLinkedListContext *context;
};

static
void ANSLinkedListCountAddValue(ANSLinkedList *list, short value);

static
void ANSLinkedListSetCount(ANSLinkedList *list, uint64_t value);

static
ANSLinkedListContext *ANSLinkedListCreateContextFindNodeWithObject(ANSLinkedList *list, void *object);

#pragma mark -
#pragma mark Public Implementation 

ANSLinkedListEnumerator *ANSLinkedListCreateEnumeratorFromList(ANSLinkedList *list) {
    return ANSLinkedListEnumeratorCreateWithList(list);
}

void __ANSLinkedListDeallocate(void *object) {
    ANSLinkedListSetCount(object, 0);
    
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
    ANSLinkedListContext *context = ANSLinkedListCreateContextFindNodeWithObject(list,object);
        if (context->previousNode) {
        previousObject = ANSLinkedListNodeGetObject(context->previousNode);
    }
    
    free(context);
    
    return previousObject;
}

void *ANSLinkedListGetNextObject(ANSLinkedList *list, void *object) {
    assert(list);
    
    void *nextObject = NULL;
    ANSLinkedListContext *context = ANSLinkedListCreateContextFindNodeWithObject(list,object);
    if (context->node) {
        ANSLinkedListNode *nextNode = ANSLinkedListNodeGetNextNode(context->node);
        if (nextNode) {
            nextObject = ANSLinkedListNodeGetObject(nextNode);
        }
    }
    
    free(context);
    
    return nextObject;

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
    assert(list);
    
    ANSLinkedListContext context = *ANSLinkedListContextCreateWithObject(object);
    ANSLinkedListNode *node = ANSLinkedListFindNodeWithContext(list, ANSLinkedListNodeContainsObject, &context);
    if (node) {
        ANSLinkedListNode *previousNode = context.previousNode;
        ANSLinkedListNode *nexNode =  ANSLinkedListNodeGetNextNode(node);
        ANSLinkedListNodeSetNextNode(previousNode, nexNode);
        ANSLinkedListCountAddValue(list, -1);
    }
}

void ANSLinkedListRemoveAllObjects(ANSLinkedList *list) {
    assert(list);
    
    ANSLinkedListSetCount(list, 0);
}

bool ANSLinkedListContainsObject(ANSLinkedList *list, void *object) {
    assert(list);
    
    ANSLinkedListContext *context = ANSLinkedListContextCreateWithObject(object);
    ANSLinkedListNode *node = ANSLinkedListFindNodeWithContext(list, ANSLinkedListNodeContainsObject, context);
    bool value = node;
    
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
    
    ANSRetainSetter(list, _head, head);
}

ANSLinkedListNode *ANSLinkedListGetHead(ANSLinkedList *list) {
    assert(list);
    
    return list->_head;
}

void ANSLinkedListSetMutationsCount(ANSLinkedList *list, uint64_t count) {
    ANSAssignSetter(list, _mutationsCount, count);
}

void ANSLinkedListMutationsCountAddValue(ANSLinkedList *list, uint64_t value) {
    uint64_t count = ANSLinkedListGetMutationsCount(list);
    ANSLinkedListSetMutationsCount(list, count += value);
}

bool ANSNodeToObjectBringeFunction(ANSLinkedListNode *node, ANSLinkedListContext *context) {
    ANSNodeToObjectContext *wrapperContext = (void *)context;
    
    return wrapperContext->compare(ANSLinkedListNodeGetObject(node), wrapperContext->context);
}

ANSLinkedListNode *ANSLinkedListFindNodeWithContext(ANSLinkedList *list,
                                                   ANSLinkedListNodeComparisonFunction comparator,
                                                   void *context) {
    ANSLinkedListNode *result = NULL;
    if (list) {
        ANSLinkedListEnumerator *enumerator = ANSLinkedListEnumeratorCreateWithList(list);
        while (ANSLinkedListEnumeratorIsValid(enumerator) && ANSLinkedListEnumeratorGetNextObject(enumerator))  {
            ANSLinkedListNode *node = ANSLinkedListEnumeratorGetNode(enumerator);
            
            if (ANSLinkedListNodeContainsObject(node, context)) {
                result = node;
                break;
            }
        }
        
        ANSObjectRelease(enumerator);
    }
    
    return result;
}

ANSLinkedListNode *ANSLinkedListFindObjectWithContext(ANSLinkedList *list,
                                                      ANSLinkedListNodeComparisonFunction comparator,
                                                      void *context) {
    ANSNodeToObjectContext wrapperContext;
    memset(&wrapperContext, 0, sizeof(wrapperContext));
    wrapperContext.compare = comparator;
    wrapperContext.context = context;
    
    return ANSLinkedListFindNodeWithContext(list, ANSNodeToObjectBringeFunction, &wrapperContext);
}

// comparator function
bool ANSLinkedListNodeContainsObject(ANSLinkedListNode *node, ANSLinkedListContext *context) {
    bool result = false;
    if (node) {
        
        context->previousNode = context->node;
        context->node = node;
        
        void *object = ANSLinkedListNodeGetObject(node);
        if (context->object == object) {
            result = true;
        }
    }
    
    return result;
}

ANSLinkedListContext* ANSLinkedListContextCreateWithObject(void *object) {
    ANSLinkedListContext *context = calloc(1, sizeof(*context));
    context->object = object;

    return context;
}

ANSLinkedListContext *ANSLinkedListCreateContextFindNodeWithObject(ANSLinkedList *list, void *object) {
    ANSLinkedListContext *context = ANSLinkedListContextCreateWithObject(object);
   __unused ANSLinkedListNode *node = ANSLinkedListFindNodeWithContext(list, ANSLinkedListNodeContainsObject, context);

    return context;
}
