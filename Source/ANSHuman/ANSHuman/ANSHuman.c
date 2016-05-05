//
//  ANSHuman.c
//  LCHW
//
//  Created by Nikola Andriiev on 19.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "ANSHuman.h"

#pragma mark -
#pragma mark Privat declaration

static
void ANSHumanChildrenCountAddValue(ANSHuman *human, unsigned short count);

static
void ANSHumanSetStrongSpouse (ANSHuman *human, ANSHuman *spouse);

static
void ANSHumanSetWeakSpouse (ANSHuman *human, ANSHuman *spouse);

static
void ANSHumanSetSpouse(ANSHuman *human, ANSHuman *spouse);

static
void ANSChildSetMother(ANSHuman *child, ANSHuman *mother);

static
void ANSChildSetFather(ANSHuman *child, ANSHuman *father);

static
void ANSChildSetParent(ANSHuman *child, ANSHuman *parent);

static
void ANSHumanSetChild(ANSHuman *human, ANSHuman *child);

static
void ANSHumanSetStrongChildAtIndex(ANSHuman *human, ANSHuman *child, unsigned short index);

static
void ANSRemoveAllChildren(ANSHuman *parent);

static
__unused bool ANSHumanMariedWithSpouse(ANSHuman *human, ANSHuman *spouse);

static
bool ANSHumanCanGetMarried(ANSHuman *human, ANSHuman *spouse);

static
void ANSHumanReorderChildren(ANSHuman *human);

static
void ANSChildRemoveParant(ANSHuman *child, ANSHuman *parant);

#pragma mark -
#pragma mark Public implementation

void __ANSHumanDeallocate(void *human) {
    
    ANSHumanSetSpouse(human, NULL);
    ANSChildSetMother(human, NULL);
    ANSChildSetFather(human, NULL);
    ANSRemoveAllChildren(human);
    
    __ANSObjectDeallocate(human);
}

ANSHuman *ANSCreateHuman(void) {
    ANSHuman *human = ANSObjectCreateWithType(ANSHuman);
    human->_gender = ANSGenderUndefined;
    
    return human;
}

void ANSHumanSetName(ANSHuman *human, char *name) {
    assert(NULL != human && human->_name != name); {
        if (NULL != human->_name) {
            free(human->_name);
            human->_name = NULL;
        }
        
        if (name) {
            human->_name = strdup(name);
        }
    }
}

char *ANSHumanGetName(ANSHuman *human) {
    return (NULL == human) ? NULL : human->_name;
}

void ANSHumanSetAge(ANSHuman *human, unsigned short age) {
    assert(human);
    
    human->_age = age;
}

unsigned short ANSHumanGetAge(ANSHuman *human) {
    return (!human) ? 0 : human->_age;
}

void ANSHumanSetGender(ANSHuman *human, ANSGender gender) {
    assert(human);
    
    human->_gender = gender;
}

ANSGender ANSHumanGetGender(ANSHuman *human) {
    return (!human) ? ANSGenderUndefined : human->_gender; //
}


ANSHuman *ANSHumanGetSpouse(ANSHuman *human) {
    return (NULL == human) ? NULL : human->_spouse;
}

ANSHuman *ANSChildGetMother(ANSHuman *child) {
    return child->_mother;
}

ANSHuman *ANSChildGetFather(ANSHuman *child) {
    return child->_father;
}

ANSHuman *ANSHumanGetChildAtIndex(ANSHuman *human, unsigned short index) {
    return human->_children[index];
}

unsigned short ANSHumanGetIndexOfChild(ANSHuman *human, ANSHuman *child) {
    assert(human && child);
    
    for (unsigned short index = 0; index < ANSHumanChildrenCount; index ++) {
        if (ANSHumanGetChildAtIndex(human, index) == child) {
            
            return index;
            break;
        }
    }
    
    return UINT16_MAX;
}

unsigned short ANSHumanGetChildrenCount(ANSHuman *human) {
    return human->_childrenCount;
}
//___________________Get married/ GetDivorsed__________________________
void ANSHumanGetMarriedWithSpouse(ANSHuman *human, ANSHuman *spouse) {
    bool status = ANSHumanCanGetMarried(human, spouse);
    assert(status);
    
    ANSHumanSetSpouse(human, spouse);
    ANSHumanSetSpouse(spouse, human);
    puts("successful marriage!");
}

void ANSHumanGetDivorsedWithSpouse(ANSHuman *human) {
    ANSHuman *partner = ANSHumanGetSpouse(human);
        ANSHumanSetSpouse(partner, NULL);
        ANSHumanSetSpouse(human, NULL);
        puts("successful divorse!");
}

ANSHuman *ANSParentsCreateChild(ANSHuman *human) {
        assert(ANSHumanGetChildrenCount(human) < ANSHumanChildrenCount - 1);
    
        ANSHuman *partner = ANSHumanGetSpouse(human);
        ANSHuman *child = ANSObjectCreateWithType(ANSHuman);
        assert(child);
    
        ANSHumanSetChild(human, child);
        ANSHumanSetChild(partner, child);
        ANSChildSetParent(child, human);
        ANSChildSetParent(child, partner);
        ANSHumanChildrenCountAddValue(human, 1);
        ANSHumanChildrenCountAddValue(partner, 1);
   
    return child;
}

