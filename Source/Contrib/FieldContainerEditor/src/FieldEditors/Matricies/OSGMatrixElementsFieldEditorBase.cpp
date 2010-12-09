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
 **     class MatrixElementsFieldEditor!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include "OSGConfig.h"




#include "OSGMatrixElementsFieldEditorBase.h"
#include "OSGMatrixElementsFieldEditor.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::MatrixElementsFieldEditor
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<MatrixElementsFieldEditor *>::_type("MatrixElementsFieldEditorPtr", "SingleFieldEditorComponentPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(MatrixElementsFieldEditor *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           MatrixElementsFieldEditor *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           MatrixElementsFieldEditor *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void MatrixElementsFieldEditorBase::classDescInserter(TypeObject &oType)
{
}


MatrixElementsFieldEditorBase::TypeObject MatrixElementsFieldEditorBase::_type(
    MatrixElementsFieldEditorBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&MatrixElementsFieldEditorBase::createEmptyLocal),
    MatrixElementsFieldEditor::initMethod,
    MatrixElementsFieldEditor::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&MatrixElementsFieldEditor::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"MatrixElementsFieldEditor\"\n"
    "\tparent=\"SingleFieldEditorComponent\"\n"
    "    library=\"ContribFieldContainerEditor\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "\tstructure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "\tdecoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    authors=\"David Kabala (djkabala@gmail.com)                             \"\n"
    ">\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &MatrixElementsFieldEditorBase::getType(void)
{
    return _type;
}

const FieldContainerType &MatrixElementsFieldEditorBase::getType(void) const
{
    return _type;
}

UInt32 MatrixElementsFieldEditorBase::getContainerSize(void) const
{
    return sizeof(MatrixElementsFieldEditor);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

UInt32 MatrixElementsFieldEditorBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void MatrixElementsFieldEditorBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void MatrixElementsFieldEditorBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
MatrixElementsFieldEditorTransitPtr MatrixElementsFieldEditorBase::createLocal(BitVector bFlags)
{
    MatrixElementsFieldEditorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<MatrixElementsFieldEditor>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
MatrixElementsFieldEditorTransitPtr MatrixElementsFieldEditorBase::createDependent(BitVector bFlags)
{
    MatrixElementsFieldEditorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<MatrixElementsFieldEditor>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
MatrixElementsFieldEditorTransitPtr MatrixElementsFieldEditorBase::create(void)
{
    MatrixElementsFieldEditorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<MatrixElementsFieldEditor>(tmpPtr);
    }

    return fc;
}

MatrixElementsFieldEditor *MatrixElementsFieldEditorBase::createEmptyLocal(BitVector bFlags)
{
    MatrixElementsFieldEditor *returnValue;

    newPtr<MatrixElementsFieldEditor>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
MatrixElementsFieldEditor *MatrixElementsFieldEditorBase::createEmpty(void)
{
    MatrixElementsFieldEditor *returnValue;

    newPtr<MatrixElementsFieldEditor>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}

FieldContainerTransitPtr MatrixElementsFieldEditorBase::shallowCopyLocal(
    BitVector bFlags) const
{
    MatrixElementsFieldEditor *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const MatrixElementsFieldEditor *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr MatrixElementsFieldEditorBase::shallowCopyDependent(
    BitVector bFlags) const
{
    MatrixElementsFieldEditor *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const MatrixElementsFieldEditor *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr MatrixElementsFieldEditorBase::shallowCopy(void) const
{
    MatrixElementsFieldEditor *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const MatrixElementsFieldEditor *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

MatrixElementsFieldEditorBase::MatrixElementsFieldEditorBase(void) :
    Inherited()
{
}

MatrixElementsFieldEditorBase::MatrixElementsFieldEditorBase(const MatrixElementsFieldEditorBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

MatrixElementsFieldEditorBase::~MatrixElementsFieldEditorBase(void)
{
}




#ifdef OSG_MT_CPTR_ASPECT
void MatrixElementsFieldEditorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    MatrixElementsFieldEditor *pThis = static_cast<MatrixElementsFieldEditor *>(this);

    pThis->execSync(static_cast<MatrixElementsFieldEditor *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *MatrixElementsFieldEditorBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    MatrixElementsFieldEditor *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const MatrixElementsFieldEditor *>(pRefAspect),
                  dynamic_cast<const MatrixElementsFieldEditor *>(this));

    return returnValue;
}
#endif

void MatrixElementsFieldEditorBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE