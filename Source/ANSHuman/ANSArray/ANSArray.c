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

static
void ANSArraySetCapacity(ANSArray *array, uint64_t capacity);

static
bool ANSArrayShouldResize(ANSArray *array);

static
void ANSArrayResizeCapacity(ANSArray *array, uint64_t requiredCapacity);

static
void ANSArraySetCount(ANSArray *array, uint64_t count);

static
void ANSArraySetObjectAtIndex(ANSArray *array,void *object, uint64_t index);



#pragma mark -
#pragma mark Public Methods

extern
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
        if (true == ANSArrayShouldResize(array)) {
            ANSArrayResizeCapacity(array, count + 1);
        }
            
        ANSArraySetCount(array, count + 1);
        ANSArraySetObjectAtIndex(array, object, count);
    }
}

uint64_t ANSArrayGetCount(ANSArray *array) {
    return NULL != array ? array->_count : 0;
}

extern
bool ANSArrayContainsObject(ANSArray *array, void *object) {
    return ANSNotFound != ANSArrayGetIndexOfObject(array, object);
}

extern
uint64_t ANSArrayGetIndexOfObject(ANSArray *array, void *object) {
    if (NULL == array) {
        return 0;
    }
    
    if (NULL == object) {
        return ANSNotFound;
    }
    
    uint64_t result = ANSNotFound;
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
        if (index < (count - 1)) {
            uint64_t elementsCount = count - (index - 1);
            void **data = array->_data;
            memmove(data[index],data[index + 1], elementsCount);
        }
        
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

void ANSArraySetCapacity(ANSArray *array, uint64_t capacity) {
    // доделать
}

bool ANSArrayShouldResize(ANSArray *array) {
    return false;
}

void ANSArrayResizeCapacity(ANSArray *array, uint64_t requiredCapacity) {
        // доделать
}

void ANSArraySetCount(ANSArray *array, uint64_t count) {
   if (NULL != array) {
       array->_count = count;
    }
}

void ANSArraySetObjectAtIndex(ANSArray *array,void *object, uint64_t index) {
     // доделать
}