#pragma mark -
#pragma mark Privat implementation

//_____________________Set partner___________________________
void ANSHumanSetStrongSpouse(ANSHuman *human, ANSHuman *spouse) {
    assert(human);
    
    if (ANSHumanGetSpouse(human) != human) {
        ANSObjectRelease(human->_spouse);
        human->_spouse = spouse;
        ANSObjectRetain(spouse);
    }
}

void ANSHumanSetWeakSpouse (ANSHuman *human, ANSHuman *spouse) {
    assert(human);
    
    if (ANSHumanGetSpouse(human) != human) {
        human->_spouse = spouse;
    }
}

void ANSHumanSetSpouse(ANSHuman *human, ANSHuman *spouse) {
    assert(ANSHumanGetGender(human) != ANSGenderUndefined);
    
    if (ANSHumanGetGender(human) == ANSGenderMale) {
        ANSHumanSetStrongSpouse(human, spouse);
    } else {
        ANSHumanSetWeakSpouse(human, spouse);
    }
}
// ___________________Set Parents________________________
void ANSChildSetMother(ANSHuman *child, ANSHuman *mother) {
    assert(child);
    
    if (ANSChildGetMother(child) != mother) {
        child->_mother = mother;
    }
}

void ANSChildSetFather(ANSHuman *child, ANSHuman *father) {
    assert(child);
    
    if (ANSChildGetFather(child) != father) {
        child->_father = father;
    }
}

void ANSChildSetParent(ANSHuman *child, ANSHuman *parent) {
    assert(child && ANSHumanGetGender(parent) != ANSGenderUndefined);

     if (ANSHumanGetGender(parent) == ANSGenderMale) {
        ANSChildSetFather(child, parent);
    } else {
        ANSChildSetMother(child, parent);
    }
}

#pragma mark -
#pragma mark Set/RemoveChild

void ANSHumanSetStrongChildAtIndex(ANSHuman *human, ANSHuman *child, unsigned short index) {
    assert(human);
    
    if (ANSHumanGetChildAtIndex(human, index) != child) {
        ANSObjectRelease(human->_children[index]);
        human->_children[index] = child;
        ANSObjectRetain(child);
    }
}

void ANSHumanChildrenCountAddValue(ANSHuman *human, unsigned short count) {
    assert(human);
    
    human->_childrenCount += count;
}

void ANSHumanSetChild(ANSHuman *human, ANSHuman *child) {
    for (short index = 0; index < ANSHumanChildrenCount; index ++) {
        if (ANSHumanGetChildAtIndex (human, index) != NULL) {
            continue;
        } else {
            ANSHumanSetStrongChildAtIndex(human, child, index);
            break;
        }
    }
}
    // removeChildFromParent 
void ANSRemoveChildFromParant(ANSHuman *human, ANSHuman *child) {
    ANSChildRemoveParant(child, human);
    unsigned short indexOfChild = ANSHumanGetIndexOfChild(human, child);
    ANSHumanSetStrongChildAtIndex(human, NULL, indexOfChild);
    ANSHumanChildrenCountAddValue(human, -1);
    ANSHumanReorderChildren(human);
}

void ANSRemoveAllChildren(ANSHuman *parent) {
    assert(parent);
    
    for (unsigned short index = 0; index < ANSHumanChildrenCount; index++) {
        ANSHuman *child = ANSHumanGetChildAtIndex(parent, index);
        if (child != NULL) {
            ANSChildSetParent(child, NULL);
            ANSHumanSetStrongChildAtIndex(parent, NULL, index);
            ANSHumanChildrenCountAddValue(parent, -1);
        }
    }
}

#pragma mark -
#pragma mark accessory functions

bool ANSHumanMariedWithSpouse(ANSHuman *human, ANSHuman *spouse) {
    return ((ANSHumanGetSpouse(human) == spouse) && (ANSHumanGetSpouse(spouse) == human));
}

bool ANSHumanCanGetMarried(ANSHuman *human, ANSHuman *spouse) {
    return ANSHumanGetGender(human) != ANSHumanGetGender(spouse);
}

//reorder children in human
void ANSHumanReorderChildren(ANSHuman *human) {

    short indexOfLastChild = ANSHumanGetChildrenCount(human);
    for (short index = 0; index < indexOfLastChild; index ++) {
        if (ANSHumanGetChildAtIndex(human, index) == NULL) {
        ANSHuman *child = ANSHumanGetChildAtIndex(human, indexOfLastChild);
            ANSHumanSetStrongChildAtIndex(human, child, index);
            ANSHumanSetStrongChildAtIndex(human, NULL, indexOfLastChild);
        }
    }
}

void ANSChildRemoveParant(ANSHuman *child, ANSHuman *parant) {
    if (ANSHumanGetGender(parant) == ANSGenderMale) {
        child->_father = NULL;
    } else {
        child->_mother = NULL;
    }
}
