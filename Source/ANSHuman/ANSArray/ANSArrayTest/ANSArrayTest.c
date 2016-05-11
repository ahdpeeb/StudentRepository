//
//  ANSArrayTest.c
//  LCHW
//
//  Created by Nikola Andriiev on 09.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include <stdio.h>
#include <assert.h>

#include "ANSArrayTest.h"
#include "ANSHuman.h"

void ANSRunArrayTest(uint64_t NewCapacity) {
    
    ANSArray *array = ANSArrayCreateWithCapacity(NewCapacity);
    assert(array);
    
    for (int index = 0; index < 100; index++) {
    ANSHuman *human = ANSObjectCreateWithType(ANSHuman);
        assert(human);
        
    ANSArrayAddObject(array, human);
    uint64_t value = ANSArrayGetCount(array);
        printf("numberOfObjects %llu \n", value);
        
    ANSHuman *returnedHuman = ANSArrayGetObjectAtIndex(array, ANSArrayGetCount(array) - 1);
        assert(returnedHuman);
    }
    puts("stop");
    
    for (int index = 99; index >= 0; index --) {
        ANSArrayGetObjectAtIndex(array, index);
        ANSHuman *returnedHuman = ANSArrayGetObjectAtIndex(array, index);
        ANSArrayRemoveObject(array, returnedHuman);
        puts("stop");
    }
    
puts("stop");
}

