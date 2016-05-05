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
#include "ANSArray.h"

void ANSTest(void) {
    ANSHuman *Man = ANSObjectCreateWithType(ANSHuman);
    ANSHumanSetGender(Man, ANSGenderMale);
    ANSHumanSetName(Man, "Sergey");
    ANSHumanSetAge(Man, 30);
    
    ANSHuman *Woman = ANSObjectCreateWithType(ANSHuman);
    ANSHumanSetGender(Woman, ANSGenderFemale);
    ANSHumanSetName(Woman, "Vika");
    ANSHumanSetAge(Woman, 32);
    
    ANSHumanGetMarriedWithSpouse(Man, Woman);
    
    ANSHuman *Child0 = ANSParentsCreateChild(Woman);
    ANSHumanSetName(Child0, "Нулевой");
    ANSHuman *Child1 = ANSParentsCreateChild(Woman);
    ANSHumanSetName(Child1, "Первый");
    ANSHuman *Child2 = ANSParentsCreateChild(Woman);
    ANSHumanSetName(Child2, "Второй");
    ANSHuman *Child3 = ANSParentsCreateChild(Woman);
    ANSHumanSetName(Child3, "Третий");
    ANSHuman *Child4 = ANSParentsCreateChild(Woman);
    ANSHumanSetName(Child4, "Четвертный");
    
    ANSRemoveChildFromParent(Woman, Child4);
    ANSRemoveChildFromParent(Woman, Child2);
    ANSRemoveChildFromParent(Woman, Child1);
    
    ANSHumanGetDivorsedWithSpouse(Woman);
}
