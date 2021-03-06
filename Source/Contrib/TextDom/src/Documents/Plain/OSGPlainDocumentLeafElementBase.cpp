/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: Achyuthan Vasanth (vasanth.achyuthan@gmail.com)                  *
 *          David Kabala (djkabala@gmail.com)                                *
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
 **     class PlainDocumentLeafElement!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include "OSGConfig.h"




#include "OSGPlainDocumentLeafElementBase.h"
#include "OSGPlainDocumentLeafElement.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::PlainDocumentLeafElement
    Plain Document Leaf Element
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<PlainDocumentLeafElement *>::_type("PlainDocumentLeafElementPtr", "AbstractLeafElementPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(PlainDocumentLeafElement *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           PlainDocumentLeafElement *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           PlainDocumentLeafElement *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void PlainDocumentLeafElementBase::classDescInserter(TypeObject &oType)
{
}


PlainDocumentLeafElementBase::TypeObject PlainDocumentLeafElementBase::_type(
    PlainDocumentLeafElementBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&PlainDocumentLeafElementBase::createEmptyLocal),
    PlainDocumentLeafElement::initMethod,
    PlainDocumentLeafElement::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&PlainDocumentLeafElement::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"PlainDocumentLeafElement\"\n"
    "\tparent=\"AbstractLeafElement\"\n"
    "    library=\"ContribTextDom\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "\tstructure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"false\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    authors=\"Achyuthan Vasanth (vasanth.achyuthan@gmail.com), David Kabala (djkabala@gmail.com)\"\n"
    ">\n"
    "Plain Document Leaf Element\n"
    "</FieldContainer>\n"
    "\n"
    "\n",
    "Plain Document Leaf Element\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &PlainDocumentLeafElementBase::getType(void)
{
    return _type;
}

const FieldContainerType &PlainDocumentLeafElementBase::getType(void) const
{
    return _type;
}

UInt32 PlainDocumentLeafElementBase::getContainerSize(void) const
{
    return sizeof(PlainDocumentLeafElement);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

UInt32 PlainDocumentLeafElementBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void PlainDocumentLeafElementBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void PlainDocumentLeafElementBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
PlainDocumentLeafElementTransitPtr PlainDocumentLeafElementBase::createLocal(BitVector bFlags)
{
    PlainDocumentLeafElementTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<PlainDocumentLeafElement>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
PlainDocumentLeafElementTransitPtr PlainDocumentLeafElementBase::createDependent(BitVector bFlags)
{
    PlainDocumentLeafElementTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<PlainDocumentLeafElement>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
PlainDocumentLeafElementTransitPtr PlainDocumentLeafElementBase::create(void)
{
    PlainDocumentLeafElementTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<PlainDocumentLeafElement>(tmpPtr);
    }

    return fc;
}

PlainDocumentLeafElement *PlainDocumentLeafElementBase::createEmptyLocal(BitVector bFlags)
{
    PlainDocumentLeafElement *returnValue;

    newPtr<PlainDocumentLeafElement>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
PlainDocumentLeafElement *PlainDocumentLeafElementBase::createEmpty(void)
{
    PlainDocumentLeafElement *returnValue;

    newPtr<PlainDocumentLeafElement>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}

FieldContainerTransitPtr PlainDocumentLeafElementBase::shallowCopyLocal(
    BitVector bFlags) const
{
    PlainDocumentLeafElement *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const PlainDocumentLeafElement *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr PlainDocumentLeafElementBase::shallowCopyDependent(
    BitVector bFlags) const
{
    PlainDocumentLeafElement *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const PlainDocumentLeafElement *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr PlainDocumentLeafElementBase::shallowCopy(void) const
{
    PlainDocumentLeafElement *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const PlainDocumentLeafElement *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

PlainDocumentLeafElementBase::PlainDocumentLeafElementBase(void) :
    Inherited()
{
}

PlainDocumentLeafElementBase::PlainDocumentLeafElementBase(const PlainDocumentLeafElementBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

PlainDocumentLeafElementBase::~PlainDocumentLeafElementBase(void)
{
}




#ifdef OSG_MT_CPTR_ASPECT
void PlainDocumentLeafElementBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    PlainDocumentLeafElement *pThis = static_cast<PlainDocumentLeafElement *>(this);

    pThis->execSync(static_cast<PlainDocumentLeafElement *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *PlainDocumentLeafElementBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    PlainDocumentLeafElement *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const PlainDocumentLeafElement *>(pRefAspect),
                  dynamic_cast<const PlainDocumentLeafElement *>(this));

    return returnValue;
}
#endif

void PlainDocumentLeafElementBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
