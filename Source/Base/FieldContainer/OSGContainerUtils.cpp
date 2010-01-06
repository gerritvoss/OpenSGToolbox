#include "OSGContainerUtils.h"
#include "OSGNameAttachment.h"
#include "OSGAttachmentContainer.h"
#include "OSGFieldContainerFactory.h"
//#include "OSGFieldContainerFields.h"
//#include "OSGFilePathAttachment.h"

OSG_BEGIN_NAMESPACE

//const FieldContainerType* getClosestAncestor(const FieldContainerType *type, const std::vector<FieldContainerPtr>& Ancestors)
//{
    //if(type == NULL)
    //{
        //return NULL;
    //}

    //const FieldContainerType* AncestorType(NULL);
    //const FieldContainerType* FCType(NULL);

    //for(UInt32 i(0) ; i<Ancestors.size() ; ++i)
    //{
        //FCType = &(Ancestors[i]->getType());
    //if(type->isDerivedFrom(*FCType)&&
       //(AncestorType == NULL || FCType->isDerivedFrom(*AncestorType)))
    //{
        //AncestorType = FCType;
    //}
//}

//return AncestorType;
//}

//std::vector<FieldContainerPtr> getAllContainersByType(const FieldContainerType *szType)
//{
//std::vector<FieldContainerPtr> Result;

//const std::vector<FieldContainerPtr>* FCStore(	FieldContainerFactory::the()->getFieldContainerStore () );

    //std::vector<FieldContainerPtr>::const_iterator FCStoreIter;
    //for(FCStoreIter = FCStore->begin() ; FCStoreIter != FCStore->end() ; ++FCStoreIter)
    //{
        //if( (*FCStoreIter) != NullFC && (*FCStoreIter)->getType() == (*szType) )
        //{
            //Result.push_back(*FCStoreIter);
        //}
    //}
    //return Result;
//}

//std::vector<FieldContainerPtr> getAllContainersByDerivedType(const FieldContainerType *szType)
//{
    //std::vector<FieldContainerPtr> Result;

    //const std::vector<FieldContainerPtr>* FCStore(	FieldContainerFactory::the()->getFieldContainerStore () );

    //std::vector<FieldContainerPtr>::const_iterator FCStoreIter;
    //for(FCStoreIter = FCStore->begin() ; FCStoreIter != FCStore->end() ; ++FCStoreIter)
    //{
        //if( (*FCStoreIter) != NullFC && (*FCStoreIter)->getType().isDerivedFrom(*szType) )
        //{
            //Result.push_back(*FCStoreIter);
        //}
    //}
    //return Result;
//}

//std::vector<FieldContainerPtr> getAllFieldContainers(const std::string &namestring)
//{
    //std::vector<FieldContainerPtr> Result;
    //std::vector<FieldContainerPtr>::const_iterator FCStoreIter;

    //const std::vector<FieldContainerPtr>* FCStore(	FieldContainerFactory::the()->getFieldContainerStore () );

    //for(FCStoreIter = FCStore->begin() ; FCStoreIter != FCStore->end() ; ++FCStoreIter)
    //{
        //const Char8 *Name( getName(AttachmentContainerPtr::dcast(*FCStoreIter)) );
        //if(Name != NULL && namestring.compare(Name) == 0)
        //{
            //Result.push_back(*FCStoreIter);
        //}
    //}
    //return Result;
//}

FieldContainerUnrecPtr getFieldContainer(const std::string &szTypeName, const std::string &namestring)
{
   return getFieldContainer(FieldContainerFactory::the()->findType(szTypeName.c_str()), namestring);
}

FieldContainerUnrecPtr getFieldContainer(const FieldContainerType *szType, const std::string &namestring)
{
    if(szType == NULL)
    {
        SWARNING << "getFieldContainer(): The Field type is not defined." << std::endl;
        return NULL;
    }

    const FieldContainerFactoryBase::ContainerStore &FCStore(	FieldContainerFactory::the()->getFieldContainerStore () );

    FieldContainerFactoryBase::ContainerStore::const_iterator FCStoreIter;
    FieldContainerFactoryBase::ContainerPtr Cont;
    for(FCStoreIter = FCStore.begin() ; FCStoreIter != FCStore.end() ; ++FCStoreIter)
    {
#ifdef OSG_MT_CPTR_ASPECT
        Cont = (*FCStoreIter)->getPtr();
#else
        Cont = *FCStoreIter;
#endif
        if( Cont != NULL && Cont->getType() == (*szType) )
        {
            const Char8 *Name( getName(dynamic_cast<AttachmentContainer*>(Cont)) );
            if(Name != NULL && namestring.compare(Name) == 0)
            {
                return Cont;
            }
        }
    }

    return NULL;
}

