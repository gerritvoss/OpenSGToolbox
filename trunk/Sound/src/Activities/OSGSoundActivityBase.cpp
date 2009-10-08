/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Sound                               *
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
 **     class SoundActivity!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILESOUNDACTIVITYINST

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "OSGSoundActivityBase.h"
#include "OSGSoundActivity.h"


OSG_BEGIN_NAMESPACE

const OSG::BitVector  SoundActivityBase::SoundFieldMask = 
    (TypeTraits<BitVector>::One << SoundActivityBase::SoundFieldId);

const OSG::BitVector  SoundActivityBase::ChannelFieldMask = 
    (TypeTraits<BitVector>::One << SoundActivityBase::ChannelFieldId);

const OSG::BitVector  SoundActivityBase::ActivityTypeFieldMask = 
    (TypeTraits<BitVector>::One << SoundActivityBase::ActivityTypeFieldId);

const OSG::BitVector SoundActivityBase::MTInfluenceMask = 
    (Inherited::MTInfluenceMask) | 
    (static_cast<BitVector>(0x0) << Inherited::NextFieldId); 


// Field descriptions

/*! \var SoundPtr        SoundActivityBase::_sfSound
    
*/
/*! \var UInt32          SoundActivityBase::_sfChannel
    
*/
/*! \var UInt8           SoundActivityBase::_sfActivityType
    
*/

//! SoundActivity description

FieldDescription *SoundActivityBase::_desc[] = 
{
    new FieldDescription(SFSoundPtr::getClassType(), 
                     "Sound", 
                     SoundFieldId, SoundFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&SoundActivityBase::editSFSound)),
    new FieldDescription(SFUInt32::getClassType(), 
                     "Channel", 
                     ChannelFieldId, ChannelFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&SoundActivityBase::editSFChannel)),
    new FieldDescription(SFUInt8::getClassType(), 
                     "ActivityType", 
                     ActivityTypeFieldId, ActivityTypeFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&SoundActivityBase::editSFActivityType))
};


FieldContainerType SoundActivityBase::_type(
    "SoundActivity",
    "Activity",
    NULL,
    reinterpret_cast<PrototypeCreateF>(&SoundActivityBase::createEmpty),
    SoundActivity::initMethod,
    _desc,
    sizeof(_desc));

//OSG_FIELD_CONTAINER_DEF(SoundActivityBase, SoundActivityPtr)

/*------------------------------ get -----------------------------------*/

FieldContainerType &SoundActivityBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &SoundActivityBase::getType(void) const 
{
    return _type;
} 


FieldContainerPtr SoundActivityBase::shallowCopy(void) const 
{ 
    SoundActivityPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const SoundActivity *>(this)); 

    return returnValue; 
}

UInt32 SoundActivityBase::getContainerSize(void) const 
{ 
    return sizeof(SoundActivity); 
}


#if !defined(OSG_FIXED_MFIELDSYNC)
void SoundActivityBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField)
{
    this->executeSyncImpl(static_cast<SoundActivityBase *>(&other),
                          whichField);
}
#else
void SoundActivityBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField,                                    const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((SoundActivityBase *) &other, whichField, sInfo);
}
void SoundActivityBase::execBeginEdit(const BitVector &whichField, 
                                            UInt32     uiAspect,
                                            UInt32     uiContainerSize) 
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}

void SoundActivityBase::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    Inherited::onDestroyAspect(uiId, uiAspect);

}
#endif

/*------------------------- constructors ----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

SoundActivityBase::SoundActivityBase(void) :
    _sfSound                  (SoundPtr(NullFC)), 
    _sfChannel                (UInt32(0)), 
    _sfActivityType           (UInt8(SoundActivity::SOUND_PLAY)), 
    Inherited() 
{
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

SoundActivityBase::SoundActivityBase(const SoundActivityBase &source) :
    _sfSound                  (source._sfSound                  ), 
    _sfChannel                (source._sfChannel                ), 
    _sfActivityType           (source._sfActivityType           ), 
    Inherited                 (source)
{
}

/*-------------------------- destructors ----------------------------------*/

SoundActivityBase::~SoundActivityBase(void)
{
}

/*------------------------------ access -----------------------------------*/

UInt32 SoundActivityBase::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (SoundFieldMask & whichField))
    {
        returnValue += _sfSound.getBinSize();
    }

    if(FieldBits::NoField != (ChannelFieldMask & whichField))
    {
        returnValue += _sfChannel.getBinSize();
    }

    if(FieldBits::NoField != (ActivityTypeFieldMask & whichField))
    {
        returnValue += _sfActivityType.getBinSize();
    }


    return returnValue;
}

void SoundActivityBase::copyToBin(      BinaryDataHandler &pMem,
                                  const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (SoundFieldMask & whichField))
    {
        _sfSound.copyToBin(pMem);
    }

    if(FieldBits::NoField != (ChannelFieldMask & whichField))
    {
        _sfChannel.copyToBin(pMem);
    }

    if(FieldBits::NoField != (ActivityTypeFieldMask & whichField))
    {
        _sfActivityType.copyToBin(pMem);
    }


}

void SoundActivityBase::copyFromBin(      BinaryDataHandler &pMem,
                                    const BitVector    &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (SoundFieldMask & whichField))
    {
        _sfSound.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (ChannelFieldMask & whichField))
    {
        _sfChannel.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (ActivityTypeFieldMask & whichField))
    {
        _sfActivityType.copyFromBin(pMem);
    }


}

#if !defined(OSG_FIXED_MFIELDSYNC)
void SoundActivityBase::executeSyncImpl(      SoundActivityBase *pOther,
                                        const BitVector         &whichField)
{

    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (SoundFieldMask & whichField))
        _sfSound.syncWith(pOther->_sfSound);

    if(FieldBits::NoField != (ChannelFieldMask & whichField))
        _sfChannel.syncWith(pOther->_sfChannel);

    if(FieldBits::NoField != (ActivityTypeFieldMask & whichField))
        _sfActivityType.syncWith(pOther->_sfActivityType);


}
#else
void SoundActivityBase::executeSyncImpl(      SoundActivityBase *pOther,
                                        const BitVector         &whichField,
                                        const SyncInfo          &sInfo      )
{

    Inherited::executeSyncImpl(pOther, whichField, sInfo);

    if(FieldBits::NoField != (SoundFieldMask & whichField))
        _sfSound.syncWith(pOther->_sfSound);

    if(FieldBits::NoField != (ChannelFieldMask & whichField))
        _sfChannel.syncWith(pOther->_sfChannel);

    if(FieldBits::NoField != (ActivityTypeFieldMask & whichField))
        _sfActivityType.syncWith(pOther->_sfActivityType);



}

void SoundActivityBase::execBeginEditImpl (const BitVector &whichField, 
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
DataType FieldDataTraits<SoundActivityPtr>::_type("SoundActivityPtr", "ActivityPtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(SoundActivityPtr, OSG_SOUNDLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(SoundActivityPtr, OSG_SOUNDLIB_DLLTMPLMAPPING);


OSG_END_NAMESPACE

