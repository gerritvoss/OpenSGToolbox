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

#ifndef _OSGFCFILEHANDLER_H_
#define _OSGFCFILEHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include <vector>
#include <set>
#include <string>
#include <iostream>

#include "OSGBaseTypes.h"
#include "OSGFCFileType.h"
#include "OSGPathType.h"
#include "OSGPathHandler.h"
#include "OSGSingletonHolder.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEM_DLLMAPPING FCFileHandlerBase
{
     /*==========================  PUBLIC  =================================*/
   public:
 
     typedef FCFileType::FCPtrStore FCPtrStore;
 
     /*---------------------------------------------------------------------*/
     virtual ~FCFileHandlerBase(void);
 
     /*---------------------------------------------------------------------*/
	 virtual FCFileTypeP getFileType(const std::string& FileExtension, UInt32 Flags = FCFileType::OSG_READ_SUPPORTED |
                                              FCFileType::OSG_WRITE_SUPPORTED);

	 virtual FCFileTypeP getFileType(const BoostPath& FilePath, UInt32 Flags = FCFileType::OSG_READ_SUPPORTED |
                                              FCFileType::OSG_WRITE_SUPPORTED);
 
	 virtual std::vector<std::string> getSuffixList(UInt32 flags = FCFileType::OSG_READ_SUPPORTED |
                                              FCFileType::OSG_WRITE_SUPPORTED) const;
 
     /*---------------------------------------------------------------------*/
     typedef void (*progresscbfp) (UInt32 p);
     void setReadProgressCB(progresscbfp fp);
     progresscbfp getReadProgressCB(void);
 
     /*---------------------------------------------------------------------*/
     virtual FCPtrStore    read(std::istream &InputStream, const std::string& Extension);
  
	 virtual FCPtrStore    read(const  BoostPath& FilePath);

	 virtual FieldContainerUnrecPtr    read(const  BoostPath& FilePath, const FieldContainerType& Type);
  
     /*---------------------------------------------------------------------*/
	 virtual bool write(const FCPtrStore Containers, std::ostream &OutputStream, const std::string& Extension, const FCFileType::FCTypeVector& IgnoreTypes = FCFileType::FCTypeVector(), bool Compress = false);
     virtual bool write(const FCPtrStore Containers, const BoostPath& FilePath, const FCFileType::FCTypeVector& IgnoreTypes = FCFileType::FCTypeVector(), bool Compress = false);
 
	 virtual bool    write(const FieldContainerUnrecPtr Container, const  BoostPath& FilePath, const FCFileType::FCTypeVector& IgnoreTypes = FCFileType::FCTypeVector(), bool Compress = false);
     /*---------------------------------------------------------------------*/
     //virtual bool               setOptions(const Char8 *suffix, const Char8 *options);
     //virtual const Char8        *getOptions(const Char8 *suffix);

     const BoostPath& getRootFilePath(void) const;
 
     /*=========================  PROTECTED  ===============================*/
   protected:
 
     typedef std::vector<FCFileTypeP> FileTypeVector;
	 typedef std::map <std::string, FileTypeVector> FileTypeMap;
 
     /*---------------------------------------------------------------------*/
            FileTypeMap       _SuffixTypeMap;
 
 
     bool addFCFileType(FCFileTypeP FileType);
     bool subFCFileType(FCFileTypeP FileType);
     
     /*---------------------------------------------------------------------*/
     FCFileHandlerBase(void);
     FCFileHandlerBase(const FCFileHandlerBase &obj);
 
     /*==========================  PRIVATE  ================================*/
   private:
 
    template <class SingletonT>
    friend class SingletonHolder;
    
     friend class OSG_SYSTEM_DLLMAPPING FCFileType;
     
     void operator =(const FCFileHandlerBase &source);
 
     typedef struct
     {
         UInt64 length;
         std::istream *is;
     } progressS;
 
     void startReadProgressThread(std::istream &is);
     void stopReadProgressThread(void);
     static void readProgress(void *data);
 
     progresscbfp    _ReadProgressFP;
     progressS       _ProgressData;
     bool            _ReadReady;

     BoostPath _RootFilePath;

	 
	PathHandler   *_pathHandler;
	PathHandler    _defaultPathHandler;
	std::string initPathHandler(const Char8 *filename);
};

typedef SingletonHolder<FCFileHandlerBase> FCFileHandler;

typedef FCFileHandler* FCFileHandlerP;

OSG_END_NAMESPACE

#include "OSGFCFileHandler.inl"

#endif /* _OSGFCFILEHANDLER_H_ */


