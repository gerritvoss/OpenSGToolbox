/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class AbstractDocument!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILEABSTRACTDOCUMENTINST

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "OSGAbstractDocumentBase.h"
#include "OSGAbstractDocument.h"


OSG_BEGIN_NAMESPACE

const OSG::BitVector  AbstractDocumentBase::RootElementFieldMask = 
    (TypeTraits<BitVector>::One << AbstractDocumentBase::RootElementFieldId);

const OSG::BitVector AbstractDocumentBase::MTInfluenceMask = 
    (Inherited::MTInfluenceMask) | 
    (static_cast<BitVector>(0x0) << Inherited::NextFieldId); 


// Field descriptions

/*! \var ElementPtr      AbstractDocumentBase::_sfRootElement
    
*/

//! AbstractDocument description

FieldDescription *AbstractDocumentBase::_desc[] = 
{
    new FieldDescription(SFElementPtr::getClassType(), 
                     "RootElement", 
                     RootElementFieldId, RootElementFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&AbstractDocumentBase::editSFRootElement))
};


FieldContainerType AbstractDocumentBase::_type(
    "AbstractDocument",
    "Document",
    NULL,
    NULL, 
    AbstractDocument::initMethod,
    _desc,
    sizeof(_desc));

//OSG_FIELD_CONTAINER_DEF(AbstractDocumentBase, AbstractDocumentPtr)

/*------------------------------ get -----------------------------------*/

FieldContainerType &AbstractDocumentBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &AbstractDocumentBase::getType(void) const 
{
    return _type;
} 


UInt32 AbstractDocumentBase::getContainerSize(void) const 
{ 
    return sizeof(AbstractDocument); 
}


#if !defined(OSG_FIXED_MFIELDSYNC)
void AbstractDocumentBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField)
{
    this->executeSyncImpl(static_cast<AbstractDocumentBase *>(&other),
                          whichField);
}
#else
void AbstractDocumentBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField,                                    const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((AbstractDocumentBase *) &other, whichField, sInfo);
}
void AbstractDocumentBase::execBeginEdit(const BitVector &whichField, 
                                            UInt32     uiAspect,
                                            UInt32     uiContainerSize) 
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}

void AbstractDocumentBase::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    Inherited::onDestroyAspect(uiId, uiAspect);

}
#endif

/*------------------------- constructors ----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

AbstractDocumentBase::AbstractDocumentBase(void) :
    _sfRootElement            (ElementPtr(NullFC)), 
    Inherited() 
{
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

AbstractDocumentBase::AbstractDocumentBase(const AbstractDocumentBase &source) :
    _sfRootElement            (source._sfRootElement            ), 
    Inherited                 (source)
{
}

/*-------------------------- destructors ----------------------------------*/

AbstractDocumentBase::~AbstractDocumentBase(void)
{
}

/*------------------------------ access -----------------------------------*/

UInt32 AbstractDocumentBase::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (RootElementFieldMask & whichField))
    {
        returnValue += _sfRootElement.getBinSize();
    }


    return returnValue;
}

void AbstractDocumentBase::copyToBin(      BinaryDataHandler &pMem,
                                  const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (RootElementFieldMask & whichField))
    {
        _sfRootElement.copyToBin(pMem);
    }


}

void AbstractDocumentBase::copyFromBin(      BinaryDataHandler &pMem,
                                    const BitVector    &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (RootElementFieldMask & whichField))
    {
        _sfRootElement.copyFromBin(pMem);
    }


}

#if !defined(OSG_FIXED_MFIELDSYNC)
void AbstractDocumentBase::executeSyncImpl(      AbstractDocumentBase *pOther,
                                        const BitVector         &whichField)
{

    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (RootElementFieldMask & whichField))
        _sfRootElement.syncWith(pOther->_sfRootElement);


}
#else
void AbstractDocumentBase::executeSyncImpl(      AbstractDocumentBase *pOther,
                                        const BitVector         &whichField,
                                        const SyncInfo          &sInfo      )
{

    Inherited::executeSyncImpl(pOther, whichField, sInfo);

    if(FieldBits::NoField != (RootElementFieldMask & whichField))
        _sfRootElement.syncWith(pOther->_sfRootElement);



}

void AbstractDocumentBase::execBeginEditImpl (const BitVector &whichField, 
                                                 UInt32     uiAspect,
                                                 UInt32     uiContainerSize)
{
    Inherited::execBeginEditImpl(whichField, uiAspect, uiContainerSize);

}
#endif



OSG_END_NAMESPACE

#include <OpenSG/OSGSFieldTypeDef.inl>
#include <OpenSG/OSGMFieldTypeDef.inl>

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldDataTraits<AbstractDocumentPtr>::_type("AbstractDocumentPtr", "DocumentPtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(AbstractDocumentPtr, OSG_USERINTERFACELIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(AbstractDocumentPtr, OSG_USERINTERFACELIB_DLLTMPLMAPPING);


OSG_END_NAMESPACE
