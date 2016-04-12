//
//  ANSPrintMamaPapaSoluiton.c
//  LCHW
//
//  Created by Nikola Andriiev on 12.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
#include <stdio.h>

#include "ANSPrintMamaPapaSoluiton.h"

void ANSPrintMamaPapaShortSoluiton(int value) {
    printf("value = %d, %s%s \n",value, value % 3 == 0 ? "Mama": "", value % 5 == 0 ?"Papa" : "");
}