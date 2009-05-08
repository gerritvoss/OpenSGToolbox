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
 **     class ScrollBar
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGSCROLLBARBASE_H_
#define _OSGSCROLLBARBASE_H_
#ifdef __sgi
#pragma once
#endif


#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGRefPtr.h>
#include <OpenSG/OSGCoredNodePtr.h>

#include "Component/Container/OSGContainer.h" // Parent

#include <OpenSG/OSGUInt32Fields.h> // Orientation type
#include <OpenSG/OSGUInt32Fields.h> // UnitIncrement type
#include <OpenSG/OSGUInt32Fields.h> // BlockIncrement type
#include "Component/Button/OSGButton.h" // VerticalMinButton type
#include "Component/Button/OSGButton.h" // VerticalMaxButton type
#include "Component/Button/OSGButton.h" // VerticalScrollBar type
#include "Component/Button/OSGButton.h" // VerticalScrollField type
#include "Component/Button/OSGButton.h" // HorizontalMinButton type
#include "Component/Button/OSGButton.h" // HorizontalMaxButton type
#include "Component/Button/OSGButton.h" // HorizontalScrollBar type
#include "Component/Button/OSGButton.h" // HorizontalScrollField type
#include <OpenSG/OSGUInt32Fields.h> // ScrollBarMinLength type
#include "Component/Scroll/OSGBoundedRangeModelFields.h" // RangeModel type

#include "OSGScrollBarFields.h"

OSG_BEGIN_NAMESPACE

class ScrollBar;
class BinaryDataHandler;

//! \brief ScrollBar Base Class.

class OSG_USERINTERFACELIB_DLLMAPPING ScrollBarBase : public Container
{
  private:

    typedef Container    Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    typedef ScrollBarPtr  Ptr;

    enum
    {
        OrientationFieldId           = Inherited::NextFieldId,
        UnitIncrementFieldId         = OrientationFieldId           + 1,
        BlockIncrementFieldId        = UnitIncrementFieldId         + 1,
        VerticalMinButtonFieldId     = BlockIncrementFieldId        + 1,
        VerticalMaxButtonFieldId     = VerticalMinButtonFieldId     + 1,
        VerticalScrollBarFieldId     = VerticalMaxButtonFieldId     + 1,
        VerticalScrollFieldFieldId   = VerticalScrollBarFieldId     + 1,
        HorizontalMinButtonFieldId   = VerticalScrollFieldFieldId   + 1,
        HorizontalMaxButtonFieldId   = HorizontalMinButtonFieldId   + 1,
        HorizontalScrollBarFieldId   = HorizontalMaxButtonFieldId   + 1,
        HorizontalScrollFieldFieldId = HorizontalScrollBarFieldId   + 1,
        ScrollBarMinLengthFieldId    = HorizontalScrollFieldFieldId + 1,
        RangeModelFieldId            = ScrollBarMinLengthFieldId    + 1,
        NextFieldId                  = RangeModelFieldId            + 1
    };

    static const OSG::BitVector OrientationFieldMask;
    static const OSG::BitVector UnitIncrementFieldMask;
    static const OSG::BitVector BlockIncrementFieldMask;
    static const OSG::BitVector VerticalMinButtonFieldMask;
    static const OSG::BitVector VerticalMaxButtonFieldMask;
    static const OSG::BitVector VerticalScrollBarFieldMask;
    static const OSG::BitVector VerticalScrollFieldFieldMask;
    static const OSG::BitVector HorizontalMinButtonFieldMask;
    static const OSG::BitVector HorizontalMaxButtonFieldMask;
    static const OSG::BitVector HorizontalScrollBarFieldMask;
    static const OSG::BitVector HorizontalScrollFieldFieldMask;
    static const OSG::BitVector ScrollBarMinLengthFieldMask;
    static const OSG::BitVector RangeModelFieldMask;


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

           SFUInt32            *getSFOrientation    (void);
           SFUInt32            *getSFUnitIncrement  (void);
           SFUInt32            *getSFBlockIncrement (void);
           SFButtonPtr         *getSFVerticalMinButton(void);
           SFButtonPtr         *getSFVerticalMaxButton(void);
           SFButtonPtr         *getSFVerticalScrollBar(void);
           SFButtonPtr         *getSFVerticalScrollField(void);
           SFButtonPtr         *getSFHorizontalMinButton(void);
           SFButtonPtr         *getSFHorizontalMaxButton(void);
           SFButtonPtr         *getSFHorizontalScrollBar(void);
           SFButtonPtr         *getSFHorizontalScrollField(void);
           SFUInt32            *getSFScrollBarMinLength(void);
           SFBoundedRangeModelPtr *getSFRangeModel     (void);

