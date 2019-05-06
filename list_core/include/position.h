// position.h - Defines the interface to the POSITION data structure.
//
// Copyright (c) 2019 by Brian Hart.
//
// This file is part of list_core.
//
// list_core is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// list_core is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with list_core.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef __POSITION_H__
#define __POSITION_H__

typedef struct _tagPOSITION {
  void* pvData;
  struct _tagPOSITION* pPrev;
  struct _tagPOSITION* pNext;
} POSITION, *LPPOSITION, **LPPPOSITION;

void CreatePosition(LPPPOSITION lppPosition);
void DestroyPosition(LPPPOSITION lppPosition);
void GetHeadPosition(LPPPOSITION lppElement);
LPPOSITION GetNextPosition(LPPOSITION lpElement);
LPPOSITION GetPrevPosition(LPPOSITION lpElement);
void GetTailPosition(LPPPOSITION lppElement);
BOOL IsPositionHead(LPPOSITION lpElement);
BOOL IsPositionTail(LPPOSITION lpElement);
BOOL IsSoleElement(LPPOSITION lpElement);
void SetNextPosition(LPPOSITION lpElement, LPPOSITION lpValue);
void SetPositionData(LPPOSITION lpElement, void* pvData);
void SetPrevPosition(LPPOSITION lpElement, LPPOSITION lpValue);

#endif /* __POSITION_H__ */
