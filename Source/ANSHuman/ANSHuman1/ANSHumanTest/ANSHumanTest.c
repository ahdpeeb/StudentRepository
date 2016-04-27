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
    ANSHuman *Man = ANSObjectCreateWithType(ANSHuman);
    ANSSetGender(Man, ANSGenderMale);
    ANSSetName(Man, "Sergey");
    ANSSetAge(Man, 30);
    
    ANSHuman *Woman = ANSObjectCreateWithType(ANSHuman);
    ANSSetGender(Woman, ANSGenderFemale);
    ANSSetName(Woman, "Vika");
    ANSSetAge(Woman, 32);
    
    ANSHumanGetMarriedWithSpouse(Man, Woman);
  //ANSHumanGetDivorsedWithSpouse(Woman);
    ANSParentsCreateChild(Man);
  
   
    
    
}
