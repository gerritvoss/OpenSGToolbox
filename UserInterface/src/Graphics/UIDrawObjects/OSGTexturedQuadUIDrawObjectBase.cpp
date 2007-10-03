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
 **     class TexturedQuadUIDrawObject!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILETEXTUREDQUADUIDRAWOBJECTINST

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "OSGTexturedQuadUIDrawObjectBase.h"
#include "OSGTexturedQuadUIDrawObject.h"


OSG_BEGIN_NAMESPACE

const OSG::BitVector  TexturedQuadUIDrawObjectBase::Point1FieldMask = 
    (TypeTraits<BitVector>::One << TexturedQuadUIDrawObjectBase::Point1FieldId);

const OSG::BitVector  TexturedQuadUIDrawObjectBase::Point2FieldMask = 
    (TypeTraits<BitVector>::One << TexturedQuadUIDrawObjectBase::Point2FieldId);

const OSG::BitVector  TexturedQuadUIDrawObjectBase::Point3FieldMask = 
    (TypeTraits<BitVector>::One << TexturedQuadUIDrawObjectBase::Point3FieldId);

const OSG::BitVector  TexturedQuadUIDrawObjectBase::Point4FieldMask = 
    (TypeTraits<BitVector>::One << TexturedQuadUIDrawObjectBase::Point4FieldId);

const OSG::BitVector  TexturedQuadUIDrawObjectBase::TexCoord1FieldMask = 
    (TypeTraits<BitVector>::One << TexturedQuadUIDrawObjectBase::TexCoord1FieldId);

const OSG::BitVector  TexturedQuadUIDrawObjectBase::TexCoord2FieldMask = 
    (TypeTraits<BitVector>::One << TexturedQuadUIDrawObjectBase::TexCoord2FieldId);

const OSG::BitVector  TexturedQuadUIDrawObjectBase::TexCoord3FieldMask = 
    (TypeTraits<BitVector>::One << TexturedQuadUIDrawObjectBase::TexCoord3FieldId);

const OSG::BitVector  TexturedQuadUIDrawObjectBase::TexCoord4FieldMask = 
    (TypeTraits<BitVector>::One << TexturedQuadUIDrawObjectBase::TexCoord4FieldId);

const OSG::BitVector  TexturedQuadUIDrawObjectBase::TextureFieldMask = 
    (TypeTraits<BitVector>::One << TexturedQuadUIDrawObjectBase::TextureFieldId);

const OSG::BitVector  TexturedQuadUIDrawObjectBase::OpacityFieldMask = 
    (TypeTraits<BitVector>::One << TexturedQuadUIDrawObjectBase::OpacityFieldId);

const OSG::BitVector TexturedQuadUIDrawObjectBase::MTInfluenceMask = 
    (Inherited::MTInfluenceMask) | 
    (static_cast<BitVector>(0x0) << Inherited::NextFieldId); 


// Field descriptions

/*! \var Pnt2s           TexturedQuadUIDrawObjectBase::_sfPoint1
    
*/
/*! \var Pnt2s           TexturedQuadUIDrawObjectBase::_sfPoint2
    
*/
/*! \var Pnt2s           TexturedQuadUIDrawObjectBase::_sfPoint3
    
*/
/*! \var Pnt2s           TexturedQuadUIDrawObjectBase::_sfPoint4
    
*/
/*! \var Vec2f           TexturedQuadUIDrawObjectBase::_sfTexCoord1
    
*/
/*! \var Vec2f           TexturedQuadUIDrawObjectBase::_sfTexCoord2
    
*/
/*! \var Vec2f           TexturedQuadUIDrawObjectBase::_sfTexCoord3
    
*/
/*! \var Vec2f           TexturedQuadUIDrawObjectBase::_sfTexCoord4
    
*/
/*! \var TextureChunkPtr TexturedQuadUIDrawObjectBase::_sfTexture
    
*/
/*! \var Real32          TexturedQuadUIDrawObjectBase::_sfOpacity
    
*/

//! TexturedQuadUIDrawObject description

