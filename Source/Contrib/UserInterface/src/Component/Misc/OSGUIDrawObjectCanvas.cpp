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

#include "OSGUIDrawObjectCanvas.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGUIDrawObjectCanvasBase.cpp file.
// To modify it, please change the .fcd file (OSGUIDrawObjectCanvas.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UIDrawObjectCanvas::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void UIDrawObjectCanvas::getDrawObjectBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
	if(getMFDrawObjects()->size() > 0)
	{
		Pnt2f TempTopLeft, TempBottomRight;
		getDrawObjects(0)->getBounds(TopLeft, BottomRight);
		//Determine Top Left And Bottom Right
		for(UInt32 i(0) ; i<getMFDrawObjects()->size(); ++i)
		{
			getDrawObjects(i)->getBounds(TempTopLeft, TempBottomRight);
		    TopLeft.setValues( osgMin(TopLeft.x(), TempTopLeft.x()),
				               osgMin(TopLeft.y(), TempTopLeft.y()) );

		    BottomRight.setValues(osgMax<Real32>(BottomRight.x(), TempBottomRight.x()),
		                          osgMax<Real32>(BottomRight.y(), TempBottomRight.y()) );
		}
	}
}

Vec2f UIDrawObjectCanvas::getRequestedSize(void) const
{
    if(getUsePreferredSizeAsRequested())
    {
        return getPreferredSize();
    }
    else
    {
        return Inherited::getRequestedSize();
    }
}

Vec2f UIDrawObjectCanvas::getContentRequestedSize(void) const
{
    Pnt2f TopLeft, BottomRight;
    getDrawObjectBounds(TopLeft, BottomRight);
    return Vec2f(BottomRight - TopLeft);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void UIDrawObjectCanvas::drawInternal(Graphics* const Graphics, Real32 Opacity) const
{
	for(UInt32 i(0) ; i<getMFDrawObjects()->size(); ++i)
	{
		getDrawObjects(i)->draw(Graphics, getOpacity()*Opacity);
	}
}

/*----------------------- constructors & destructors ----------------------*/

UIDrawObjectCanvas::UIDrawObjectCanvas(void) :
    Inherited()
{
	//setClipping(false);
}

UIDrawObjectCanvas::UIDrawObjectCanvas(const UIDrawObjectCanvas &source) :
    Inherited(source)
{
	//setClipping(false);
}

UIDrawObjectCanvas::~UIDrawObjectCanvas(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UIDrawObjectCanvas::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
	
    if( (whichField & DrawObjectsFieldMask) )
    {
        setPreferredSize(getRequestedSize());
    }
}

void UIDrawObjectCanvas::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump UIDrawObjectCanvas NI" << std::endl;
}

OSG_END_NAMESPACE
