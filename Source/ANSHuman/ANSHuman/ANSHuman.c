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
void ANSChildSetParent(ANSHuman *child, ANSHuman *value, ANSGender parentGender);

static
void ANSHumanChildrenCountAddValue(ANSHuman *human, unsigned short count);

static
void ANSHumanSetChildAtIndex(ANSHuman *human, ANSHuman *child, unsigned short index);

static
void ANSHumanAddChild(ANSHuman *human, ANSHuman *child);

static
void ANSHumanAppendChild(ANSHuman *human, ANSHuman *child);

static
void ANSRemoveAllChildren(ANSHuman *parent);

static
bool ANSHumanCanGetMarried(ANSHuman *human, ANSHuman *spouse);

static
void ANSHumanReorderChildren(ANSHuman *human);

#pragma mark -
#pragma mark Public implementation

void __ANSHumanDeallocate(void *human) {
    ANSHumanDivorce(human);
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
    assert(human);
    
    if (human->_name != name) {
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
    assert(human);
    
    return human->_name;
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
    assert(human);
    
    return human->_spouse;
}

ANSHuman *ANSChildGetMother(ANSHuman *child) {
    assert(child);
    
    return child->_mother;
}

ANSHuman *ANSChildGetFather(ANSHuman *child) {
    assert(child);
    
    return child->_father;
}

ANSHuman *ANSHumanGetChildAtIndex(ANSHuman *human, unsigned short index) {
    assert(human);
    
    return human->_children[index];
}

unsigned short ANSHumanGetIndexOfChild(ANSHuman *human, ANSHuman *child) {
    assert(human);
    
    for (unsigned short index = 0; index < ANSHumanChildrenCount; index +=1) {
        if (ANSHumanGetChildAtIndex(human, index) == child) {
            return index;
        }
    }
    
    return kANSIndexNotFound;
}

unsigned short ANSHumanGetChildrenCount(ANSHuman *human) {
    assert(human);
    
    return human->_childrenCount;
}
//___________________Get married/ GetDivorsed__________________________
void ANSHumanGetMarriedWithSpouse(ANSHuman *human, ANSHuman *spouse) {
    bool status = ANSHumanCanGetMarried(human, spouse);
    assert(status);

    ANSHumanDivorce(human);
    ANSHumanDivorce(spouse);
    
    ANSHumanSetSpouse(human, spouse);
    ANSHumanSetSpouse(spouse, human);
    puts("successful marriage!");
}

void ANSHumanDivorce(ANSHuman *human) {
    ANSHuman *partner = ANSHumanGetSpouse(human);
    if (partner) {
        ANSHumanSetSpouse(partner, NULL);
        ANSHumanSetSpouse(human, NULL);
    }
    
        puts("successful divorse!");
}

void ANSHumanAddChild(ANSHuman *human, ANSHuman *child) {
    ANSHumanAppendChild(human, child);
    ANSHumanChildrenCountAddValue(human, 1);
    ANSChildSetParent(child, human, ANSHumanGetGender(human));
}

ANSHuman *ANSHumanCreateChild(ANSHuman *human) {
    assert(ANSHumanGetChildrenCount(human) < ANSHumanChildrenCount - 1);

    ANSHuman *spouse = ANSHumanGetSpouse(human);
    ANSHuman *child = ANSObjectCreateWithType(ANSHuman);
    assert(child);

    ANSHumanAddChild(human, child);
    ANSHumanAddChild(spouse, child);

return child;
}

#pragma mark -
#pragma mark Privat implementation

//_____________________Set partner___________________________
void ANSHumanSetStrongSpouse(ANSHuman *human, ANSHuman *spouse) {
    assert(human && ANSHumanGetSpouse(human) != spouse);
    
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
    assert(human);
    
    if (ANSHumanGetGender(human) == ANSGenderMale) {
        ANSHumanSetStrongSpouse(human, spouse);
    } else {
        ANSHumanSetWeakSpouse(human, spouse);
    }
}

#pragma mark -
#pragma mark set/remove parents

void ANSChildSetMother(ANSHuman *child, ANSHuman *mother) {
    assert(child);
    
    if (child->_mother != mother) {
        child->_mother = mother;
    }
}

void ANSChildSetFather(ANSHuman *child, ANSHuman *father) {
    assert(child);
    
    if (child->_father != father) {
        child->_father = father;
    }
}

void ANSChildSetParent(ANSHuman *child, ANSHuman *value, ANSGender parentGender) {
    assert(parentGender != ANSGenderUndefined);
    
    if (parentGender == ANSGenderMale) {
        ANSChildSetFather(child, value);
    } else {
        ANSChildSetMother(child, value);
    }
}

#pragma mark -
#pragma mark Set/RemoveChild

void ANSHumanChildrenCountAddValue(ANSHuman *human, unsigned short count) {
    assert(human);
    
    human->_childrenCount += count;
}

void ANSHumanSetChildAtIndex(ANSHuman *human, ANSHuman *child, unsigned short index) {
    assert(human);
    
    if (ANSHumanGetChildAtIndex(human, index) != child) {
        ANSObjectRelease(human->_children[index]);
        human->_children[index] = child;
        ANSObjectRetain(child);
    }
}

void ANSHumanAppendChild(ANSHuman *human, ANSHuman *child) {
    unsigned short indexOfChild = ANSHumanGetChildrenCount(human);
    ANSHumanSetChildAtIndex(human, child, indexOfChild);
}

void ANSRemoveChildFromParent(ANSHuman *human, ANSHuman *child) {
    ANSChildSetParent(child, NULL, ANSHumanGetGender(human));
    unsigned short indexOfChild = ANSHumanGetIndexOfChild(human, child);
    ANSHumanSetChildAtIndex(human, NULL, indexOfChild);
    ANSHumanChildrenCountAddValue(human, -1);
    ANSHumanReorderChildren(human);
}

void ANSRemoveAllChildren(ANSHuman *parent) {
    assert(parent);
    
    for (unsigned short index = 0; index < ANSHumanChildrenCount; index++) {
        ANSHuman *child = ANSHumanGetChildAtIndex(parent, index);
        if (child != NULL) {
            ANSChildSetParent(child, NULL, ANSHumanGetGender(parent));
            ANSHumanSetChildAtIndex(parent, NULL, index);
            ANSHumanChildrenCountAddValue(parent, -1);
        }
    }
}

#pragma mark -
#pragma mark Accessorial methods

bool ANSHumanCanGetMarried(ANSHuman *human, ANSHuman *spouse) {
    return ANSHumanGetGender(human) != ANSHumanGetGender(spouse);
}

void ANSHumanReorderChildren(ANSHuman *human) {
    assert(human);
    
    unsigned short indexOfNull = ANSHumanGetIndexOfChild(human, NULL);
    unsigned short indexOfLastValue = ANSHumanGetChildrenCount(human);
    if (indexOfNull < indexOfLastValue) {
        ANSHuman *child = ANSHumanGetChildAtIndex(human, indexOfLastValue);
        ANSHumanSetChildAtIndex(human, child, indexOfNull);
        ANSHumanSetChildAtIndex(human, NULL, indexOfLastValue);
    }
}

