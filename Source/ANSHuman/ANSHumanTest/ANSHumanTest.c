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
    
    ANSHuman *Child0 = ANSHumanCreateChild(Woman);
    ANSHumanSetName(Child0, "Нулевой");
    ANSHuman *Child1 = ANSHumanCreateChild(Woman);
    ANSHumanSetName(Child1, "Первый");
    ANSHuman *Child2 = ANSHumanCreateChild(Woman);
    ANSHumanSetName(Child2, "Второй");
    ANSHuman *Child3 = ANSHumanCreateChild(Woman);
    ANSHumanSetName(Child3, "Третий");
    ANSHuman *Child4 = ANSHumanCreateChild(Woman);
    ANSHumanSetName(Child4, "Четвертный");
//________________________________________________
    ANSRemoveChildFromParent(Woman, Child4);
    ANSRemoveChildFromParent(Woman, Child2);
    ANSRemoveChildFromParent(Woman, Child1);
//________________________________________________
    
    ANSHuman *Child5 = ANSHumanCreateChild(Woman);
    ANSHumanSetName(Child5, "Пятый");
    
    ANSHumanDivorce(Man);
}
