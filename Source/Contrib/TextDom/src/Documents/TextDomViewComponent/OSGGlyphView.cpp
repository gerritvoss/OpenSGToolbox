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

void GlyphView::drawView(const GraphicsWeakPtr Graphics, Real32 Opacity)
{
	if(!_IsWordWrapEnabled)
	{
		Pnt2f tempPosition;
		tempPosition = _InitialPosition;
		
		std::vector<UInt32> theColoredIndices = SyntaxHighlighter::the()->processInput(temp->getText());
		if(theColoredIndices.size())
		{
			std::string theString;
			Pnt2f topLeft,bottomRight;
			for(Int32 i=0;i<theColoredIndices.size();i+=2)
			{
				if(i==0)theString = temp->getText().substr(0,theColoredIndices[i]);
				else	theString = temp->getText().substr(theColoredIndices[i-1],theColoredIndices[i] - theColoredIndices[i-1]);
				
				Graphics->drawText(tempPosition,theString,_Font,Color4f(0.0,0.0,0.0,1.0),Opacity);
				_Font->getBounds(theString,topLeft,bottomRight);
				tempPosition.setValues(tempPosition.x() + bottomRight.x(),tempPosition.y());
			

				theString = temp->getText().substr(theColoredIndices[i],theColoredIndices[i+1] - theColoredIndices[i]);
				Graphics->drawText(tempPosition,theString,_Font,Color4f(0.0,0.0,1.0,1.0),Opacity);
				_Font->getBounds(theString,topLeft,bottomRight);
				tempPosition.setValues(tempPosition.x() + bottomRight.x(),tempPosition.y());

				if(i==theColoredIndices.size()-2)
				{
					theString = temp->getText().substr(theColoredIndices[theColoredIndices.size()-1]);
					Graphics->drawText(tempPosition,theString,_Font,Color4f(0.0,0.0,0.0,1.0),Opacity);
				}
			}
		}
		else
		{
			Graphics->drawText(_InitialPosition,temp->getText(),_Font,Color4f(0.0,0.0,0.0,1.0),Opacity);
		}
	}
}

/*
void GlyphView::drawView_old(const GraphicsWeakPtr Graphics, Real32 Opacity,UIFontRefPtr Font)
{

	if(_Element)
	{
		Pnt2f tempInitPos = _InitialPosition;
		PlainDocumentLeafElementRefPtr temp = dynamic_pointer_cast<PlainDocumentLeafElement>(_Element);
		std::stringstream iss(temp->getText());
		std::string tempsentence="";
		std::string t;
		std::string theLine=" ";
		Pnt2f topLeft,bottomRight;
		bool ret;
		bool shouldRead=true;

		while(1)
		{
			if(shouldRead)
			{
				ret = (iss>>t);
				if(!ret)break;
				tempsentence+=t+" ";
			}

			if(canFitIn(tempsentence))
			{
				theLine = tempsentence;
				shouldRead=true;
			}
			else
			{
				if(theLine != " ")
				{
					Graphics->drawText(tempInitPos,theLine,Font,Color4f(0.0,0.0,0.0,1.0),Opacity);
					theLine = " ";
					tempsentence = t+" ";
					tempInitPos.setValues(tempInitPos.x(),tempInitPos.y()+_LineHeight);
					shouldRead = false;
				}
				else	// deal with the case when the length of the current word is longer than the width of the textdomarea
				{// // as of now if this is the last element, then it would print an extra " " on the screen.
					theLine = tempsentence;
					Graphics->drawText(tempInitPos,theLine,Font,Color4f(0.0,0.0,0.0,1.0),Opacity);
					theLine = " ";
					tempsentence = "";
					tempInitPos.setValues(tempInitPos.x(),tempInitPos.y()+_LineHeight);
					shouldRead = true;
				}
			}
		}
		if(theLine!=" ")
		{
			theLine = theLine.substr(0,theLine.size()-1);
			Graphics->drawText(tempInitPos,theLine,Font,Color4f(0.0,0.0,0.0,1.0),Opacity);
		}
	}
}

inline bool GlyphView::canFitIn(std::string sentence)
{
	return (sentence.size() * _CharacterWidth < _LineWidth);
}
*/
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/



GlyphView::GlyphView(void) :
	_InitialPosition(Pnt2f(0,0)),
	_Element(NULL),
	//_GutterSpace(40.0),
	//_GutterSeparation(5.0),
	_IsWordWrapEnabled(false),
	Inherited()
{

}

GlyphView::GlyphView(const GlyphView &source) :
    Inherited(source)
{
	_Element = source._Element;
	_InitialPosition = source._InitialPosition;
	_IsWordWrapEnabled = source._IsWordWrapEnabled;
	//_GutterSpace = source._GutterSpace;
	//_GutterSeparation = source._GutterSeparation;
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
