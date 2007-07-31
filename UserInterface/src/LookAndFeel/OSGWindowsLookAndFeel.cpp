/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGWindowsLookAndFeel.h"
#include "Text/OSGFont.h"
#include "Border/OSGLineBorder.h"
#include "Border/OSGEmptyBorder.h"
#include "Border/OSGEtchedBorder.h"
#include "Border/OSGBevelBorder.h"
#include "Border/OSGMatteBorder.h"
#include "Border/OSGCompoundBorder.h"
#include "Background/OSGColorUIBackground.h"
#include "Background/OSGEmptyUIBackground.h"
#include "Background/OSGCompoundUIBackground.h"
#include "Background/OSGGradientUIBackground.h"
#include "Background/OSGMaterialUIBackground.h"
#include "Background/OSGTextureUIBackground.h"
#include "Component/OSGButton.h"
#include "Component/OSGLabel.h"
#include "Component/OSGFrame.h"
#include "Component/OSGPanel.h"
#include "Component/OSGImageComponent.h"
#include "Util/OSGUIDefines.h"
#include "Component/OSGCheckboxButton.h"
#include "Component/OSGRadioButton.h"
#include "Component/OSGToggleButton.h"
#include "Graphics/UIDrawObjects/OSGRectUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGArcUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGDiscUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGLineUIDrawObject.h"
#include "Component/OSGUIDrawObjectCanvas.h"
#include "Component/Text/OSGTextField.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::WindowsLookAndFeel
UI Windows LookAndFeel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void WindowsLookAndFeel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 WindowsLookAndFeel::getTextCaretRate(void) const
{
	return _TextCaretRate;
}

void WindowsLookAndFeel::init(void)
{
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

WindowsLookAndFeel::WindowsLookAndFeel(void) :
    Inherited(),
		_TextCaretRate(1.0)
{
}

WindowsLookAndFeel::WindowsLookAndFeel(const WindowsLookAndFeel &source) :
    Inherited(source),
		_TextCaretRate(source._TextCaretRate)
{
}

WindowsLookAndFeel::~WindowsLookAndFeel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void WindowsLookAndFeel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void WindowsLookAndFeel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump WindowsLookAndFeel NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGWINDOWSLOOKANDFEELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGWINDOWSLOOKANDFEELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGWINDOWSLOOKANDFEELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

