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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGFunctionComponent.h"
#include <OpenSG/Dynamics/OSGFunction.h>
#include "Util/OSGUIDrawUtils.h"
#include <OpenSG/Toolbox/OSGStringUtils.h>
#include "Component/Dynamics/IOTabGenerators/OSGFunctionComponentIOTabComponentGenerator.h"

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
	//Get bounds of function component
	Pnt2f TopLeft, BottomRight;
	getInsideBorderBounds(TopLeft, BottomRight);
	
	if (getFont() != NullFC)
	{
		//Draw Text for the Function Type
		//Get text
		std::string TheText(addStringBetweenUpperCaseChange(getFunction()->getType().getCName(), std::string(" ")));

		//Calculate text alignment
		Pnt2f AlignedTextPosition;
		Pnt2f TextTopLeft, TextBottomRight;
		getFont()->getBounds(TheText, TextTopLeft, TextBottomRight);
		AlignedTextPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft), getTextAlignment().y(), getTextAlignment().x());
		
		//Draw the text
		Graphics->drawText(AlignedTextPosition, TheText, getFont(), getTextColor(), 1.0);
	}
	
    Inherited::drawInternal(Graphics);
}

Vec2f FunctionComponent::getContentRequestedSize(void) const
{
	Pnt2f InputsTopLeft, InputsBottomRight, OutputsTopLeft, OutputsBottomRight, TextTopLeft, TextBottomRight;
	//Find bounding points for INPUT tabs
	if(getInputTabs().size() > 0)
	{
		InputsTopLeft = Pnt2f(0.0f, 0.0f);
		InputsBottomRight = Pnt2f(getInputTabs()[0]->getRequestedSize().x(), getInputTabs()[0]->getRequestedSize().y());
		if (getInputTabs().size() > 1)
		{
			for (UInt32 i(1); i < getInputTabs().size(); ++i)
			{
				if(getInputTabOrientation() == VERTICAL_ORIENTATION)
				{
					if(InputsBottomRight.x() < getInputTabs()[i]->getRequestedSize().x())
					{
						InputsBottomRight[0] = getInputTabs()[i]->getRequestedSize().x();
					}
					
					InputsBottomRight[1] += getInputTabs()[i]->getRequestedSize().y() + getInputTabSpacing();
				}
				else //HORIZONTAL ORIENTATION
				{
					if(InputsBottomRight.y() < getInputTabs()[i]->getRequestedSize().y())
					{
						InputsBottomRight[1] = getInputTabs()[i]->getRequestedSize().y();
					}
					
					InputsBottomRight[0] += getInputTabs()[i]->getRequestedSize().x() + getInputTabSpacing();
				}
			}
		}
	}
	
	//Find bounding points for OUTPUT tabs
	if(getOutputTabs().size() > 0)
	{
		OutputsTopLeft = Pnt2f(0.0f, 0.0f);
		OutputsBottomRight = Pnt2f(getOutputTabs()[0]->getRequestedSize().x(), getOutputTabs()[0]->getRequestedSize().y());
		if (getOutputTabs().size() > 1)
		{
			for (UInt32 i(1); i < getOutputTabs().size(); ++i)
			{
				if(getOutputTabOrientation() == VERTICAL_ORIENTATION)
				{
					if(OutputsBottomRight.x() < getOutputTabs()[i]->getRequestedSize().x())
					{
						OutputsBottomRight[0] = getOutputTabs()[i]->getRequestedSize().x();
					}
					
					OutputsBottomRight[1] += getOutputTabs()[i]->getRequestedSize().y() + getOutputTabSpacing();
				}
				else //HORIZONTAL ORIENTATION
				{
					if(OutputsBottomRight.y() < getOutputTabs()[i]->getRequestedSize().y())
					{
						OutputsBottomRight[1] = getOutputTabs()[i]->getRequestedSize().y();
					}
					
					OutputsBottomRight[0] += getOutputTabs()[i]->getRequestedSize().x() + getOutputTabSpacing();
				}
			}
		}
	}	
	//Calculate component size
	Vec2f InputSize, OutputSize, TextSize, FunctionComponentSize;
	
	InputSize[0] = InputsBottomRight.x() - InputsTopLeft.x();
	InputSize[1] = InputsBottomRight.y() - InputsTopLeft.y();
	
	OutputSize[0] = OutputsBottomRight.x() - OutputsTopLeft.x();
	OutputSize[1] = OutputsBottomRight.y() - OutputsTopLeft.y();
	
	
	if(getFont() != NullFC)
	{
		//Find bounding points for TEXT
		std::string TheText(addStringBetweenUpperCaseChange(getFunction()->getType().getCName(), std::string(" ")));
		getFont()->getBounds(TheText, TextTopLeft, TextBottomRight);
		
		TextSize[0] = TextBottomRight.x() - TextTopLeft.x();
		TextSize[1] = TextBottomRight.y() - TextTopLeft.y();
	}
	else
	{
		TextSize.setValues(0.0f,0.0f);
	}

	
	if(getInputTabOrientation() == VERTICAL_ORIENTATION)
	{
		if(getOutputTabOrientation() == VERTICAL_ORIENTATION)
		{
			FunctionComponentSize[0] = InputSize.x() + OutputSize.x() + TextSize.x() + 2*getInputTabSpacing();
			if(InputSize.y() > OutputSize.y())
			{
				if(InputSize.y() > TextSize.y())
				{
					FunctionComponentSize[1] = InputSize.y() + 2*getInputTabSpacing();
				}
				else
				{
					FunctionComponentSize[1] = TextSize.y() + 2*getInputTabSpacing();
				}
			}
			else
			{
				if(OutputSize.y() > TextSize.y())
				{
					FunctionComponentSize[1] = OutputSize.y() + 2*getOutputTabSpacing();
				}
				else
				{
					FunctionComponentSize[1] = TextSize.y() + 2*getOutputTabSpacing();
				}
			}
			
			//Make sure text doesn't overlap tabs
			Pnt2f TopLeft = Pnt2f(0.0, 0.0);
			Pnt2f BottomRight = Pnt2f(FunctionComponentSize.x(), FunctionComponentSize.y());
			Pnt2f AlignedInputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (InputsBottomRight - InputsTopLeft), getInputTabAlignment().y(), getInputTabAlignment().x());
			Pnt2f AlignedOutputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (OutputsBottomRight - OutputsTopLeft), getOutputTabAlignment().y(), getOutputTabAlignment().x());
			Pnt2f AlignedTextPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft), getTextAlignment().y(), getTextAlignment().x());
			
			while((AlignedInputTabPosition.x() + InputSize.x() - AlignedTextPosition.x()) >= 0)
			{
				FunctionComponentSize[0] += (AlignedInputTabPosition.x() + InputSize.x() - AlignedTextPosition.x()) + getInputTabSpacing();
				
				BottomRight = Pnt2f(FunctionComponentSize.x(), FunctionComponentSize.y());
				AlignedInputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (InputsBottomRight - InputsTopLeft), getInputTabAlignment().y(), getInputTabAlignment().x());
				AlignedOutputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (OutputsBottomRight - OutputsTopLeft), getOutputTabAlignment().y(), getOutputTabAlignment().x());
				AlignedTextPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft), getTextAlignment().y(), getTextAlignment().x());
			}
			while((AlignedTextPosition.x() + TextSize.x() - AlignedOutputTabPosition.x()) >= 0)
			{
				FunctionComponentSize[0] += (AlignedTextPosition.x() + TextSize.x() - AlignedOutputTabPosition.x()) + getOutputTabSpacing();
				
				BottomRight = Pnt2f(FunctionComponentSize.x(), FunctionComponentSize.y());
				AlignedInputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (InputsBottomRight - InputsTopLeft), getInputTabAlignment().y(), getInputTabAlignment().x());
				AlignedOutputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (OutputsBottomRight - OutputsTopLeft), getOutputTabAlignment().y(), getOutputTabAlignment().x());
				AlignedTextPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft), getTextAlignment().y(), getTextAlignment().x());
			}
		}
		else
		{
			FunctionComponentSize[0] = 2*InputSize.x() + OutputSize.x() + 2*getOutputTabSpacing();
			FunctionComponentSize[1] = InputSize.y() + 2*OutputSize.y() + 2*getInputTabSpacing();
			
			//Make sure text doesn't overlap tabs
			Pnt2f TopLeft = Pnt2f(0.0, 0.0);
			Pnt2f BottomRight = Pnt2f(FunctionComponentSize.x(), FunctionComponentSize.y());
			Pnt2f AlignedInputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (InputsBottomRight - InputsTopLeft), getInputTabAlignment().y(), getInputTabAlignment().x());
			Pnt2f AlignedOutputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (OutputsBottomRight - OutputsTopLeft), getOutputTabAlignment().y(), getOutputTabAlignment().x());
			Pnt2f AlignedTextPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft), getTextAlignment().y(), getTextAlignment().x());
			
			while((AlignedInputTabPosition.x() + InputSize.x() - AlignedTextPosition.x()) >= 0)
			{
				FunctionComponentSize[0] += (AlignedInputTabPosition.x() + InputSize.x() - AlignedTextPosition.x()) + getInputTabSpacing();
				
				BottomRight = Pnt2f(FunctionComponentSize.x(), FunctionComponentSize.y());
				AlignedInputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (InputsBottomRight - InputsTopLeft), getInputTabAlignment().y(), getInputTabAlignment().x());
				AlignedOutputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (OutputsBottomRight - OutputsTopLeft), getOutputTabAlignment().y(), getOutputTabAlignment().x());
				AlignedTextPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft), getTextAlignment().y(), getTextAlignment().x());
			}
			while((AlignedTextPosition.y() + TextSize.y() - AlignedOutputTabPosition.y()) >= 0)
			{
				FunctionComponentSize[1] += (AlignedTextPosition.y() + TextSize.y() - AlignedOutputTabPosition.y()) + getOutputTabSpacing();
				
				BottomRight = Pnt2f(FunctionComponentSize.x(), FunctionComponentSize.y());
				AlignedInputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (InputsBottomRight - InputsTopLeft), getInputTabAlignment().y(), getInputTabAlignment().x());
				AlignedOutputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (OutputsBottomRight - OutputsTopLeft), getOutputTabAlignment().y(), getOutputTabAlignment().x());
				AlignedTextPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft), getTextAlignment().y(), getTextAlignment().x());
			}
			while((AlignedInputTabPosition.y() + InputSize.y() - AlignedOutputTabPosition.y()) >= 0)
			{
				FunctionComponentSize[1] += (AlignedInputTabPosition.y() + InputSize.y() - AlignedOutputTabPosition.y()) + getOutputTabSpacing();
				
				BottomRight = Pnt2f(FunctionComponentSize.x(), FunctionComponentSize.y());
				AlignedInputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (InputsBottomRight - InputsTopLeft), getInputTabAlignment().y(), getInputTabAlignment().x());
				AlignedOutputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (OutputsBottomRight - OutputsTopLeft), getOutputTabAlignment().y(), getOutputTabAlignment().x());
				AlignedTextPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft), getTextAlignment().y(), getTextAlignment().x());
			}
		}
	}
	else //getInputTabOrientation() == HORIZONTAL_ORIENTATION
	{
		if(getOutputTabOrientation() == HORIZONTAL_ORIENTATION)
		{
			FunctionComponentSize[1] = InputSize.y() + OutputSize.y() + TextSize.y() + 2*getInputTabSpacing();
			if(InputSize.x() > OutputSize.x())
			{
				if(InputSize.x() > TextSize.x())
				{
					FunctionComponentSize[0] = InputSize.x() + 2*getInputTabSpacing();
				}
				else
				{
					FunctionComponentSize[0] = TextSize.x() + 2*getInputTabSpacing();
				}
			}
			else
			{
				if(OutputSize.x() > TextSize.x())
				{
					FunctionComponentSize[0] = OutputSize.x() + 2*getOutputTabSpacing();
				}
				else
				{
					FunctionComponentSize[0] = TextSize.x() + 2*getOutputTabSpacing();
				}
			}
			
			//Make sure text doesn't overlap tabs
			Pnt2f TopLeft = Pnt2f(0.0, 0.0);
			Pnt2f BottomRight = Pnt2f(FunctionComponentSize.x(), FunctionComponentSize.y());
			Pnt2f AlignedInputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (InputsBottomRight - InputsTopLeft), getInputTabAlignment().y(), getInputTabAlignment().x());
			Pnt2f AlignedOutputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (OutputsBottomRight - OutputsTopLeft), getOutputTabAlignment().y(), getOutputTabAlignment().x());
			Pnt2f AlignedTextPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft), getTextAlignment().y(), getTextAlignment().x());
			
			while((AlignedInputTabPosition.y() + InputSize.y() - AlignedTextPosition.y()) >= 0)
			{
				FunctionComponentSize[1] += (AlignedInputTabPosition.y() + InputSize.y() - AlignedTextPosition.y()) + getInputTabSpacing();
				
				BottomRight = Pnt2f(FunctionComponentSize.x(), FunctionComponentSize.y());
				AlignedInputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (InputsBottomRight - InputsTopLeft), getInputTabAlignment().y(), getInputTabAlignment().x());
				AlignedOutputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (OutputsBottomRight - OutputsTopLeft), getOutputTabAlignment().y(), getOutputTabAlignment().x());
				AlignedTextPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft), getTextAlignment().y(), getTextAlignment().x());
			}
			while((AlignedTextPosition.y() + TextSize.y() - AlignedOutputTabPosition.y()) >= 0)
			{
				FunctionComponentSize[1] += (AlignedTextPosition.y() + TextSize.y() - AlignedOutputTabPosition.y()) + getOutputTabSpacing();
				
				BottomRight = Pnt2f(FunctionComponentSize.x(), FunctionComponentSize.y());
				AlignedInputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (InputsBottomRight - InputsTopLeft), getInputTabAlignment().y(), getInputTabAlignment().x());
				AlignedOutputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (OutputsBottomRight - OutputsTopLeft), getOutputTabAlignment().y(), getOutputTabAlignment().x());
				AlignedTextPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft), getTextAlignment().y(), getTextAlignment().x());
			}
		}
		else
		{
			FunctionComponentSize[0] = InputSize.x() + 2*OutputSize.x() + 2*getInputTabSpacing();
			FunctionComponentSize[1] = 2*InputSize.y() + OutputSize.y() + 2*getOutputTabSpacing();
			
			//Make sure text doesn't overlap tabs
			Pnt2f TopLeft = Pnt2f(0.0, 0.0);
			Pnt2f BottomRight = Pnt2f(FunctionComponentSize.x(), FunctionComponentSize.y());
			Pnt2f AlignedInputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (InputsBottomRight - InputsTopLeft), getInputTabAlignment().y(), getInputTabAlignment().x());
			Pnt2f AlignedOutputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (OutputsBottomRight - OutputsTopLeft), getOutputTabAlignment().y(), getOutputTabAlignment().x());
			Pnt2f AlignedTextPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft), getTextAlignment().y(), getTextAlignment().x());
			
			while((AlignedInputTabPosition.y() + InputSize.y() - AlignedTextPosition.y()) >= 0)
			{
				FunctionComponentSize[1] += (AlignedInputTabPosition.y() + InputSize.y() - AlignedTextPosition.y()) + getInputTabSpacing();
				
				BottomRight = Pnt2f(FunctionComponentSize.x(), FunctionComponentSize.y());
				AlignedInputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (InputsBottomRight - InputsTopLeft), getInputTabAlignment().y(), getInputTabAlignment().x());
				AlignedOutputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (OutputsBottomRight - OutputsTopLeft), getOutputTabAlignment().y(), getOutputTabAlignment().x());
				AlignedTextPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft), getTextAlignment().y(), getTextAlignment().x());
			}
			while((AlignedTextPosition.x() + TextSize.x() - AlignedOutputTabPosition.x()) >= 0)
			{
				FunctionComponentSize[0] += (AlignedTextPosition.x() + TextSize.x() - AlignedOutputTabPosition.x()) + getOutputTabSpacing();
				
				BottomRight = Pnt2f(FunctionComponentSize.x(), FunctionComponentSize.y());
				AlignedInputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (InputsBottomRight - InputsTopLeft), getInputTabAlignment().y(), getInputTabAlignment().x());
				AlignedOutputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (OutputsBottomRight - OutputsTopLeft), getOutputTabAlignment().y(), getOutputTabAlignment().x());
				AlignedTextPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft), getTextAlignment().y(), getTextAlignment().x());
			}
			while((AlignedInputTabPosition.y() + InputSize.y() - AlignedOutputTabPosition.y()) >= 0)
			{
				FunctionComponentSize[1] += (AlignedInputTabPosition.y() + InputSize.y() - AlignedOutputTabPosition.y()) + getInputTabSpacing();
				
				BottomRight = Pnt2f(FunctionComponentSize.x(), FunctionComponentSize.y());
				AlignedInputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (InputsBottomRight - InputsTopLeft), getInputTabAlignment().y(), getInputTabAlignment().x());
				AlignedOutputTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (OutputsBottomRight - OutputsTopLeft), getOutputTabAlignment().y(), getOutputTabAlignment().x());
				AlignedTextPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft), getTextAlignment().y(), getTextAlignment().x());
			}
		}
	}

    return FunctionComponentSize;
}

