#include "OSGContainerGatherUtils.h"
#include "OSGNameAttachment.h"
#include "OSGAttachmentContainer.h"
#include "OSGFieldContainerFactory.h"
#include "OSGFilePathAttachment.h"
#include "OSGDrawableStatsAttachment.h"

OSG_BEGIN_NAMESPACE

FCFileType::FCPtrStore getAllDependantFCs(const FCFileType::FCPtrStore& Containers,
                                    const FCFileType::FCPtrStore& IgnoreContainers,
                                    const std::vector<const FieldContainerType*>& IgnoreTypes,
                                    bool RecurseFilePathAttachedContainers)
{
    std::vector<UInt32> IgnoreTypeIds;
    for(UInt32 i = 0; i < IgnoreTypes.size(); ++i)
    {
        IgnoreTypeIds.push_back(IgnoreTypes[i]->getId());
    }
    
    return getAllDependantFCs(Containers,
                              IgnoreContainers,
                              IgnoreTypeIds,
                              RecurseFilePathAttachedContainers);
}

FCFileType::FCPtrStore getAllDependantFCs(const FCFileType::FCPtrStore& Containers,
                                                    const FCFileType::FCPtrStore& IgnoreContainers,
                                                    const std::vector<UInt32>& IgnoreTypes,
                                                    bool RecurseFilePathAttachedContainers)
{
    FCFileType::FCPtrStore AllContainers(Containers);
    FCFileType::FCPtrStore NewIgnores(IgnoreContainers);

    UInt32 NumFields;
    const FieldDescriptionBase* TheFieldDesc(NULL);
    GetFieldHandlePtr TheFieldHandle;
    const Field* TheField(NULL);

    //Loop through all of the given containers
    FCFileType::FCPtrStore ContainersDifference;
    std::set_difference(AllContainers.begin(),AllContainers.end(), 
                        NewIgnores.begin(), NewIgnores.end(), 
                        std::inserter(ContainersDifference, ContainersDifference.begin()),
                        FCFileType::FCPtrStore::key_compare() );
    for(FCFileType::FCPtrStore::iterator ContainersItor(ContainersDifference.begin()) ; ContainersItor != ContainersDifference.end() ; ++ContainersItor)
    {
        if(std::find(IgnoreTypes.begin(), IgnoreTypes.end(), (*ContainersItor)->getType().getId()) != IgnoreTypes.end())
        {
            continue;
        }

        if((*ContainersItor)->getType().isDerivedFrom(AttachmentContainer::getClassType()))
        {
            //If the Container has a FilePathAttachment, and the RecurseFilePathAttachedContainers
            //flag is true then dependent containers of this container should be
            //skipped
            if(!RecurseFilePathAttachedContainers &&
               FilePathAttachment::getFilePath(dynamic_pointer_cast<AttachmentContainer>(*ContainersItor)) != NULL)
            {
                continue;
            }

            //All of the Attachments
            std::vector<std::string> AttachmentIds;
            AttachmentMap::const_iterator MapItor(dynamic_pointer_cast<AttachmentContainer>(*ContainersItor)->getSFAttachments()->getValue().begin());
            AttachmentMap::const_iterator MapEnd(dynamic_pointer_cast<AttachmentContainer>(*ContainersItor)->getSFAttachments()->getValue().end());
            for( ; MapItor!=MapEnd  ; ++MapItor)
            {
                if(MapItor->second->getType() != Name::getClassType() &&
                   MapItor->second->getType() != FilePathAttachment::getClassType() &&
                   MapItor->second->getType() != DrawableStatsAttachment::getClassType())
                {
                    FCFileType::FCPtrStore TheContainer;
                    TheContainer.insert(MapItor->second);
                    
                    AllContainers.insert(MapItor->second);
                    NewIgnores.insert(Containers.begin(), Containers.end());

                    FCFileType::FCPtrStore NewContainers(getAllDependantFCs(TheContainer, NewIgnores, IgnoreTypes));

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
            TheFieldHandle =
                (*ContainersItor)->getField(TheFieldDesc->getFieldId());
            TheField = TheFieldHandle->getField();

            if(!TheFieldDesc->isInternal())
            {
                //Determine if the Field is a Field Container Ptr
				if(TheFieldDesc->getFieldType().getClass() == FieldType::PtrField ||
					TheFieldDesc->getFieldType().getClass() == FieldType::ParentPtrField ||
					TheFieldDesc->getFieldType().getClass() == FieldType::ChildPtrField)
                {
                    //Determine the cardinality of the field
                    if(TheFieldHandle->getCardinality() == FieldType::SingleField)
                    {
                        //If the Ptr is NOT NULL and is NOT in the Containers already
                        if(static_cast<const SFUnrecFieldContainerPtr *>(TheField)->getValue() != NULL &&
                            AllContainers.find(static_cast<const SFUnrecFieldContainerPtr *>(TheField)->getValue()) == AllContainers.end() &&
                            NewIgnores.find(static_cast<const SFUnrecFieldContainerPtr *>(TheField)->getValue()) == NewIgnores.end() && 
                            std::find(IgnoreTypes.begin(), IgnoreTypes.end(), static_cast<const SFUnrecFieldContainerPtr *>(TheField)->getValue()->getTypeId()) == IgnoreTypes.end())
                        {
                            FCFileType::FCPtrStore TheContainer;
                            
                            TheContainer.insert(static_cast<const SFUnrecFieldContainerPtr *>(TheField)->getValue());
                            
                            AllContainers.insert(static_cast<const SFUnrecFieldContainerPtr *>(TheField)->getValue());
                            NewIgnores.insert(Containers.begin(), Containers.end());
                        
                            FCFileType::FCPtrStore NewContainers(getAllDependantFCs(TheContainer, NewIgnores, IgnoreTypes));

                            AllContainers.insert(NewContainers.begin(), NewContainers.end());
                            NewIgnores.insert(NewContainers.begin(), NewContainers.end());
                        }
                    }
                    else
                    {
                        for(UInt32 i(0) ; i<TheFieldHandle->size() ; ++i)
                        {
                            if(static_cast<const MFUnrecFieldContainerPtr *>(TheField)->operator[](i) != NULL &&
                                AllContainers.find(static_cast<const MFUnrecFieldContainerPtr *>(TheField)->operator[](i)) == AllContainers.end() &&
                                NewIgnores.find(static_cast<const MFUnrecFieldContainerPtr *>(TheField)->operator[](i)) == NewIgnores.end() && 
                                std::find(IgnoreTypes.begin(), IgnoreTypes.end(), static_cast<const MFUnrecFieldContainerPtr *>(TheField)->operator[](i)->getTypeId()) == IgnoreTypes.end())
                            {
                                FCFileType::FCPtrStore TheContainer;
                                TheContainer.insert(static_cast<const MFUnrecFieldContainerPtr *>(TheField)->operator[](i));
                                
                                AllContainers.insert(static_cast<const MFUnrecFieldContainerPtr *>(TheField)->operator[](i));
                                NewIgnores.insert(Containers.begin(), Containers.end());

                                FCFileType::FCPtrStore NewContainers(getAllDependantFCs(TheContainer, NewIgnores, IgnoreTypes));

                                AllContainers.insert(NewContainers.begin(), NewContainers.end());
                                NewIgnores.insert(NewContainers.begin(), NewContainers.end());
                            }
                        }
                    }
                }
                //If this is a EventProducer field
                //else if(TheFieldDesc->getFieldType().getContentType() ==
                //        FieldTraits<EventProducerPtr>::getType())
                //{
                //    //Get all of the Activities
                //    if(static_cast<const SFEventProducerPtr*>(TheField)->getValue() != NULL)
                //    {
                //        Activity* TheActvitiy;
                //        EventProducerPtr TheProducer(static_cast<const SFEventProducerPtr*>(TheField)->getValue());
                //        for(UInt32 i(1) ; i<=TheProducer->getNumProducedEvents() ; ++i)
                //        {
                //            for(UInt32 j(0) ; j<TheProducer->getNumActivitiesAttached(i) ; ++j)
                //            {
                //                TheActvitiy = TheProducer->getAttachedActivity(i,j);
                //                if(AllContainers.find(TheActvitiy) == AllContainers.end() &&
                //                   NewIgnores.find(TheActvitiy) == NewIgnores.end() && 
                //                   std::find(IgnoreTypes.begin(), IgnoreTypes.end(), TheActvitiy->getTypeId()) == IgnoreTypes.end())
                //                {
                //                    FCFileType::FCPtrStore TheContainer;
                //                    TheContainer.insert(TheActvitiy);
                //                    
                //                    AllContainers.insert(TheActvitiy);
                //                    NewIgnores.insert(Containers.begin(), Containers.end());

                //                    FCFileType::FCPtrStore NewContainers(getAllDependantFCs(TheContainer, NewIgnores, IgnoreTypes));

                //                    AllContainers.insert(NewContainers.begin(), NewContainers.end());
                //                    NewIgnores.insert(NewContainers.begin(), NewContainers.end());
                //                }
                //            }
                //        }
                //    }
                //}
            }
        }
    }

    return AllContainers;
}

OSG_END_NAMESPACE


