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
void PrintMama(void) {
    printf("Mama");
}

void PrintPapa(void) {
    printf("Papa");
}

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
    
    if (condition & ANSMamaCondition) {
        printf("mama");
    }   else { printf("\n");
    }
    if (condition & ANSPapaCondition) {
        printf("papa");
    }   else { printf("\n");
    }

}
