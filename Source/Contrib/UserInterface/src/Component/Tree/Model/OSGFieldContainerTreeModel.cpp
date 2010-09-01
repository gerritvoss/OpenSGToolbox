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

#include "OSGFieldContainerTreeModel.h"
#include "OSGTreePath.h"
#include "OSGPointerSFieldBase.h"
#include "OSGFieldContainerSFieldHandle.h"
#include "OSGPointerMFieldBase.h"
#include "OSGFieldContainerMFieldHandle.h"
#include "OSGAttachmentMapFieldTraits.h"
#include "OSGChangedFunctorFieldTraits.h"

#include "OSGAttachmentMapSFields.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFieldContainerTreeModelBase.cpp file.
// To modify it, please change the .fcd file (OSGFieldContainerTreeModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FieldContainerTreeModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

boost::any FieldContainerTreeModel::getChild(const boost::any& parent, const UInt32& index) const
{
    try
    {
	    ContainerFieldIdPair ThePair = boost::any_cast<ContainerFieldIdPair>(parent);

        //FieldContainer
        if(ThePair._FieldID == FIELD_CONTAINER_ID)
        {
            UInt32 FieldId(1);
            UInt32 NumFields(0);
            for( ; FieldId<=ThePair._Container->getNumFields() ; ++FieldId)
            {
                if(isFieldAllowed(ThePair._Container->getFieldDescription(FieldId)))
                {
                    ++NumFields;
                    if(NumFields == index+1)
                    {
                        break;
                    }
                }
            }

            ContainerFieldIdPair ChildPair(ThePair._Container,FieldId);
            return boost::any(ChildPair);
        }
        //Field
        else
        {
            const FieldType& fcType(ThePair._Container->getFieldDescription(ThePair._FieldID)->getFieldType());
           
            if((fcType.getClass() == FieldType::PtrField      ) ||
               (fcType.getClass() == FieldType::ParentPtrField) ||
               (fcType.getClass() == FieldType::ChildPtrField ))
            {
                if(fcType.getCardinality() == FieldType::MultiField )
                {
                    if(index < ThePair._Container->getField(ThePair._FieldID)->size())
                    {
                        GetFieldHandlePtr TempHandle(ThePair._Container->getField(ThePair._FieldID));
                        FieldContainer* TheContainer = dynamic_cast<GetMFieldHandle<FieldContainerPtrMFieldBase>*>(TempHandle.get())->get(index);

                        return boost::any(ContainerFieldIdPair(TheContainer,FIELD_CONTAINER_ID));
                    }
                    else
                    {
                        SWARNING << "Index out of bounds." << std::endl;
                        return boost::any();
                    }
                }
                else
                {
                    if(index == 0)
                    {
                        GetFieldHandlePtr TempHandle(ThePair._Container->getField(ThePair._FieldID));
                        FieldContainer* TheContainer = dynamic_cast<GetSFieldHandle<FieldContainerPtrSFieldBase>*>(TempHandle.get())->get();

                        return boost::any(ContainerFieldIdPair(TheContainer,FIELD_CONTAINER_ID));
                    }
                    else
                    {
                        SWARNING << "Index out of bounds." << std::endl;
                        return boost::any();
                    }
                }
            }
            else if(fcType.getContentType() == FieldTraits<AttachmentMap>::getType())
            {
                //Attachment Map
                if(index < static_cast<const SFAttachmentPtrMap*>(ThePair._Container->getField(ThePair._FieldID).get()->getField())->getValue().size())
                {
                    GetMapFieldHandle::ContainerList TheContainerList;
                    static_cast<GetSFieldHandle<SFAttachmentPtrMap>*>(ThePair._Container->getField(ThePair._FieldID).get())->flatten(TheContainerList);
                    return boost::any(ContainerFieldIdPair(TheContainerList[index],FIELD_CONTAINER_ID));
                }
                else
                {
                    SWARNING << "Index out of bounds." << std::endl;
                    return boost::any();
                }
                return boost::any();
            }
            else
            {
                SWARNING << "Not Valid field." << std::endl;
                return boost::any();
            }
        }
    }
    catch(const boost::bad_any_cast &ex)
    {
        SWARNING << "Bad any cast" << ex.what() << "." << std::endl;
        return boost::any();
    }
}

