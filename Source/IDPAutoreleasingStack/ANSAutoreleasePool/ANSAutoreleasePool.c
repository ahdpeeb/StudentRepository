//
//  ANSAutoreleasePool.c
//  LCHW
//
//  Created by Nikola Andriiev on 19.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include <assert.h>

#include "ANSAutoreleasePool.h"

#pragma mark -
#pragma mark Privat Declaration

static const size_t kANSSizeOfStack = 512;

static
void ANSAutoreleasePoolSetCount(ANSAutoreleasePool *pool, uint64_t count);

static
uint64_t ANSAutoreleasePoolGetCount(ANSAutoreleasePool *pool);

static
void ANSAutoreleasePoolCountAddValue(ANSAutoreleasePool *pool, short value);

static
ANSLinkedList *ANSAutoreleasePoolGetList(ANSAutoreleasePool *pool);

static
void ANSAutoreleasePoolSetList(ANSAutoreleasePool *pool);

#pragma mark -
#pragma mark Publick Implementation

void __ANSAutoreleasePoolDeallocate(ANSAutoreleasePool *pool) {
    ANSAutoreleasePoolCleanUpPool(pool);
    
    ANSObjectRelease(pool->_list);
    __ANSObjectDeallocate(pool);
}

ANSAutoreleasePool *ANSAutoreleasePoolCreatePool(void) {
    ANSAutoreleasePool *pool = ANSObjectCreateWithType(ANSAutoreleasePool);
    
    return pool;
}

void ANSAutoreleasePoolAddObject(ANSAutoreleasePool *pool, void *object) {
    assert(pool);
    
//    if() {
//        ANSAutoreleasingStack stack
//    }
}

void ANSAutoreleasePoolCleanUpPool(ANSAutoreleasePool *pool);

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

void ANSAutoreleasePoolSetList(ANSAutoreleasePool *pool) {
    
    ANSLinkedList *list = ANSObjectCreateWithType(ANSLinkedList);
    ANSRetainSetter(pool, _list, list);
}

ANSLinkedList *ANSAutoreleasePoolGetList(ANSAutoreleasePool *pool) {
    return pool->_list;
}

