#include "OSGContainerGatherUtils.h"
#include "OSGNameAttachment.h"
#include "OSGAttachmentContainer.h"
#include "OSGFieldContainerFactory.h"
#include "OSGFilePathAttachment.h"

OSG_BEGIN_NAMESPACE

std::set<FieldContainerUnrecPtr> getAllDependantFCs(const std::set<FieldContainerUnrecPtr>& Containers, const std::set<FieldContainerUnrecPtr>& IgnoreContainers, const std::vector<UInt32>& IgnoreTypes)
{
    std::set<FieldContainerUnrecPtr> AllContainers(Containers);
    std::set<FieldContainerUnrecPtr> NewIgnores(IgnoreContainers);

    UInt32 NumFields;
    const FieldDescriptionBase* TheFieldDesc(NULL);
    const Field* TheField(NULL);

    //Loop through all of the given containers
    std::set<FieldContainerUnrecPtr> ContainersDifference;
    std::set_difference(AllContainers.begin(),AllContainers.end(), NewIgnores.begin(), NewIgnores.end(), std::inserter(ContainersDifference, ContainersDifference.begin()));
    for(std::set<FieldContainerUnrecPtr>::iterator ContainersItor(ContainersDifference.begin()) ; ContainersItor != ContainersDifference.end() ; ++ContainersItor)
    {
        if(std::find(IgnoreTypes.begin(), IgnoreTypes.end(), (*ContainersItor)->getType().getId()) != IgnoreTypes.end())
        {
            continue;
        }

        if((*ContainersItor)->getType().isDerivedFrom(AttachmentContainer::getClassType()))
        {
            //All of the Attachments
            std::vector<std::string> AttachmentIds;
            AttachmentMap::const_iterator MapItor(dynamic_pointer_cast<AttachmentContainer>(*ContainersItor)->getSFAttachments()->getValue().begin());
            AttachmentMap::const_iterator MapEnd(dynamic_pointer_cast<AttachmentContainer>(*ContainersItor)->getSFAttachments()->getValue().end());
            for( ; MapItor!=MapEnd  ; ++MapItor)
            {
                if(MapItor->second->getType() != Name::getClassType() &&
                   MapItor->second->getType() != FilePathAttachment::getClassType())
                {
                    std::set<FieldContainerUnrecPtr> TheContainer;
                    TheContainer.insert(MapItor->second);
                    
                    AllContainers.insert(MapItor->second);
                    NewIgnores.insert(Containers.begin(), Containers.end());

                    std::set<FieldContainerUnrecPtr> NewContainers(getAllDependantFCs(TheContainer, NewIgnores, IgnoreTypes));

                    AllContainers.insert(NewContainers.begin(), NewContainers.end());
                    NewIgnores.insert(NewContainers.begin(), NewContainers.end());
                }
            }
        }

        //Loop through all of the fields of the Container
        NumFields = (*ContainersItor)->getType().getNumFieldDescs();
        for(UInt32 i(1) ; i<NumFields+1 ; ++i)
        {
            TheFieldDesc = (*ContainersItor)->getFieldDescription(i);
            if((*ContainersItor)->getField(TheFieldDesc->getFieldId()) == NULL)
            {
                continue;
            }

            TheField = (*ContainersItor)->getField(TheFieldDesc->getFieldId())->getField();

            if(!TheFieldDesc->isInternal())
            {
                //Determine if the Field is a Field Container Ptr
                if(TheFieldDesc->getFieldType().isPtrField())
                {
                    //Determine the cardinality of the field
                    if(TheField->getCardinality() == FieldType::SingleField)
                    {
                        //If the Ptr is NOT NULL and is NOT in the Containers already
                        if(static_cast<const SFUnrecFieldContainerPtr *>(TheField)->getValue() != NULL &&
                            AllContainers.find(static_cast<const SFUnrecFieldContainerPtr *>(TheField)->getValue()) == AllContainers.end() &&
                            NewIgnores.find(static_cast<const SFUnrecFieldContainerPtr *>(TheField)->getValue()) == NewIgnores.end() && 
                            std::find(IgnoreTypes.begin(), IgnoreTypes.end(), static_cast<const SFUnrecFieldContainerPtr *>(TheField)->getValue()->getTypeId()) == IgnoreTypes.end())
                        {
                            std::set<FieldContainerUnrecPtr> TheContainer;
                            
                            TheContainer.insert(static_cast<const SFUnrecFieldContainerPtr *>(TheField)->getValue());
                            
                            AllContainers.insert(static_cast<const SFUnrecFieldContainerPtr *>(TheField)->getValue());
                            NewIgnores.insert(Containers.begin(), Containers.end());
                        
                            std::set<FieldContainerUnrecPtr> NewContainers(getAllDependantFCs(TheContainer, NewIgnores, IgnoreTypes));

                            AllContainers.insert(NewContainers.begin(), NewContainers.end());
                            NewIgnores.insert(NewContainers.begin(), NewContainers.end());
                        }
                    }
                    else
                    {
                        for(UInt32 i(0) ; i<TheField->getSize() ; ++i)
                        {
                            if(static_cast<const MFUnrecFieldContainerPtr *>(TheField)->operator[](i) != NULL &&
                                AllContainers.find(static_cast<const MFUnrecFieldContainerPtr *>(TheField)->operator[](i)) == AllContainers.end() &&
                                NewIgnores.find(static_cast<const MFUnrecFieldContainerPtr *>(TheField)->operator[](i)) == NewIgnores.end() && 
                                std::find(IgnoreTypes.begin(), IgnoreTypes.end(), static_cast<const MFUnrecFieldContainerPtr *>(TheField)->operator[](i)->getTypeId()) == IgnoreTypes.end())
                            {
                                std::set<FieldContainerUnrecPtr> TheContainer;
                                TheContainer.insert(static_cast<const MFUnrecFieldContainerPtr *>(TheField)->operator[](i));
                                
                                AllContainers.insert(static_cast<const MFUnrecFieldContainerPtr *>(TheField)->operator[](i));
                                NewIgnores.insert(Containers.begin(), Containers.end());

                                std::set<FieldContainerUnrecPtr> NewContainers(getAllDependantFCs(TheContainer, NewIgnores, IgnoreTypes));

                                AllContainers.insert(NewContainers.begin(), NewContainers.end());
                                NewIgnores.insert(NewContainers.begin(), NewContainers.end());
                            }
                        }
                    }
                }
            }
        }
    }

    return AllContainers;
}

OSG_END_NAMESPACE


