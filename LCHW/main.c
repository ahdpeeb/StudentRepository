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

#include "ASNPrintingOperations.h"
#include "ANSFunctionOperation.h"

void ANSPrintTransition(void);

int main(int argc, const char * argv[]) {
    //    ANSPrintParametresOutput(1, 0.0001, "This is a set of characters: 184 711 Ezhh");
    //    ANSPrintTransition();
    //    ANSPrintIncrement(100);
    //    ANSPrintTransition();
    //    ANSSplitFormulaCalculation();
    /* for (int index = 0; index < 5; index++){
     printf (" prefix form - %d\n",++index);
     }*/
    //__________________5th lecture______________________________________
    
    //  ANSPrintBoolStrint(0);
    //  ANSIdentifyDisease(true, 36);
    //  ANSPrintMamaOfDad(5, 10);
    //  ANSDefineStateEmployeeHonesty(1500, 131243423);
    
    char string[] = "Hello, how are you";
    ANSPrintingOfStringComponents(string);
    
    
    ANSOutputMamOfDad (3); // не закончил
    
    return 0;
}

void ANSPrintTransition(void){
    printf("\n");
}
