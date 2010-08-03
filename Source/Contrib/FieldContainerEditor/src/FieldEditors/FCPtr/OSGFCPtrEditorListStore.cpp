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

#include "OSGFCPtrEditorListStore.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::FCPtrEditorListStore
A FCPtrEditorListStore. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

FCPtrEditorListStorePtr FCPtrEditorListStore::create(void)
{
    return FCPtrEditorListStorePtr(new FCPtrEditorListStore());
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
FCPtrEditorStorePtr FCPtrEditorListStore::clone(void) const
{
    return FCPtrEditorStorePtr(new FCPtrEditorListStore(*this));
}

void FCPtrEditorListStore::updateList(void)
{
   //Do Nothing
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/
FCPtrEditorListStore::FCPtrEditorListStore(void) :
    Inherited()
{
}

FCPtrEditorListStore::FCPtrEditorListStore(const FieldContianerVector& Store) :
    Inherited(Store)
{
}

FCPtrEditorListStore::FCPtrEditorListStore(const FCPtrEditorListStore& source) :
    Inherited(source)
{
}


FCPtrEditorListStore::~FCPtrEditorListStore(void)
{
}

/*----------------------------- class specific ----------------------------*/
void FCPtrEditorListStore::operator =(const FCPtrEditorListStore& source)
{
    if(this == &source)
    {
        return;
    }

    Inherited::operator=(source);
    _Store = source._Store;
}

