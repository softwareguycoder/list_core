// list_core.h - Defines the interface to a doubly-linked list.
//

#ifndef __LIST_CORE_H__
#define __LIST_CORE_H__

typedef struct _tagPOSITION POSITION, *LPPOSITION, **LPPPOSITION;

typedef BOOL (*LPCOMPARE_ROUTINE)(void*, void*);

typedef void (*LPDEALLOC_ROUTINE)(void*);

typedef BOOL (*LPPREDICATE_ROUTINE)(void*);

void AddElement(LPPPOSITION lppElement, void* pvData);
void ClearList(LPPPOSITION lppElement, LPDEALLOC_ROUTINE lpfnDeallocFunc);
void CreateList(LPPPOSITION lppNewHead, void* pvData);
LPPOSITION FindElement(LPPOSITION lpElement, void* pvSearchKey,
    LPCOMPARE_ROUTINE lpfnCompare);
LPPOSITION FindElementWhere(LPPOSITION lpElement,
    LPPREDICATE_ROUTINE lpfnPredicate);
int GetElementCount(LPPOSITION lpElement);
int GetElementCountWhere(LPPOSITION lpElement,
    LPPREDICATE_ROUTINE lpfnPredicate);
void RemoveElement(LPPPOSITION lppElement, LPDEALLOC_ROUTINE lpfnDealloc);

#endif //__LIST_CORE_H__
