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
    ANSSetHumanGender(Man, ANSGenderMale);
    ANSSetHumanName(Man, "Sergey");
    ANSSetHumanAge(Man, 30);
    
    ANSHuman *Woman = ANSObjectCreateWithType(ANSHuman);
    ANSSetHumanGender(Woman, ANSGenderFemale);
    ANSSetHumanName(Woman, "Vika");
    ANSSetHumanAge(Woman, 32);
    
    ANSHumanGetMarriedWithSpouse(Man, Woman);
    
    ANSHuman *Child0 = ANSParentsCreateChild(Woman);
    ANSSetHumanName(Child0, "Нулевой");
    ANSHuman *Child1 = ANSParentsCreateChild(Woman);
    ANSSetHumanName(Child1, "Первый");
    ANSHuman *Child2 = ANSParentsCreateChild(Woman);
    ANSSetHumanName(Child2, "Второй");
    ANSHuman *Child3 = ANSParentsCreateChild(Woman);
    ANSSetHumanName(Child3, "Третий");
    ANSHuman *Child4 = ANSParentsCreateChild(Woman);
    ANSSetHumanName(Child4, "Четвертный");
    
//    ANSRemoveChildFromParents(Child1);
//    ANSRemoveChildFromParents(Child3);
//    ANSRemoveChildFromParents(Child2);
//    ANSRemoveChildFromParents(Child0);
    ANSRemoveChildFromParents(Child4);
    
    ANSHumanGetDivorsedWithSpouse(Woman);
}
