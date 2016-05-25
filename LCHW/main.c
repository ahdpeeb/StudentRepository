//
//  main.c
//  LCHW
//
//  Created by Nikola Andriiev on 07.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include <string.h>
#include <stdio.h>
#include "ANSHumanTest.h"
#include "ANSArrayTest.h"
#include "ANSLinkedListTest.h"
#include "ANSAutoreleasingStackTest.h"

int main(int argc, const char * argv[]) {
  // ANSRunArrayTest(1);
  // ANSLinkedListEnumerationTest();
  //ANSLinkedListTest();
    ANSRunPoolTest(19);
  // ANSRunStackTest(6);
    return 0;
}

