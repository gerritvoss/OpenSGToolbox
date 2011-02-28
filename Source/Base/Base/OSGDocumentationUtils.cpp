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
#include "OSGDocumentationUtils.h"
#include <boost/xpressive/xpressive.hpp>

using namespace boost::xpressive;

OSG_BEGIN_NAMESPACE

std::string doxygenToPlainFormatting(const std::string &Doc)
{
    std::string Result(Doc);

    //Remove all newlines that do not have another newline directly afterward
    sregex SingleNewlineRegex = _ln >> (s1 = ~_ln);
    std::string SingleNewlineReplace(" $1");

    Result = regex_replace( Result, SingleNewlineRegex, SingleNewlineReplace );

    //Generate a vector of tags that define internal sections
    typedef std::pair<std::string,std::string> StringPair;
    typedef std::vector<StringPair> StringPairVector;
    StringPairVector TagsToRemove;
    TagsToRemove.push_back(std::pair<std::string,std::string>("ext","endext"));
    TagsToRemove.push_back(std::pair<std::string,std::string>("dev","enddev"));

    //Remove the tagged sections from the string
    for(StringPairVector::const_iterator Itor(TagsToRemove.begin());
        Itor != TagsToRemove.end() ;
        ++Itor)
    {
        sregex RemoveRegex = as_xpr('\\') >> Itor->first >> -*_ >> '\\' >> Itor->second;
        Result = regex_replace( Result, RemoveRegex, "" );
    }

    /*!\todo Replace some of the embedded html tags, like <br>*/
    /*!\todo Convert common doxygen tags*/

    return Result;
}

OSG_END_NAMESPACE

