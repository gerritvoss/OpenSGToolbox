/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Dynamics                            *
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
 **     class PerlinNoiseDistribution3D
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGPERLINNOISEDISTRIBUTION3DBASE_H_
#define _OSGPERLINNOISEDISTRIBUTION3DBASE_H_
#ifdef __sgi
#pragma once
#endif


#include <OpenSG/OSGConfig.h>
#include "OSGDynamicsDef.h"

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGRefPtr.h>
#include <OpenSG/OSGCoredNodePtr.h>

#include "Function/OSGFunction.h" // Parent

#include <OpenSG/OSGUInt32Fields.h> // Frequency type
#include <OpenSG/OSGReal32Fields.h> // Persistance type
#include <OpenSG/OSGUInt32Fields.h> // Octaves type
#include <OpenSG/OSGReal32Fields.h> // Amplitude type
#include <OpenSG/OSGUInt32Fields.h> // InterpolationType type

#include "OSGPerlinNoiseDistribution3DFields.h"

OSG_BEGIN_NAMESPACE

class PerlinNoiseDistribution3D;
class BinaryDataHandler;

//! \brief PerlinNoiseDistribution3D Base Class.

class OSG_DYNAMICSLIB_DLLMAPPING PerlinNoiseDistribution3DBase : public Function
{
  private:

    typedef Function    Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    typedef PerlinNoiseDistribution3DPtr  Ptr;

    enum
    {
        FrequencyFieldId         = Inherited::NextFieldId,
        PersistanceFieldId       = FrequencyFieldId         + 1,
        OctavesFieldId           = PersistanceFieldId       + 1,
        AmplitudeFieldId         = OctavesFieldId           + 1,
        InterpolationTypeFieldId = AmplitudeFieldId         + 1,
        NextFieldId              = InterpolationTypeFieldId + 1
    };

    static const OSG::BitVector FrequencyFieldMask;
    static const OSG::BitVector PersistanceFieldMask;
    static const OSG::BitVector OctavesFieldMask;
    static const OSG::BitVector AmplitudeFieldMask;
    static const OSG::BitVector InterpolationTypeFieldMask;


    static const OSG::BitVector MTInfluenceMask;

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static        FieldContainerType &getClassType    (void); 
    static        UInt32              getClassTypeId  (void); 

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

           SFUInt32            *getSFFrequency      (void);
           SFReal32            *getSFPersistance    (void);
           SFUInt32            *getSFOctaves        (void);
           SFReal32            *getSFAmplitude      (void);
           SFUInt32            *getSFInterpolationType(void);

           UInt32              &getFrequency      (void);
     const UInt32              &getFrequency      (void) const;
           Real32              &getPersistance    (void);
     const Real32              &getPersistance    (void) const;
           UInt32              &getOctaves        (void);
     const UInt32              &getOctaves        (void) const;
           Real32              &getAmplitude      (void);
     const Real32              &getAmplitude      (void) const;
           UInt32              &getInterpolationType(void);
     const UInt32              &getInterpolationType(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setFrequency      ( const UInt32 &value );
     void setPersistance    ( const Real32 &value );
     void setOctaves        ( const UInt32 &value );
     void setAmplitude      ( const Real32 &value );
     void setInterpolationType( const UInt32 &value );

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

    static  PerlinNoiseDistribution3DPtr      create          (void); 
    static  PerlinNoiseDistribution3DPtr      createEmpty     (void); 

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                       Copy                                   */
    /*! \{                                                                 */

    virtual FieldContainerPtr     shallowCopy     (void) const; 

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFUInt32            _sfFrequency;
    SFReal32            _sfPersistance;
    SFUInt32            _sfOctaves;
    SFReal32            _sfAmplitude;
    SFUInt32            _sfInterpolationType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PerlinNoiseDistribution3DBase(void);
    PerlinNoiseDistribution3DBase(const PerlinNoiseDistribution3DBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PerlinNoiseDistribution3DBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#if !defined(OSG_FIXED_MFIELDSYNC)
    void executeSyncImpl(      PerlinNoiseDistribution3DBase *pOther,
                         const BitVector         &whichField);

    virtual void   executeSync(      FieldContainer    &other,
                               const BitVector         &whichField);
#else
    void executeSyncImpl(      PerlinNoiseDistribution3DBase *pOther,
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

    static FieldDescription   *_desc[];
    static FieldContainerType  _type;


    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PerlinNoiseDistribution3DBase &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


typedef PerlinNoiseDistribution3DBase *PerlinNoiseDistribution3DBaseP;

typedef osgIF<PerlinNoiseDistribution3DBase::isNodeCore,
              CoredNodePtr<PerlinNoiseDistribution3D>,
              FieldContainer::attempt_to_create_CoredNodePtr_on_non_NodeCore_FC
              >::_IRet PerlinNoiseDistribution3DNodePtr;

typedef RefPtr<PerlinNoiseDistribution3DPtr> PerlinNoiseDistribution3DRefPtr;

OSG_END_NAMESPACE

#define OSGPERLINNOISEDISTRIBUTION3DBASE_HEADER_CVSID "@(#)$Id: FCBaseTemplate_h.h,v 1.40 2005/07/20 00:10:14 vossg Exp $"

#endif /* _OSGPERLINNOISEDISTRIBUTION3DBASE_H_ */