//bool isFieldAFieldContainerPtr(const Field* TheField)
//{
	//if(TheField != NULL)
	//{
		//std::string TypeName(TheField->getType().getCName());
		//return TypeName.size() >= 3 && TypeName.substr(TypeName.size()-3,3).compare("Ptr") == 0 && TypeName.compare("SFEventProducerPtr") != 0;
	//}
	//else
	//{
		//return false;
	//}
//}


//std::set<FieldContainerPtr> getAllDependantFCs(const std::set<FieldContainerPtr>& Containers, const std::set<FieldContainerPtr>& IgnoreContainers, const std::vector<UInt32>& IgnoreTypes)
//{
	//std::set<FieldContainerPtr> AllContainers(Containers);
	//std::set<FieldContainerPtr> NewIgnores(IgnoreContainers);

	//UInt32 NumFields;
	//const FieldDescription* TheFieldDesc(NULL);
	//Field* TheField(NULL);

	////Loop through all of the given containers
	//std::set<FieldContainerPtr> ContainersDifference;
	//std::set_difference(AllContainers.begin(),AllContainers.end(), NewIgnores.begin(), NewIgnores.end(), std::inserter(ContainersDifference, ContainersDifference.begin()));
	//for(std::set<FieldContainerPtr>::iterator ContainersItor(ContainersDifference.begin()) ; ContainersItor != ContainersDifference.end() ; ++ContainersItor)
	//{
		//if(std::find(IgnoreTypes.begin(), IgnoreTypes.end(), (*ContainersItor)->getType().getId()) != IgnoreTypes.end())
		//{
			//continue;
		//}

        //if((*ContainersItor)->getType().isDerivedFrom(AttachmentContainer::getClassType()))
        //{
            ////All of the Attachments
            //std::vector<std::string> AttachmentIds;
            //AttachmentMap::iterator MapItor(AttachmentContainerPtr::dcast(*ContainersItor)->getSFAttachments()->getValue().begin());
            //AttachmentMap::iterator MapEnd(AttachmentContainerPtr::dcast(*ContainersItor)->getSFAttachments()->getValue().end());
            //for( ; MapItor!=MapEnd  ; ++MapItor)
            //{
                //if(MapItor->second->getType() != Name::getClassType() &&
                   //MapItor->second->getType() != FilePathAttachment::getClassType())
                //{
                    //std::set<FieldContainerPtr> TheContainer;
                    //TheContainer.insert(MapItor->second);
                    
                    //AllContainers.insert(MapItor->second);
                    //NewIgnores.insert(Containers.begin(), Containers.end());

                    //std::set<FieldContainerPtr> NewContainers(getAllDependantFCs(TheContainer, NewIgnores, IgnoreTypes));

                    //AllContainers.insert(NewContainers.begin(), NewContainers.end());
                    //NewIgnores.insert(NewContainers.begin(), NewContainers.end());
                //}
            //}
        //}

		////Loop through all of the fields of the Container
		//NumFields = (*ContainersItor)->getType().getNumFieldDescs();
		//for(UInt32 i(1) ; i<NumFields+1 ; ++i)
		//{
			//TheFieldDesc = (*ContainersItor)->getType().getFieldDescription(i);
			//TheField = (*ContainersItor)->getField(TheFieldDesc->getFieldId());

			//if(!TheFieldDesc->isInternal())
			//{
				////Determine if the Field is a Field Container Ptr
				//if(isFieldAFieldContainerPtr(TheField))
				//{
					////Determine the cardinality of the field
					//if(TheField->getCardinality() == FieldType::SINGLE_FIELD)
					//{
						////If the Ptr is NOT NullFC and is NOT in the Containers already
						//if(static_cast<SFFieldContainerPtr *>(TheField)->getValue() != NullFC &&
							//AllContainers.find(static_cast<SFFieldContainerPtr *>(TheField)->getValue()) == AllContainers.end() &&
							//NewIgnores.find(static_cast<SFFieldContainerPtr *>(TheField)->getValue()) == NewIgnores.end() && 
							//std::find(IgnoreTypes.begin(), IgnoreTypes.end(), static_cast<SFFieldContainerPtr *>(TheField)->getValue()->getTypeId()) == IgnoreTypes.end())
						//{
							//std::set<FieldContainerPtr> TheContainer;
							
							//TheContainer.insert(static_cast<SFFieldContainerPtr *>(TheField)->getValue());
                            
                            //AllContainers.insert(static_cast<SFFieldContainerPtr *>(TheField)->getValue());
							//NewIgnores.insert(Containers.begin(), Containers.end());
						
                            //std::set<FieldContainerPtr> NewContainers(getAllDependantFCs(TheContainer, NewIgnores, IgnoreTypes));

							//AllContainers.insert(NewContainers.begin(), NewContainers.end());
							//NewIgnores.insert(NewContainers.begin(), NewContainers.end());
						//}
					//}
					//else
					//{
						//for(UInt32 i(0) ; i<TheField->getSize() ; ++i)
						//{
							//if(static_cast<MFFieldContainerPtr *>(TheField)->operator[](i) != NullFC &&
								//AllContainers.find(static_cast<MFFieldContainerPtr *>(TheField)->operator[](i)) == AllContainers.end() &&
								//NewIgnores.find(static_cast<MFFieldContainerPtr *>(TheField)->operator[](i)) == NewIgnores.end() && 
								//std::find(IgnoreTypes.begin(), IgnoreTypes.end(), static_cast<MFFieldContainerPtr *>(TheField)->operator[](i)->getTypeId()) == IgnoreTypes.end())
							//{
								//std::set<FieldContainerPtr> TheContainer;
								//TheContainer.insert(static_cast<MFFieldContainerPtr *>(TheField)->operator[](i));
                                
                                //AllContainers.insert(static_cast<MFFieldContainerPtr *>(TheField)->operator[](i));
								//NewIgnores.insert(Containers.begin(), Containers.end());

                                //std::set<FieldContainerPtr> NewContainers(getAllDependantFCs(TheContainer, NewIgnores, IgnoreTypes));

								//AllContainers.insert(NewContainers.begin(), NewContainers.end());
								//NewIgnores.insert(NewContainers.begin(), NewContainers.end());
							//}
						//}
					//}
				//}
			//}
		//}
	//}

	//return AllContainers;
