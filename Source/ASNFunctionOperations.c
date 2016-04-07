//
//  ASNFunctionOperations.c
//  LCHW
//
//  Created by Nikola Andriiev on 07.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include "ASNFunctionOperations.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void ANSPrintBoolStrint(bool boolValue) {
    (boolValue) ? puts("true") : puts("falce");
}

void ANSIdentifyDisease(bool redDotes, float bodyTemperature) {
    if ((redDotes) && (bodyTemperature >= 38.f) && (bodyTemperature < 42.f)) {
        puts("the patient has malaria");
    }
    else if ((redDotes != true) && (bodyTemperature >= 37.f) && (bodyTemperature < 42.f)) {
        puts("the patient has flu");
    }
    else if ((bodyTemperature >= 42.f) || (redDotes)) {
        puts("panient dead");
    } else {
        puts("healthy patient");
    }
}

void ANSPrintMamaOfDad(int firstValue, int secondValue){
    (firstValue > secondValue) ?  puts("Mama") : puts("Dad");
}

/*  исходные данные Вор: (статок > зп * 100)/
 мошенник: (статок > зп * 10)
 святой: (статок > зп * 1)
 труп: (все остальные случаи)  */

typedef enum  {
    ANSStateEmployeeThief,
    ANSStateEmployeeFraudster,
    ANSStateEmployeeHoly,
    ANSStateEmployeeСorpse
} ANSStateEmployeeHonesty;

void ANSPrintStateEmployeeHonesty (ANSStateEmployeeHonesty EmployeeType){
    switch (EmployeeType) {
        case ANSStateEmployeeThief:
            puts("Our state employee - thief.");
            break;
            
        case ANSStateEmployeeFraudster:
            puts("Our state employee - fraudster.");
            break;
            
        case ANSStateEmployeeHoly:
            puts("Our state employee - holy.");
            break;
            
        default:
            puts("Our state employee - stinking corpse.");
            break;
    }
}

void ANSDefineStateEmployeeHonesty(int salary, int capital){
    ANSStateEmployeeHonesty EmployeeType =
    (capital > salary * 100) ? ANSStateEmployeeThief
        :(capital > salary * 10) ? ANSStateEmployeeFraudster
            :(capital > salary) ? ANSStateEmployeeHoly : ANSStateEmployeeСorpse;
    
    ANSPrintStateEmployeeHonesty(EmployeeType);
}

void ANSPrintingOfStringComponents(char *string){
    printf("the number of characters in the stringArray - %lu\n",strlen(string));
    
    for (int index = 0; index < strlen(string); index++){
        printf ("%c\n", string[index]);
    }
}

void ANSOutputMomOfDad(int value){
    (value % 15 == 0) ? printf("mama\n")
        :(value % 5 == 0) ? printf("papa\n")
            :(value % 3 == 0) ? printf("mamapapa\n") : printf("");
  
}
