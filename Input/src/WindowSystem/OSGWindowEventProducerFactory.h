/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   contact: dkabala@vrac.iastate.edu                                       *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
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
#ifndef _OSGWINDOWEVENTPRODUCERFACTORY_H_
#define _OSGWINDOWEVENTPRODUCERFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include <map>

#include "OSGInputConfig.h"

#include "OSGWindowEventProducer.h"

OSG_BEGIN_NAMESPACE

class OSG_INPUT_CLASS_API WindowEventProducerFactory
{
   /*=========================  PUBLIC  ===============================*/
public:
   static WindowEventProducerFactory* the(void);

   const FieldContainerType* registerProducer(const FieldContainerType* WindowType, const FieldContainerType* WindowEventProducerType);

   const FieldContainerType* unregisterProducer(const FieldContainerType* WindowType);

   WindowEventProducerPtr createWindowEventProducer(WindowPtr TheWindow);

private:
   static WindowEventProducerFactory* _the;

   typedef std::map<UInt32, UInt32> WindowToWindowEventProducerMap;

   WindowToWindowEventProducerMap _WindowToWindowEventProducerMap;

   WindowEventProducerFactory(void);
    
};

OSG_END_NAMESPACE

#include "OSGWindowEventProducerFactory.inl"

#endif /* _OSGWINDOWEVENTPRODUCERFACTORY_H_ */
