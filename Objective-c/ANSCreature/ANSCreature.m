//
//  ANSCreature.m
//  LCHW
//
//  Created by Nikola Andriiev on 30.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#import "ANSCreature.h"

@interface ANSCreature ()

@property (nonatomic, retain) NSMutableArray *_mutableArray;

@end

@implementation ANSCreature

@synthesize age, weight, gender, _mutableArray;
@dynamic children; //I'am responsible for property implementation, do not create new field

#pragma mark -
#pragma mark Public implementation

- (NSArray *) children {
    return [[[self _mutableArray] copy] autorelease];
}

- (instancetype)initWithNameArray:(NSString*) name {
    self = [super init];
    if (self) {
        NSMutableArray *array = [[NSMutableArray new] autorelease];
        [self set_mutableArray:array];
        [self setName:name];
    }
    
    return self;
}

+ (instancetype)createAutoreleaseObject {
    return [[[self alloc] init] autorelease];
}

- (void)addChild:(ANSCreature *)creature {
    if(![self._mutableArray containsObject:creature]) {
        [self._mutableArray addObject:creature];
    }
}

- (void)removeChild:(ANSCreature *)creature {
    if ([self._mutableArray containsObject:creature]) {
        [self._mutableArray removeObject:creature];
    }
}

- (void)sayPrivet {
    NSLog(@"Privet");
}

- (void)famylySayPrivet {
    [self sayPrivet];
    [self.children makeObjectsPerformSelector:@selector(sayPrivet)];
}

- (void)goFight:(ANSCreature *) creature {
    NSLog(@"%@ - i'am go to fing", creature.name);
}

- (ANSCreature *)goGiveBirth:(ANSCreature *) creature {
    NSLog(@"%@ - i'am can give birth" , creature.name);
    
    return [ANSCreature createAutoreleaseObject];
}

- (NSString *) description {
    return [NSString stringWithFormat:@"Name - %@, Age - %d, Children - %@", self.name, self.age, self.children];
}

- (void) performGenderSpecificOperation {
    NSLog(@"performGenderSpecificOperation");
}

@end
