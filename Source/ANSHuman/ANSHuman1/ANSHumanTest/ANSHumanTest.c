//
//  ANSHumanTest.c
//  LCHW
//
//  Created by Nikola Andriiev on 25.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
#include <stdio.h>

#include "ANSHumanTest.h"
#include "ANSHuman.h"
#include "ANSObject.h"

void ANSTest(void) {
    ANSHuman *Man = ANSObjectCreateOfType(ANSHuman);
    ANSSetGender(Man, ANSGenderMale);
    ANSSetName(Man, "Sergey");
    ANSSetAge(Man, 30);
    
    ANSHuman *Female = ANSObjectCreateOfType(ANSHuman);
    ANSSetGender(Female, ANSGenderFemale);
    ANSSetName(Female, "Vika");
    ANSSetAge(Female, 32);
    
    ANSHuman *childOne = ANSObjectCreateOfType(ANSHuman);
    ANSSetGender(childOne, ANSGenderMale);
    ANSSetName(childOne, "Bulka");
    ANSSetAge(childOne, 1);
    
    ANSHuman *childTwo = ANSObjectCreateOfType(ANSHuman);
    ANSSetGender(childTwo, ANSGenderFemale);
    ANSSetName(childTwo, "Sopelka");
    ANSSetAge(childTwo, 2);
    
    ANSHuman *childThree = ANSObjectCreateOfType(ANSHuman);
    ANSSetGender(childThree, ANSGenderFemale);
    ANSSetName(childThree, "Picec");
    ANSSetAge(childThree, 3);
    
    ANSHumanAndSpouseGetMarried(Man, Female);
    ANSParantsGotChild(Man, Female, childOne);
    ANSParantsGotChild(Female, Man, childTwo);
    ANSParantsGotChild(Man, Female, childThree);
    
    printf("MAN amountOfChildren = %d \n", ANSGetChildrenCount(Man)); // test
    
    ANSKillChild(childTwo);
    ANSKillChild(childOne);
    printf("MAN amountOfChildren = %d \n", ANSGetChildrenCount(Man)); // test
    
    ANSHumanAndSpouseGetDivorsed(Man, Female);
}