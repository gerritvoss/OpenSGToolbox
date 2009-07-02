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


#ifndef _OSGKEYADAPTER_H_
#define _OSGKEYADAPTER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"

#include "OSGKeyListener.h"

OSG_BEGIN_NAMESPACE

class OSG_INPUTLIB_DLLMAPPING KeyAdapter : public KeyListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
   virtual void keyPressed(const KeyEvent& e);
   virtual void keyReleased(const KeyEvent& e);
   virtual void keyTyped(const KeyEvent& e);
};

typedef KeyAdapter* KeyAdapterPtr;

OSG_END_NAMESPACE

#endif /* _OSGKEYADAPTER_H_ */


