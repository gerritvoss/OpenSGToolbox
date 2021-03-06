/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: Achyuthan Vasanth (vasanth.achyuthan@gmail.com)                  *
 *          David Kabala (djkabala@gmail.com)                                *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
#include "OSGConfig.h"
#include "OSGTextDomLayoutManager.h"
#include "OSGPlainDocument.h"

OSG_BEGIN_NAMESPACE

inline
InsertStringCommand::InsertStringCommand(TextDomLayoutManagerRefPtr Manager,PlainDocumentRefPtr DocumentModel,UInt32 theCaretPosition,std::string theString) : Inherited(),
_Manager(Manager),
_TheDocumentModel(DocumentModel),
_TheOriginalCaretPosition(theCaretPosition),
_StringToBeInserted(theString),
_theOriginalCaretLine(0),
_theOriginalCaretIndex(0)
{
}

inline
InsertStringCommand::InsertStringCommand(const InsertStringCommand& source) : Inherited(source),
_Manager(source._Manager),
_TheDocumentModel(source._TheDocumentModel),
_TheOriginalCaretPosition(source._TheOriginalCaretPosition),
_StringToBeInserted(source._StringToBeInserted),
_theOriginalCaretLine(source._theOriginalCaretLine),
_theOriginalCaretIndex(source._theOriginalCaretIndex)
{
}

inline 
const CommandType &InsertStringCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
