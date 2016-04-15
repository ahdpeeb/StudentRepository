//
//  ANSStructureTest.c
//  LCHW
//
//  Created by Nikola Andriiev on 15.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
#include <stdio.h>
#include <stddef.h>

#include "ANSStructureTest.h"

void ANSRunAllAplicaitons(unsigned char charValue) {
    ANSPrintShiftStructureField();
    ANSPrintSizeOfStructure();
    ANSPrintBiraryRepresentationOfCharValue(charValue);
}

void ANSPrintShiftStructureField(void) {
    ANSMacrosImplementsShiftOutput(intValue)
    ANSMacrosImplementsShiftOutput(floatValue)
    ANSMacrosImplementsShiftOutput(llValue)
    ANSMacrosImplementsShiftOutput(shortValue1)
    ANSMacrosImplementsShiftOutput(testString)
    ANSMacrosImplementsShiftOutput(testDouble)
    ANSMacrosImplementsShiftOutput(shortValue3)
    ANSMacrosImplementsShiftOutput(bitField)
    ANSMacrosImplementsShiftOutput(flags);
}

void ANSPrintSizeOfStructure(void) {
    printf("Size of structure - %lu \n",sizeof(ANSStructureTest));
}

void ANSPrintBiraryRepresentationOfCharValue(unsigned char charValue) {
    printf("[ ");
    for (uint8_t iterator = 8; iterator > 0; -- iterator) {
        uint8_t shiftedValue = charValue >> (iterator - 1);
        (shiftedValue & 1) ? printf("1 ") : printf("0 ");
    }
    printf("]\n");
}

