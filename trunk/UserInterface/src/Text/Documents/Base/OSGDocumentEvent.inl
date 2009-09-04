/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE

inline
const EventType &DocumentEvent::getClassType(void)
{
    return _Type;
}

inline
DocumentPtr 	DocumentEvent::getDocument(void) const
{
   return _Document;
}

inline
Int32 DocumentEvent::getOffset(void) const
{
   return _Offset;
}

inline
UInt32 DocumentEvent::getLength(void) const
{
   return _Length;
}

inline
DocumentEvent::DocumentEvent(FieldContainerPtr Source, Time TimeStamp, DocumentPtr Document, Int32 Offset, UInt32 Length)
 : Event(Source, TimeStamp),
   _Document(Document),
   _Offset(Offset),
   _Length(Length)
{
}
    
OSG_END_NAMESPACE
