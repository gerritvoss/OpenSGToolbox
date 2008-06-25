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

#ifndef _OSGFCFILEHANDLER_H_
#define _OSGFCFILEHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"

#include <vector>
#include <set>
#include <string>
#include <iostream>

#include "OSGFCFileType.h"
#include "Types/OSGPathType.h"

OSG_BEGIN_NAMESPACE

class OSG_TOOLBOXLIB_DLLMAPPING FCFileHandler
{
     /*==========================  PUBLIC  =================================*/
   public:
 
     typedef std::set<FieldContainerPtr> FCPtrStore;
 
     /*---------------------------------------------------------------------*/
     static FCFileHandler *the(void);
 
     /*---------------------------------------------------------------------*/
     virtual ~FCFileHandler(void);
 
     /*---------------------------------------------------------------------*/
	 virtual FCFileTypeP getFileType(const std::string& FileExtension, UInt32 Flags = FCFileType::OSG_READ_SUPPORTED |
                                              FCFileType::OSG_WRITE_SUPPORTED);
 
	 virtual std::vector<std::string> getSuffixList(UInt32 flags = FCFileType::OSG_READ_SUPPORTED |
                                              FCFileType::OSG_WRITE_SUPPORTED) const;
 
     /*---------------------------------------------------------------------*/
     typedef void (*progresscbfp) (UInt32 p);
     void setReadProgressCB(progresscbfp fp);
     progresscbfp getReadProgressCB(void);
 
     /*---------------------------------------------------------------------*/
     virtual FCPtrStore    read(std::istream &InputStream, const std::string& Extension);
  
	 virtual FCPtrStore    read(const  Path& FilePath);
  
     /*---------------------------------------------------------------------*/
	 virtual bool write(const FCPtrStore Containers, std::ostream &OutputStream, const std::string& Extension, const FCFileType::FCTypeVector& IgnoreTypes = FCFileType::FCTypeVector(), bool Compress = false);
     virtual bool write(const FCPtrStore Containers, const Path& FilePath, const FCFileType::FCTypeVector& IgnoreTypes = FCFileType::FCTypeVector(), bool Compress = false);
 
     /*---------------------------------------------------------------------*/
     //virtual bool               setOptions(const Char8 *suffix, const Char8 *options);
     //virtual const Char8        *getOptions(const Char8 *suffix);

     const Path& getRootFilePath(void) const;
 
     /*=========================  PROTECTED  ===============================*/
   protected:
 
     typedef std::vector<FCFileTypeP> FileTypeVector;
	 typedef std::map <std::string, FileTypeVector> FileTypeMap;
 
     /*---------------------------------------------------------------------*/
     static FCFileHandler *_the;
 
            FileTypeMap       _SuffixTypeMap;
 
 
     bool addFCFileType(FCFileTypeP FileType);
     bool subFCFileType(FCFileTypeP FileType);
     
     /*---------------------------------------------------------------------*/
     FCFileHandler(void);
     FCFileHandler(const FCFileHandler &obj);
 
     /*==========================  PRIVATE  ================================*/
   private:
 
     friend class OSG_TOOLBOXLIB_DLLMAPPING FCFileType;
     
     void operator =(const FCFileHandler &source);
 
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

     Path _RootFilePath;
};

typedef FCFileHandler* FCFileHandlerP;

OSG_END_NAMESPACE

#include "OSGFCFileHandler.inl"

#endif /* _OSGFCFILEHANDLER_H_ */
