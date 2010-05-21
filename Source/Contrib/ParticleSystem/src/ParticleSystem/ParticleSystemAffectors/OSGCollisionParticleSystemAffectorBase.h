/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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
 **     class CollisionParticleSystemAffector
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGCOLLISIONPARTICLESYSTEMAFFECTORBASE_H_
#define _OSGCOLLISIONPARTICLESYSTEMAFFECTORBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribParticleSystemDef.h"

//#include "OSGBaseTypes.h"

#include "OSGParticleSystemAffector.h" // Parent

#include "OSGSysFields.h"               // CollisionDistance type
#include "OSGParticleSystemFields.h"    // SecondaryCollisionSystems type

#include "OSGCollisionParticleSystemAffectorFields.h"

//Event Producer Headers
#include "OSGEventProducer.h"
#include "OSGEventProducerType.h"
#include "OSGMethodDescription.h"
#include "OSGEventProducerPtrType.h"

OSG_BEGIN_NAMESPACE

class CollisionParticleSystemAffector;

//! \brief CollisionParticleSystemAffector Base Class.

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING CollisionParticleSystemAffectorBase : public ParticleSystemAffector
{
  public:

    typedef ParticleSystemAffector Inherited;
    typedef ParticleSystemAffector ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(CollisionParticleSystemAffector);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        CollisionDistanceFieldId = Inherited::NextFieldId,
        SecondaryCollisionSystemsFieldId = CollisionDistanceFieldId + 1,
        EventProducerFieldId = SecondaryCollisionSystemsFieldId + 1,
        NextFieldId = EventProducerFieldId + 1
    };

    static const OSG::BitVector CollisionDistanceFieldMask =
        (TypeTraits<BitVector>::One << CollisionDistanceFieldId);
    static const OSG::BitVector SecondaryCollisionSystemsFieldMask =
        (TypeTraits<BitVector>::One << SecondaryCollisionSystemsFieldId);
    static const OSG::BitVector EventProducerFieldMask =
        (TypeTraits<BitVector>::One << EventProducerFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFReal32          SFCollisionDistanceType;
    typedef MFUnrecParticleSystemPtr MFSecondaryCollisionSystemsType;
    typedef SFEventProducerPtr          SFEventProducerType;

    enum
    {
        ParticleCollisionMethodId = 1,
        NextProducedMethodId = ParticleCollisionMethodId + 1
    };

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static FieldContainerType &getClassType   (void);
    static UInt32              getClassTypeId (void);
    static UInt16              getClassGroupId(void);
    static const  EventProducerType  &getProducerClassType  (void);
    static        UInt32              getProducerClassTypeId(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                FieldContainer Get                            */
    /*! \{                                                                 */

    virtual       FieldContainerType &getType         (void);
    virtual const FieldContainerType &getType         (void) const;

    virtual       UInt32              getContainerSize(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */


                  SFReal32            *editSFCollisionDistance(void);
            const SFReal32            *getSFCollisionDistance (void) const;
            const MFUnrecParticleSystemPtr *getMFSecondaryCollisionSystems(void) const;
                  MFUnrecParticleSystemPtr *editMFSecondaryCollisionSystems(void);


                  Real32              &editCollisionDistance(void);
                  Real32               getCollisionDistance (void) const;

                  ParticleSystem * getSecondaryCollisionSystems(const UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setCollisionDistance(const Real32 value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr Field Set                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

    void pushToSecondaryCollisionSystems           (ParticleSystem * const value   );
    void assignSecondaryCollisionSystems          (const MFUnrecParticleSystemPtr &value);
    void removeFromSecondaryCollisionSystems (UInt32               uiIndex );
    void removeObjFromSecondaryCollisionSystems(ParticleSystem * const value   );
    void clearSecondaryCollisionSystems            (void                         );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    virtual UInt32 getBinSize (ConstFieldMaskArg  whichField);
    virtual void   copyToBin  (BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);
    virtual void   copyFromBin(BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Method Produced Get                           */
    /*! \{                                                                 */

    virtual const EventProducerType &getProducerType(void) const; 

    EventConnection          attachActivity             (ActivityRefPtr TheActivity,
                                                         UInt32 ProducedEventId);
    bool                     isActivityAttached         (ActivityRefPtr TheActivity,
                                                         UInt32 ProducedEventId) const;
    UInt32                   getNumActivitiesAttached   (UInt32 ProducedEventId) const;
    ActivityRefPtr           getAttachedActivity        (UInt32 ProducedEventId,
                                                         UInt32 ActivityIndex) const;
    void                     detachActivity             (ActivityRefPtr TheActivity,
                                                         UInt32 ProducedEventId);
    UInt32                   getNumProducedEvents       (void) const;
    const MethodDescription *getProducedEventDescription(const std::string &ProducedEventName) const;
    const MethodDescription *getProducedEventDescription(UInt32 ProducedEventId) const;
    UInt32                   getProducedEventId         (const std::string &ProducedEventName) const;

    SFEventProducerPtr *editSFEventProducer(void);
    EventProducerPtr   &editEventProducer  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static  CollisionParticleSystemAffectorTransitPtr  create          (void);
    static  CollisionParticleSystemAffector           *createEmpty     (void);

    static  CollisionParticleSystemAffectorTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  CollisionParticleSystemAffector            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  CollisionParticleSystemAffectorTransitPtr  createDependent  (BitVector bFlags);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Copy                                   */
    /*! \{                                                                 */

    virtual FieldContainerTransitPtr shallowCopy     (void) const;
    virtual FieldContainerTransitPtr shallowCopyLocal(
                                       BitVector bFlags = FCLocal::All) const;
    virtual FieldContainerTransitPtr shallowCopyDependent(
                                                      BitVector bFlags) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
    /*---------------------------------------------------------------------*/
    /*! \name                    Event Producer                            */
    /*! \{                                                                 */
    EventProducer _Producer;

    /*! \}                                                                 */

    static TypeObject _type;

    static       void   classDescInserter(TypeObject &oType);
    static const Char8 *getClassname     (void             );

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFReal32          _sfCollisionDistance;
    MFUnrecParticleSystemPtr _mfSecondaryCollisionSystems;
    SFEventProducerPtr _sfEventProducer;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    CollisionParticleSystemAffectorBase(void);
    CollisionParticleSystemAffectorBase(const CollisionParticleSystemAffectorBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CollisionParticleSystemAffectorBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const CollisionParticleSystemAffector *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleCollisionDistance (void) const;
    EditFieldHandlePtr editHandleCollisionDistance(void);
    GetFieldHandlePtr  getHandleSecondaryCollisionSystems (void) const;
    EditFieldHandlePtr editHandleSecondaryCollisionSystems(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);

            void execSync (      CollisionParticleSystemAffectorBase *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Aspect Create                            */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual FieldContainer *createAspectCopy(
                                    const FieldContainer *pRefAspect) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
    /*---------------------------------------------------------------------*/
    static MethodDescription   *_methodDesc[];
    static EventProducerType _producerType;


    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CollisionParticleSystemAffectorBase &source);
};

typedef CollisionParticleSystemAffectorBase *CollisionParticleSystemAffectorBaseP;

OSG_END_NAMESPACE

#endif /* _OSGCOLLISIONPARTICLESYSTEMAFFECTORBASE_H_ */