/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
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
 **     class DistanceParticleAffector!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILEDISTANCEPARTICLEAFFECTORINST

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "OSGDistanceParticleAffectorBase.h"
#include "OSGDistanceParticleAffector.h"


OSG_BEGIN_NAMESPACE

const OSG::BitVector  DistanceParticleAffectorBase::DistanceFromSourceFieldMask = 
    (TypeTraits<BitVector>::One << DistanceParticleAffectorBase::DistanceFromSourceFieldId);

const OSG::BitVector  DistanceParticleAffectorBase::DistanceFromNodeFieldMask = 
    (TypeTraits<BitVector>::One << DistanceParticleAffectorBase::DistanceFromNodeFieldId);

const OSG::BitVector  DistanceParticleAffectorBase::ParticleSystemNodeFieldMask = 
    (TypeTraits<BitVector>::One << DistanceParticleAffectorBase::ParticleSystemNodeFieldId);

const OSG::BitVector  DistanceParticleAffectorBase::DistanceFromCameraFieldMask = 
    (TypeTraits<BitVector>::One << DistanceParticleAffectorBase::DistanceFromCameraFieldId);

const OSG::BitVector DistanceParticleAffectorBase::MTInfluenceMask = 
    (Inherited::MTInfluenceMask) | 
    (static_cast<BitVector>(0x0) << Inherited::NextFieldId); 


// Field descriptions

/*! \var UInt32          DistanceParticleAffectorBase::_sfDistanceFromSource
    
*/
/*! \var NodePtr         DistanceParticleAffectorBase::_sfDistanceFromNode
    
*/
/*! \var NodePtr         DistanceParticleAffectorBase::_sfParticleSystemNode
    
*/
/*! \var CameraPtr       DistanceParticleAffectorBase::_sfDistanceFromCamera
    
*/

//! DistanceParticleAffector description

FieldDescription *DistanceParticleAffectorBase::_desc[] = 
{
    new FieldDescription(SFUInt32::getClassType(), 
                     "DistanceFromSource", 
                     DistanceFromSourceFieldId, DistanceFromSourceFieldMask,
                     false,
                     (FieldAccessMethod) &DistanceParticleAffectorBase::getSFDistanceFromSource),
    new FieldDescription(SFNodePtr::getClassType(), 
                     "DistanceFromNode", 
                     DistanceFromNodeFieldId, DistanceFromNodeFieldMask,
                     false,
                     (FieldAccessMethod) &DistanceParticleAffectorBase::getSFDistanceFromNode),
    new FieldDescription(SFNodePtr::getClassType(), 
                     "ParticleSystemNode", 
                     ParticleSystemNodeFieldId, ParticleSystemNodeFieldMask,
                     false,
                     (FieldAccessMethod) &DistanceParticleAffectorBase::getSFParticleSystemNode),
    new FieldDescription(SFCameraPtr::getClassType(), 
                     "DistanceFromCamera", 
                     DistanceFromCameraFieldId, DistanceFromCameraFieldMask,
                     false,
                     (FieldAccessMethod) &DistanceParticleAffectorBase::getSFDistanceFromCamera)
};


FieldContainerType DistanceParticleAffectorBase::_type(
    "DistanceParticleAffector",
    "ParticleAffector",
    NULL,
    NULL, 
    DistanceParticleAffector::initMethod,
    _desc,
    sizeof(_desc));

//OSG_FIELD_CONTAINER_DEF(DistanceParticleAffectorBase, DistanceParticleAffectorPtr)

/*------------------------------ get -----------------------------------*/

FieldContainerType &DistanceParticleAffectorBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &DistanceParticleAffectorBase::getType(void) const 
{
    return _type;
} 


UInt32 DistanceParticleAffectorBase::getContainerSize(void) const 
{ 
    return sizeof(DistanceParticleAffector); 
}


#if !defined(OSG_FIXED_MFIELDSYNC)
void DistanceParticleAffectorBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField)
{
    this->executeSyncImpl((DistanceParticleAffectorBase *) &other, whichField);
}
#else
void DistanceParticleAffectorBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField,                                    const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((DistanceParticleAffectorBase *) &other, whichField, sInfo);
}
void DistanceParticleAffectorBase::execBeginEdit(const BitVector &whichField, 
                                            UInt32     uiAspect,
                                            UInt32     uiContainerSize) 
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}

void DistanceParticleAffectorBase::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    Inherited::onDestroyAspect(uiId, uiAspect);

}
#endif

/*------------------------- constructors ----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

DistanceParticleAffectorBase::DistanceParticleAffectorBase(void) :
    _sfDistanceFromSource     (UInt32(DistanceParticleAffector::DISTANCE_FROM_CAMERA)), 
    _sfDistanceFromNode       (NodePtr(NullFC)), 
    _sfParticleSystemNode     (NodePtr(NullFC)), 
    _sfDistanceFromCamera     (CameraPtr(NullFC)), 
    Inherited() 
{
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

DistanceParticleAffectorBase::DistanceParticleAffectorBase(const DistanceParticleAffectorBase &source) :
    _sfDistanceFromSource     (source._sfDistanceFromSource     ), 
    _sfDistanceFromNode       (source._sfDistanceFromNode       ), 
    _sfParticleSystemNode     (source._sfParticleSystemNode     ), 
    _sfDistanceFromCamera     (source._sfDistanceFromCamera     ), 
    Inherited                 (source)
{
}

/*-------------------------- destructors ----------------------------------*/

