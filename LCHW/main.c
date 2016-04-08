//
//  main.c
//  LCHW
//
//  Created by Nikola Andriiev on 07.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include <float.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "ASNFunctionOperations.h"

void runCycleWithInt(int minValue, int maxValue, int stepsValue);

int main(int argc, const char * argv[]) {
//
//    //__________________5th lecture______________________
//    char string[] = "Hello, how are you";
//    ANSPrintBoolStrint(0);
//    ANSIdentifyDisease(true, 36);
//    ANSPrintMamaOfDad(5, 10);
//    ANSDefineStateEmployeeHonesty(1500, 131243423);
//    ANSPrintingOfStringComponents(string);
//    ANSPrintLastElementNumber(string);
//    ANSDifineCondition(45);
    runCycleWithInt(0, 100, 100);

}

void runCycleWithInt(int minValue, int maxValue, int stepsValue) {
    int steps = minValue + stepsValue; // начальный шаг, + кол-во шагов
    while (maxValue > minValue) {
        minValue++;
        if (minValue % 3 == 0) continue; {
            printf("%d\n",minValue);
        }
    }
    
}