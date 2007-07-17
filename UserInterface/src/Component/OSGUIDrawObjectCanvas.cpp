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

#include "OSGUIDrawObjectCanvas.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::UIDrawObjectCanvas
A UI UIDrawObjectCanvas. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UIDrawObjectCanvas::initMethod (void)
{
}

void UIDrawObjectCanvas::getDrawObjectBounds(Pnt2s& TopLeft, Vec2s& Size) const
{
	if(getDrawObjects().size() > 0)
	{
		Vec2s TempSize;
		Pnt2s TempTopLeft;
		getDrawObjects().getValue(0)->getBounds(TopLeft, Size);
		Pnt2s BottomRight = TopLeft + Size;
		//Determine Top Left And Bottom Right
		for(UInt32 i(0) ; i<getDrawObjects().size(); ++i)
		{
			getDrawObjects().getValue(0)->getBounds(TempTopLeft, TempSize);
		    TopLeft.setValues( osgMin(TopLeft.x(), TempTopLeft.x()),
				               osgMin(TopLeft.y(), TempTopLeft.y()) );

		    BottomRight.setValues(osgMax<UInt16>(BottomRight.x(), TopLeft.x()+TempSize.x()),
		                          osgMax<UInt16>(BottomRight.y(), TopLeft.y()+TempSize.y()) );
		}
		Size = BottomRight - TopLeft;
	}
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void UIDrawObjectCanvas::drawInternal(const GraphicsPtr Graphics) const
{
	for(UInt32 i(0) ; i<getDrawObjects().size(); ++i)
	{
		getDrawObjects().getValue(i)->draw(Graphics);
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UIDrawObjectCanvas::UIDrawObjectCanvas(void) :
    Inherited()
{
}

UIDrawObjectCanvas::UIDrawObjectCanvas(const UIDrawObjectCanvas &source) :
    Inherited(source)
{
}

UIDrawObjectCanvas::~UIDrawObjectCanvas(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UIDrawObjectCanvas::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void UIDrawObjectCanvas::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump UIDrawObjectCanvas NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGUIDRAWOBJECTCANVASBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGUIDRAWOBJECTCANVASBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGUIDRAWOBJECTCANVASFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

