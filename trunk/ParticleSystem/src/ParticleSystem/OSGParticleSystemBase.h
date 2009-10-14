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
 **     class ParticleSystem
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGPARTICLESYSTEMBASE_H_
#define _OSGPARTICLESYSTEMBASE_H_
#ifdef __sgi
#pragma once
#endif


#include <OpenSG/OSGConfig.h>
#include "OSGParticleSystemDef.h"

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGRefPtr.h>
#include <OpenSG/OSGCoredNodePtr.h>

#include <OpenSG/OSGAttachmentContainer.h> // Parent

#include <OpenSG/OSGNodeFields.h> // Beacon type
#include <OpenSG/OSGPnt3fFields.h> // InternalPositions type
#include <OpenSG/OSGPnt3fFields.h> // InternalSecPositions type
#include <OpenSG/OSGVec3fFields.h> // InternalNormals type
#include <OpenSG/OSGColor4fFields.h> // InternalColors type
#include <OpenSG/OSGVec3fFields.h> // InternalSizes type
#include <OpenSG/OSGTimeFields.h> // InternalLifespans type
#include <OpenSG/OSGTimeFields.h> // InternalAges type
#include <OpenSG/OSGVec3fFields.h> // InternalVelocities type
#include <OpenSG/OSGVec3fFields.h> // InternalSecVelocities type
#include <OpenSG/OSGVec3fFields.h> // InternalAccelerations type
#include <OpenSG/Toolbox/OSGStringToUInt32MapType.h> // InternalAttributes type
#include <OpenSG/OSGUInt32Fields.h> // MaxParticles type
#include <OpenSG/OSGBoolFields.h> // Dynamic type
#include <OpenSG/OSGBoolFields.h> // UpdateSecAttribs type
#include <OpenSG/OSGTimeFields.h> // LastElapsedTime type
#include "ParticleSystem/ParticleGenerators/OSGParticleGeneratorFields.h" // Generators type
#include "ParticleSystem/ParticleAffectors/OSGParticleAffectorFields.h" // Affectors type
#include "ParticleSystem/ParticleSystemAffectors/OSGParticleSystemAffectorFields.h" // SystemAffectors type
#include <OpenSG/OSGDynamicVolumeFields.h> // Volume type
#include <OpenSG/OSGVec3fFields.h> // MaxParticleSize type

#include "OSGParticleSystemFields.h"
#include <OpenSG/Toolbox/OSGEventProducer.h>
#include <OpenSG/Toolbox/OSGEventProducerType.h>
#include <OpenSG/Toolbox/OSGMethodDescription.h>
#include <OpenSG/Toolbox/OSGEventProducerPtrType.h>

OSG_BEGIN_NAMESPACE

class ParticleSystem;
class BinaryDataHandler;

//! \brief ParticleSystem Base Class.

class OSG_PARTICLESYSTEMLIB_DLLMAPPING ParticleSystemBase : public AttachmentContainer
{
  private:

    typedef AttachmentContainer    Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    typedef ParticleSystemPtr  Ptr;

    enum
    {
        BeaconFieldId                = Inherited::NextFieldId,
        InternalPositionsFieldId     = BeaconFieldId                + 1,
        InternalSecPositionsFieldId  = InternalPositionsFieldId     + 1,
        InternalNormalsFieldId       = InternalSecPositionsFieldId  + 1,
        InternalColorsFieldId        = InternalNormalsFieldId       + 1,
        InternalSizesFieldId         = InternalColorsFieldId        + 1,
        InternalLifespansFieldId     = InternalSizesFieldId         + 1,
        InternalAgesFieldId          = InternalLifespansFieldId     + 1,
        InternalVelocitiesFieldId    = InternalAgesFieldId          + 1,
        InternalSecVelocitiesFieldId = InternalVelocitiesFieldId    + 1,
        InternalAccelerationsFieldId = InternalSecVelocitiesFieldId + 1,
        InternalAttributesFieldId    = InternalAccelerationsFieldId + 1,
        MaxParticlesFieldId          = InternalAttributesFieldId    + 1,
        DynamicFieldId               = MaxParticlesFieldId          + 1,
        UpdateSecAttribsFieldId      = DynamicFieldId               + 1,
        LastElapsedTimeFieldId       = UpdateSecAttribsFieldId      + 1,
        GeneratorsFieldId            = LastElapsedTimeFieldId       + 1,
        AffectorsFieldId             = GeneratorsFieldId            + 1,
        SystemAffectorsFieldId       = AffectorsFieldId             + 1,
        VolumeFieldId                = SystemAffectorsFieldId       + 1,
        MaxParticleSizeFieldId       = VolumeFieldId                + 1,
        EventProducerFieldId         = MaxParticleSizeFieldId       + 1,
        NextFieldId                  = EventProducerFieldId         + 1
    };

