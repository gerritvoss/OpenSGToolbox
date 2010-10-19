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

#ifndef _OSGTEXTFILETYPE_H_
#define _OSGTEXTFILETYPE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTextDomDef.h"

#include <vector>
#include <set>
#include <string>
#include <iostream>

#include "OSGIOFileTypeBase.h"
#include "OSGFieldContainer.h"

#include "OSGDocument.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBTEXTDOM_DLLMAPPING TextFileType : public IOFileTypeBase
{
     /*==========================  PUBLIC  =================================*/
   public:
    typedef IOFileTypeBase Inherited;
    typedef TextFileType  Self;
 
	 typedef std::vector<std::string> ExtensionVector;

     /*---------------------------------------------------------------------*/
	 virtual std::string getName(void) const = 0;
 
     /*---------------------------------------------------------------------*/
     
     /*---------------------------------------------------------------------*/
     virtual ~TextFileType(void);
 
     /*---------------------------------------------------------------------*/
     //void setOptions(const Char8 *options);
 
     
     /*---------------------------------------------------------------------*/
     virtual const ExtensionVector &getSuffixList         (void) const;
 
           // bool                    doOverride         (void);
          //  UInt32                  getOverridePriority(void);
     
     /*---------------------------------------------------------------------*/
     virtual DocumentRefPtr read(std::istream &is,
		                     const std::string& fileNameOrExtension);
 
     /*---------------------------------------------------------------------*/
     virtual bool write(DocumentRefPtr Doc, std::ostream &os,
                        const std::string& fileNameOrExtension);
 
     virtual void print(void);
     /*=========================  PROTECTED  ===============================*/
   protected:
 
     /*---------------------------------------------------------------------*/
	 ExtensionVector _suffixList;
 
    /*! If true loader can override others. */
    //bool                   _override;         
    /*! The priority for overriding. */
    //UInt32                 _overridePriority; 
   
     /*---------------------------------------------------------------------*/
     TextFileType(const ExtensionVector&  suffixArray,
                       // bool    override,
                       // UInt32  overridePriority,
                        UInt32  flags = OSG_READ_SUPPORTED);
 
     TextFileType(const TextFileType &obj);
 
    virtual void terminate(void);
     /*==========================  PRIVATE  ================================*/
   private:
 
     void operator =(const TextFileType &source);
};

typedef TextFileType* TextFileTypeP;

OSG_END_NAMESPACE

#include "OSGTextFileType.inl"

#endif /* _OSGTEXTFILETYPE_H_ */


