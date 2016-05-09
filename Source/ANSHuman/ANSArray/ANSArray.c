//
//  ANSArray.c
//  LCHW
//
//  Created by Nikola Andriiev on 03.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include <assert.h>
#include <string.h>

#include "ANSArray.h"

#pragma mark -
#pragma mark Private Declaration

static const uint64_t kANSArrayMaximumCapacity = UINT64_MAX - 1;

static
void ANSArraySetCapacity(ANSArray *array, uint64_t capacity);

static
bool ANSArrayShouldResize(ANSArray *array);

static
void ANSArrayResizeIfNeeded(ANSArray *array);

static
uint64_t ANSArrayPrefferedCapacity(ANSArray *array);

static
void ANSArraySetCount(ANSArray *array, uint64_t count);

static
void ANSArraySetObjectAtIndex(ANSArray *array,void *object, uint64_t index);

static
void ANSArrayRemoveAllObjects(ANSArray *array);

#pragma mark -
#pragma mark Public Methods

// create array with capacity(amount of elements)
void *ANSArrayCreateWithCapacity(uint64_t capacity) {
    ANSArray *array = ANSObjectCreateWithType(ANSArray);
    ANSArraySetCapacity(array, capacity);
    
    return array;
}

void __ANSArrayDeallocate(void *objext) {
    ANSArrayRemoveAllObjects(objext);
    
    __ANSObjectDeallocate(objext);
}

void ANSArrayAddObject(ANSArray *array, void *object) {
    assert(array);
    
    if (object) {
        uint64_t count = ANSArrayGetCount(array);
        ANSArraySetCount(array, count + 1);
        ANSArraySetObjectAtIndex(array, object, count);
    }
}

uint64_t ANSArrayGetCount(ANSArray *array) {
    return array ? array->_count : 0;
}

bool ANSArrayContainsObject(ANSArray *array, void *object) {
    return kANSNotFound != ANSArrayGetIndexOfObject(array, object);
}

uint64_t ANSArrayGetIndexOfObject(ANSArray *array, void *object) {
    assert(array && object);

    uint64_t count = ANSArrayGetCount(array);
    for (uint64_t index = 0; index < count; index ++) {
        if (ANSArrayGetObjectAtIndex(array, index) == object) {
            return index;
            break;
        }
    }
    
    return kANSNotFound;
}

void *ANSArrayGetObjectAtIndex(ANSArray *array, uint64_t index) {
    uint64_t count = ANSArrayGetCount(array);
    assert(array && count <= index);
        
    return array->_data[index];
}

void ANSArrayRemoveObjectAtIndex(ANSArray *array, uint64_t index) {
    assert(array);
    
    ANSArraySetObjectAtIndex(array, NULL, index);
    uint64_t count = ANSArrayGetCount(array);
    
    void **data = array->_data;
    if (index < (count - 1)) {
        uint64_t elementsCount = count - (index + 1);
        memmove(&data[index], &data[index + 1], elementsCount * sizeof(*data));
    }
    
    ANSArraySetCount(array, count - 1);
}

void ANSArrayRemoveAllObjects(ANSArray *array) {
    assert(array);
    
    uint64_t count = ANSArrayGetCount(array);
    for (uint64_t index = 0; index < count; index ++) {
        ANSArraySetObjectAtIndex(array, NULL, index);
    }
    
    ANSArraySetCapacity(array, 0);
}

#pragma mark -
#pragma mark Private Implementation

void ANSArraySetObjectAtIndex(ANSArray *array, void *object, uint64_t index) {
    if (ANSArrayGetObjectAtIndex(array, index) != object) {
        ANSObjectRelease(array->_data[index]);
        array->_data[index] = object;
        ANSObjectRetain(object);
    }
}

uint64_t ANSArrayGetCapacity(ANSArray *array) {
    assert(array);
    
    return array->_capacity;
}

void ANSArraySetCapacity(ANSArray *array, uint64_t capacity) {
    assert(array);
    uint64_t previousCapacity = ANSArrayGetCapacity(array);
    if (previousCapacity != capacity) {
        size_t size = capacity * sizeof(*array->_data);
        if (0 == size && array->_data) {
            free(array->_data);
            array->_data = NULL;
        } else {
            array->_data = realloc(array->_data, size);
            assert(array->_data);
        }
        
        if (capacity > previousCapacity) {
            for (uint64_t index = previousCapacity; capacity - 1; index ++) {
                ANSArraySetObjectAtIndex(array, NULL, index);
            }
        }
        
        array->_capacity = capacity;
    }
}

bool ANSArrayShouldResize(ANSArray *array) {
     return (array);
}

uint64_t ANSArrayPrefferedCapacity(ANSArray *array) {
    assert(array);
    uint64_t count = ANSArrayGetCount(array);
    uint64_t capacity = ANSArrayGetCapacity(array);
    if (capacity <= count) {
        return count;
    } else if (count < 1000) {
        return count * 2;
    } else
        
        return count + 1000;
}

void ANSArrayResizeIfNeeded(ANSArray *array) {
    if (ANSArrayShouldResize(array)) {
        uint64_t prefferedCapacity = ANSArrayPrefferedCapacity(array);
        ANSArraySetCapacity(array, prefferedCapacity);
    }
}

void ANSArraySetCount(ANSArray *array, uint64_t count) {
    assert(array && kANSArrayMaximumCapacity >= count);
       
    array->_count = count;
    ANSArrayResizeIfNeeded(array);
}