bool FieldContainerTreeModel::isFieldAllowed(const FieldDescriptionBase* fieldDesc) const
{
    const FieldType&       fcType(fieldDesc->getFieldType());
    FieldType::Cardinality fieldCardinality(fcType.getCardinality());
    FieldType::Class       fieldClass(fcType.getClass());
    const DataType&        contentType(fcType.getContentType());

    if( (!getShowInternalFields()    && fieldDesc->isInternal() ) ||
        
        
        (!getShowMultiFields ()    && fieldCardinality == FieldType::MultiField ) ||
        (!getShowSingleFields()    && fieldCardinality == FieldType::SingleField) ||

        (!getShowDataFields()      && fieldClass == FieldType::ValueField
         && 
         (!getShowAttachments() ||
          (getShowAttachments() && contentType != FieldTraits<AttachmentMap>::getType()))) ||
                                 
        (!getShowAttachments()  && contentType == FieldTraits<AttachmentMap>::getType())      ||

        (!getShowParentPtrFields() && fieldClass == FieldType::ParentPtrField   ) ||

        (!getShowChildPtrFields()  && fieldClass == FieldType::ChildPtrField    ) ||
        
        (!getShowPtrFields() && (fieldClass == FieldType::ParentPtrField ||
                                 fieldClass == FieldType::ChildPtrField  ||
                                 fieldClass == FieldType::PtrField         )    ) ||
                        
        //(!getShowEventProducers()  && contentType == FieldTraits<EventProducerPtr>::getType())      ||
                                 
        (!getShowCallbackFunctors()  && contentType == FieldTraits<ChangedFunctorCallback>::getType())
      )
    {
        return false;
    }

    return true;
}

UInt32 FieldContainerTreeModel::getIndexFromFieldId(const FieldContainer* container, UInt32 fieldId) const
{
    UInt32 index(0);
    for(UInt32 i(1) ; i<=fieldId ; ++i)
    {
        if(isFieldAllowed(container->getFieldDescription(i)))
        {
            ++index;
        }
    }
    return index;
}

UInt32 FieldContainerTreeModel::getChildCount(const boost::any& parent) const
{
    try
    {
	    ContainerFieldIdPair ThePair = boost::any_cast<ContainerFieldIdPair>(parent);

        //FieldContainer
        if(ThePair._FieldID == FIELD_CONTAINER_ID)
        {
            if(ThePair._Container != NULL)
            {
                UInt32 NumFields(0);
                for(UInt32 i(1) ; i<=ThePair._Container->getNumFields() ; ++i)
                {
                    if(isFieldAllowed(ThePair._Container->getFieldDescription(i)))
                    {
                        ++NumFields;
                    }
                }

                return NumFields;
            }
            else
            {
                return 0;
            }
        }
        //Field
        else
        {
            const FieldType& fcType(ThePair._Container->getFieldDescription(ThePair._FieldID)->getFieldType());
           
            if(isFieldAllowed(ThePair._Container->getFieldDescription(ThePair._FieldID)))
            {
                if((fcType.getClass() == FieldType::PtrField      ) ||
                   (fcType.getClass() == FieldType::ParentPtrField) ||
                   (fcType.getClass() == FieldType::ChildPtrField ))
                {
                    if(fcType.getCardinality() == FieldType::MultiField )
                    {
                        return ThePair._Container->getField(ThePair._FieldID)->size();
                    }
                    else
                    {
                        return 1;
                    }
                }
                else if(fcType.getContentType() == FieldTraits<AttachmentMap>::getType())
                {
                    GetMapFieldHandle::ContainerList TheContainerList;
                    static_cast<GetSFieldHandle<SFAttachmentPtrMap>*>(ThePair._Container->getField(ThePair._FieldID).get())->flatten(TheContainerList);
                    return TheContainerList.size();
                }
            }
            else
            {
                return 0;
            }
        }
    }
    catch(const boost::bad_any_cast &ex)
    {
        SWARNING << "Bad any cast" << ex.what() << "." << std::endl;
        return 0;
    }
}