FieldDescription *TexturedQuadUIDrawObjectBase::_desc[] = 
{
    new FieldDescription(SFPnt2s::getClassType(), 
                     "Point1", 
                     Point1FieldId, Point1FieldMask,
                     false,
                     (FieldAccessMethod) &TexturedQuadUIDrawObjectBase::getSFPoint1),
    new FieldDescription(SFPnt2s::getClassType(), 
                     "Point2", 
                     Point2FieldId, Point2FieldMask,
                     false,
                     (FieldAccessMethod) &TexturedQuadUIDrawObjectBase::getSFPoint2),
    new FieldDescription(SFPnt2s::getClassType(), 
                     "Point3", 
                     Point3FieldId, Point3FieldMask,
                     false,
                     (FieldAccessMethod) &TexturedQuadUIDrawObjectBase::getSFPoint3),
    new FieldDescription(SFPnt2s::getClassType(), 
                     "Point4", 
                     Point4FieldId, Point4FieldMask,
                     false,
                     (FieldAccessMethod) &TexturedQuadUIDrawObjectBase::getSFPoint4),
    new FieldDescription(SFVec2f::getClassType(), 
                     "TexCoord1", 
                     TexCoord1FieldId, TexCoord1FieldMask,
                     false,
                     (FieldAccessMethod) &TexturedQuadUIDrawObjectBase::getSFTexCoord1),
    new FieldDescription(SFVec2f::getClassType(), 
                     "TexCoord2", 
                     TexCoord2FieldId, TexCoord2FieldMask,
                     false,
                     (FieldAccessMethod) &TexturedQuadUIDrawObjectBase::getSFTexCoord2),
    new FieldDescription(SFVec2f::getClassType(), 
                     "TexCoord3", 
                     TexCoord3FieldId, TexCoord3FieldMask,
                     false,
                     (FieldAccessMethod) &TexturedQuadUIDrawObjectBase::getSFTexCoord3),
    new FieldDescription(SFVec2f::getClassType(), 
                     "TexCoord4", 
                     TexCoord4FieldId, TexCoord4FieldMask,
                     false,
                     (FieldAccessMethod) &TexturedQuadUIDrawObjectBase::getSFTexCoord4),
    new FieldDescription(SFTextureChunkPtr::getClassType(), 
                     "Texture", 
                     TextureFieldId, TextureFieldMask,
                     false,
                     (FieldAccessMethod) &TexturedQuadUIDrawObjectBase::getSFTexture),
    new FieldDescription(SFReal32::getClassType(), 
                     "Opacity", 
                     OpacityFieldId, OpacityFieldMask,
                     false,
                     (FieldAccessMethod) &TexturedQuadUIDrawObjectBase::getSFOpacity)
};


FieldContainerType TexturedQuadUIDrawObjectBase::_type(
    "TexturedQuadUIDrawObject",
    "UIDrawObject",
    NULL,
    (PrototypeCreateF) &TexturedQuadUIDrawObjectBase::createEmpty,
    TexturedQuadUIDrawObject::initMethod,
    _desc,
    sizeof(_desc));

//OSG_FIELD_CONTAINER_DEF(TexturedQuadUIDrawObjectBase, TexturedQuadUIDrawObjectPtr)

/*------------------------------ get -----------------------------------*/

FieldContainerType &TexturedQuadUIDrawObjectBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &TexturedQuadUIDrawObjectBase::getType(void) const 
{
    return _type;
} 


FieldContainerPtr TexturedQuadUIDrawObjectBase::shallowCopy(void) const 
{ 
    TexturedQuadUIDrawObjectPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const TexturedQuadUIDrawObject *>(this)); 

    return returnValue; 
}

UInt32 TexturedQuadUIDrawObjectBase::getContainerSize(void) const 
{ 
    return sizeof(TexturedQuadUIDrawObject); 
}


#if !defined(OSG_FIXED_MFIELDSYNC)
void TexturedQuadUIDrawObjectBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField)
{
    this->executeSyncImpl((TexturedQuadUIDrawObjectBase *) &other, whichField);
}
#else
void TexturedQuadUIDrawObjectBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField,                                    const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((TexturedQuadUIDrawObjectBase *) &other, whichField, sInfo);
}
void TexturedQuadUIDrawObjectBase::execBeginEdit(const BitVector &whichField, 
                                            UInt32     uiAspect,
                                            UInt32     uiContainerSize) 
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}

void TexturedQuadUIDrawObjectBase::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    Inherited::onDestroyAspect(uiId, uiAspect);

}
#endif

