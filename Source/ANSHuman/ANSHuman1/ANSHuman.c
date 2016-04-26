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

#include "ANSHuman.h"

#pragma mark -
#pragma mark Privat declaration

static char ANSConsoleString [256];

static
void ANSSetStrongSpouse (ANSHuman *human, ANSHuman *spouse); //  1 LVL

static
void ANSSetWeakSpouse (ANSHuman *human, ANSHuman *spouse); // 1 LVL

static
void ANSSetSpouse(ANSHuman *human, ANSHuman *spouse); // 2 LVL

static
void ANSSetParant(ANSHuman *child, ANSHuman *parant); // 1 LVL

static
void ANSSetChildren(ANSHuman *human, ANSHuman *child);

static
void ANSRemoveChildFromParant (ANSHuman *parant, ANSHuman *child); // 2 lvl

#pragma mark -
#pragma mark Public implementation

void __ANSHumanDeallocate(void *human) {
    ANSSetName(human, NULL);
    ANSSetSpouse(human, NULL);
    ANSSetParant(human, NULL);
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
    if (NULL == human) {
        exit(1);
    }
    
    human->_age = age;
}

uint8_t ANSGetAge(ANSHuman *human) {
    return (NULL == human) ? 0 : human->_age;
}

//______________________________Gender____________________________________________
void ANSSetGender(ANSHuman *human, ANSGender gender) {
    if (NULL == human) {
        exit(1);
    }
    
    human->_gender = gender;
}

ANSGender ANSGetGender(ANSHuman *human) {
    return (NULL == human) ? ANSGenderNotDefined : human->_gender; // or ANSGND = NULL
}
//_______________________________Get Married, GetDivorsed__________________________
void ANSHumanAndSpouseGetMarried(ANSHuman *human, ANSHuman *spouse) {
    if (NULL == human || NULL == spouse || ANSGetGender(human) == ANSGetGender(spouse)) {
        puts("lesbians or gays \n");
        exit(1);
    }
    
    ANSSetSpouse(human, spouse);
    puts("Will you marry me!? YES ? \n");
    fgets(ANSConsoleString, 256, stdin);
    if (strncmp(ANSConsoleString, "YES", 3) == 0) {
        ANSSetSpouse(spouse, human);
        puts("successful marriage! \n");
    } else {
        puts("She refused! \n");
        exit(1);
    }
}

void ANSHumanAndSpouseGetDivorsed(ANSHuman *human, ANSHuman *spouse) {
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
    ANSRemoveChildFromParant(mother, child);
    ANSRemoveChildFromParant(father, child);
}

void ANSParantsGotChild(ANSHuman *human, ANSHuman *spouse, ANSHuman *child) {
    if ((ANSGetSpouse(human) != spouse) || (ANSGetSpouse(spouse) != human)) {
        puts("it seems they are not married");
        exit(1);
    }
    
    ANSSetChildren(human, child);
    ANSSetChildren(spouse, child);
    ANSSetParant(child, human);
    ANSSetParant(child, spouse);
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

//______________________________SetParant_____________________________________
void ANSSetParant(ANSHuman *child, ANSHuman *parant) {
    if (NULL == child || ANSGetGender(parant) == ANSGenderNotDefined) {
        exit(1);
    }
    
    if (NULL == parant) {
            child->_father = NULL;
            child->_mother = NULL;
    } else if (ANSGetGender(parant) == ANSGenderMale) {
        child->_father = parant;
    } else { child->_mother = parant;
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

void ANSRemoveChildFromParant (ANSHuman *parant, ANSHuman *child) {
    if (NULL == parant) {
        exit(1);
    }
    
    for (int index = 0; index < ANSHumanChildrenCount; index++) {
        if (parant->_children[index] == child) {
            ANSObjectRelease(child);
            parant->_children[index] = NULL;
            parant->_childrenCount--;
            parant->_children[index] = parant->_children[index + 1];
            parant->_children[index + 1] = NULL;
        } else {
            continue;
        }
    }
}


