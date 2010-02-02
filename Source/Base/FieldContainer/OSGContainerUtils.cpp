#include "OSGContainerUtils.h"
#include "OSGNameAttachment.h"
#include "OSGAttachmentContainer.h"
#include "OSGFieldContainerFactory.h"
#include "OSGEventProducerPtrType.h"
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

std::vector<FieldContainerUnrecPtr> getAllContainersByDerivedType(const FieldContainerType *szType)
{
    std::vector<FieldContainerUnrecPtr> Result;

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
        if( Cont != NULL && Cont->getType().isDerivedFrom(*szType) )
        {
            Result.push_back(Cont);
        }
    }
    return Result;
}

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


FieldContainerUnrecPtr getFieldContainer(const std::string &namestring)
{
   const FieldContainerFactoryBase::ContainerStore &FCStore(	FieldContainerFactory::the()->getFieldContainerStore () );

   FieldContainerFactoryBase::ContainerStore::const_iterator FCStoreIter;
   FieldContainerFactoryBase::ContainerPtr Cont;
   for(FCStoreIter = FCStore.begin() ; FCStoreIter != FCStore.end() ; ++FCStoreIter)
   {
       if(*FCStoreIter == NULL)
       {
           continue;
       }
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

bool isFieldContentDerivedFrom(const FieldType &TheFieldType, const FieldContainerType* TheFCType)
{
    if(TheFieldType.isPtrField())
    {
        std::string FieldPtrTypeName(TheFieldType.getName());
        switch(TheFieldType.getClass())
        {
            case FieldType::PtrField:
                FieldPtrTypeName = FieldPtrTypeName.substr(7,FieldPtrTypeName.size()-10);
                break;
            case FieldType::ParentPtrField:
                FieldPtrTypeName = FieldPtrTypeName.substr(13,FieldPtrTypeName.size()-16);
                break;
            case FieldType::ChildPtrField:
                FieldPtrTypeName = FieldPtrTypeName.substr(12,FieldPtrTypeName.size()-15);
                break;
            default:
            case FieldType::ValueField:
                return false;
                break;
        }
        const FieldContainerType* PtrContentType = FieldContainerFactory::the()->findType(FieldPtrTypeName.c_str());
        
        return TheFCType->isDerivedFrom(*PtrContentType);
    }
    else
    {
        return false;
    }
    return false;
}

bool isEventProducer(const FieldContainerRefPtr TheFC)
{
    return TheFC->getField("EventProducer") != NULL;
}

EventProducerPtr getEventProducer(const FieldContainerRefPtr TheFC)
{
    EditFieldHandlePtr TheFieldHandle(TheFC->editField("EventProducer"));
    if(TheFieldHandle == NULL)
    {
        return NULL;
    }

    SFEventProducerPtr*
        TheField(static_cast<SFEventProducerPtr*>(TheFieldHandle->getField()));

    if(TheField == NULL)
    {
        return NULL;
    }
    else
    {
        return TheField->getValue();
    }
}

OSG_END_NAMESPACE


