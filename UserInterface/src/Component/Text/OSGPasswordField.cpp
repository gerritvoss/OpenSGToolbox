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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGPasswordField.h"
#include "Util/OSGUIDrawUtils.h"

#include "Component/Container/OSGFrame.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/Input/OSGStringUtils.h>

#include "LookAndFeel/OSGLookAndFeelManager.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PasswordField
A UI Password Field  	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PasswordField::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

std::string PasswordField::getDrawnText(void) const
{
	return getEcho();
}

void PasswordField::mouseClicked(const MouseEvent& e)
{	
	if(e.getButton() == e.BUTTON1)
	{

		if(e.getClickCount() == 2)
		{
			selectAll();
			setCaretPosition(getText().size());
		}
	}
	TextComponent::mouseClicked(e);

}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PasswordField::PasswordField(void) :
    Inherited()
{
}

PasswordField::PasswordField(const PasswordField &source) :
    Inherited(source)
{
}

PasswordField::~PasswordField(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PasswordField::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
    
    if(whichField & TextFieldMask)
    {
        std::string EchoString("");
        for(UInt32 i(0) ; i<getText().size(); ++i)
        {
            EchoString = EchoString + getEchoChar();
        }
        setEcho(EchoString);
    }
}

void PasswordField::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PasswordField NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGPASSWORDFIELDBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPASSWORDFIELDBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPASSWORDFIELDFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

