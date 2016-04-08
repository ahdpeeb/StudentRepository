//
//  ASNFunctionOperations.h
//  LCHW
//
//  Created by Nikola Andriiev on 07.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
// 
#ifndef ASNFunctionOperations_h
#define ASNFunctionOperations_h

#include <stdbool.h>

// print a strint dependint of "bool" value
void ANSPrintBoolStrint(bool boolValue);

// function identifies disease
void ANSIdentifyDisease(bool redDotes, float bodyTemperature);

// print Mam of Dad
void ANSPrintMamaOfDad(int firstValue, int secondValue);

// define the type of state employee by comparing their capital
void ANSDefineStateEmployeeHonesty(int salary, int capital);

// it's count and displays the character-string
void ANSPrintingOfStringComponents(char *string);

// determines number of the last item in array
void ANSPrintLastElementNumber(char *string);

// determines the condition of division
void ANSDifineCondition(int value);
#endif /* ASNFunctionOperations_h */

// run all class functions 
void runAllFuncitons(void);
