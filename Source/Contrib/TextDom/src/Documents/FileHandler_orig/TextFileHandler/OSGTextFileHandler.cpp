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

#include "OSGTextFileHandler.h"
#include <fstream>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/algorithm/string.hpp>

#include "OSGSingletonHolder.ins"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TextFileHandlerBase
A TextFileHandlerBase. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_SINGLETON_INST(TextFileHandlerBase, addPostFactoryExitFunction)

template class SingletonHolder<TextFileHandlerBase>;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

bool TextFileHandlerBase::addTextFileType(TextFileTypeP FileType)
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

        FileSuffixMapSearch = TextFileHandler::the()->_SuffixTypeMap.find(Suffix);

        if (FileSuffixMapSearch != TextFileHandler::the()->_SuffixTypeMap.end())
        {
            TextFileHandler::the()->_SuffixTypeMap[Suffix].push_back(FileType);

            SWARNING << "Added an file type with suffix "
                     << Suffix
                     << " non overriding at the end of the list"
                     << std::endl;
        }
        else
        {
            FileTypeVector pTmpList;

            pTmpList.push_back(FileType);

            TextFileHandler::the()->_SuffixTypeMap[Suffix] = pTmpList;

            retCode = true;
        }
    }

    return retCode;
}

bool TextFileHandlerBase::subTextFileType(TextFileTypeP FileType)
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

        FileSuffixMapSearch = TextFileHandler::the()->_SuffixTypeMap.find(Suffix);
        if (FileSuffixMapSearch != TextFileHandler::the()->_SuffixTypeMap.end())
        {
            TextFileHandler::the()->_SuffixTypeMap.erase(FileSuffixMapSearch);
            retCode = true;
        }
    }
    return retCode;
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

TextFileTypeP TextFileHandlerBase::getFileType(const std::string& FileExtension, UInt32 Flags)
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

