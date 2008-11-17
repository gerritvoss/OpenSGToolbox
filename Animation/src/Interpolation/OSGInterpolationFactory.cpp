/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#include <OpenSG/OSGConfig.h>
#include "OSGInterpolationFactory.h"

#include <OpenSG/OSGLog.h>
#include <OpenSG/OSGTypeBase.h>

OSG_USING_NAMESPACE

/*! \class osg::InterpolationFactory
 */

InterpolationFactory *InterpolationFactory::_the = NULL;

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

InterpolationFactory *InterpolationFactory::the(void)
{
    if(_the == NULL)
        _the = new InterpolationFactory;

    return _the;
}

/*-------------------------------------------------------------------------*/
/*                              Type Info                                  */


bool InterpolationFactory::registerFieldInterpFunc(const osg::InterpolationType& InterpType,const osg::FieldType& F, const InterpFunc& Func)
{
   if(Func == NULL)
   {
      SWARNING << "Tried to register Null Function." << std::endl;
      return false;
   }
   
   if( _InterpMap.find(InterpType) != _InterpMap.end() )
   {
      SLOG << "Creating new Interpolation type " << InterpType << "." << std::endl;
   }
   
   if( _InterpMap[InterpType].find(F.getId()) != _InterpMap[InterpType].end() )
   {
      SWARNING << "Already registered " << InterpType << " interpolation function for " << F.getName() << " type." << std::endl;
      return true;
   }
   
   SLOG << "Registering " << InterpType << " interpolation function for type: " << F.getName() << ", Id: " << F.getId() << ", Ptr: " << Func << "." << std::endl;
   _InterpMap[InterpType][F.getId()] = Func;
   return true;
}

osg::UInt32 InterpolationFactory::getNumFuncs(const osg::InterpolationType& InterpType)
{
   if( _InterpMap.find(InterpType) != _InterpMap.end() )
   {
      return _InterpMap[InterpType].size();
   }
   else
   {
      return 0;
   }
}

InterpolationFactory::InterpFunc InterpolationFactory::getFunc(const osg::InterpolationType& InterpType, const osg::FieldType& F)
{
   return getFunc(InterpType, F.getId());
}

InterpolationFactory::InterpFunc InterpolationFactory::getFunc(const osg::InterpolationType& InterpType, const UInt32& Id)
{
   if( _InterpMap.find(InterpType) != _InterpMap.end() )
   {
      if( _InterpMap[InterpType].find(Id) != _InterpMap[InterpType].end() )
      {
         return _InterpMap[InterpType][Id];
      }
      else
      {
         SWARNING << "No " << InterpType << " interpolation function defined for " << Id << " type." << std::endl;
         return NULL;
      }
   }
   else
   {
      return NULL;
   }
}

bool InterpolationFactory::registerMFieldInterpFunc(const osg::InterpolationType& InterpType,const osg::FieldType& F, const MFieldInterpFunc& Func)
{
   if(Func == NULL)
   {
      SWARNING << "Tried to register Null Function." << std::endl;
      return false;
   }
   
   if( _MFieldInterpMap.find(InterpType) != _MFieldInterpMap.end() )
   {
      SLOG << "Creating new Interpolation type " << InterpType << "." << std::endl;
   }
   
   if( _MFieldInterpMap[InterpType].find(F.getId()) != _MFieldInterpMap[InterpType].end() )
   {
      SWARNING << "Already registered " << InterpType << " interpolation function for " << F.getName() << " type." << std::endl;
      return true;
   }
   
   SLOG << "Registering " << InterpType << " interpolation function for type: " << F.getName() << ", Id: " << F.getId() << ", Ptr: " << Func << "." << std::endl;
   _MFieldInterpMap[InterpType][F.getId()] = Func;
   return true;
}

osg::UInt32 InterpolationFactory::getNumMFieldFuncs(const osg::InterpolationType& InterpType)
{
   if( _MFieldInterpMap.find(InterpType) != _MFieldInterpMap.end() )
   {
      return _MFieldInterpMap[InterpType].size();
   }
   else
   {
      return 0;
   }
}

InterpolationFactory::MFieldInterpFunc InterpolationFactory::getMFieldFunc(const osg::InterpolationType& InterpType, const osg::FieldType& F)
{
   return getMFieldFunc(InterpType, F.getId());
}

InterpolationFactory::MFieldInterpFunc InterpolationFactory::getMFieldFunc(const osg::InterpolationType& InterpType, const UInt32& Id)
{
   if( _MFieldInterpMap.find(InterpType) != _MFieldInterpMap.end() )
   {
      if( _MFieldInterpMap[InterpType].find(Id) != _MFieldInterpMap[InterpType].end() )
      {
         return _MFieldInterpMap[InterpType][Id];
      }
      else
      {
         SWARNING << "No " << InterpType << " interpolation function defined for " << Id << " type." << std::endl;
         return NULL;
      }
   }
   else
   {
      return NULL;
   }
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

InterpolationFactory::InterpolationFactory(void) :
    _InterpMap()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

InterpolationFactory::~InterpolationFactory(void)
{
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGTYPEFACTORY_HEADER_CVSID;
}
