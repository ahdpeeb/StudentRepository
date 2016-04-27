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
void ANSSetChildrenCount(ANSHuman *human, uint8_t count);
static
void ANSSetStrongSpouse (ANSHuman *human, ANSHuman *spouse);

static
void ANSSetWeakSpouse (ANSHuman *human, ANSHuman *spouse);

static
void ANSSetSpouse(ANSHuman *human, ANSHuman *spouse);

static
void ANSSetMother(ANSHuman *child, ANSHuman *mother);

static
void ANSSetFather(ANSHuman *child, ANSHuman *father);

static
void ANSSetParent(ANSHuman *child, ANSHuman *parent);

static
void ANSSetChild(ANSHuman *human, ANSHuman *child);

static
void ANSSetChildOfIndex(ANSHuman *human, ANSHuman *child, uint8_t index);

static
void ANSRemoveChildFromHuman(ANSHuman *human, ANSHuman *child);

static
bool ANSAreTheyMaried(ANSHuman *human, ANSHuman *spouse);

static
bool ANSHumanCanGetMarried(ANSHuman *human, ANSHuman *spouse);

#pragma mark -
#pragma mark Public implementation

void __ANSHumanDeallocate(void *human) {
    ANSSetName(human, NULL);
    ANSSetSpouse(human, NULL);
    ANSSetParent(human, NULL);
    
    __ANSObjectDeallocate(human);
}

ANSHuman *ANSCreateHuman(void) {
    ANSHuman *human = ANSObjectCreateWithType(ANSHuman);
    human->_gender = ANSGenderNotDefined;
    
    return human;
}

