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
 **     class UIForeground!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILEUIFOREGROUNDINST

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "OSGUIForegroundBase.h"
#include "OSGUIForeground.h"


OSG_BEGIN_NAMESPACE

const OSG::BitVector  UIForegroundBase::RootFrameFieldMask = 
    (TypeTraits<BitVector>::One << UIForegroundBase::RootFrameFieldId);

const OSG::BitVector  UIForegroundBase::GraphicsFieldMask = 
    (TypeTraits<BitVector>::One << UIForegroundBase::GraphicsFieldId);

const OSG::BitVector  UIForegroundBase::FramePositionOffsetFieldMask = 
    (TypeTraits<BitVector>::One << UIForegroundBase::FramePositionOffsetFieldId);

const OSG::BitVector  UIForegroundBase::FrameBoundsFieldMask = 
    (TypeTraits<BitVector>::One << UIForegroundBase::FrameBoundsFieldId);

const OSG::BitVector  UIForegroundBase::VerticalAlignmentFieldMask = 
    (TypeTraits<BitVector>::One << UIForegroundBase::VerticalAlignmentFieldId);

const OSG::BitVector  UIForegroundBase::HorizontalAlignmentFieldMask = 
    (TypeTraits<BitVector>::One << UIForegroundBase::HorizontalAlignmentFieldId);

const OSG::BitVector UIForegroundBase::MTInfluenceMask = 
    (Inherited::MTInfluenceMask) | 
    (static_cast<BitVector>(0x0) << Inherited::NextFieldId); 


// Field descriptions

/*! \var FramePtr        UIForegroundBase::_sfRootFrame
    
*/
/*! \var GraphicsPtr     UIForegroundBase::_sfGraphics
    
*/
/*! \var Vec2s           UIForegroundBase::_sfFramePositionOffset
    
*/
/*! \var Vec2f           UIForegroundBase::_sfFrameBounds
    
*/
/*! \var UInt32          UIForegroundBase::_sfVerticalAlignment
    
*/
/*! \var UInt32          UIForegroundBase::_sfHorizontalAlignment
    
*/

//! UIForeground description

FieldDescription *UIForegroundBase::_desc[] = 
{
    new FieldDescription(SFFramePtr::getClassType(), 
                     "RootFrame", 
                     RootFrameFieldId, RootFrameFieldMask,
                     false,
                     (FieldAccessMethod) &UIForegroundBase::getSFRootFrame),
    new FieldDescription(SFGraphicsPtr::getClassType(), 
                     "Graphics", 
                     GraphicsFieldId, GraphicsFieldMask,
                     false,
                     (FieldAccessMethod) &UIForegroundBase::getSFGraphics),
    new FieldDescription(SFVec2s::getClassType(), 
                     "FramePositionOffset", 
                     FramePositionOffsetFieldId, FramePositionOffsetFieldMask,
                     false,
                     (FieldAccessMethod) &UIForegroundBase::getSFFramePositionOffset),
    new FieldDescription(SFVec2f::getClassType(), 
                     "FrameBounds", 
                     FrameBoundsFieldId, FrameBoundsFieldMask,
                     false,
                     (FieldAccessMethod) &UIForegroundBase::getSFFrameBounds),
    new FieldDescription(SFUInt32::getClassType(), 
                     "VerticalAlignment", 
                     VerticalAlignmentFieldId, VerticalAlignmentFieldMask,
                     false,
                     (FieldAccessMethod) &UIForegroundBase::getSFVerticalAlignment),
    new FieldDescription(SFUInt32::getClassType(), 
                     "HorizontalAlignment", 
                     HorizontalAlignmentFieldId, HorizontalAlignmentFieldMask,
                     false,
                     (FieldAccessMethod) &UIForegroundBase::getSFHorizontalAlignment)
};


FieldContainerType UIForegroundBase::_type(
    "UIForeground",
    "Foreground",
    NULL,
    (PrototypeCreateF) &UIForegroundBase::createEmpty,
    UIForeground::initMethod,
    _desc,
    sizeof(_desc));

//OSG_FIELD_CONTAINER_DEF(UIForegroundBase, UIForegroundPtr)

/*------------------------------ get -----------------------------------*/

FieldContainerType &UIForegroundBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &UIForegroundBase::getType(void) const 
{
    return _type;
} 


FieldContainerPtr UIForegroundBase::shallowCopy(void) const 
{ 
    UIForegroundPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const UIForeground *>(this)); 

    return returnValue; 
}

UInt32 UIForegroundBase::getContainerSize(void) const 
{ 
    return sizeof(UIForeground); 
}


#if !defined(OSG_FIXED_MFIELDSYNC)
void UIForegroundBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField)
{
    this->executeSyncImpl((UIForegroundBase *) &other, whichField);
}
#else
void UIForegroundBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField,                                    const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((UIForegroundBase *) &other, whichField, sInfo);
}
void UIForegroundBase::execBeginEdit(const BitVector &whichField, 
                                            UInt32     uiAspect,
                                            UInt32     uiContainerSize) 
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}

void UIForegroundBase::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    Inherited::onDestroyAspect(uiId, uiAspect);

}
#endif

/*------------------------- constructors ----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

UIForegroundBase::UIForegroundBase(void) :
    _sfRootFrame              (), 
    _sfGraphics               (), 
    _sfFramePositionOffset    (), 
    _sfFrameBounds            (), 
    _sfVerticalAlignment      (UInt32(0)), 
    _sfHorizontalAlignment    (UInt32(0)), 
    Inherited() 
{
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

UIForegroundBase::UIForegroundBase(const UIForegroundBase &source) :
    _sfRootFrame              (source._sfRootFrame              ), 
    _sfGraphics               (source._sfGraphics               ), 
    _sfFramePositionOffset    (source._sfFramePositionOffset    ), 
    _sfFrameBounds            (source._sfFrameBounds            ), 
    _sfVerticalAlignment      (source._sfVerticalAlignment      ), 
    _sfHorizontalAlignment    (source._sfHorizontalAlignment    ), 
    Inherited                 (source)
{
}

/*-------------------------- destructors ----------------------------------*/

UIForegroundBase::~UIForegroundBase(void)
{
}

/*------------------------------ access -----------------------------------*/

UInt32 UIForegroundBase::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (RootFrameFieldMask & whichField))
    {
        returnValue += _sfRootFrame.getBinSize();
    }

    if(FieldBits::NoField != (GraphicsFieldMask & whichField))
    {
        returnValue += _sfGraphics.getBinSize();
    }

    if(FieldBits::NoField != (FramePositionOffsetFieldMask & whichField))
    {
        returnValue += _sfFramePositionOffset.getBinSize();
    }

    if(FieldBits::NoField != (FrameBoundsFieldMask & whichField))
    {
        returnValue += _sfFrameBounds.getBinSize();
    }

    if(FieldBits::NoField != (VerticalAlignmentFieldMask & whichField))
    {
        returnValue += _sfVerticalAlignment.getBinSize();
    }

    if(FieldBits::NoField != (HorizontalAlignmentFieldMask & whichField))
    {
        returnValue += _sfHorizontalAlignment.getBinSize();
    }


    return returnValue;
}

void UIForegroundBase::copyToBin(      BinaryDataHandler &pMem,
                                  const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (RootFrameFieldMask & whichField))
    {
        _sfRootFrame.copyToBin(pMem);
    }

    if(FieldBits::NoField != (GraphicsFieldMask & whichField))
    {
        _sfGraphics.copyToBin(pMem);
    }

    if(FieldBits::NoField != (FramePositionOffsetFieldMask & whichField))
    {
        _sfFramePositionOffset.copyToBin(pMem);
    }

    if(FieldBits::NoField != (FrameBoundsFieldMask & whichField))
    {
        _sfFrameBounds.copyToBin(pMem);
    }

    if(FieldBits::NoField != (VerticalAlignmentFieldMask & whichField))
    {
        _sfVerticalAlignment.copyToBin(pMem);
    }

    if(FieldBits::NoField != (HorizontalAlignmentFieldMask & whichField))
    {
        _sfHorizontalAlignment.copyToBin(pMem);
    }


}

void UIForegroundBase::copyFromBin(      BinaryDataHandler &pMem,
                                    const BitVector    &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (RootFrameFieldMask & whichField))
    {
        _sfRootFrame.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (GraphicsFieldMask & whichField))
    {
        _sfGraphics.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (FramePositionOffsetFieldMask & whichField))
    {
        _sfFramePositionOffset.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (FrameBoundsFieldMask & whichField))
    {
        _sfFrameBounds.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (VerticalAlignmentFieldMask & whichField))
    {
        _sfVerticalAlignment.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (HorizontalAlignmentFieldMask & whichField))
    {
        _sfHorizontalAlignment.copyFromBin(pMem);
    }


}

#if !defined(OSG_FIXED_MFIELDSYNC)
void UIForegroundBase::executeSyncImpl(      UIForegroundBase *pOther,
                                        const BitVector         &whichField)
{

    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (RootFrameFieldMask & whichField))
        _sfRootFrame.syncWith(pOther->_sfRootFrame);

    if(FieldBits::NoField != (GraphicsFieldMask & whichField))
        _sfGraphics.syncWith(pOther->_sfGraphics);

    if(FieldBits::NoField != (FramePositionOffsetFieldMask & whichField))
        _sfFramePositionOffset.syncWith(pOther->_sfFramePositionOffset);

    if(FieldBits::NoField != (FrameBoundsFieldMask & whichField))
        _sfFrameBounds.syncWith(pOther->_sfFrameBounds);

    if(FieldBits::NoField != (VerticalAlignmentFieldMask & whichField))
        _sfVerticalAlignment.syncWith(pOther->_sfVerticalAlignment);

    if(FieldBits::NoField != (HorizontalAlignmentFieldMask & whichField))
        _sfHorizontalAlignment.syncWith(pOther->_sfHorizontalAlignment);


}
#else
void UIForegroundBase::executeSyncImpl(      UIForegroundBase *pOther,
                                        const BitVector         &whichField,
                                        const SyncInfo          &sInfo      )
{

    Inherited::executeSyncImpl(pOther, whichField, sInfo);

    if(FieldBits::NoField != (RootFrameFieldMask & whichField))
        _sfRootFrame.syncWith(pOther->_sfRootFrame);

    if(FieldBits::NoField != (GraphicsFieldMask & whichField))
        _sfGraphics.syncWith(pOther->_sfGraphics);

    if(FieldBits::NoField != (FramePositionOffsetFieldMask & whichField))
        _sfFramePositionOffset.syncWith(pOther->_sfFramePositionOffset);

    if(FieldBits::NoField != (FrameBoundsFieldMask & whichField))
        _sfFrameBounds.syncWith(pOther->_sfFrameBounds);

    if(FieldBits::NoField != (VerticalAlignmentFieldMask & whichField))
        _sfVerticalAlignment.syncWith(pOther->_sfVerticalAlignment);

    if(FieldBits::NoField != (HorizontalAlignmentFieldMask & whichField))
        _sfHorizontalAlignment.syncWith(pOther->_sfHorizontalAlignment);



}

void UIForegroundBase::execBeginEditImpl (const BitVector &whichField, 
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
DataType FieldDataTraits<UIForegroundPtr>::_type("UIForegroundPtr", "ForegroundPtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(UIForegroundPtr, );
OSG_DLLEXPORT_MFIELD_DEF1(UIForegroundPtr, );


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
    static Char8 cvsid_hpp       [] = OSGUIFOREGROUNDBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGUIFOREGROUNDBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGUIFOREGROUNDFIELDS_HEADER_CVSID;
}

OSG_END_NAMESPACE

