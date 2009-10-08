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
 **     class Sound!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILESOUNDINST

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "OSGSoundBase.h"
#include "OSGSound.h"


OSG_BEGIN_NAMESPACE

const OSG::BitVector  SoundBase::PositionFieldMask = 
    (TypeTraits<BitVector>::One << SoundBase::PositionFieldId);

const OSG::BitVector  SoundBase::VelocityFieldMask = 
    (TypeTraits<BitVector>::One << SoundBase::VelocityFieldId);

const OSG::BitVector  SoundBase::VolumeFieldMask = 
    (TypeTraits<BitVector>::One << SoundBase::VolumeFieldId);

const OSG::BitVector  SoundBase::PanFieldMask = 
    (TypeTraits<BitVector>::One << SoundBase::PanFieldId);

const OSG::BitVector  SoundBase::FrequencyFieldMask = 
    (TypeTraits<BitVector>::One << SoundBase::FrequencyFieldId);

const OSG::BitVector  SoundBase::LoopingFieldMask = 
    (TypeTraits<BitVector>::One << SoundBase::LoopingFieldId);

const OSG::BitVector  SoundBase::StreamingFieldMask = 
    (TypeTraits<BitVector>::One << SoundBase::StreamingFieldId);

const OSG::BitVector  SoundBase::FileFieldMask = 
    (TypeTraits<BitVector>::One << SoundBase::FileFieldId);

const OSG::BitVector  SoundBase::Enable3DFieldMask = 
    (TypeTraits<BitVector>::One << SoundBase::Enable3DFieldId);

const OSG::BitVector  SoundBase::EventProducerFieldMask =
    (TypeTraits<BitVector>::One << SoundBase::EventProducerFieldId);

const OSG::BitVector SoundBase::MTInfluenceMask = 
    (Inherited::MTInfluenceMask) | 
    (static_cast<BitVector>(0x0) << Inherited::NextFieldId); 


// Field descriptions

/*! \var Pnt3f           SoundBase::_sfPosition
    Initial position of this sound.
*/
/*! \var Vec3f           SoundBase::_sfVelocity
    Initial velocity of this sound.
*/
/*! \var Real32          SoundBase::_sfVolume
    Values from 0.0 to 1.0.  0.0 = Silent, 1.0 = Full Volume.
*/
/*! \var Real32          SoundBase::_sfPan
    Values from -1.0 to 1.0. -1.0 = Full Left, 0.0 = Full Center, 1.0 = Full Right.
*/
/*! \var Real32          SoundBase::_sfFrequency
    Default playback frequency.
*/
/*! \var Int32           SoundBase::_sfLooping
    Number of times to loop this sound. 1 = play the sound once, Values less than 0 = Inifinite loop. Values 2 greater than plays the sound that many times.
*/
/*! \var bool            SoundBase::_sfStreaming
    Whether or not this sound should be streamed.
*/
/*! \var Path            SoundBase::_sfFile
    The Path to the sound file to load this sound from.
*/
/*! \var bool            SoundBase::_sfEnable3D
    
*/

//! Sound description

FieldDescription *SoundBase::_desc[] = 
{
    new FieldDescription(SFPnt3f::getClassType(), 
                     "Position", 
                     PositionFieldId, PositionFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&SoundBase::editSFPosition)),
    new FieldDescription(SFVec3f::getClassType(), 
                     "Velocity", 
                     VelocityFieldId, VelocityFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&SoundBase::editSFVelocity)),
    new FieldDescription(SFReal32::getClassType(), 
                     "Volume", 
                     VolumeFieldId, VolumeFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&SoundBase::editSFVolume)),
    new FieldDescription(SFReal32::getClassType(), 
                     "Pan", 
                     PanFieldId, PanFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&SoundBase::editSFPan)),
    new FieldDescription(SFReal32::getClassType(), 
                     "Frequency", 
                     FrequencyFieldId, FrequencyFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&SoundBase::editSFFrequency)),
    new FieldDescription(SFInt32::getClassType(), 
                     "Looping", 
                     LoopingFieldId, LoopingFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&SoundBase::editSFLooping)),
    new FieldDescription(SFBool::getClassType(), 
                     "Streaming", 
                     StreamingFieldId, StreamingFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&SoundBase::editSFStreaming)),
    new FieldDescription(SFPath::getClassType(), 
                     "File", 
                     FileFieldId, FileFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&SoundBase::editSFFile)),
    new FieldDescription(SFBool::getClassType(), 
                     "Enable3D", 
                     Enable3DFieldId, Enable3DFieldMask,
                     false,
                     reinterpret_cast<FieldAccessMethod>(&SoundBase::editSFEnable3D))
    , 
    new FieldDescription(SFEventProducerPtr::getClassType(), 
                     "EventProducer", 
                     EventProducerFieldId,EventProducerFieldMask,
                     true,
                     FieldAccessMethod(NULL))
};


