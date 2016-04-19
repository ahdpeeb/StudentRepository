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


static void ANSCharBitOutput(uint8_t value);

static ASNEndiannessType ANSDefineCPUType(void);

static void __ANSPrintValueBits(void *byteAdress, size_t size);

#pragma mark - Public

#define ANSPrintValueBits(value) \
__ANSPrintValueBits(&value, sizeof(value))

void ANSRunApplications(unsigned char charValue) {
    int value = 255;
    ANSPrintValueBits(value);
}

#pragma mark - Privat

void __ANSPrintValueBits(void *address, size_t size) {
    uint8_t *value = (unsigned char *)address;
    for (uint16_t index = size ; index > 0; index--) {
        // как мне во втором случае вычесть size? еще один терннарник?
            ANSCharBitOutput(value[index - ANSDefineCPUType()]);
        }
    printf("\n");
}

void ANSCharBitOutput(uint8_t value) {
    const uint8_t bitCount = 8;
    printf("[ ");
    for (uint8_t iterator = 0; iterator < bitCount; iterator++) {
        uint8_t shiftedValue = value >> (bitCount - (iterator +1));
        printf("%d ",shiftedValue & 1);
    }
    printf("] ");
}

void ANSValueBitOutput(void *byteAdress, size_t size) {
    for (uint16_t index = size ; index > 0; index--) {
        char byte = ((char *)byteAdress)[index - 1];
        ANSCharBitOutput(byte);
    }
    printf("\n");
}

#define PrintShiftOfValue(typeValue) \
printf(#typeValue"= %lu \n", offsetof(ANSStructureTest, typeValue))

void ANSPrintOffset(void) {
    PrintShiftOfValue(intValue);
    PrintShiftOfValue(floatValue);
    PrintShiftOfValue(llValue);
    PrintShiftOfValue(shortValue1);
    PrintShiftOfValue(testString);
    PrintShiftOfValue(testDouble);
    PrintShiftOfValue(shortValue3);
    PrintShiftOfValue(bitField);
    PrintShiftOfValue(flags);
}

#undef ANSMacrosImplementsShiftOutput

void ANSPrintSizeOfStructure(void) {
    printf("Size of structure - %lu \n", sizeof(ANSStructureTest));
}

ASNEndiannessType ANSDefineCPUType(void) {
    unsigned short testValue = 1;
    uint8_t value = (((char *)&testValue)[0]);
    ASNEndiannessType processorValue = (1 == value) ? (processorValue = ANSLitteleEndianness)
        : (processorValue = ANSBigEndEndianness);
    
    return processorValue;
}
