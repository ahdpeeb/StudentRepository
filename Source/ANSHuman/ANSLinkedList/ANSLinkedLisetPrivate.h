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

typedef struct ANSLinkedListContext ANSLinkedListContext;
struct ANSLinkedListContext {
    void *previousNode;
    void *node;
    void *object;
};

typedef bool (*ANSLinkedListNodeComparisonFunction)(ANSLinkedListNode *node, ANSLinkedListContext *context);

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

extern
ANSLinkedListNode *ANSLinkedListFindNodeWithContext(ANSLinkedList *list,
                                                   ANSLinkedListNodeComparisonFunction comparator,
                                                   ANSLinkedListContext context);

extern
bool ANSLinkedListNodeContainsObject(ANSLinkedListNode *node, ANSLinkedListContext *context);

ANSLinkedListContext* ANSLinkedListContextCreateWithObject(void *object);

#endif /* ANSLinkedLisetPrivate_h */
