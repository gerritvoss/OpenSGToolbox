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
 **     class RadioButton
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGRADIOBUTTONBASE_H_
#define _OSGRADIOBUTTONBASE_H_
#ifdef __sgi
#pragma once
#endif


#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGRefPtr.h>
#include <OpenSG/OSGCoredNodePtr.h>

#include "OSGToggleButton.h" // Parent

#include "OSGUIDrawObjectCanvas.h" // DrawObject type
#include "OSGUIDrawObjectCanvas.h" // CheckedDrawObject type
#include "OSGUIDrawObjectCanvas.h" // ActiveDrawObject type
#include "OSGUIDrawObjectCanvas.h" // ActiveCheckedDrawObject type

#include "OSGRadioButtonFields.h"

OSG_BEGIN_NAMESPACE

class RadioButton;
class BinaryDataHandler;

//! \brief RadioButton Base Class.

class OSG_USERINTERFACELIB_DLLMAPPING RadioButtonBase : public ToggleButton
{
  private:

    typedef ToggleButton    Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    typedef RadioButtonPtr  Ptr;

    enum
    {
        DrawObjectFieldId              = Inherited::NextFieldId,
        CheckedDrawObjectFieldId       = DrawObjectFieldId              + 1,
        ActiveDrawObjectFieldId        = CheckedDrawObjectFieldId       + 1,
        ActiveCheckedDrawObjectFieldId = ActiveDrawObjectFieldId        + 1,
        NextFieldId                    = ActiveCheckedDrawObjectFieldId + 1
    };

    static const OSG::BitVector DrawObjectFieldMask;
    static const OSG::BitVector CheckedDrawObjectFieldMask;
    static const OSG::BitVector ActiveDrawObjectFieldMask;
    static const OSG::BitVector ActiveCheckedDrawObjectFieldMask;


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

           SFUIDrawObjectCanvasPtr *getSFDrawObject     (void);
           SFUIDrawObjectCanvasPtr *getSFCheckedDrawObject(void);
           SFUIDrawObjectCanvasPtr *getSFActiveDrawObject(void);
           SFUIDrawObjectCanvasPtr *getSFActiveCheckedDrawObject(void);

           UIDrawObjectCanvasPtr &getDrawObject     (void);
     const UIDrawObjectCanvasPtr &getDrawObject     (void) const;
           UIDrawObjectCanvasPtr &getCheckedDrawObject(void);
     const UIDrawObjectCanvasPtr &getCheckedDrawObject(void) const;
           UIDrawObjectCanvasPtr &getActiveDrawObject(void);
     const UIDrawObjectCanvasPtr &getActiveDrawObject(void) const;
           UIDrawObjectCanvasPtr &getActiveCheckedDrawObject(void);
     const UIDrawObjectCanvasPtr &getActiveCheckedDrawObject(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setDrawObject     ( const UIDrawObjectCanvasPtr &value );
     void setCheckedDrawObject( const UIDrawObjectCanvasPtr &value );
     void setActiveDrawObject( const UIDrawObjectCanvasPtr &value );
     void setActiveCheckedDrawObject( const UIDrawObjectCanvasPtr &value );

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

    static  RadioButtonPtr      create          (void); 
    static  RadioButtonPtr      createEmpty     (void); 

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

    SFUIDrawObjectCanvasPtr   _sfDrawObject;
    SFUIDrawObjectCanvasPtr   _sfCheckedDrawObject;
    SFUIDrawObjectCanvasPtr   _sfActiveDrawObject;
    SFUIDrawObjectCanvasPtr   _sfActiveCheckedDrawObject;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    RadioButtonBase(void);
    RadioButtonBase(const RadioButtonBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RadioButtonBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#if !defined(OSG_FIXED_MFIELDSYNC)
    void executeSyncImpl(      RadioButtonBase *pOther,
                         const BitVector         &whichField);

    virtual void   executeSync(      FieldContainer    &other,
                               const BitVector         &whichField);
#else
    void executeSyncImpl(      RadioButtonBase *pOther,
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
    void operator =(const RadioButtonBase &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


typedef RadioButtonBase *RadioButtonBaseP;

typedef osgIF<RadioButtonBase::isNodeCore,
              CoredNodePtr<RadioButton>,
              FieldContainer::attempt_to_create_CoredNodePtr_on_non_NodeCore_FC
              >::_IRet RadioButtonNodePtr;

typedef RefPtr<RadioButtonPtr> RadioButtonRefPtr;

OSG_END_NAMESPACE

#define OSGRADIOBUTTONBASE_HEADER_CVSID "@(#)$Id: FCBaseTemplate_h.h,v 1.40 2005/07/20 00:10:14 vossg Exp $"

#endif /* _OSGRADIOBUTTONBASE_H_ */
