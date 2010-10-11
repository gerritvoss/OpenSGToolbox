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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGDocumentElementAttributes.h"

OSG_BEGIN_NAMESPACE


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DocumentElementAttribute::DocumentElementAttribute(UInt32 fs,
                                                   bool b,
                                                   bool i,
                                                   bool u,
                                                   const std::string& fface,
                                                   Int32 ffaceindex,
                                                   const Color3f& fg,
                                                   Int32 fgindex,
                                                   const Color3f& bg,
                                                   Int32 bgindex,
                                                   bool e,
                                                   bool p)
{
	fontsize = fs;
	bold = b;
	italics =i;
	underlined = u;
	fontface = fface;
	fontfaceindex=ffaceindex;
	foreground=fg;
	foregroundindex=fgindex;
	background=bg;
	backgroundindex=bgindex;
	ends=e;
	processed=p;
}

DocumentElementAttribute::DocumentElementAttribute(const DocumentElementAttribute &source) :
    fontsize(source.fontsize),
    bold(source.bold),
    italics(source.italics),
    underlined(source.underlined),
    fontfaceindex(source.fontfaceindex),
    foreground(source.foreground),
    foregroundindex(source.foregroundindex),
    background(source.background),
    backgroundindex(source.backgroundindex),
    ends(source.ends),
    processed(source.processed)
{
}

DocumentElementAttribute::~DocumentElementAttribute(void)
{
}

/*----------------------------- class specific ----------------------------*/


OSG_END_NAMESPACE
