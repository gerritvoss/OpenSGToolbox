/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#ifndef _OSGCOMMANDFACTORY_H_
#define _OSGCOMMANDFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGFactoryBase.h"
#include "OSGSingletonHolder.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING CommandFactoryBase : public FactoryBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*=========================  PROTECTED  ===============================*/

  protected:
    typedef FactoryBase Inherited;
  
    CommandFactoryBase(void);
    
    /*---------------------------------------------------------------------*/
    virtual ~CommandFactoryBase(void);
    

    virtual bool initialize           (void);
    virtual bool terminate            (void);

    virtual bool onLoadInitialize     (void);

    virtual bool initializeFactoryPost(void);
    /*==========================  PRIVATE  ================================*/
  private:
    template <class SingletonT>
    friend class SingletonHolder;

    CommandFactoryBase(const CommandFactoryBase &source);
    void operator =(const CommandFactoryBase &source);
};

typedef OSG::SingletonHolder<OSG::CommandFactoryBase> CommandFactory;

OSG_END_NAMESPACE

#endif /* _OSGCOMMANDFACTORY_H_ */
