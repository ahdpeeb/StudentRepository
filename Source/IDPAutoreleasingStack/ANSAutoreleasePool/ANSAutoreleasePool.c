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

static ANSAutoreleasePool *__pool = NULL;

static
void ANSAutoreleasePoolSetCount(ANSAutoreleasePool *pool, uint64_t count);

static
uint64_t ANSAutoreleasePoolGetCount(ANSAutoreleasePool *pool);

static
void ANSAutoreleasePoolCountAddValue(ANSAutoreleasePool *pool, short value);

static
ANSLinkedList *ANSAutoreleasePoolGetList(ANSAutoreleasePool *pool);

static
void ANSAutoreleasePoolSetValid(ANSAutoreleasePool *pool, bool valid);

static  //set Linkedlist to pool and retain in/
void ANSAutoreleasePoolInitList(ANSAutoreleasePool *pool);

static // create ANSAutoreleasingStack and add to poop->_list.
ANSAutoreleasingStack *ANSAutoreleasePoolAddStackToList(ANSAutoreleasePool *pool);

static //return pointer to HEAD stack
ANSAutoreleasingStack *ANSAutoreleasePoolGetHeadStack(ANSAutoreleasePool *pool);

static  //return next stack after current stack
ANSAutoreleasingStack *ANSAutoreleasePoolGetNextStack(ANSAutoreleasePool *pool, ANSAutoreleasingStack *stack);

static //  return tail stack
ANSAutoreleasingStack *ANSAutoreleasePoolGetTailStack(void);

ANSAutoreleasingStack *ANSAutoreleasePoolIfEmptyRemoveStackGetNextStack(void);

#pragma mark -
#pragma mark Publick Implementation

void __ANSAutoreleasePoolDeallocate(ANSAutoreleasePool *pool) {
     ANSAutoreleasePoolDrain();
    
    __ANSObjectDeallocate(pool);
}

ANSAutoreleasePool *ANSAutoreleasePoolCreate(void) {
    if (!__pool) {
        __pool = ANSObjectCreateWithType(ANSAutoreleasePool);
        ANSAutoreleasePoolInitList(__pool);
        ANSAutoreleasePoolAddStackToList(__pool);
    }
    
    ANSAutoreleasePoolAddObject(__pool, NULL);
    ANSAutoreleasePoolSetValid(__pool, true);
    
    return __pool;
}

ANSAutoreleasePool* ANSAutoreleasePoolGetPool(void) {
    return __pool;
}

void ANSAutoreleasePoolAddObject(ANSAutoreleasePool *pool, void *object) {
    assert(pool);
    
    ANSAutoreleasingStack *stack = ANSAutoreleasePoolGetHeadStack(pool);
    assert(stack);
    
    if (ANSAutoreleasingStackIsFull(stack)) { // if true - add new stack
        stack = ANSAutoreleasePoolAddStackToList(pool);
    }
    
    if (object) {
        assert(ANSAutoreleasePoolGetValid());
    }
    
    ANSAutoreleasingStackPushObject(stack, object);
    ANSAutoreleasePoolCountAddValue(pool, +1);
}

void ANSAutoreleasePoolDrain() {
    ANSAutoreleasingStackType type = ANSAutoreleasingStackTypeNull;
    
    do {
        ANSAutoreleasingStack *stack = ANSAutoreleasePoolIfEmptyRemoveStackGetNextStack();
        type = ANSAutoreleasingStackPopObjectsUntilNull(stack);
    } while (type == ANSAutoreleasingStackTypeObject);
    
    if (ANSAutoreleasingStackIsEmpty(ANSAutoreleasePoolGetTailStack())) {
        ANSAutoreleasePoolSetValid(ANSAutoreleasePoolGetPool(), false);
    }
}

#pragma mark -
#pragma mark Privat Implementation

#pragma mark -
#pragma mark Accessors

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

void ANSAutoreleasePoolInitList(ANSAutoreleasePool *pool) {
    assert(pool);
    
    ANSLinkedList *list = ANSObjectCreateWithType(ANSLinkedList);
    ANSRetainSetter(pool, _list, list)
    
    ANSObjectRelease(list);
}

ANSLinkedList *ANSAutoreleasePoolGetList(ANSAutoreleasePool *pool) {
    assert(pool);
    
    return pool->_list;
}

void ANSAutoreleasePoolSetValid(ANSAutoreleasePool *pool, bool valid) {
    ANSAssignSetter(pool, _valid, valid);
}

bool ANSAutoreleasePoolGetValid(void) {
    ANSAutoreleasePool *pool = ANSAutoreleasePoolGetPool();
    assert(pool);
    
    return pool->_valid;
}

#pragma mark -
#pragma mark Auxiliary

ANSAutoreleasingStack *ANSAutoreleasePoolAddStackToList (ANSAutoreleasePool *pool) {
    assert(pool);
    
    ANSLinkedList *list = ANSAutoreleasePoolGetList(pool);
    ANSAutoreleasingStack *stack = ANSAutoreleasingStackCreateWithSize(kANSSizeOfStack);
    ANSLinkedListAddObject(list, stack);
    
    ANSObjectRelease(stack);
    
    return stack;
}

ANSAutoreleasingStack *ANSAutoreleasePoolGetHeadStack(ANSAutoreleasePool *pool) {
   return ANSLinkedListGetFirstObject(ANSAutoreleasePoolGetList(pool));
}

ANSAutoreleasingStack *ANSAutoreleasePoolGetNextStack(ANSAutoreleasePool *pool, ANSAutoreleasingStack *stack) {
    return ANSLinkedListGetNextObject(ANSAutoreleasePoolGetList(pool), stack);

}
ANSAutoreleasingStack *ANSAutoreleasePoolGetTailStack(void) {
    ANSAutoreleasePool *pool = ANSAutoreleasePoolGetPool();
    ANSAutoreleasingStack *stack = ANSAutoreleasePoolGetHeadStack(pool);
    assert(pool && stack);
    
    ANSAutoreleasingStack *curentStack = NULL;
    while (stack) {
        curentStack = stack;
        stack = ANSAutoreleasePoolGetNextStack(pool, stack);
    }
        
    return curentStack;
}

ANSAutoreleasingStack *ANSAutoreleasePoolIfEmptyRemoveStackGetNextStack(void) {
    ANSAutoreleasePool *pool = ANSAutoreleasePoolGetPool();
    ANSLinkedList *list = ANSAutoreleasePoolGetList(pool);
    ANSAutoreleasingStack *stack = ANSAutoreleasePoolGetHeadStack(pool);
    assert(pool && list && stack);
    
    if (ANSAutoreleasingStackIsEmpty(stack)) {
        if (1 != ANSLinkedListGetCount(list)) {
            ANSLinkedListRemoveFirstObject(list);
            stack = ANSAutoreleasePoolGetHeadStack(pool);
        }
    }
    
    return stack;
}

