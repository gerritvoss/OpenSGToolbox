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

#include "Background/OSGColorUIBackground.h"
#include "Border/OSGLineBorder.h"
#include "Border/OSGEmptyBorder.h"

#include "OSGDefaultListCellGenerator.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultListCellGenerator
A DefaultListCellGenerator. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultListCellGenerator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
ComponentPtr DefaultListCellGenerator::getListCellGeneratorComponent(ListPtr list, Field* value, UInt32 index, bool isSelected, bool cellHasFocus)
{
	if(value == NULL){
		return NullFC;
	}
	beginEditCP(DefaultListCellGeneratorPtr(this), DefaultListCellGenerator::TextFieldMask);
		std::string tempString;
		value->getValueByStr(tempString);
		setText(tempString);
	endEditCP(DefaultListCellGeneratorPtr(this), DefaultListCellGenerator::TextFieldMask);
	ColorUIBackgroundPtr tempBackground;
	if(getBackground()->getType() == ColorUIBackground::getClassType()){
		tempBackground = ColorUIBackground::Ptr::dcast(getBackground());
	}
	else{
		tempBackground = ColorUIBackground::create();
		beginEditCP(DefaultListCellGeneratorPtr(this), DefaultListCellGenerator::BackgroundFieldMask);
			setBackground(tempBackground);
		endEditCP(DefaultListCellGeneratorPtr(this), DefaultListCellGenerator::BackgroundFieldMask);
	}
	beginEditCP(tempBackground, ColorUIBackground::ColorFieldMask);
		if(isSelected){
			tempBackground->setColor(Color4f(0.4, 0.4, 1.0, 1.0));
		}
		else{
			tempBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
		}
	endEditCP(tempBackground, ColorUIBackground::ColorFieldMask);
	if(cellHasFocus){
		LineBorderPtr tempBorder;
		if(getBorder()->getType() == LineBorder::getClassType()){
			tempBorder = LineBorder::Ptr::dcast(getBorder());
		}
		else{
			tempBorder = LineBorder::create();
			beginEditCP(DefaultListCellGeneratorPtr(this), DefaultListCellGenerator::BorderFieldMask);
				setBorder(tempBorder);
			endEditCP(DefaultListCellGeneratorPtr(this), DefaultListCellGenerator::BorderFieldMask);
		}
		beginEditCP(tempBorder, LineBorder::ColorFieldMask);
			tempBorder->setColor(Color4f(0.0, 0.0, 1.0, 1.0));
		endEditCP(tempBorder, LineBorder::ColorFieldMask);
	}
	else{
		EmptyBorderPtr tempBorder;
		if(getBorder()->getType()==EmptyBorder::getClassType()){
			tempBorder = EmptyBorder::Ptr::dcast(getBorder());
		}
		else{
			tempBorder = EmptyBorder::create();
			beginEditCP(DefaultListCellGeneratorPtr(this), DefaultListCellGenerator::BorderFieldMask);
				setBorder(tempBorder);
			endEditCP(DefaultListCellGeneratorPtr(this), DefaultListCellGenerator::BorderFieldMask);
		}
	}
	return Component::Ptr::dcast(deepClone(DefaultListCellGeneratorPtr(this), "Material"));
	
	
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultListCellGenerator::DefaultListCellGenerator(void) :
    Inherited()
{
}

DefaultListCellGenerator::DefaultListCellGenerator(const DefaultListCellGenerator &source) :
    Inherited(source)
{
}

DefaultListCellGenerator::~DefaultListCellGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultListCellGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultListCellGenerator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultListCellGenerator NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDEFAULTLISTCELLGENERATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTLISTCELLGENERATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTLISTCELLGENERATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