//}

FieldContainerUnrecPtr getFieldContainer(const std::string &namestring)
{
   const FieldContainerFactoryBase::ContainerStore &FCStore(	FieldContainerFactory::the()->getFieldContainerStore () );

   FieldContainerFactoryBase::ContainerStore::const_iterator FCStoreIter;
   FieldContainerFactoryBase::ContainerPtr Cont;
   for(FCStoreIter = FCStore.begin() ; FCStoreIter != FCStore.end() ; ++FCStoreIter)
   {
#ifdef OSG_MT_CPTR_ASPECT
        Cont = (*FCStoreIter)->getPtr();
#else
        Cont = *FCStoreIter;
#endif
        const Char8 *Name( getName(dynamic_cast<AttachmentContainer*>(Cont)) );
        if(Name != NULL && namestring.compare(Name) == 0)
        {
            return Cont;
        }
   }

   return NULL;
}

//bool isFieldConentDerivedFrom(const Field* TheField, const FieldContainerType* TheFCType)
//{
	//if(TheField != NULL &&
       //isFieldAFieldContainerPtr(TheField))
	//{
		//std::string FieldPtrTypeName(TheField->getType().getCName());
        //FieldPtrTypeName = FieldPtrTypeName.substr(2,FieldPtrTypeName.size()-5);
        //const FieldContainerType* PtrContentType = FieldContainerFactory::the()->findType(FieldPtrTypeName.c_str());
        
		//return TheFCType->isDerivedFrom(*PtrContentType);
	//}
	//else
	//{
		//return false;
	//}
    //return false;
//}

//bool isEventProducer(const FieldContainerPtr TheFC)
//{
    //return TheFC->getField("EventProducer") != NULL;
//}

//EventProducerPtr getEventProducer(const FieldContainerPtr TheFC)
//{
    //SFEventProducerPtr* TheField(static_cast<SFEventProducerPtr*>(TheFC->getField("EventProducer")));
    //if(TheField == NULL)
    //{
        //return NULL;
    //}
    //else
    //{
        //return TheField->getValue();
    //}
//}

OSG_END_NAMESPACE


