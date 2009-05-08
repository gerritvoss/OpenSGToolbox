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
 **     class SpringLayoutConstraints!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILESPRINGLAYOUTCONSTRAINTSINST

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "OSGSpringLayoutConstraintsBase.h"
#include "OSGSpringLayoutConstraints.h"


OSG_BEGIN_NAMESPACE

const OSG::BitVector  SpringLayoutConstraintsBase::NorthSpringFieldMask = 
    (TypeTraits<BitVector>::One << SpringLayoutConstraintsBase::NorthSpringFieldId);

const OSG::BitVector  SpringLayoutConstraintsBase::WestSpringFieldMask = 
    (TypeTraits<BitVector>::One << SpringLayoutConstraintsBase::WestSpringFieldId);

const OSG::BitVector  SpringLayoutConstraintsBase::EastSpringFieldMask = 
    (TypeTraits<BitVector>::One << SpringLayoutConstraintsBase::EastSpringFieldId);

const OSG::BitVector  SpringLayoutConstraintsBase::SouthSpringFieldMask = 
    (TypeTraits<BitVector>::One << SpringLayoutConstraintsBase::SouthSpringFieldId);

const OSG::BitVector  SpringLayoutConstraintsBase::WidthSpringFieldMask = 
    (TypeTraits<BitVector>::One << SpringLayoutConstraintsBase::WidthSpringFieldId);

const OSG::BitVector  SpringLayoutConstraintsBase::HeightSpringFieldMask = 
    (TypeTraits<BitVector>::One << SpringLayoutConstraintsBase::HeightSpringFieldId);

const OSG::BitVector  SpringLayoutConstraintsBase::HorizontalCenterSpringFieldMask = 
    (TypeTraits<BitVector>::One << SpringLayoutConstraintsBase::HorizontalCenterSpringFieldId);

const OSG::BitVector  SpringLayoutConstraintsBase::VerticalCenterSpringFieldMask = 
    (TypeTraits<BitVector>::One << SpringLayoutConstraintsBase::VerticalCenterSpringFieldId);

const OSG::BitVector  SpringLayoutConstraintsBase::BaselineSpringFieldMask = 
    (TypeTraits<BitVector>::One << SpringLayoutConstraintsBase::BaselineSpringFieldId);

const OSG::BitVector  SpringLayoutConstraintsBase::ComponentFieldMask = 
    (TypeTraits<BitVector>::One << SpringLayoutConstraintsBase::ComponentFieldId);

const OSG::BitVector SpringLayoutConstraintsBase::MTInfluenceMask = 
    (Inherited::MTInfluenceMask) | 
    (static_cast<BitVector>(0x0) << Inherited::NextFieldId); 


// Field descriptions

/*! \var LayoutSpringPtr SpringLayoutConstraintsBase::_sfNorthSpring
    
*/
/*! \var LayoutSpringPtr SpringLayoutConstraintsBase::_sfWestSpring
    
*/
/*! \var LayoutSpringPtr SpringLayoutConstraintsBase::_sfEastSpring
    
*/
/*! \var LayoutSpringPtr SpringLayoutConstraintsBase::_sfSouthSpring
    
*/
/*! \var LayoutSpringPtr SpringLayoutConstraintsBase::_sfWidthSpring
    
*/
/*! \var LayoutSpringPtr SpringLayoutConstraintsBase::_sfHeightSpring
    
*/
/*! \var LayoutSpringPtr SpringLayoutConstraintsBase::_sfHorizontalCenterSpring
    
*/
/*! \var LayoutSpringPtr SpringLayoutConstraintsBase::_sfVerticalCenterSpring
    
*/
/*! \var LayoutSpringPtr SpringLayoutConstraintsBase::_sfBaselineSpring
    
*/
/*! \var ComponentPtr    SpringLayoutConstraintsBase::_sfComponent
    
*/

//! SpringLayoutConstraints description

