//
//  ANSPrintMamaPapaSoluiton.c
//  LCHW
//
//  Created by Nikola Andriiev on 12.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
#include <stdio.h>
#include <string.h>

#include "ANSPrintMamaPapaSoluiton.h"

void ANSPrintMamaPapaShortSolution(int value) {
    printf("%s%s \n", value % 3 == 0 ? "Mama": "", value % 5 == 0 ? "Papa" : "");
    }

ANSConditions ANSPrintDefinedCondition(int value) {
    ANSConditions condition = ANSBlankCondition;
    
    if (0 == value % 3) {
        printf("Mama");
        condition |=ANSMamaCondition;
    }
    
    if (0 == value % 5) {
        printf("Papa");
        condition |=ANSPapaCondition;
    }
    
    if (value !=ANSBlankCondition) {
        printf("\n");
    }
    
    return condition;
}
