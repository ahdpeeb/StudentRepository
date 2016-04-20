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

#include "ANSHumanTest.h"

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
void ASN_SetName(ANSHuman *human, char* name) {
    human->_name = name;
}

char *ASN_GetName(ANSHuman *human) {
    return human->_name;
}

void ASN_SetAge(ANSHuman *human, uint8_t age) {
    human->_age = age;
}

uint8_t ASN_GetAge(ANSHuman *human) {
    return human->_age;
}

void ASN_SetGender(ANSHuman *human, ANSGender gender) {
    human->_gender = gender;
}

ANSGender ASN_GetGender(ANSHuman *human) {
    return human->_gender;
}

void ASN_SetChildrenCount(ANSHuman *human, uint8_t childrenCount) {
    human->_childrenCount = childrenCount;
}

uint8_t ASN_GetChildrenCount(ANSHuman *human) {
    return human->_childrenCount;
}

void ASN_SetMariedStatus(ANSHuman *human, bool maried) {
    human->_maried = maried;
}

bool ASN_GetMariedStatus(ANSHuman *human) {
    return human->_maried;
}


void ASN_SetSpouses(ANSHuman *human, ANSHuman *spouse) {
    human->_spouse = spouse;
}

ANSHuman *ASN_GetSpouse(ANSHuman *human) {
    return human->_spouse;
}

void ASN_SetMother(ANSHuman *human, ANSHuman *mother) {
    human->_mother = mother;
}

ANSHuman *ASN_GetMother(ANSHuman *human) {
    return human->_mother;
}

void ASN_SetFather(ANSHuman *human, ANSHuman *father) {
    human->_father = father;
}

ANSHuman *ASN_GetFather(ANSHuman *human) {
    return human->_father;
}

// полодижить в массив, детей. при удалении детей не должно быть дырок.(если убрать детей по индексу не должно быть смещений)
void ASN_SetChildren(ANSHuman *human, ANSHuman *children[ASNHumanChildrenCount]) {
    human->_children[ASNHumanChildrenCount] = children[ASNHumanChildrenCount];
}

ANSHuman *ASN_GetChildren(ANSHuman *human) {
    return human->_children[ASNHumanChildrenCount];
}


