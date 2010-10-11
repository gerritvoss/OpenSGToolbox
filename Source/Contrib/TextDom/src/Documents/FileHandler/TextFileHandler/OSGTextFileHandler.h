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

#ifndef _OSGTEXTFILEHANDLER_H_
#define _OSGTEXTFILEHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTextDomDef.h"

#include <vector>
#include <set>
#include <string>
#include <iostream>

#include "OSGBaseTypes.h"
#include "OSGTextFileType.h"
#include "OSGPathType.h"
#include "OSGSingletonHolder.h"

#include "OSGDocument.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBTEXTDOM_DLLMAPPING TextFileHandlerBase
{
     /*==========================  PUBLIC  =================================*/
   public:
 
     /*---------------------------------------------------------------------*/
     virtual ~TextFileHandlerBase(void);
 
     /*---------------------------------------------------------------------*/
	 virtual TextFileTypeP getFileType(const std::string& FileExtension, UInt32 Flags = TextFileType::OSG_READ_SUPPORTED |
                                              TextFileType::OSG_WRITE_SUPPORTED);
 
	 virtual std::vector<std::string> getSuffixList(UInt32 flags = TextFileType::OSG_READ_SUPPORTED |
                                              TextFileType::OSG_WRITE_SUPPORTED) const;
 
     /*---------------------------------------------------------------------*/
     typedef void (*progresscbfp) (UInt32 p);
     void setReadProgressCB(progresscbfp fp);
     progresscbfp getReadProgressCB(void);
 
     /*---------------------------------------------------------------------*/
     virtual DocumentTransitPtr		read(std::istream &InputStream, const std::string& Extension);
  
	 virtual DocumentTransitPtr		read(const  BoostPath& FilePath);
	
	 virtual DocumentTransitPtr		forceRead(const  BoostPath& FilePath);
	 

  
     /*---------------------------------------------------------------------*/
	 virtual bool write(Document* const Doc, std::ostream &OutputStream, const std::string& Extension,bool Compress = false);
     virtual bool write(Document* const Doc, const BoostPath& FilePath, bool Compress = false);
	 virtual bool forceWrite(Document* const Doc, const BoostPath& FilePath, bool Compress = false);
 
     /*---------------------------------------------------------------------*/
     //virtual bool               setOptions(const Char8 *suffix, const Char8 *options);
     //virtual const Char8        *getOptions(const Char8 *suffix);

     const BoostPath& getRootFilePath(void) const;
 
     /*=========================  PROTECTED  ===============================*/
   protected:
 
     typedef std::vector<TextFileTypeP> FileTypeVector;
	 typedef std::map <std::string, FileTypeVector> FileTypeMap;
 
     /*---------------------------------------------------------------------*/
            FileTypeMap       _SuffixTypeMap;
 
 
     bool addTextFileType(TextFileTypeP FileType);
     bool subTextFileType(TextFileTypeP FileType);
     
     /*---------------------------------------------------------------------*/
     TextFileHandlerBase(void);
     TextFileHandlerBase(const TextFileHandlerBase &obj);
 
     /*==========================  PRIVATE  ================================*/
   private:
 
    template <class SingletonT>
    friend class SingletonHolder;
    
     friend class OSG_CONTRIBTEXTDOM_DLLMAPPING TextFileType;
     
     void operator =(const TextFileHandlerBase &source);
 
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
};

typedef SingletonHolder<TextFileHandlerBase> TextFileHandler;

typedef TextFileHandler* TextFileHandlerP;

OSG_END_NAMESPACE

#include "OSGTextFileHandler.inl"

#endif /* _OSGTextFILEHANDLER_H_ */


