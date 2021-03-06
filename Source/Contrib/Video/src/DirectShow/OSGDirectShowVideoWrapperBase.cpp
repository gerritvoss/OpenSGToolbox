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
 **     class DirectShowVideoWrapper!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include "OSGConfig.h"




#include "OSGDirectShowVideoWrapperBase.h"
#include "OSGDirectShowVideoWrapper.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::DirectShowVideoWrapper
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<DirectShowVideoWrapper *>::_type("DirectShowVideoWrapperPtr", "VideoWrapperPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(DirectShowVideoWrapper *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           DirectShowVideoWrapper *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           DirectShowVideoWrapper *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void DirectShowVideoWrapperBase::classDescInserter(TypeObject &oType)
{
}


DirectShowVideoWrapperBase::TypeObject DirectShowVideoWrapperBase::_type(
    DirectShowVideoWrapperBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&DirectShowVideoWrapperBase::createEmptyLocal),
    DirectShowVideoWrapper::initMethod,
    DirectShowVideoWrapper::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&DirectShowVideoWrapper::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"DirectShowVideoWrapper\"\n"
    "\tparent=\"VideoWrapper\"\n"
    "\tlibrary=\"ContribVideo\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    authors=\"David Kabala (djkabala@gmail.com)                             \"\n"
    ">\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &DirectShowVideoWrapperBase::getType(void)
{
    return _type;
}

const FieldContainerType &DirectShowVideoWrapperBase::getType(void) const
{
    return _type;
}

UInt32 DirectShowVideoWrapperBase::getContainerSize(void) const
{
    return sizeof(DirectShowVideoWrapper);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

UInt32 DirectShowVideoWrapperBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void DirectShowVideoWrapperBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void DirectShowVideoWrapperBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
DirectShowVideoWrapperTransitPtr DirectShowVideoWrapperBase::createLocal(BitVector bFlags)
{
    DirectShowVideoWrapperTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<DirectShowVideoWrapper>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
DirectShowVideoWrapperTransitPtr DirectShowVideoWrapperBase::createDependent(BitVector bFlags)
{
    DirectShowVideoWrapperTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<DirectShowVideoWrapper>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
DirectShowVideoWrapperTransitPtr DirectShowVideoWrapperBase::create(void)
{
    DirectShowVideoWrapperTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<DirectShowVideoWrapper>(tmpPtr);
    }

    return fc;
}

DirectShowVideoWrapper *DirectShowVideoWrapperBase::createEmptyLocal(BitVector bFlags)
{
    DirectShowVideoWrapper *returnValue;

    newPtr<DirectShowVideoWrapper>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
DirectShowVideoWrapper *DirectShowVideoWrapperBase::createEmpty(void)
{
    DirectShowVideoWrapper *returnValue;

    newPtr<DirectShowVideoWrapper>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}

FieldContainerTransitPtr DirectShowVideoWrapperBase::shallowCopyLocal(
    BitVector bFlags) const
{
    DirectShowVideoWrapper *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const DirectShowVideoWrapper *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr DirectShowVideoWrapperBase::shallowCopyDependent(
    BitVector bFlags) const
{
    DirectShowVideoWrapper *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const DirectShowVideoWrapper *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr DirectShowVideoWrapperBase::shallowCopy(void) const
{
    DirectShowVideoWrapper *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const DirectShowVideoWrapper *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

DirectShowVideoWrapperBase::DirectShowVideoWrapperBase(void) :
    Inherited()
{
}

DirectShowVideoWrapperBase::DirectShowVideoWrapperBase(const DirectShowVideoWrapperBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

DirectShowVideoWrapperBase::~DirectShowVideoWrapperBase(void)
{
}




#ifdef OSG_MT_CPTR_ASPECT
void DirectShowVideoWrapperBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    DirectShowVideoWrapper *pThis = static_cast<DirectShowVideoWrapper *>(this);

    pThis->execSync(static_cast<DirectShowVideoWrapper *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *DirectShowVideoWrapperBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    DirectShowVideoWrapper *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const DirectShowVideoWrapper *>(pRefAspect),
                  dynamic_cast<const DirectShowVideoWrapper *>(this));

    return returnValue;
}
#endif

void DirectShowVideoWrapperBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
