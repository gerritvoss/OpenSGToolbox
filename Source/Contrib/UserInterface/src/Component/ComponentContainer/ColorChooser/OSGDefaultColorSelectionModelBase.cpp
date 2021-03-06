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
 **     class DefaultColorSelectionModel!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include "OSGConfig.h"




#include "OSGDefaultColorSelectionModelBase.h"
#include "OSGDefaultColorSelectionModel.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::DefaultColorSelectionModel
    A UI DefaultColorSelectionModel.
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Color4f         DefaultColorSelectionModelBase::_sfColor
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<DefaultColorSelectionModel *>::_type("DefaultColorSelectionModelPtr", "ColorSelectionModelPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(DefaultColorSelectionModel *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           DefaultColorSelectionModel *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           DefaultColorSelectionModel *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void DefaultColorSelectionModelBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFColor4f::Description(
        SFColor4f::getClassType(),
        "Color",
        "",
        ColorFieldId, ColorFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DefaultColorSelectionModel::editHandleColor),
        static_cast<FieldGetMethodSig >(&DefaultColorSelectionModel::getHandleColor));

    oType.addInitialDesc(pDesc);
}


DefaultColorSelectionModelBase::TypeObject DefaultColorSelectionModelBase::_type(
    DefaultColorSelectionModelBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&DefaultColorSelectionModelBase::createEmptyLocal),
    DefaultColorSelectionModel::initMethod,
    DefaultColorSelectionModel::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&DefaultColorSelectionModel::classDescInserter),
    false,
    ColorFieldMask,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"DefaultColorSelectionModel\"\n"
    "\tparent=\"ColorSelectionModel\"\n"
    "    library=\"ContribUserInterface\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "\tstructure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "\tdecoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    authors=\"David Kabala (djkabala@gmail.com)                             \"\n"
    ">\n"
    "A UI DefaultColorSelectionModel.\n"
    "\t<Field\n"
    "\t\tname=\"Color\"\n"
    "\t\ttype=\"Color4f\"\n"
    "        category=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"1.0f,1.0f,1.0f,1.0f\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    "A UI DefaultColorSelectionModel.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &DefaultColorSelectionModelBase::getType(void)
{
    return _type;
}

const FieldContainerType &DefaultColorSelectionModelBase::getType(void) const
{
    return _type;
}

UInt32 DefaultColorSelectionModelBase::getContainerSize(void) const
{
    return sizeof(DefaultColorSelectionModel);
}

/*------------------------- decorator get ------------------------------*/


SFColor4f *DefaultColorSelectionModelBase::editSFColor(void)
{
    editSField(ColorFieldMask);

    return &_sfColor;
}

const SFColor4f *DefaultColorSelectionModelBase::getSFColor(void) const
{
    return &_sfColor;
}






/*------------------------------ access -----------------------------------*/

UInt32 DefaultColorSelectionModelBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ColorFieldMask & whichField))
    {
        returnValue += _sfColor.getBinSize();
    }

    return returnValue;
}

void DefaultColorSelectionModelBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ColorFieldMask & whichField))
    {
        _sfColor.copyToBin(pMem);
    }
}

void DefaultColorSelectionModelBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ColorFieldMask & whichField))
    {
        _sfColor.copyFromBin(pMem);
    }
}

//! create a new instance of the class
DefaultColorSelectionModelTransitPtr DefaultColorSelectionModelBase::createLocal(BitVector bFlags)
{
    DefaultColorSelectionModelTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<DefaultColorSelectionModel>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
DefaultColorSelectionModelTransitPtr DefaultColorSelectionModelBase::createDependent(BitVector bFlags)
{
    DefaultColorSelectionModelTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<DefaultColorSelectionModel>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
DefaultColorSelectionModelTransitPtr DefaultColorSelectionModelBase::create(void)
{
    DefaultColorSelectionModelTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<DefaultColorSelectionModel>(tmpPtr);
    }

    return fc;
}

DefaultColorSelectionModel *DefaultColorSelectionModelBase::createEmptyLocal(BitVector bFlags)
{
    DefaultColorSelectionModel *returnValue;

    newPtr<DefaultColorSelectionModel>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
DefaultColorSelectionModel *DefaultColorSelectionModelBase::createEmpty(void)
{
    DefaultColorSelectionModel *returnValue;

    newPtr<DefaultColorSelectionModel>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr DefaultColorSelectionModelBase::shallowCopyLocal(
    BitVector bFlags) const
{
    DefaultColorSelectionModel *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const DefaultColorSelectionModel *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr DefaultColorSelectionModelBase::shallowCopyDependent(
    BitVector bFlags) const
{
    DefaultColorSelectionModel *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const DefaultColorSelectionModel *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr DefaultColorSelectionModelBase::shallowCopy(void) const
{
    DefaultColorSelectionModel *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const DefaultColorSelectionModel *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

DefaultColorSelectionModelBase::DefaultColorSelectionModelBase(void) :
    Inherited(),
    _sfColor                  (Color4f(1.0f,1.0f,1.0f,1.0f))
{
}

DefaultColorSelectionModelBase::DefaultColorSelectionModelBase(const DefaultColorSelectionModelBase &source) :
    Inherited(source),
    _sfColor                  (source._sfColor                  )
{
}


/*-------------------------- destructors ----------------------------------*/

DefaultColorSelectionModelBase::~DefaultColorSelectionModelBase(void)
{
}


GetFieldHandlePtr DefaultColorSelectionModelBase::getHandleColor           (void) const
{
    SFColor4f::GetHandlePtr returnValue(
        new  SFColor4f::GetHandle(
             &_sfColor,
             this->getType().getFieldDesc(ColorFieldId),
             const_cast<DefaultColorSelectionModelBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DefaultColorSelectionModelBase::editHandleColor          (void)
{
    SFColor4f::EditHandlePtr returnValue(
        new  SFColor4f::EditHandle(
             &_sfColor,
             this->getType().getFieldDesc(ColorFieldId),
             this));


    editSField(ColorFieldMask);

    return returnValue;
}



#ifdef OSG_MT_CPTR_ASPECT
void DefaultColorSelectionModelBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    DefaultColorSelectionModel *pThis = static_cast<DefaultColorSelectionModel *>(this);

    pThis->execSync(static_cast<DefaultColorSelectionModel *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *DefaultColorSelectionModelBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    DefaultColorSelectionModel *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const DefaultColorSelectionModel *>(pRefAspect),
                  dynamic_cast<const DefaultColorSelectionModel *>(this));

    return returnValue;
}
#endif

void DefaultColorSelectionModelBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
