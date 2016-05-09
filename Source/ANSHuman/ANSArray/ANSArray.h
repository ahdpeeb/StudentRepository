//
//  ANSArray.h
//  LCHW
//
//  Created by Nikola Andriiev on 03.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#ifndef ANSArray_h
#define ANSArray_h

#include <stdbool.h>

#include "ANSObject.h"

static const uint64_t kANSNotFound = UINT64_MAX;

typedef struct {
    ANSObject _super;
    void **_data;
    uint16_t _count;
    uint16_t _capacity;
} ANSArray;

extern
void *ANSArrayCreateWithCapacity(uint64_t capacity);

//returns index of added object. Otherwise kANSNotFound
extern
void ANSArrayAddObject(ANSArray *array, void *object);

extern
uint64_t ANSArrayGetCount(ANSArray *array);

extern
bool ANSArrayContainsObject(ANSArray *array, void *object);

extern
uint64_t ANSArrayGetIndexOfObject(ANSArray *array, void *object);

extern
void *ANSArrayGetObjectAtIndex(ANSArray *array, uint64_t index);

extern
void ANSArrayRemoveAllObjects(ANSArray *array);

extern
void __ANSArrayDeallocate(void *objext);

#endif /* ANSArray_h */
