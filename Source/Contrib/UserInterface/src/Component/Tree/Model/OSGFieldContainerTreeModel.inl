/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

inline
FieldContainer* FieldContainerTreeModel::getRootFieldContainer(void) const
{
    return getInternalRootFieldContainer();
}

inline
FieldContainerTreeModel::ContainerFieldIdPair::ContainerFieldIdPair(FieldContainer* container, UInt32 fieldId) :
_Container(container),
_FieldID(fieldId)
{
}

inline
FieldContainerTreeModel::ContainerFieldIdPair::ContainerFieldIdPair(void) :
_Container(NULL),
_FieldID(0)
{
}

inline
bool FieldContainerTreeModel::ContainerFieldIdPair::operator==(const ContainerFieldIdPair& right) const
{
    return (_Container == right._Container) && 
           (_FieldID   == right._FieldID  );
}

OSG_END_NAMESPACE
