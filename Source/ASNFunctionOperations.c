//
//  ASNFunctionOperations.c
//  LCHW
//
//  Created by Nikola Andriiev on 07.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include "ASNFunctionOperations.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void ANSPrintBoolStrint(bool boolValue){
    (boolValue == 1) ? printf("true\n") : printf("falce\n");
}

void ANSIdentifyDisease(bool redDotes, float bodyTemperature) {
    if ((redDotes == true) && (bodyTemperature >= 38.f) && (bodyTemperature < 42.f)){
        printf("the patient has malaria\n");
    }
    else if ((redDotes != true) && (bodyTemperature >= 37.f) && (bodyTemperature < 42.f)) {
        printf("the patient has flu\n");
    }
    else if ((bodyTemperature >= 42.f) || (redDotes == true)){
        printf("panient dead\n");
    } else {
        printf("healthy patient\n");
    }
}

void ANSPrintMamaOfDad(int firstValue, int secondValue){
    (firstValue > secondValue) ?  printf("Mama\n") : printf("Dad\n");
}

void ANSDefineDeputyHonesty(int salary) {
    
    
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
    (capital > salary * 100) ? ANSStateEmployeeThief :
    (capital > salary * 10) ? ANSStateEmployeeFraudster :
    (capital > salary) ? ANSStateEmployeeHoly : ANSStateEmployeeСorpse;
    
    ANSPrintStateEmployeeHonesty(EmployeeType);
}

void ANSPrintingOfStringComponents(char *string){
    printf("the number of characters in the stringArray - %lu\n",strlen(string));
    
    for (int index = 0; index < strlen(string); index++){
        printf ("%c\n",string[index]);
    }
}

bool ANSOutputMamOfDad(int value){
    bool successfuloperation = true;
    (value % 15 == 0) ? printf("mama\n") :
    (value % 5 == 0) ? printf("papa\n") :
    (value % 3 == 0) ? printf("mamapapa\n") : successfuloperation == false;
    return successfuloperation;
}
