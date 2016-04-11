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
ANSGeneratePrintingFuncton(char, c);
ANSGeneratePrintingFuncton(int, d);
ANSGeneratePrintingFuncton(float, f)

void ANSPrint_intValue(value) {
    ANSOutput_int(5.5);
}

void ANSPrint_floatValue(void) {
    ANSOutput_float(5.5);
}

void ANSPrint_charValue(void) {
    ANSOutput_char('A');
}
