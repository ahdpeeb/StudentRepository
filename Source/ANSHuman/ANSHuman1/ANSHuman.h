//
//  ANSHumanTest.h
//  LCHW
//
//  Created by Nikola Andriiev on 19.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#ifndef ANSHuman_h
#define ANSHuman_h

#include <stdbool.h>
#include <string.h>

#include "ANSObject.h"

static const uint8_t ANSHumanChildrenCount = 20;

typedef enum {
    ANSGenderNotDefined,
    ANSGenderMale,
    ANSGenderFemale
} ANSGender;

typedef struct ANSHuman ANSHuman;
struct ANSHuman {
    ANSObject _super;
    char *_name;
    uint8_t _age;
    ANSGender _gender;
    
    uint8_t _childrenCount;
    
    ANSHuman *_spouse;
    ANSHuman *_mother;
    ANSHuman *_father;
    
    ANSHuman *_children[ANSHumanChildrenCount];
};

extern
void __ANSHumanDeallocate(void *human);

extern
ANSHuman *ANSCreateHuman(void);

extern
void ANSSetHumanName(ANSHuman *human, char* name);

extern
char *ANSGetHumanName(ANSHuman *human);

extern
void ANSSetHumanAge(ANSHuman *human, int _age);

extern
int ANSGetHumanAge(ANSHuman *human);

extern
void ANSSetHumanGender(ANSHuman *human, ANSGender gender);

extern
ANSGender ANSGetHumanGender(ANSHuman *human);

extern
int ANSGetChildrenCount(ANSHuman *child);

extern
ANSHuman *ANSGetHumanSpouse(ANSHuman *human);

extern
ANSHuman *ANSGetHumanMother(ANSHuman *human);

extern
ANSHuman *ANSGetHumanFather(ANSHuman *human);

extern
ANSHuman *ANSGetChildOfIndex(ANSHuman *human, int index);

extern
void ANSHumanGetMarriedWithSpouse(ANSHuman *human, ANSHuman *spouse);

extern
void ANSHumanGetDivorsedWithSpouse(ANSHuman *human);

extern
ANSHuman *ANSParentsCreateChild(ANSHuman *parant);

extern
void ANSRemoveChildFromParents(ANSHuman *child);

#endif /* ANSHuman_h */