void FunctionComponent::updateLayout(void)
{	
	//Get bounds of function component
	Pnt2f TopLeft, BottomRight;
	getInsideBorderBounds(TopLeft, BottomRight);

    //Loop through each of the INPUT tabs and set its Size and Position
	if(getInputTabs().size() > 0)
	{
		//Calculate tab alignment
		Pnt2f InputsTopLeft, InputsBottomRight;
		InputsTopLeft = Pnt2f(0.0f, 0.0f);
		InputsBottomRight = Pnt2f(getInputTabs()[0]->getRequestedSize().x(), getInputTabs()[0]->getRequestedSize().y());
		if (getInputTabs().size() > 1)
		{
			for (UInt32 i(1); i < getInputTabs().size(); ++i)
			{
				if(getInputTabOrientation() == VERTICAL_ORIENTATION)
				{
					if(InputsBottomRight.x() < getInputTabs()[i]->getRequestedSize().x())
					{
						InputsBottomRight[0] = getInputTabs()[i]->getRequestedSize().x();
					}
					
					InputsBottomRight[1] += getInputTabs()[i]->getRequestedSize().y() + getInputTabSpacing();
				}
				else //HORIZONTAL ORIENTATION
				{
					if(InputsBottomRight.y() < getInputTabs()[i]->getRequestedSize().y())
					{
						InputsBottomRight[1] = getInputTabs()[i]->getRequestedSize().y();
					}
					
					InputsBottomRight[0] += getInputTabs()[i]->getRequestedSize().x() + getInputTabSpacing();
				}
			}
		}
		Pnt2f AlignedTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (InputsBottomRight - InputsTopLeft), getInputTabAlignment().y(), getInputTabAlignment().x());
		
		//Set position and size
		Pnt2f TabTopLeft = AlignedTabPosition;
		for (UInt32 i(0); i < getInputTabs().size(); ++i)
		{
			//Calculate position of tab
			if(i > 0)
			{
				if(getInputTabOrientation() == VERTICAL_ORIENTATION)
				{
					TabTopLeft[1] += getInputTabs()[i - 1]->getRequestedSize().y() + getInputTabSpacing();
				}
				else //HORIZONTAL ORIENTATION
				{
					TabTopLeft[0] += getInputTabs()[i - 1]->getRequestedSize().x() + getInputTabSpacing();
				}
			}
			
			beginEditCP(getInputTabs()[i], Component::PositionFieldMask | Component::SizeFieldMask);
				getInputTabs()[i]->setPosition(TabTopLeft);
				getInputTabs()[i]->setSize(getInputTabs()[i]->getRequestedSize());
			endEditCP(getInputTabs()[i], Component::PositionFieldMask | Component::SizeFieldMask);
		}
	}
	
    //Loop through each of the OUTPUT tabs and set its Size and Position
	if(getOutputTabs().size() > 0)
	{
		//Calculate tab alignment
		Pnt2f OutputsTopLeft, OutputsBottomRight;
		OutputsTopLeft = Pnt2f(0.0f, 0.0f);
		OutputsBottomRight = Pnt2f(getOutputTabs()[0]->getRequestedSize().x(), getOutputTabs()[0]->getRequestedSize().y());
		if (getOutputTabs().size() > 1)
		{
			for (UInt32 i(1); i < getOutputTabs().size(); ++i)
			{
				if(getOutputTabOrientation() == VERTICAL_ORIENTATION)
				{
					if(OutputsBottomRight.x() < getOutputTabs()[i]->getRequestedSize().x())
					{
						OutputsBottomRight[0] = getOutputTabs()[i]->getRequestedSize().x();
					}
					
					OutputsBottomRight[1] += getOutputTabs()[i]->getRequestedSize().y() + getOutputTabSpacing();
				}
				else //HORIZONTAL ORIENTATION
				{
					if(OutputsBottomRight.y() < getOutputTabs()[i]->getRequestedSize().y())
					{
						OutputsBottomRight[1] = getOutputTabs()[i]->getRequestedSize().y();
					}
					
					OutputsBottomRight[0] += getOutputTabs()[i]->getRequestedSize().x() + getOutputTabSpacing();
				}
				
			}
		}
		Pnt2f AlignedTabPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (OutputsBottomRight - OutputsTopLeft), getOutputTabAlignment().y(), getOutputTabAlignment().x());
		
		//Set position and size
		Pnt2f TabTopLeft = AlignedTabPosition;
		for (UInt32 i(0); i < getOutputTabs().size(); ++i)
		{
			//Calculate position of tab
			if(i > 0)
			{
				if (getOutputTabOrientation() == VERTICAL_ORIENTATION)
				{
					TabTopLeft[1] += getOutputTabs()[i - 1]->getRequestedSize().y() + getOutputTabSpacing();
				}
				else //HORIZONTAL ORIENTATION
				{
					TabTopLeft[0] += getOutputTabs()[i - 1]->getRequestedSize().x() + getOutputTabSpacing();
				}
			}
			
			beginEditCP(getOutputTabs()[i], Component::PositionFieldMask | Component::SizeFieldMask);
				getOutputTabs()[i]->setPosition(TabTopLeft);
				getOutputTabs()[i]->setSize(getOutputTabs()[i]->getRequestedSize());
			endEditCP(getOutputTabs()[i], Component::PositionFieldMask | Component::SizeFieldMask);
		}
	}

    Inherited::updateLayout();
}

