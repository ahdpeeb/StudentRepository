//
//  ANSLinkedLisetPrivate.h
//  LCHW
//
//  Created by Nikola Andriiev on 15.05.16.
//  Copyright © 2016 Anfriiev.Mykola. All rights reserved.
//

#ifndef ANSLinkedLisetPrivate_h
#define ANSLinkedLisetPrivate_h

#include "ANSLinkedList.h"

extern
void ANSLinkedListSetHead(ANSLinkedList *list, ANSLinkedListNode *head);

extern
ANSLinkedListNode *ANSLinkedListGetHead(ANSLinkedList *list);

extern
uint64_t ANSLinkedListGetMutationsCount(ANSLinkedList *list);

extern
void ANSLinkedListSetMutationsCount(ANSLinkedList *list, uint64_t count);

extern
void ANSLinkedListMutationsCountAddValue(ANSLinkedList *list, uint64_t value);

#endif /* ANSLinkedLisetPrivate_h */
