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
void ANSHumanSetChildAtIndex(ANSHuman *human, ANSHuman *child, unsigned short index);

static
__unused bool ANSHumanMariedWithSpouse(ANSHuman *human, ANSHuman *spouse);

static
bool ANSHumanCanGetMarried(ANSHuman *human, ANSHuman *spouse);

static
unsigned short ANSRemoveChildReturnItsIndex(ANSHuman *human, ANSHuman *child);

static
void ANSReorderChildrenInHuman(ANSHuman *human, unsigned short indexOfRemovedChild);

static
void ANSRemoveAllChildren(ANSHuman *parent);

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
    human->_gender = ANSGenderNotDefined;
    
    return human;
}

void ANSHumanSetName(ANSHuman *human, char *name) {
    if (NULL != human) {
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
    return (!human) ? ANSGenderNotDefined : human->_gender; //
}


ANSHuman *ANSHumanGetSpouse(ANSHuman *human) {
    return (NULL == human) ? NULL : human->_spouse;
}

ANSHuman *ANSHumanGetMother(ANSHuman *human) {
    return human->_mother;
}

ANSHuman *ANSHumanGetFather(ANSHuman *human) {
    return human->_father;
}

ANSHuman *ANSGetChildOfIndex(ANSHuman *human, unsigned short index) {
    return human->_children[index];
}

unsigned short ANSGetChildrenCount(ANSHuman *child) {
    return child->_childrenCount;
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

void ANSRemoveChildFromParents(ANSHuman *child) {
    ANSHuman *mother = ANSHumanGetMother(child);
    ANSChildSetMother(child, NULL);
    unsigned short ChildIndexFromMother = ANSRemoveChildReturnItsIndex(mother, child);
    ANSReorderChildrenInHuman(mother, ChildIndexFromMother);
    
    ANSHuman *father = ANSHumanGetFather(child);
    ANSChildSetFather(child, NULL);
    unsigned short ChildIndexFromFather = ANSRemoveChildReturnItsIndex(father, child);
    ANSReorderChildrenInHuman(father, ChildIndexFromFather);
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
    assert(ANSHumanGetGender(human) != ANSGenderNotDefined);
    
    if (ANSHumanGetGender(human) == ANSGenderMale) {
        ANSHumanSetStrongSpouse(human, spouse);
    } else {
        ANSHumanSetWeakSpouse(human, spouse);
    }
}
// ___________________Set Parents________________________
void ANSChildSetMother(ANSHuman *child, ANSHuman *mother) {
    assert(child);
    
    if (ANSHumanGetMother(child) != mother) {
        child->_mother = mother;
    }
}

void ANSChildSetFather(ANSHuman *child, ANSHuman *father) {
    assert(child);
    
    if (ANSHumanGetFather(child) != father) {
        child->_father = father;
    }
}

void ANSChildSetParent(ANSHuman *child, ANSHuman *parent) {
    assert(child);

     if (ANSHumanGetGender(parent) == ANSGenderMale) {
        ANSChildSetFather(child, parent);
    } else {
        ANSChildSetMother(child, parent);
    }
}

#pragma mark -
#pragma mark Set/RemoveChild

void ANSHumanSetChildAtIndex(ANSHuman *human, ANSHuman *child, unsigned short index) {
    assert(human);
    
    human->_children[index] = child;
}

void ANSHumanChildrenCountAddValue(ANSHuman *human, unsigned short count) {
    assert(human);
    
    human->_childrenCount += count;
}

void ANSHumanSetChild(ANSHuman *human, ANSHuman *child) {
    for (short index = 0; index < ANSHumanChildrenCount; index ++) {
        if (ANSGetChildOfIndex (human, index) != NULL) {
            continue;
        } else {
            ANSHumanSetChildAtIndex(human, child, index);
            ANSObjectRetain(child);
            break;
        }
    }
}
// (remove  child from human and return his index)
unsigned short ANSRemoveChildReturnItsIndex(ANSHuman *human, ANSHuman *child) {
    for (short index = 0; index < ANSHumanChildrenCount; index++) {
        if (ANSGetChildOfIndex(human, index) == child) {
            ANSHumanSetChildAtIndex(human, NULL, index);
            ANSObjectRelease(child);
            ANSHumanChildrenCountAddValue(human, -1);
            return index;
        } else {
            continue;
        }
    }
    
    return UINT16_MAX; // правильно ли это?
}

void ANSRemoveAllChildren(ANSHuman *parent) {
    assert(parent);
    for (unsigned short index = 0; index < ANSHumanChildrenCount; index++) {
        ANSHuman *child = ANSGetChildOfIndex(parent, index);
        if (child != NULL) {
            ANSChildSetParent(child, NULL);
            ANSObjectRelease(child);
            ANSHumanSetChildAtIndex(parent, NULL, index);
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
void ANSReorderChildrenInHuman(ANSHuman *human, unsigned short indexOfRemovedChild) {
    for (unsigned short index = ANSHumanChildrenCount - 1; index >= 0; index--) {
        if (ANSGetChildOfIndex(human, index) != NULL && index != indexOfRemovedChild + 1) {
            ANSHuman *child = ANSGetChildOfIndex(human, index);
            ANSHumanSetChildAtIndex(human, child, indexOfRemovedChild);
            ANSHumanSetChildAtIndex(human, NULL, index);
            puts("Successful reordering!");
            break;
        } else {
           continue;
        }
    }
}
