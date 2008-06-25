/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGFCFileHandler.h"
#include <fstream>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/algorithm/string.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FCFileHandler
A FCFileHandler. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
FCFileHandler * FCFileHandler::_the = FCFileHandler::the();
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

FCFileHandler* FCFileHandler::the(void)
{
	if(_the == NULL)
	{
		_the = new FCFileHandler();
	}
	else
	{
		return _the;
	}
}

bool FCFileHandler::addFCFileType(FCFileTypeP FileType)
{
    bool retCode = false;

	std::vector<std::string>::const_iterator FileSuffixItor;
         FileTypeMap   ::iterator FileSuffixMapSearch;

	std::string Suffix;

	for(  FileSuffixItor  = FileType->getSuffixList().begin();
          FileSuffixItor != FileType->getSuffixList().end();
        ++FileSuffixItor)
    {
        Suffix = (*FileSuffixItor);
		boost::algorithm::to_lower(Suffix);

        FileSuffixMapSearch = the()->_SuffixTypeMap.find(Suffix);

        if (FileSuffixMapSearch != the()->_SuffixTypeMap.end())
        {
            the()->_SuffixTypeMap[Suffix].push_back(FileType);

            SWARNING << "Added an file type with suffix "
                     << Suffix
                     << " non overriding at the end of the list"
                     << std::endl;
        }
        else
        {
            FileTypeVector pTmpList;

            pTmpList.push_back(FileType);

            the()->_SuffixTypeMap[Suffix] = pTmpList;

            retCode = true;
        }
    }

    return retCode;
}

