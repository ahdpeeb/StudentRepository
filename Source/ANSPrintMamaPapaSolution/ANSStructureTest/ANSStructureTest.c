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

#pragma mark - public
void ANSRunApplications(unsigned char charValue) {
    int value = 255;
    ANSValueBitOutputDepindingOnProcessorType(&value, sizeof(value));
    ANSPrintOffset();
    ANSPrintSizeOfStructure();
    // ANSPrintBiraryRepresentationOfCharValue(charValue);
}

void ANSValueBitOutputDepindingOnProcessorType(void *byteAdress, size_t size) {
    unsigned int testValue  = 1;
    uint8_t value = (((char *)&testValue)[0]);
    size_t processorValue = (1 == value) ? (processorValue = 1) : (processorValue = size);
    for (uint16_t index = size ; index > 0; index--) {
            char byte = ((char*)byteAdress)[index-processorValue];
            ANSCharBitOutput(&byte);
        }
    printf("\n");
}

void ANSCharBitOutput(char *charValue) {
    uint8_t addres = *charValue;
    printf("[ ");
    for (uint8_t iterator = 8; iterator > 0; iterator--) {
        uint8_t shiftedValue = addres >> (iterator - 1);
        (shiftedValue & 1) ? printf("1 ") : printf("0 ");
    }
    printf("] ");
}

void ANSValueBitOutput(void *byteAdress, size_t size) {
    for (uint16_t index = size ; index > 0; index--) {
        char byte = ((char*)byteAdress)[index-1];
        ANSCharBitOutput(&byte);
    }
    printf("\n");
}

#define ANSMacrosImplementsShiftOutput(typeValue) \
printf(#typeValue"= %lu \n", offsetof(ANSStructureTest, typeValue));

void ANSPrintOffset(void) {
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

#undef ANSMacrosImplementsShiftOutput

void ANSPrintSizeOfStructure(void) {
    printf("Size of structure - %lu \n", sizeof(ANSStructureTest));
}


