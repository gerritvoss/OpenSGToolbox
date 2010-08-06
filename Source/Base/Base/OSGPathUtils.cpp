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

#include "OSGPathUtils.h"
#include <boost/filesystem/operations.hpp>

OSG_BEGIN_NAMESPACE

BoostPath makeRelative(const BoostPath& Root, const BoostPath& ToPath)
{
    BoostPath RootComplete(boost::filesystem::system_complete(Root));

    BoostPath ToPathComplete(boost::filesystem::system_complete(ToPath));

    BoostPath Result;
    boost::filesystem::path::iterator RootIter = RootComplete.begin();
    boost::filesystem::path::iterator ToPathIter = ToPathComplete.begin();

    while(RootIter != RootComplete.end() &&
          ToPathIter != ToPathComplete.end() &&
          RootIter->compare(*ToPathIter) == 0)
    {
        ++RootIter;
        ++ToPathIter;
    }

    while(ToPathIter != ToPathComplete.end())
    {
        if(Result.empty())
        {
            Result = *ToPathIter;
        }
        else
        {
            Result = Result / *ToPathIter;
        }
        ++ToPathIter;
    }

    if(RootIter != RootComplete.end())
    {
        ++RootIter;
    }
    while(RootIter != RootComplete.end())
    {
        Result = BoostPath("..") / Result;
        ++RootIter;
    }


    return Result;
} 

OSG_END_NAMESPACE

