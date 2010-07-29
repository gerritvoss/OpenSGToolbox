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

#include "OSGConfig.h"

#include "OSGFCFileHandler.h"
#include <fstream>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/algorithm/string.hpp>

#include "OSGSingletonHolder.ins"
#include "OSGImageFileHandler.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FCFileHandlerBase
A FCFileHandlerBase. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_SINGLETON_INST(FCFileHandlerBase, addPostFactoryExitFunction)

template class SingletonHolder<FCFileHandlerBase>;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

bool FCFileHandlerBase::addFCFileType(FCFileTypeP FileType)
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

        FileSuffixMapSearch = FCFileHandler::the()->_SuffixTypeMap.find(Suffix);

        if (FileSuffixMapSearch != FCFileHandler::the()->_SuffixTypeMap.end())
        {
            FCFileHandler::the()->_SuffixTypeMap[Suffix].push_back(FileType);

            SWARNING << "Added an file type with suffix "
                     << Suffix
                     << " non overriding at the end of the list"
                     << std::endl;
        }
        else
        {
            FileTypeVector pTmpList;

            pTmpList.push_back(FileType);

            FCFileHandler::the()->_SuffixTypeMap[Suffix] = pTmpList;

            retCode = true;
        }
    }

    return retCode;
}

bool FCFileHandlerBase::subFCFileType(FCFileTypeP FileType)
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

        FileSuffixMapSearch = FCFileHandler::the()->_SuffixTypeMap.find(Suffix);
        if (FileSuffixMapSearch != FCFileHandler::the()->_SuffixTypeMap.end())
        {
            FCFileHandler::the()->_SuffixTypeMap.erase(FileSuffixMapSearch);
            retCode = true;
        }
    }
    return retCode;
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