FieldDescription *SpringLayoutConstraintsBase::_desc[] = 
{
    new FieldDescription(SFLayoutSpringPtr::getClassType(), 
                     "NorthSpring", 
                     NorthSpringFieldId, NorthSpringFieldMask,
                     false,
                     (FieldAccessMethod) &SpringLayoutConstraintsBase::getSFNorthSpring),
    new FieldDescription(SFLayoutSpringPtr::getClassType(), 
                     "WestSpring", 
                     WestSpringFieldId, WestSpringFieldMask,
                     false,
                     (FieldAccessMethod) &SpringLayoutConstraintsBase::getSFWestSpring),
    new FieldDescription(SFLayoutSpringPtr::getClassType(), 
                     "EastSpring", 
                     EastSpringFieldId, EastSpringFieldMask,
                     false,
                     (FieldAccessMethod) &SpringLayoutConstraintsBase::getSFEastSpring),
    new FieldDescription(SFLayoutSpringPtr::getClassType(), 
                     "SouthSpring", 
                     SouthSpringFieldId, SouthSpringFieldMask,
                     false,
                     (FieldAccessMethod) &SpringLayoutConstraintsBase::getSFSouthSpring),
    new FieldDescription(SFLayoutSpringPtr::getClassType(), 
                     "WidthSpring", 
                     WidthSpringFieldId, WidthSpringFieldMask,
                     false,
                     (FieldAccessMethod) &SpringLayoutConstraintsBase::getSFWidthSpring),
    new FieldDescription(SFLayoutSpringPtr::getClassType(), 
                     "HeightSpring", 
                     HeightSpringFieldId, HeightSpringFieldMask,
                     false,
                     (FieldAccessMethod) &SpringLayoutConstraintsBase::getSFHeightSpring),
    new FieldDescription(SFLayoutSpringPtr::getClassType(), 
                     "HorizontalCenterSpring", 
                     HorizontalCenterSpringFieldId, HorizontalCenterSpringFieldMask,
                     false,
                     (FieldAccessMethod) &SpringLayoutConstraintsBase::getSFHorizontalCenterSpring),
    new FieldDescription(SFLayoutSpringPtr::getClassType(), 
                     "VerticalCenterSpring", 
                     VerticalCenterSpringFieldId, VerticalCenterSpringFieldMask,
                     false,
                     (FieldAccessMethod) &SpringLayoutConstraintsBase::getSFVerticalCenterSpring),
    new FieldDescription(SFLayoutSpringPtr::getClassType(), 
                     "BaselineSpring", 
                     BaselineSpringFieldId, BaselineSpringFieldMask,
                     false,
                     (FieldAccessMethod) &SpringLayoutConstraintsBase::getSFBaselineSpring),
    new FieldDescription(SFComponentPtr::getClassType(), 
                     "Component", 
                     ComponentFieldId, ComponentFieldMask,
                     false,
                     (FieldAccessMethod) &SpringLayoutConstraintsBase::getSFComponent)
};


FieldContainerType SpringLayoutConstraintsBase::_type(
    "SpringLayoutConstraints",
    "LayoutConstraints",
    NULL,
    (PrototypeCreateF) &SpringLayoutConstraintsBase::createEmpty,
    SpringLayoutConstraints::initMethod,
    _desc,
    sizeof(_desc));

//OSG_FIELD_CONTAINER_DEF(SpringLayoutConstraintsBase, SpringLayoutConstraintsPtr)

/*------------------------------ get -----------------------------------*/

FieldContainerType &SpringLayoutConstraintsBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &SpringLayoutConstraintsBase::getType(void) const 
{
    return _type;
} 


FieldContainerPtr SpringLayoutConstraintsBase::shallowCopy(void) const 
{ 
    SpringLayoutConstraintsPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const SpringLayoutConstraints *>(this)); 

    return returnValue; 
}

UInt32 SpringLayoutConstraintsBase::getContainerSize(void) const 
{ 
    return sizeof(SpringLayoutConstraints); 
}


#if !defined(OSG_FIXED_MFIELDSYNC)
void SpringLayoutConstraintsBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField)
{
    this->executeSyncImpl((SpringLayoutConstraintsBase *) &other, whichField);
}
#else
void SpringLayoutConstraintsBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField,                                    const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((SpringLayoutConstraintsBase *) &other, whichField, sInfo);
}
void SpringLayoutConstraintsBase::execBeginEdit(const BitVector &whichField, 
                                            UInt32     uiAspect,
                                            UInt32     uiContainerSize) 
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}

void SpringLayoutConstraintsBase::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    Inherited::onDestroyAspect(uiId, uiAspect);

}
#endif

/*------------------------- constructors ----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

SpringLayoutConstraintsBase::SpringLayoutConstraintsBase(void) :
    _sfNorthSpring            (LayoutSpringPtr(NullFC)), 
    _sfWestSpring             (LayoutSpringPtr(NullFC)), 
    _sfEastSpring             (LayoutSpringPtr(NullFC)), 
    _sfSouthSpring            (LayoutSpringPtr(NullFC)), 
    _sfWidthSpring            (LayoutSpringPtr(NullFC)), 
    _sfHeightSpring           (LayoutSpringPtr(NullFC)), 
    _sfHorizontalCenterSpring (LayoutSpringPtr(NullFC)), 
    _sfVerticalCenterSpring   (LayoutSpringPtr(NullFC)), 
    _sfBaselineSpring         (LayoutSpringPtr(NullFC)), 
    _sfComponent              (ComponentPtr(NullFC)), 
    Inherited() 
{
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

SpringLayoutConstraintsBase::SpringLayoutConstraintsBase(const SpringLayoutConstraintsBase &source) :
    _sfNorthSpring            (source._sfNorthSpring            ), 
    _sfWestSpring             (source._sfWestSpring             ), 
    _sfEastSpring             (source._sfEastSpring             ), 
    _sfSouthSpring            (source._sfSouthSpring            ), 
    _sfWidthSpring            (source._sfWidthSpring            ), 
    _sfHeightSpring           (source._sfHeightSpring           ), 
    _sfHorizontalCenterSpring (source._sfHorizontalCenterSpring ), 
    _sfVerticalCenterSpring   (source._sfVerticalCenterSpring   ), 
    _sfBaselineSpring         (source._sfBaselineSpring         ), 
    _sfComponent              (source._sfComponent              ), 
    Inherited                 (source)
{
}

/*-------------------------- destructors ----------------------------------*/

