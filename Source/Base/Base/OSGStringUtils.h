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
#ifndef _OPENSG_TOOLBOX_STRING_UTILS_H_
#define _OPENSG_TOOLBOX_STRING_UTILS_H_

#include "OSGConfig.h"
#include "OSGBaseDef.h"
#include "OSGBaseTypes.h"

#include <string>
#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>

OSG_BEGIN_NAMESPACE

std::string OSG_BASE_DLLMAPPING addStringBetweenUpperCaseChange(const std::string& Source, const std::string& Pad);

std::string OSG_BASE_DLLMAPPING lexical_cast(const boost::any& Source);

void OSG_BASE_DLLMAPPING getLine(const std::string& Text, UInt32 TextPos, Int32& LineNumber, Int32& LineStartPos);

bool OSG_BASE_DLLMAPPING isPrintableChar(UChar8 c);
bool OSG_BASE_DLLMAPPING isAlphabetChar(UChar8 c);
bool OSG_BASE_DLLMAPPING isNumericChar(UChar8 c);
bool OSG_BASE_DLLMAPPING isWordChar(UChar8 c);
bool OSG_BASE_DLLMAPPING isPunctuationChar(UChar8 c);
bool OSG_BASE_DLLMAPPING isWhitespaceChar(UChar8 c);

OSG_END_NAMESPACE

#endif