           UInt32              &getOrientation    (void);
     const UInt32              &getOrientation    (void) const;
           UInt32              &getUnitIncrement  (void);
     const UInt32              &getUnitIncrement  (void) const;
           UInt32              &getBlockIncrement (void);
     const UInt32              &getBlockIncrement (void) const;
           ButtonPtr           &getVerticalMinButton(void);
     const ButtonPtr           &getVerticalMinButton(void) const;
           ButtonPtr           &getVerticalMaxButton(void);
     const ButtonPtr           &getVerticalMaxButton(void) const;
           ButtonPtr           &getVerticalScrollBar(void);
     const ButtonPtr           &getVerticalScrollBar(void) const;
           ButtonPtr           &getVerticalScrollField(void);
     const ButtonPtr           &getVerticalScrollField(void) const;
           ButtonPtr           &getHorizontalMinButton(void);
     const ButtonPtr           &getHorizontalMinButton(void) const;
           ButtonPtr           &getHorizontalMaxButton(void);
     const ButtonPtr           &getHorizontalMaxButton(void) const;
           ButtonPtr           &getHorizontalScrollBar(void);
     const ButtonPtr           &getHorizontalScrollBar(void) const;
           ButtonPtr           &getHorizontalScrollField(void);
     const ButtonPtr           &getHorizontalScrollField(void) const;
           UInt32              &getScrollBarMinLength(void);
     const UInt32              &getScrollBarMinLength(void) const;
           BoundedRangeModelPtr &getRangeModel     (void);
     const BoundedRangeModelPtr &getRangeModel     (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setOrientation    ( const UInt32 &value );
     void setUnitIncrement  ( const UInt32 &value );
     void setBlockIncrement ( const UInt32 &value );
     void setVerticalMinButton( const ButtonPtr &value );
     void setVerticalMaxButton( const ButtonPtr &value );
     void setVerticalScrollBar( const ButtonPtr &value );
     void setVerticalScrollField( const ButtonPtr &value );
     void setHorizontalMinButton( const ButtonPtr &value );
     void setHorizontalMaxButton( const ButtonPtr &value );
     void setHorizontalScrollBar( const ButtonPtr &value );
     void setHorizontalScrollField( const ButtonPtr &value );
     void setScrollBarMinLength( const UInt32 &value );
     void setRangeModel     ( const BoundedRangeModelPtr &value );

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

    static  ScrollBarPtr      create          (void); 
    static  ScrollBarPtr      createEmpty     (void); 

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

    SFUInt32            _sfOrientation;
    SFUInt32            _sfUnitIncrement;
    SFUInt32            _sfBlockIncrement;
    SFButtonPtr         _sfVerticalMinButton;
    SFButtonPtr         _sfVerticalMaxButton;
    SFButtonPtr         _sfVerticalScrollBar;
    SFButtonPtr         _sfVerticalScrollField;
    SFButtonPtr         _sfHorizontalMinButton;
    SFButtonPtr         _sfHorizontalMaxButton;
    SFButtonPtr         _sfHorizontalScrollBar;
    SFButtonPtr         _sfHorizontalScrollField;
    SFUInt32            _sfScrollBarMinLength;
    SFBoundedRangeModelPtr   _sfRangeModel;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ScrollBarBase(void);
    ScrollBarBase(const ScrollBarBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ScrollBarBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#if !defined(OSG_FIXED_MFIELDSYNC)
    void executeSyncImpl(      ScrollBarBase *pOther,
                         const BitVector         &whichField);

    virtual void   executeSync(      FieldContainer    &other,
                               const BitVector         &whichField);
#else
    void executeSyncImpl(      ScrollBarBase *pOther,
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
    void operator =(const ScrollBarBase &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


typedef ScrollBarBase *ScrollBarBaseP;

typedef osgIF<ScrollBarBase::isNodeCore,
              CoredNodePtr<ScrollBar>,
              FieldContainer::attempt_to_create_CoredNodePtr_on_non_NodeCore_FC
              >::_IRet ScrollBarNodePtr;

typedef RefPtr<ScrollBarPtr> ScrollBarRefPtr;

OSG_END_NAMESPACE

#define OSGSCROLLBARBASE_HEADER_CVSID "@(#)$Id: FCBaseTemplate_h.h,v 1.40 2005/07/20 00:10:14 vossg Exp $"

#endif /* _OSGSCROLLBARBASE_H_ */
