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

static const unsigned short ANSHumanChildrenCount = 20;

typedef enum {
    ANSGenderNotDefined,
    ANSGenderMale,
    ANSGenderFemale
} ANSGender;

typedef struct ANSHuman ANSHuman;
struct ANSHuman {
    ANSObject _super;
    char *_name;
    unsigned short _age;
    ANSGender _gender;
    
    unsigned short _childrenCount;
    
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
void ANSHumanSetName(ANSHuman *human, char* name);

extern
char *ANSHumanGetName(ANSHuman *human);

extern
void ANSHumanSetAge(ANSHuman *human, unsigned short _age);

extern
unsigned short ANSHumanGetAge(ANSHuman *human);

extern
void ANSHumanSetGender(ANSHuman *human, ANSGender gender);

extern
ANSGender ANSHumanGetGender(ANSHuman *human);

extern
unsigned short ANSGetChildrenCount(ANSHuman *child);

extern
ANSHuman *ANSHumanGetSpouse(ANSHuman *human);

extern
ANSHuman *ANSHumanGetMother(ANSHuman *human);

extern
ANSHuman *ANSHumanGetFather(ANSHuman *human);

extern
ANSHuman *ANSGetChildOfIndex(ANSHuman *human, unsigned short index);

extern
void ANSHumanGetMarriedWithSpouse(ANSHuman *human, ANSHuman *spouse);

extern
void ANSHumanGetDivorsedWithSpouse(ANSHuman *human);

extern
ANSHuman *ANSParentsCreateChild(ANSHuman *parant);

extern
void ANSRemoveChildFromParents(ANSHuman *child);


#endif /* ANSHuman_h */
