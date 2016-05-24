 //
//  ANSAutoreleasePool.h
//  LCHW
//
//  Created by Nikola Andriiev on 19.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#ifndef ANSAutoreleasePool_h
#define ANSAutoreleasePool_h

#include "ANSAutoreleasingStack.h"
#include "ANSLinkedList.h"

typedef struct ANSAutoreleasePool ANSAutoreleasePool;
struct ANSAutoreleasePool {
    ANSObject _super;
    
    ANSLinkedList *_list;
    uint64_t _count;
    bool _validity;
};

extern
void __ANSAutoreleasePoolDeallocate(ANSAutoreleasePool *pool);

extern
ANSAutoreleasePool *ANSAutoreleasePoolCreate(void);

extern
void ANSAutoreleasePoolAddObject(ANSAutoreleasePool *pool, void *object);

extern
void ANSAutoreleasePoolDrain();

extern
ANSAutoreleasePool* ANSAutoreleasePoolGetPool(void);

#endif /* ANSAutoreleasePool_h */
