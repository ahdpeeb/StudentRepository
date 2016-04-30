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
void ANSSetChildrenCount(ANSHuman *human, short count);

static
void ANSSetStrongSpouse (ANSHuman *human, ANSHuman *spouse);

static
void ANSSetWeakSpouse (ANSHuman *human, ANSHuman *spouse);

static
void ANSSetHumanSpouse(ANSHuman *human, ANSHuman *spouse);

static
void ANSSetChildMother(ANSHuman *child, ANSHuman *mother);

static
void ANSSetChildFather(ANSHuman *child, ANSHuman *father);

static
void ANSSetChildParent(ANSHuman *child, ANSHuman *parent);

static
void ANSSetHumanChild(ANSHuman *human, ANSHuman *child);

static
void ANSSetChildOfIndex(ANSHuman *human, ANSHuman *child, short index);

static
bool ANSAreHumanAndSpouseMaried(ANSHuman *human, ANSHuman *spouse);

static
bool ANSHumanCanGetMarried(ANSHuman *human, ANSHuman *spouse);

static
short ANSRemoveChildReturnItsIndex(ANSHuman *human, ANSHuman *child);

static
void ANSReorderChildrenInHuman(ANSHuman *human, short indexOfRemovedChild);

static
void ANSRemoveAllChildren(ANSHuman *parent);
#pragma mark -
#pragma mark Public implementation

void __ANSHumanDeallocate(void *human) {
    ANSSetHumanName(human, NULL);
    ANSSetHumanAge(human, 0);
    ANSSetHumanGender(human, ANSGenderNotDefined);
    ANSSetHumanSpouse(human, NULL);
    ANSSetChildMother(human, NULL);
    ANSSetChildFather(human, NULL);
    ANSRemoveAllChildren(human);
    
    __ANSObjectDeallocate(human);
}

ANSHuman *ANSCreateHuman(void) {
    ANSHuman *human = ANSObjectCreateWithType(ANSHuman);
    human->_gender = ANSGenderNotDefined;
    
    return human;
}

