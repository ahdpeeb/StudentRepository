//
//  ANSPrintMamaPapaSoluiton.h
//  LCHW
//
//  Created by Nikola Andriiev on 12.04.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#ifndef ANSPrintMamaPapaSoluiton_h
#define ANSPrintMamaPapaSoluiton_h

typedef enum{
    ANSBlankCondition       = 1 << 0,
    ANSMamaCondition        = 1 << 1,
    ANSPapaCondition        = 1 << 2,
}ANSConditions;

void ANSPrintMamaPapaShortSolution(int value);

void ANSPrintDefinedCondition(int value);

void ANSPrintDefinedCondition2(int value);

#endif /* ANSPrintMamaPapaSoluiton_h */
