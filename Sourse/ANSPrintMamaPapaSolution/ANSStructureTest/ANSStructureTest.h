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
/*typedef struct {
} ANSCar;*/

#define ANSMacrosImplementsShiftOutput(typeValue) \
printf(#typeValue"= %lu \n", offsetof(ANSStructTest, typeValue));

struct ANSStructTest {
    int intValue;
    bool boolValue1;
    float floatValue;
    long long llValue;
    short shortValue1;
    bool boolValue2;
    short shortValue2;
    char *testString;
    double testDouble;
    bool boolValue3;
    short shortValue3;
    bool boolValue4;
    bool boolValue5;
    bool boolValue6;
};

typedef struct ANSStructTest ANSStructTest;

//Function print structure field shifting from the begingn of structure;
void ANSPrintShiftStructureField(void);
#endif /* ANSStructureTest_h */
