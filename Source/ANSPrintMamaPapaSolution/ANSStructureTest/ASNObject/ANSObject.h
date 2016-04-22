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

typedef void (*ANSObjectDeallocator)(void *object);

typedef struct {
    uint64_t _retainCount;
    ANSObjectDeallocator _deallocatorFunctionPointer;
    
} ANSObject;

extern
void *ANSObjectCreate(size_t objectSize, ANSObjectDeallocator dealocator);

extern
void __ANSObjectDeallocate(void *object);

extern
uint64_t ANSObjectGetRetainCount(void *object);

extern
void *ANSObjectRetain(void *object);

extern
void ANSObjectReleace(void *object);

#endif /* ANSObject_h */
