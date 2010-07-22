/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
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

#include "OSGConfig.h"

#include "OSGFCPtrEditorStore.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::FCPtrEditorStore
A FCPtrEditorStore. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool FCPtrEditorStore::isExcluded(FieldContainer* ptr) const
{
    for(UInt32 i(0) ; i<_ExcludedPtrs.size() ; ++i)
    {
        if(_ExcludedPtrs[i] == ptr)
        {
            return true;
        }
    }

    for(UInt32 i(0) ; i<_ExcludedTypes.size() ; ++i)
    {
        if(*_ExcludedTypes[i] == ptr->getType())
        {
            return true;
        }
    }

    return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/
FCPtrEditorStore::FCPtrEditorStore(const FieldContianerVector& Exclude,
                 const FieldContianerTypeVector& ExcludeTypes) :
    _ExcludedPtrs(Exclude),
    _ExcludedTypes(ExcludeTypes)
{
}

FCPtrEditorStore::FCPtrEditorStore(const FCPtrEditorStore& source) :
    _ExcludedPtrs(source._ExcludedPtrs),
    _ExcludedTypes(source._ExcludedTypes)
{
}


FCPtrEditorStore::~FCPtrEditorStore(void)
{
}

/*----------------------------- class specific ----------------------------*/
void FCPtrEditorStore::operator =(const FCPtrEditorStore& source)
{
    if(this == &source)
    {
        return;
    }

    _ExcludedPtrs = source._ExcludedPtrs;
    _ExcludedTypes = source._ExcludedTypes;
}