UInt32 FieldContainerTreeModel::getIndexOfChild(const boost::any& parent, const boost::any& child) const
{
   try
    {
	    ContainerFieldIdPair ChildPair = boost::any_cast<ContainerFieldIdPair>(child);
	    ContainerFieldIdPair ParentPair = boost::any_cast<ContainerFieldIdPair>(parent);

        //FieldContainer
        if(ChildPair._FieldID == FIELD_CONTAINER_ID)
        {
            const FieldType& fcType(ParentPair._Container->getFieldDescription(ParentPair._FieldID)->getFieldType());
           
            if((fcType.getClass() == FieldType::PtrField      ) ||
               (fcType.getClass() == FieldType::ParentPtrField) ||
               (fcType.getClass() == FieldType::ChildPtrField ))
            {
                if(fcType.getCardinality() == FieldType::MultiField )
                {
                    GetFieldHandlePtr TempHandle(ParentPair._Container->getField(ParentPair._FieldID));
                    GetMFieldHandle<FieldContainerPtrMFieldBase>* TheParentMField = dynamic_cast<GetMFieldHandle<FieldContainerPtrMFieldBase>*>(TempHandle.get());
                    FieldContainer* TheChildContainer = ChildPair._Container;
                    
                    for(UInt32 i(0) ; i<TheParentMField->size() ; ++i)
                    {
                        if(TheParentMField->get(i) == TheChildContainer)
                        {
                            return i;
                        }
                    }

                    SWARNING << "Could not find index." << std::endl;
                    return 0;
                }
                else
                {
                    return 0;
                }
            }
            else if(fcType.getContentType() == FieldTraits<AttachmentMap>::getType())
            {
                //Attachment Map
                GetMapFieldHandle::ContainerList TheContainerList;
                static_cast<GetSFieldHandle<SFAttachmentPtrMap>*>(ParentPair._Container->getField(ParentPair._FieldID).get())->flatten(TheContainerList);
                FieldContainerWeakPtr TheChildContainer = ChildPair._Container;

                for(UInt32 i(0) ; i<TheContainerList.size() ; ++i)
                {
                    if(TheContainerList[i] == TheChildContainer)
                    {
                        return i;
                    }
                }
                SWARNING << "Could not find index." << std::endl;
                return 0;
            }
        }
        else
        {
            return getIndexFromFieldId(ChildPair._Container,ChildPair._FieldID);
        }
    }
    catch(const boost::bad_any_cast &ex)
    {
        SWARNING << "Bad any cast" << ex.what() << "." << std::endl;
        return 0;
    }
}

boost::any FieldContainerTreeModel::getRoot(void) const
{
    return boost::any(ContainerFieldIdPair(getInternalRootFieldContainer(),FIELD_CONTAINER_ID));
}

bool FieldContainerTreeModel::isLeaf(const boost::any& node) const
{
    return getChildCount(node) == 0;
}

void FieldContainerTreeModel::valueForPathChanged(TreePath path, const boost::any& newValue)
{
    //TODO
}

void FieldContainerTreeModel::setRoot(FieldContainer* const root)
{
    setInternalRootFieldContainer(root);
}


bool FieldContainerTreeModel::isEqual(const boost::any& left, const boost::any& right) const
{
    try
    {
        ContainerFieldIdPair LeftPath  = boost::any_cast<ContainerFieldIdPair>(left);
        ContainerFieldIdPair RightPath = boost::any_cast<ContainerFieldIdPair>(right);

        return LeftPath == RightPath;
    }
    catch(boost::bad_any_cast &ex)
    {
        SWARNING << "Bad any cast" << ex.what() << "." << std::endl;
        return false;
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FieldContainerTreeModel::FieldContainerTreeModel(void) :
    Inherited()
{
}

FieldContainerTreeModel::FieldContainerTreeModel(const FieldContainerTreeModel &source) :
    Inherited(source)
{
}

FieldContainerTreeModel::~FieldContainerTreeModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FieldContainerTreeModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & (InternalRootFieldContainerFieldMask |
                     ShowInternalFieldsFieldMask |
                     ShowMultiFieldsFieldMask |
                     ShowSingleFieldsFieldMask |
                     ShowPtrFieldsFieldMask |
                     ShowDataFieldsFieldMask |
                     ShowParentPtrFieldsFieldMask |
                     ShowChildPtrFieldsFieldMask |
                     ShowAttachmentsFieldMask |
                     ShowCallbackFunctorsFieldMask)
        )
    {
        produceTreeStructureChanged(getRootPath(),std::vector<UInt32>(1, 0),std::vector<boost::any>(1, getRoot()));
    }
}

void FieldContainerTreeModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump FieldContainerTreeModel NI" << std::endl;
}

OSG_END_NAMESPACE