/*------------------------- constructors ----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

TexturedQuadUIDrawObjectBase::TexturedQuadUIDrawObjectBase(void) :
    _sfPoint1                 (Pnt2s(0,0)), 
    _sfPoint2                 (Pnt2s(0,1)), 
    _sfPoint3                 (Pnt2s(1,1)), 
    _sfPoint4                 (Pnt2s(1,0)), 
    _sfTexCoord1              (Vec2f(0.0,0.0)), 
    _sfTexCoord2              (Vec2f(0.0,1.0)), 
    _sfTexCoord3              (Vec2f(1.0,1.0)), 
    _sfTexCoord4              (Vec2f(1.0,0.0)), 
    _sfTexture                (TextureChunkPtr(NullFC)), 
    _sfOpacity                (Real32(1.0)), 
    Inherited() 
{
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

TexturedQuadUIDrawObjectBase::TexturedQuadUIDrawObjectBase(const TexturedQuadUIDrawObjectBase &source) :
    _sfPoint1                 (source._sfPoint1                 ), 
    _sfPoint2                 (source._sfPoint2                 ), 
    _sfPoint3                 (source._sfPoint3                 ), 
    _sfPoint4                 (source._sfPoint4                 ), 
    _sfTexCoord1              (source._sfTexCoord1              ), 
    _sfTexCoord2              (source._sfTexCoord2              ), 
    _sfTexCoord3              (source._sfTexCoord3              ), 
    _sfTexCoord4              (source._sfTexCoord4              ), 
    _sfTexture                (source._sfTexture                ), 
    _sfOpacity                (source._sfOpacity                ), 
    Inherited                 (source)
{
}

/*-------------------------- destructors ----------------------------------*/

TexturedQuadUIDrawObjectBase::~TexturedQuadUIDrawObjectBase(void)
{
}

/*------------------------------ access -----------------------------------*/

UInt32 TexturedQuadUIDrawObjectBase::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (Point1FieldMask & whichField))
    {
        returnValue += _sfPoint1.getBinSize();
    }

    if(FieldBits::NoField != (Point2FieldMask & whichField))
    {
        returnValue += _sfPoint2.getBinSize();
    }

    if(FieldBits::NoField != (Point3FieldMask & whichField))
    {
        returnValue += _sfPoint3.getBinSize();
    }

    if(FieldBits::NoField != (Point4FieldMask & whichField))
    {
        returnValue += _sfPoint4.getBinSize();
    }

    if(FieldBits::NoField != (TexCoord1FieldMask & whichField))
    {
        returnValue += _sfTexCoord1.getBinSize();
    }

    if(FieldBits::NoField != (TexCoord2FieldMask & whichField))
    {
        returnValue += _sfTexCoord2.getBinSize();
    }

    if(FieldBits::NoField != (TexCoord3FieldMask & whichField))
    {
        returnValue += _sfTexCoord3.getBinSize();
    }

    if(FieldBits::NoField != (TexCoord4FieldMask & whichField))
    {
        returnValue += _sfTexCoord4.getBinSize();
    }

    if(FieldBits::NoField != (TextureFieldMask & whichField))
    {
        returnValue += _sfTexture.getBinSize();
    }

    if(FieldBits::NoField != (OpacityFieldMask & whichField))
    {
        returnValue += _sfOpacity.getBinSize();
    }


    return returnValue;
}

void TexturedQuadUIDrawObjectBase::copyToBin(      BinaryDataHandler &pMem,
                                  const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (Point1FieldMask & whichField))
    {
        _sfPoint1.copyToBin(pMem);
    }

    if(FieldBits::NoField != (Point2FieldMask & whichField))
    {
        _sfPoint2.copyToBin(pMem);
    }

    if(FieldBits::NoField != (Point3FieldMask & whichField))
    {
        _sfPoint3.copyToBin(pMem);
    }

    if(FieldBits::NoField != (Point4FieldMask & whichField))
    {
        _sfPoint4.copyToBin(pMem);
    }

    if(FieldBits::NoField != (TexCoord1FieldMask & whichField))
    {
        _sfTexCoord1.copyToBin(pMem);
    }

    if(FieldBits::NoField != (TexCoord2FieldMask & whichField))
    {
        _sfTexCoord2.copyToBin(pMem);
    }

    if(FieldBits::NoField != (TexCoord3FieldMask & whichField))
    {
        _sfTexCoord3.copyToBin(pMem);
    }

    if(FieldBits::NoField != (TexCoord4FieldMask & whichField))
    {
        _sfTexCoord4.copyToBin(pMem);
    }

    if(FieldBits::NoField != (TextureFieldMask & whichField))
    {
        _sfTexture.copyToBin(pMem);
    }

    if(FieldBits::NoField != (OpacityFieldMask & whichField))
    {
        _sfOpacity.copyToBin(pMem);
    }


}

void TexturedQuadUIDrawObjectBase::copyFromBin(      BinaryDataHandler &pMem,
                                    const BitVector    &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (Point1FieldMask & whichField))
    {
        _sfPoint1.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (Point2FieldMask & whichField))
    {
        _sfPoint2.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (Point3FieldMask & whichField))
    {
        _sfPoint3.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (Point4FieldMask & whichField))
    {
        _sfPoint4.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (TexCoord1FieldMask & whichField))
    {
        _sfTexCoord1.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (TexCoord2FieldMask & whichField))
    {
        _sfTexCoord2.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (TexCoord3FieldMask & whichField))
    {
        _sfTexCoord3.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (TexCoord4FieldMask & whichField))
    {
        _sfTexCoord4.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (TextureFieldMask & whichField))
    {
        _sfTexture.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (OpacityFieldMask & whichField))
    {
        _sfOpacity.copyFromBin(pMem);
    }


}

