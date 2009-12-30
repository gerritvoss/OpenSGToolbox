/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Input                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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
#ifndef _OPENSG_WINDOW_UTILS_H_
#define _OPENSG_WINDOW_UTILS_H_

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"

#include <OpenSG/OSGWindow.h>
#include <OpenSG/OSGFieldContainerType.h>
#include <OpenSG/OSGVector.h>

#include "OSGWindowEventProducer.h"

OSG_BEGIN_NAMESPACE

WindowEventProducerPtr OSG_INPUTLIB_DLLMAPPING createDefaultWindowEventProducer(void);

WindowEventProducerPtr OSG_INPUTLIB_DLLMAPPING createWindowEventProducer(const FieldContainerType WindowType);

OSG_END_NAMESPACE

#endif


