//
//  ANSCreature.m
//  LCHW
//
//  Created by Nikola Andriiev on 30.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#import "ANSCreature.h"

@interface ANSCreature ()
@property (nonatomic, retain) NSMutableArray *mutableArray;

- (NSArray *) _children;

@end

@implementation ANSCreature
@synthesize age, weight, gender, mutableArray;

#pragma mark -
#pragma mark private implementation

@dynamic children; //I'am responsible for property implementation, do not create new field
- (NSArray *) _children {
    return [[[self mutableArray] copy] autorelease];
}

#pragma mark -
#pragma mark public implementation

- (instancetype)initWithNameArray:(NSString*) name {
    self = [super init];
    if (self) {
        NSMutableArray *array = [[NSMutableArray new] autorelease];
        [self setMutableArray:array];
        [self setName:name];
    }
    
    return self;
}

+ (instancetype)createAutoreleaseObject {
    return [[[self alloc] init] autorelease];
}

- (void)addChild:(ANSCreature *)creature {
    if(![self.mutableArray containsObject:creature]) {
        [self.mutableArray addObject:creature];
    }
}

- (void)removeChild:(ANSCreature *)creature {
    if ([self.mutableArray containsObject:creature]) {
        [self.mutableArray removeObject:creature];
    }
}

- (void)sayPrivet {
    NSLog(@"Privet");
}

- (void)goFight:(ANSCreature *) creature {
    NSLog(@"%@ - i'am go to fing", creature.name);
}

- (ANSCreature *)goGiveBirth:(ANSCreature *) creature {
    NSLog(@"%@ - i'am can give birth" , creature.name);
    
    return [[ANSCreature new] autorelease];
}

- (NSString *) description {
    return [NSString stringWithFormat:@"Name - %@, Age - %d, Children - %@", self.name, self.age, self.children];
}

- (void) performGenderSpecificOperation {
    NSLog(@"performGenderSpecificOperation");
}

@end
