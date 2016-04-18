//
//  ANSPrintFunctionValue.c
//  LCHW
//
//  Created by Nikola Andriiev on 11.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include "ANSPrintFunctionValue.h"
#include "ANSMacrosDeclaration.h"

#include <stdio.h>
// function generation

ANSGeneratePrintingFuncton(int, d)
ANSGeneratePrintingFuncton(char, c)
ANSGeneratePrintingFuncton(float, f)

void ANSRunApplication(int intValue, char charValue, float floatValue) {
    ANSOutputValue(int, intValue)
    ANSOutputValue(char, charValue)
    ANSOutputValue(float, floatValue)
}
