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
    
    ANSHuman *human = ANSObjectCreateOfType(ANSHuman);
    ANSObjectRetain(human);
    assert(NULL != human);
    assert(2 == ANSObjectGetRetainCount(human));
    ANSObjectReleace(human);
    
    return 0;
}
