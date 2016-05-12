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
    
    char *_value;
};

extern
ANSString *ASNReturnStringCopy(char *value);

extern
void __ANSStringDeallocate(void *object);

extern
ANSString* ANSStringCreate(void);

extern
size_t ANSStringGetStringLength(char *string);

extern
char *ANSStringGetString(ANSString *string);

#endif /* ANSString_h */
