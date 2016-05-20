//
//  ANSAutoreleasingStack.c
//  LCHW
//
//  Created by Nikola Andriiev on 17.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include "ANSAutoreleasingStackTest.h"
#include "ANSObject.h"
#include "ANSHuman.h"

void ANSRunPoolTest(uint64_t value) {
    ANSAutoreleasePool *pool = ANSAutoreleasePoolCreatePool(); // successfully
    __unused ANSAutoreleasingStack *headStack = ANSAutoreleasePoolGetHeadStack(pool);
    for (uint64_t index = 0; index < value; index++) {
        ANSHuman *human = ANSObjectCreateWithType(ANSHuman);
        __unused ANSHuman **link = &human;
        ANSAutoreleasePoolAddObject(pool, human);
    }
}