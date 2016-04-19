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

typedef enum {
    ANSGenderMale,
    ANSGenderFemale
} ANSGender;

typedef struct ANSHuman ANSHuman;
struct ANSHuman {
    char* _name;
    uint8_t _age;
    ANSGender _gender;
    uint8_t _amountOfChildren;
    bool _isMaried;
    ANSHuman *spouse;
    ANSHuman *parant;
    void *children[20];
};
typedef struct ANSHuman ANSHuman;

#endif /* ANSHumanTest_h */
