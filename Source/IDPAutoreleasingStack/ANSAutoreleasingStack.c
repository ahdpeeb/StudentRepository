//
//  ANSAutoreleasingStack.c
//  LCHW
//
//  Created by Nikola Andriiev on 17.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
#include <assert.h>
#include <string.h>

#include "ANSAutoreleasingStack.h"

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
    void **data = ANSAutoreleasingStackGetData(stack); // array of pointers
    size_t size = ANSAutoreleasingStackGetSize(stack); // размер 40
    void *head = ANSAutoreleasingStackGetHead(stack); // указатель на голову
    void *dataTail = data[size / sizeof(data)];;
    return dataTail == head;
}

void ANSAutoreleasingStackPushObject(ANSAutoreleasingStack *stack, void *object) {
    assert(stack || !ANSAutoreleasingStackIsFull(stack));
    
    void *headObject = ANSAutoreleasingStackGetHead(stack) + 1;
    headObject = object; // may be &object !
    ANSAutoreleasingStackSetHead(stack, headObject);
}

ANSAutoreleasingStackType ANSAutoreleasingStackPopObject(ANSAutoreleasingStack *stack) {
    assert(stack || !ANSAutoreleasingStackIsEmpty(stack));
    
    void **head = ANSAutoreleasingStackGetHead(stack);
    void **nextHead = head +1;
    ANSAutoreleasingStackSetHead(stack, nextHead);
    ANSAutoreleasingStackType type = (head) ? ANSAutoreleasingStackTypeObject : ANSAutoreleasingStackTypeNull;
    ANSObjectRelease(head);
    
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
    } while (type != ANSAutoreleasingStackTypeNull || !ANSAutoreleasingStackIsEmpty(stack));
    
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

void *ANSAutoreleasingStackGetHead(ANSAutoreleasingStack *stack) {
    assert(stack);
    
    return stack->_head;
}

void **ANSAutoreleasingStackGetData(ANSAutoreleasingStack *stack) {
    assert(stack);
    
    return stack->_data;
}
