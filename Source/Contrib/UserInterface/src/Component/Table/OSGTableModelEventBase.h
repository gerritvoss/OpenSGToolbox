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
 **     class TableModelEvent
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGTABLEMODELEVENTBASE_H_
#define _OSGTABLEMODELEVENTBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

//#include "OSGBaseTypes.h"

#include "OSGEvent.h" // Parent

#include "OSGSysFields.h"               // FirstColumn type

#include "OSGTableModelEventFields.h"

OSG_BEGIN_NAMESPACE

class TableModelEvent;

//! \brief TableModelEvent Base Class.

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TableModelEventBase : public Event
{
  public:

    typedef Event Inherited;
    typedef Event ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(TableModelEvent);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        FirstColumnFieldId = Inherited::NextFieldId,
        LastColumnFieldId = FirstColumnFieldId + 1,
        FirstRowFieldId = LastColumnFieldId + 1,
        LastRowFieldId = FirstRowFieldId + 1,
        NextFieldId = LastRowFieldId + 1
    };

    static const OSG::BitVector FirstColumnFieldMask =
        (TypeTraits<BitVector>::One << FirstColumnFieldId);
    static const OSG::BitVector LastColumnFieldMask =
        (TypeTraits<BitVector>::One << LastColumnFieldId);
    static const OSG::BitVector FirstRowFieldMask =
        (TypeTraits<BitVector>::One << FirstRowFieldId);
    static const OSG::BitVector LastRowFieldMask =
        (TypeTraits<BitVector>::One << LastRowFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef SFUInt32          SFFirstColumnType;
    typedef SFUInt32          SFLastColumnType;
    typedef SFUInt32          SFFirstRowType;
    typedef SFUInt32          SFLastRowType;

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


            const SFUInt32            *getSFFirstColumn     (void) const;

            const SFUInt32            *getSFLastColumn      (void) const;

            const SFUInt32            *getSFFirstRow        (void) const;

            const SFUInt32            *getSFLastRow         (void) const;


                  UInt32               getFirstColumn     (void) const;

                  UInt32               getLastColumn      (void) const;

                  UInt32               getFirstRow        (void) const;

                  UInt32               getLastRow         (void) const;

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

    static  TableModelEventTransitPtr  create          (void);
    static  TableModelEvent           *createEmpty     (void);

    static  TableModelEventTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  TableModelEvent            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  TableModelEventTransitPtr  createDependent  (BitVector bFlags);

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

    SFUInt32          _sfFirstColumn;
    SFUInt32          _sfLastColumn;
    SFUInt32          _sfFirstRow;
    SFUInt32          _sfLastRow;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TableModelEventBase(void);
    TableModelEventBase(const TableModelEventBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TableModelEventBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleFirstColumn     (void) const;
    EditFieldHandlePtr editHandleFirstColumn    (void);
    GetFieldHandlePtr  getHandleLastColumn      (void) const;
    EditFieldHandlePtr editHandleLastColumn     (void);
    GetFieldHandlePtr  getHandleFirstRow        (void) const;
    EditFieldHandlePtr editHandleFirstRow       (void);
    GetFieldHandlePtr  getHandleLastRow         (void) const;
    EditFieldHandlePtr editHandleLastRow        (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */


                  SFUInt32            *editSFFirstColumn    (void);

                  SFUInt32            *editSFLastColumn     (void);

                  SFUInt32            *editSFFirstRow       (void);

                  SFUInt32            *editSFLastRow        (void);


                  UInt32              &editFirstColumn    (void);

                  UInt32              &editLastColumn     (void);

                  UInt32              &editFirstRow       (void);

                  UInt32              &editLastRow        (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setFirstColumn    (const UInt32 value);
            void setLastColumn     (const UInt32 value);
            void setFirstRow       (const UInt32 value);
            void setLastRow        (const UInt32 value);

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

            void execSync (      TableModelEventBase *pFrom,
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
    void operator =(const TableModelEventBase &source);
};

typedef TableModelEventBase *TableModelEventBaseP;

OSG_END_NAMESPACE

#endif /* _OSGTABLEMODELEVENTBASE_H_ */
