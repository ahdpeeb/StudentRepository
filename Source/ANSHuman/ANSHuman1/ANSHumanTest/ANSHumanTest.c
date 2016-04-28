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
    
    ANSHuman *Child0 = ANSParentsCreateChild(Woman);
    ANSSetName(Child0, "Нулевой");
    ANSHuman *Child1 = ANSParentsCreateChild(Woman);
    ANSSetName(Child1, "Первый");
    ANSHuman *Child2 = ANSParentsCreateChild(Woman);
    ANSSetName(Child2, "Второй");
    ANSHuman *Child3 = ANSParentsCreateChild(Woman);
    ANSSetName(Child3, "Третий");
    ANSHuman *Child4 = ANSParentsCreateChild(Woman);
    ANSSetName(Child4, "Четвертный");
    

    ANSRemoveChildFromParents(Child1);
    ANSRemoveChildFromParents(Child3);
    ANSRemoveChildFromParents(Child2);
    ANSRemoveChildFromParents(Child0);
//    ANSRemoveChildFromParents(Child4);
    
    ANSHumanGetDivorsedWithSpouse(Woman);
}
