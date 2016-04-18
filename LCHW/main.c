//
//  main.c
//  LCHW
//
//  Created by Nikola Andriiev on 07.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include <stdio.h>

#include "ANSStructureTest.h"

int main(int argc, const char * argv[]) {
    
    int value = 5;
    ANSNumberBitOutputDepindingOnProcessorType(&value, sizeof(value));
}

