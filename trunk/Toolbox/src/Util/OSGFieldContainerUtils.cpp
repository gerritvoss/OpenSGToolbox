#include "OSGFieldContainerUtils.h"
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGAttachmentContainer.h>

OSG_BEGIN_NAMESPACE

FieldContainerPtr getFieldContainer(const Char8 *szTypeName, const std::string &namestring)
{
   return getFieldContainer(FieldContainerFactory::the()->findType(szTypeName), namestring);
}

FieldContainerPtr getFieldContainer(const FieldContainerType *szType, const std::string &namestring)
{
   if(szType == NULL)
   {
      std::cout << "The Field type is not defined." << std::endl;
   }

   const std::vector<FieldContainerPtr>* FCStore(	FieldContainerFactory::the()->getFieldContainerStore () );

   std::vector<FieldContainerPtr>::const_iterator FCStoreIter;
   for(FCStoreIter = FCStore->begin() ; FCStoreIter != FCStore->end() ; ++FCStoreIter)
   {
      if( (*FCStoreIter) != NullFC && (*FCStoreIter)->getType() == (*szType) )
      {
         const Char8 *Name( getName(AttachmentContainerPtr::dcast(*FCStoreIter)) );
         if(Name != NULL && namestring.compare(Name) == 0)
         {
            return (*FCStoreIter);
         }
      }
   }

   return NullFC;
}


FieldContainerPtr getFieldContainer(const std::string &namestring)
{
   const std::vector<FieldContainerPtr>* FCStore(	FieldContainerFactory::the()->getFieldContainerStore () );

   std::vector<FieldContainerPtr>::const_iterator FCStoreIter;
   for(FCStoreIter = FCStore->begin() ; FCStoreIter != FCStore->end() ; ++FCStoreIter)
   {
		const Char8 *Name( getName(AttachmentContainerPtr::dcast(*FCStoreIter)) );
		if(Name != NULL && namestring.compare(Name) == 0)
		{
			return (*FCStoreIter);
		}
   }

   return NullFC;
}


OSG_END_NAMESPACE
