#include "OSGIntrusivePtrImplBase.h"


namespace boost
{
void intrusive_ptr_release(osg::IntrusivePtrImplBase * p)
{
    if( --(p->_ReferenceCount) == 0 )
    {
        delete p;
    }
}

}
