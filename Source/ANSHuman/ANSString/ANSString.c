//
//  ANSString.c
//  LCHW
//
//  Created by Nikola Andriiev on 08.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#include <string.h>
#include <assert.h>

#include "ANSString.h"

void __ANSStringDeallocate(void *string) {
    
    __ANSObjectDeallocate(string);
}

ANSString* ANSCreateString(void) {
    ANSString *string = ANSObjectCreateWithType(ANSString);
    
    return string;
}

void ANSStringSetString(ANSString string, char *value) {
    
}

char *ANSStringGetString(ANSString string);