void ANSSetName(ANSHuman *human, char *name) {
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

char *ANSGetName(ANSHuman *human) {
    return (NULL == human) ? NULL : human->_name;
}

void ANSSetAge(ANSHuman *human, uint8_t age) {
    assert(human);
    
    human->_age = age;
}

uint8_t ANSGetAge(ANSHuman *human) {
    return (!human) ? 0 : human->_age;
}

void ANSSetGender(ANSHuman *human, ANSGender gender) {
    assert(human);
    
    human->_gender = gender;
}

ANSGender ANSGetGender(ANSHuman *human) {
    return (!human) ? ANSGenderNotDefined : human->_gender; //
}

//___________________Get married/ GetDivorsed__________________________
void ANSHumanGetMarriedWithSpouse(ANSHuman *human, ANSHuman *spouse) {
    bool status = ANSHumanCanGetMarried(human, spouse);
    assert(status);
    if (status) {
        ANSSetSpouse(human, spouse);
        ANSSetSpouse(spouse, human);
        puts("successful marriage!");
    }
}

void ANSHumanGetDivorsedWithSpouse(ANSHuman *human) {
    ANSHuman *partner = ANSGetSpouse(human);
    if (ANSAreTheyMaried(human, partner)) {
        ANSSetSpouse(partner, NULL);
        ANSSetSpouse(human, NULL);
        puts("successful divorse!");
    }
}

ANSHuman *ANSParentsCreateChild(ANSHuman *human) {
    ANSHuman *partner = ANSGetSpouse(human);
    ANSHuman *child = ANSObjectCreateWithType(ANSHuman);
    assert(child);
    
    if (ANSAreTheyMaried(human, partner)) {
        ANSSetChild(human, child);
        ANSSetChild(partner, child);
        ANSSetParent(child, human);
        ANSSetParent(child, partner);
    }
    
    return child;
}

void ANSRemoveChildFromParants(ANSHuman *child) {
    assert(child);
    
    ANSHuman *mother = ANSGetMother(child);
    ANSHuman *father = ANSGetFather(child);
    ANSSetMother(child, NULL);
    ANSSetFather(child, NULL);
    ANSRemoveChildFromHuman(mother, child);
    ANSRemoveChildFromHuman(father, child);
}

ANSHuman *ANSGetSpouse(ANSHuman *human) {
    return (NULL == human) ? NULL : human->_spouse;
}

ANSHuman *ANSGetMother(ANSHuman *human) {
    return human->_mother;
}

ANSHuman *ANSGetFather(ANSHuman *human) {
    return human->_father;
}

ANSHuman *ANSGetChildOfIndex(ANSHuman *child, uint8_t index) {
    return child->_children[index];
}

uint8_t ANSGetChildrenCount(ANSHuman *child) {
    return child->_childrenCount;
}

#pragma mark -
#pragma mark Privat implementation

//_____________________Set partner___________________________
void ANSSetStrongSpouse(ANSHuman *human, ANSHuman *spouse) {
    assert(human);
    
    if (ANSGetSpouse(human) != human) {
        ANSObjectRelease(human->_spouse);
        human->_spouse = spouse;
        ANSObjectRetain(spouse);
    }
}

void ANSSetWeakSpouse (ANSHuman *human, ANSHuman *spouse) {
    assert(human);
    
    if (ANSGetSpouse(human) != human) {
        human->_spouse = spouse;
    }
}

void ANSSetSpouse(ANSHuman *human, ANSHuman *spouse) {
    assert(ANSGetGender(human) != ANSGenderNotDefined);
    if (ANSGetGender(human) == ANSGenderMale) {
        ANSSetStrongSpouse(human, spouse);
    } else {
        ANSSetWeakSpouse(human, spouse);
    }
}
// ___________________Set Paranats________________________
void ANSSetMother(ANSHuman *child, ANSHuman *mother) {
    assert(child);
    
    if (ANSGetMother(child) != mother) {
        child->_mother = mother;
    }
}

void ANSSetFather(ANSHuman *child, ANSHuman *father) {
    assert(child);
    
    if (ANSGetMother(child) != father) {
        child->_father = father;
    }
}

void ANSSetParent(ANSHuman *child, ANSHuman *parent) {
    assert(child);

     if (ANSGetGender(parent) == ANSGenderMale) {
        ANSSetFather(child, parent);
    } else {
        ANSSetMother(child, parent);
    }
}
//____________________Set Child_________________________________________
void ANSSetChildOfIndex(ANSHuman *human, ANSHuman *child, uint8_t index) {
    assert(human && child);
    
    human->_children[index] = child;
}

void ANSSetChildrenCount(ANSHuman *human, uint8_t count) {
    assert(human);
    human->_childrenCount += count;
}

void ANSSetChild(ANSHuman *human, ANSHuman *child) {
    for (int index = 0; index < ANSHumanChildrenCount; index ++) {
        if (ANSGetChildOfIndex (child, index) != NULL) {
            continue;
        } else {
            ANSSetChildOfIndex(human, child, index);
            ANSObjectRetain(child);
            ANSSetChildrenCount(human, 1);
            break;
        }
    }
}
// not finished
void ANSRemoveChildFromHuman(ANSHuman *human, ANSHuman *child) {
    assert(human && child);
    
    for (int index = 0; index < ANSHumanChildrenCount; index++) {
        if (human->_children[index] == child) {
            ANSObjectRelease(child);
            human->_children[index] = NULL;
            ANSSetChildrenCount(human, 1);
            human->_children[index] = human->_children[index + 1];
            human->_children[index + 1] = NULL;
        } else {
            continue;
        }
    }
}
// not finished
void ANSRemoveAllChildren(ANSHuman *parent) {
    assert(parent);
    for (int index = 0; index < ANSHumanChildrenCount; index++) {
        if (parent->_children[index] != NULL) {
        //  ANSGetChildOfIndex
            ANSObjectRelease(parent->_children[index]);
            parent->_children[index] = NULL;
        }
    }
}

bool ANSAreTheyMaried(ANSHuman *human, ANSHuman *spouse) {
    return ((ANSGetSpouse(human) == spouse) && (ANSGetSpouse(spouse) == human));
}

bool ANSHumanCanGetMarried(ANSHuman *human, ANSHuman *spouse) {
    return ANSGetGender(human) != ANSGetGender(spouse);
}
