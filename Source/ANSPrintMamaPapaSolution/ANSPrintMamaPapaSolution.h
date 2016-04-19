//
//  ANSPrintMamaPapaSoluiton.h
//  LCHW
//
//  Created by Nikola Andriiev on 12.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#ifndef ANSPrintMamaPapaSoluiton_h
#define ANSPrintMamaPapaSoluiton_h

typedef enum {
    ANSStateBlank           = 1 << 0,
    ANSStateMama            = 1 << 1,
    ANSStatePapa            = 1 << 2,
    ANSStateMamaPapa        = ANSStateMama | ANSStatePapa,
} ANSState;

void ANSPrintMamaPapaShortSolution(int value);

ANSState ANSPrintState(int value);

#endif /* ANSPrintMamaPapaSoluiton_h */
