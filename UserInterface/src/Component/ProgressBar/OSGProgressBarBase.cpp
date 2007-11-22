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
 **     class ProgressBar!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILEPROGRESSBARINST

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "OSGProgressBarBase.h"
#include "OSGProgressBar.h"


OSG_BEGIN_NAMESPACE

const OSG::BitVector  ProgressBarBase::IndeterminateFieldMask = 
    (TypeTraits<BitVector>::One << ProgressBarBase::IndeterminateFieldId);

const OSG::BitVector  ProgressBarBase::IndeterminateBarMoveRateFieldMask = 
    (TypeTraits<BitVector>::One << ProgressBarBase::IndeterminateBarMoveRateFieldId);

const OSG::BitVector  ProgressBarBase::IndeterminateBarSizeFieldMask = 
    (TypeTraits<BitVector>::One << ProgressBarBase::IndeterminateBarSizeFieldId);

const OSG::BitVector  ProgressBarBase::EnableProgressStringFieldMask = 
    (TypeTraits<BitVector>::One << ProgressBarBase::EnableProgressStringFieldId);

const OSG::BitVector  ProgressBarBase::ProgressStringFieldMask = 
    (TypeTraits<BitVector>::One << ProgressBarBase::ProgressStringFieldId);

const OSG::BitVector  ProgressBarBase::VerticalAlignmentFieldMask = 
    (TypeTraits<BitVector>::One << ProgressBarBase::VerticalAlignmentFieldId);

const OSG::BitVector  ProgressBarBase::HorizontalAlignmentFieldMask = 
    (TypeTraits<BitVector>::One << ProgressBarBase::HorizontalAlignmentFieldId);

const OSG::BitVector  ProgressBarBase::FontFieldMask = 
    (TypeTraits<BitVector>::One << ProgressBarBase::FontFieldId);

const OSG::BitVector  ProgressBarBase::TextColorFieldMask = 
    (TypeTraits<BitVector>::One << ProgressBarBase::TextColorFieldId);

const OSG::BitVector  ProgressBarBase::OrientationFieldMask = 
    (TypeTraits<BitVector>::One << ProgressBarBase::OrientationFieldId);

const OSG::BitVector  ProgressBarBase::ProgressBarDrawObjectFieldMask = 
    (TypeTraits<BitVector>::One << ProgressBarBase::ProgressBarDrawObjectFieldId);

const OSG::BitVector ProgressBarBase::MTInfluenceMask = 
    (Inherited::MTInfluenceMask) | 
    (static_cast<BitVector>(0x0) << Inherited::NextFieldId); 


// Field descriptions

/*! \var bool            ProgressBarBase::_sfIndeterminate
    
*/
/*! \var Real32          ProgressBarBase::_sfIndeterminateBarMoveRate
    
*/
/*! \var Real32          ProgressBarBase::_sfIndeterminateBarSize
    
*/
/*! \var bool            ProgressBarBase::_sfEnableProgressString
    
*/
/*! \var std::string     ProgressBarBase::_sfProgressString
    
*/
/*! \var Real32          ProgressBarBase::_sfVerticalAlignment
    
*/
/*! \var Real32          ProgressBarBase::_sfHorizontalAlignment
    
*/
/*! \var UIFontPtr       ProgressBarBase::_sfFont
    
*/
/*! \var Color4f         ProgressBarBase::_sfTextColor
    
*/
/*! \var UInt32          ProgressBarBase::_sfOrientation
    
*/
/*! \var UIDrawObjectCanvasPtr ProgressBarBase::_sfProgressBarDrawObject
    
*/

//! ProgressBar description

FieldDescription *ProgressBarBase::_desc[] = 
{
    new FieldDescription(SFBool::getClassType(), 
                     "Indeterminate", 
                     IndeterminateFieldId, IndeterminateFieldMask,
                     false,
                     (FieldAccessMethod) &ProgressBarBase::getSFIndeterminate),
    new FieldDescription(SFReal32::getClassType(), 
                     "IndeterminateBarMoveRate", 
                     IndeterminateBarMoveRateFieldId, IndeterminateBarMoveRateFieldMask,
                     false,
                     (FieldAccessMethod) &ProgressBarBase::getSFIndeterminateBarMoveRate),
    new FieldDescription(SFReal32::getClassType(), 
                     "IndeterminateBarSize", 
                     IndeterminateBarSizeFieldId, IndeterminateBarSizeFieldMask,
                     false,
                     (FieldAccessMethod) &ProgressBarBase::getSFIndeterminateBarSize),
    new FieldDescription(SFBool::getClassType(), 
                     "EnableProgressString", 
                     EnableProgressStringFieldId, EnableProgressStringFieldMask,
                     false,
                     (FieldAccessMethod) &ProgressBarBase::getSFEnableProgressString),
    new FieldDescription(SFString::getClassType(), 
                     "ProgressString", 
                     ProgressStringFieldId, ProgressStringFieldMask,
                     false,
                     (FieldAccessMethod) &ProgressBarBase::getSFProgressString),
    new FieldDescription(SFReal32::getClassType(), 
                     "VerticalAlignment", 
                     VerticalAlignmentFieldId, VerticalAlignmentFieldMask,
                     false,
                     (FieldAccessMethod) &ProgressBarBase::getSFVerticalAlignment),
    new FieldDescription(SFReal32::getClassType(), 
                     "HorizontalAlignment", 
                     HorizontalAlignmentFieldId, HorizontalAlignmentFieldMask,
                     false,
                     (FieldAccessMethod) &ProgressBarBase::getSFHorizontalAlignment),
    new FieldDescription(SFUIFontPtr::getClassType(), 
                     "Font", 
                     FontFieldId, FontFieldMask,
                     false,
                     (FieldAccessMethod) &ProgressBarBase::getSFFont),
    new FieldDescription(SFColor4f::getClassType(), 
                     "TextColor", 
                     TextColorFieldId, TextColorFieldMask,
                     false,
                     (FieldAccessMethod) &ProgressBarBase::getSFTextColor),
    new FieldDescription(SFUInt32::getClassType(), 
                     "Orientation", 
                     OrientationFieldId, OrientationFieldMask,
                     false,
                     (FieldAccessMethod) &ProgressBarBase::getSFOrientation),
    new FieldDescription(SFUIDrawObjectCanvasPtr::getClassType(), 
                     "ProgressBarDrawObject", 
                     ProgressBarDrawObjectFieldId, ProgressBarDrawObjectFieldMask,
                     false,
                     (FieldAccessMethod) &ProgressBarBase::getSFProgressBarDrawObject)
};


FieldContainerType ProgressBarBase::_type(
    "ProgressBar",
    "Component",
    NULL,
    (PrototypeCreateF) &ProgressBarBase::createEmpty,
    ProgressBar::initMethod,
    _desc,
    sizeof(_desc));

//OSG_FIELD_CONTAINER_DEF(ProgressBarBase, ProgressBarPtr)

/*------------------------------ get -----------------------------------*/

FieldContainerType &ProgressBarBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &ProgressBarBase::getType(void) const 
{
    return _type;
} 


FieldContainerPtr ProgressBarBase::shallowCopy(void) const 
{ 
    ProgressBarPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const ProgressBar *>(this)); 

    return returnValue; 
}

UInt32 ProgressBarBase::getContainerSize(void) const 
{ 
    return sizeof(ProgressBar); 
}


#if !defined(OSG_FIXED_MFIELDSYNC)
void ProgressBarBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField)
{
    this->executeSyncImpl((ProgressBarBase *) &other, whichField);
}
#else
void ProgressBarBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField,                                    const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((ProgressBarBase *) &other, whichField, sInfo);
}
void ProgressBarBase::execBeginEdit(const BitVector &whichField, 
                                            UInt32     uiAspect,
                                            UInt32     uiContainerSize) 
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}

void ProgressBarBase::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    Inherited::onDestroyAspect(uiId, uiAspect);

}
#endif

/*------------------------- constructors ----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

ProgressBarBase::ProgressBarBase(void) :
    _sfIndeterminate          (bool(false)), 
    _sfIndeterminateBarMoveRate(Real32(0.5)), 
    _sfIndeterminateBarSize   (Real32(0.25)), 
    _sfEnableProgressString   (bool(false)), 
    _sfProgressString         (), 
    _sfVerticalAlignment      (Real32(0.5)), 
    _sfHorizontalAlignment    (Real32(0.5)), 
    _sfFont                   (), 
    _sfTextColor              (), 
    _sfOrientation            (UInt32(VERTICAL_ALIGNMENT)), 
    _sfProgressBarDrawObject  (), 
    Inherited() 
{
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

ProgressBarBase::ProgressBarBase(const ProgressBarBase &source) :
    _sfIndeterminate          (source._sfIndeterminate          ), 
    _sfIndeterminateBarMoveRate(source._sfIndeterminateBarMoveRate), 
    _sfIndeterminateBarSize   (source._sfIndeterminateBarSize   ), 
    _sfEnableProgressString   (source._sfEnableProgressString   ), 
    _sfProgressString         (source._sfProgressString         ), 
    _sfVerticalAlignment      (source._sfVerticalAlignment      ), 
    _sfHorizontalAlignment    (source._sfHorizontalAlignment    ), 
    _sfFont                   (source._sfFont                   ), 
    _sfTextColor              (source._sfTextColor              ), 
    _sfOrientation            (source._sfOrientation            ), 
    _sfProgressBarDrawObject  (source._sfProgressBarDrawObject  ), 
    Inherited                 (source)
{
}

/*-------------------------- destructors ----------------------------------*/

ProgressBarBase::~ProgressBarBase(void)
{
}

/*------------------------------ access -----------------------------------*/

UInt32 ProgressBarBase::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (IndeterminateFieldMask & whichField))
    {
        returnValue += _sfIndeterminate.getBinSize();
    }

    if(FieldBits::NoField != (IndeterminateBarMoveRateFieldMask & whichField))
    {
        returnValue += _sfIndeterminateBarMoveRate.getBinSize();
    }

    if(FieldBits::NoField != (IndeterminateBarSizeFieldMask & whichField))
    {
        returnValue += _sfIndeterminateBarSize.getBinSize();
    }

    if(FieldBits::NoField != (EnableProgressStringFieldMask & whichField))
    {
        returnValue += _sfEnableProgressString.getBinSize();
    }

    if(FieldBits::NoField != (ProgressStringFieldMask & whichField))
    {
        returnValue += _sfProgressString.getBinSize();
    }

    if(FieldBits::NoField != (VerticalAlignmentFieldMask & whichField))
    {
        returnValue += _sfVerticalAlignment.getBinSize();
    }

    if(FieldBits::NoField != (HorizontalAlignmentFieldMask & whichField))
    {
        returnValue += _sfHorizontalAlignment.getBinSize();
    }

    if(FieldBits::NoField != (FontFieldMask & whichField))
    {
        returnValue += _sfFont.getBinSize();
    }

    if(FieldBits::NoField != (TextColorFieldMask & whichField))
    {
        returnValue += _sfTextColor.getBinSize();
    }

    if(FieldBits::NoField != (OrientationFieldMask & whichField))
    {
        returnValue += _sfOrientation.getBinSize();
    }

    if(FieldBits::NoField != (ProgressBarDrawObjectFieldMask & whichField))
    {
        returnValue += _sfProgressBarDrawObject.getBinSize();
    }


    return returnValue;
}

void ProgressBarBase::copyToBin(      BinaryDataHandler &pMem,
                                  const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (IndeterminateFieldMask & whichField))
    {
        _sfIndeterminate.copyToBin(pMem);
    }

    if(FieldBits::NoField != (IndeterminateBarMoveRateFieldMask & whichField))
    {
        _sfIndeterminateBarMoveRate.copyToBin(pMem);
    }

    if(FieldBits::NoField != (IndeterminateBarSizeFieldMask & whichField))
    {
        _sfIndeterminateBarSize.copyToBin(pMem);
    }

    if(FieldBits::NoField != (EnableProgressStringFieldMask & whichField))
    {
        _sfEnableProgressString.copyToBin(pMem);
    }

    if(FieldBits::NoField != (ProgressStringFieldMask & whichField))
    {
        _sfProgressString.copyToBin(pMem);
    }

    if(FieldBits::NoField != (VerticalAlignmentFieldMask & whichField))
    {
        _sfVerticalAlignment.copyToBin(pMem);
    }

    if(FieldBits::NoField != (HorizontalAlignmentFieldMask & whichField))
    {
        _sfHorizontalAlignment.copyToBin(pMem);
    }

    if(FieldBits::NoField != (FontFieldMask & whichField))
    {
        _sfFont.copyToBin(pMem);
    }

    if(FieldBits::NoField != (TextColorFieldMask & whichField))
    {
        _sfTextColor.copyToBin(pMem);
    }

    if(FieldBits::NoField != (OrientationFieldMask & whichField))
    {
        _sfOrientation.copyToBin(pMem);
    }

    if(FieldBits::NoField != (ProgressBarDrawObjectFieldMask & whichField))
    {
        _sfProgressBarDrawObject.copyToBin(pMem);
    }


}

void ProgressBarBase::copyFromBin(      BinaryDataHandler &pMem,
                                    const BitVector    &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (IndeterminateFieldMask & whichField))
    {
        _sfIndeterminate.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (IndeterminateBarMoveRateFieldMask & whichField))
    {
        _sfIndeterminateBarMoveRate.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (IndeterminateBarSizeFieldMask & whichField))
    {
        _sfIndeterminateBarSize.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (EnableProgressStringFieldMask & whichField))
    {
        _sfEnableProgressString.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (ProgressStringFieldMask & whichField))
    {
        _sfProgressString.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (VerticalAlignmentFieldMask & whichField))
    {
        _sfVerticalAlignment.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (HorizontalAlignmentFieldMask & whichField))
    {
        _sfHorizontalAlignment.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (FontFieldMask & whichField))
    {
        _sfFont.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (TextColorFieldMask & whichField))
    {
        _sfTextColor.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (OrientationFieldMask & whichField))
    {
        _sfOrientation.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (ProgressBarDrawObjectFieldMask & whichField))
    {
        _sfProgressBarDrawObject.copyFromBin(pMem);
    }


}

