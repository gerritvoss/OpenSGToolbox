/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com),  Behboud Kalantary         *
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
 **     class PhysicsLMotorJoint
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGPHYSICSLMOTORJOINTBASE_H_
#define _OSGPHYSICSLMOTORJOINTBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribPhysicsDef.h"

//#include "OSGBaseTypes.h"

#include "OSGPhysicsJoint.h" // Parent

#include "OSGSysFields.h"               // NumAxes type
#include "OSGVecFields.h"               // Axis1 type

#include "OSGPhysicsLMotorJointFields.h"

OSG_BEGIN_NAMESPACE

class PhysicsLMotorJoint;

//! \brief PhysicsLMotorJoint Base Class.

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsLMotorJointBase : public PhysicsJoint
{
  public:

    typedef PhysicsJoint Inherited;
    typedef PhysicsJoint ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(PhysicsLMotorJoint);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        NumAxesFieldId = Inherited::NextFieldId,
        Axis1FieldId = NumAxesFieldId + 1,
        Axis2FieldId = Axis1FieldId + 1,
        Axis3FieldId = Axis2FieldId + 1,
        Axis1ReferenceFrameFieldId = Axis3FieldId + 1,
        Axis2ReferenceFrameFieldId = Axis1ReferenceFrameFieldId + 1,
        Axis3ReferenceFrameFieldId = Axis2ReferenceFrameFieldId + 1,
        VelFieldId = Axis3ReferenceFrameFieldId + 1,
        FMaxFieldId = VelFieldId + 1,
        FudgeFactorFieldId = FMaxFieldId + 1,
        Vel2FieldId = FudgeFactorFieldId + 1,
        FMax2FieldId = Vel2FieldId + 1,
        FudgeFactor2FieldId = FMax2FieldId + 1,
        Vel3FieldId = FudgeFactor2FieldId + 1,
        FMax3FieldId = Vel3FieldId + 1,
        FudgeFactor3FieldId = FMax3FieldId + 1,
        HiStopFieldId = FudgeFactor3FieldId + 1,
        LoStopFieldId = HiStopFieldId + 1,
        BounceFieldId = LoStopFieldId + 1,
        CFMFieldId = BounceFieldId + 1,
        StopERPFieldId = CFMFieldId + 1,
        StopCFMFieldId = StopERPFieldId + 1,
        HiStop2FieldId = StopCFMFieldId + 1,
        LoStop2FieldId = HiStop2FieldId + 1,
        Bounce2FieldId = LoStop2FieldId + 1,
        CFM2FieldId = Bounce2FieldId + 1,
        StopERP2FieldId = CFM2FieldId + 1,
        StopCFM2FieldId = StopERP2FieldId + 1,
        HiStop3FieldId = StopCFM2FieldId + 1,
        LoStop3FieldId = HiStop3FieldId + 1,
        Bounce3FieldId = LoStop3FieldId + 1,
        CFM3FieldId = Bounce3FieldId + 1,
        StopERP3FieldId = CFM3FieldId + 1,
        StopCFM3FieldId = StopERP3FieldId + 1,
        NextFieldId = StopCFM3FieldId + 1
    };

    static const OSG::BitVector NumAxesFieldMask =
        (TypeTraits<BitVector>::One << NumAxesFieldId);
    static const OSG::BitVector Axis1FieldMask =
        (TypeTraits<BitVector>::One << Axis1FieldId);
    static const OSG::BitVector Axis2FieldMask =
        (TypeTraits<BitVector>::One << Axis2FieldId);
    static const OSG::BitVector Axis3FieldMask =
        (TypeTraits<BitVector>::One << Axis3FieldId);
    static const OSG::BitVector Axis1ReferenceFrameFieldMask =
        (TypeTraits<BitVector>::One << Axis1ReferenceFrameFieldId);
    static const OSG::BitVector Axis2ReferenceFrameFieldMask =
        (TypeTraits<BitVector>::One << Axis2ReferenceFrameFieldId);
    static const OSG::BitVector Axis3ReferenceFrameFieldMask =
        (TypeTraits<BitVector>::One << Axis3ReferenceFrameFieldId);
    static const OSG::BitVector VelFieldMask =
        (TypeTraits<BitVector>::One << VelFieldId);
    static const OSG::BitVector FMaxFieldMask =
        (TypeTraits<BitVector>::One << FMaxFieldId);
    static const OSG::BitVector FudgeFactorFieldMask =
        (TypeTraits<BitVector>::One << FudgeFactorFieldId);
    static const OSG::BitVector Vel2FieldMask =
        (TypeTraits<BitVector>::One << Vel2FieldId);
    static const OSG::BitVector FMax2FieldMask =
        (TypeTraits<BitVector>::One << FMax2FieldId);
    static const OSG::BitVector FudgeFactor2FieldMask =
        (TypeTraits<BitVector>::One << FudgeFactor2FieldId);
    static const OSG::BitVector Vel3FieldMask =
        (TypeTraits<BitVector>::One << Vel3FieldId);
    static const OSG::BitVector FMax3FieldMask =
        (TypeTraits<BitVector>::One << FMax3FieldId);
    static const OSG::BitVector FudgeFactor3FieldMask =
        (TypeTraits<BitVector>::One << FudgeFactor3FieldId);
    static const OSG::BitVector HiStopFieldMask =
        (TypeTraits<BitVector>::One << HiStopFieldId);
    static const OSG::BitVector LoStopFieldMask =
        (TypeTraits<BitVector>::One << LoStopFieldId);
    static const OSG::BitVector BounceFieldMask =
        (TypeTraits<BitVector>::One << BounceFieldId);
    static const OSG::BitVector CFMFieldMask =
        (TypeTraits<BitVector>::One << CFMFieldId);
    static const OSG::BitVector StopERPFieldMask =
        (TypeTraits<BitVector>::One << StopERPFieldId);
    static const OSG::BitVector StopCFMFieldMask =
        (TypeTraits<BitVector>::One << StopCFMFieldId);
    static const OSG::BitVector HiStop2FieldMask =
        (TypeTraits<BitVector>::One << HiStop2FieldId);
    static const OSG::BitVector LoStop2FieldMask =
        (TypeTraits<BitVector>::One << LoStop2FieldId);
    static const OSG::BitVector Bounce2FieldMask =
        (TypeTraits<BitVector>::One << Bounce2FieldId);
    static const OSG::BitVector CFM2FieldMask =
        (TypeTraits<BitVector>::One << CFM2FieldId);
    static const OSG::BitVector StopERP2FieldMask =
        (TypeTraits<BitVector>::One << StopERP2FieldId);
    static const OSG::BitVector StopCFM2FieldMask =
        (TypeTraits<BitVector>::One << StopCFM2FieldId);
    static const OSG::BitVector HiStop3FieldMask =
        (TypeTraits<BitVector>::One << HiStop3FieldId);
    static const OSG::BitVector LoStop3FieldMask =
        (TypeTraits<BitVector>::One << LoStop3FieldId);
    static const OSG::BitVector Bounce3FieldMask =
        (TypeTraits<BitVector>::One << Bounce3FieldId);
    static const OSG::BitVector CFM3FieldMask =
        (TypeTraits<BitVector>::One << CFM3FieldId);
    static const OSG::BitVector StopERP3FieldMask =
        (TypeTraits<BitVector>::One << StopERP3FieldId);
    static const OSG::BitVector StopCFM3FieldMask =
        (TypeTraits<BitVector>::One << StopCFM3FieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFUInt8           SFNumAxesType;
    typedef SFVec3f           SFAxis1Type;
    typedef SFVec3f           SFAxis2Type;
    typedef SFVec3f           SFAxis3Type;
    typedef SFUInt8           SFAxis1ReferenceFrameType;
    typedef SFUInt8           SFAxis2ReferenceFrameType;
    typedef SFUInt8           SFAxis3ReferenceFrameType;
    typedef SFReal32          SFVelType;
    typedef SFReal32          SFFMaxType;
    typedef SFReal32          SFFudgeFactorType;
    typedef SFReal32          SFVel2Type;
    typedef SFReal32          SFFMax2Type;
    typedef SFReal32          SFFudgeFactor2Type;
    typedef SFReal32          SFVel3Type;
    typedef SFReal32          SFFMax3Type;
    typedef SFReal32          SFFudgeFactor3Type;
    typedef SFReal32          SFHiStopType;
    typedef SFReal32          SFLoStopType;
    typedef SFReal32          SFBounceType;
    typedef SFReal32          SFCFMType;
    typedef SFReal32          SFStopERPType;
    typedef SFReal32          SFStopCFMType;
    typedef SFReal32          SFHiStop2Type;
    typedef SFReal32          SFLoStop2Type;
    typedef SFReal32          SFBounce2Type;
    typedef SFReal32          SFCFM2Type;
    typedef SFReal32          SFStopERP2Type;
    typedef SFReal32          SFStopCFM2Type;
    typedef SFReal32          SFHiStop3Type;
    typedef SFReal32          SFLoStop3Type;
    typedef SFReal32          SFBounce3Type;
    typedef SFReal32          SFCFM3Type;
    typedef SFReal32          SFStopERP3Type;
    typedef SFReal32          SFStopCFM3Type;

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


                  SFUInt8             *editSFNumAxes        (void);
            const SFUInt8             *getSFNumAxes         (void) const;

                  SFReal32            *editSFVel            (void);
            const SFReal32            *getSFVel             (void) const;

                  SFReal32            *editSFFMax           (void);
            const SFReal32            *getSFFMax            (void) const;

                  SFReal32            *editSFFudgeFactor    (void);
            const SFReal32            *getSFFudgeFactor     (void) const;

                  SFReal32            *editSFVel2           (void);
            const SFReal32            *getSFVel2            (void) const;

                  SFReal32            *editSFFMax2          (void);
            const SFReal32            *getSFFMax2           (void) const;

                  SFReal32            *editSFFudgeFactor2   (void);
            const SFReal32            *getSFFudgeFactor2    (void) const;

                  SFReal32            *editSFVel3           (void);
            const SFReal32            *getSFVel3            (void) const;

                  SFReal32            *editSFFMax3          (void);
            const SFReal32            *getSFFMax3           (void) const;

                  SFReal32            *editSFFudgeFactor3   (void);
            const SFReal32            *getSFFudgeFactor3    (void) const;

                  SFReal32            *editSFHiStop         (void);
            const SFReal32            *getSFHiStop          (void) const;

                  SFReal32            *editSFLoStop         (void);
            const SFReal32            *getSFLoStop          (void) const;

                  SFReal32            *editSFBounce         (void);
            const SFReal32            *getSFBounce          (void) const;

                  SFReal32            *editSFCFM            (void);
            const SFReal32            *getSFCFM             (void) const;

                  SFReal32            *editSFStopERP        (void);
            const SFReal32            *getSFStopERP         (void) const;

                  SFReal32            *editSFStopCFM        (void);
            const SFReal32            *getSFStopCFM         (void) const;

                  SFReal32            *editSFHiStop2        (void);
            const SFReal32            *getSFHiStop2         (void) const;

                  SFReal32            *editSFLoStop2        (void);
            const SFReal32            *getSFLoStop2         (void) const;

                  SFReal32            *editSFBounce2        (void);
            const SFReal32            *getSFBounce2         (void) const;

                  SFReal32            *editSFCFM2           (void);
            const SFReal32            *getSFCFM2            (void) const;

                  SFReal32            *editSFStopERP2       (void);
            const SFReal32            *getSFStopERP2        (void) const;

                  SFReal32            *editSFStopCFM2       (void);
            const SFReal32            *getSFStopCFM2        (void) const;

                  SFReal32            *editSFHiStop3        (void);
            const SFReal32            *getSFHiStop3         (void) const;

                  SFReal32            *editSFLoStop3        (void);
            const SFReal32            *getSFLoStop3         (void) const;

                  SFReal32            *editSFBounce3        (void);
            const SFReal32            *getSFBounce3         (void) const;

                  SFReal32            *editSFCFM3           (void);
            const SFReal32            *getSFCFM3            (void) const;

                  SFReal32            *editSFStopERP3       (void);
            const SFReal32            *getSFStopERP3        (void) const;

                  SFReal32            *editSFStopCFM3       (void);
            const SFReal32            *getSFStopCFM3        (void) const;


                  UInt8               &editNumAxes        (void);
                  UInt8                getNumAxes         (void) const;

                  Real32              &editVel            (void);
                  Real32               getVel             (void) const;

                  Real32              &editFMax           (void);
                  Real32               getFMax            (void) const;

                  Real32              &editFudgeFactor    (void);
                  Real32               getFudgeFactor     (void) const;

                  Real32              &editVel2           (void);
                  Real32               getVel2            (void) const;

                  Real32              &editFMax2          (void);
                  Real32               getFMax2           (void) const;

                  Real32              &editFudgeFactor2   (void);
                  Real32               getFudgeFactor2    (void) const;

                  Real32              &editVel3           (void);
                  Real32               getVel3            (void) const;

                  Real32              &editFMax3          (void);
                  Real32               getFMax3           (void) const;

                  Real32              &editFudgeFactor3   (void);
                  Real32               getFudgeFactor3    (void) const;

                  Real32              &editHiStop         (void);
                  Real32               getHiStop          (void) const;

                  Real32              &editLoStop         (void);
                  Real32               getLoStop          (void) const;

                  Real32              &editBounce         (void);
                  Real32               getBounce          (void) const;

                  Real32              &editCFM            (void);
                  Real32               getCFM             (void) const;

                  Real32              &editStopERP        (void);
                  Real32               getStopERP         (void) const;

                  Real32              &editStopCFM        (void);
                  Real32               getStopCFM         (void) const;

                  Real32              &editHiStop2        (void);
                  Real32               getHiStop2         (void) const;

                  Real32              &editLoStop2        (void);
                  Real32               getLoStop2         (void) const;

                  Real32              &editBounce2        (void);
                  Real32               getBounce2         (void) const;

                  Real32              &editCFM2           (void);
                  Real32               getCFM2            (void) const;

                  Real32              &editStopERP2       (void);
                  Real32               getStopERP2        (void) const;

                  Real32              &editStopCFM2       (void);
                  Real32               getStopCFM2        (void) const;

                  Real32              &editHiStop3        (void);
                  Real32               getHiStop3         (void) const;

                  Real32              &editLoStop3        (void);
                  Real32               getLoStop3         (void) const;

                  Real32              &editBounce3        (void);
                  Real32               getBounce3         (void) const;

                  Real32              &editCFM3           (void);
                  Real32               getCFM3            (void) const;

                  Real32              &editStopERP3       (void);
                  Real32               getStopERP3        (void) const;

                  Real32              &editStopCFM3       (void);
                  Real32               getStopCFM3        (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setNumAxes        (const UInt8 value);
            void setVel            (const Real32 value);
            void setFMax           (const Real32 value);
            void setFudgeFactor    (const Real32 value);
            void setVel2           (const Real32 value);
            void setFMax2          (const Real32 value);
            void setFudgeFactor2   (const Real32 value);
            void setVel3           (const Real32 value);
            void setFMax3          (const Real32 value);
            void setFudgeFactor3   (const Real32 value);
            void setHiStop         (const Real32 value);
            void setLoStop         (const Real32 value);
            void setBounce         (const Real32 value);
            void setCFM            (const Real32 value);
            void setStopERP        (const Real32 value);
            void setStopCFM        (const Real32 value);
            void setHiStop2        (const Real32 value);
            void setLoStop2        (const Real32 value);
            void setBounce2        (const Real32 value);
            void setCFM2           (const Real32 value);
            void setStopERP2       (const Real32 value);
            void setStopCFM2       (const Real32 value);
            void setHiStop3        (const Real32 value);
            void setLoStop3        (const Real32 value);
            void setBounce3        (const Real32 value);
            void setCFM3           (const Real32 value);
            void setStopERP3       (const Real32 value);
            void setStopCFM3       (const Real32 value);

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

    static  PhysicsLMotorJointTransitPtr  create          (void);
    static  PhysicsLMotorJoint           *createEmpty     (void);

    static  PhysicsLMotorJointTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  PhysicsLMotorJoint            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  PhysicsLMotorJointTransitPtr  createDependent  (BitVector bFlags);

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

    SFUInt8           _sfNumAxes;
    SFVec3f           _sfAxis1;
    SFVec3f           _sfAxis2;
    SFVec3f           _sfAxis3;
    SFUInt8           _sfAxis1ReferenceFrame;
    SFUInt8           _sfAxis2ReferenceFrame;
    SFUInt8           _sfAxis3ReferenceFrame;
    SFReal32          _sfVel;
    SFReal32          _sfFMax;
    SFReal32          _sfFudgeFactor;
    SFReal32          _sfVel2;
    SFReal32          _sfFMax2;
    SFReal32          _sfFudgeFactor2;
    SFReal32          _sfVel3;
    SFReal32          _sfFMax3;
    SFReal32          _sfFudgeFactor3;
    SFReal32          _sfHiStop;
    SFReal32          _sfLoStop;
    SFReal32          _sfBounce;
    SFReal32          _sfCFM;
    SFReal32          _sfStopERP;
    SFReal32          _sfStopCFM;
    SFReal32          _sfHiStop2;
    SFReal32          _sfLoStop2;
    SFReal32          _sfBounce2;
    SFReal32          _sfCFM2;
    SFReal32          _sfStopERP2;
    SFReal32          _sfStopCFM2;
    SFReal32          _sfHiStop3;
    SFReal32          _sfLoStop3;
    SFReal32          _sfBounce3;
    SFReal32          _sfCFM3;
    SFReal32          _sfStopERP3;
    SFReal32          _sfStopCFM3;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PhysicsLMotorJointBase(void);
    PhysicsLMotorJointBase(const PhysicsLMotorJointBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsLMotorJointBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleNumAxes         (void) const;
    EditFieldHandlePtr editHandleNumAxes        (void);
    GetFieldHandlePtr  getHandleAxis1           (void) const;
    EditFieldHandlePtr editHandleAxis1          (void);
    GetFieldHandlePtr  getHandleAxis2           (void) const;
    EditFieldHandlePtr editHandleAxis2          (void);
    GetFieldHandlePtr  getHandleAxis3           (void) const;
    EditFieldHandlePtr editHandleAxis3          (void);
    GetFieldHandlePtr  getHandleAxis1ReferenceFrame (void) const;
    EditFieldHandlePtr editHandleAxis1ReferenceFrame(void);
    GetFieldHandlePtr  getHandleAxis2ReferenceFrame (void) const;
    EditFieldHandlePtr editHandleAxis2ReferenceFrame(void);
    GetFieldHandlePtr  getHandleAxis3ReferenceFrame (void) const;
    EditFieldHandlePtr editHandleAxis3ReferenceFrame(void);
    GetFieldHandlePtr  getHandleVel             (void) const;
    EditFieldHandlePtr editHandleVel            (void);
    GetFieldHandlePtr  getHandleFMax            (void) const;
    EditFieldHandlePtr editHandleFMax           (void);
    GetFieldHandlePtr  getHandleFudgeFactor     (void) const;
    EditFieldHandlePtr editHandleFudgeFactor    (void);
    GetFieldHandlePtr  getHandleVel2            (void) const;
    EditFieldHandlePtr editHandleVel2           (void);
    GetFieldHandlePtr  getHandleFMax2           (void) const;
    EditFieldHandlePtr editHandleFMax2          (void);
    GetFieldHandlePtr  getHandleFudgeFactor2    (void) const;
    EditFieldHandlePtr editHandleFudgeFactor2   (void);
    GetFieldHandlePtr  getHandleVel3            (void) const;
    EditFieldHandlePtr editHandleVel3           (void);
    GetFieldHandlePtr  getHandleFMax3           (void) const;
    EditFieldHandlePtr editHandleFMax3          (void);
    GetFieldHandlePtr  getHandleFudgeFactor3    (void) const;
    EditFieldHandlePtr editHandleFudgeFactor3   (void);
    GetFieldHandlePtr  getHandleHiStop          (void) const;
    EditFieldHandlePtr editHandleHiStop         (void);
    GetFieldHandlePtr  getHandleLoStop          (void) const;
    EditFieldHandlePtr editHandleLoStop         (void);
    GetFieldHandlePtr  getHandleBounce          (void) const;
    EditFieldHandlePtr editHandleBounce         (void);
    GetFieldHandlePtr  getHandleCFM             (void) const;
    EditFieldHandlePtr editHandleCFM            (void);
    GetFieldHandlePtr  getHandleStopERP         (void) const;
    EditFieldHandlePtr editHandleStopERP        (void);
    GetFieldHandlePtr  getHandleStopCFM         (void) const;
    EditFieldHandlePtr editHandleStopCFM        (void);
    GetFieldHandlePtr  getHandleHiStop2         (void) const;
    EditFieldHandlePtr editHandleHiStop2        (void);
    GetFieldHandlePtr  getHandleLoStop2         (void) const;
    EditFieldHandlePtr editHandleLoStop2        (void);
    GetFieldHandlePtr  getHandleBounce2         (void) const;
    EditFieldHandlePtr editHandleBounce2        (void);
    GetFieldHandlePtr  getHandleCFM2            (void) const;
    EditFieldHandlePtr editHandleCFM2           (void);
    GetFieldHandlePtr  getHandleStopERP2        (void) const;
    EditFieldHandlePtr editHandleStopERP2       (void);
    GetFieldHandlePtr  getHandleStopCFM2        (void) const;
    EditFieldHandlePtr editHandleStopCFM2       (void);
    GetFieldHandlePtr  getHandleHiStop3         (void) const;
    EditFieldHandlePtr editHandleHiStop3        (void);
    GetFieldHandlePtr  getHandleLoStop3         (void) const;
    EditFieldHandlePtr editHandleLoStop3        (void);
    GetFieldHandlePtr  getHandleBounce3         (void) const;
    EditFieldHandlePtr editHandleBounce3        (void);
    GetFieldHandlePtr  getHandleCFM3            (void) const;
    EditFieldHandlePtr editHandleCFM3           (void);
    GetFieldHandlePtr  getHandleStopERP3        (void) const;
    EditFieldHandlePtr editHandleStopERP3       (void);
    GetFieldHandlePtr  getHandleStopCFM3        (void) const;
    EditFieldHandlePtr editHandleStopCFM3       (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */


                  SFVec3f             *editSFAxis1          (void);
            const SFVec3f             *getSFAxis1           (void) const;

                  SFVec3f             *editSFAxis2          (void);
            const SFVec3f             *getSFAxis2           (void) const;

                  SFVec3f             *editSFAxis3          (void);
            const SFVec3f             *getSFAxis3           (void) const;

                  SFUInt8             *editSFAxis1ReferenceFrame(void);
            const SFUInt8             *getSFAxis1ReferenceFrame (void) const;

                  SFUInt8             *editSFAxis2ReferenceFrame(void);
            const SFUInt8             *getSFAxis2ReferenceFrame (void) const;

                  SFUInt8             *editSFAxis3ReferenceFrame(void);
            const SFUInt8             *getSFAxis3ReferenceFrame (void) const;


                  Vec3f               &editAxis1          (void);
            const Vec3f               &getAxis1           (void) const;

                  Vec3f               &editAxis2          (void);
            const Vec3f               &getAxis2           (void) const;

                  Vec3f               &editAxis3          (void);
            const Vec3f               &getAxis3           (void) const;

                  UInt8               &editAxis1ReferenceFrame(void);
                  UInt8                getAxis1ReferenceFrame (void) const;

                  UInt8               &editAxis2ReferenceFrame(void);
                  UInt8                getAxis2ReferenceFrame (void) const;

                  UInt8               &editAxis3ReferenceFrame(void);
                  UInt8                getAxis3ReferenceFrame (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setAxis1          (const Vec3f &value);
            void setAxis2          (const Vec3f &value);
            void setAxis3          (const Vec3f &value);
            void setAxis1ReferenceFrame(const UInt8 value);
            void setAxis2ReferenceFrame(const UInt8 value);
            void setAxis3ReferenceFrame(const UInt8 value);

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

            void execSync (      PhysicsLMotorJointBase *pFrom,
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
    void operator =(const PhysicsLMotorJointBase &source);
};

typedef PhysicsLMotorJointBase *PhysicsLMotorJointBaseP;

OSG_END_NAMESPACE

#endif /* _OSGPHYSICSLMOTORJOINTBASE_H_ */