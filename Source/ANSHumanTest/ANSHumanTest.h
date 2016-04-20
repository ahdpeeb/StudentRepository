//
//  ANSHumanTest.h
//  LCHW
//
//  Created by Nikola Andriiev on 19.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#ifndef ANSHumanTest_h
#define ANSHumanTest_h

#include <stdbool.h>
#include <string.h>

const int ASNHumanChildrenCount = 20;

typedef enum {
    ANSGenderMale,
    ANSGenderFemale
} ANSGender;

typedef struct ANSHuman ANSHuman;
struct ANSHuman {
    char* _name;
    uint8_t _age;
    ANSGender _gender;
    
    uint8_t _childrenCount;
    bool _maried;
    
    ANSHuman *_spouse;
    ANSHuman *_mother;
    ANSHuman *_father;

    ANSHuman *_children[ASNHumanChildrenCount];
};


#endif /* ANSHumanTest_h */