    static const OSG::BitVector BeaconFieldMask;
    static const OSG::BitVector InternalPositionsFieldMask;
    static const OSG::BitVector InternalSecPositionsFieldMask;
    static const OSG::BitVector InternalNormalsFieldMask;
    static const OSG::BitVector InternalColorsFieldMask;
    static const OSG::BitVector InternalSizesFieldMask;
    static const OSG::BitVector InternalLifespansFieldMask;
    static const OSG::BitVector InternalAgesFieldMask;
    static const OSG::BitVector InternalVelocitiesFieldMask;
    static const OSG::BitVector InternalSecVelocitiesFieldMask;
    static const OSG::BitVector InternalAccelerationsFieldMask;
    static const OSG::BitVector InternalAttributesFieldMask;
    static const OSG::BitVector MaxParticlesFieldMask;
    static const OSG::BitVector DynamicFieldMask;
    static const OSG::BitVector UpdateSecAttribsFieldMask;
    static const OSG::BitVector LastElapsedTimeFieldMask;
    static const OSG::BitVector GeneratorsFieldMask;
    static const OSG::BitVector AffectorsFieldMask;
    static const OSG::BitVector SystemAffectorsFieldMask;
    static const OSG::BitVector VolumeFieldMask;
    static const OSG::BitVector MaxParticleSizeFieldMask;
    static const OSG::BitVector EventProducerFieldMask;


    enum
    {
        SystemUpdatedMethodId     = 1,
        VolumeChangedMethodId     = SystemUpdatedMethodId     + 1,
        ParticleGeneratedMethodId = VolumeChangedMethodId     + 1,
        ParticleKilledMethodId    = ParticleGeneratedMethodId + 1,
        ParticleStolenMethodId    = ParticleKilledMethodId    + 1,
        NextMethodId              = ParticleStolenMethodId    + 1
    };



