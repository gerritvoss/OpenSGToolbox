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

#ifndef _OSGCOMMANDTYPE_H_
#define _OSGCOMMANDTYPE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/OSGTypeBase.h>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING CommandType : public TypeBase
{
    /*==========================  PUBLIC  =================================*/

  public :
    UInt32 getEventId(void) const;

    /*---------------------------------------------------------------------*/
    CommandType(const Char8  *szName, 
             const Char8  *szParentName,
             const UInt32  uiNameSpace = 0);
    
    /*---------------------------------------------------------------------*/
    virtual ~CommandType(void);

    /*---------------------------------------------------------------------*/
    bool operator ==(const CommandType &other) const;
    bool operator !=(const CommandType &other) const;

	bool isDerivedFrom( const TypeBase &   	 other ) const;
	bool isDerivedFrom( const CommandType & other ) const;
    CommandType * getParent(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:
    UInt32 _uiCommandTypeId;
    UInt32 _uiCommandTypeRootId;

    typedef TypeBase Inherited;

    CommandType(const CommandType &source);

    /*==========================  PRIVATE  ================================*/
  private:

    void operator =(const CommandType &source);
};

typedef CommandType *CommandTypeP;

OSG_END_NAMESPACE
        
#include "OSGCommandType.inl"

#endif /* _OSGCOMMANDTYPE_H_ */