bool FCFileHandler::subFCFileType(FCFileTypeP FileType)
{
    bool retCode = false;

	std::vector<std::string>::const_iterator FileSuffixItor;
         FileTypeMap   ::iterator FileSuffixMapSearch;

    std::string Suffix;

    for(  FileSuffixItor  = FileType->getSuffixList().begin();
          FileSuffixItor != FileType->getSuffixList().end();
        ++FileSuffixItor)
    {
        Suffix = (*FileSuffixItor);
		boost::algorithm::to_lower(Suffix);

        FileSuffixMapSearch = the()->_SuffixTypeMap.find(Suffix);
        if (FileSuffixMapSearch != the()->_SuffixTypeMap.end())
        {
            the()->_SuffixTypeMap.erase(FileSuffixMapSearch);
            retCode = true;
        }
    }
    return retCode;
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

FCFileTypeP FCFileHandler::getFileType(const std::string& FileExtension, UInt32 Flags)
{
	FileTypeMap::const_iterator SearchItor(_SuffixTypeMap.find(FileExtension));

	if(SearchItor != _SuffixTypeMap.end())
	{
		for(FileTypeVector::const_iterator VecItor(SearchItor->second.begin()) ; VecItor != SearchItor->second.end() ; ++VecItor)
		{
			if((*VecItor)->getFlags() & Flags)
			{
				return (*VecItor);
			}
		}
		return NULL;
	}
	else
	{
		return NULL;
	}
}

std::vector<std::string> FCFileHandler::getSuffixList(UInt32 flags) const
{
	std::vector<std::string> FileTypesResult;

	for(FileTypeMap::const_iterator MapItor(_SuffixTypeMap.begin()) ; MapItor != _SuffixTypeMap.end() ; ++MapItor)
	{
		for(FileTypeVector::const_iterator VecItor(MapItor->second.begin()) ; VecItor != MapItor->second.end() ; ++VecItor)
		{
			if((*VecItor)->getFlags() & flags)
			{
				std::vector<std::string> Suffixes((*VecItor)->getSuffixList());
				for(std::vector<std::string>::const_iterator SuffixItor(Suffixes.begin()) ; SuffixItor<Suffixes.end() ; ++SuffixItor)
				{
					FileTypesResult.push_back(*SuffixItor);
				}
			}
		}
	}

	return FileTypesResult;
}

 void FCFileHandler::setReadProgressCB(progresscbfp fp)
 {
	 stopReadProgressThread();
     _ReadProgressFP = fp;
 }

 FCFileHandler::progresscbfp FCFileHandler::getReadProgressCB(void)
 {
	 return _ReadProgressFP;
 }

 FCFileHandler::FCPtrStore FCFileHandler::read(std::istream &InputStream, const std::string& Extension)
 {
	 FCPtrStore Result;
	 //Get the FileType for this extension
	 FCFileTypeP TheFileType(getFileType(Extension, FCFileType::OSG_READ_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "Cannot read Field Container stream, because no File types support " << Extension <<  " extension." << std::endl;
		return Result;
	 }
	 else
	 {
		 //Read from the input stream
		 startReadProgressThread(InputStream);
		 Result = TheFileType->read(InputStream, Extension);
		 stopReadProgressThread();
	 }
	 return Result;
 }

 FCFileHandler::FCPtrStore FCFileHandler::read(const Path& FilePath)
 {
	 FCPtrStore Result;
	 //Determine if the file exists
	 if(!boost::filesystem::exists(FilePath))
	 {
		SWARNING << "FC File: " << FilePath.string() << " does not exists." << std::endl;
		return Result;
	 }

	 //Determine the file extension
	 std::string Extension(boost::filesystem::extension(FilePath));
	 boost::algorithm::trim_if(Extension,boost::is_any_of("."));

     //Get the Parent Directory Path of the file
     _RootFilePath = FilePath;
     _RootFilePath.remove_leaf();

	 //Get the FileType for this extension
	 FCFileTypeP TheFileType(getFileType(Extension, FCFileType::OSG_READ_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "Cannot read Field Container file: " << FilePath.string() << ", because no File types support " << Extension <<  " extension." << std::endl;
		return Result;
	 }
	 else
	 {
		 //Open up the input stream of the file
		 std::ifstream InputStream(FilePath.string().c_str(), std::ios::binary);

		 if(!InputStream)
		 {
			SWARNING << "Couldn't open input stream for file " << FilePath.string() << std::endl;
			return Result;
		 }
		 else
		 {
			 Result = read(InputStream, Extension);
			 InputStream.close();
		 }
	 }

	 return Result;
 }

bool FCFileHandler::write(const FCPtrStore Containers, std::ostream &OutputStream, const std::string& Extension, const FCFileType::FCTypeVector& IgnoreTypes, bool Compress)
{
	 //Get the FileType for this extension
	 FCFileTypeP TheFileType(getFileType(Extension, FCFileType::OSG_WRITE_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "Cannot write Field Container outstream, because no File types support " << Extension <<  " extension." << std::endl;
		return false;
	 }
	 else
	 {
		 if(Compress)
		 {
		 }
		 else
		 {
		 }
		 return TheFileType->write(Containers, OutputStream, Extension, IgnoreTypes);
	 }
}

bool FCFileHandler::write(const FCPtrStore Containers, const Path& FilePath, const FCFileType::FCTypeVector& IgnoreTypes, bool Compress)
{
	 //Determine the file extension
	 std::string Extension(boost::filesystem::extension(FilePath));
	 boost::algorithm::trim_if(Extension,boost::is_any_of("."));

	 //Get the FileType for this extension
	 FCFileTypeP TheFileType(getFileType(Extension, FCFileType::OSG_WRITE_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "Cannot write Field Container file: " << FilePath.string() << ", because no File types support " << Extension <<  " extension." << std::endl;
		return false;
	 }
	 else
	 {
		 //Open up the input stream of the file
		 std::ofstream OutputStream(FilePath.string().c_str(), std::ios::binary);

		 if(!OutputStream)
		 {
			SWARNING << "Couldn't open output stream for file " << FilePath.string() << std::endl;
			return false;
		 }
		 else
		 {
			 bool Result;
			 Result = write(Containers, OutputStream, Extension, IgnoreTypes, Compress);
			 OutputStream.close();
			 return Result;
		 }
	 }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void FCFileHandler::startReadProgressThread(std::istream &is)
{
    if(_ReadProgressFP == NULL)
        return;

    // get length of the stream.
    _ProgressData.is = &is;
    is.seekg(0, std::ios::end);
    _ProgressData.length = is.tellg();
    is.seekg(0, std::ios::beg);

    Thread *pt = Thread::find("osg::FileIOReadProgressThread");
    if(pt == NULL)
        pt = OSG::Thread::get("osg::FileIOReadProgressThread");

    _ReadReady = false;
    if(pt != NULL)
        pt->runFunction(readProgress, 0, NULL);
    else
        SWARNING << "Couldn't create read progress thread!" << std::endl;
}

void FCFileHandler::stopReadProgressThread(void)
{
    if(_ReadProgressFP == NULL)
        return;

    Thread *pt = Thread::find("osg::FileIOReadProgressThread");

    if(pt != NULL)
    {
        // terminate thread
        _ReadReady = true;
        Thread::join(pt);
    }
}

void FCFileHandler::readProgress(void *data)
{
    UInt32 p = 0;
    while(p < 100 && !the()->_ReadReady)
    {
        if(!the()->_ProgressData.is->eof() &&
           !the()->_ProgressData.is->bad())
        {
            UInt64 pos = the()->_ProgressData.is->tellg();
            p = UInt32((pos * 100) / the()->_ProgressData.length);
            if(p > 100)
                p = 100;
        }
        else
        {
            p = 100;
        }

        the()->_ReadProgressFP(p);
        osgsleep(100);
    }
    if(p < 100)
        the()->_ReadProgressFP(100);
}

/*----------------------- constructors & destructors ----------------------*/

FCFileHandler::FCFileHandler(void) :
    _ReadProgressFP(NULL),
    _ProgressData(),
    _ReadReady(false)
{
}

FCFileHandler::FCFileHandler(const FCFileHandler &obj)
{
	SWARNING << "In FCFileHandler copy constructor" << std::endl;
}

FCFileHandler::~FCFileHandler(void)
{
}

/*----------------------------- class specific ----------------------------*/

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

