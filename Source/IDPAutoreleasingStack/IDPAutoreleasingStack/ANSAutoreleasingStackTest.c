//
//  ANSAutoreleasingStack.c
//  LCHW
//
//  Created by Nikola Andriiev on 17.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
#include <stdio.h>
#include "ANSAutoreleasingStackTest.h"
#include "ANSObject.h"
#include "ANSHuman.h"

void ANSRunPoolTest(uint64_t value) {
    
    ANSAutoreleasePoolCreate();
    ANSAutoreleasePool *pool = ANSAutoreleasePoolGetPool();
    
    for (uint64_t index = 0; index < value; index++) {
        ANSHuman *human = ANSObjectCreateWithType(ANSHuman);
        ANSAutoreleasePoolAddObject(pool, human);
        printf("human %llu - %p \n", index, human);
    }
    
    ANSAutoreleasePoolCreate();
    pool = ANSAutoreleasePoolGetPool();
    
    for (uint64_t index = 0; index < value; index++) {
        ANSHuman *human = ANSObjectCreateWithType(ANSHuman);
        ANSAutoreleasePoolAddObject(pool, human);
        printf("human %llu - %p \n", index, human);
    }
    
    ANSAutoreleasePoolDrain(); //
    pool = ANSAutoreleasePoolGetPool();
    bool validity1 = ANSAutoreleasePoolGetValid();
    
    ANSAutoreleasePoolDrain();
    bool validity2 = ANSAutoreleasePoolGetValid();
    pool = ANSAutoreleasePoolGetPool();
}

void ANSRunStackTest(uint64_t value) {
    ANSAutoreleasingStack *stack = ANSAutoreleasingStackCreateWithSize(48);
  
    ANSHuman *human0 = ANSObjectCreateWithType(ANSHuman);
    ANSAutoreleasingStackPushObject(stack, human0);
    printf("%p\n", human0);
    ANSHuman *human1 = ANSObjectCreateWithType(ANSHuman);
    ANSAutoreleasingStackPushObject(stack, human1);
    printf("%p\n", human1);
    ANSHuman *human2 = ANSObjectCreateWithType(ANSHuman);
    ANSAutoreleasingStackPushObject(stack, human2);
    printf("%p\n", human2);
    ANSHuman *human3 = ANSObjectCreateWithType(ANSHuman);
    ANSAutoreleasingStackPushObject(stack, human3);
    printf("%p\n", human3);
    ANSHuman *human4 = ANSObjectCreateWithType(ANSHuman);
    ANSAutoreleasingStackPushObject(stack, human4);
    printf("%p\n", human4);
    ANSHuman *human5 = ANSObjectCreateWithType(ANSHuman);
    ANSAutoreleasingStackPushObject(stack, human5);
    printf("%p\n", human5);
        if (ANSAutoreleasingStackIsFull(stack)) {
            puts("stack is Full");
        }
    
    ANSAutoreleasingStackPopObjectsUntilNull(stack);
        puts("finish");
}