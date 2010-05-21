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
 **     class AbstractMutableComboBoxModel!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include "OSGConfig.h"




#include "OSGAbstractMutableComboBoxModelBase.h"
#include "OSGAbstractMutableComboBoxModel.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::AbstractMutableComboBoxModel
    A UI AbstractMutableComboBoxModel.
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<AbstractMutableComboBoxModel *>::_type("AbstractMutableComboBoxModelPtr", "MutableComboBoxModelPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(AbstractMutableComboBoxModel *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           AbstractMutableComboBoxModel *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           AbstractMutableComboBoxModel *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void AbstractMutableComboBoxModelBase::classDescInserter(TypeObject &oType)
{
}


AbstractMutableComboBoxModelBase::TypeObject AbstractMutableComboBoxModelBase::_type(
    AbstractMutableComboBoxModelBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    NULL,
    AbstractMutableComboBoxModel::initMethod,
    AbstractMutableComboBoxModel::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&AbstractMutableComboBoxModel::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"AbstractMutableComboBoxModel\"\n"
    "\tparent=\"MutableComboBoxModel\"\n"
    "    library=\"ContribUserInterface\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "\tstructure=\"abstract\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    authors=\"David Kabala (djkabala@gmail.com)                             \"\n"
    ">\n"
    "A UI AbstractMutableComboBoxModel.\n"
    "</FieldContainer>\n",
    "A UI AbstractMutableComboBoxModel.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &AbstractMutableComboBoxModelBase::getType(void)
{
    return _type;
}

const FieldContainerType &AbstractMutableComboBoxModelBase::getType(void) const
{
    return _type;
}

UInt32 AbstractMutableComboBoxModelBase::getContainerSize(void) const
{
    return sizeof(AbstractMutableComboBoxModel);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

UInt32 AbstractMutableComboBoxModelBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void AbstractMutableComboBoxModelBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void AbstractMutableComboBoxModelBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}




/*------------------------- constructors ----------------------------------*/

AbstractMutableComboBoxModelBase::AbstractMutableComboBoxModelBase(void) :
    Inherited()
{
}

AbstractMutableComboBoxModelBase::AbstractMutableComboBoxModelBase(const AbstractMutableComboBoxModelBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

AbstractMutableComboBoxModelBase::~AbstractMutableComboBoxModelBase(void)
{
}



#ifdef OSG_MT_CPTR_ASPECT
void AbstractMutableComboBoxModelBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    AbstractMutableComboBoxModel *pThis = static_cast<AbstractMutableComboBoxModel *>(this);

    pThis->execSync(static_cast<AbstractMutableComboBoxModel *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif



void AbstractMutableComboBoxModelBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE