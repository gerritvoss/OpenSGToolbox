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
 **     class AbstractLeafElement!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include "OSGConfig.h"




#include "OSGAbstractLeafElementBase.h"
#include "OSGAbstractLeafElement.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::AbstractLeafElement
    Document Element
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<AbstractLeafElement *>::_type("AbstractLeafElementPtr", "AbstractElementPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(AbstractLeafElement *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           AbstractLeafElement *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           AbstractLeafElement *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void AbstractLeafElementBase::classDescInserter(TypeObject &oType)
{
}


AbstractLeafElementBase::TypeObject AbstractLeafElementBase::_type(
    AbstractLeafElementBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    NULL,
    AbstractLeafElement::initMethod,
    AbstractLeafElement::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&AbstractLeafElement::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"AbstractLeafElement\"\n"
    "\tparent=\"AbstractElement\"\n"
    "    library=\"ContribTextDom\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "\tstructure=\"abstract\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    authors=\"David Kabala (djkabala@gmail.com)                             \"\n"
    ">\n"
    "Document Element\n"
    "</FieldContainer>\n",
    "Document Element\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &AbstractLeafElementBase::getType(void)
{
    return _type;
}

const FieldContainerType &AbstractLeafElementBase::getType(void) const
{
    return _type;
}

UInt32 AbstractLeafElementBase::getContainerSize(void) const
{
    return sizeof(AbstractLeafElement);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

UInt32 AbstractLeafElementBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void AbstractLeafElementBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void AbstractLeafElementBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}




/*------------------------- constructors ----------------------------------*/

AbstractLeafElementBase::AbstractLeafElementBase(void) :
    Inherited()
{
}

AbstractLeafElementBase::AbstractLeafElementBase(const AbstractLeafElementBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

AbstractLeafElementBase::~AbstractLeafElementBase(void)
{
}



#ifdef OSG_MT_CPTR_ASPECT
void AbstractLeafElementBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    AbstractLeafElement *pThis = static_cast<AbstractLeafElement *>(this);

    pThis->execSync(static_cast<AbstractLeafElement *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif



void AbstractLeafElementBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE