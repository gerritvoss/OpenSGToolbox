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
 **     class ComboBoxSelectionEventDetails!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include "OSGConfig.h"




#include "OSGComboBoxSelectionEventDetailsBase.h"
#include "OSGComboBoxSelectionEventDetails.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ComboBoxSelectionEventDetails
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Int32           ComboBoxSelectionEventDetailsBase::_sfCurrentIndex
    
*/

/*! \var Int32           ComboBoxSelectionEventDetailsBase::_sfPreviousIndex
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<ComboBoxSelectionEventDetails *>::_type("ComboBoxSelectionEventDetailsPtr", "EventDetailsPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(ComboBoxSelectionEventDetails *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           ComboBoxSelectionEventDetails *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           ComboBoxSelectionEventDetails *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void ComboBoxSelectionEventDetailsBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFInt32::Description(
        SFInt32::getClassType(),
        "CurrentIndex",
        "",
        CurrentIndexFieldId, CurrentIndexFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ComboBoxSelectionEventDetails::editHandleCurrentIndex),
        static_cast<FieldGetMethodSig >(&ComboBoxSelectionEventDetails::getHandleCurrentIndex));

    oType.addInitialDesc(pDesc);

    pDesc = new SFInt32::Description(
        SFInt32::getClassType(),
        "PreviousIndex",
        "",
        PreviousIndexFieldId, PreviousIndexFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&ComboBoxSelectionEventDetails::editHandlePreviousIndex),
        static_cast<FieldGetMethodSig >(&ComboBoxSelectionEventDetails::getHandlePreviousIndex));

    oType.addInitialDesc(pDesc);
}


ComboBoxSelectionEventDetailsBase::TypeObject ComboBoxSelectionEventDetailsBase::_type(
    ComboBoxSelectionEventDetailsBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&ComboBoxSelectionEventDetailsBase::createEmptyLocal),
    ComboBoxSelectionEventDetails::initMethod,
    ComboBoxSelectionEventDetails::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&ComboBoxSelectionEventDetails::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"ComboBoxSelectionEventDetails\"\n"
    "\tparent=\"EventDetails\"\n"
    "    library=\"ContribUserInterface\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "\tstructure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "\tsupportUnregisteredCreate=\"true\"\n"
    "    authors=\"David Kabala (djkabala@gmail.com)                             \"\n"
    ">\n"
    "\t<Field\n"
    "\t\tname=\"CurrentIndex\"\n"
    "\t\ttype=\"Int32\"\n"
    "\t\tcategory=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"protected\"\n"
    "\t\tdefaultValue=\"-1\"\n"
    "        publicRead=\"true\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"PreviousIndex\"\n"
    "\t\ttype=\"Int32\"\n"
    "\t\tcategory=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"protected\"\n"
    "\t\tdefaultValue=\"-1\"\n"
    "        publicRead=\"true\"\n"
    "\t>\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &ComboBoxSelectionEventDetailsBase::getType(void)
{
    return _type;
}

const FieldContainerType &ComboBoxSelectionEventDetailsBase::getType(void) const
{
    return _type;
}

UInt32 ComboBoxSelectionEventDetailsBase::getContainerSize(void) const
{
    return sizeof(ComboBoxSelectionEventDetails);
}

/*------------------------- decorator get ------------------------------*/


SFInt32 *ComboBoxSelectionEventDetailsBase::editSFCurrentIndex(void)
{
    editSField(CurrentIndexFieldMask);

    return &_sfCurrentIndex;
}

const SFInt32 *ComboBoxSelectionEventDetailsBase::getSFCurrentIndex(void) const
{
    return &_sfCurrentIndex;
}


SFInt32 *ComboBoxSelectionEventDetailsBase::editSFPreviousIndex(void)
{
    editSField(PreviousIndexFieldMask);

    return &_sfPreviousIndex;
}

const SFInt32 *ComboBoxSelectionEventDetailsBase::getSFPreviousIndex(void) const
{
    return &_sfPreviousIndex;
}






/*------------------------------ access -----------------------------------*/

UInt32 ComboBoxSelectionEventDetailsBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (CurrentIndexFieldMask & whichField))
    {
        returnValue += _sfCurrentIndex.getBinSize();
    }
    if(FieldBits::NoField != (PreviousIndexFieldMask & whichField))
    {
        returnValue += _sfPreviousIndex.getBinSize();
    }

    return returnValue;
}

void ComboBoxSelectionEventDetailsBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (CurrentIndexFieldMask & whichField))
    {
        _sfCurrentIndex.copyToBin(pMem);
    }
    if(FieldBits::NoField != (PreviousIndexFieldMask & whichField))
    {
        _sfPreviousIndex.copyToBin(pMem);
    }
}

void ComboBoxSelectionEventDetailsBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (CurrentIndexFieldMask & whichField))
    {
        _sfCurrentIndex.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (PreviousIndexFieldMask & whichField))
    {
        _sfPreviousIndex.copyFromBin(pMem);
    }
}

//! create a new instance of the class
ComboBoxSelectionEventDetailsTransitPtr ComboBoxSelectionEventDetailsBase::createLocal(BitVector bFlags)
{
    ComboBoxSelectionEventDetailsTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<ComboBoxSelectionEventDetails>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
ComboBoxSelectionEventDetailsTransitPtr ComboBoxSelectionEventDetailsBase::createDependent(BitVector bFlags)
{
    ComboBoxSelectionEventDetailsTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<ComboBoxSelectionEventDetails>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
ComboBoxSelectionEventDetailsTransitPtr ComboBoxSelectionEventDetailsBase::create(void)
{
    ComboBoxSelectionEventDetailsTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<ComboBoxSelectionEventDetails>(tmpPtr);
    }

    return fc;
}

ComboBoxSelectionEventDetails *ComboBoxSelectionEventDetailsBase::createEmptyLocal(BitVector bFlags)
{
    ComboBoxSelectionEventDetails *returnValue;

    newPtr<ComboBoxSelectionEventDetails>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
ComboBoxSelectionEventDetails *ComboBoxSelectionEventDetailsBase::createEmpty(void)
{
    ComboBoxSelectionEventDetails *returnValue;

    newPtr<ComboBoxSelectionEventDetails>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}

ComboBoxSelectionEventDetails *ComboBoxSelectionEventDetailsBase::createUnregistered(void)
{
    ComboBoxSelectionEventDetails *returnValue = new ComboBoxSelectionEventDetails;

#ifdef OSG_MT_CPTR_ASPECT
    returnValue->setupAspectStore();
#endif
    //Do not register with the FieldContainer Factory

    returnValue->onCreate      (      );
    returnValue->onCreateAspect(returnValue);
    
    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();
    
    return returnValue;
}

FieldContainerTransitPtr ComboBoxSelectionEventDetailsBase::shallowCopyLocal(
    BitVector bFlags) const
{
    ComboBoxSelectionEventDetails *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ComboBoxSelectionEventDetails *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr ComboBoxSelectionEventDetailsBase::shallowCopyDependent(
    BitVector bFlags) const
{
    ComboBoxSelectionEventDetails *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ComboBoxSelectionEventDetails *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr ComboBoxSelectionEventDetailsBase::shallowCopy(void) const
{
    ComboBoxSelectionEventDetails *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const ComboBoxSelectionEventDetails *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

ComboBoxSelectionEventDetailsBase::ComboBoxSelectionEventDetailsBase(void) :
    Inherited(),
    _sfCurrentIndex           (Int32(-1)),
    _sfPreviousIndex          (Int32(-1))
{
}

ComboBoxSelectionEventDetailsBase::ComboBoxSelectionEventDetailsBase(const ComboBoxSelectionEventDetailsBase &source) :
    Inherited(source),
    _sfCurrentIndex           (source._sfCurrentIndex           ),
    _sfPreviousIndex          (source._sfPreviousIndex          )
{
}


/*-------------------------- destructors ----------------------------------*/

ComboBoxSelectionEventDetailsBase::~ComboBoxSelectionEventDetailsBase(void)
{
}


GetFieldHandlePtr ComboBoxSelectionEventDetailsBase::getHandleCurrentIndex    (void) const
{
    SFInt32::GetHandlePtr returnValue(
        new  SFInt32::GetHandle(
             &_sfCurrentIndex,
             this->getType().getFieldDesc(CurrentIndexFieldId),
             const_cast<ComboBoxSelectionEventDetailsBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ComboBoxSelectionEventDetailsBase::editHandleCurrentIndex   (void)
{
    SFInt32::EditHandlePtr returnValue(
        new  SFInt32::EditHandle(
             &_sfCurrentIndex,
             this->getType().getFieldDesc(CurrentIndexFieldId),
             this));


    editSField(CurrentIndexFieldMask);

    return returnValue;
}

GetFieldHandlePtr ComboBoxSelectionEventDetailsBase::getHandlePreviousIndex   (void) const
{
    SFInt32::GetHandlePtr returnValue(
        new  SFInt32::GetHandle(
             &_sfPreviousIndex,
             this->getType().getFieldDesc(PreviousIndexFieldId),
             const_cast<ComboBoxSelectionEventDetailsBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr ComboBoxSelectionEventDetailsBase::editHandlePreviousIndex  (void)
{
    SFInt32::EditHandlePtr returnValue(
        new  SFInt32::EditHandle(
             &_sfPreviousIndex,
             this->getType().getFieldDesc(PreviousIndexFieldId),
             this));


    editSField(PreviousIndexFieldMask);

    return returnValue;
}



#ifdef OSG_MT_CPTR_ASPECT
void ComboBoxSelectionEventDetailsBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    ComboBoxSelectionEventDetails *pThis = static_cast<ComboBoxSelectionEventDetails *>(this);

    pThis->execSync(static_cast<ComboBoxSelectionEventDetails *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *ComboBoxSelectionEventDetailsBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    ComboBoxSelectionEventDetails *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const ComboBoxSelectionEventDetails *>(pRefAspect),
                  dynamic_cast<const ComboBoxSelectionEventDetails *>(this));

    return returnValue;
}
#endif

void ComboBoxSelectionEventDetailsBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE