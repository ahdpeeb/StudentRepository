//
//  ANSArrayTest.c
//  LCHW
//
//  Created by Nikola Andriiev on 09.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include "ANSArrayTest.h"
#include "ANSHuman.h"

void ANSRunArrayTest(uint64_t NewCapacity) {
    
    //
    ANSArray *array = ANSArrayCreateWithCapacity(NewCapacity);
    
    ANSHuman *human = ANSObjectCreateWithType(ANSHuman);
    ANSHuman *human1 = ANSObjectCreateWithType(ANSHuman);
    ANSHuman *human2 = ANSObjectCreateWithType(ANSHuman);
    ANSHuman *human3 = ANSObjectCreateWithType(ANSHuman);
    ANSHuman *human4 = ANSObjectCreateWithType(ANSHuman);
    
    ANSArrayAddObject(array, human);
    ANSArrayGetCount(array);
    
    ANSArrayAddObject(array, human1);
    ANSArrayGetCount(array);
    
    ANSArrayAddObject(array, human2);
    ANSArrayGetCount(array);
    
    ANSArrayAddObject(array, human3);
    ANSArrayGetCount(array);
    
    ANSArrayAddObject(array, human4);
    ANSArrayGetCount(array);
    
}

