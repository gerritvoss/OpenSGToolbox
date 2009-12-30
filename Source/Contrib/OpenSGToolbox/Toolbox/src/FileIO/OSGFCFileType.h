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

#ifndef _OSGFCFILETYPE_H_
#define _OSGFCFILETYPE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"

#include <vector>
#include <set>
#include <string>
#include <iostream>

#include <OpenSG/OSGFieldContainerPtr.h>

OSG_BEGIN_NAMESPACE

class OSG_TOOLBOXLIB_DLLMAPPING FCFileType
{
     /*==========================  PUBLIC  =================================*/
   public:
 
     typedef std::set<FieldContainerPtr> FCPtrStore;
	 typedef std::vector<std::string> ExtensionVector;
     typedef std::vector<UInt32> FCTypeVector;
     /*---------------------------------------------------------------------*/
	 virtual std::string getName(void) const = 0;
 
     /*---------------------------------------------------------------------*/
     enum
     {
         OSG_READ_SUPPORTED = 1,
         OSG_WRITE_SUPPORTED = 2
     };
     
     /*---------------------------------------------------------------------*/
     virtual ~FCFileType(void);
 
     /*---------------------------------------------------------------------*/
     //void setOptions(const Char8 *options);
 
     
     /*---------------------------------------------------------------------*/
     virtual const ExtensionVector &getSuffixList         (void) const;
 
     //        bool                 doOverride         (void);
     //        UInt32               getOverridePriority(void);
             UInt32               getFlags           (void) const;
     
     //        const Char8         *getOptions         (void);
 
     /*---------------------------------------------------------------------*/
     virtual FCPtrStore read(std::istream &is,
		                     const std::string& fileNameOrExtension) const;
 
     /*---------------------------------------------------------------------*/
     virtual bool write(const FCPtrStore &Containers, std::ostream &os,
                        const std::string& fileNameOrExtension, const FCTypeVector& IgnoreTypes) const;
 
     /*=========================  PROTECTED  ===============================*/
   protected:
 
     /*---------------------------------------------------------------------*/
	 ExtensionVector _SuffixList;
 
     //bool                _override;
     //UInt32              _overridePriority;
     UInt32              _Flags;
   
     //std::string         _options;
 
     /*---------------------------------------------------------------------*/
     FCFileType(const ExtensionVector  suffixArray,
                         //bool    override,
                         //UInt32  overridePriority,
                         UInt32  flags = OSG_READ_SUPPORTED);
 
     FCFileType(const FCFileType &obj);
 
     /*==========================  PRIVATE  ================================*/
   private:
 
     void operator =(const FCFileType &source);
};

typedef FCFileType* FCFileTypeP;

OSG_END_NAMESPACE

#include "OSGFCFileType.inl"

#endif /* _OSGFCFILETYPE_H_ */