SpringLayoutConstraintsBase::~SpringLayoutConstraintsBase(void)
{
}

/*------------------------------ access -----------------------------------*/

UInt32 SpringLayoutConstraintsBase::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (NorthSpringFieldMask & whichField))
    {
        returnValue += _sfNorthSpring.getBinSize();
    }

    if(FieldBits::NoField != (WestSpringFieldMask & whichField))
    {
        returnValue += _sfWestSpring.getBinSize();
    }

    if(FieldBits::NoField != (EastSpringFieldMask & whichField))
    {
        returnValue += _sfEastSpring.getBinSize();
    }

    if(FieldBits::NoField != (SouthSpringFieldMask & whichField))
    {
        returnValue += _sfSouthSpring.getBinSize();
    }

    if(FieldBits::NoField != (WidthSpringFieldMask & whichField))
    {
        returnValue += _sfWidthSpring.getBinSize();
    }

    if(FieldBits::NoField != (HeightSpringFieldMask & whichField))
    {
        returnValue += _sfHeightSpring.getBinSize();
    }

    if(FieldBits::NoField != (HorizontalCenterSpringFieldMask & whichField))
    {
        returnValue += _sfHorizontalCenterSpring.getBinSize();
    }

    if(FieldBits::NoField != (VerticalCenterSpringFieldMask & whichField))
    {
        returnValue += _sfVerticalCenterSpring.getBinSize();
    }

    if(FieldBits::NoField != (BaselineSpringFieldMask & whichField))
    {
        returnValue += _sfBaselineSpring.getBinSize();
    }

    if(FieldBits::NoField != (ComponentFieldMask & whichField))
    {
        returnValue += _sfComponent.getBinSize();
    }


    return returnValue;
}

void SpringLayoutConstraintsBase::copyToBin(      BinaryDataHandler &pMem,
                                  const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (NorthSpringFieldMask & whichField))
    {
        _sfNorthSpring.copyToBin(pMem);
    }

    if(FieldBits::NoField != (WestSpringFieldMask & whichField))
    {
        _sfWestSpring.copyToBin(pMem);
    }

    if(FieldBits::NoField != (EastSpringFieldMask & whichField))
    {
        _sfEastSpring.copyToBin(pMem);
    }

    if(FieldBits::NoField != (SouthSpringFieldMask & whichField))
    {
        _sfSouthSpring.copyToBin(pMem);
    }

    if(FieldBits::NoField != (WidthSpringFieldMask & whichField))
    {
        _sfWidthSpring.copyToBin(pMem);
    }

    if(FieldBits::NoField != (HeightSpringFieldMask & whichField))
    {
        _sfHeightSpring.copyToBin(pMem);
    }

    if(FieldBits::NoField != (HorizontalCenterSpringFieldMask & whichField))
    {
        _sfHorizontalCenterSpring.copyToBin(pMem);
    }

    if(FieldBits::NoField != (VerticalCenterSpringFieldMask & whichField))
    {
        _sfVerticalCenterSpring.copyToBin(pMem);
    }

    if(FieldBits::NoField != (BaselineSpringFieldMask & whichField))
    {
        _sfBaselineSpring.copyToBin(pMem);
    }

    if(FieldBits::NoField != (ComponentFieldMask & whichField))
    {
        _sfComponent.copyToBin(pMem);
    }


}

void SpringLayoutConstraintsBase::copyFromBin(      BinaryDataHandler &pMem,
                                    const BitVector    &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (NorthSpringFieldMask & whichField))
    {
        _sfNorthSpring.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (WestSpringFieldMask & whichField))
    {
        _sfWestSpring.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (EastSpringFieldMask & whichField))
    {
        _sfEastSpring.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (SouthSpringFieldMask & whichField))
    {
        _sfSouthSpring.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (WidthSpringFieldMask & whichField))
    {
        _sfWidthSpring.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (HeightSpringFieldMask & whichField))
    {
        _sfHeightSpring.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (HorizontalCenterSpringFieldMask & whichField))
    {
        _sfHorizontalCenterSpring.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (VerticalCenterSpringFieldMask & whichField))
    {
        _sfVerticalCenterSpring.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (BaselineSpringFieldMask & whichField))
    {
        _sfBaselineSpring.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (ComponentFieldMask & whichField))
    {
        _sfComponent.copyFromBin(pMem);
    }


}

