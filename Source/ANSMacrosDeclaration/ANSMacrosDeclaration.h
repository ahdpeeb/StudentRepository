//
//  ANSMacrosDeclaration.h
//  LCHW
//
//  Created by Nikola Andriiev on 09.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#ifndef ANSMacrosDeclaration_h
#define ANSMacrosDeclaration_h

// #puts quotes
//## ## split text merging

// test macros, that assume values
#define ANSPrintTestString(string, string2, string3) \
    printf("I have to print some information " #string" "#string2" "#string3"\n");

// macros create function generation
#define ANSGeneratePrintingFuncton(type, qualifier) \
    void ANSOutput_ ##type(type value) { \
        printf(#type " value = %" #qualifier "\n", value); \
    }

// macros call function, that preciously was created by macros "ANSGenerateFuncton"
#define ANSOutputValue(type, value) \
    ANSOutput_##type(value);


// macros create function (Print sizeOfValue)
#define ANSGenereteFunctionPrintSizeOfValue(type) \
            do { \
                type value; \
                printf("Size of"#type" value = %lu", sizeof(value)); \
            } while (0);

#endif /* ANSMacrosDeclaration_h */
