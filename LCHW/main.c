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
    runAllFuncitons();
    runCycleWithInt(0, 100, 50);
}
// Тестовая реализация Не закончено!
void runCycleWithInt(int minValue, int maxValue, int stepsValue) {
    //int steps = minValue + stepsValue; // начальный шаг, + кол-во шагов
    while (maxValue > minValue) {
        minValue++;
        if (minValue % 3 == 0) continue; {
            printf("%d\n",minValue);
            }
        if (minValue == 50){
            return;
        }
    }
}