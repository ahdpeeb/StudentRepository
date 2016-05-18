//
//  IDPAutoreleasingStack.h
//  LCHW
//
//  Created by Nikola Andriiev on 17.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#ifndef IDPAutoreleasingStack_h
#define IDPAutoreleasingStack_h

#include <stdbool.h>

#include "ANSObject.h"

typedef struct ANSAutoreleasingStack ANSAutoreleasingStack;
struct ANSAutoreleasingStack {
    ANSObject _super;
    
    void *_head;
    size_t _size;
    void **_data;
};

typedef enum ANSAutoreleasingStackType ANSAutoreleasingStackType;
enum ANSAutoreleasingStackType {
    ANSAutoreleasingStackTypeNull,
    ANSAutoreleasingStackTypeObject,
};

extern
ANSAutoreleasingStack *ANSAutoreleasingStackCreateWithSize(size_t size);

extern
bool ANSAutoreleasingStackIsEmpty(ANSAutoreleasingStack *stack);

extern
bool ANSAutoreleasingStackIsFull(ANSAutoreleasingStack *stack);

extern
void ANSAutoreleasingStackPushObject(ANSAutoreleasingStack *stack, void *object);

extern
ANSAutoreleasingStackType ANSAutoreleasingStackPopObject(ANSAutoreleasingStack *stact);

extern
void ANSAutoreleasingStackPopAllObjects(ANSAutoreleasingStack *stack);

#endif /* IDPAutoreleasingStack_h */
