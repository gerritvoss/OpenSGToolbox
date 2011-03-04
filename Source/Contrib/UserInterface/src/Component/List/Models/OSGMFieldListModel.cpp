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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGMFieldListModel.h"
#include "OSGPointerMFieldBase.h"
#include "OSGFieldContainerMFieldHandle.h"
#include "OSGFieldContainerFactory.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMFieldListModelBase.cpp file.
// To modify it, please change the .fcd file (OSGMFieldListModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MFieldListModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

UInt32 MFieldListModel::getSize(void) const
{
    //Check for a valid Field Container
    if(getContainer() == NULL)
    {
        SWARNING << "FieldContainer is NULL." << std::endl;
        return 0;
    }

    //Check for valid Field
    GetFieldHandlePtr TheFieldHandle = getContainer()->getField(getFieldId());
    if(!TheFieldHandle->isValid())
    {
        SWARNING << "No Field with Id: " << getFieldId() << " in FieldContainers of type " << getContainer()->getType().getName() << std::endl;
        return 0;
    }

    //Check for valid Field cardinality
    if(TheFieldHandle->getCardinality() != FieldType::MultiField)
    {
        SWARNING << "Field: " << getContainer()->getType().getName() << " is not a MultiField" << std::endl;
        return 0;
    }
    
    return TheFieldHandle->size();
}

boost::any MFieldListModel::getElementAt(UInt32 index) const
{
    //Check for a valid Field Container
    if(getContainer() == NULL)
    {
        SWARNING << "FieldContainer is NULL." << std::endl;
        return boost::any();
    }

    //Check for valid Field
    GetFieldHandlePtr TheFieldHandle = getContainer()->getField(getFieldId());
    if(!TheFieldHandle->isValid())
    {
        SWARNING << "No Field with Id: " << getFieldId() << " in FieldContainers of type " << getContainer()->getType().getName() << std::endl;
        return boost::any();
    }

    //Check for valid Field cardinality
    if(TheFieldHandle->getCardinality() != FieldType::MultiField)
    {
        SWARNING << "Field: " << getContainer()->getType().getName() << " is not a MultiField" << std::endl;
        return boost::any();
    }

    //Check for valid indexing
    if(index >= TheFieldHandle->size())
    {
        SWARNING << "Cannot get value of from index " << index << ", on field " << TheFieldHandle->getDescription()->getName() 
                 << ", on FieldContianer of type " << getContainer()->getType().getName()
                 << " because that field has size " << TheFieldHandle->size() << std::endl;
        return boost::any();
    }
    //std::string Value("");
    //if(TheFieldHandle->isPointerField())
    //{
        //GetMFieldHandle<FieldContainerPtrMFieldBase>* TheHandle(dynamic_cast<GetMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));
        //if(TheHandle->get(index))
        //{
            //Value = boost::lexical_cast<std::string>(TheHandle->get(index)->getId());
        //}
        //else
        //{
            //Value = "NULL";
        //}
    //}
    //else
    //{
        //std::ostringstream StrStream;
        //OutStream TheOutStream(StrStream);

        ////Get the from index value
        //TheFieldHandle->pushIndexedValueToStream(TheOutStream, index);
        //Value = StrStream.str();
    //}

    return boost::any(MFieldIndexed(TheFieldHandle,index));
}

void MFieldListModel::containerChanged(FieldContainer * container, ConstFieldMaskArg whichField)
{
    if(container != getContainer())
    {
        if(container != NULL)
        {
            //Remove callback from container that this model is no longer connected to
            container->subChangedFunctor(boost::bind(&MFieldListModel::containerChanged, this, _1, _2));
        }
        return;
    }

    GetFieldHandlePtr TheFieldHandle = getContainer()->getField(getFieldId());
    if(whichField & TheFieldHandle->getDescription()->getFieldMask())
    {
        produceListDataContentsChanged(this,0,TheFieldHandle->size());
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void MFieldListModel::resolveLinks(void)
{
    if(getContainer())
    {
        getContainer()->subChangedFunctor(boost::bind(&MFieldListModel::containerChanged, this, _1, _2));
    }

    Inherited::resolveLinks();
}

/*----------------------- constructors & destructors ----------------------*/

MFieldListModel::MFieldListModel(void) :
    Inherited()
{
}

MFieldListModel::MFieldListModel(const MFieldListModel &source) :
    Inherited(source)
{
}

MFieldListModel::~MFieldListModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MFieldListModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    //Do not respond to changes that have a Sync origin
    if(origin & ChangedOrigin::Sync)
    {
        return;
    }

    if((whichField & ContainerFieldMask) || (whichField & FieldIdFieldMask))
    {
        //Check for a valid Field Container
        if(getContainer() == NULL)
        {
            SWARNING << "FieldContainer is NULL." << std::endl;
            return;
        }

        //Check for valid Field
        GetFieldHandlePtr TheFieldHandle = getContainer()->getField(getFieldId());
        if(!TheFieldHandle->isValid())
        {
            SWARNING << "No Field with Id: " << getFieldId() << " in FieldContainers of type " << getContainer()->getType().getName() << std::endl;
            return;
        }

        //Check for valid Field cardinality
        if(TheFieldHandle->getCardinality() != FieldType::MultiField)
        {
            SWARNING << "Field: " << getContainer()->getType().getName() << " is not a MultiField" << std::endl;
            return;
        }

        //Attach a callback function to the Container
        getContainer()->addChangedFunctor(boost::bind(&MFieldListModel::containerChanged, this, _1, _2),"");

        produceListDataContentsChanged(this,0,TheFieldHandle->size());
    }
}

void MFieldListModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MFieldListModel NI" << std::endl;
}

OSG_END_NAMESPACE
