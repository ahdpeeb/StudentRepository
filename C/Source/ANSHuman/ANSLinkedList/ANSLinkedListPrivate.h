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

typedef bool (*ANSLinkedListComparisonFunction)(void *object, void *context);

typedef struct ANSNodeToObjectContext ANSNodeToObjectContext;
struct ANSNodeToObjectContext {
    void *context;
    ANSLinkedListComparisonFunction comporator;
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
                                                   ANSLinkedListComparisonFunction comporator,
                                                   void *context);
extern
void *ANSLinkedListFindObjectWithContext(ANSLinkedList *list,
                                         ANSLinkedListComparisonFunction comporator,
                                         void *context);
extern
ANSLinkedListContext *ANSLinkedListContextCreateWithObject(void *object);

extern
ANSArray *ANSLinkedListSortObjectsDependOnComporator(ANSLinkedList *list,
                                                     ANSLinkedListComparisonFunction comparator);

#endif /* ANSLinkedLisetPrivate_h */
