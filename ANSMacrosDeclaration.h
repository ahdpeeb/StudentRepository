//
//  ANSMacrosDeclaration.h
//  LCHW
//
//  Created by Nikola Andriiev on 09.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#ifndef ANSMacrosDeclaration_h
#define ANSMacrosDeclaration_h

// # ставит ковычку
//две решетки сливают два поля текста (не ставит ковычки)

// test macros, that assume values
#define ANSPrintTestString(string, string2, string3) \
printf("I have to print some informatino " #string" "#string2" "#string3"\n");
#endif /* ANSMacrosDeclaration_h */

// macros create function generation
#define ANSGenerateFuncton(type,qualifier) \
    void ANSOutput_ ##type(type value) { \
    printf(#type " value = %" #qualifier "\n", value); \
    }
// macros call function, that preciously was created by macros "ANSGenerateFuncton"
#define ANSCallFunction(functionType) \
    ANSPrint_ ##functionType();

