//
//  ANSLinkedListTest.c
//  LCHW
//
//  Created by Nikola Andriiev on 12.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
#include <assert.h>
#include <stdio.h>

#include "ANSLinkedList.h"
#include "ANSLinkedListEnumerator.h"
#include "ANSHuman.h"

#include "ANSLinkedListTest.h"

void ANSLinkedListTest(void) {
    ANSLinkedList *linkedList = ANSObjectCreateWithType(ANSLinkedList);
    assert(linkedList);
    
    ANSHuman *human = ANSObjectCreateWithType(ANSHuman);
    ANSLinkedListAddObject(linkedList, human);
    
    ANSHuman *human1 = ANSObjectCreateWithType(ANSHuman);
    ANSLinkedListAddObject(linkedList, human1);
    
    ANSHuman *human2 = ANSObjectCreateWithType(ANSHuman);
    ANSLinkedListAddObject(linkedList, human2);
    
    ANSHuman *human3 = ANSObjectCreateWithType(ANSHuman);
    ANSLinkedListAddObject(linkedList, human3);
    
    ANSHuman *human4 = ANSObjectCreateWithType(ANSHuman);
    ANSLinkedListAddObject(linkedList, human4);
    
    ANSHuman *firstObject = ANSLinkedListGetFirstObject(linkedList);
    assert(human2 = firstObject);
    
    ANSLinkedListRemoveFirstObject(linkedList); // удалил 4ый объект
    assert(human1 = firstObject);
    
    printf("count - %d \n", (int)ANSLinkedListGetCount(linkedList));
    
    bool isEmpty = ANSLinkedListIsEmpty(linkedList);
    if (!isEmpty) {
        puts("linkedList заполнен");
    }
    
    ANSLinkedListRemoveAllObjects(linkedList);
    printf("count - %d \n",(int)ANSLinkedListGetCount(linkedList));
    
    bool value = ANSLinkedListContainsObject(linkedList, human2);
    (value) ?  puts("Содержит") : puts("НЕ СОДЕРЖИТ");

     ANSLinkedListRemoveObject(linkedList, human3);
     printf("count - %d \n",(int)ANSLinkedListGetCount(linkedList));
    
   __unused ANSHuman *returnTest = ANSLinkedListGetObjectBeforeObject(linkedList, human3);
    
}

void ANSLinkedListEnumerationTest(void) {
    ANSLinkedListEnumerator *enumerator = ANSObjectCreateWithType(ANSLinkedListEnumerator);
    assert(enumerator);
    
    
}
