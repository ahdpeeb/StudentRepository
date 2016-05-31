//
//  ANSCreatureTest.m
//  LCHW
//
//  Created by Nikola Andriiev on 30.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#import "ANSCreatureTest.h"

@implementation ANSCreatureTest

#pragma mark -
#pragma mark Public test

- (void)runTest {
    NSMutableArray *arrayOfCreatures = [[NSMutableArray new]autorelease];
    
    for (int index = 0; index < 5; index ++) {
        NSString *name = [NSString stringWithFormat:@"Human %d", index];
        ANSCreature *creature = [[ANSCreature alloc] initWithNameArray:name];
        
        BOOL value = arc4random() % 2;
        NSString *gender = [[NSString new] autorelease];
        gender = (value) ? @"Male" : @"Female";
        creature.gender = gender;
      
        [arrayOfCreatures addObject: creature];
    }
    
    for (int index = 0; index < arrayOfCreatures.count; index ++) {
        ANSCreature *creature = [arrayOfCreatures objectAtIndex:index];
        
        ANSCreature *child1 = [[ANSCreature new]autorelease];
        [creature addChild:child1];
        
        ANSCreature *child2 = [[ANSCreature new]autorelease];
        [creature addChild:child2];
        
        if ([creature.gender isEqualToString:@"Male"]) {
            [creature goFight:creature];
        } else {
            [creature goGiveBirth:creature];
        }
    }
}

- (void) performGenderSpecificOperation {
    NSLog(@"overridden method");
}
@end
