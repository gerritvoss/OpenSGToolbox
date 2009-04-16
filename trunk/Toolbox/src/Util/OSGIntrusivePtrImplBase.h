/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          Authors: David Kabala                            *
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
#ifndef _OSG_INTRUSIVE_PTR_IMPL_BASE_H_
#define _OSG_INTRUSIVE_PTR_IMPL_BASE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"

#include <boost/detail/atomic_count.hpp>
#include <boost/intrusive_ptr.hpp>

OSG_BEGIN_NAMESPACE

class IntrusivePtrImplBase;

OSG_END_NAMESPACE

namespace boost{
void OSG_TOOLBOXLIB_DLLMAPPING intrusive_ptr_add_ref(osg::IntrusivePtrImplBase * p);
void OSG_TOOLBOXLIB_DLLMAPPING intrusive_ptr_release(osg::IntrusivePtrImplBase * p);
}

OSG_BEGIN_NAMESPACE

class OSG_TOOLBOXLIB_DLLMAPPING IntrusivePtrImplBase
{
    protected:
        boost::detail::atomic_count _ReferenceCount;

        IntrusivePtrImplBase(void);

        IntrusivePtrImplBase(const IntrusivePtrImplBase& source);
        void operator =(const IntrusivePtrImplBase& source);

        virtual ~IntrusivePtrImplBase(void);

        friend void ::boost::intrusive_ptr_add_ref(IntrusivePtrImplBase * p);
        friend void ::boost::intrusive_ptr_release(IntrusivePtrImplBase * p);
};

OSG_END_NAMESPACE

#include "OSGIntrusivePtrImplBase.inl"
#endif /* _OSG_INTRUSIVE_PTR_IMPL_BASE_H_ */
