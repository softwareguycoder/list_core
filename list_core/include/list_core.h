// list_core.h - Defines the interface to a doubly-linked list.
//

#ifndef __LIST_CORE_H__
#define __LIST_CORE_H__

typedef struct _tagPOSITION POSITION, *LPPOSITION, **LPPPOSITION;

/**
 * @name GetCount
 * @brief Gets the number of elements contained in the list.
 * @param Pointer to a POSITION structure that refers to any of the elements
 * in the list.
 * @return Count of elements in the list.
 */
int GetCount(LPPOSITION lpMember);

#endif //__LIST_CORE_H__
