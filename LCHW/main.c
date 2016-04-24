//
//  main.c
//  LCHW
//
//  Created by Nikola Andriiev on 07.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include <stdio.h>
#include <assert.h>

#include "ANSHuman.h"
#include "ANSObject.h"

int main(int argc, const char * argv[]) {
    
    ANSHuman *Man = ANSObjectCreateOfType(ANSHuman);
    ANSSetGender(Man, ANSGenderMale);
    ANSSetName(Man, "Nick");
    ANSSetAge(Man, 27);
    
    ANSHuman *Female = ANSObjectCreateOfType(ANSHuman);
    ANSSetGender(Female, ANSGenderFemale);
    ANSSetName(Female, "Julia");
    ANSSetAge(Female, 25);
    
    ANSHumanAndSpouseGetMarried(Female, Man);
    
    
    
    
    return 0;
}
