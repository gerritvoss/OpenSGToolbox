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

#ifndef _OSGDOCUMENTELEMENTATTRIBUTE_H_
#define _OSGDOCUMENTELEMENTATTRIBUTE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTextDomDef.h"
#include "OSGBaseTypes.h"
#include "OSGColor.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBTEXTDOM_DLLMAPPING DocumentElementAttribute
{
public:
	// the actual text
	std::string text;

	// properties
	UInt32 fontsize;
	bool bold;
	bool italics;
	bool underlined;
	std::string fontface;
	Int32 fontfaceindex;
	Color3f foreground;
	Int32 foregroundindex;
	Color3f background;
	int backgroundindex;
	bool ends;	// is true if after this text a new paragraph begins
	bool processed;

public:
	DocumentElementAttribute(UInt32 fs=22,
                  bool b=false,
                  bool i=false,
                  bool u=false,
                  const std::string& fface="Arial",
                  Int32 ffaceindex=0,
                  const Color3f& fg=Color3f(1.0f,1.0f,1.0f),
                  Int32 fgindex=0,
                  const Color3f& bg=Color3f(1.0f,1.0f,1.0f),
                  Int32 bgindex=0,
                  bool e=false,
                  bool p=false);

    DocumentElementAttribute(const DocumentElementAttribute &source);
    
    ~DocumentElementAttribute(void);
};

OSG_END_NAMESPACE

#endif //_OSGDOCUMENTELEMENTATTRIBUTE_H_