DistanceParticleAffectorBase::~DistanceParticleAffectorBase(void)
{
}

/*------------------------------ access -----------------------------------*/

UInt32 DistanceParticleAffectorBase::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (DistanceFromSourceFieldMask & whichField))
    {
        returnValue += _sfDistanceFromSource.getBinSize();
    }

    if(FieldBits::NoField != (DistanceFromNodeFieldMask & whichField))
    {
        returnValue += _sfDistanceFromNode.getBinSize();
    }

    if(FieldBits::NoField != (ParticleSystemNodeFieldMask & whichField))
    {
        returnValue += _sfParticleSystemNode.getBinSize();
    }

    if(FieldBits::NoField != (DistanceFromCameraFieldMask & whichField))
    {
        returnValue += _sfDistanceFromCamera.getBinSize();
    }


    return returnValue;
}

void DistanceParticleAffectorBase::copyToBin(      BinaryDataHandler &pMem,
                                  const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (DistanceFromSourceFieldMask & whichField))
    {
        _sfDistanceFromSource.copyToBin(pMem);
    }

    if(FieldBits::NoField != (DistanceFromNodeFieldMask & whichField))
    {
        _sfDistanceFromNode.copyToBin(pMem);
    }

    if(FieldBits::NoField != (ParticleSystemNodeFieldMask & whichField))
    {
        _sfParticleSystemNode.copyToBin(pMem);
    }

    if(FieldBits::NoField != (DistanceFromCameraFieldMask & whichField))
    {
        _sfDistanceFromCamera.copyToBin(pMem);
    }


}

void DistanceParticleAffectorBase::copyFromBin(      BinaryDataHandler &pMem,
                                    const BitVector    &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (DistanceFromSourceFieldMask & whichField))
    {
        _sfDistanceFromSource.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (DistanceFromNodeFieldMask & whichField))
    {
        _sfDistanceFromNode.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (ParticleSystemNodeFieldMask & whichField))
    {
        _sfParticleSystemNode.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (DistanceFromCameraFieldMask & whichField))
    {
        _sfDistanceFromCamera.copyFromBin(pMem);
    }


}

#if !defined(OSG_FIXED_MFIELDSYNC)
void DistanceParticleAffectorBase::executeSyncImpl(      DistanceParticleAffectorBase *pOther,
                                        const BitVector         &whichField)
{

    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (DistanceFromSourceFieldMask & whichField))
        _sfDistanceFromSource.syncWith(pOther->_sfDistanceFromSource);

    if(FieldBits::NoField != (DistanceFromNodeFieldMask & whichField))
        _sfDistanceFromNode.syncWith(pOther->_sfDistanceFromNode);

    if(FieldBits::NoField != (ParticleSystemNodeFieldMask & whichField))
        _sfParticleSystemNode.syncWith(pOther->_sfParticleSystemNode);

    if(FieldBits::NoField != (DistanceFromCameraFieldMask & whichField))
        _sfDistanceFromCamera.syncWith(pOther->_sfDistanceFromCamera);


}
#else
void DistanceParticleAffectorBase::executeSyncImpl(      DistanceParticleAffectorBase *pOther,
                                        const BitVector         &whichField,
                                        const SyncInfo          &sInfo      )
{

    Inherited::executeSyncImpl(pOther, whichField, sInfo);

    if(FieldBits::NoField != (DistanceFromSourceFieldMask & whichField))
        _sfDistanceFromSource.syncWith(pOther->_sfDistanceFromSource);

    if(FieldBits::NoField != (DistanceFromNodeFieldMask & whichField))
        _sfDistanceFromNode.syncWith(pOther->_sfDistanceFromNode);

    if(FieldBits::NoField != (ParticleSystemNodeFieldMask & whichField))
        _sfParticleSystemNode.syncWith(pOther->_sfParticleSystemNode);

    if(FieldBits::NoField != (DistanceFromCameraFieldMask & whichField))
        _sfDistanceFromCamera.syncWith(pOther->_sfDistanceFromCamera);



}

void DistanceParticleAffectorBase::execBeginEditImpl (const BitVector &whichField, 
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
DataType FieldDataTraits<DistanceParticleAffectorPtr>::_type("DistanceParticleAffectorPtr", "ParticleAffectorPtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(DistanceParticleAffectorPtr, OSG_PARTICLESYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(DistanceParticleAffectorPtr, OSG_PARTICLESYSTEMLIB_DLLTMPLMAPPING);


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
    static Char8 cvsid_hpp       [] = OSGDISTANCEPARTICLEAFFECTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDISTANCEPARTICLEAFFECTORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDISTANCEPARTICLEAFFECTORFIELDS_HEADER_CVSID;
}

OSG_END_NAMESPACE

