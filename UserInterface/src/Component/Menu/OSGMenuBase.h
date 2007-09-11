/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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
 **     class Menu
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGMENUBASE_H_
#define _OSGMENUBASE_H_
#ifdef __sgi
#pragma once
#endif


#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGRefPtr.h>
#include <OpenSG/OSGCoredNodePtr.h>

#include "OSGLabelMenuItem.h" // Parent

#include "Component/Button/OSGToggleButtonFields.h" // Button type
#include "Component/Menu/OSGPopupMenuFields.h" // InternalPopupMenu type
#include <OpenSG/OSGReal32Fields.h> // SubMenuDelay type
#include <OpenSG/OSGBoolFields.h> // TopLevelMenu type
#include "Component/OSGUIDrawObjectCanvas.h" // ExpandDrawObject type
#include "Component/Menu/OSGMenuItemFields.h" // MenuItems type

#include "OSGMenuFields.h"

OSG_BEGIN_NAMESPACE

class Menu;
class BinaryDataHandler;

//! \brief Menu Base Class.

class OSG_USERINTERFACELIB_DLLMAPPING MenuBase : public LabelMenuItem
{
  private:

    typedef LabelMenuItem    Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    typedef MenuPtr  Ptr;

    enum
    {
        ButtonFieldId            = Inherited::NextFieldId,
        InternalPopupMenuFieldId = ButtonFieldId            + 1,
        SubMenuDelayFieldId      = InternalPopupMenuFieldId + 1,
        TopLevelMenuFieldId      = SubMenuDelayFieldId      + 1,
        ExpandDrawObjectFieldId  = TopLevelMenuFieldId      + 1,
        MenuItemsFieldId         = ExpandDrawObjectFieldId  + 1,
        NextFieldId              = MenuItemsFieldId         + 1
    };

    static const OSG::BitVector ButtonFieldMask;
    static const OSG::BitVector InternalPopupMenuFieldMask;
    static const OSG::BitVector SubMenuDelayFieldMask;
    static const OSG::BitVector TopLevelMenuFieldMask;
    static const OSG::BitVector ExpandDrawObjectFieldMask;
    static const OSG::BitVector MenuItemsFieldMask;


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

           SFToggleButtonPtr   *getSFButton         (void);
           SFReal32            *getSFSubMenuDelay   (void);
           SFBool              *getSFTopLevelMenu   (void);
           SFUIDrawObjectCanvasPtr *getSFExpandDrawObject(void);

           ToggleButtonPtr     &getButton         (void);
     const ToggleButtonPtr     &getButton         (void) const;
           Real32              &getSubMenuDelay   (void);
     const Real32              &getSubMenuDelay   (void) const;
           bool                &getTopLevelMenu   (void);
     const bool                &getTopLevelMenu   (void) const;
           UIDrawObjectCanvasPtr &getExpandDrawObject(void);
     const UIDrawObjectCanvasPtr &getExpandDrawObject(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setButton         ( const ToggleButtonPtr &value );
     void setSubMenuDelay   ( const Real32 &value );
     void setTopLevelMenu   ( const bool &value );
     void setExpandDrawObject( const UIDrawObjectCanvasPtr &value );

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

    static  MenuPtr      create          (void); 
    static  MenuPtr      createEmpty     (void); 

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

    SFToggleButtonPtr   _sfButton;
    SFPopupMenuPtr      _sfInternalPopupMenu;
    SFReal32            _sfSubMenuDelay;
    SFBool              _sfTopLevelMenu;
    SFUIDrawObjectCanvasPtr   _sfExpandDrawObject;
    MFMenuItemPtr       _mfMenuItems;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    MenuBase(void);
    MenuBase(const MenuBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MenuBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

           SFPopupMenuPtr      *getSFInternalPopupMenu(void);
           MFMenuItemPtr       *getMFMenuItems      (void);

           PopupMenuPtr        &getInternalPopupMenu(void);
     const PopupMenuPtr        &getInternalPopupMenu(void) const;
           MenuItemPtr         &getMenuItems      (UInt32 index);
           MFMenuItemPtr       &getMenuItems      (void);
     const MFMenuItemPtr       &getMenuItems      (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setInternalPopupMenu(const PopupMenuPtr &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#if !defined(OSG_FIXED_MFIELDSYNC)
    void executeSyncImpl(      MenuBase *pOther,
                         const BitVector         &whichField);

    virtual void   executeSync(      FieldContainer    &other,
                               const BitVector         &whichField);
#else
    void executeSyncImpl(      MenuBase *pOther,
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
    void operator =(const MenuBase &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


typedef MenuBase *MenuBaseP;

typedef osgIF<MenuBase::isNodeCore,
              CoredNodePtr<Menu>,
              FieldContainer::attempt_to_create_CoredNodePtr_on_non_NodeCore_FC
              >::_IRet MenuNodePtr;

typedef RefPtr<MenuPtr> MenuRefPtr;

OSG_END_NAMESPACE

#define OSGMENUBASE_HEADER_CVSID "@(#)$Id: FCBaseTemplate_h.h,v 1.40 2005/07/20 00:10:14 vossg Exp $"

#endif /* _OSGMENUBASE_H_ */
