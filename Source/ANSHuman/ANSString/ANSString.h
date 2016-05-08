//
//  ANSString.h
//  LCHW
//
//  Created by Nikola Andriiev on 08.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#ifndef ANSString_h
#define ANSString_h

#include "ANSObject.h"

typedef struct ANSString ANSString;
struct ANSString {
    ANSObject _super;
    
    char *value;
};

void __ANSStringDeallocate(void *string); 

ANSString* ANSCreateString(void);

void ANSStringSetString(ANSString string, char *value);

char *ANSStringGetString(ANSString string);



#endif /* ANSString_h */
