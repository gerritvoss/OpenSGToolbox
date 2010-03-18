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
 **     class TableModelEvent!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include "OSGConfig.h"




#include "OSGTableModelEventBase.h"
#include "OSGTableModelEvent.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::TableModelEvent
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var UInt32          TableModelEventBase::_sfFirstColumn
    
*/

/*! \var UInt32          TableModelEventBase::_sfLastColumn
    
*/

/*! \var UInt32          TableModelEventBase::_sfFirstRow
    
*/

/*! \var UInt32          TableModelEventBase::_sfLastRow
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<TableModelEvent *>::_type("TableModelEventPtr", "EventPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(TableModelEvent *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           TableModelEvent *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           TableModelEvent *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void TableModelEventBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "FirstColumn",
        "",
        FirstColumnFieldId, FirstColumnFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&TableModelEvent::editHandleFirstColumn),
        static_cast<FieldGetMethodSig >(&TableModelEvent::getHandleFirstColumn));

    oType.addInitialDesc(pDesc);


    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "LastColumn",
        "",
        LastColumnFieldId, LastColumnFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&TableModelEvent::editHandleLastColumn),
        static_cast<FieldGetMethodSig >(&TableModelEvent::getHandleLastColumn));

    oType.addInitialDesc(pDesc);


    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "FirstRow",
        "",
        FirstRowFieldId, FirstRowFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&TableModelEvent::editHandleFirstRow),
        static_cast<FieldGetMethodSig >(&TableModelEvent::getHandleFirstRow));

    oType.addInitialDesc(pDesc);


    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "LastRow",
        "",
        LastRowFieldId, LastRowFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&TableModelEvent::editHandleLastRow),
        static_cast<FieldGetMethodSig >(&TableModelEvent::getHandleLastRow));

    oType.addInitialDesc(pDesc);

}


TableModelEventBase::TypeObject TableModelEventBase::_type(
    TableModelEventBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&TableModelEventBase::createEmptyLocal),
    TableModelEvent::initMethod,
    TableModelEvent::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&TableModelEvent::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"TableModelEvent\"\n"
    "\tparent=\"Event\"\n"
    "    library=\"ContribUserInterface\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    authors=\"David Kabala (djkabala@gmail.com)                             \"\n"
    ">\n"
    "\t<Field\n"
    "\t\tname=\"FirstColumn\"\n"
    "\t\ttype=\"UInt32\"\n"
    "        category=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"protected\"\n"
    "\t\tdefaultValue=\"0\"\n"
    "        publicRead=\"true\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"LastColumn\"\n"
    "\t\ttype=\"UInt32\"\n"
    "        category=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"protected\"\n"
    "\t\tdefaultValue=\"0\"\n"
    "        publicRead=\"true\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"FirstRow\"\n"
    "\t\ttype=\"UInt32\"\n"
    "        category=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"protected\"\n"
    "\t\tdefaultValue=\"0\"\n"
    "        publicRead=\"true\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"LastRow\"\n"
    "\t\ttype=\"UInt32\"\n"
    "        category=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"protected\"\n"
    "\t\tdefaultValue=\"0\"\n"
    "        publicRead=\"true\"\n"
    "\t>\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    ""
    );


/*------------------------------ get -----------------------------------*/

FieldContainerType &TableModelEventBase::getType(void)
{
    return _type;
}

const FieldContainerType &TableModelEventBase::getType(void) const
{
    return _type;
}

UInt32 TableModelEventBase::getContainerSize(void) const
{
    return sizeof(TableModelEvent);
}

/*------------------------- decorator get ------------------------------*/


SFUInt32 *TableModelEventBase::editSFFirstColumn(void)
{
    editSField(FirstColumnFieldMask);

    return &_sfFirstColumn;
}

const SFUInt32 *TableModelEventBase::getSFFirstColumn(void) const
{
    return &_sfFirstColumn;
}


SFUInt32 *TableModelEventBase::editSFLastColumn(void)
{
    editSField(LastColumnFieldMask);

    return &_sfLastColumn;
}

const SFUInt32 *TableModelEventBase::getSFLastColumn(void) const
{
    return &_sfLastColumn;
}


SFUInt32 *TableModelEventBase::editSFFirstRow(void)
{
    editSField(FirstRowFieldMask);

    return &_sfFirstRow;
}

const SFUInt32 *TableModelEventBase::getSFFirstRow(void) const
{
    return &_sfFirstRow;
}


SFUInt32 *TableModelEventBase::editSFLastRow(void)
{
    editSField(LastRowFieldMask);

    return &_sfLastRow;
}

const SFUInt32 *TableModelEventBase::getSFLastRow(void) const
{
    return &_sfLastRow;
}






/*------------------------------ access -----------------------------------*/

UInt32 TableModelEventBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (FirstColumnFieldMask & whichField))
    {
        returnValue += _sfFirstColumn.getBinSize();
    }
    if(FieldBits::NoField != (LastColumnFieldMask & whichField))
    {
        returnValue += _sfLastColumn.getBinSize();
    }
    if(FieldBits::NoField != (FirstRowFieldMask & whichField))
    {
        returnValue += _sfFirstRow.getBinSize();
    }
    if(FieldBits::NoField != (LastRowFieldMask & whichField))
    {
        returnValue += _sfLastRow.getBinSize();
    }

    return returnValue;
}

void TableModelEventBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (FirstColumnFieldMask & whichField))
    {
        _sfFirstColumn.copyToBin(pMem);
    }
    if(FieldBits::NoField != (LastColumnFieldMask & whichField))
    {
        _sfLastColumn.copyToBin(pMem);
    }
    if(FieldBits::NoField != (FirstRowFieldMask & whichField))
    {
        _sfFirstRow.copyToBin(pMem);
    }
    if(FieldBits::NoField != (LastRowFieldMask & whichField))
    {
        _sfLastRow.copyToBin(pMem);
    }
}

void TableModelEventBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (FirstColumnFieldMask & whichField))
    {
        _sfFirstColumn.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (LastColumnFieldMask & whichField))
    {
        _sfLastColumn.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (FirstRowFieldMask & whichField))
    {
        _sfFirstRow.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (LastRowFieldMask & whichField))
    {
        _sfLastRow.copyFromBin(pMem);
    }
}

//! create a new instance of the class
TableModelEventTransitPtr TableModelEventBase::createLocal(BitVector bFlags)
{
    TableModelEventTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<TableModelEvent>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
TableModelEventTransitPtr TableModelEventBase::createDependent(BitVector bFlags)
{
    TableModelEventTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<TableModelEvent>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
TableModelEventTransitPtr TableModelEventBase::create(void)
{
    TableModelEventTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<TableModelEvent>(tmpPtr);
    }

    return fc;
}

TableModelEvent *TableModelEventBase::createEmptyLocal(BitVector bFlags)
{
    TableModelEvent *returnValue;

    newPtr<TableModelEvent>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
TableModelEvent *TableModelEventBase::createEmpty(void)
{
    TableModelEvent *returnValue;

    newPtr<TableModelEvent>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr TableModelEventBase::shallowCopyLocal(
    BitVector bFlags) const
{
    TableModelEvent *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const TableModelEvent *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr TableModelEventBase::shallowCopyDependent(
    BitVector bFlags) const
{
    TableModelEvent *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const TableModelEvent *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr TableModelEventBase::shallowCopy(void) const
{
    TableModelEvent *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const TableModelEvent *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

TableModelEventBase::TableModelEventBase(void) :
    Inherited(),
    _sfFirstColumn            (UInt32(0)),
    _sfLastColumn             (UInt32(0)),
    _sfFirstRow               (UInt32(0)),
    _sfLastRow                (UInt32(0))
{
}

TableModelEventBase::TableModelEventBase(const TableModelEventBase &source) :
    Inherited(source),
    _sfFirstColumn            (source._sfFirstColumn            ),
    _sfLastColumn             (source._sfLastColumn             ),
    _sfFirstRow               (source._sfFirstRow               ),
    _sfLastRow                (source._sfLastRow                )
{
}


/*-------------------------- destructors ----------------------------------*/

TableModelEventBase::~TableModelEventBase(void)
{
}


GetFieldHandlePtr TableModelEventBase::getHandleFirstColumn     (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfFirstColumn,
             this->getType().getFieldDesc(FirstColumnFieldId),
             const_cast<TableModelEventBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr TableModelEventBase::editHandleFirstColumn    (void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfFirstColumn,
             this->getType().getFieldDesc(FirstColumnFieldId),
             this));


    editSField(FirstColumnFieldMask);

    return returnValue;
}

GetFieldHandlePtr TableModelEventBase::getHandleLastColumn      (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfLastColumn,
             this->getType().getFieldDesc(LastColumnFieldId),
             const_cast<TableModelEventBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr TableModelEventBase::editHandleLastColumn     (void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfLastColumn,
             this->getType().getFieldDesc(LastColumnFieldId),
             this));


    editSField(LastColumnFieldMask);

    return returnValue;
}

GetFieldHandlePtr TableModelEventBase::getHandleFirstRow        (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfFirstRow,
             this->getType().getFieldDesc(FirstRowFieldId),
             const_cast<TableModelEventBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr TableModelEventBase::editHandleFirstRow       (void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfFirstRow,
             this->getType().getFieldDesc(FirstRowFieldId),
             this));


    editSField(FirstRowFieldMask);

    return returnValue;
}

GetFieldHandlePtr TableModelEventBase::getHandleLastRow         (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfLastRow,
             this->getType().getFieldDesc(LastRowFieldId),
             const_cast<TableModelEventBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr TableModelEventBase::editHandleLastRow        (void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfLastRow,
             this->getType().getFieldDesc(LastRowFieldId),
             this));


    editSField(LastRowFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void TableModelEventBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    TableModelEvent *pThis = static_cast<TableModelEvent *>(this);

    pThis->execSync(static_cast<TableModelEvent *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *TableModelEventBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    TableModelEvent *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const TableModelEvent *>(pRefAspect),
                  dynamic_cast<const TableModelEvent *>(this));

    return returnValue;
}
#endif

void TableModelEventBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
