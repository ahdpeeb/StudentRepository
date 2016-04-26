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
void ANSSetStrongSpouse (ANSHuman *human, ANSHuman *spouse); //  1 LVL

static
void ANSSetWeakSpouse (ANSHuman *human, ANSHuman *spouse); // 1 LVL

static
void ANSSetSpouse(ANSHuman *human, ANSHuman *spouse); // 2 LVL

static
void ANSSetParent(ANSHuman *child, ANSHuman *parent); // 1 LVL

static
void ANSSetChildren(ANSHuman *human, ANSHuman *child);

static
void ANSRemoveChildFromParent (ANSHuman *parent, ANSHuman *child); // 2 lvl

static
bool ANSAreTheyMaried(ANSHuman *human, ANSHuman *spouse);

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
    assert(human || spouse);
    if (ANSAreTheyMaried(human, spouse)) {
        ANSSetSpouse(human, spouse);
        ANSSetSpouse(spouse, human);
    } else {
        exit(1);
    }
}

void ANSHumanAndSpouseGetDivorsed(ANSHuman *human, ANSHuman *spouse) {
    // развести по одному родителю.
    if ((ANSGetSpouse(human) != spouse) || (ANSGetSpouse(spouse) != human)) {
        puts("something is wrong");
        exit(1);
    }
    
    spouse->_spouse = NULL;
    ANSObjectRelease(human->_spouse);
    human->_spouse = NULL;
    puts("successful divorse!");
}

void ANSKillChild(ANSHuman *child) {
    if (NULL == child) {
        exit(1);
    }
    
    ANSHuman *mother = ANSGetMother(child);
    ANSHuman *father = ANSGetFather(child);
    child->_mother = NULL;
    child->_father = NULL;
    ANSRemoveChildFromParent(mother, child);
    ANSRemoveChildFromParent(father, child);
}

void ANSParentsGotChild(ANSHuman *human, ANSHuman *spouse, ANSHuman *child) {
    if ((ANSGetSpouse(human) != spouse) || (ANSGetSpouse(spouse) != human)) {
        puts("it seems they are not married");
        exit(1);
    }
    
    ANSSetChildren(human, child);
    ANSSetChildren(spouse, child);
    ANSSetParent(child, human);
    ANSSetParent(child, spouse);
    printf("They got a child successfully, her name %s \n", ANSGetName(child));
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

ANSHuman *ANSGetChildren(ANSHuman *human, uint8_t index) {
    return human->_children[index];
}

uint8_t ANSGetChildrenCount(ANSHuman *human) {
    return human->_childrenCount;
}

#pragma mark -
#pragma mark Privat implementation

//___________________________________SetSpouse_________________________________________

static
void ANSSetStrongSpouse(ANSHuman *human, ANSHuman *spouse) {
    if (NULL == human || human->_spouse == spouse) {
        exit(1);
    }
    
    if (ANSGetSpouse(human) == NULL) {
        human->_spouse = spouse;
        ANSObjectRetain(spouse);
    } else {
        ANSObjectRelease
        (human->_spouse);
        human->_spouse = spouse;
        ANSObjectRetain(spouse);
    }
}

void ANSSetWeakSpouse (ANSHuman *human, ANSHuman *spouse) {
    if (NULL == human || human->_spouse == spouse) {
        exit(1);
    }
    
    human->_spouse = spouse;
}

void ANSSetSpouse(ANSHuman *human, ANSHuman *spouse) {    
    (human->_gender == ANSGenderMale) ? ANSSetStrongSpouse(human, spouse)
        : ANSSetWeakSpouse(human, spouse);
}

//______________________________SetParent_____________________________________
void ANSSetParent(ANSHuman *child, ANSHuman *parent) {
    if (NULL == child || ANSGetGender(parent) == ANSGenderNotDefined) {
        exit(1);
    }
    
    if (NULL == parent) {
            child->_father = NULL;
            child->_mother = NULL;
    } else if (ANSGetGender(parent) == ANSGenderMale) {
        child->_father = parent;
    } else { child->_mother = parent;
    }
}

//______________________________ANSSet/Remove___________________________________

void ANSSetChildren(ANSHuman *human, ANSHuman *child) {
    if (NULL == human || human == child) {
        exit(1);
    }
    
    for (int index = 0; index < ANSHumanChildrenCount; index ++) {
        if (human->_children[index] != NULL) {
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
    if (NULL == parent) {
        exit(1);
    }
    
    for (int index = 0; index < ANSHumanChildrenCount; index++) {
        if (parent->_children[index] == child) {
            ANSObjectRelease(child);
            parent->_children[index] = NULL;
            parent->_childrenCount--;
            parent->_children[index] = parent->_children[index + 1];
            parent->_children[index + 1] = NULL;
        } else {
            continue;
        }
    }
}

// метод возвращает женаты они или неm? да или нет
bool ANSAreTheyMaried(ANSHuman *human, ANSHuman *spouse) {
    bool boolValue = ((ANSGetSpouse(human) != spouse) || (ANSGetSpouse(spouse) != human)) ? true : false;
    
    return boolValue;
}

