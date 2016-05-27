//
//  ANSAutoreleasingStack.c
//  LCHW
//
//  Created by Nikola Andriiev on 17.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "ANSAutoreleasingStack.h"

#pragma mark -
#pragma mark Accessors declaration

void ANSAutoreleasingStackSetSize(ANSAutoreleasingStack *stack, size_t size);

size_t ANSAutoreleasingStackGetSize(ANSAutoreleasingStack *stack);

void ANSAutoreleasingStackSetHead(ANSAutoreleasingStack *stack, void *head);

void **ANSAutoreleasingStackGetHead(ANSAutoreleasingStack *stack);

void **ANSAutoreleasingStackGetData(ANSAutoreleasingStack *stack);

#pragma mark -
#pragma mark Public implementation

void __ANSAutoreleasingStackDeallocate(void *object) {
    ANSAutoreleasingStackSetSize(object, 0);
    
    __ANSObjectDeallocate(object);
}

ANSAutoreleasingStack *ANSAutoreleasingStackCreateWithSize(size_t size) {
    assert(size);
    
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
    void **data = ANSAutoreleasingStackGetData(stack);
    size_t size = ANSAutoreleasingStackGetSize(stack);
    void **head = ANSAutoreleasingStackGetHead(stack);
    void **lastObject = &data[size / sizeof(*data)];
    bool value = lastObject == head;
    return value;
}

void ANSAutoreleasingStackPushObject(ANSAutoreleasingStack *stack, void *object) {
    assert(stack && !ANSAutoreleasingStackIsFull(stack));
    void **nextHead = ANSAutoreleasingStackGetHead(stack) + 1;
    *nextHead = object;
    ANSAutoreleasingStackSetHead(stack, nextHead);
}

ANSAutoreleasingStackType ANSAutoreleasingStackPopObject(ANSAutoreleasingStack *stack) {
    assert(stack);
    
    void **head = ANSAutoreleasingStackGetHead(stack);
    void **previousHead = head - 1;
    ANSAutoreleasingStackSetHead(stack, previousHead);
    ANSAutoreleasingStackType type = (*head) ? ANSAutoreleasingStackTypeObject : ANSAutoreleasingStackTypeNull;
    printf("%p\n", *head);
    ANSObjectRelease(*head);
    
    return type;
}

void ANSAutoreleasingStackPopAllObjects(ANSAutoreleasingStack *stack) {
    assert(stack);
    
    while (!ANSAutoreleasingStackIsEmpty(stack)) {
        ANSAutoreleasingStackPopObject(stack);
    }
}

ANSAutoreleasingStackType ANSAutoreleasingStackPopObjectsUntilNull(ANSAutoreleasingStack *stack) {
    assert(stack);

    ANSAutoreleasingStackType type = ANSAutoreleasingStackTypeNull;
    do {
        type = ANSAutoreleasingStackPopObject(stack);
    } while (type != ANSAutoreleasingStackTypeNull && !ANSAutoreleasingStackIsEmpty(stack));
    if (type == ANSAutoreleasingStackTypeNull ) {
        puts("I fount NULL VALUE");
    }
    return type;
}

#pragma mark -
#pragma mark Accessors declaration

void ANSAutoreleasingStackSetSize(ANSAutoreleasingStack *stack, size_t size) {
    assert(stack);
    
    if (stack->_size != size) {
        if (!size) {
            ANSAutoreleasingStackPopAllObjects(stack);
        }
        
        if (stack->_data) {
            free(stack->_data);
            stack->_data = NULL;
        }
        
        if (size) {
            stack->_data = calloc(1, size);
        }
        
        ANSAssignSetter(stack, _size, size);
    }
}

size_t ANSAutoreleasingStackGetSize(ANSAutoreleasingStack *stack) {
    assert(stack);

    return stack->_size;
}

void ANSAutoreleasingStackSetHead(ANSAutoreleasingStack *stack, void *head) {
    ANSAssignSetter(stack, _head, head);
}

void **ANSAutoreleasingStackGetHead(ANSAutoreleasingStack *stack) {
    assert(stack);
    
    return stack->_head;
}

void **ANSAutoreleasingStackGetData(ANSAutoreleasingStack *stack) {
    assert(stack);
    
    return stack->_data;
}