#if !defined(OSG_FIXED_MFIELDSYNC)
void ProgressBarBase::executeSyncImpl(      ProgressBarBase *pOther,
                                        const BitVector         &whichField)
{

    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (IndeterminateFieldMask & whichField))
        _sfIndeterminate.syncWith(pOther->_sfIndeterminate);

    if(FieldBits::NoField != (IndeterminateBarMoveRateFieldMask & whichField))
        _sfIndeterminateBarMoveRate.syncWith(pOther->_sfIndeterminateBarMoveRate);

    if(FieldBits::NoField != (IndeterminateBarSizeFieldMask & whichField))
        _sfIndeterminateBarSize.syncWith(pOther->_sfIndeterminateBarSize);

    if(FieldBits::NoField != (EnableProgressStringFieldMask & whichField))
        _sfEnableProgressString.syncWith(pOther->_sfEnableProgressString);

    if(FieldBits::NoField != (ProgressStringFieldMask & whichField))
        _sfProgressString.syncWith(pOther->_sfProgressString);

    if(FieldBits::NoField != (VerticalAlignmentFieldMask & whichField))
        _sfVerticalAlignment.syncWith(pOther->_sfVerticalAlignment);

    if(FieldBits::NoField != (HorizontalAlignmentFieldMask & whichField))
        _sfHorizontalAlignment.syncWith(pOther->_sfHorizontalAlignment);

    if(FieldBits::NoField != (FontFieldMask & whichField))
        _sfFont.syncWith(pOther->_sfFont);

    if(FieldBits::NoField != (TextColorFieldMask & whichField))
        _sfTextColor.syncWith(pOther->_sfTextColor);

    if(FieldBits::NoField != (OrientationFieldMask & whichField))
        _sfOrientation.syncWith(pOther->_sfOrientation);

    if(FieldBits::NoField != (ProgressBarDrawObjectFieldMask & whichField))
        _sfProgressBarDrawObject.syncWith(pOther->_sfProgressBarDrawObject);


}
#else
void ProgressBarBase::executeSyncImpl(      ProgressBarBase *pOther,
                                        const BitVector         &whichField,
                                        const SyncInfo          &sInfo      )
{

    Inherited::executeSyncImpl(pOther, whichField, sInfo);

    if(FieldBits::NoField != (IndeterminateFieldMask & whichField))
        _sfIndeterminate.syncWith(pOther->_sfIndeterminate);

    if(FieldBits::NoField != (IndeterminateBarMoveRateFieldMask & whichField))
        _sfIndeterminateBarMoveRate.syncWith(pOther->_sfIndeterminateBarMoveRate);

    if(FieldBits::NoField != (IndeterminateBarSizeFieldMask & whichField))
        _sfIndeterminateBarSize.syncWith(pOther->_sfIndeterminateBarSize);

    if(FieldBits::NoField != (EnableProgressStringFieldMask & whichField))
        _sfEnableProgressString.syncWith(pOther->_sfEnableProgressString);

    if(FieldBits::NoField != (ProgressStringFieldMask & whichField))
        _sfProgressString.syncWith(pOther->_sfProgressString);

    if(FieldBits::NoField != (VerticalAlignmentFieldMask & whichField))
        _sfVerticalAlignment.syncWith(pOther->_sfVerticalAlignment);

    if(FieldBits::NoField != (HorizontalAlignmentFieldMask & whichField))
        _sfHorizontalAlignment.syncWith(pOther->_sfHorizontalAlignment);

    if(FieldBits::NoField != (FontFieldMask & whichField))
        _sfFont.syncWith(pOther->_sfFont);

    if(FieldBits::NoField != (TextColorFieldMask & whichField))
        _sfTextColor.syncWith(pOther->_sfTextColor);

    if(FieldBits::NoField != (OrientationFieldMask & whichField))
        _sfOrientation.syncWith(pOther->_sfOrientation);

    if(FieldBits::NoField != (ProgressBarDrawObjectFieldMask & whichField))
        _sfProgressBarDrawObject.syncWith(pOther->_sfProgressBarDrawObject);



}

void ProgressBarBase::execBeginEditImpl (const BitVector &whichField, 
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
DataType FieldDataTraits<ProgressBarPtr>::_type("ProgressBarPtr", "ComponentPtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(ProgressBarPtr, OSG_USERINTERFACELIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(ProgressBarPtr, OSG_USERINTERFACELIB_DLLTMPLMAPPING);


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
    static Char8 cvsid_hpp       [] = OSGPROGRESSBARBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPROGRESSBARBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPROGRESSBARFIELDS_HEADER_CVSID;
}

OSG_END_NAMESPACE