FieldContainerType SoundBase::_type(
    "Sound",
    "AttachmentContainer",
    NULL,
    NULL, 
    Sound::initMethod,
    _desc,
    sizeof(_desc));

//! Sound Produced Methods

MethodDescription *SoundBase::_methodDesc[] =
{
    new MethodDescription("SoundPlayed", 
                     SoundPlayedMethodId, 
                     SFEventPtr::getClassType(),
                     FunctorAccessMethod()),
    new MethodDescription("SoundStopped", 
                     SoundStoppedMethodId, 
                     SFEventPtr::getClassType(),
                     FunctorAccessMethod()),
    new MethodDescription("SoundPaused", 
                     SoundPausedMethodId, 
                     SFEventPtr::getClassType(),
                     FunctorAccessMethod()),
    new MethodDescription("SoundUnpaused", 
                     SoundUnpausedMethodId, 
                     SFEventPtr::getClassType(),
                     FunctorAccessMethod()),
    new MethodDescription("SoundLooped", 
                     SoundLoopedMethodId, 
                     SFEventPtr::getClassType(),
                     FunctorAccessMethod()),
    new MethodDescription("SoundEnded", 
                     SoundEndedMethodId, 
                     SFEventPtr::getClassType(),
                     FunctorAccessMethod())
};

EventProducerType SoundBase::_producerType(
    "SoundProducerType",
    "EventProducerType",
    NULL,
    InitEventProducerFunctor(),
    _methodDesc,
    sizeof(_methodDesc));
//OSG_FIELD_CONTAINER_DEF(SoundBase, SoundPtr)

/*------------------------------ get -----------------------------------*/

FieldContainerType &SoundBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &SoundBase::getType(void) const 
{
    return _type;
} 

const EventProducerType &SoundBase::getProducerType(void) const
{
    return _producerType;
}


UInt32 SoundBase::getContainerSize(void) const 
{ 
    return sizeof(Sound); 
}


#if !defined(OSG_FIXED_MFIELDSYNC)
void SoundBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField)
{
    this->executeSyncImpl(static_cast<SoundBase *>(&other),
                          whichField);
}
#else
void SoundBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField,                                    const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((SoundBase *) &other, whichField, sInfo);
}
void SoundBase::execBeginEdit(const BitVector &whichField, 
                                            UInt32     uiAspect,
                                            UInt32     uiContainerSize) 
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}

void SoundBase::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    Inherited::onDestroyAspect(uiId, uiAspect);

}
#endif

