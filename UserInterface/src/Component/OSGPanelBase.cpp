/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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
 **     class Panel!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILEPANELINST

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "OSGPanelBase.h"
#include "OSGPanel.h"


OSG_BEGIN_NAMESPACE

const OSG::BitVector  PanelBase::ChildrenFieldMask = 
    (TypeTraits<BitVector>::One << PanelBase::ChildrenFieldId);

const OSG::BitVector  PanelBase::ArrangementFieldMask = 
    (TypeTraits<BitVector>::One << PanelBase::ArrangementFieldId);

const OSG::BitVector PanelBase::MTInfluenceMask = 
    (Inherited::MTInfluenceMask) | 
    (static_cast<BitVector>(0x0) << Inherited::NextFieldId); 


// Field descriptions

/*! \var ComponentPtr    PanelBase::_mfChildren
    
*/
/*! \var LayoutPtr       PanelBase::_sfArrangement
    
*/

//! Panel description

FieldDescription *PanelBase::_desc[] = 
{
    new FieldDescription(MFComponentPtr::getClassType(), 
                     "Children", 
                     ChildrenFieldId, ChildrenFieldMask,
                     false,
                     (FieldAccessMethod) &PanelBase::getMFChildren),
    new FieldDescription(SFLayoutPtr::getClassType(), 
                     "Arrangement", 
                     ArrangementFieldId, ArrangementFieldMask,
                     false,
                     (FieldAccessMethod) &PanelBase::getSFArrangement)
};


FieldContainerType PanelBase::_type(
    "Panel",
    "Component",
    NULL,
    (PrototypeCreateF) &PanelBase::createEmpty,
    Panel::initMethod,
    _desc,
    sizeof(_desc));

//OSG_FIELD_CONTAINER_DEF(PanelBase, PanelPtr)

/*------------------------------ get -----------------------------------*/

FieldContainerType &PanelBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &PanelBase::getType(void) const 
{
    return _type;
} 


FieldContainerPtr PanelBase::shallowCopy(void) const 
{ 
    PanelPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const Panel *>(this)); 

    return returnValue; 
}

UInt32 PanelBase::getContainerSize(void) const 
{ 
    return sizeof(Panel); 
}


#if !defined(OSG_FIXED_MFIELDSYNC)
void PanelBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField)
{
    this->executeSyncImpl((PanelBase *) &other, whichField);
}
#else
void PanelBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField,                                    const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((PanelBase *) &other, whichField, sInfo);
}
void PanelBase::execBeginEdit(const BitVector &whichField, 
                                            UInt32     uiAspect,
                                            UInt32     uiContainerSize) 
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}

void PanelBase::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    Inherited::onDestroyAspect(uiId, uiAspect);

    _mfChildren.terminateShare(uiAspect, this->getContainerSize());
}
#endif

/*------------------------- constructors ----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

PanelBase::PanelBase(void) :
    _mfChildren               (), 
    _sfArrangement            (), 
    Inherited() 
{
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

PanelBase::PanelBase(const PanelBase &source) :
    _mfChildren               (source._mfChildren               ), 
    _sfArrangement            (source._sfArrangement            ), 
    Inherited                 (source)
{
}

/*-------------------------- destructors ----------------------------------*/

PanelBase::~PanelBase(void)
{
}

/*------------------------------ access -----------------------------------*/

UInt32 PanelBase::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        returnValue += _mfChildren.getBinSize();
    }

    if(FieldBits::NoField != (ArrangementFieldMask & whichField))
    {
        returnValue += _sfArrangement.getBinSize();
    }


    return returnValue;
}

void PanelBase::copyToBin(      BinaryDataHandler &pMem,
                                  const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        _mfChildren.copyToBin(pMem);
    }

    if(FieldBits::NoField != (ArrangementFieldMask & whichField))
    {
        _sfArrangement.copyToBin(pMem);
    }


}

void PanelBase::copyFromBin(      BinaryDataHandler &pMem,
                                    const BitVector    &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        _mfChildren.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (ArrangementFieldMask & whichField))
    {
        _sfArrangement.copyFromBin(pMem);
    }


}

#if !defined(OSG_FIXED_MFIELDSYNC)
void PanelBase::executeSyncImpl(      PanelBase *pOther,
                                        const BitVector         &whichField)
{

    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
        _mfChildren.syncWith(pOther->_mfChildren);

    if(FieldBits::NoField != (ArrangementFieldMask & whichField))
        _sfArrangement.syncWith(pOther->_sfArrangement);


}
#else
void PanelBase::executeSyncImpl(      PanelBase *pOther,
                                        const BitVector         &whichField,
                                        const SyncInfo          &sInfo      )
{

    Inherited::executeSyncImpl(pOther, whichField, sInfo);

    if(FieldBits::NoField != (ArrangementFieldMask & whichField))
        _sfArrangement.syncWith(pOther->_sfArrangement);


    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
        _mfChildren.syncWith(pOther->_mfChildren, sInfo);


}

void PanelBase::execBeginEditImpl (const BitVector &whichField, 
                                                 UInt32     uiAspect,
                                                 UInt32     uiContainerSize)
{
    Inherited::execBeginEditImpl(whichField, uiAspect, uiContainerSize);

    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
        _mfChildren.beginEdit(uiAspect, uiContainerSize);

}
#endif



OSG_END_NAMESPACE

#include <OpenSG/OSGSFieldTypeDef.inl>
#include <OpenSG/OSGMFieldTypeDef.inl>

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldDataTraits<PanelPtr>::_type("PanelPtr", "ComponentPtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(PanelPtr, );
OSG_DLLEXPORT_MFIELD_DEF1(PanelPtr, );


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCBaseTemplate_cpp.h,v 1.47 2006/03/17 17:03:19 pdaehne Exp $";
    static Char8 cvsid_hpp       [] = OSGPANELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPANELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPANELFIELDS_HEADER_CVSID;
}

OSG_END_NAMESPACE

