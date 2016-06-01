//
//  main.m
//  Objective-c
//
//  Created by Nikola Andriiev on 27.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include "ANSCreature.h"
#include "ANSCreatureTest.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        ANSCreatureTest *test = [ANSCreatureTest createAutoreleaseObject];
        [test performGenderSpecificOperation];
        [test runTest];
    }
    
    return 0;
}
