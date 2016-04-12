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

void ANSPrintDefinedCondition(int value) {
    ANSConditions condition1 = (value % 3 == 0) ? ANSMamaCondition : ANSBlankCondition;
    ANSConditions condition2 = (value % 5 == 0) ? ANSPapaCondition : ANSBlankCondition;
    
    if (condition1 == ANSMamaCondition) {
        printf("Mama");
    }if (condition2 == ANSPapaCondition) {
        printf("Papa");
    }
}

void ANSPrintDefinedCondition2(int value) {
    ANSConditions condition = (value % 3 == 0) ? (value % 5 == 0) ? ANSMamaCondition | ANSPapaCondition : ANSMamaCondition
            : (value % 5 == 0) ? ANSPapaCondition : ANSBlankCondition;
    
    if (condition == ANSMamaCondition) {
        printf("Mama");
    } else if  (condition == ANSPapaCondition) {
        printf("Papa");
    } else if (condition == ANSMamaPapaCondition) {
        printf("MamaPapa");
    }
}
