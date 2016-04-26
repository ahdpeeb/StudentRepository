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
void ANSSetName(ANSHuman *human, char* name);
extern
char *ANSGetName(ANSHuman *human);

extern
void ANSSetAge(ANSHuman *human, uint8_t _age);
extern
uint8_t ANSGetAge(ANSHuman *human);

extern
void ANSSetGender(ANSHuman *human, ANSGender gender);
extern
ANSGender ANSGetGender(ANSHuman *human);

extern
uint8_t ANSGetChildrenCount(ANSHuman *human); // 1 LVL

extern
ANSHuman *ANSGetSpouse(ANSHuman *human); // 1 lvl

extern
ANSHuman *ANSGetMother(ANSHuman *human); // 1 LVL
extern
ANSHuman *ANSGetFather(ANSHuman *human); // 1 LVL

extern
void ANSParantsGotChild(ANSHuman *Papa, ANSHuman *Mama, ANSHuman *child);  // 3 LVL

extern
void ANSHumanAndSpouseGetMarried(ANSHuman *human, ANSHuman *spouse); // 3 LVL

extern
void ANSHumanAndSpouseGetDivorsed(ANSHuman *human, ANSHuman *spouse); // 3 LVL

extern
void ANSKillChild(ANSHuman *child); // 3 LVL

#endif /* ANSHuman_h */
