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
void ANSAutoreleasePoolCountAddValue(short value);

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

static //return previous stack after current stack
ANSAutoreleasingStack *ANSAutoreleasePoolGetPrevStack(ANSAutoreleasePool *pool, ANSAutoreleasingStack *stack);

static //  return tail stack
ANSAutoreleasingStack *ANSAutoreleasePoolGetTailStack(ANSAutoreleasePool *pool);

static //resize pool
void ANSAutoreleasePoolResize(void);

void ANSAutoreleasePoolDrainAllObject(void);
    //get first not empty stack
ANSAutoreleasingStack *ANSAutoreleasePoolGetFirstNotEmptyStack(void);

#pragma mark -
#pragma mark Publick Implementation

void __ANSAutoreleasePoolDeallocate(ANSAutoreleasePool *pool) {
     ANSAutoreleasePoolDrainAllObject();
    
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
        assert(ANSAutoreleasePoolGetValid(ANSAutoreleasePoolGetPool()));
    }
    
    ANSAutoreleasingStackPushObject(stack, object);
    ANSAutoreleasePoolCountAddValue(+ 1);
}

void ANSAutoreleasePoolDrain() {
    ANSAutoreleasingStackType type = ANSAutoreleasingStackTypeNull;
    ANSAutoreleasingStack *stack = ANSAutoreleasePoolGetFirstNotEmptyStack();
    do {
        type = ANSAutoreleasingStackPopObjectsUntilNull(stack);
        stack = ANSAutoreleasePoolGetNextStack(ANSAutoreleasePoolGetPool(), stack);
    } while (type == ANSAutoreleasingStackTypeObject);
    
    
    if (ANSAutoreleasingStackIsEmpty(ANSAutoreleasePoolGetTailStack(ANSAutoreleasePoolGetPool()))) {
        ANSAutoreleasePoolSetValid(ANSAutoreleasePoolGetPool(), false);
    }
    
    ANSAutoreleasePoolResize(); // testing
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

void ANSAutoreleasePoolCountAddValue(short value) {
    ANSAutoreleasePool *pool = ANSAutoreleasePoolGetPool();
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

bool ANSAutoreleasePoolGetValid(ANSAutoreleasePool *pool) {
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
    
ANSAutoreleasingStack *ANSAutoreleasePoolGetPrevStack(ANSAutoreleasePool *pool, ANSAutoreleasingStack *stack) {
    return ANSLinkedListGetObjectBeforeObject(ANSAutoreleasePoolGetList(pool), stack);
}
    
ANSAutoreleasingStack *ANSAutoreleasePoolGetTailStack(ANSAutoreleasePool *pool) {
    ANSAutoreleasingStack *stack = ANSAutoreleasePoolGetHeadStack(pool);
    assert(pool && stack);
    
    ANSAutoreleasingStack *curentStack = NULL;
    while (stack) {
        curentStack = stack;
        stack = ANSAutoreleasePoolGetNextStack(pool, stack);
    }
        
    return curentStack;
}

void ANSAutoreleasePoolResize(void) { // testing
    ANSAutoreleasePool *pool = ANSAutoreleasePoolGetPool();
    ANSLinkedList *list = ANSAutoreleasePoolGetList(pool);
    ANSAutoreleasingStack *head = ANSAutoreleasePoolGetHeadStack(pool); //head
    ANSAutoreleasingStack *tail = ANSAutoreleasePoolGetTailStack(pool); // tail test
    ANSAutoreleasingStack *notEmpty = ANSAutoreleasePoolGetFirstNotEmptyStack(); // first not empty
    
    assert(pool && list && head);
    
    ANSAutoreleasingStack *previousStack = ANSAutoreleasePoolGetPrevStack(pool, notEmpty);
    if (previousStack) {
        while (head != previousStack) {
            ANSLinkedListRemoveFirstObject(list);
            head = ANSAutoreleasePoolGetHeadStack(pool);
        }
    }
}

void ANSAutoreleasePoolDrainAllObject(void) {
    while (ANSAutoreleasePoolGetValid(ANSAutoreleasePoolGetPool())) {
        ANSAutoreleasePoolDrain();
    }
}

void ANSAutoreleasePoolWipeOut(void) {
    __ANSAutoreleasePoolDeallocate(ANSAutoreleasePoolGetPool());
}

ANSAutoreleasingStack *ANSAutoreleasePoolGetFirstNotEmptyStack(void) {
    ANSAutoreleasePool *pool = ANSAutoreleasePoolGetPool();
    ANSAutoreleasingStack *head = ANSAutoreleasePoolGetHeadStack(pool);
    assert(pool && head);
    while (ANSAutoreleasingStackIsEmpty(head)) {
        head = ANSAutoreleasePoolGetNextStack(pool, head);
    }
    
    return head;
}
