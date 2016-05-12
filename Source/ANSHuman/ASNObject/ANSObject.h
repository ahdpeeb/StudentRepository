//
//  ANSObject.h
//  LCHW
//
//  Created by Nikola Andriiev on 22.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#ifndef ANSObject_h
#define ANSObject_h

#include <stdlib.h>

typedef void (*ANSObjectDeallocator)(void *);

typedef struct {
    uint64_t _retainCount;
    ANSObjectDeallocator _deallocatorFunctionPointer;
} ANSObject;

#define ANSObjectCreateWithType(type) \
    __ANSObjectCreate(sizeof(type), (ANSObjectDeallocator)__##type##Deallocate)

extern
void *__ANSObjectCreate(size_t objectSize, ANSObjectDeallocator dealocator);

extern
void __ANSObjectDeallocate(void *object);

extern
uint64_t ANSObjectGetRetainCount(void *object);

extern
void *ANSObjectRetain(void *object);

extern
void ANSObjectRelease(void *object);


#define ANSAssingSetter(object, ivar, newIvar) \
    assert(object); \
    object->ivar = newIvar;

#define ANSRetainSetter(object, ivar, newIvar) \
    assert(object); \
    if (object->ivar != newIvar) { \
        ANSObjectRelease(object->ivar); \
        object->ivar = newIvar; \
        ANSObjectRetain(newIvar); \
    }

#endif /* ANSObject_h */