std::vector<std::string> TextFileHandlerBase::getSuffixList(UInt32 flags) const
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

 void TextFileHandlerBase::setReadProgressCB(progresscbfp fp)
 {
	 stopReadProgressThread();
     _ReadProgressFP = fp;
 }

 TextFileHandlerBase::progresscbfp TextFileHandlerBase::getReadProgressCB(void)
 {
	 return _ReadProgressFP;
 }


 DocumentRefPtr TextFileHandlerBase::read(std::istream &InputStream, const std::string& Extension)
 {
	 DocumentRefPtr Result;
	 //Get the FileType for this extension
	 TextFileTypeP TheFileType(getFileType(Extension, TextFileType::OSG_READ_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "TextFileHandlerBase::read(): Cannot read Field Container stream, because no File types support " << Extension <<  " extension." << std::endl;
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

 DocumentRefPtr TextFileHandlerBase::read(const BoostPath& FilePath)
 {
	 DocumentRefPtr Result;
	 //Determine if the file exists
	 if(!boost::filesystem::exists(FilePath))
	 {
		SWARNING << "TextFileHandlerBase::read(): " << FilePath.string() << " does not exists." << std::endl;
		return Result;
	 }

	 //Determine the file extension
	 std::string Extension(boost::filesystem::extension(FilePath));
	 boost::algorithm::trim_if(Extension,boost::is_any_of("."));

     //Get the Parent Directory Path of the file
     _RootFilePath = FilePath;
     _RootFilePath.remove_leaf();

	 //Get the FileType for this extension
	 TextFileTypeP TheFileType(getFileType(Extension, TextFileType::OSG_READ_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "TextFileHandlerBase::read(): Cannot read Field Container file: " << FilePath.string() << ", because no File types support " << Extension <<  " extension." << std::endl;
		return Result;
	 }
	 else
	 {
		 //Open up the input stream of the file
		 std::ifstream InputStream(FilePath.string().c_str(), std::ios::binary);

		 if(!InputStream)
		 {
			SWARNING << "TextFileHandlerBase::read(): Couldn't open input stream for file " << FilePath.string() << std::endl;
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

 
 DocumentRefPtr TextFileHandlerBase::forceRead(const BoostPath& FilePath)
 {
	 DocumentRefPtr Result;
	 //Determine if the file exists
	 if(!boost::filesystem::exists(FilePath))
	 {
		SWARNING << "TextFileHandlerBase::read(): " << FilePath.string() << " does not exists." << std::endl;
		return Result;
	 }

	 //Determine the file extension
	 std::string Extension(boost::filesystem::extension(FilePath));
	 boost::algorithm::trim_if(Extension,boost::is_any_of("."));

     //Get the Parent Directory Path of the file
     _RootFilePath = FilePath;
     _RootFilePath.remove_leaf();

	 //Get the FileType of a "txt" file (Forcing the document to be opened as a txt file)
	 TextFileTypeP TheFileType(getFileType("txt", TextFileType::OSG_READ_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "TextFileHandlerBase::read(): Cannot read Field Container file: " << FilePath.string() << ", because no File types support " << Extension <<  " extension." << std::endl;
		return Result;
	 }
	 else
	 {
		 //Open up the input stream of the file
		 std::ifstream InputStream(FilePath.string().c_str(), std::ios::binary);

		 if(!InputStream)
		 {
			SWARNING << "TextFileHandlerBase::read(): Couldn't open input stream for file " << FilePath.string() << std::endl;
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

bool TextFileHandlerBase::write(DocumentRefPtr Doc, std::ostream &OutputStream, const std::string& Extension,bool Compress)
{
	 //Get the FileType for this extension
	 TextFileTypeP TheFileType(getFileType(Extension, TextFileType::OSG_WRITE_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "TextFileHandlerBase::write(): Cannot write Field Container outstream, because no File types support " << Extension <<  " extension." << std::endl;
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
		 return TheFileType->write(Doc, OutputStream, Extension);
	 }
}

bool TextFileHandlerBase::write(DocumentRefPtr Doc, const BoostPath& FilePath, bool Compress)
{
	 //Determine the file extension
	 std::string Extension(boost::filesystem::extension(FilePath));
	 boost::algorithm::trim_if(Extension,boost::is_any_of("."));

	 _RootFilePath = FilePath;
     _RootFilePath.remove_filename();

	 //Get the FileType for this extension
	 TextFileTypeP TheFileType(getFileType(Extension, TextFileType::OSG_WRITE_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "TextFileHandlerBase::write(): Cannot write Field Container file: " << FilePath.string() << ", because no File types support " << Extension <<  " extension." << std::endl;
		return false;
	 }
	 else
	 {
		 //Open up the input stream of the file
		 std::ofstream OutputStream(FilePath.string().c_str(), std::ios::binary);

		 if(!OutputStream)
		 {
			SWARNING << "TextFileHandlerBase::write(): Couldn't open output stream for file " << FilePath.string() << std::endl;
			return false;
		 }
		 else
		 {
			 bool Result;
			 Result = write(Doc, OutputStream, Extension, Compress);
			 OutputStream.close();
			 return Result;
		 }
	 }
}


bool TextFileHandlerBase::forceWrite(DocumentRefPtr Doc, const BoostPath& FilePath, bool Compress)
{
	 //Determine the file extension
	 std::string Extension(boost::filesystem::extension(FilePath));
	 boost::algorithm::trim_if(Extension,boost::is_any_of("."));

	 _RootFilePath = FilePath;
     _RootFilePath.remove_filename();

	 //Get the FileType for this extension
	 TextFileTypeP TheFileType(getFileType("txt", TextFileType::OSG_WRITE_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "TextFileHandlerBase::write(): Cannot write Field Container file: " << FilePath.string() << ", because no File types support " << Extension <<  " extension." << std::endl;
		return false;
	 }
	 else
	 {
		 //Open up the output stream of the file
		 std::ofstream OutputStream(FilePath.string().c_str(), std::ios::binary);

		 if(!OutputStream)
		 {
			SWARNING << "TextFileHandlerBase::write(): Couldn't open output stream for file " << FilePath.string() << std::endl;
			return false;
		 }
		 else
		 {
			 bool Result;
			 Result = write(Doc, OutputStream, "txt", Compress);
			 OutputStream.close();
			 return Result;
		 }
	 }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void TextFileHandlerBase::startReadProgressThread(std::istream &is)
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

void TextFileHandlerBase::stopReadProgressThread(void)
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

void TextFileHandlerBase::readProgress(void *data)
{
    UInt32 p = 0;
    while(p < 100 && !TextFileHandler::the()->_ReadReady)
    {
        if(!TextFileHandler::the()->_ProgressData.is->eof() &&
           !TextFileHandler::the()->_ProgressData.is->bad())
        {
            UInt64 pos = TextFileHandler::the()->_ProgressData.is->tellg();
            p = UInt32((pos * 100) / TextFileHandler::the()->_ProgressData.length);
            if(p > 100)
                p = 100;
        }
        else
        {
            p = 100;
        }

        TextFileHandler::the()->_ReadProgressFP(p);
        osgSleep(100);
    }
    if(p < 100)
        TextFileHandler::the()->_ReadProgressFP(100);
}

/*----------------------- constructors & destructors ----------------------*/

TextFileHandlerBase::TextFileHandlerBase(void) :
    _ReadProgressFP(NULL),
    _ProgressData(),
    _ReadReady(false)
{
}

TextFileHandlerBase::TextFileHandlerBase(const TextFileHandlerBase &obj)
{
	SWARNING << "In TextFileHandlerBase copy constructor" << std::endl;
}

TextFileHandlerBase::~TextFileHandlerBase(void)
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

