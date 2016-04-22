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

#include "ANSHuman.h"

#pragma mark -
#pragma mark privat methods

static
void ANSSetChildrenCount(ANSHuman *human, uint8_t childrenCount);
uint8_t ANSGetChildrenCount(ANSHuman *human);

static
void ANSSetSpouse(ANSHuman *human, ANSHuman *spouse);
static
ANSHuman *ANSGetSpouse(ANSHuman *human);

static
void ANSSetMother(ANSHuman *human, ANSHuman *mother);
static
ANSHuman *ANSGetMother(ANSHuman *human);

static
void ANSSetFather(ANSHuman *human, ANSHuman *father);
static
ANSHuman *ANSGetFather(ANSHuman *human);

#pragma mark -
#pragma mark Public implementation

void ANSHumanDeallocate(ANSHuman *human) {
    ANSSetName(human, NULL);
    ANSSetSpouse(human, NULL);
    ANSSetMother(human, NULL);
    ANSSetFather(human, NULL);
    
    free(human);
}

ANSHuman *ANSCreateHuman(void) {
    ANSHuman *human = calloc(1, sizeof(ANSHuman)); 
    if (NULL == human) {
        return NULL;
    }
    
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
void ANSSetSpouse(ANSHuman *human, ANSHuman *spouse) {
    if (NULL != human) {
        if (human->_spouse) {
      //    ASNObjectReleace (human->_spouse); //метод развладеть объектом. (forvard method)
            human->_spouse = NULL;
        }
        
        human->_spouse = spouse;
     //   ANSObjectRetain(human);// метод завладеть объектом.,
    }
        
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
