/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)*
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

#define OSG_COMPILECONTRIBTEXTDOMLIB

#include <OSGConfig.h>

#include "OSGGlyphView.h"
#include "OSGGraphics.h"
#include "OSGSyntaxHighlighter.h"


OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGlyphViewBase.cpp file.
// To modify it, please change the .fcd file (OSGGlyphView.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GlyphView::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

void GlyphView::drawView(Graphics * const TheGraphics, Real32 Opacity)
{
	if(!_IsWordWrapEnabled)
	{
		Pnt2f tempPosition;
		tempPosition = _InitialPosition;
		
		std::vector<UInt32> theColoredIndices = SyntaxHighlighter::the()->processInput(dynamic_cast<PlainDocumentLeafElement*>(_Element)->getText());
		if(theColoredIndices.size())
		{
			std::string theString;
			Pnt2f topLeft,bottomRight;
			for(Int32 i=0;i<theColoredIndices.size();i+=2)
			{
				if(i==0)theString = dynamic_cast<PlainDocumentLeafElement*>(_Element)->getText().substr(0,theColoredIndices[i]);
				else	theString = dynamic_cast<PlainDocumentLeafElement*>(_Element)->getText().substr(theColoredIndices[i-1],theColoredIndices[i] - theColoredIndices[i-1]);
				
				TheGraphics->drawText(tempPosition,theString,_Font,Color4f(0.0,0.0,0.0,1.0),Opacity);
				_Font->getBounds(theString,topLeft,bottomRight);
				tempPosition.setValues(tempPosition.x() + bottomRight.x(),tempPosition.y());
			

				theString = dynamic_cast<PlainDocumentLeafElement*>(_Element)->getText().substr(theColoredIndices[i],theColoredIndices[i+1] - theColoredIndices[i]);
				TheGraphics->drawText(tempPosition,theString,_Font,Color4f(0.0,0.0,1.0,1.0),Opacity);
				_Font->getBounds(theString,topLeft,bottomRight);
				tempPosition.setValues(tempPosition.x() + bottomRight.x(),tempPosition.y());

				if(i==theColoredIndices.size()-2)
				{
					theString = dynamic_cast<PlainDocumentLeafElement*>(_Element)->getText().substr(theColoredIndices[theColoredIndices.size()-1]);
					TheGraphics->drawText(tempPosition,theString,_Font,Color4f(0.0,0.0,0.0,1.0),Opacity);
				}
			}
		}
		else
		{
			TheGraphics->drawText(_InitialPosition,dynamic_cast<PlainDocumentLeafElement*>(_Element)->getText(),_Font,Color4f(0.0,0.0,0.0,1.0),Opacity);
		}
	}
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/



GlyphView::GlyphView(void) :
	Inherited(),
	_InitialPosition(Pnt2f(0,0)),
	_Element(NULL),
	_IsWordWrapEnabled(false)
{

}

GlyphView::GlyphView(const GlyphView &source) :
    Inherited(source),
	_InitialPosition(source._InitialPosition),
	_Element(source._Element),
	_IsWordWrapEnabled(source._IsWordWrapEnabled)
{
}

GlyphView::~GlyphView(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GlyphView::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GlyphView::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GlyphView NI" << std::endl;
}

OSG_END_NAMESPACE
