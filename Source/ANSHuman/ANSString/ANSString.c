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

#pragma mark -
#pragma mark forvard declaration

static
void ANSStringSetValue(ANSString *string, char *value);

#pragma mark -
#pragma mark implementation

void __ANSStringDeallocate(void *object) {
    ANSStringSetValue(object, NULL);
    
    __ANSObjectDeallocate(object);
}

ANSString* ANSStringCreate(void) {
    ANSString *string = ANSObjectCreateWithType(ANSString);
    
    return string;
}

void ANSStringSetValue(ANSString *string, char *value) {
    
    if (string->_value != value) {
        if (string->_value) {
            free(string->_value);
            string->_value = NULL;
        }
        
        if (value) {
            size_t fieldSize = ANSStringGetStringLength(value) + 1;
            string->_value = malloc(fieldSize);
            memmove(string->_value, value, fieldSize);
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

ANSString *ANSStringWithCharString(char *value) {
    ANSString *object = ANSStringCreate();
    ANSStringSetValue(object, value);
    
    return object;
}

ANSString *ASNStringCopy(ANSString *string) {
    return ANSStringWithCharString(ANSStringGetString(string));
}
