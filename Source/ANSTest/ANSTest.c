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


void ANSAlloctionTest(void) {
    const int count = 1000000;
    void *allocatedDataPointers[count]; // массив указателей на стеке, которые включает 100.. элементов.
    void *currentObject = NULL;
    
    for (uint64_t index = 0; index < count; index++) {
        currentObject = malloc(1); // объекту выделили один байт
        if (NULL == currentObject) {
            assert(NULL != currentObject); //assert - падает приложение. (ничего не равно текуему объекту)
        }
        if (NULL != currentObject) {
            allocatedDataPointers[index] = currentObject;
        }
    }
    for (uint64_t index = 0; index < count; index++)  {
        free(allocatedDataPointers[index]); //обнуление всех указателей
    }
}