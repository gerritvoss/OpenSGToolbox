#include "OSGContainerUtils.h"
#include "OSGNameAttachment.h"
#include "OSGAttachmentContainer.h"
#include "OSGFieldContainerFactory.h"
//#include "OSGFilePathAttachment.h"

OSG_BEGIN_NAMESPACE

const FieldContainerType* getClosestAncestor(const FieldContainerType *type,
                                             MFUnrecFieldContainerPtr::const_iterator begin,
                                             MFUnrecFieldContainerPtr::const_iterator end)
{
    if(type == NULL)
    {
        return NULL;
    }

    const FieldContainerType* AncestorType(NULL);
    const FieldContainerType* FCType(NULL);
    MFUnrecFieldContainerPtr::const_iterator Itor(begin);
    for(; Itor!=end ; ++Itor)
    {
        FCType = &((*Itor)->getType());
        if(type->isDerivedFrom(*FCType)&&
           (AncestorType == NULL || FCType->isDerivedFrom(*AncestorType)))
        {
            AncestorType = FCType;
        }
    }

    return AncestorType;
}

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
    FieldContainerFactoryBase::ContainerPtr Cont(NULL);
    for(FCStoreIter = FCStore.begin() ; FCStoreIter != FCStore.end() ; ++FCStoreIter)
    {
        if(*FCStoreIter != NULL)
        {
#ifdef OSG_MT_CPTR_ASPECT
            Cont = (*FCStoreIter)->getPtr();
#else
            Cont = *FCStoreIter;
#endif
        }
        else
        {
            Cont = NULL;
        }
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

const FieldContainerType* getFieldContainerTypeFromPtrType(const DataType& type)
{
    std::string FCPtrTypeName = type.getName().substr(0,type.getName().size()-3);
    return FieldContainerFactory::the()->findType(FCPtrTypeName.c_str());
}

bool isFieldContentDerivedFrom(const FieldType &TheFieldType, const FieldContainerType* TheFCType)
{
    if(TheFieldType.isPtrField())
    {
        std::string FieldPtrTypeName(TheFieldType.getContentType().getName());
        switch(TheFieldType.getClass())
        {
            case FieldType::PtrField:
            case FieldType::ParentPtrField:
            case FieldType::ChildPtrField:
                FieldPtrTypeName = FieldPtrTypeName.substr(0,FieldPtrTypeName.size()-3);
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

OSG_END_NAMESPACE


