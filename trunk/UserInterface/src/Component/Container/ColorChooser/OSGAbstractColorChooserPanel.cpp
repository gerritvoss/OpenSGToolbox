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

#include "OSGAbstractColorChooserPanel.h"
#include "OSGColorChooser.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractColorChooserPanel
A UI AbstractColorChooserPanel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractColorChooserPanel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Color4f AbstractColorChooserPanel::getColorFromModel(void) const
{
	if(getParentChooser() != NullFC && getParentChooser()->getSelectionModel() != NULL)
	{
		return getParentChooser()->getSelectionModel()->getSelectedColor();
	}
	else
	{
		return Color4f();
	}
}

ColorSelectionModelPtr AbstractColorChooserPanel::getColorSelectionModel(void)
{
	if(getParentChooser() != NullFC)
	{
		return getParentChooser()->getSelectionModel();
	}
	else
	{
		return NULL;
	}
}

void AbstractColorChooserPanel::installChooserPanel(ColorChooserPtr enclosingChooser)
{
	beginEditCP(AbstractColorChooserPanelPtr(this), AbstractColorChooserPanel::ParentChooserFieldMask);
		setParentChooser(enclosingChooser);
	endEditCP(AbstractColorChooserPanelPtr(this), AbstractColorChooserPanel::ParentChooserFieldMask);

	buildChooser();
}

void AbstractColorChooserPanel::uninstallChooserPanel(ColorChooserPtr enclosingChooser)
{
	beginEditCP(AbstractColorChooserPanelPtr(this), AbstractColorChooserPanel::ParentChooserFieldMask);
		setParentChooser(NullFC);
	endEditCP(AbstractColorChooserPanelPtr(this), AbstractColorChooserPanel::ParentChooserFieldMask);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractColorChooserPanel::AbstractColorChooserPanel(void) :
    Inherited()
{
}

AbstractColorChooserPanel::AbstractColorChooserPanel(const AbstractColorChooserPanel &source) :
    Inherited(source)
{
}

AbstractColorChooserPanel::~AbstractColorChooserPanel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractColorChooserPanel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AbstractColorChooserPanel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AbstractColorChooserPanel NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGABSTRACTCOLORCHOOSERPANELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGABSTRACTCOLORCHOOSERPANELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGABSTRACTCOLORCHOOSERPANELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

