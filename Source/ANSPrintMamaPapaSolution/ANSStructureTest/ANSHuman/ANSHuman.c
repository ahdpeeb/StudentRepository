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

static
void ANSSetChildrenCount(ANSHuman *human, uint8_t childrenCount);
static
uint8_t ANSGetChildrenCount(ANSHuman *human);

static
void ANSSetStrongSpouse (ANSHuman *human, ANSHuman *spouse); // strong partner. 1 LVL
static
void ANSSetWeakSpouse (ANSHuman *human, ANSHuman *spouse); // weak partner 1 LVL
static
void ANSSetSpouse(ANSHuman *human, ANSHuman *spouse); // 2 LVL

static
void ANSSetMother(ANSHuman *human, ANSHuman *mother); // 1 LVL
static
ANSHuman *ANSGetMother(ANSHuman *human); // 1 LVL

static
void ANSSetFather(ANSHuman *human, ANSHuman *father); // 1 LVL
static
ANSHuman *ANSGetFather(ANSHuman *human); // 1 LVL

#pragma mark -
#pragma mark Public implementation

void __ANSHumanDeallocate(void *human) {
    ANSSetName(human, NULL);
    ANSSetSpouse(human, NULL);
    ANSSetMother(human, NULL);
    ANSSetFather(human, NULL);
    
    __ANSObjectDeallocate(human);
}

ANSHuman *ANSCreateHuman(void) {
    ANSHuman *human = ANSObjectCreateOfType(ANSHuman);
    
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
        printf("lesbians or gays \n");
        exit(1);
    }
    
    ANSSetSpouse(human, spouse);
    char consoleString [256];
    printf("Will you marry me!? YES ? \n");
    fgets(consoleString, 256, stdin);
    if (strncmp(consoleString, "YES", 3) == 0) {
        ANSSetSpouse(spouse, human);
        printf("successful marriage! \n");
    } else {
        printf("She refused! \n");
        exit(1);
    }
}

void ANSHumanAndSpouseGetDivorsed(ANSHuman *human, ANSHuman *spouse) {
    if ((ANSGetSpouse(human) != spouse) || (ANSGetSpouse(spouse) != human)) {
        exit(1);
    }
    
    spouse->_spouse = NULL;
    ANSObjectReleace(human->_spouse);
    human->_spouse = NULL;
    printf("successful divorse");
}

#pragma mark -
#pragma mark Privat implementation
//______________________________ChildrenCount_____________________________________
void ANSSetChildrenCount(ANSHuman *human, uint8_t childrenCount) {
    if (NULL == human) {
        exit(1);
    }
    
    human->_childrenCount = childrenCount;
}

uint8_t ANSGetChildrenCount(ANSHuman *human) {
    return human->_childrenCount;
}
//___________________________________spouse_________________________________________

static
void ANSSetStrongSpouse(ANSHuman *human, ANSHuman *spouse) {
    if (NULL == human || NULL == spouse) {
        exit(1);
    }
    
    if (ANSGetSpouse(human) == NULL) {
        human->_spouse = spouse;
        ANSObjectRetain(human->_spouse); // корректно ли писать просто spouse?
    } else {
        ANSObjectReleace(human->_spouse);
        human->_spouse = spouse;
        ANSObjectRetain(human->_spouse);
    }
}
static
void ANSSetWeakSpouse (ANSHuman *human, ANSHuman *spouse) {
    if (NULL == human || NULL == spouse) {
        exit(1);
    }
    
    human->_spouse = spouse;
}

void ANSSetSpouse(ANSHuman *human, ANSHuman *spouse) {
    if (NULL == human || NULL == spouse) {
        exit(1);
    }
    
    (human->_gender == ANSGenderMale) ? ANSSetStrongSpouse(human, spouse)
        : ANSSetWeakSpouse(human, spouse);
}

ANSHuman *ANSGetSpouse(ANSHuman *human) {
    return (NULL == human) ? NULL : human->_spouse;
}

//______________________________Mother__________________________________________
void ANSSetMother(ANSHuman *human, ANSHuman *mother) {
    if (NULL == human) {
        exit(1);
    }
    
    human->_mother = mother;
}

ANSHuman *ANSGetMother(ANSHuman *human) {
    return human->_mother;
}
//______________________________Father__________________________________________
void ANSSetFather(ANSHuman *human, ANSHuman *father) {
    if (NULL == human) {
        exit(1);
    }
    
    human->_father = father;
}

ANSHuman *ANSGetFather(ANSHuman *human) {
    return human->_father;
}
//______________________________ANSSetChildren___________________________________
// полодижить в массив, детей. при удалении детей не должно быть дырок.(если убрать детей по индексу не должно быть смещений)
void ANSSetChildren(ANSHuman *human, ANSHuman *children[ANSHumanChildrenCount]) {
    human->_children[ANSHumanChildrenCount] = children[ANSHumanChildrenCount];
}

ANSHuman *ANSGetChildren(ANSHuman *human) {
    return human->_children[ANSHumanChildrenCount];
}

