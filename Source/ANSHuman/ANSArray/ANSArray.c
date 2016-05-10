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
void ANSArrayCountAddValue(ANSArray *array, uint64_t count);

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
        ANSArrayCountAddValue(array, 1);
        uint64_t count = ANSArrayGetCount(array);
        ANSArraySetObjectAtIndex(array, object, count - 1);
        
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
        }
    }
    
    return kANSNotFound;
}

void *ANSArrayGetObjectAtIndex(ANSArray *array, uint64_t index) {
    uint64_t count = ANSArrayGetCount(array);
    assert(array && count >= index);
        
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
    
    ANSArrayCountAddValue (array, - 1);
}

void ANSArrayRemoveAllObjects(ANSArray *array) {
    assert(array);
    
    uint64_t count = ANSArrayGetCount(array);
    for (uint64_t index = 0; index < count; index ++) {
        ANSArraySetObjectAtIndex(array, NULL, index);
        ANSArrayCountAddValue (array, - 1);
    }
}

#pragma mark -
#pragma mark Private Implementation

void ANSArraySetObjectAtIndex(ANSArray *array, void *object, uint64_t index) {
    ANSObject *value = ANSArrayGetObjectAtIndex(array, index);
    if (value != object) {
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
            
            if (capacity > previousCapacity) {
                for (uint64_t index = previousCapacity; index < capacity - 1; index ++) {
                    array->_data[index] = NULL;
                }
            }
        }
        
        array->_capacity = capacity;
    }
}

bool ANSArrayShouldResize(ANSArray *array) {
    assert(array);
    return (ANSArrayGetCapacity(array) != ANSArrayPrefferedCapacity(array));
}

uint64_t ANSArrayPrefferedCapacity(ANSArray *array) {
    assert(array);
    
    uint64_t count = ANSArrayGetCount(array);
    uint64_t capacity = ANSArrayGetCapacity(array);
    if (capacity < count && capacity != count - 1) {
        return  count;
    }
    
    if (capacity > count * 2) {
        return 1 + count + count / 4;
    }

    return 1 + count + capacity;
}

void ANSArrayResizeIfNeeded(ANSArray *array) {
    if (ANSArrayShouldResize(array)) {
        uint64_t prefferedCapacity = ANSArrayPrefferedCapacity(array);
        ANSArraySetCapacity(array, prefferedCapacity);
    }
}

void ANSArrayCountAddValue(ANSArray *array, uint64_t count) {
    assert(array);
       
    array->_count += count;
    ANSArrayResizeIfNeeded(array);
}

void ANSArrayRemoveObject(ANSArray *array, void *object) {
    uint64_t index = ANSArrayGetIndexOfObject(array, object);
    ANSArraySetObjectAtIndex(array, object, index);
    ANSArrayCountAddValue(array, -1);
}
