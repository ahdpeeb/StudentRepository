//
//  ANSStructureTest.h
//  LCHW
//
//  Created by Nikola Andriiev on 15.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#ifndef ANSStructureTest_h
#define ANSStructureTest_h

#include <stdbool.h>
typedef enum {
    ANSProcessorTypeLittleEndian,
    ANSProcessorTypeBigEndian
}ANSProcessorType;


//initial size 56 bytes;
// than 48;
// than 40;
// uint8_t bitField - 
struct ANSStructureTest {
    char *testString;   //8
    long long llValue;  //8
    double testDouble;  //8
    float floatValue;   //4
    int intValue;       //4
    short shortValue1;
    short shortValue2;
    short shortValue3;
        union {
            struct {
                bool boolValue1:1;
                bool boolValue2:1;
                bool boolValue3:1;
                bool boolValue4:1;
                bool boolValue5:1;
                bool boolValue6:1;
            } flags;
            uint8_t bitField;
        };
};

typedef struct ANSStructureTest ANSStructureTest;

//Function print structure field shifting from the begingn of structure;
void ANSPrintOffset(void);

// Function print Size of any Structure
void ANSPrintSizeOfStructure(void);

void ANSCharBitOutput(char *charValue);

void ANSNumberBitOutputDepindingOnProcessorType(void *byteAdress, size_t size);

void ANSValueBitOutput(void *byteAdress, size_t size);

#endif /* ANSStructureTest_h */


