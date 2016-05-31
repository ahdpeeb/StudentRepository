//
//  ANSCreature.h
//  LCHW
//
//  Created by Nikola Andriiev on 30.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ANSCreature : NSObject

typedef NSString * creatureGender;

@property (nonatomic, retain) NSString *name;
@property (nonatomic, assign) unsigned short age;
@property (nonatomic, assign) float weight;
@property (nonatomic, retain) creatureGender gender;
@property (nonatomic, retain, readonly) NSArray *children;

- (instancetype)initWithNameArray:(NSString*) name;

+ (instancetype)createAutoreleaseObject;

- (void)addChild:(ANSCreature *)creature;

- (void)removeChild:(ANSCreature *)creature;

- (void)sayPrivet;

- (void)goFight:(ANSCreature *) creature;

- (ANSCreature *)goGiveBirth:(ANSCreature *) creature;

- (void) performGenderSpecificOperation;

- (NSArray *) children;
@end
