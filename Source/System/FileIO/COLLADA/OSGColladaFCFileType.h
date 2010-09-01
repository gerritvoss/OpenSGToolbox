/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *      contact: Daniel Guilliams (dan.guilliams@gmail.com)                  *
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
#ifndef _OSGColladaFCFILETYPE_H_
#define _OSGColladaFCFILETYPE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGTBFileIODef.h"

#include <boost/function.hpp>
#include <utility>
#include "OSGFCFileType.h"
#include "OSGFCFileHandler.h"
#include "OSGContainerIdMapper.h"
#include "OSGFieldContainer.h"
#include "OSGPathHandler.h"



OSG_BEGIN_NAMESPACE


class OSG_TBFILEIO_DLLMAPPING ColladaFCFileType : public FCFileType
{
/*========================== PUBLIC =================================*/
public:
    struct FCIdMapper;
    friend struct FCIdMapper;
     /*---------------------------------------------------------------------*/
virtual std::string getName(void) const;
 
     /*---------------------------------------------------------------------*/
     
     /*---------------------------------------------------------------------*/
     ColladaFCFileType(void);
     ColladaFCFileType(const ColladaFCFileType &obj);
     virtual ~ColladaFCFileType(void);
 
     /*---------------------------------------------------------------------*/
     //void setOptions(const Char8 *options);

   /* Inherited typedefs
* typedef FCFileType::FCPtrStore FCPtrStore;
* typedef std::vector<std::string> ExtensionVector;
* typedef std::vector<UInt32> FCTypeVector;
*/
     

     /*---------------------------------------------------------------------*/
     virtual FCPtrStore read(std::istream &is,
     const std::string& fileNameOrExtension) const;
 
     /*---------------------------------------------------------------------*/
     virtual bool write(const FCPtrStore &Containers, std::ostream &os,
                        const std::string& fileNameOrExtension, const FCTypeVector& IgnoreTypes) const;

protected:

typedef FCFileType Inherited;
// this is a singleton class
static ColladaFCFileType* _the;


private:
// path handlers for images & such



void operator =(const ColladaFCFileType &source);
};

typedef ColladaFCFileType* ColladaFCFileTypeP;

OSG_END_NAMESPACE

#include "OSGColladaFCFileType.inl"

#endif /* _OSGColladaFCFILETYPE_H_ */


