/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), Daniel Guilliams           *
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
 **     class AirParticleAffector
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGAIRPARTICLEAFFECTORBASE_H_
#define _OSGAIRPARTICLEAFFECTORBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribParticleSystemDef.h"

//#include "OSGBaseTypes.h"

#include "OSGParticleAffector.h" // Parent

#include "OSGSysFields.h"               // Magnitude type
#include "OSGVecFields.h"               // Direction type
#include "OSGNodeFields.h"              // Beacon type

#include "OSGAirParticleAffectorFields.h"

OSG_BEGIN_NAMESPACE

class AirParticleAffector;

//! \brief AirParticleAffector Base Class.

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING AirParticleAffectorBase : public ParticleAffector
{
  public:

    typedef ParticleAffector Inherited;
    typedef ParticleAffector ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(AirParticleAffector);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        MagnitudeFieldId = Inherited::NextFieldId,
        DirectionFieldId = MagnitudeFieldId + 1,
        AttenuationFieldId = DirectionFieldId + 1,
        SpeedFieldId = AttenuationFieldId + 1,
        SpreadFieldId = SpeedFieldId + 1,
        MaxDistanceFieldId = SpreadFieldId + 1,
        UseSpreadFieldId = MaxDistanceFieldId + 1,
        BeaconFieldId = UseSpreadFieldId + 1,
        NextFieldId = BeaconFieldId + 1
    };

    static const OSG::BitVector MagnitudeFieldMask =
        (TypeTraits<BitVector>::One << MagnitudeFieldId);
    static const OSG::BitVector DirectionFieldMask =
        (TypeTraits<BitVector>::One << DirectionFieldId);
    static const OSG::BitVector AttenuationFieldMask =
        (TypeTraits<BitVector>::One << AttenuationFieldId);
    static const OSG::BitVector SpeedFieldMask =
        (TypeTraits<BitVector>::One << SpeedFieldId);
    static const OSG::BitVector SpreadFieldMask =
        (TypeTraits<BitVector>::One << SpreadFieldId);
    static const OSG::BitVector MaxDistanceFieldMask =
        (TypeTraits<BitVector>::One << MaxDistanceFieldId);
    static const OSG::BitVector UseSpreadFieldMask =
        (TypeTraits<BitVector>::One << UseSpreadFieldId);
    static const OSG::BitVector BeaconFieldMask =
        (TypeTraits<BitVector>::One << BeaconFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFReal32          SFMagnitudeType;
    typedef SFVec3f           SFDirectionType;
    typedef SFReal32          SFAttenuationType;
    typedef SFReal32          SFSpeedType;
    typedef SFReal32          SFSpreadType;
    typedef SFReal32          SFMaxDistanceType;
    typedef SFBool            SFUseSpreadType;
    typedef SFUnrecNodePtr    SFBeaconType;

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static FieldContainerType &getClassType   (void);
    static UInt32              getClassTypeId (void);
    static UInt16              getClassGroupId(void);

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


                  SFReal32            *editSFMagnitude      (void);
            const SFReal32            *getSFMagnitude       (void) const;

                  SFVec3f             *editSFDirection      (void);
            const SFVec3f             *getSFDirection       (void) const;

                  SFReal32            *editSFAttenuation    (void);
            const SFReal32            *getSFAttenuation     (void) const;

                  SFReal32            *editSFSpeed          (void);
            const SFReal32            *getSFSpeed           (void) const;

                  SFReal32            *editSFSpread         (void);
            const SFReal32            *getSFSpread          (void) const;

                  SFReal32            *editSFMaxDistance    (void);
            const SFReal32            *getSFMaxDistance     (void) const;

                  SFBool              *editSFUseSpread      (void);
            const SFBool              *getSFUseSpread       (void) const;
            const SFUnrecNodePtr      *getSFBeacon         (void) const;
                  SFUnrecNodePtr      *editSFBeacon         (void);


                  Real32              &editMagnitude      (void);
                  Real32               getMagnitude       (void) const;

                  Vec3f               &editDirection      (void);
            const Vec3f               &getDirection       (void) const;

                  Real32              &editAttenuation    (void);
                  Real32               getAttenuation     (void) const;

                  Real32              &editSpeed          (void);
                  Real32               getSpeed           (void) const;

                  Real32              &editSpread         (void);
                  Real32               getSpread          (void) const;

                  Real32              &editMaxDistance    (void);
                  Real32               getMaxDistance     (void) const;

                  bool                &editUseSpread      (void);
                  bool                 getUseSpread       (void) const;

                  Node * getBeacon         (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setMagnitude      (const Real32 value);
            void setDirection      (const Vec3f &value);
            void setAttenuation    (const Real32 value);
            void setSpeed          (const Real32 value);
            void setSpread         (const Real32 value);
            void setMaxDistance    (const Real32 value);
            void setUseSpread      (const bool value);
            void setBeacon         (Node * const value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr Field Set                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

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
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static  AirParticleAffectorTransitPtr  create          (void);
    static  AirParticleAffector           *createEmpty     (void);

    static  AirParticleAffectorTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  AirParticleAffector            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  AirParticleAffectorTransitPtr  createDependent  (BitVector bFlags);

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

    static TypeObject _type;

    static       void   classDescInserter(TypeObject &oType);
    static const Char8 *getClassname     (void             );

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFReal32          _sfMagnitude;
    SFVec3f           _sfDirection;
    SFReal32          _sfAttenuation;
    SFReal32          _sfSpeed;
    SFReal32          _sfSpread;
    SFReal32          _sfMaxDistance;
    SFBool            _sfUseSpread;
    SFUnrecNodePtr    _sfBeacon;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    AirParticleAffectorBase(void);
    AirParticleAffectorBase(const AirParticleAffectorBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AirParticleAffectorBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const AirParticleAffector *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleMagnitude       (void) const;
    EditFieldHandlePtr editHandleMagnitude      (void);
    GetFieldHandlePtr  getHandleDirection       (void) const;
    EditFieldHandlePtr editHandleDirection      (void);
    GetFieldHandlePtr  getHandleAttenuation     (void) const;
    EditFieldHandlePtr editHandleAttenuation    (void);
    GetFieldHandlePtr  getHandleSpeed           (void) const;
    EditFieldHandlePtr editHandleSpeed          (void);
    GetFieldHandlePtr  getHandleSpread          (void) const;
    EditFieldHandlePtr editHandleSpread         (void);
    GetFieldHandlePtr  getHandleMaxDistance     (void) const;
    EditFieldHandlePtr editHandleMaxDistance    (void);
    GetFieldHandlePtr  getHandleUseSpread       (void) const;
    EditFieldHandlePtr editHandleUseSpread      (void);
    GetFieldHandlePtr  getHandleBeacon          (void) const;
    EditFieldHandlePtr editHandleBeacon         (void);

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

            void execSync (      AirParticleAffectorBase *pFrom,
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

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AirParticleAffectorBase &source);
};

typedef AirParticleAffectorBase *AirParticleAffectorBaseP;

OSG_END_NAMESPACE

#endif /* _OSGAIRPARTICLEAFFECTORBASE_H_ */