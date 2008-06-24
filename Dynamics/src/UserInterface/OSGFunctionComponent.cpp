/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Dynamics                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#define OSG_COMPILEDYNAMICSLIB

#include <OpenSG/OSGConfig.h>

#include "OSGFunctionComponent.h"
#include "Function/OSGFunction.h"
#include <OpenSG/UserInterface/OSGUIDrawUtils.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FunctionComponent
A User Interface Component that represents a function. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FunctionComponent::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void FunctionComponent::drawInternal(const GraphicsPtr Graphics) const
{
	if(getFunction() != NullFC)
	{
		//Get Input/Output information about function
		FunctionIOTypeVector EmptyTypeVector;
		FunctionIOTypeVector OutputTypes = getFunction()->getOutputTypes(EmptyTypeVector);
		FunctionIOTypeVector InputTypes = getFunction()->getInputTypes(EmptyTypeVector);
		UInt32 NumInputs = InputTypes.size();
		UInt32 NumOutputs = OutputTypes.size();
		
		//Get bounds of function component
		Pnt2f TopLeft, BottomRight;
		getInsideBorderBounds(TopLeft, BottomRight);
		
		/*
		//Determine size of and draw component
		UInt32 ComponentWidth = 450;
		UInt32 ComponentHeight;
		
		if(NumOutputs > NumInputs)
		{
			ComponentHeight = (50 + (25*NumOutputs) + (15*(NumOutputs - 1)));
		}
		else
		{
			ComponentHeight = (50 + (25*NumInputs) + (15*(NumInputs - 1)));
		}
		*/
		
		
		//Input/Outup tab properties
		Real32 TabWidth = 20; //Scaled down; normally 100
		Real32 TabHeight = 5; //Scaled down; normally 25
		Real32 HorizontalSpacing = 15;
		Real32 VerticalSpacing = 15;
		Color4f TabColor = Color4f(1.0f, 1.0f, 1.0f, 1.0f);
		Real32 TabOpacity = 1.0;
		
		//DRAW INPUT TABS
		if(getInputTabOrientation() == VERTICAL_ORIENTATION)
		{
			Pnt2f InputsTopLeft, InputsBottomRight;
			InputsTopLeft = Pnt2f(25.0f, 25.0f);
			InputsBottomRight = Pnt2f(25.0f + TabWidth, 25.0f + TabHeight + ((NumInputs - 1) * (TabHeight + VerticalSpacing)));
		
			//Calculate Alignment
			Pnt2f AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (InputsBottomRight - InputsTopLeft), getInputTabVerticalAlignment(), getInputTabHorizontalAlignment());
			
			for (UInt32 i(0); i < NumInputs; ++i)
			{
				//Calculate bounding points
				Pnt2f RectangleTopLeft, RectangleBottomRight;
				RectangleTopLeft = Pnt2f(AlignedPosition.x(), AlignedPosition.y() + (i * (TabHeight + VerticalSpacing)));
				RectangleBottomRight = Pnt2f(AlignedPosition.x() + TabWidth, AlignedPosition.y() + TabHeight + (i * (TabHeight + VerticalSpacing)));
				
				//Draw rectangle
				Graphics->drawRect(RectangleTopLeft, RectangleBottomRight, TabColor, TabOpacity);
			}
		}
		else
		{
			Pnt2f InputsTopLeft, InputsBottomRight;
			InputsTopLeft = Pnt2f(25.0f, 25.0f);
			InputsBottomRight = Pnt2f(25.0f + TabWidth + ((NumInputs - 1) * TabWidth + HorizontalSpacing), 25.0f + TabHeight);
		
			//Calculate Alignment
			Pnt2f AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (InputsBottomRight - InputsTopLeft), getInputTabVerticalAlignment(), getInputTabHorizontalAlignment());
			
			for (UInt32 i(0); i < NumInputs; ++i)
			{
				//Calculate bounding points
				Pnt2f RectangleTopLeft, RectangleBottomRight;
				RectangleTopLeft = Pnt2f(AlignedPosition.x() + (i * (TabWidth + HorizontalSpacing)), AlignedPosition.y());
				RectangleBottomRight = Pnt2f(AlignedPosition.x() + TabWidth + (i * (TabWidth + HorizontalSpacing)), AlignedPosition.y() + TabHeight);
				
				//Draw rectangle
				Graphics->drawRect(RectangleTopLeft, RectangleBottomRight, TabColor, TabOpacity);
			}
		}
			
					
		//DRAW OUTPUT TABS
		if(getOutputTabOrientation() == VERTICAL_ORIENTATION)
		{
			Pnt2f OutputsTopLeft, OutputsBottomRight;
			OutputsTopLeft = Pnt2f(25.0f, 25.0f);
			OutputsBottomRight = Pnt2f(25.0f + TabWidth, 25.0f + TabHeight + ((NumOutputs - 1) * (TabHeight + VerticalSpacing)));
		
			//Calculate Alignment
			Pnt2f AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (OutputsBottomRight - OutputsTopLeft), getOutputTabVerticalAlignment(), getOutputTabHorizontalAlignment());
			
			for (UInt32 i(0); i < NumOutputs; ++i)
			{
				//Calculate bounding points
				Pnt2f RectangleTopLeft, RectangleBottomRight;
				RectangleTopLeft = Pnt2f(AlignedPosition.x(), AlignedPosition.y() + (i * (TabHeight + VerticalSpacing)));
				RectangleBottomRight = Pnt2f(AlignedPosition.x() + TabWidth, AlignedPosition.y() + TabHeight + (i * (TabHeight + VerticalSpacing)));
				
				//Draw rectangle
				Graphics->drawRect(RectangleTopLeft, RectangleBottomRight, TabColor, TabOpacity);
			}
		}
		else
		{
			Pnt2f OutputsTopLeft, OutputsBottomRight;
			OutputsTopLeft = Pnt2f(25.0f, 25.0f);
			OutputsBottomRight = Pnt2f(25.0f + TabWidth + ((NumOutputs - 1) * TabWidth + HorizontalSpacing), 25.0f + TabHeight);
		
			//Calculate Alignment
			Pnt2f AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (OutputsBottomRight - OutputsTopLeft), getOutputTabVerticalAlignment(), getOutputTabHorizontalAlignment());
			
			for (UInt32 i(0); i < NumOutputs; ++i)
			{
				//Calculate bounding points
				Pnt2f RectangleTopLeft, RectangleBottomRight;
				RectangleTopLeft = Pnt2f(AlignedPosition.x() + (i * (TabWidth + HorizontalSpacing)), AlignedPosition.y());
				RectangleBottomRight = Pnt2f(AlignedPosition.x() + TabWidth + (i * (TabWidth + HorizontalSpacing)), AlignedPosition.y() + TabHeight);
				
				//Draw rectangle
				Graphics->drawRect(RectangleTopLeft, RectangleBottomRight, TabColor, TabOpacity);
			}
		}

		
		/*
		for (UInt32 i(0); i < NumOutputs; ++i)
		{
			//Calculate bounding points
			Pnt2f RectangleTopLeft, RectangleBottomRight;
			RectangleTopLeft = Pnt2f(BottomRight.x() - 125.0f, 25.0f + (i * 40.0f));
			RectangleBottomRight = Pnt2f(BottomRight.x() - 25.0f, 50.0f + (i * 40.0f));
			
			//Draw rectangle
			Graphics->drawRect(RectangleTopLeft, RectangleBottomRight, Color4f(1.0f, 1.0f, 1.0f, 1.0f), 1.0);
		}
		*/
	}
}

