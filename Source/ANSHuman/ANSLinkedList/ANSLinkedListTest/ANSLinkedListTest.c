//
//  ANSLinkedListTest.c
//  LCHW
//
//  Created by Nikola Andriiev on 12.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
#include <assert.h>
#include <stdio.h>

#include "ANSLinkedListTest.h"

void ANSLinkedListTest(void) {

    ANSLinkedList *linkedList = ANSObjectCreateWithType(ANSLinkedList);
    assert(linkedList);
    
    printf("count - %d \n",(int)ANSLinkedListGetCount(linkedList));
    
    ANSHuman *human = ANSObjectCreateWithType(ANSHuman);
    ANSLinkedListAddObject(linkedList, human);
    
    ANSHuman *human1 = ANSObjectCreateWithType(ANSHuman);
    ANSLinkedListAddObject(linkedList, human1);
    
    ANSHuman *human2 = ANSObjectCreateWithType(ANSHuman);
    ANSLinkedListAddObject(linkedList, human2);
    ANSHuman *firstObject = ANSLinkedListGetFirstObject(linkedList);
    assert(human2 = firstObject);
    
    printf("count - %d \n",(int)ANSLinkedListGetCount(linkedList));
    
    ANSLinkedListRemoveFirstObject(linkedList);
    assert(human1 = firstObject);
    
    printf("count - %d \n",(int)ANSLinkedListGetCount(linkedList));
    bool isEmpty = ANSLinkedListIsEmpty(linkedList);
    if (!isEmpty) {
        puts("linkedList заполнен");
    }
    ANSHuman *human3 = ANSObjectCreateWithType(ANSHuman);
    ANSLinkedListAddObject(linkedList, human3);
    
    ANSHuman *human4 = ANSObjectCreateWithType(ANSHuman);
    ANSLinkedListAddObject(linkedList, human4);
    
    printf("count - %d \n",(int)ANSLinkedListGetCount(linkedList));
    //  ANSLinkedListRemoveAllObjects(linkedList);
    // printf("count - %d \n",(int)ANSLinkedListGetCount(linkedList));
    
    bool value = ANSLinkedListContainsObject(linkedList, human); //human - true/ human2 - falce
    if (value) {
        puts("linkedList содержит объект");
    } else {
        puts("linkedList НЕ СОДЕРЖИТ");
    }
    
}