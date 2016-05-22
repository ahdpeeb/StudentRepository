//
//  ANSAutoreleasePool.c
//  LCHW
//
//  Created by Nikola Andriiev on 19.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include <assert.h>

#include "ANSAutoreleasePool.h"
#include "ANSObject.h"

#pragma mark -
#pragma mark Privat Declaration

static const size_t kANSSizeOfStack = 16;

static ANSAutoreleasePool *__pool = NULL;

static
void ANSAutoreleasePoolSetCount(ANSAutoreleasePool *pool, uint64_t count);

static
uint64_t ANSAutoreleasePoolGetCount(ANSAutoreleasePool *pool);

static
void ANSAutoreleasePoolCountAddValue(ANSAutoreleasePool *pool, short value);

static
ANSLinkedList *ANSAutoreleasePoolGetList(ANSAutoreleasePool *pool);

static  //set Linkedlist to pool and retain in/
void ANSAutoreleasePoolIninList(ANSAutoreleasePool *pool);

static // create ANSAutoreleasingStack and add to poop->_list.
ANSAutoreleasingStack *ANSAutoreleasePoolAddStackToList(ANSAutoreleasePool *pool);

static //return pointer to HEAD stack
ANSAutoreleasingStack *ANSAutoreleasePoolGetHeadStack(ANSAutoreleasePool *pool);

#pragma mark -
#pragma mark Publick Implementation

void __ANSAutoreleasePoolDeallocate(ANSAutoreleasePool *pool) {
     ANSAutoreleasePoolDrain(pool);
    
    __ANSObjectDeallocate(pool);
}

ANSAutoreleasePool *ANSAutoreleasePoolCreate(void) {
    if (!__pool) {
    __pool = ANSObjectCreateWithType(ANSAutoreleasePool);
    ANSAutoreleasePoolIninList(__pool);
    ANSAutoreleasePoolAddStackToList(__pool);
    }
    
    ANSAutoreleasePoolAddObject(__pool, NULL);

    return __pool;
}

void ANSAutoreleasePoolAddObject(ANSAutoreleasePool *pool, void *object) {
    assert(pool);
    
    ANSAutoreleasingStack *stack = ANSAutoreleasePoolGetHeadStack(pool);
    assert(stack);
    
    bool value = ANSAutoreleasingStackIsFull(stack);
    if (value) {
        stack = ANSAutoreleasePoolAddStackToList(pool);
    }
    
    ANSAutoreleasingStackPushObject(stack, object);
    ANSAutoreleasePoolCountAddValue(pool, +1);
}

void ANSAutoreleasePoolDrain() {
    ANSAutoreleasePool *pool = ANSAutoreleasePoolGetPool();
    ANSLinkedList *list = ANSAutoreleasePoolGetList(pool);
    assert(pool || list);
    
    ANSAutoreleasingStackType type = ANSAutoreleasingStackTypeNull;
        do {
            ANSAutoreleasingStack *stack = ANSAutoreleasePoolGetHeadStack(pool);
            type = ANSAutoreleasingStackPopObjectsUntilNull(stack);
        } while (type == ANSAutoreleasingStackTypeObject && ANSAutoreleasePoolGetHeadStack(pool));

        ANSLinkedListRemoveFirstObject(list);
}

#pragma mark -
#pragma mark Privat Implementation

void ANSAutoreleasePoolSetCount(ANSAutoreleasePool *pool, uint64_t count) {
    ANSAssignSetter(pool, _count, count);
}

uint64_t ANSAutoreleasePoolGetCount(ANSAutoreleasePool *pool) {
    assert(pool);
    
    return pool->_count;
}

void ANSAutoreleasePoolCountAddValue(ANSAutoreleasePool *pool, short value) {
    uint64_t count = ANSAutoreleasePoolGetCount(pool);
    ANSAutoreleasePoolSetCount(pool, count += value);
}

void ANSAutoreleasePoolIninList(ANSAutoreleasePool *pool) {
    assert(pool);
    
    ANSLinkedList *list = ANSObjectCreateWithType(ANSLinkedList);
    ANSRetainSetter(pool, _list, list)
    
    ANSObjectRelease(list);
}

ANSLinkedList *ANSAutoreleasePoolGetList(ANSAutoreleasePool *pool) {
    return pool->_list;
}


ANSAutoreleasingStack *ANSAutoreleasePoolAddStackToList (ANSAutoreleasePool *pool) {
    assert(pool);
    
    ANSLinkedList *list = ANSAutoreleasePoolGetList(pool);
    ANSAutoreleasingStack *stack = ANSAutoreleasingStackCreateWithSize(kANSSizeOfStack);
    ANSLinkedListAddObject(list, stack);
    
    ANSObjectRelease(stack);
    return stack;
}

ANSAutoreleasingStack *ANSAutoreleasePoolGetHeadStack(ANSAutoreleasePool *pool) {
   return (ANSAutoreleasingStack *)ANSLinkedListGetFirstObject(ANSAutoreleasePoolGetList(pool));
}
    // test
ANSAutoreleasingStack *ANSAutoreleasePoolGetNextStack(ANSAutoreleasePool *pool) {
//    ANSLinkedList *list = ANSAutoreleasePoolGetList(pool);
    return NULL;
}

ANSAutoreleasePool* ANSAutoreleasePoolGetPool(void) {
    return __pool;
}
