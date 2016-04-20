//
//  ANSTest.c
//  LCHW
//
//  Created by Nikola Andriiev on 19.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "ANSTest.h"

#pragma mark -
#pragma mark Memory allocation

int arifmeticFunction(int argument1, int argument2);

void ANSAlloctionTest(void) {
    const int count = 1000000;
    void *allocatedDataPointers[count]; // array of pointers on stack (includes 100 members)
    void *currentObject = NULL;
    
    for (uint64_t index = 0; index < count; index++) {
        currentObject = malloc(1); // size of currentObject - 1 byte;
        if (NULL == currentObject) {
            assert(NULL != currentObject); //assert -
        }
        if (NULL != currentObject) {
            allocatedDataPointers[index] = currentObject;
        }
    }
    for (uint64_t index = 0; index < count; index++)  {
        free(allocatedDataPointers[index]); // menory
    }
}

#pragma mark -
#pragma mark Selector


void ANSFunctionPointerTest(void){
    
}