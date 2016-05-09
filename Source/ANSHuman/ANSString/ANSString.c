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

size_t ANSStringGetStringLength(char *string);

void __ANSStringDeallocate(void *object) {
    ANSStringSetString(object, NULL);
    
    __ANSObjectDeallocate(object);
}

ANSString* ANSStringCreateString(void) {
    ANSString *string = ANSObjectCreateWithType(ANSString);
    
    return string;
}

void ANSStringSetString(ANSString *string, char *value) {
    
    if (string->_value != value) {
        if (string->_value) {
            free(string->_value);
            string->_value = NULL;
        }
        
        if (value) {
            size_t fieldSize = ANSStringGetStringLength(value) + 1;
            string->_value = malloc(fieldSize);
            string->_value = strdup(value);
        }
    }
}

char *ANSStringGetString(ANSString *string) {
    assert(string);
    
    return string->_value;
}

size_t ANSStringGetStringLength(char *string) {
    assert(string);
    
    return strlen(string);
}
