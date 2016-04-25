//
//  ANSObject.c
//  LCHW
//
//  Created by Nikola Andriiev on 22.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include "ANSObject.h"

#include <assert.h>
#include <stdio.h>

#pragma mark -
#pragma mark Public Implementation 

void *__ANSObjectCreate(size_t objectSize, ANSObjectDeallocator dealocator) {
    assert(0 != objectSize);
    assert(NULL != dealocator);
    ANSObject *object = calloc(1, objectSize );
    
    assert(NULL != object);
    
    object->_retainCount = 1;
    object->_deallocatorFunctionPointer = dealocator;
    
    return object; //return pointer; 
}

void __ANSObjectDeallocate(void *object) {
    if (NULL != object) {
        free(object);
    }
}

uint64_t ANSObjectGetRetainCount(void *object) {
    return object ? ((ANSObject*)object)->_retainCount : 0;
}


void *ANSObjectRetain(void *object) {
    if (NULL != object) {
        ((ANSObject*)object)->_retainCount++;
    }
    
    return object;
}

void ANSObjectReleace(void *object) {
    if (NULL != object) {
       ((ANSObject*)object)->_retainCount--;
        if (0 == ((ANSObject*)object)->_retainCount) {
            ANSObjectDeallocator dealocator = ((ANSObject*)object)->_deallocatorFunctionPointer;
            dealocator(object);
        }
    }
}
