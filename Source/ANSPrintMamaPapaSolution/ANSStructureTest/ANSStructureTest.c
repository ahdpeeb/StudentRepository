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

#pragma mark -
#pragma mark Forvard Declaration

static
void ANSCharBitOutput(uint8_t value);

static
ASNEndiannessType ANSGetEndiannes(void);

static
void ANSPrintValueBitsWithEndianness(void *address, size_t size, ASNEndiannessType endianness);

static
void __ANSPrintValueBits(void *address, size_t size);

#pragma mark -
#pragma mark Public Implementetion

#define ANSPrintValueBits(value) \
    __ANSPrintValueBits(&value, sizeof(value))

void ANSRunApplications(unsigned char charValue) {
    int value = 255;
    ANSPrintValueBits(value);
}

#pragma mark -
#pragma mark Privat Implementation

void __ANSPrintValueBits(void *address, size_t size) {
    ANSPrintValueBitsWithEndianness(address, size, ANSGetEndiannes());
}

void ANSPrintValueBitsWithEndianness(void *address, size_t size, ASNEndiannessType endianness){
    uint8_t *value = (unsigned char *)address;
    for (size_t iterator = 0; iterator < size; iterator++) {
        size_t index = endianness == ANSBigEndian ? iterator : size - iterator - 1;
        ANSCharBitOutput(value[index]);
    }
    
    printf("\n");
}

void ANSCharBitOutput(uint8_t value) {
    const uint8_t bitCount = 8;
    printf("[ ");
    for (uint8_t iterator = 0; iterator < bitCount; iterator++) {
        uint8_t shiftedValue = value >> (bitCount - (iterator + 1));
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

#undef PrintShiftOfValue

void ANSPrintSizeOfStructure(void) {
    printf("Size of structure - %lu \n", sizeof(ANSStructureTest));
}

ASNEndiannessType ANSGetEndiannes(void) {
    unsigned short testValue = 1;
    uint8_t value = (((uint8_t *)&testValue)[0]);
    
    return (1 == value) ? ANSLitteleEndian :  ANSBigEndian;
}
