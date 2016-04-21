//
//  ANSHumanTest.c
//  LCHW
//
//  Created by Nikola Andriiev on 19.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "ANSHuman.h"

#pragma mark -
#pragma mark Public implementation

void ANSHumanDealloc(ANSHuman *human) {
    
}
ANSHuman *ANSCreateHuman(void) {
    ANSHuman *human = calloc(1, sizeof(ANSHuman));
    
    //что-то тут нужно сделать
    assert(NULL != human);
    
    human->_name = "NameNotFound";
    human->_age = 0;
    human->_gender = ANSGenderNotDefined;
    human->_childrenCount = 0;
    human->_maried = false;
    
    return human;
}
//нужно завладеть объектом. 
void ASNSetName(ANSHuman *human, char* name) {
    human->_name = name;
}

char *ASNGetName(ANSHuman *human) {
    return human->_name;
}

void ASNSetAge(ANSHuman *human, uint8_t age) {
    human->_age = age;
}

uint8_t ASNGetAge(ANSHuman *human) {
    return human->_age;
}

void ASNSetGender(ANSHuman *human, ANSGender gender) {
    human->_gender = gender;
}

ANSGender ASNGetGender(ANSHuman *human) {
    return human->_gender;
}

void ASNSetChildrenCount(ANSHuman *human, uint8_t childrenCount) {
    human->_childrenCount = childrenCount;
}

uint8_t ASNGetChildrenCount(ANSHuman *human) {
    return human->_childrenCount;
}

void ASNSetMariedStatus(ANSHuman *human, bool maried) {
    human->_maried = maried;
}

bool ASNGetMariedStatus(ANSHuman *human) {
    return human->_maried;
}


void ASNSetSpouses(ANSHuman *human, ANSHuman *spouse) {
    human->_spouse = spouse;
}

ANSHuman *ASNGetSpouse(ANSHuman *human) {
    return human->_spouse;
}

void ASNSetMother(ANSHuman *human, ANSHuman *mother) {
    human->_mother = mother;
}

ANSHuman *ASNGetMother(ANSHuman *human) {
    return human->_mother;
}

void ASNSetFather(ANSHuman *human, ANSHuman *father) {
    human->_father = father;
}

ANSHuman *ASNGetFather(ANSHuman *human) {
    return human->_father;
}

// полодижить в массив, детей. при удалении детей не должно быть дырок.(если убрать детей по индексу не должно быть смещений)
void ASNSetChildren(ANSHuman *human, ANSHuman *children[ASNHumanChildrenCount]) {
    human->_children[ASNHumanChildrenCount] = children[ASNHumanChildrenCount];
}

ANSHuman *ASNGetChildren(ANSHuman *human) {
    return human->_children[ASNHumanChildrenCount];
}


