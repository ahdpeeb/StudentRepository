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
    ANSMamaCondition = 1,
    ANSPapaCondition = 2,
    ANSMamaPapaCondition = 3,
    ANSBlankCondition = 4,
}ANSConditions;

void ANSPrintMamaPapaShortSolution(int value);

void ANSPrintDefinedCondition(int value);

void ANSPrintDefinedCondition2(int value);

#endif /* ANSPrintMamaPapaSoluiton_h */
