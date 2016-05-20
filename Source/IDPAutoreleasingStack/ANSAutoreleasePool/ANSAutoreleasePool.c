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

static const size_t kANSSizeOfStack = 40;

static
void ANSAutoreleasePoolSetCount(ANSAutoreleasePool *pool, uint64_t count);

static
uint64_t ANSAutoreleasePoolGetCount(ANSAutoreleasePool *pool);

static
void ANSAutoreleasePoolCountAddValue(ANSAutoreleasePool *pool, short value);

static
ANSLinkedList *ANSAutoreleasePoolGetList(ANSAutoreleasePool *pool);

static  //set Linkedlist to pool and retain in/
void ANSAutoreleasePoolSetList(ANSAutoreleasePool *pool);

static // create ANSAutoreleasingStack and add to poop->_list.
ANSAutoreleasingStack *ANSAutoreleasePoolNewStackAddToList(ANSAutoreleasePool *pool);

//static //return pointer to HEAD stack
//ANSAutoreleasingStack *ANSAutoreleasePoolGetHeadStack(ANSAutoreleasePool *pool);

#pragma mark -
#pragma mark Publick Implementation

void __ANSAutoreleasePoolDeallocate(ANSAutoreleasePool *pool) {
    ANSAutoreleasePoolCleanUpPool(pool); // полностью очищает пул.
    
    __ANSObjectDeallocate(pool);
}

ANSAutoreleasePool *ANSAutoreleasePoolCreatePool(void) {
    ANSAutoreleasePool *pool = ANSObjectCreateWithType(ANSAutoreleasePool);
    ANSAutoreleasePoolSetList(pool);
    
    ANSAutoreleasingStack *stack = ANSAutoreleasePoolNewStackAddToList(pool);
    ANSAutoreleasingStackPushObject(stack, NULL);

    return pool;
}

void ANSAutoreleasePoolAddObject(ANSAutoreleasePool *pool, void *object) {
    assert(pool);
    
    ANSAutoreleasingStack *stack = ANSAutoreleasePoolGetHeadStack(pool);
    assert(stack);
    bool status = ANSAutoreleasingStackIsFull(stack);
    if (status) {
            stack = ANSAutoreleasePoolNewStackAddToList(pool);
    }
    
    ANSAutoreleasingStackPushObject(stack, object);
    ANSAutoreleasePoolCountAddValue(pool, +1);
}

void ANSAutoreleasePoolCleanUpPool(ANSAutoreleasePool *pool) {
    //implementation
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
    //установить лист
void ANSAutoreleasePoolSetList(ANSAutoreleasePool *pool) {
    assert(pool);
    
    ANSLinkedList *list = ANSObjectCreateWithType(ANSLinkedList);
    ANSRetainSetter(pool, _list, list)
    
    ANSObjectRelease(list);
}

ANSLinkedList *ANSAutoreleasePoolGetList(ANSAutoreleasePool *pool) {
    return pool->_list;
}


ANSAutoreleasingStack *ANSAutoreleasePoolNewStackAddToList(ANSAutoreleasePool *pool) {
    assert(pool);
    
    ANSLinkedList *list = ANSAutoreleasePoolGetList(pool);
    ANSAutoreleasingStack *stack = ANSAutoreleasingStackCreateWithSize(kANSSizeOfStack);
    ANSLinkedListAddObject(list, stack);
    
    return stack;
}

ANSAutoreleasingStack *ANSAutoreleasePoolGetHeadStack(ANSAutoreleasePool *pool) {
   return (ANSAutoreleasingStack *)ANSLinkedListGetFirstObject(ANSAutoreleasePoolGetList(pool));
}