FCFileTypeP FCFileHandlerBase::getFileType(const std::string& FileExtension, UInt32 Flags)
{
    //Check if this is a FileName or just the file extension

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

std::vector<std::string> FCFileHandlerBase::getSuffixList(UInt32 flags) const
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

 void FCFileHandlerBase::setReadProgressCB(progresscbfp fp)
 {
	 stopReadProgressThread();
     _ReadProgressFP = fp;
 }

 FCFileHandlerBase::progresscbfp FCFileHandlerBase::getReadProgressCB(void)
 {
	 return _ReadProgressFP;
 }

 FieldContainerUnrecPtr FCFileHandlerBase::read(const  BoostPath& FilePath, const FieldContainerType& Type)
 {
    FCPtrStore Containers;
    Containers = read(FilePath);

    FCPtrStore::iterator ContainerItor;
    for(ContainerItor = Containers.begin(); ContainerItor != Containers.end(); ++ContainerItor)
    {
        if((*ContainerItor)->getType() == Type)
        {
            return (*ContainerItor);
            break;
        }
    }
    return NULL;
 }
 
 bool FCFileHandlerBase::write(const FieldContainerUnrecPtr Container, const  BoostPath& FilePath, const FCFileType::FCTypeVector& IgnoreTypes, bool Compress)
 {
	FCPtrStore Containers;
	Containers.insert(Container);

	//Save the Field Containers to a file
	return write(Containers,FilePath, IgnoreTypes, Compress);
 }


 FCFileHandlerBase::FCPtrStore FCFileHandlerBase::read(std::istream &InputStream, const std::string& Extension)
 {
	 FCPtrStore Result;
	 //Get the FileType for this extension
	 FCFileTypeP TheFileType(getFileType(Extension, FCFileType::OSG_READ_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "FCFileHandlerBase::read(): Cannot read Field Container stream, because no File types support " << Extension <<  " extension." << std::endl;
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

FCFileTypeP  FCFileHandlerBase::getFileType(const BoostPath& FilePath, UInt32 Flags)
{
	 //Determine the file extension
	 std::string Extension(boost::filesystem::extension(FilePath.string()));
	 boost::algorithm::trim_if(Extension,boost::is_any_of("."));

     return getFileType(Extension, Flags);
}

 FCFileHandlerBase::FCPtrStore FCFileHandlerBase::read(const BoostPath& FilePath)
 {
	 FCPtrStore Result;
	 //Determine if the file exists
	 if(!boost::filesystem::exists(FilePath))
	 {
		SWARNING << "FCFileHandlerBase::read(): " << FilePath.string() << " does not exists." << std::endl;
		return Result;
	 }

	 std::string filename = initPathHandler(FilePath.string().c_str());

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
		SWARNING << "FCFileHandlerBase::read(): Cannot read Field Container file: " << FilePath.string() << ", because no File types support " << Extension <<  " extension." << std::endl;
		return Result;
	 }
	 else
	 {
		 //Open up the input stream of the file
		 std::ifstream InputStream(FilePath.string().c_str(), std::ios::binary);

		 if(!InputStream)
		 {
			SWARNING << "FCFileHandlerBase::read(): Couldn't open input stream for file " << FilePath.string() << std::endl;
			return Result;
		 }
		 else
		 {
             //Read from the input stream
             startReadProgressThread(InputStream);
             Result = TheFileType->read(InputStream, FilePath.string());
             stopReadProgressThread();
             
			 InputStream.close();
		 }
	 }

	 return Result;
 }

bool FCFileHandlerBase::write(const FCPtrStore Containers, std::ostream &OutputStream, const std::string& Extension, const FCFileType::FCTypeVector& IgnoreTypes, bool Compress)
{
	 //Get the FileType for this extension
	 FCFileTypeP TheFileType(getFileType(Extension, FCFileType::OSG_WRITE_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "FCFileHandlerBase::write(): Cannot write Field Container outstream, because no File types support " << Extension <<  " extension." << std::endl;
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

bool FCFileHandlerBase::write(const FCPtrStore Containers, const BoostPath& FilePath, const FCFileType::FCTypeVector& IgnoreTypes, bool Compress)
{
	 //Determine the file extension
	 std::string Extension(boost::filesystem::extension(FilePath));
	 boost::algorithm::trim_if(Extension,boost::is_any_of("."));

	 _RootFilePath = FilePath;
     _RootFilePath.remove_filename();

	 //Get the FileType for this extension
	 FCFileTypeP TheFileType(getFileType(Extension, FCFileType::OSG_WRITE_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "FCFileHandlerBase::write(): Cannot write Field Container file: " << FilePath.string() << ", because no File types support " << Extension <<  " extension." << std::endl;
		return false;
	 }
	 else
	 {
		 //Open up the input stream of the file
		 std::ofstream OutputStream(FilePath.string().c_str(), std::ios::binary);

		 if(!OutputStream)
		 {
			SWARNING << "FCFileHandlerBase::write(): Couldn't open output stream for file " << FilePath.string() << std::endl;
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

void FCFileHandlerBase::startReadProgressThread(std::istream &is)
{
    if(_ReadProgressFP == NULL)
        return;

    // get length of the stream.
    _ProgressData.is = &is;
    is.seekg(0, std::ios::end);
    _ProgressData.length = is.tellg();
    is.seekg(0, std::ios::beg);

    ThreadRefPtr pt = dynamic_cast<Thread *>(
            ThreadManager::the()->findThread("OSG::FileIOReadProgressThread"));

    if(pt == NULL)
        pt = dynamic_pointer_cast<Thread>(
                ThreadManager::the()->getThread("OSG::FileIOReadProgressThread",1));

    _ReadReady = false;
    if(pt != NULL)
        pt->runFunction(readProgress, 0, NULL);
    else
        SWARNING << "Couldn't create read progress thread!" << std::endl;
}

void FCFileHandlerBase::stopReadProgressThread(void)
{
    if(_ReadProgressFP == NULL)
        return;

    Thread* pt = dynamic_cast<Thread *>(
            ThreadManager::the()->findThread("OSG::FileIOReadProgressThread"));

    if(pt != NULL)
    {
        // terminate thread
        _ReadReady = true;
        Thread::join(pt);
    }
}

void FCFileHandlerBase::readProgress(void *data)
{
    UInt32 p = 0;
    while(p < 100 && !FCFileHandler::the()->_ReadReady)
    {
        if(!FCFileHandler::the()->_ProgressData.is->eof() &&
           !FCFileHandler::the()->_ProgressData.is->bad())
        {
            UInt64 pos = FCFileHandler::the()->_ProgressData.is->tellg();
            p = UInt32((pos * 100) / FCFileHandler::the()->_ProgressData.length);
            if(p > 100)
                p = 100;
        }
        else
        {
            p = 100;
        }

        FCFileHandler::the()->_ReadProgressFP(p);
        osgSleep(100);
    }
    if(p < 100)
        FCFileHandler::the()->_ReadProgressFP(100);
}

std::string FCFileHandlerBase::initPathHandler(const Char8 *filename) 
{
	std::string fullFilePath;
	if(_pathHandler != NULL)
    {
        // Set an image path handler if not set.
		if(ImageFileHandler::the()->getPathHandler() == NULL)
        {
            ImageFileHandler::the()->setPathHandler(_pathHandler);
        }
		fullFilePath = _pathHandler->findFile(filename);
    }
    else
    {	
        // Set a default image path handler if not set.
        if(ImageFileHandler::the()->getPathHandler() == NULL)
        {
            ImageFileHandler::the()->setPathHandler(&_defaultPathHandler);
        }

        _defaultPathHandler.clearPathList();
        _defaultPathHandler.clearBaseFile();

        _defaultPathHandler.push_frontCurrentDir(        );

		std::string fullFilePath = _defaultPathHandler.findFile(filename);

        _defaultPathHandler.setBaseFile(fullFilePath.c_str());
    }

	return fullFilePath;
}

/*----------------------- constructors & destructors ----------------------*/

FCFileHandlerBase::FCFileHandlerBase(void) :
    _ReadProgressFP(NULL),
    _ProgressData(),
    _ReadReady(false),
	_pathHandler(NULL),
    _defaultPathHandler()
{
}

FCFileHandlerBase::FCFileHandlerBase(const FCFileHandlerBase &obj)
{
	SWARNING << "In FCFileHandlerBase copy constructor" << std::endl;
}

FCFileHandlerBase::~FCFileHandlerBase(void)
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