#if !defined(OSG_FIXED_MFIELDSYNC)
void SpringLayoutConstraintsBase::executeSyncImpl(      SpringLayoutConstraintsBase *pOther,
                                        const BitVector         &whichField)
{

    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (NorthSpringFieldMask & whichField))
        _sfNorthSpring.syncWith(pOther->_sfNorthSpring);

    if(FieldBits::NoField != (WestSpringFieldMask & whichField))
        _sfWestSpring.syncWith(pOther->_sfWestSpring);

    if(FieldBits::NoField != (EastSpringFieldMask & whichField))
        _sfEastSpring.syncWith(pOther->_sfEastSpring);

    if(FieldBits::NoField != (SouthSpringFieldMask & whichField))
        _sfSouthSpring.syncWith(pOther->_sfSouthSpring);

    if(FieldBits::NoField != (WidthSpringFieldMask & whichField))
        _sfWidthSpring.syncWith(pOther->_sfWidthSpring);

    if(FieldBits::NoField != (HeightSpringFieldMask & whichField))
        _sfHeightSpring.syncWith(pOther->_sfHeightSpring);

    if(FieldBits::NoField != (HorizontalCenterSpringFieldMask & whichField))
        _sfHorizontalCenterSpring.syncWith(pOther->_sfHorizontalCenterSpring);

    if(FieldBits::NoField != (VerticalCenterSpringFieldMask & whichField))
        _sfVerticalCenterSpring.syncWith(pOther->_sfVerticalCenterSpring);

    if(FieldBits::NoField != (BaselineSpringFieldMask & whichField))
        _sfBaselineSpring.syncWith(pOther->_sfBaselineSpring);

    if(FieldBits::NoField != (ComponentFieldMask & whichField))
        _sfComponent.syncWith(pOther->_sfComponent);


}
#else
void SpringLayoutConstraintsBase::executeSyncImpl(      SpringLayoutConstraintsBase *pOther,
                                        const BitVector         &whichField,
                                        const SyncInfo          &sInfo      )
{

    Inherited::executeSyncImpl(pOther, whichField, sInfo);

    if(FieldBits::NoField != (NorthSpringFieldMask & whichField))
        _sfNorthSpring.syncWith(pOther->_sfNorthSpring);

    if(FieldBits::NoField != (WestSpringFieldMask & whichField))
        _sfWestSpring.syncWith(pOther->_sfWestSpring);

    if(FieldBits::NoField != (EastSpringFieldMask & whichField))
        _sfEastSpring.syncWith(pOther->_sfEastSpring);

    if(FieldBits::NoField != (SouthSpringFieldMask & whichField))
        _sfSouthSpring.syncWith(pOther->_sfSouthSpring);

    if(FieldBits::NoField != (WidthSpringFieldMask & whichField))
        _sfWidthSpring.syncWith(pOther->_sfWidthSpring);

    if(FieldBits::NoField != (HeightSpringFieldMask & whichField))
        _sfHeightSpring.syncWith(pOther->_sfHeightSpring);

    if(FieldBits::NoField != (HorizontalCenterSpringFieldMask & whichField))
        _sfHorizontalCenterSpring.syncWith(pOther->_sfHorizontalCenterSpring);

    if(FieldBits::NoField != (VerticalCenterSpringFieldMask & whichField))
        _sfVerticalCenterSpring.syncWith(pOther->_sfVerticalCenterSpring);

    if(FieldBits::NoField != (BaselineSpringFieldMask & whichField))
        _sfBaselineSpring.syncWith(pOther->_sfBaselineSpring);

    if(FieldBits::NoField != (ComponentFieldMask & whichField))
        _sfComponent.syncWith(pOther->_sfComponent);



}

void SpringLayoutConstraintsBase::execBeginEditImpl (const BitVector &whichField, 
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
DataType FieldDataTraits<SpringLayoutConstraintsPtr>::_type("SpringLayoutConstraintsPtr", "LayoutConstraintsPtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(SpringLayoutConstraintsPtr, OSG_USERINTERFACELIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(SpringLayoutConstraintsPtr, OSG_USERINTERFACELIB_DLLTMPLMAPPING);


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
    static Char8 cvsid_hpp       [] = OSGSPRINGLAYOUTCONSTRAINTSBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSPRINGLAYOUTCONSTRAINTSBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSPRINGLAYOUTCONSTRAINTSFIELDS_HEADER_CVSID;
}

OSG_END_NAMESPACE
