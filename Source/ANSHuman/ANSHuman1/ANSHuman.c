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
void ANSSetStrongSpouse (ANSHuman *human, ANSHuman *spouse);

static
void ANSSetWeakSpouse (ANSHuman *human, ANSHuman *spouse);

static
void ANSSetSpouse(ANSHuman *human, ANSHuman *spouse);

static
void ANSSetParent(ANSHuman *child, ANSHuman *parent);

static
void ANSSetChild(ANSHuman *human, ANSHuman *child);

static
void ANSRemoveChildFromParent (ANSHuman *parent, ANSHuman *child); // 2 lvl

static
bool ANSAreTheyMaried(ANSHuman *human, ANSHuman *spouse);

static
bool ANSAreTheyGetero(ANSHuman *human, ANSHuman *spouse);

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

//________________________________Name____________________________________________
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
//________________________________Age____________________________________________
void ANSSetAge(ANSHuman *human, uint8_t age) {
    assert(human);
    
    human->_age = age;
}

uint8_t ANSGetAge(ANSHuman *human) {
    return (NULL == human) ? 0 : human->_age;
}

//______________________________Gender____________________________________________
void ANSSetGender(ANSHuman *human, ANSGender gender) {
    assert(human);
    
    human->_gender = gender;
}

ANSGender ANSGetGender(ANSHuman *human) {
    return (!human) ? ANSGenderNotDefined : human->_gender; //
}
//_______________________________Get Married, GetDivorsed__________________________
void ANSHumanAndSpouseGetMarried(ANSHuman *human, ANSHuman *spouse) {
    if (ANSAreTheyGetero(human, spouse)) {
        ANSSetSpouse(human, spouse);
        ANSSetSpouse(spouse, human);
    } else {
        exit(1);
    }
}

void ANSHumanAndSpouseGetDivorsed(ANSHuman *human) {
    assert(human);
    
    ANSHuman *partner = ANSGetSpouse(human);
        assert(partner);
    if (ANSAreTheyMaried(human, partner)) {
        ANSSetSpouse(partner, NULL);
        ANSSetSpouse(human, NULL);
        ANSObjectRelease(human->_spouse);
        puts("successful divorse!");
    }
}

void ANSKillChild(ANSHuman *child) {
    assert(child);
    
    ANSHuman *mother = ANSGetMother(child);
    ANSHuman *father = ANSGetFather(child);
    child->_mother = NULL;
    child->_father = NULL;
    ANSRemoveChildFromParent(mother, child);
    ANSRemoveChildFromParent(father, child);
}

ANSHuman *ANSParentsCreateChild(ANSHuman *human) {
    ANSHuman *child = ANSObjectCreateWithType(ANSHuman);
    assert(child && human);
    
    ANSHuman *partner = ANSGetSpouse(human);
    assert (partner);
    
    if (ANSAreTheyMaried(human, partner)) {
        ANSSetChild(human, child);
        ANSSetChild(partner, child);
        ANSSetParent(child, human);
        ANSSetParent(child, partner);
        printf("They got a child successfully, her name %s \n", ANSGetName(child));
    } else {
        return NULL;
    }
    
    return child;
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

ANSHuman *ANSGetChild(ANSHuman *child, uint8_t index) {
    return child->_children[index];
}

uint8_t ANSGetChildrenCount(ANSHuman *child) {
    return child->_childrenCount;
}

#pragma mark -
#pragma mark Privat implementation

//___________________________________SetSpouse_________________________________________

static
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

//______________________________SetParents_____________________________________
void ANSSetMother(ANSHuman *human, ANSHuman *mother) {
    assert(human);
    
    if (ANSGetMother(human) != mother) {
        human->_mother = mother;
    }
}

void ANSSetFather(ANSHuman *human, ANSHuman *father) {
    assert(human);
    
    if (ANSGetMother(human) != father) {
        human->_father = father;
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

//______________________________ANSSet/Remove___________________________________

void ANSSetChild(ANSHuman *human, ANSHuman *child) {
    assert(human && child);
    
    for (int index = 0; index < ANSHumanChildrenCount; index ++) {
        if (ANSGetChild(child, index) != NULL) {
            continue;
        } else {
            human->_children[index] = child;
            ANSObjectRetain(child);
            human->_childrenCount++;
            break;
        }
    }
}

void ANSRemoveChildFromParent (ANSHuman *parent, ANSHuman *child) {
    assert(parent);
    
    for (int index = 0; index < ANSHumanChildrenCount; index++) {
        if (parent->_children[index] == child) {
            ANSObjectRelease(child);
            parent->_children[index] = NULL;
            parent->_childrenCount --;
            parent->_children[index] = parent->_children[index + 1];
            parent->_children[index + 1] = NULL;
        } else {
            continue;
        }
    }
}

bool ANSAreTheyMaried(ANSHuman *human, ANSHuman *spouse) {
    bool boolValue = ((ANSGetSpouse(human) == spouse) && (ANSGetSpouse(spouse) == human)) ? true : false;
    
    return boolValue;
}

bool ANSAreTheyGetero(ANSHuman *human, ANSHuman *spouse) {
    bool boolValue = ANSGetGender(human) != ANSGetGender(spouse) ? true : false;
    
    return boolValue;
}
