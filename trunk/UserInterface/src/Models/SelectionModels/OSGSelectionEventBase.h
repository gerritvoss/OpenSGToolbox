/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
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
 **     class SelectionEvent
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGSELECTIONEVENTBASE_H_
#define _OSGSELECTIONEVENTBASE_H_
#ifdef __sgi
#pragma once
#endif


#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGRefPtr.h>
#include <OpenSG/OSGCoredNodePtr.h>

#include <OpenSG/Toolbox/OSGEvent.h> // Parent

#include <OpenSG/OSGInt32Fields.h> // Selected type
#include <OpenSG/OSGInt32Fields.h> // PreviouslySelected type
#include <OpenSG/OSGBoolFields.h> // ValueIsAdjusting type

#include "OSGSelectionEventFields.h"
OSG_BEGIN_NAMESPACE

class SelectionEvent;
class BinaryDataHandler;

//! \brief SelectionEvent Base Class.

class OSG_USERINTERFACELIB_DLLMAPPING SelectionEventBase : public Event
{
  private:

    typedef Event    Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    typedef SelectionEventPtr  Ptr;

    enum
    {
        SelectedFieldId           = Inherited::NextFieldId,
        PreviouslySelectedFieldId = SelectedFieldId           + 1,
        ValueIsAdjustingFieldId   = PreviouslySelectedFieldId + 1,
        NextFieldId               = ValueIsAdjustingFieldId   + 1
    };

    static const OSG::BitVector SelectedFieldMask;
    static const OSG::BitVector PreviouslySelectedFieldMask;
    static const OSG::BitVector ValueIsAdjustingFieldMask;


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

     const MFInt32             *getMFSelected       (void) const;
     const MFInt32             *getMFPreviouslySelected(void) const;
     const SFBool              *getSFValueIsAdjusting(void) const;


     const bool                &getValueIsAdjusting(void) const;

     const Int32               &getSelected       (const UInt32 index) const;

     const Int32               &getPreviouslySelected(const UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */


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

    static  SelectionEventPtr      create          (void); 
    static  SelectionEventPtr      createEmpty     (void); 

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

    MFInt32             _mfSelected;
    MFInt32             _mfPreviouslySelected;
    SFBool              _sfValueIsAdjusting;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SelectionEventBase(void);
    SelectionEventBase(const SelectionEventBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SelectionEventBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

           MFInt32             *editMFSelected       (void);
           MFInt32             *editMFPreviouslySelected(void);
           SFBool              *editSFValueIsAdjusting(void);

           bool                &editValueIsAdjusting(void);
           Int32               &editSelected       (UInt32 index);
#ifndef OSG_2_PREP
           MFInt32             &getSelected       (void);
     const MFInt32             &getSelected       (void) const;
#endif
           Int32               &editPreviouslySelected(UInt32 index);
#ifndef OSG_2_PREP
           MFInt32             &getPreviouslySelected(void);
     const MFInt32             &getPreviouslySelected(void) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setValueIsAdjusting(const bool &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#if !defined(OSG_FIXED_MFIELDSYNC)
    void executeSyncImpl(      SelectionEventBase *pOther,
                         const BitVector         &whichField);

    virtual void   executeSync(      FieldContainer    &other,
                               const BitVector         &whichField);
#else
    void executeSyncImpl(      SelectionEventBase *pOther,
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
    void operator =(const SelectionEventBase &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


typedef SelectionEventBase *SelectionEventBaseP;

typedef osgIF<SelectionEventBase::isNodeCore,
              CoredNodePtr<SelectionEvent>,
              FieldContainer::attempt_to_create_CoredNodePtr_on_non_NodeCore_FC
              >::_IRet SelectionEventNodePtr;

typedef RefPtr<SelectionEventPtr> SelectionEventRefPtr;

OSG_END_NAMESPACE

#endif /* _OSGSELECTIONEVENTBASE_H_ */