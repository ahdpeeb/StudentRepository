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
    ANSStringSetString(string, NULL);
    
    __ANSObjectDeallocate(string);
}

ANSString* ANSStringCreateString(void) {
    ANSString *string = ANSObjectCreateWithType(ANSString);
    
    return string;
}

void ANSStringSetString(ANSString *string, char *value) {
    assert(string);
    
    if (string->_value != value) {
        if (NULL != string->_value) {
            free(string->_value);
            string->_value = NULL;
        }
        
        if (value) {
            string->_value = strdup(value);
        }
    }
}

char *ANSStringGetString(ANSString *string) {
    assert(string);
    
    return string->_value;
}