Vec2f FunctionComponent::getContentRequestedSize(void) const
{
    return Inherited::getContentRequestedSize();
}

void FunctionComponent::updateLayout(void)
{
    //TODO: Implement
    Inherited::updateLayout();
}

void FunctionComponent::updateTabs(void)
{
    //For Each Input Tab
    //Update it
    
    //For Each Output Tab
    //Update it
}

void FunctionComponent::updateInputTab(UInt32 Index)
{
}

void FunctionComponent::updateOutputTab(UInt32 Index)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FunctionComponent::FunctionComponent(void) :
    Inherited()
{
}

FunctionComponent::FunctionComponent(const FunctionComponent &source) :
    Inherited(source)
{
}

FunctionComponent::~FunctionComponent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FunctionComponent::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if((whichField & InputTabComponentGeneratorFieldMask) ||
        (whichField & OutputTabComponentGeneratorFieldMask))
    {
        updateTabs();
    }

    if((whichField & InputTabsFieldMask) ||
        (whichField & OutputTabsFieldMask))
    {
        beginEditCP(FunctionComponentPtr(this), FunctionComponent::ChildrenFieldMask);
            getChildren().clear();
            for(UInt32 i(0) ; i<getInputTabs().size() ; ++i)
            {
                getChildren().push_back(getInputTabs()[i]);
            }
            for(UInt32 i(0) ; i<getOutputTabs().size() ; ++i)
            {
                getChildren().push_back(getOutputTabs()[i]);
            }
        endEditCP(FunctionComponentPtr(this), FunctionComponent::ChildrenFieldMask);
    }
}

void FunctionComponent::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FunctionComponent NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGFUNCTIONCOMPONENTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFUNCTIONCOMPONENTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFUNCTIONCOMPONENTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

