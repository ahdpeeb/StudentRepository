//
//  ANSHumanTest.h
//  LCHW
//
//  Created by Nikola Andriiev on 19.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//
// нельзя использовать нижнее подчеркивание
#ifndef ANSHuman_h
#define ANSHuman_h

#include <stdbool.h>
#include <string.h>

const int ASNHumanChildrenCount = 20;
typedef enum {
    ANSGenderMale,
    ANSGenderFemale,
    ANSGenderNotDefined
} ANSGender;

typedef struct ANSHuman ANSHuman;
struct ANSHuman {
    char *_name;
    uint8_t _age;
    ANSGender _gender;
    
    uint8_t _childrenCount;
    bool _maried; // убрать
    
    ANSHuman *_spouse;
    ANSHuman *_mother;
    ANSHuman *_father;
    
    ANSHuman *_children[ASNHumanChildrenCount];
};

// dealloc object on heap
void ANSHumanDeallocate(ANSHuman *human);

// alloc => init object on heap
ANSHuman *ANSCreateHuman(void);

// setter/ getter-> name
void ASNSetName(ANSHuman *human, char* name);
char *ASNGetName(ANSHuman *human);

// setter/ getter-> age
void ASNSetAge(ANSHuman *human, uint8_t _age);
uint8_t ASNGetAge(ANSHuman *human);

// setter/ getter-> gender
void ASNSetGender(ANSHuman *human, ANSGender gender);
ANSGender ASN_GetGender(ANSHuman *human);
// приватный метод
// setter/ getter-> childrenCount
void ASNSetChildrenCount(ANSHuman *human, uint8_t childrenCount);
uint8_t ASNGetChildrenCount(ANSHuman *human);

// setter/ getter-> spouse
void ASNSetSpouse(ANSHuman *human, ANSHuman *spouse);
ANSHuman *ASNGetSpouse(ANSHuman *human);

// setter/ getter-> mother
void ASNSetMother(ANSHuman *human, ANSHuman *mother);
ANSHuman *ASNGetMother(ANSHuman *human);

// setter/ getter-> father
void ASNSetFather(ANSHuman *human, ANSHuman *father);
ANSHuman *ASNGetFather(ANSHuman *human);

#endif /* ANSHuman_h */
