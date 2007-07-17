/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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
 **     class RectUIDrawObject
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGRECTUIDRAWOBJECTBASE_H_
#define _OSGRECTUIDRAWOBJECTBASE_H_
#ifdef __sgi
#pragma once
#endif


#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGRefPtr.h>
#include <OpenSG/OSGCoredNodePtr.h>

#include "OSGUIDrawObject.h" // Parent

#include <OpenSG/OSGVec2sFields.h> // TopLeft type
#include <OpenSG/OSGVec2sFields.h> // BottomRight type
#include <OpenSG/OSGColor4fFields.h> // Color type
#include <OpenSG/OSGReal32Fields.h> // Opacity type

#include "OSGRectUIDrawObjectFields.h"

OSG_BEGIN_NAMESPACE

class RectUIDrawObject;
class BinaryDataHandler;

//! \brief RectUIDrawObject Base Class.

class OSG_USERINTERFACELIB_DLLMAPPING RectUIDrawObjectBase : public UIDrawObject
{
  private:

    typedef UIDrawObject    Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    typedef RectUIDrawObjectPtr  Ptr;

    enum
    {
        TopLeftFieldId     = Inherited::NextFieldId,
        BottomRightFieldId = TopLeftFieldId     + 1,
        ColorFieldId       = BottomRightFieldId + 1,
        OpacityFieldId     = ColorFieldId       + 1,
        NextFieldId        = OpacityFieldId     + 1
    };

    static const OSG::BitVector TopLeftFieldMask;
    static const OSG::BitVector BottomRightFieldMask;
    static const OSG::BitVector ColorFieldMask;
    static const OSG::BitVector OpacityFieldMask;


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

           SFPnt2s             *getSFTopLeft        (void);
           SFPnt2s             *getSFBottomRight    (void);
           SFColor4f           *getSFColor          (void);
           SFReal32            *getSFOpacity        (void);

           Pnt2s               &getTopLeft        (void);
     const Pnt2s               &getTopLeft        (void) const;
           Pnt2s               &getBottomRight    (void);
     const Pnt2s               &getBottomRight    (void) const;
           Color4f             &getColor          (void);
     const Color4f             &getColor          (void) const;
           Real32              &getOpacity        (void);
     const Real32              &getOpacity        (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setTopLeft        ( const Pnt2s &value );
     void setBottomRight    ( const Pnt2s &value );
     void setColor          ( const Color4f &value );
     void setOpacity        ( const Real32 &value );

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

    static  RectUIDrawObjectPtr      create          (void); 
    static  RectUIDrawObjectPtr      createEmpty     (void); 

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

    SFPnt2s             _sfTopLeft;
    SFPnt2s             _sfBottomRight;
    SFColor4f           _sfColor;
    SFReal32            _sfOpacity;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    RectUIDrawObjectBase(void);
    RectUIDrawObjectBase(const RectUIDrawObjectBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RectUIDrawObjectBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#if !defined(OSG_FIXED_MFIELDSYNC)
    void executeSyncImpl(      RectUIDrawObjectBase *pOther,
                         const BitVector         &whichField);

    virtual void   executeSync(      FieldContainer    &other,
                               const BitVector         &whichField);
#else
    void executeSyncImpl(      RectUIDrawObjectBase *pOther,
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
    void operator =(const RectUIDrawObjectBase &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


typedef RectUIDrawObjectBase *RectUIDrawObjectBaseP;

typedef osgIF<RectUIDrawObjectBase::isNodeCore,
              CoredNodePtr<RectUIDrawObject>,
              FieldContainer::attempt_to_create_CoredNodePtr_on_non_NodeCore_FC
              >::_IRet RectUIDrawObjectNodePtr;

typedef RefPtr<RectUIDrawObjectPtr> RectUIDrawObjectRefPtr;

OSG_END_NAMESPACE

#define OSGRECTUIDRAWOBJECTBASE_HEADER_CVSID "@(#)$Id: FCBaseTemplate_h.h,v 1.40 2005/07/20 00:10:14 vossg Exp $"

#endif /* _OSGRECTUIDRAWOBJECTBASE_H_ */
