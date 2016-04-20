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
    ANSGenderFemale,
    ANSGenderNotDefined
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

// alloc => init object on heap
ANSHuman *ANSCreateHuman(void);
// setter/ getter-> name
void ASN_SetName(ANSHuman *human, char* name);
char *ASN_GetName(ANSHuman *human);

// setter/ getter-> age
void ASN_SetAge(ANSHuman *human, uint8_t _age);
uint8_t ASN_GetAge(ANSHuman *human);

// setter/ getter-> gender
void ASN_SetGender(ANSHuman *human, ANSGender gender);
ANSGender ASN_GetGender(ANSHuman *human);

// setter/ getter-> childrenCount
void ASN_SetChildrenCount(ANSHuman *human, uint8_t childrenCount);
uint8_t ASN_GetChildrenCount(ANSHuman *human);

// setter/ getter-> MariedStatus
void ASN_SetMariedStatus(ANSHuman *human, bool maried);
bool ASN_GetMariedStatus(ANSHuman *human);

// setter/ getter-> spouse
void ASN_SetSpouse(ANSHuman *human, ANSHuman *spouse);
ANSHuman* ASN_GetSpouse(ANSHuman *human);

// setter/ getter-> mother
void ASN_SetMother(ANSHuman *human, ANSHuman *mother);
ANSHuman* ASN_GetMother(ANSHuman *human);

// setter/ getter-> father
void ASN_SetFather(ANSHuman *human, ANSHuman *father);
ANSHuman* ASN_GetFather(ANSHuman *human);

// dealloc object on heap
void ANSHumanDealloc(ANSHuman *human);
#endif /* ANSHumanTest_h */
