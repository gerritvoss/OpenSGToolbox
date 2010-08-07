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
 **     class ParticleEvent
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGPARTICLEEVENTBASE_H_
#define _OSGPARTICLEEVENTBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribParticleSystemDef.h"

//#include "OSGBaseTypes.h"

#include "OSGEvent.h" // Parent

#include "OSGSysFields.h"               // ParticleIndex type
#include "OSGVecFields.h"               // ParticlePosition type
#include "OSGBaseFields.h"              // ParticleColor type
#include "OSGStringToUInt32MapFields.h" // ParticleAttributes type

#include "OSGParticleEventFields.h"

OSG_BEGIN_NAMESPACE

class ParticleEvent;

//! \brief ParticleEvent Base Class.

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING ParticleEventBase : public Event
{
  public:

    typedef Event Inherited;
    typedef Event ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(ParticleEvent);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        ParticleIndexFieldId = Inherited::NextFieldId,
        ParticleIDFieldId = ParticleIndexFieldId + 1,
        ParticlePositionFieldId = ParticleIDFieldId + 1,
        ParticleSecPositionFieldId = ParticlePositionFieldId + 1,
        ParticleNormalFieldId = ParticleSecPositionFieldId + 1,
        ParticleColorFieldId = ParticleNormalFieldId + 1,
        ParticleSizeFieldId = ParticleColorFieldId + 1,
        ParticleLifespanFieldId = ParticleSizeFieldId + 1,
        ParticleAgeFieldId = ParticleLifespanFieldId + 1,
        ParticleVelocityFieldId = ParticleAgeFieldId + 1,
        ParticleSecVelocityFieldId = ParticleVelocityFieldId + 1,
        ParticleAccelerationFieldId = ParticleSecVelocityFieldId + 1,
        ParticleAttributesFieldId = ParticleAccelerationFieldId + 1,
        NextFieldId = ParticleAttributesFieldId + 1
    };

    static const OSG::BitVector ParticleIndexFieldMask =
        (TypeTraits<BitVector>::One << ParticleIndexFieldId);
    static const OSG::BitVector ParticleIDFieldMask =
        (TypeTraits<BitVector>::One << ParticleIDFieldId);
    static const OSG::BitVector ParticlePositionFieldMask =
        (TypeTraits<BitVector>::One << ParticlePositionFieldId);
    static const OSG::BitVector ParticleSecPositionFieldMask =
        (TypeTraits<BitVector>::One << ParticleSecPositionFieldId);
    static const OSG::BitVector ParticleNormalFieldMask =
        (TypeTraits<BitVector>::One << ParticleNormalFieldId);
    static const OSG::BitVector ParticleColorFieldMask =
        (TypeTraits<BitVector>::One << ParticleColorFieldId);
    static const OSG::BitVector ParticleSizeFieldMask =
        (TypeTraits<BitVector>::One << ParticleSizeFieldId);
    static const OSG::BitVector ParticleLifespanFieldMask =
        (TypeTraits<BitVector>::One << ParticleLifespanFieldId);
    static const OSG::BitVector ParticleAgeFieldMask =
        (TypeTraits<BitVector>::One << ParticleAgeFieldId);
    static const OSG::BitVector ParticleVelocityFieldMask =
        (TypeTraits<BitVector>::One << ParticleVelocityFieldId);
    static const OSG::BitVector ParticleSecVelocityFieldMask =
        (TypeTraits<BitVector>::One << ParticleSecVelocityFieldId);
    static const OSG::BitVector ParticleAccelerationFieldMask =
        (TypeTraits<BitVector>::One << ParticleAccelerationFieldId);
    static const OSG::BitVector ParticleAttributesFieldMask =
        (TypeTraits<BitVector>::One << ParticleAttributesFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFInt32           SFParticleIndexType;
    typedef SFUInt32          SFParticleIDType;
    typedef SFPnt3f           SFParticlePositionType;
    typedef SFPnt3f           SFParticleSecPositionType;
    typedef SFVec3f           SFParticleNormalType;
    typedef SFColor4f         SFParticleColorType;
    typedef SFVec3f           SFParticleSizeType;
    typedef SFReal32          SFParticleLifespanType;
    typedef SFReal32          SFParticleAgeType;
    typedef SFVec3f           SFParticleVelocityType;
    typedef SFVec3f           SFParticleSecVelocityType;
    typedef SFVec3f           SFParticleAccelerationType;
    typedef SFStringToUInt32Map SFParticleAttributesType;

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


            const SFInt32             *getSFParticleIndex   (void) const;

            const SFUInt32            *getSFParticleID      (void) const;

            const SFPnt3f             *getSFParticlePosition (void) const;

            const SFPnt3f             *getSFParticleSecPosition (void) const;

            const SFVec3f             *getSFParticleNormal  (void) const;

            const SFColor4f           *getSFParticleColor   (void) const;

            const SFVec3f             *getSFParticleSize    (void) const;

            const SFReal32            *getSFParticleLifespan (void) const;

            const SFReal32            *getSFParticleAge     (void) const;

            const SFVec3f             *getSFParticleVelocity (void) const;

            const SFVec3f             *getSFParticleSecVelocity (void) const;

            const SFVec3f             *getSFParticleAcceleration (void) const;

            const SFStringToUInt32Map *getSFParticleAttributes (void) const;


                  Int32                getParticleIndex   (void) const;

                  UInt32               getParticleID      (void) const;

            const Pnt3f               &getParticlePosition (void) const;

            const Pnt3f               &getParticleSecPosition (void) const;

            const Vec3f               &getParticleNormal  (void) const;

            const Color4f             &getParticleColor   (void) const;

            const Vec3f               &getParticleSize    (void) const;

                  Real32               getParticleLifespan (void) const;

                  Real32               getParticleAge     (void) const;

            const Vec3f               &getParticleVelocity (void) const;

            const Vec3f               &getParticleSecVelocity (void) const;

            const Vec3f               &getParticleAcceleration (void) const;

            const StringToUInt32Map   &getParticleAttributes (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
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

    static  ParticleEventTransitPtr  create          (void);
    static  ParticleEvent           *createEmpty     (void);

    static  ParticleEventTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  ParticleEvent            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  ParticleEventTransitPtr  createDependent  (BitVector bFlags);

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

    SFInt32           _sfParticleIndex;
    SFUInt32          _sfParticleID;
    SFPnt3f           _sfParticlePosition;
    SFPnt3f           _sfParticleSecPosition;
    SFVec3f           _sfParticleNormal;
    SFColor4f         _sfParticleColor;
    SFVec3f           _sfParticleSize;
    SFReal32          _sfParticleLifespan;
    SFReal32          _sfParticleAge;
    SFVec3f           _sfParticleVelocity;
    SFVec3f           _sfParticleSecVelocity;
    SFVec3f           _sfParticleAcceleration;
    SFStringToUInt32Map _sfParticleAttributes;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ParticleEventBase(void);
    ParticleEventBase(const ParticleEventBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleEventBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleParticleIndex   (void) const;
    EditFieldHandlePtr editHandleParticleIndex  (void);
    GetFieldHandlePtr  getHandleParticleID      (void) const;
    EditFieldHandlePtr editHandleParticleID     (void);
    GetFieldHandlePtr  getHandleParticlePosition (void) const;
    EditFieldHandlePtr editHandleParticlePosition(void);
    GetFieldHandlePtr  getHandleParticleSecPosition (void) const;
    EditFieldHandlePtr editHandleParticleSecPosition(void);
    GetFieldHandlePtr  getHandleParticleNormal  (void) const;
    EditFieldHandlePtr editHandleParticleNormal (void);
    GetFieldHandlePtr  getHandleParticleColor   (void) const;
    EditFieldHandlePtr editHandleParticleColor  (void);
    GetFieldHandlePtr  getHandleParticleSize    (void) const;
    EditFieldHandlePtr editHandleParticleSize   (void);
    GetFieldHandlePtr  getHandleParticleLifespan (void) const;
    EditFieldHandlePtr editHandleParticleLifespan(void);
    GetFieldHandlePtr  getHandleParticleAge     (void) const;
    EditFieldHandlePtr editHandleParticleAge    (void);
    GetFieldHandlePtr  getHandleParticleVelocity (void) const;
    EditFieldHandlePtr editHandleParticleVelocity(void);
    GetFieldHandlePtr  getHandleParticleSecVelocity (void) const;
    EditFieldHandlePtr editHandleParticleSecVelocity(void);
    GetFieldHandlePtr  getHandleParticleAcceleration (void) const;
    EditFieldHandlePtr editHandleParticleAcceleration(void);
    GetFieldHandlePtr  getHandleParticleAttributes (void) const;
    EditFieldHandlePtr editHandleParticleAttributes(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */


                  SFInt32             *editSFParticleIndex  (void);

                  SFUInt32            *editSFParticleID     (void);

                  SFPnt3f             *editSFParticlePosition(void);

                  SFPnt3f             *editSFParticleSecPosition(void);

                  SFVec3f             *editSFParticleNormal (void);

                  SFColor4f           *editSFParticleColor  (void);

                  SFVec3f             *editSFParticleSize   (void);

                  SFReal32            *editSFParticleLifespan(void);

                  SFReal32            *editSFParticleAge    (void);

                  SFVec3f             *editSFParticleVelocity(void);

                  SFVec3f             *editSFParticleSecVelocity(void);

                  SFVec3f             *editSFParticleAcceleration(void);

                  SFStringToUInt32Map *editSFParticleAttributes(void);


                  Int32               &editParticleIndex  (void);

                  UInt32              &editParticleID     (void);

                  Pnt3f               &editParticlePosition(void);

                  Pnt3f               &editParticleSecPosition(void);

                  Vec3f               &editParticleNormal (void);

                  Color4f             &editParticleColor  (void);

                  Vec3f               &editParticleSize   (void);

                  Real32              &editParticleLifespan(void);

                  Real32              &editParticleAge    (void);

                  Vec3f               &editParticleVelocity(void);

                  Vec3f               &editParticleSecVelocity(void);

                  Vec3f               &editParticleAcceleration(void);

                  StringToUInt32Map   &editParticleAttributes(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setParticleIndex  (const Int32 value);
            void setParticleID     (const UInt32 value);
            void setParticlePosition(const Pnt3f &value);
            void setParticleSecPosition(const Pnt3f &value);
            void setParticleNormal (const Vec3f &value);
            void setParticleColor  (const Color4f &value);
            void setParticleSize   (const Vec3f &value);
            void setParticleLifespan(const Real32 value);
            void setParticleAge    (const Real32 value);
            void setParticleVelocity(const Vec3f &value);
            void setParticleSecVelocity(const Vec3f &value);
            void setParticleAcceleration(const Vec3f &value);
            void setParticleAttributes(const StringToUInt32Map &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

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

            void execSync (      ParticleEventBase *pFrom,
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
    void operator =(const ParticleEventBase &source);
};

typedef ParticleEventBase *ParticleEventBaseP;

OSG_END_NAMESPACE

#endif /* _OSGPARTICLEEVENTBASE_H_ */
