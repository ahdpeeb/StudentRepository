//
//  main.m
//  Objective-c
//
//  Created by Nikola Andriiev on 27.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include "ANSCreature.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSMutableArray *arrayOfCreatures = [[NSMutableArray new]autorelease];
        
        for (int index = 0; index < 3; index ++) {
            NSString *string = [NSString stringWithFormat:@"Human %d", index];
            ANSCreature *creature = [[ANSCreature alloc] initWithNameArray:string];
            [arrayOfCreatures addObject: creature];
        }
        
        for (int index = 2; index >= 0; index --) {
            ANSCreature *creature = [arrayOfCreatures objectAtIndex:index];
            ANSCreature *child = [[ANSCreature new]autorelease];
            [creature addChild:child];
        }
    }
    
    return 0;
}