    static const OSG::BitVector MTInfluenceMask;

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static        FieldContainerType &getClassType    (void); 
    static        UInt32              getClassTypeId  (void); 
    static const  EventProducerType  &getProducerClassType  (void); 
    static        UInt32              getProducerClassTypeId(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                FieldContainer Get                            */
    /*! \{                                                                 */

    virtual       FieldContainerType &getType  (void); 
    virtual const FieldContainerType &getType  (void) const; 

    virtual       UInt32              getContainerSize(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */


           SFNodePtr           *editSFBeacon         (void);
     const SFNodePtr           *getSFBeacon         (void) const;
     const MFPnt3f             *getMFInternalPositions(void) const;

           SFUInt32            *editSFMaxParticles   (void);
     const SFUInt32            *getSFMaxParticles   (void) const;

           SFBool              *editSFDynamic        (void);
     const SFBool              *getSFDynamic        (void) const;

           SFBool              *editSFUpdateSecAttribs(void);
     const SFBool              *getSFUpdateSecAttribs(void) const;

           SFTime              *editSFLastElapsedTime(void);
     const SFTime              *getSFLastElapsedTime(void) const;

           MFParticleGeneratorPtr *editMFGenerators     (void);
     const MFParticleGeneratorPtr *getMFGenerators     (void) const;

           MFParticleAffectorPtr *editMFAffectors      (void);
     const MFParticleAffectorPtr *getMFAffectors      (void) const;

           MFParticleSystemAffectorPtr *editMFSystemAffectors(void);
     const MFParticleSystemAffectorPtr *getMFSystemAffectors(void) const;
     const SFDynamicVolume     *getSFVolume         (void) const;
     const SFVec3f             *getSFMaxParticleSize(void) const;


           NodePtr             &editBeacon         (void);
     const NodePtr             &getBeacon         (void) const;

           UInt32              &editMaxParticles   (void);
     const UInt32              &getMaxParticles   (void) const;

           bool                &editDynamic        (void);
     const bool                &getDynamic        (void) const;

           bool                &editUpdateSecAttribs(void);
     const bool                &getUpdateSecAttribs(void) const;

           Time                &editLastElapsedTime(void);
     const Time                &getLastElapsedTime(void) const;

     const DynamicVolume       &getVolume         (void) const;

     const Vec3f               &getMaxParticleSize(void) const;

     const Pnt3f               &getInternalPositions(const UInt32 index) const;











           ParticleGeneratorPtr &editGenerators     (const UInt32 index);
     const ParticleGeneratorPtr &getGenerators     (const UInt32 index) const;
#ifndef OSG_2_PREP
           MFParticleGeneratorPtr &getGenerators     (void);
     const MFParticleGeneratorPtr &getGenerators     (void) const;
#endif

           ParticleAffectorPtr &editAffectors      (const UInt32 index);
     const ParticleAffectorPtr &getAffectors      (const UInt32 index) const;
#ifndef OSG_2_PREP
           MFParticleAffectorPtr &getAffectors      (void);
     const MFParticleAffectorPtr &getAffectors      (void) const;
#endif

           ParticleSystemAffectorPtr &editSystemAffectors(const UInt32 index);
     const ParticleSystemAffectorPtr &getSystemAffectors(const UInt32 index) const;
#ifndef OSG_2_PREP
           MFParticleSystemAffectorPtr &getSystemAffectors(void);
     const MFParticleSystemAffectorPtr &getSystemAffectors(void) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setBeacon         ( const NodePtr &value );
     void setMaxParticles   ( const UInt32 &value );
     void setDynamic        ( const bool &value );
     void setUpdateSecAttribs( const bool &value );
     void setLastElapsedTime( const Time &value );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Method Produced Get                           */
    /*! \{                                                                 */

    virtual const EventProducerType &getProducerType(void) const; 
    EventConnection attachActivity(ActivityPtr TheActivity, UInt32 ProducedEventId);
    bool isActivityAttached(ActivityPtr TheActivity, UInt32 ProducedEventId) const;
    UInt32 getNumActivitiesAttached(UInt32 ProducedEventId) const;
    ActivityPtr getAttachedActivity(UInt32 ProducedEventId, UInt32 ActivityIndex) const;
    void detachActivity(ActivityPtr TheActivity, UInt32 ProducedEventId);
    UInt32 getNumProducedEvents(void) const;
    const MethodDescription *getProducedEventDescription(const Char8 *ProducedEventName) const;
    const MethodDescription *getProducedEventDescription(UInt32 ProducedEventId) const;
    UInt32 getProducedEventId(const Char8 *ProducedEventName) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    virtual UInt32 getBinSize (const BitVector         &whichField);
    virtual void   copyToBin  (      BinaryDataHandler &pMem,
                               const BitVector         &whichField);
    virtual void   copyFromBin(      BinaryDataHandler &pMem,
                               const BitVector         &whichField);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static  ParticleSystemPtr      create          (void); 
    static  ParticleSystemPtr      createEmpty     (void); 

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                       Copy                                   */
    /*! \{                                                                 */

    virtual FieldContainerPtr     shallowCopy     (void) const; 

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    EventProducer _Producer;

    SFEventProducerPtr *editSFEventProducer(void);
    EventProducerPtr &editEventProducer(void);

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFNodePtr           _sfBeacon;
    MFPnt3f             _mfInternalPositions;
    MFPnt3f             _mfInternalSecPositions;
    MFVec3f             _mfInternalNormals;
    MFColor4f           _mfInternalColors;
    MFVec3f             _mfInternalSizes;
    MFTime              _mfInternalLifespans;
    MFTime              _mfInternalAges;
    MFVec3f             _mfInternalVelocities;
    MFVec3f             _mfInternalSecVelocities;
    MFVec3f             _mfInternalAccelerations;
    MFStringToUInt32Map   _mfInternalAttributes;
    SFUInt32            _sfMaxParticles;
    SFBool              _sfDynamic;
    SFBool              _sfUpdateSecAttribs;
    SFTime              _sfLastElapsedTime;
    MFParticleGeneratorPtr   _mfGenerators;
    MFParticleAffectorPtr   _mfAffectors;
    MFParticleSystemAffectorPtr   _mfSystemAffectors;
    SFDynamicVolume     _sfVolume;
    SFVec3f             _sfMaxParticleSize;

    /*! \}                                                                 */
    SFEventProducerPtr _sfEventProducer;
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ParticleSystemBase(void);
    ParticleSystemBase(const ParticleSystemBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleSystemBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

           MFPnt3f             *editMFInternalPositions(void);
           MFPnt3f             *editMFInternalSecPositions(void);
     const MFPnt3f             *getMFInternalSecPositions(void) const;
           MFVec3f             *editMFInternalNormals(void);
     const MFVec3f             *getMFInternalNormals(void) const;
           MFColor4f           *editMFInternalColors (void);
     const MFColor4f           *getMFInternalColors (void) const;
           MFVec3f             *editMFInternalSizes  (void);
     const MFVec3f             *getMFInternalSizes  (void) const;
           MFTime              *editMFInternalLifespans(void);
     const MFTime              *getMFInternalLifespans(void) const;
           MFTime              *editMFInternalAges   (void);
     const MFTime              *getMFInternalAges   (void) const;
           MFVec3f             *editMFInternalVelocities(void);
     const MFVec3f             *getMFInternalVelocities(void) const;
           MFVec3f             *editMFInternalSecVelocities(void);
     const MFVec3f             *getMFInternalSecVelocities(void) const;
           MFVec3f             *editMFInternalAccelerations(void);
     const MFVec3f             *getMFInternalAccelerations(void) const;
           MFStringToUInt32Map *editMFInternalAttributes(void);
     const MFStringToUInt32Map *getMFInternalAttributes(void) const;
           SFDynamicVolume     *editSFVolume         (void);
           SFVec3f             *editSFMaxParticleSize(void);

           DynamicVolume       &editVolume         (void);
           Vec3f               &editMaxParticleSize(void);
           Pnt3f               &editInternalPositions(UInt32 index);
#ifndef OSG_2_PREP
           MFPnt3f             &getInternalPositions(void);
     const MFPnt3f             &getInternalPositions(void) const;
#endif
           Pnt3f               &editInternalSecPositions(UInt32 index);
#ifndef OSG_2_PREP
           MFPnt3f             &getInternalSecPositions(void);
     const MFPnt3f             &getInternalSecPositions(void) const;
#endif
     const Pnt3f               &getInternalSecPositions(UInt32 index) const;
           Vec3f               &editInternalNormals(UInt32 index);
#ifndef OSG_2_PREP
           MFVec3f             &getInternalNormals(void);
     const MFVec3f             &getInternalNormals(void) const;
#endif
     const Vec3f               &getInternalNormals(UInt32 index) const;
           Color4f             &editInternalColors (UInt32 index);
#ifndef OSG_2_PREP
           MFColor4f           &getInternalColors (void);
     const MFColor4f           &getInternalColors (void) const;
#endif
     const Color4f             &getInternalColors (UInt32 index) const;
           Vec3f               &editInternalSizes  (UInt32 index);
#ifndef OSG_2_PREP
           MFVec3f             &getInternalSizes  (void);
     const MFVec3f             &getInternalSizes  (void) const;
#endif
     const Vec3f               &getInternalSizes  (UInt32 index) const;
           Time                &editInternalLifespans(UInt32 index);
#ifndef OSG_2_PREP
           MFTime              &getInternalLifespans(void);
     const MFTime              &getInternalLifespans(void) const;
#endif
     const Time                &getInternalLifespans(UInt32 index) const;
           Time                &editInternalAges   (UInt32 index);
#ifndef OSG_2_PREP
           MFTime              &getInternalAges   (void);
     const MFTime              &getInternalAges   (void) const;
#endif
     const Time                &getInternalAges   (UInt32 index) const;
           Vec3f               &editInternalVelocities(UInt32 index);
#ifndef OSG_2_PREP
           MFVec3f             &getInternalVelocities(void);
     const MFVec3f             &getInternalVelocities(void) const;
#endif
     const Vec3f               &getInternalVelocities(UInt32 index) const;
           Vec3f               &editInternalSecVelocities(UInt32 index);
#ifndef OSG_2_PREP
           MFVec3f             &getInternalSecVelocities(void);
     const MFVec3f             &getInternalSecVelocities(void) const;
#endif
     const Vec3f               &getInternalSecVelocities(UInt32 index) const;
           Vec3f               &editInternalAccelerations(UInt32 index);
#ifndef OSG_2_PREP
           MFVec3f             &getInternalAccelerations(void);
     const MFVec3f             &getInternalAccelerations(void) const;
#endif
     const Vec3f               &getInternalAccelerations(UInt32 index) const;
           StringToUInt32Map   &editInternalAttributes(UInt32 index);
#ifndef OSG_2_PREP
           MFStringToUInt32Map &getInternalAttributes(void);
     const MFStringToUInt32Map &getInternalAttributes(void) const;
#endif
     const StringToUInt32Map   &getInternalAttributes(UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setVolume         (const DynamicVolume &value);
     void setMaxParticleSize(const Vec3f &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#if !defined(OSG_FIXED_MFIELDSYNC)
    void executeSyncImpl(      ParticleSystemBase *pOther,
                         const BitVector         &whichField);

    virtual void   executeSync(      FieldContainer    &other,
                               const BitVector         &whichField);
#else
    void executeSyncImpl(      ParticleSystemBase *pOther,
                         const BitVector         &whichField,
                         const SyncInfo          &sInfo     );

    virtual void   executeSync(      FieldContainer    &other,
                               const BitVector         &whichField,
                               const SyncInfo          &sInfo);

    virtual void execBeginEdit     (const BitVector &whichField,
                                          UInt32     uiAspect,
                                          UInt32     uiContainerSize);

            void execBeginEditImpl (const BitVector &whichField,
                                          UInt32     uiAspect,
                                          UInt32     uiContainerSize);

    virtual void onDestroyAspect(UInt32 uiId, UInt32 uiAspect);
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;

    static MethodDescription   *_methodDesc[];
    static EventProducerType _producerType;

    static FieldDescription   *_desc[];
    static FieldContainerType  _type;


    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ParticleSystemBase &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


typedef ParticleSystemBase *ParticleSystemBaseP;

typedef osgIF<ParticleSystemBase::isNodeCore,
              CoredNodePtr<ParticleSystem>,
              FieldContainer::attempt_to_create_CoredNodePtr_on_non_NodeCore_FC
              >::_IRet ParticleSystemNodePtr;

typedef RefPtr<ParticleSystemPtr> ParticleSystemRefPtr;

OSG_END_NAMESPACE

#endif /* _OSGPARTICLESYSTEMBASE_H_ */