/*------------------------- constructors ----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

SoundBase::SoundBase(void) :
    _Producer(&getProducerType()),
    _sfPosition               (Pnt3f(0.0,0.0,0.0)), 
    _sfVelocity               (Vec3f(0.0,0.0,0.0)), 
    _sfVolume                 (Real32(1.0)), 
    _sfPan                    (Real32(0.0)), 
    _sfFrequency              (Real32(44100.0)), 
    _sfLooping                (Int32(1)), 
    _sfStreaming              (bool(false)), 
    _sfFile                   (), 
    _sfEnable3D               (bool(false)), 
    _sfEventProducer(&_Producer),
    Inherited() 
{
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

SoundBase::SoundBase(const SoundBase &source) :
    _Producer(&getProducerType()),
    _sfPosition               (source._sfPosition               ), 
    _sfVelocity               (source._sfVelocity               ), 
    _sfVolume                 (source._sfVolume                 ), 
    _sfPan                    (source._sfPan                    ), 
    _sfFrequency              (source._sfFrequency              ), 
    _sfLooping                (source._sfLooping                ), 
    _sfStreaming              (source._sfStreaming              ), 
    _sfFile                   (source._sfFile                   ), 
    _sfEnable3D               (source._sfEnable3D               ), 
    _sfEventProducer(&_Producer),
    Inherited                 (source)
{
}

/*-------------------------- destructors ----------------------------------*/

SoundBase::~SoundBase(void)
{
}

/*------------------------------ access -----------------------------------*/

UInt32 SoundBase::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (PositionFieldMask & whichField))
    {
        returnValue += _sfPosition.getBinSize();
    }

    if(FieldBits::NoField != (VelocityFieldMask & whichField))
    {
        returnValue += _sfVelocity.getBinSize();
    }

    if(FieldBits::NoField != (VolumeFieldMask & whichField))
    {
        returnValue += _sfVolume.getBinSize();
    }

    if(FieldBits::NoField != (PanFieldMask & whichField))
    {
        returnValue += _sfPan.getBinSize();
    }

    if(FieldBits::NoField != (FrequencyFieldMask & whichField))
    {
        returnValue += _sfFrequency.getBinSize();
    }

    if(FieldBits::NoField != (LoopingFieldMask & whichField))
    {
        returnValue += _sfLooping.getBinSize();
    }

    if(FieldBits::NoField != (StreamingFieldMask & whichField))
    {
        returnValue += _sfStreaming.getBinSize();
    }

    if(FieldBits::NoField != (FileFieldMask & whichField))
    {
        returnValue += _sfFile.getBinSize();
    }

    if(FieldBits::NoField != (Enable3DFieldMask & whichField))
    {
        returnValue += _sfEnable3D.getBinSize();
    }

    if(FieldBits::NoField != (EventProducerFieldMask & whichField))
    {
        returnValue += _sfEventProducer.getBinSize();
    }


    return returnValue;
}

void SoundBase::copyToBin(      BinaryDataHandler &pMem,
                                  const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (PositionFieldMask & whichField))
    {
        _sfPosition.copyToBin(pMem);
    }

    if(FieldBits::NoField != (VelocityFieldMask & whichField))
    {
        _sfVelocity.copyToBin(pMem);
    }

    if(FieldBits::NoField != (VolumeFieldMask & whichField))
    {
        _sfVolume.copyToBin(pMem);
    }

    if(FieldBits::NoField != (PanFieldMask & whichField))
    {
        _sfPan.copyToBin(pMem);
    }

    if(FieldBits::NoField != (FrequencyFieldMask & whichField))
    {
        _sfFrequency.copyToBin(pMem);
    }

    if(FieldBits::NoField != (LoopingFieldMask & whichField))
    {
        _sfLooping.copyToBin(pMem);
    }

    if(FieldBits::NoField != (StreamingFieldMask & whichField))
    {
        _sfStreaming.copyToBin(pMem);
    }

    if(FieldBits::NoField != (FileFieldMask & whichField))
    {
        _sfFile.copyToBin(pMem);
    }

    if(FieldBits::NoField != (Enable3DFieldMask & whichField))
    {
        _sfEnable3D.copyToBin(pMem);
    }

    if(FieldBits::NoField != (EventProducerFieldMask & whichField))
    {
        _sfEventProducer.copyToBin(pMem);
    }


}