void ANSSetHumanName(ANSHuman *human, char *name) {
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

char *ANSGetHumanName(ANSHuman *human) {
    return (NULL == human) ? NULL : human->_name;
}

void ANSSetHumanAge(ANSHuman *human, short age) {
    assert(human);
    
    human->_age = age;
}

short ANSGetHumanAge(ANSHuman *human) {
    return (!human) ? 0 : human->_age;
}

void ANSSetHumanGender(ANSHuman *human, ANSGender gender) {
    assert(human);
    
    human->_gender = gender;
}

ANSGender ANSGetHumanGender(ANSHuman *human) {
    return (!human) ? ANSGenderNotDefined : human->_gender; //
}


ANSHuman *ANSGetHumanSpouse(ANSHuman *human) {
    return (NULL == human) ? NULL : human->_spouse;
}

ANSHuman *ANSGetHumanMother(ANSHuman *human) {
    return human->_mother;
}

ANSHuman *ANSGetHumanFather(ANSHuman *human) {
    return human->_father;
}

ANSHuman *ANSGetChildOfIndex(ANSHuman *human, short index) {
    return human->_children[index];
}

short ANSGetChildrenCount(ANSHuman *child) {
    return child->_childrenCount;
}
//___________________Get married/ GetDivorsed__________________________
void ANSHumanGetMarriedWithSpouse(ANSHuman *human, ANSHuman *spouse) {
    bool status = ANSHumanCanGetMarried(human, spouse);
    assert(status);
    if (status) {
        ANSSetHumanSpouse(human, spouse);
        ANSSetHumanSpouse(spouse, human);
        puts("successful marriage!");
    }
}

void ANSHumanGetDivorsedWithSpouse(ANSHuman *human) {
    ANSHuman *partner = ANSGetHumanSpouse(human);
    if (ANSAreHumanAndSpouseMaried(human, partner)) {
        ANSSetHumanSpouse(partner, NULL);
        ANSSetHumanSpouse(human, NULL);
        puts("successful divorse!");
    }
}

ANSHuman *ANSParentsCreateChild(ANSHuman *human) {
    ANSHuman *partner = ANSGetHumanSpouse(human);
    ANSHuman *child = ANSObjectCreateWithType(ANSHuman);
    assert(child);
    
    if (ANSHumanCanGetMarried(human, partner)) {
        ANSSetHumanChild(human, child);
        ANSSetHumanChild(partner, child);
        ANSSetChildParent(child, human);
        ANSSetChildParent(child, partner);
        ANSSetChildrenCount(human, 1);
        ANSSetChildrenCount(partner, 1);
    }
    
    return child;
}

void ANSRemoveChildFromParents(ANSHuman *child) {
    ANSHuman *mother = ANSGetHumanMother(child);
    ANSSetChildMother(child, NULL);
    short ChildIndexFromMother = ANSRemoveChildReturnItsIndex(mother, child);
    ANSReorderChildrenInHuman(mother, ChildIndexFromMother);
    
    ANSHuman *father = ANSGetHumanFather(child);
    ANSSetChildFather(child, NULL);
    short ChildIndexFromFather = ANSRemoveChildReturnItsIndex(father, child);
    ANSReorderChildrenInHuman(father, ChildIndexFromFather);
}

#pragma mark -
#pragma mark Privat implementation

//_____________________Set partner___________________________
void ANSSetStrongSpouse(ANSHuman *human, ANSHuman *spouse) {
    assert(human);
    
    if (ANSGetHumanSpouse(human) != human) {
        ANSObjectRelease(human->_spouse);
        human->_spouse = spouse;
        ANSObjectRetain(spouse);
    }
}

void ANSSetWeakSpouse (ANSHuman *human, ANSHuman *spouse) {
    assert(human);
    
    if (ANSGetHumanSpouse(human) != human) {
        human->_spouse = spouse;
    }
}

void ANSSetHumanSpouse(ANSHuman *human, ANSHuman *spouse) {
    assert(ANSGetHumanGender(human) != ANSGenderNotDefined);
    if (ANSGetHumanGender(human) == ANSGenderMale) {
        ANSSetStrongSpouse(human, spouse);
    } else {
        ANSSetWeakSpouse(human, spouse);
    }
}
// ___________________Set Paranats________________________
void ANSSetChildMother(ANSHuman *child, ANSHuman *mother) {
    assert(child);
    
    if (ANSGetHumanMother(child) != mother) {
        child->_mother = mother;
    }
}

void ANSSetChildFather(ANSHuman *child, ANSHuman *father) {
    assert(child);
    
    if (ANSGetHumanFather(child) != father) {
        child->_father = father;
    }
}

void ANSSetChildParent(ANSHuman *child, ANSHuman *parent) {
    assert(child);

     if (ANSGetHumanGender(parent) == ANSGenderMale) {
        ANSSetChildFather(child, parent);
    } else {
        ANSSetChildMother(child, parent);
    }
}
#pragma mark -
#pragma mark Set/RemoveChild

void ANSSetChildOfIndex(ANSHuman *human, ANSHuman *child, short index) {
    assert(human);
    
    human->_children[index] = child;
}

void ANSSetChildrenCount(ANSHuman *human, short count) {
    assert(human);
    
    human->_childrenCount += count;
}

void ANSSetHumanChild(ANSHuman *human, ANSHuman *child) {
    for (short index = 0; index < ANSHumanChildrenCount; index ++) {
        if (ANSGetChildOfIndex (human, index) != NULL) {
            continue;
        } else {
            ANSSetChildOfIndex(human, child, index);
            ANSObjectRetain(child);
            break;
        }
    }
}
// (remove  child from human and return his index)
short ANSRemoveChildReturnItsIndex(ANSHuman *human, ANSHuman *child) {
    for (short index = 0; index < ANSHumanChildrenCount; index++) {
        if (ANSGetChildOfIndex(human, index) == child) {
            ANSSetChildOfIndex(human, NULL, index);
            ANSObjectRelease(child);
            ANSSetChildrenCount(human, -1);
            return index;
        } else {
            continue;
        }
    }
    
    return 0; // правильно ли это?
}

void ANSRemoveAllChildren(ANSHuman *parent) {
    assert(parent);
    for (short index = 0; index < ANSHumanChildrenCount; index++) {
        ANSHuman *child = ANSGetChildOfIndex(parent, index);
        if (child != NULL) {
            ANSSetChildParent(child, NULL);
            ANSObjectRelease(child);
            ANSSetChildOfIndex(parent, NULL, index);
            ANSSetChildrenCount(parent, -1);
        }
    }
}

#pragma mark -
#pragma mark accessory functions

bool ANSAreHumanAndSpouseMaried(ANSHuman *human, ANSHuman *spouse) {
    return ((ANSGetHumanSpouse(human) == spouse) && (ANSGetHumanSpouse(spouse) == human));
}

bool ANSHumanCanGetMarried(ANSHuman *human, ANSHuman *spouse) {
    return ANSGetHumanGender(human) != ANSGetHumanGender(spouse);
}

//reorder children in human
void ANSReorderChildrenInHuman(ANSHuman *human, short indexOfRemovedChild) {
    for (short index = ANSHumanChildrenCount - 1; index >= 0; index--) {
        if (ANSGetChildOfIndex(human, index) != NULL || index == indexOfRemovedChild + 1) {
            ANSHuman *child = ANSGetChildOfIndex(human, index);
            ANSSetChildOfIndex(human, child, indexOfRemovedChild);
            ANSSetChildOfIndex(human, NULL, index);
            puts("Successful reordering!");
            break;
        } else {
           continue;
        }
    }
}
