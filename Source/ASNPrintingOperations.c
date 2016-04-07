//
//  ASNPrintingOperations.c
//  LCHW
//
//  Created by Nikola Andriiev on 07.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include "ASNPrintingOperations.h"

#include <stdio.h>

void ANSPrintParametresOutput(int integerValue,
                              float floatValue,
                              char *charValue){
    printf(" integer = %d;\n float = %f;\n char = %s.\n", integerValue, floatValue,     charValue);
}

void ANSPrintIncrement(int integerValue){
    int increment = integerValue +1;
    printf (" increment = %d.\n",increment);
}
// Вопрос, зачем после определенния переменной добавлять "f"
void ANSSplitFormulaCalculation(void){
    float doubleResult = 3.0f; // first variable
    float floatResult = 3.0f; // second variable
    doubleResult = doubleResult * doubleResult;
    doubleResult = doubleResult / 4;
    doubleResult = (int) doubleResult % 7; //
    floatResult = doubleResult * 4;
    floatResult = floatResult - 1.5;
    floatResult = floatResult + 'A';
    doubleResult = doubleResult + floatResult;
    printf(" value of formula = %.2f\n",doubleResult);
    
    
    ///adsf
    //dsaf
}

