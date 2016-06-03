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
#include "ANSAutoreleasingStack.h"

#pragma mark -
#pragma mark Private Declaration

static
void ANSLinkedListCountAddValue(ANSLinkedList *list, short value);

static
void ANSLinkedListSetCount(ANSLinkedList *list, uint64_t value);

static
bool ANSLinkedListTransitionNodeToObject(ANSLinkedListNode *node, void *context);

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

ANSLinkedListContext *ANSLinkedListContextCreateWithObject(void *object) {
    ANSLinkedListContext *context = calloc(1, sizeof(*context));
    context->object = object;
    
    return context;
}

ANSLinkedListContext *ANSLinkedListCreateContextFindNodeWithObject(ANSLinkedList *list, void *object) {
    ANSLinkedListContext *context = ANSLinkedListContextCreateWithObject(object);
    __unused ANSLinkedListNode *node = ANSLinkedListFindNodeWithContext(list, ANSLinkedListNodeContainsObject, context);
    
    return context;
}

//_____________________________________________________________________________
ANSLinkedListNode *ANSLinkedListFindNodeWithContext(ANSLinkedList *list,
                                                   ANSLinkedListNodeComparisonFunction comparator,
                                                   void *context)
{
    ANSLinkedListNode *result = NULL;
    if (list) {
        ANSLinkedListEnumerator *enumerator = ANSLinkedListEnumeratorCreateWithList(list);
        while (ANSLinkedListEnumeratorIsValid(enumerator) && ANSLinkedListEnumeratorGetNextObject(enumerator))  {
            ANSLinkedListNode *node = ANSLinkedListEnumeratorGetNode(enumerator);
            
            if (comparator(node, context)) {
                result = node;
                break;
            }
        }
        
        ANSObjectRelease(enumerator);
    }
    
    return result;
}

// node comparator function
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

// transition node compara to object compare
bool ANSLinkedListTransitionNodeToObject(ANSLinkedListNode *node, void *context) {
    ANSNodeToObjectContext *wrapperContext = context;
    
    return wrapperContext->objectComporator(ANSLinkedListNodeGetObject(node), wrapperContext->context);
}

void *ANSLinkedListFindObjectWithContext(ANSLinkedList *list, // list
                                         ANSLinkedListObjectComparisonFunction comparator, //comporator
                                         void *context) // array
{
    ANSNodeToObjectContext wrapperContext;
    memset(&wrapperContext, 0, sizeof(wrapperContext)); //
    wrapperContext.context = context;
    wrapperContext.objectComporator = comparator;
    
    
    ANSLinkedListNode *node = ANSLinkedListFindNodeWithContext(list, ANSLinkedListTransitionNodeToObject, &wrapperContext.context);
    
    return ANSLinkedListNodeGetObject(node); //должно веруть первый пустой стек перед полным.
}

bool ANSLinkedListSortFunction(void *object, void *context) {
    bool resul = false;
    if (ANSAutoreleasingStackIsEmpty(object)) {
        (ANSArrayAddObject(context, object));
    }
    
    return resul;
}

ANSArray* ANSLinkedListSortObjectsDependsOnComporator(ANSLinkedList *list,
                                                      ANSLinkedListObjectComparisonFunction comparator)
{
    ANSArray *array = (ANSArrayCreateWithCapacity(512));
    ANSLinkedListFindObjectWithContext(list, comparator, array);
    
    return array;
}


