//
//  IDPAutoreleasingStack.c
//  LCHW
//
//  Created by Nikola Andriiev on 17.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
#include <assert.h>
#include <string.h>

#include "IDPAutoreleasingStack.h"

#pragma mark -
#pragma mark Accessors declaration

void ANSAutoreleasingStackSetSize(ANSAutoreleasingStack *stack, size_t size);

size_t ANSAutoreleasingStackGetSize(ANSAutoreleasingStack *stack);

void ANSAutoreleasingStackSetHead(ANSAutoreleasingStack *stack, void *head);

void *ANSAutoreleasingStackGetHead(ANSAutoreleasingStack *stack);

void **ANSAutoreleasingStackGetData(ANSAutoreleasingStack *stack);

#pragma mark -
#pragma mark Public implementation

void __ANSAutoreleasingStackDeallocate(void *object) {
    ANSAutoreleasingStackSetSize(object, 0);
    
    __ANSObjectDeallocate(object);
}

ANSAutoreleasingStack *ANSAutoreleasingStackCreateWithSize(size_t size) {
    assert(!size);
    
    ANSAutoreleasingStack *stack = ANSObjectCreateWithType(ANSAutoreleasingStack);
    ANSAutoreleasingStackSetSize(stack, size);
    ANSAutoreleasingStackSetHead(stack, ANSAutoreleasingStackGetData(stack));
    
    return stack;
}

bool ANSAutoreleasingStackIsEmpty(ANSAutoreleasingStack *stack) {
    assert(stack);
    
    return ANSAutoreleasingStackGetHead(stack) == ANSAutoreleasingStackGetData(stack);
}

bool ANSAutoreleasingStackIsFull(ANSAutoreleasingStack *stack) {
    void **data = ANSAutoreleasingStackGetData(stack); //array of pointers
    void *head = ANSAutoreleasingStackGetHead(stack);
    size_t size = ANSAutoreleasingStackGetSize(stack);
    
    return data[size / sizeof(*data) - 1] <= head; // last element in array <= head
}

void ANSAutoreleasingStackPushObject(ANSAutoreleasingStack *stack, void *object) {
    assert(stack);
    
    void **headObject = ANSAutoreleasingStackGetHead(stack) + 1;
    headObject = object;
    ANSAutoreleasingStackSetHead(stack, headObject);
}

ANSAutoreleasingStackType ANSAutoreleasingStackPopObject(ANSAutoreleasingStack *stack) {
    assert(stack || !ANSAutoreleasingStackIsEmpty(stack));
    
    ANSAutoreleasingStackType type;
    void **head = ANSAutoreleasingStackGetHead(stack);
    void *object = *head;
    head -= 1;
    ANSAutoreleasingStackSetHead(stack, head);
    type = (object) ? ANSAutoreleasingStackTypeObject : ANSAutoreleasingStackTypeNull;
    ANSObjectRelease(object);
    
    return type;
}

void ANSAutoreleasingStackPopAllObjects(ANSAutoreleasingStack *stack) {
    assert(stack);
    ANSAutoreleasingStackType type;
    if (!ANSAutoreleasingStackIsEmpty(stack)) {
        do {
            type = ANSAutoreleasingStackPopObject(stack);
        } while (type);
    }
}

#pragma mark -
#pragma mark Accessors declaration

void ANSAutoreleasingStackSetSize(ANSAutoreleasingStack *stack, size_t size) {
    ANSAssignSetter(stack, _size, size)
    if (0 == size) {
        ANSAutoreleasingStackPopAllObjects(stack);
    }
    
    memset(stack->_data, 0, size);
}

size_t ANSAutoreleasingStackGetSize(ANSAutoreleasingStack *stack) {
    assert(stack);

    return stack->_size;
}

void ANSAutoreleasingStackSetHead(ANSAutoreleasingStack *stack, void *head) {
    ANSAssignSetter(stack, _head, head);
}

void *ANSAutoreleasingStackGetHead(ANSAutoreleasingStack *stack) {
    assert(stack);
    
    return stack->_head;
}

void **ANSAutoreleasingStackGetData(ANSAutoreleasingStack *stack) {
    assert(stack);
    
    return stack->_data;
}
