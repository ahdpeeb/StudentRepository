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
    
    void **_data; 
    void *_head;
    
};

typedef enum ANSAutoreleasingStackType ANSAutoreleasingStackType;
enum ANSAutoreleasingStackType {
    ANSAutoreleasingStackNull,
    ANSAutoreleasingStackObject,
};

extern
ANSAutoreleasingStack *ANSAutoreleasingStackCreateWithSize(size_t size);

extern
bool ANSAutoreleasingStackIsEmpty(ANSAutoreleasingStack *stack);

extern
bool ANSAutoreleasingStackIsFull(ANSAutoreleasingStack *stack);

extern
void ANSAutoreleasingStackPushObject(ANSAutoreleasingStack *stack);

extern
void ANSAutoreleasingStackPullObject(ANSAutoreleasingStack *stack, void *object);

extern
void ANSAutoreleasingStackPullAllObjects(ANSAutoreleasingStack *stack, void *object);

#endif /* IDPAutoreleasingStack_h */
