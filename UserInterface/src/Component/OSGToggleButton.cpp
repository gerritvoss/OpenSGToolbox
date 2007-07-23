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

#include <OpenSG/OSGConfig.h>

#include "OSGToggleButton.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ToggleButton
A UI Button. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ToggleButton::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ToggleButton::ToggleButton(void) :
    Inherited()
{
}

ToggleButton::ToggleButton(const ToggleButton &source) :
    Inherited(source)
{
}

ToggleButton::~ToggleButton(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ToggleButton::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ToggleButton::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ToggleButton NI" << std::endl;
}

void ToggleButton::mouseReleased(const MouseEvent& e)
{
	if(e.getButton()==MouseEvent::BUTTON1){
		if(getActive())
		{
			beginEditCP(ToggleButtonPtr(this), Button::ActiveFieldMask);
				setActive(false);
			endEditCP(ToggleButtonPtr(this), Button::ActiveFieldMask);
		}
		else
		{
			beginEditCP(ToggleButtonPtr(this), Button::ActiveFieldMask);
				setActive(true);
			endEditCP(ToggleButtonPtr(this), ToggleButton::ActiveFieldMask);
		}
		
	}
	Component::mouseReleased(e);
}
void ToggleButton::mousePressed(const MouseEvent& e)
{

	Component::mousePressed(e);
}
void ToggleButton::mouseExited(const MouseEvent& e)
{


	Component::mouseExited(e);
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
    static Char8 cvsid_hpp       [] = OSGTOGGLEBUTTONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTOGGLEBUTTONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTOGGLEBUTTONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

