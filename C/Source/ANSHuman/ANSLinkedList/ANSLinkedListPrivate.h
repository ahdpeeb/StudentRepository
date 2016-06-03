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
#include "ANSArray.h"

typedef struct ANSLinkedListContext ANSLinkedListContext;
struct ANSLinkedListContext {
    void *previousNode;
    void *node;
    void *object;
};

typedef bool (*ANSLinkedListNodeComparisonFunction)(ANSLinkedListNode *node, ANSLinkedListContext *context);
typedef bool (*ANSLinkedListObjectComparisonFunction)(void *object, void *context);

typedef struct ANSNodeToObjectContext ANSNodeToObjectContext;
struct ANSNodeToObjectContext {
    void *context;
    ANSLinkedListObjectComparisonFunction objectComporator;
};

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
                                                   void *context);
extern
void *ANSLinkedListFindObjectWithContext(ANSLinkedList *list,
                                         ANSLinkedListObjectComparisonFunction objectComporator,
                                         void *context);
extern
bool ANSLinkedListNodeContainsObject(ANSLinkedListNode *node, ANSLinkedListContext *context);

extern
bool ANSLinkedListSortFunction(void *object, void *context);

extern
ANSLinkedListContext *ANSLinkedListContextCreateWithObject(void *object);

#endif /* ANSLinkedLisetPrivate_h */