#if !defined(OSG_FIXED_MFIELDSYNC)
void TexturedQuadUIDrawObjectBase::executeSyncImpl(      TexturedQuadUIDrawObjectBase *pOther,
                                        const BitVector         &whichField)
{

    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (Point1FieldMask & whichField))
        _sfPoint1.syncWith(pOther->_sfPoint1);

    if(FieldBits::NoField != (Point2FieldMask & whichField))
        _sfPoint2.syncWith(pOther->_sfPoint2);

    if(FieldBits::NoField != (Point3FieldMask & whichField))
        _sfPoint3.syncWith(pOther->_sfPoint3);

    if(FieldBits::NoField != (Point4FieldMask & whichField))
        _sfPoint4.syncWith(pOther->_sfPoint4);

    if(FieldBits::NoField != (TexCoord1FieldMask & whichField))
        _sfTexCoord1.syncWith(pOther->_sfTexCoord1);

    if(FieldBits::NoField != (TexCoord2FieldMask & whichField))
        _sfTexCoord2.syncWith(pOther->_sfTexCoord2);

    if(FieldBits::NoField != (TexCoord3FieldMask & whichField))
        _sfTexCoord3.syncWith(pOther->_sfTexCoord3);

    if(FieldBits::NoField != (TexCoord4FieldMask & whichField))
        _sfTexCoord4.syncWith(pOther->_sfTexCoord4);

    if(FieldBits::NoField != (TextureFieldMask & whichField))
        _sfTexture.syncWith(pOther->_sfTexture);

    if(FieldBits::NoField != (OpacityFieldMask & whichField))
        _sfOpacity.syncWith(pOther->_sfOpacity);


}
#else
void TexturedQuadUIDrawObjectBase::executeSyncImpl(      TexturedQuadUIDrawObjectBase *pOther,
                                        const BitVector         &whichField,
                                        const SyncInfo          &sInfo      )
{

    Inherited::executeSyncImpl(pOther, whichField, sInfo);

    if(FieldBits::NoField != (Point1FieldMask & whichField))
        _sfPoint1.syncWith(pOther->_sfPoint1);

    if(FieldBits::NoField != (Point2FieldMask & whichField))
        _sfPoint2.syncWith(pOther->_sfPoint2);

    if(FieldBits::NoField != (Point3FieldMask & whichField))
        _sfPoint3.syncWith(pOther->_sfPoint3);

    if(FieldBits::NoField != (Point4FieldMask & whichField))
        _sfPoint4.syncWith(pOther->_sfPoint4);

    if(FieldBits::NoField != (TexCoord1FieldMask & whichField))
        _sfTexCoord1.syncWith(pOther->_sfTexCoord1);

    if(FieldBits::NoField != (TexCoord2FieldMask & whichField))
        _sfTexCoord2.syncWith(pOther->_sfTexCoord2);

    if(FieldBits::NoField != (TexCoord3FieldMask & whichField))
        _sfTexCoord3.syncWith(pOther->_sfTexCoord3);

    if(FieldBits::NoField != (TexCoord4FieldMask & whichField))
        _sfTexCoord4.syncWith(pOther->_sfTexCoord4);

    if(FieldBits::NoField != (TextureFieldMask & whichField))
        _sfTexture.syncWith(pOther->_sfTexture);

    if(FieldBits::NoField != (OpacityFieldMask & whichField))
        _sfOpacity.syncWith(pOther->_sfOpacity);



}

void TexturedQuadUIDrawObjectBase::execBeginEditImpl (const BitVector &whichField, 
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
DataType FieldDataTraits<TexturedQuadUIDrawObjectPtr>::_type("TexturedQuadUIDrawObjectPtr", "UIDrawObjectPtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(TexturedQuadUIDrawObjectPtr, OSG_USERINTERFACELIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(TexturedQuadUIDrawObjectPtr, OSG_USERINTERFACELIB_DLLTMPLMAPPING);


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
    static Char8 cvsid_hpp       [] = OSGTEXTUREDQUADUIDRAWOBJECTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTEXTUREDQUADUIDRAWOBJECTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTEXTUREDQUADUIDRAWOBJECTFIELDS_HEADER_CVSID;
}

OSG_END_NAMESPACE

