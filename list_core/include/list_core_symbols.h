// list_core_symbols.h - Defines commonly-used symbols used by the functions included in this library.
// This file is not normally meant to be consumed by users of this library.
//

#ifndef __LIST_CORE_SYMBOLS_H__
#define __LIST_CORE_SYMBOLS_H__

#ifndef ERROR_STARTING_MEMBER_NULL
#define ERROR_STARTING_MEMBER_NULL \
    "Must specify starting member.\n"
#endif //ERROR_STARTING_MEMBER_NULL

/**
 * @brief Error message displayed when the allocation of the head of the linked
 * list has failed.
 */
#ifndef FAILED_ALLOC_HEAD
#define FAILED_ALLOC_HEAD \
    "Failed to allocate memory for list head node.\n"
#endif //FAILED_ALLOC_HEAD

#ifndef FAILED_ALLOC_NEW_NODE
#define FAILED_ALLOC_NEW_NODE \
    "Failed to allocate memory for a new linked list node.\n"
#endif //FAILED_ALLOC_NEW_NODE

/**
 * @brief Error message displayed when the allocation of the root of the list
 * has failed.
 */
#ifndef FAILED_ALLOC_ROOT
#define FAILED_ALLOC_ROOT \
    "Failed to allocate memory for list head node.\n"
#endif //FAILED_ALLOC_ROOT

#ifndef FAILED_SEARCH_NULL_COMPARER
#define FAILED_SEARCH_NULL_COMPARER \
    "Can't search for desired list element.  A comparer routine is needed.\n"
#endif //FAILED_SEARCH_NULL_COMPARER

#ifndef FAILED_SEARCH_NULL_HEAD
#define FAILED_SEARCH_NULL_HEAD \
    "Can't search for desired list element because the head has not " \
    "been initialized.\n"
#endif //FAILED_SEARCH_NULL_HEAD

#ifndef FAILED_SEARCH_NULL_KEY
#define FAILED_SEARCH_NULL_KEY \
    "Can't search the linked list because the search key is not initialized.\n"
#endif //FAILED_SEARCH_NULL_KEY

/**
 * @brief Error message that is displayed when a function is given a NULL
 * pointer for its pvData parameter.
 */
#ifndef INVALID_LIST_DATA
#define INVALID_LIST_DATA \
    "The pointer for the data to add to the linked list is an invalid value.\n"
#endif //INVALID_LIST_DATA

/**
 * @brief Error message that is displayed when the head of the list cannot
 * be accessed.
 */
#ifndef LIST_HEAD_INVALID
#define LIST_HEAD_INVALID \
    "list head cannot be accessed.\n"
#endif //LIST_HEAD_INVALID

/**
 * @brief Error message that is displayed when a function is given a NULL
 * pointer for its lpfnDeallocRoutine parameter.
 */
#ifndef NO_DEALLOC_ROUTINE_SPECIFIED
#define NO_DEALLOC_ROUTINE_SPECIFIED \
	"No address specified for deallocation routine in DestroyList.\n"
#endif //NO_DEALLOC_ROUTINE_SPECIFIED

#endif /* __LIST_CORE_SYMBOLS_H__ */
