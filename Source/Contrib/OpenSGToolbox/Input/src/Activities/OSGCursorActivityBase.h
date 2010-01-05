/*---------------------------------------------------------------------------*\
 *                          OpenSG ToolBox Input                             *
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
 **     class CursorActivity
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGCURSORACTIVITYBASE_H_
#define _OSGCURSORACTIVITYBASE_H_
#ifdef __sgi
#pragma once
#endif


#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGRefPtr.h>
#include <OpenSG/OSGCoredNodePtr.h>

#include <OpenSG/Toolbox/OSGActivity.h> // Parent

#include "WindowSystem/OSGWindowEventProducerFields.h" // WindowEventProducer type
#include <OpenSG/OSGUInt8Fields.h> // ActivityType type
#include <OpenSG/OSGUInt8Fields.h> // CursorType type

#include "OSGCursorActivityFields.h"
OSG_BEGIN_NAMESPACE

class CursorActivity;
class BinaryDataHandler;

//! \brief CursorActivity Base Class.

class OSG_INPUTLIB_DLLMAPPING CursorActivityBase : public Activity
{
  private:

    typedef Activity    Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    typedef CursorActivityPtr  Ptr;

    enum
    {
        WindowEventProducerFieldId = Inherited::NextFieldId,
        ActivityTypeFieldId        = WindowEventProducerFieldId + 1,
        CursorTypeFieldId          = ActivityTypeFieldId        + 1,
        NextFieldId                = CursorTypeFieldId          + 1
    };

    static const OSG::BitVector WindowEventProducerFieldMask;
    static const OSG::BitVector ActivityTypeFieldMask;
    static const OSG::BitVector CursorTypeFieldMask;


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


           SFWindowEventProducerPtr *editSFWindowEventProducer(void);
     const SFWindowEventProducerPtr *getSFWindowEventProducer(void) const;

           SFUInt8             *editSFActivityType   (void);
     const SFUInt8             *getSFActivityType   (void) const;

           SFUInt8             *editSFCursorType     (void);
     const SFUInt8             *getSFCursorType     (void) const;


           WindowEventProducerPtr &editWindowEventProducer(void);
     const WindowEventProducerPtr &getWindowEventProducer(void) const;

           UInt8               &editActivityType   (void);
     const UInt8               &getActivityType   (void) const;

           UInt8               &editCursorType     (void);
     const UInt8               &getCursorType     (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setWindowEventProducer( const WindowEventProducerPtr &value );
     void setActivityType   ( const UInt8 &value );
     void setCursorType     ( const UInt8 &value );

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

    static  CursorActivityPtr      create          (void); 
    static  CursorActivityPtr      createEmpty     (void); 

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

    SFWindowEventProducerPtr   _sfWindowEventProducer;
    SFUInt8             _sfActivityType;
    SFUInt8             _sfCursorType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    CursorActivityBase(void);
    CursorActivityBase(const CursorActivityBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CursorActivityBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#if !defined(OSG_FIXED_MFIELDSYNC)
    void executeSyncImpl(      CursorActivityBase *pOther,
                         const BitVector         &whichField);

    virtual void   executeSync(      FieldContainer    &other,
                               const BitVector         &whichField);
#else
    void executeSyncImpl(      CursorActivityBase *pOther,
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
    void operator =(const CursorActivityBase &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


typedef CursorActivityBase *CursorActivityBaseP;

typedef osgIF<CursorActivityBase::isNodeCore,
              CoredNodePtr<CursorActivity>,
              FieldContainer::attempt_to_create_CoredNodePtr_on_non_NodeCore_FC
              >::_IRet CursorActivityNodePtr;

typedef RefPtr<CursorActivityPtr> CursorActivityRefPtr;

OSG_END_NAMESPACE

#endif /* _OSGCURSORACTIVITYBASE_H_ */