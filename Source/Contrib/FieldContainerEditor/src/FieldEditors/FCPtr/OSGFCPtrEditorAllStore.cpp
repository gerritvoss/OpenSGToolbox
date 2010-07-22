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

#include "OSGFCPtrEditorAllStore.h"
#include "OSGFieldContainerFactory.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::FCPtrEditorAllStore
A FCPtrEditorAllStore. 
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

std::vector<FieldContainer*> FCPtrEditorAllStore::getList(void) const
{
    std::vector<FieldContainer*> Result;

   const FieldContainerFactoryBase::ContainerStore &FCStore(FieldContainerFactory::the()->getFieldContainerStore () );

   FieldContainerFactoryBase::ContainerStore::const_iterator FCStoreIter;
   FieldContainerFactoryBase::ContainerPtr Cont;
   for(FCStoreIter = FCStore.begin() ; FCStoreIter != FCStore.end() ; ++FCStoreIter)
   {
       if(*FCStoreIter == NULL)
       {
           continue;
       }
#ifdef OSG_MT_CPTR_ASPECT
        Cont = (*FCStoreIter)->getPtr();
#else
        Cont = *FCStoreIter;
#endif
        if(Cont->getType().isDerivedFrom(*_TypeToStore) && !isExcluded(Cont))
        {
            Result.push_back(Cont);
        }
   }

    return Result;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/
FCPtrEditorAllStore::FCPtrEditorAllStore(const FieldContainerType* type,
                                         const FieldContianerVector& Exclude,
                                         const FieldContianerTypeVector& ExcludeTypes) :
    Inherited(Exclude,ExcludeTypes),
    _TypeToStore(type)
{
}

FCPtrEditorAllStore::FCPtrEditorAllStore(const FCPtrEditorAllStore& source) :
    Inherited(source),
    _TypeToStore(source._TypeToStore)
{
}


FCPtrEditorAllStore::~FCPtrEditorAllStore(void)
{
}

/*----------------------------- class specific ----------------------------*/
void FCPtrEditorAllStore::operator =(const FCPtrEditorAllStore& source)
{
    if(this == &source)
    {
        return;
    }

    Inherited::operator=(source);
    _TypeToStore = source._TypeToStore;
}

