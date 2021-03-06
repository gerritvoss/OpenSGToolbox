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
 **     class SineWaveParticleAffector
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGSINEWAVEPARTICLEAFFECTORBASE_H_
#define _OSGSINEWAVEPARTICLEAFFECTORBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribParticleSystemDef.h"

//#include "OSGBaseTypes.h"

#include "OSGParticleAffector.h" // Parent

#include "OSGSysFields.h"               // Amplitude type

#include "OSGSineWaveParticleAffectorFields.h"

OSG_BEGIN_NAMESPACE

class SineWaveParticleAffector;

//! \brief SineWaveParticleAffector Base Class.

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING SineWaveParticleAffectorBase : public ParticleAffector
{
  public:

    typedef ParticleAffector Inherited;
    typedef ParticleAffector ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(SineWaveParticleAffector);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        AmplitudeFieldId = Inherited::NextFieldId,
        FrequencyFieldId = AmplitudeFieldId + 1,
        UpDirSourceFieldId = FrequencyFieldId + 1,
        NextFieldId = UpDirSourceFieldId + 1
    };

    static const OSG::BitVector AmplitudeFieldMask =
        (TypeTraits<BitVector>::One << AmplitudeFieldId);
    static const OSG::BitVector FrequencyFieldMask =
        (TypeTraits<BitVector>::One << FrequencyFieldId);
    static const OSG::BitVector UpDirSourceFieldMask =
        (TypeTraits<BitVector>::One << UpDirSourceFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFReal32          SFAmplitudeType;
    typedef SFReal32          SFFrequencyType;
    typedef SFInt32           SFUpDirSourceType;

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


                  SFReal32            *editSFAmplitude      (void);
            const SFReal32            *getSFAmplitude       (void) const;

                  SFReal32            *editSFFrequency      (void);
            const SFReal32            *getSFFrequency       (void) const;

                  SFInt32             *editSFUpDirSource    (void);
            const SFInt32             *getSFUpDirSource     (void) const;


                  Real32              &editAmplitude      (void);
                  Real32               getAmplitude       (void) const;

                  Real32              &editFrequency      (void);
                  Real32               getFrequency       (void) const;

                  Int32               &editUpDirSource    (void);
                  Int32                getUpDirSource     (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setAmplitude      (const Real32 value);
            void setFrequency      (const Real32 value);
            void setUpDirSource    (const Int32 value);

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

    static  SineWaveParticleAffectorTransitPtr  create          (void);
    static  SineWaveParticleAffector           *createEmpty     (void);

    static  SineWaveParticleAffectorTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  SineWaveParticleAffector            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  SineWaveParticleAffectorTransitPtr  createDependent  (BitVector bFlags);

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

    SFReal32          _sfAmplitude;
    SFReal32          _sfFrequency;
    SFInt32           _sfUpDirSource;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SineWaveParticleAffectorBase(void);
    SineWaveParticleAffectorBase(const SineWaveParticleAffectorBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SineWaveParticleAffectorBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleAmplitude       (void) const;
    EditFieldHandlePtr editHandleAmplitude      (void);
    GetFieldHandlePtr  getHandleFrequency       (void) const;
    EditFieldHandlePtr editHandleFrequency      (void);
    GetFieldHandlePtr  getHandleUpDirSource     (void) const;
    EditFieldHandlePtr editHandleUpDirSource    (void);

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

            void execSync (      SineWaveParticleAffectorBase *pFrom,
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
    void operator =(const SineWaveParticleAffectorBase &source);
};

typedef SineWaveParticleAffectorBase *SineWaveParticleAffectorBaseP;

OSG_END_NAMESPACE

#endif /* _OSGSINEWAVEPARTICLEAFFECTORBASE_H_ */
