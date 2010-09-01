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

#include "OSGFCPtrEditorRootedStore.h"
#include "OSGContainerUtils.h"
#include "OSGContainerGatherUtils.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::FCPtrEditorRootedStore
A FCPtrEditorRootedStore. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

FCPtrEditorRootedStorePtr FCPtrEditorRootedStore::create(void)
{
    return FCPtrEditorRootedStorePtr(new FCPtrEditorRootedStore());
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

FCPtrEditorStorePtr FCPtrEditorRootedStore::clone(void) const
{
    return FCPtrEditorStorePtr(new FCPtrEditorRootedStore(*this));
}

void FCPtrEditorRootedStore::updateList(void)
{
    _Store.clear();
    if(_TypeToStore == NULL || _Roots.empty())
    {
        return;
    }

    FCFileType::FCPtrStore SearchRoots;
    for(std::vector<FieldContainer*>::const_iterator Itor(_Roots.begin()) ; Itor!=_Roots.end() ; ++Itor)
    {
        SearchRoots.insert(*Itor);
    }

    FCFileType::FCPtrStore Exclude;
    for(std::vector<FieldContainer*>::const_iterator Itor(_ExcludedPtrs.begin()) ; Itor!=_ExcludedPtrs.end() ; ++Itor)
    {
        Exclude.insert(*Itor);
    }

    FCFileType::FCPtrStore AllContainers =
        getAllDependantFCs(SearchRoots,
                           Exclude,
                           _ExcludedTypes,
                           true);

    for(FCFileType::FCPtrStore::iterator StoreItor(AllContainers.begin());
        StoreItor != AllContainers.end();
        ++StoreItor)
    {
        if((*StoreItor)->getType().isDerivedFrom(*_TypeToStore))
        {
            _Store.push_back(*StoreItor);
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/
FCPtrEditorRootedStore::FCPtrEditorRootedStore(void) :
    Inherited(),
    _TypeToStore(NULL)
{
}

FCPtrEditorRootedStore::FCPtrEditorRootedStore(const FieldContainerType* type,
                                               const FieldContianerVector& roots,
                                               const FieldContianerVector& Exclude,
                                               const FieldContianerTypeVector& ExcludeTypes) :
    Inherited(FieldContianerVector(),Exclude,ExcludeTypes),
    _TypeToStore(type),
    _Roots(roots)
{
}

FCPtrEditorRootedStore::FCPtrEditorRootedStore(const FCPtrEditorRootedStore& source) :
    Inherited(source),
    _TypeToStore(source._TypeToStore),
    _Roots(source._Roots)
{
}


FCPtrEditorRootedStore::~FCPtrEditorRootedStore(void)
{
}

/*----------------------------- class specific ----------------------------*/
void FCPtrEditorRootedStore::operator =(const FCPtrEditorRootedStore& source)
{
    if(this == &source)
    {
        return;
    }

    Inherited::operator=(source);
    _TypeToStore = source._TypeToStore;
    _Roots = source._Roots;
}

