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
//две решетки сливают два поля текста
#define ANSPrintSomeString(string, string2, string3) \
printf("I have to print some informatino " #string" "#string2" "#string3"\n");
#endif /* ANSMacrosDeclaration_h */

// макрос создает метод, генерирующий функцию  
#define ANSGenerateFuncton(type,qualifier) \
    void ANSOutput_#type(variableType value) { \
    printf(#type " value = %" #qualifier "\n", value); \
    }

