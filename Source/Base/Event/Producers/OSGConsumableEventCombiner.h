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

#ifndef _OSGCONSUMABLEEVENTCOMBINER_H_
#define _OSGCONSUMABLEEVENTCOMBINER_H_

#include "OSGConfig.h"
#include "OSGBaseDef.h"

#include "OSGEventDetails.h"


OSG_BEGIN_NAMESPACE

class OSG_BASE_DLLMAPPING ConsumableEventCombiner
{
private:
    mutable EventDetails const * _pDetails;

public:
    ConsumableEventCombiner(void);

    ConsumableEventCombiner(EventDetails const * e);

    ConsumableEventCombiner(const ConsumableEventCombiner& );

    typedef void result_type;

    template<typename InputIterator>
    result_type operator()(InputIterator first, InputIterator last) const
    {
        while (first != last) 
        {
            *first;
            if(_pDetails->isConsumed())
            {
                break;
            }
            ++first;
        }
        _pDetails = NULL;
    }
};

OSG_END_NAMESPACE

#endif /* _OSGCONSUMABLEEVENTCOMBINER_H_ */