void FunctionComponent::updateTabs(void)
{
	FunctionIOTypeVector EmptyTypeVector;
	FunctionIOTypeVector OutputTypes = getFunction()->getOutputTypes(EmptyTypeVector);
	FunctionIOTypeVector InputTypes = getFunction()->getInputTypes(EmptyTypeVector);
	UInt32 NumInputs = InputTypes.size();
	UInt32 NumOutputs = OutputTypes.size();

    //For Each Input Tab
    ComponentPtr TabComponent;
    if(getInputTabComponentGenerator() != NullFC)
    {
        beginEditCP(FunctionComponentPtr(this), FunctionComponent::InputTabsFieldMask);
            getInputTabs().clear();
            //Update it
            for(UInt32 i(0) ; i<NumInputs ; ++i)
            {
                if(getInputTabComponentGenerator()->getType().isDerivedFrom( FunctionComponentIOTabComponentGenerator::getClassType()))
                {
                    TabComponent = FunctionComponentIOTabComponentGenerator::Ptr::dcast(getInputTabComponentGenerator())
                        ->getIOTabComponent(FunctionComponentPtr(this), InputTypes[i],i,false,false,false,false);
                }
                else
                {
                    TabComponent = getInputTabComponentGenerator()->getComponent(FunctionComponentPtr(this),boost::any(),i,0,false,false);
                }
                if(TabComponent != NullFC)
                {
                    getInputTabs().push_back(TabComponent);
                }
            }
        endEditCP(FunctionComponentPtr(this), FunctionComponent::InputTabsFieldMask);
    }

    
    //For Each Output Tab
    if(getOutputTabComponentGenerator() != NullFC)
    {
        beginEditCP(FunctionComponentPtr(this), FunctionComponent::OutputTabsFieldMask);
            getOutputTabs().clear();
            //Update it
            for(UInt32 i(0) ; i<NumOutputs ; ++i)
            {
                if(getOutputTabComponentGenerator()->getType().isDerivedFrom( FunctionComponentIOTabComponentGenerator::getClassType()))
                {
                    TabComponent = FunctionComponentIOTabComponentGenerator::Ptr::dcast(getOutputTabComponentGenerator())
                        ->getIOTabComponent(FunctionComponentPtr(this), OutputTypes[i],i,false,false,false,false);
                }
                else
                {
                    TabComponent = getOutputTabComponentGenerator()->getComponent(FunctionComponentPtr(this),boost::any(),i,0,false,false);
                }
                if(TabComponent != NullFC)
                {
                    getOutputTabs().push_back(TabComponent);
                }
            }
        endEditCP(FunctionComponentPtr(this), FunctionComponent::OutputTabsFieldMask);
    }
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
        (whichField & OutputTabComponentGeneratorFieldMask) ||
        (whichField & FunctionFieldMask))
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