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

const int ANSHumanChildrenCount = 20;

typedef enum {
    ANSGenderNotDefined,
    ANSGenderMale,
    ANSGenderFemale
} ANSGender;

typedef struct ANSHuman ANSHuman;
struct ANSHuman {
    char *_name;
    uint8_t _age;
    ANSGender _gender;
    
    uint8_t _childrenCount;
    
    ANSHuman *_spouse;
    ANSHuman *_mother;
    ANSHuman *_father;
    
    ANSHuman *_children[ANSHumanChildrenCount];
};

// dealloc object on heap
extern
void ANSHumanDeallocate(ANSHuman *human);

// alloc => init object on heap
extern
ANSHuman *ANSCreateHuman(void);

// setter/ getter-> name
extern
void ANSSetName(ANSHuman *human, char* name);
extern
char *ANSGetName(ANSHuman *human);

// setter/ getter-> age
extern
void ANSSetAge(ANSHuman *human, uint8_t _age);
extern
uint8_t ANSGetAge(ANSHuman *human);

// setter/ getter-> gender
extern
void ANSSetGender(ANSHuman *human, ANSGender gender);
extern
ANSGender ANSGetGender(ANSHuman *human);



#endif /* ANSHuman_h */
