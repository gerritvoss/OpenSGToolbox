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
#include "OSGStringUtils.h"
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGAttachmentContainer.h>
#include <OpenSG/OSGNode.h>
#include "OSGGLenumUtils.h"
#include "Types/OSGPathType.h"

OSG_BEGIN_NAMESPACE


std::string addStringBetweenUpperCaseChange(const std::string& Source, const std::string& Pad)
{
	std::string Result(Source);
	
	for (UInt32 i(0); i < Result.size() - 2; ++i)
	{
		if ((97 <= Result[i] && Result[i] <= 122) && (65 <= Result[i + 1] && Result[i + 1] <= 90))
		{
			Result.insert(i+1, Pad);
		}
	}
	
	return Result;
}

std::string lexical_cast(const boost::any& Source)
{
    if(Source.type() == typeid(std::string))  //String
    {
        return boost::any_cast<std::string>(Source);
    }
    else if(Source.type() == typeid(Char8*))   //Char8 *
    {
        return std::string(boost::any_cast<Char8*>(Source));
    }
    //Numbers
    else if(Source.type() == typeid(UInt8))   //UInt8
    {
        return boost::lexical_cast<std::string>(boost::any_cast<UInt8>(Source));
    }
    else if(Source.type() == typeid(UInt16))   //UInt16
    {
        return boost::lexical_cast<std::string>(boost::any_cast<UInt16>(Source));
    }
    else if(Source.type() == typeid(UInt32))   //UInt32
    {
        return boost::lexical_cast<std::string>(boost::any_cast<UInt32>(Source));
    }
    else if(Source.type() == typeid(UInt64))   //UInt64
    {
        return boost::lexical_cast<std::string>(boost::any_cast<UInt64>(Source));
    }
    else if(Source.type() == typeid(Int8))   //Int8
    {
        return boost::lexical_cast<std::string>(boost::any_cast<Int8>(Source));
    }
    else if(Source.type() == typeid(Int16))   //Int16
    {
        return boost::lexical_cast<std::string>(boost::any_cast<Int16>(Source));
    }
    else if(Source.type() == typeid(Int32))   //Int32
    {
        return boost::lexical_cast<std::string>(boost::any_cast<Int32>(Source));
    }
    else if(Source.type() == typeid(Int64))   //Int64
    {
        return boost::lexical_cast<std::string>(boost::any_cast<Int64>(Source));
    }
    else if(Source.type() == typeid(Real32))   //Real32
    {
        return boost::lexical_cast<std::string>(boost::any_cast<Real32>(Source));
    }
    else if(Source.type() == typeid(Real64))   //Real64
    {
        return boost::lexical_cast<std::string>(boost::any_cast<Real64>(Source));
    }
    else if(Source.type() == typeid(Real128))   //Real128
    {
        return boost::lexical_cast<std::string>(boost::any_cast<Real128>(Source));
    }
    
    else if(Source.type() == typeid(Char8))   //Char8
    {
        return boost::lexical_cast<std::string>(boost::any_cast<Char8>(Source));
    }
    else if(Source.type() == typeid(UChar8))   //UChar8
    {
        return boost::lexical_cast<std::string>(boost::any_cast<UChar8>(Source));
    }
    else if(Source.type() == typeid(SChar8))   //SChar8
    {
        return boost::lexical_cast<std::string>(boost::any_cast<SChar8>(Source));
    }
    
    else if(Source.type() == typeid(GLenum))   //GLenum
    {
        return toString(boost::any_cast<GLenum>(Source));
    }

    else if(Source.type() == typeid(Path))   //File Path
    {
        return boost::any_cast<Path>(Source).filename();
    }

    else
    {
		try
		{
			AttachmentContainerPtr Container = boost::any_cast<NodePtr>(Source);

			if(Container != NullFC)
			{
				const Char8 * ContainerName(getName(Container));
				if(ContainerName != NULL)
				{
					return std::string(ContainerName);
				}
				else
				{
					return std::string("Empty Name");
				}
			}
		}
		catch(boost::bad_any_cast &)
		{
		}
        throw boost::bad_lexical_cast(Source.type(), typeid(std::string));
    }
    return std::string("");
}

OSG_END_NAMESPACE

