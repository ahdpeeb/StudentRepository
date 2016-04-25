//
//  main.c
//  LCHW
//
//  Created by Nikola Andriiev on 07.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include <stdio.h>
#include <assert.h>

#include "ANSHuman.h"
#include "ANSObject.h"

int main(int argc, const char * argv[]) {
    
    ANSHuman *Man = ANSObjectCreateOfType(ANSHuman);
    ANSSetGender(Man, ANSGenderMale);
    ANSSetName(Man, "Sergey");
    ANSSetAge(Man, 27);
    
    ANSHuman *Female = ANSObjectCreateOfType(ANSHuman);
    ANSSetGender(Female, ANSGenderFemale);
    ANSSetName(Female, "Vika");
    ANSSetAge(Female, 25);
    
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
    ANSSetAge(childThree, 2);
    
    ANSHumanAndSpouseGetMarried(Man, Female);
    ANSParantsGotChild(Man, Female, childOne);
    ANSParantsGotChild(Female, Man, childTwo);
   // ANSHumanAndSpouseGetDivorsed(Man, Female);
    
    return 0;
}
