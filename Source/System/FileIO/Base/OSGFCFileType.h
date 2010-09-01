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

#ifndef _OSGFCFILETYPE_H_
#define _OSGFCFILETYPE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include <vector>
#include <set>
#include <string>
#include <iostream>

#include "OSGIOFileTypeBase.h"
#include "OSGFieldContainer.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEM_DLLMAPPING FCFileType : public IOFileTypeBase
{
     /*==========================  PUBLIC  =================================*/
   public:
    typedef IOFileTypeBase Inherited;
    typedef FCFileType  Self;
 
	typedef std::vector<std::string> ExtensionVector;
    typedef std::vector<UInt32> FCTypeVector;

    class FCIdCompare
    {
      public:
        bool operator()(const FieldContainerUnrecPtr& Left, const FieldContainerUnrecPtr& Right) const;
    };

    typedef std::set<FieldContainerUnrecPtr, FCIdCompare> FCPtrStore;

    /*---------------------------------------------------------------------*/
	virtual std::string getName(void) const = 0;
 
     /*---------------------------------------------------------------------*/
     
     /*---------------------------------------------------------------------*/
     virtual ~FCFileType(void);
 
     /*---------------------------------------------------------------------*/
     //void setOptions(const Char8 *options);
 
     
     /*---------------------------------------------------------------------*/
     virtual const ExtensionVector &getSuffixList         (void) const;
 
            bool                    doOverride         (void);
            UInt32                  getOverridePriority(void);
     
     /*---------------------------------------------------------------------*/
     virtual FCPtrStore read(std::istream &is,
		                     const std::string& fileNameOrExtension) const;
 
     /*---------------------------------------------------------------------*/
     virtual bool write(const FCPtrStore &Containers, std::ostream &os,
                        const std::string& fileNameOrExtension, const FCTypeVector& IgnoreTypes) const;
 
     virtual void print(void);
     /*=========================  PROTECTED  ===============================*/
   protected:
 
     /*---------------------------------------------------------------------*/
	 ExtensionVector _suffixList;
 
    /*! If true loader can override others. */
    bool                   _override;         
    /*! The priority for overriding. */
    UInt32                 _overridePriority; 
   
     /*---------------------------------------------------------------------*/
     FCFileType(const ExtensionVector&  suffixArray,
                        bool    override,
                        UInt32  overridePriority,
                        UInt32  flags = OSG_READ_SUPPORTED);
 
     FCFileType(const FCFileType &obj);
 
    virtual void terminate(void);
     /*==========================  PRIVATE  ================================*/
   private:
 
     void operator =(const FCFileType &source);
};

typedef FCFileType* FCFileTypeP;

OSG_END_NAMESPACE

#include "OSGFCFileType.inl"

#endif /* _OSGFCFILETYPE_H_ */


