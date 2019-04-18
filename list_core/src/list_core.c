// list_core.c - Provides implementations for the API function that allow access to a linked list.
//

#include "stdafx.h"

#include "list_core.h"
#include "position.h"
#include "root.h"

///////////////////////////////////////////////////////////////////////////////
// GetCount function

int GetCount(POSITION ** ppElement) {
	// In this case, we can't do anything because we do not know where in the
	// list we are starting from.  Since users of this library generally might
	// be calling this function after everything has been removed from a list,
	// assume that null input means a count of zero should be returned.
	if (ppElement == NULL || *ppElement == NULL) {
		return 0;
	}

	// Get ready to iterate through the list; use the pointer in ppElement
	// to get a reference to the head of the list by calling GetHeadPosition
	POSITION *pos = GetHeadPosition(ppElement);
	if (pos == NULL) {
		// this just means the list has nothing in it.
		return 0;
	}

	int nResult = 1;		// how many elements there are in the list
	while ((pos = GetNext(pos)) != NULL) {
		nResult++;
	}
	return nResult;
}