void SoundBase::copyFromBin(      BinaryDataHandler &pMem,
                                    const BitVector    &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (PositionFieldMask & whichField))
    {
        _sfPosition.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (VelocityFieldMask & whichField))
    {
        _sfVelocity.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (VolumeFieldMask & whichField))
    {
        _sfVolume.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (PanFieldMask & whichField))
    {
        _sfPan.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (FrequencyFieldMask & whichField))
    {
        _sfFrequency.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (LoopingFieldMask & whichField))
    {
        _sfLooping.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (StreamingFieldMask & whichField))
    {
        _sfStreaming.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (FileFieldMask & whichField))
    {
        _sfFile.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (Enable3DFieldMask & whichField))
    {
        _sfEnable3D.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (EventProducerFieldMask & whichField))
    {
        _sfEventProducer.copyFromBin(pMem);
    }


}

#if !defined(OSG_FIXED_MFIELDSYNC)
void SoundBase::executeSyncImpl(      SoundBase *pOther,
                                        const BitVector         &whichField)
{

    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (PositionFieldMask & whichField))
        _sfPosition.syncWith(pOther->_sfPosition);

    if(FieldBits::NoField != (VelocityFieldMask & whichField))
        _sfVelocity.syncWith(pOther->_sfVelocity);

    if(FieldBits::NoField != (VolumeFieldMask & whichField))
        _sfVolume.syncWith(pOther->_sfVolume);

    if(FieldBits::NoField != (PanFieldMask & whichField))
        _sfPan.syncWith(pOther->_sfPan);

    if(FieldBits::NoField != (FrequencyFieldMask & whichField))
        _sfFrequency.syncWith(pOther->_sfFrequency);

    if(FieldBits::NoField != (LoopingFieldMask & whichField))
        _sfLooping.syncWith(pOther->_sfLooping);

    if(FieldBits::NoField != (StreamingFieldMask & whichField))
        _sfStreaming.syncWith(pOther->_sfStreaming);

    if(FieldBits::NoField != (FileFieldMask & whichField))
        _sfFile.syncWith(pOther->_sfFile);

    if(FieldBits::NoField != (Enable3DFieldMask & whichField))
        _sfEnable3D.syncWith(pOther->_sfEnable3D);

    if(FieldBits::NoField != (EventProducerFieldMask & whichField))
        _sfEventProducer.syncWith(pOther->_sfEventProducer);


}
#else
void SoundBase::executeSyncImpl(      SoundBase *pOther,
                                        const BitVector         &whichField,
                                        const SyncInfo          &sInfo      )
{

    Inherited::executeSyncImpl(pOther, whichField, sInfo);

    if(FieldBits::NoField != (PositionFieldMask & whichField))
        _sfPosition.syncWith(pOther->_sfPosition);

    if(FieldBits::NoField != (VelocityFieldMask & whichField))
        _sfVelocity.syncWith(pOther->_sfVelocity);

    if(FieldBits::NoField != (VolumeFieldMask & whichField))
        _sfVolume.syncWith(pOther->_sfVolume);

    if(FieldBits::NoField != (PanFieldMask & whichField))
        _sfPan.syncWith(pOther->_sfPan);

    if(FieldBits::NoField != (FrequencyFieldMask & whichField))
        _sfFrequency.syncWith(pOther->_sfFrequency);

    if(FieldBits::NoField != (LoopingFieldMask & whichField))
        _sfLooping.syncWith(pOther->_sfLooping);

    if(FieldBits::NoField != (StreamingFieldMask & whichField))
        _sfStreaming.syncWith(pOther->_sfStreaming);

    if(FieldBits::NoField != (FileFieldMask & whichField))
        _sfFile.syncWith(pOther->_sfFile);

    if(FieldBits::NoField != (Enable3DFieldMask & whichField))
        _sfEnable3D.syncWith(pOther->_sfEnable3D);



}

void SoundBase::execBeginEditImpl (const BitVector &whichField, 
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
DataType FieldDataTraits<SoundPtr>::_type("SoundPtr", "AttachmentContainerPtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(SoundPtr, OSG_SOUNDLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(SoundPtr, OSG_SOUNDLIB_DLLTMPLMAPPING);


OSG_END_NAMESPACE

