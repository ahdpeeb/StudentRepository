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

int main(int argc, const char * argv[]) {
   // ANSRunArrayTest(1);
   // ANSLinkedListEnumerationTest();
   // ANSLinkedListTest();
    
    char *string1 = "Helloooooo";
    char *string2 = "Mama";
    char *string3 = "Papa";
    char *array[3] = {string1, string2, string3};
    char **pointToArray = array;

    printf("адрес указателя string1 - %p \n", &string1);
    printf("адрес указателя string2 - %p \n", &string2);
    printf("адрес указателя string3 - %p \n", &string3);
    printf("адрес указателя array -  %p \n",  &array);
    printf("значение *pointToArray - %p \n" , pointToArray);
    
    char **object = &array[0];
    
    printf("object = %s \n", *object);
    
    return 0;
}

