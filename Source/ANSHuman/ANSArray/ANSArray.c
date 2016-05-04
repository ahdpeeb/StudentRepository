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

#pragma mark -
#pragma mark Public Methods

void *ANSArrayCreateWithCapacity(uint64_t capacity) {
    ANSArray *result = ANSObjectCreateWithType(ANSArray);
    ANSArraySetCapacity(result, capacity);
    
    return result;
}

void __ANSArrayDeallocate(void *objext) {
    ANSArrayRemoveAllObjects(objext);
    
    
    __ANSObjectDeallocate(objext);
}

void ANSArrayAddObject(ANSArray *array, void *object) {
    if (NULL != array && NULL != object) {
        uint64_t count = ANSArrayGetCount(array);
        
        ANSArraySetCount(array, count + 1);
        ANSArraySetObjectAtIndex(array, object, count);
    }
}

uint64_t ANSArrayGetCount(ANSArray *array) {
    return NULL != array ? array->_count : 0;
}

extern
bool ANSArrayContainsObject(ANSArray *array, void *object) {
    return kANSNotFound != ANSArrayGetIndexOfObject(array, object);
}

extern
uint64_t ANSArrayGetIndexOfObject(ANSArray *array, void *object) {
    if (NULL == array) {
        return 0;
    }
    
    if (NULL == object) {
        return kANSNotFound;
    }
    
    uint64_t result = kANSNotFound;
    uint64_t count = ANSArrayGetCount(array);
    for (uint64_t index = 0; index < count; index ++) {
        if (ANSArrayGetObjectAtIndex(array, index) == object) {
            result = index;
            break;
        }
    }
    
    return result;
}

void *ANSArrayGetObjectAtIndex(ANSArray *array, uint64_t index) {
    void *result = NULL;
    if (NULL != array) {
        
        assert(ANSArrayGetCount(array) > index);
        
        result = array ->_data[index];
    }
        return result;
}

void ANSArrayRemoveObjectAtIndex(ANSArray *array, uint64_t index) {
    if (NULL != array) {
        ANSArraySetObjectAtIndex(array, NULL, index);
        uint64_t count = ANSArrayGetCount(array);
        
        void **data = array->_data;
        if (index < (count - 1)) {
            uint64_t elementsCount = count - (index + 1);
            memmove(&data[index], &data[index + 1], elementsCount * sizeof(*data));
        }
        
        data[count - 1] = NULL;
        ANSArraySetCount(array, count - 1);
    }

}

void ANSArrayRemoveAllObjects(ANSArray *array) {
    if (NULL != array) {
        uint64_t count = ANSArrayGetCount(array);
        for (uint64_t index = 0; index < count; index ++) {
            ANSArraySetObjectAtIndex(array, NULL, index);
        }
        
        ANSArraySetCapacity(array, 0);
    }
}

#pragma mark -
#pragma mark Private Implementation

uint64_t ANSArrayGetCapacity(ANSArray *array) {
    return (NULL != array) ? array->_capacity : 0;
}

void ANSArraySetCapacity(ANSArray *array, uint64_t capacity) {
    if (NULL != array && array->_capacity != capacity) {
        assert(kANSArrayMaximumCapacity >= capacity);
        
        size_t size = capacity * sizeof(*array->_data);
        if (0 == size && NULL != array->_data) {
            free(array->_data);
            array->_data = NULL;
        } else {
            array->_data = realloc(array->_data, size);
            
            assert(NULL != array->_data);
        }
        
        if (capacity > array->_capacity) {
            void *startPointer = array->_data + array->_capacity;
            size_t numberOfBytes = (capacity - array->_capacity) * sizeof(*array->_data);
            memset(startPointer, 0, numberOfBytes);
        }
        
        array->_capacity = capacity;
    }
}

bool ANSArrayShouldResize(ANSArray *array) {
     return (NULL != array);
}

uint64_t ANSArrayPrefferedCapacity(ANSArray *array) {
    if (NULL != array) {
        uint64_t count = ANSArrayGetCount(array);
        uint64_t capacity = ANSArrayGetCapacity(array);
        if (count == capacity) {
            return capacity;
        }
        
        return capacity < count ? count : 2 * count;
    }
    
    return 0;
}

void ANSArrayResizeIfNeeded(ANSArray *array) {
    if (ANSArrayShouldResize(array)) {
        ANSArraySetCapacity(array, ANSArrayPrefferedCapacity(array));
    
    }
}

void ANSArraySetCount(ANSArray *array, uint64_t count) {
   if (NULL != array) {
       assert(kANSArrayMaximumCapacity >= count);
       
       array->_count = count;

       ANSArrayResizeIfNeeded(array);
    }
}

void ANSArraySetObjectAtIndex(ANSArray *array,void *object, uint64_t index) {
     // доделать
}
