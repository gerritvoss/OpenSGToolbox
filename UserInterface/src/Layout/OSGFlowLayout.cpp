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

#include <OpenSG/OSGConfig.h>

#include "Util/OSGUIDefines.h"
#include "OSGFlowLayout.h"
#include "Component/Container/OSGContainer.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FlowLayout
A UI FlowLayout. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FlowLayout::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void FlowLayout::updateLayout(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
	/*!
      totalMajorAxis will hold the width of its container, and cumMajorAxis
	  will hold the width of all of the buttons. That way it will always know
	  when to move to the next line. In addition, maxMinorAxis keeps track of
	  the largest height so it knows how far down to move the next row. Also,
	  oneInRow is used to make sure that it places at least one component in
	  every row.
    */
	UInt32 AxisIndex(0);
	if(getAlignment() != HORIZONTAL_ALIGNMENT ) AxisIndex = 1;
	Vec2s gap(getHorizontalGap(), getVerticalGap());
	UInt32 numGaps(0);
	/*!
	  When finding the cumMinor Axis, the gap is included, because there is
	  no count for how many stacks there are. When finding cumMajor, the
	  gap isn't included because the total distance relies on how many
	  components there are in that row/column.
	*/

	Pnt2s borderTopLeft, borderBottomRight;
	Container::Ptr::dcast(ParentComponent)->getInsideInsetsBounds(borderTopLeft, borderBottomRight);
	Vec2s borderSize(borderBottomRight-borderTopLeft);
	Int64 totalMajorAxis(borderSize[AxisIndex]);
	UInt32 cumMajorAxis(0);
	UInt32 maxMinorAxis(0);
	UInt32 cumMinorAxis(0);
	UInt32 prevComponent(0);
	Int64 offsetMajorAxis(0);
	Int64 offsetMinorAxis(0);
	Int64 offsetX(borderTopLeft.x());
	Int64 offsetY(borderTopLeft.y());
	bool firstOne = true;

	for(UInt32 i=0 ; i<Components.size(); ++i)
    {
        beginEditCP(Components.getValue(i), Component::PositionFieldMask | Component::PositionFieldMask);
    }

	for(UInt32 i=0 ; i<Components.size(); ++i)
	{
		// set the component to its preferred size
		//beginEditCP(Components.getValue(i), Component::SizeFieldMask);
			Components.getValue(i)->setSize(Components.getValue(i)->getPreferredSize());
		//endEditCP(Components.getValue(i), Component::SizeFieldMask);

		// if there is only one so far, then it can't draw it using cumMajorAxis
		// because it hasn't been set yet
		if (firstOne) // this one might draw it
		{
			firstOne = false;
			// if this is the last component or it is already too big for the
			// container, draw it centered on its line
			if (i == Components.size() || Components.getValue(i)->getSize()[AxisIndex] >= totalMajorAxis)
			{
				// find how far to translate to make it properly aligned
				if (getMajorAxisAlignment() == AXIS_MIN_ALIGNMENT)
				{
					offsetMajorAxis = 0;
				} else if (getMajorAxisAlignment() == AXIS_CENTER_ALIGNMENT)
				{
					offsetMajorAxis = totalMajorAxis/2 - Components.getValue(i)->getSize()[AxisIndex]/2;
				} else 
				{
					offsetMajorAxis = totalMajorAxis - Components.getValue(i)->getSize()[AxisIndex];
				}

				if (AxisIndex)
				{
					offsetY+= offsetMajorAxis;
				}
				else
				{
					offsetX += offsetMajorAxis;
				}

				//beginEditCP(Components.getValue(i), Component::PositionFieldMask);
					Components.getValue(i)->setPosition(Pnt2s(offsetX, offsetY));
				//endEditCP(Components.getValue(i), Component::PositionFieldMask);

				// get to the next row
				if (AxisIndex)
				{
					offsetX += Components.getValue(i)->getSize()[(AxisIndex+1)%2]+gap[(AxisIndex+1)%2];
					offsetY += -offsetMajorAxis;
				}
				else
				{
					offsetX += -offsetMajorAxis;
					offsetY += Components.getValue(i)->getSize()[(AxisIndex+1)%2]+gap[(AxisIndex+1)%2];
				}
				// update cumMinorAxis, other values should still be at 0
                cumMinorAxis += Components.getValue(i)->getSize()[(AxisIndex+1)%2];
                if(i < Components.size()-1)
                {
				    cumMinorAxis += gap[(AxisIndex+1)%2];
                }
				// update prevComponent
				prevComponent++;
				// next component is still just like the first one
				firstOne = true;
			}
			else
			{
				// update the maxMinorAxis
				maxMinorAxis = Components.getValue(i)->getSize()[(AxisIndex+1)%2];
				// update cumMajorAxis
				cumMajorAxis += Components.getValue(i)->getSize()[AxisIndex];
			}
		}
		else if (cumMajorAxis + Components.getValue(i)->getSize()[AxisIndex] + gap[AxisIndex]*(i-prevComponent) > totalMajorAxis) // this one draws up to i
		{
			// The numGaps is one less than the number of components being drawn, but it
			// is actually translates once for each component, so it must be compensated
			// when returning to the next row.
			numGaps = i-prevComponent-1;

			// find how far to translate to make it properly aligned
			if (getMajorAxisAlignment() == AXIS_MIN_ALIGNMENT)
			{
				offsetMajorAxis = 0;
			} else if (getMajorAxisAlignment() == AXIS_CENTER_ALIGNMENT)
			{
				offsetMajorAxis = (totalMajorAxis - (cumMajorAxis+numGaps*gap[AxisIndex]))/2;
			} else 
			{
				offsetMajorAxis = totalMajorAxis - (cumMajorAxis+numGaps*gap[AxisIndex]);
			}
			

			if (AxisIndex){
				offsetY += offsetMajorAxis;
			}
			else
			{
				offsetX += offsetMajorAxis;
			}
			for (int j = prevComponent; j < i; j++)
			{
				// find how far to translate to make this button properly aligned
				if (getComponentAlignment() == AXIS_MIN_ALIGNMENT)
				{
					offsetMinorAxis = 0;
				} else if (getComponentAlignment() == AXIS_CENTER_ALIGNMENT)
				{
					offsetMinorAxis = (maxMinorAxis-Components.getValue(j)->getSize()[(AxisIndex+1)%2])/2;
				} else 
				{
					offsetMinorAxis = maxMinorAxis-Components.getValue(j)->getSize()[(AxisIndex+1)%2];
				}

				// translate to make it properly aligned
				if (AxisIndex)
				{	
					offsetX += offsetMinorAxis;
				}
				else
				{
					offsetY += offsetMinorAxis;
				}

				//beginEditCP(Components.getValue(j), Component::PositionFieldMask);
					Components.getValue(j)->setPosition(Pnt2s(offsetX, offsetY));
				//endEditCP(Components.getValue(j), Component::PositionFieldMask);

				// translate to next button
				if (AxisIndex)
				{
					offsetX+=-(Int64)offsetMinorAxis;
					offsetY+= Components.getValue(j)->getSize()[AxisIndex] + gap[AxisIndex];
				}
				else
				{
					offsetX+=Components.getValue(j)->getSize()[AxisIndex] + gap[AxisIndex];
					offsetY+= -offsetMinorAxis;
				}
			}
			// translate to the next row
			if (AxisIndex)
			{
				offsetX += maxMinorAxis+gap[(AxisIndex+1)%2];
				offsetY += -(offsetMajorAxis+cumMajorAxis+(numGaps+1)*gap[AxisIndex]);
			}
			else
			{
				offsetX += -(offsetMajorAxis+cumMajorAxis+(numGaps+1)*gap[AxisIndex]);
				offsetY += maxMinorAxis+gap[(AxisIndex+1)%2];
			}
				
			cumMinorAxis += maxMinorAxis + gap[(AxisIndex+1)%2];
			maxMinorAxis = Components.getValue(i)->getSize()[(AxisIndex+1)%2];
			prevComponent = i;
			cumMajorAxis = Components.getValue(i)->getSize()[AxisIndex];
		}
		else
		{
			// update the maxMinorAxis
			if (Components.getValue(i)->getSize()[(AxisIndex+1)%2] > maxMinorAxis)
				maxMinorAxis = Components.getValue(i)->getSize()[(AxisIndex+1)%2];
			// update cumMajorAxis
			cumMajorAxis += Components.getValue(i)->getSize()[AxisIndex];
		}
		if (i+1 == Components.size() && !firstOne) // if on the last one, draw the last buttons
		{
			numGaps = i-prevComponent;

			// find how far to translate to make it properly aligned
			if (getMajorAxisAlignment() == AXIS_MIN_ALIGNMENT)
			{
				offsetMajorAxis = 0;
			} else if (getMajorAxisAlignment() == AXIS_CENTER_ALIGNMENT)
			{
				offsetMajorAxis = totalMajorAxis/2 - (cumMajorAxis+numGaps*gap[AxisIndex])/2;
			} else 
			{
				offsetMajorAxis = totalMajorAxis - (cumMajorAxis+numGaps*gap[AxisIndex]);
			}

			if (AxisIndex)
			{
				offsetY += offsetMajorAxis;
			}
			else
			{			
				offsetX += offsetMajorAxis;
			}
			for (int j = prevComponent; j < i+1; j++)
			{
				// find how far to translate to make this button properly aligned
				if (getComponentAlignment() == AXIS_MIN_ALIGNMENT)
				{
					offsetMinorAxis = 0;
				} else if (getComponentAlignment() == AXIS_CENTER_ALIGNMENT)
				{
					offsetMinorAxis = (maxMinorAxis-Components.getValue(j)->getSize()[(AxisIndex+1)%2])/2;
				} else 
				{
					offsetMinorAxis = maxMinorAxis-Components.getValue(j)->getSize()[(AxisIndex+1)%2];
				}

				// translate to make it properly aligned
				if (AxisIndex)
				{
					offsetX += offsetMinorAxis;
				}
				else
				{
					offsetY += offsetMinorAxis;
				}
				//beginEditCP(Components.getValue(j), Component::PositionFieldMask);
					Components.getValue(j)->setPosition(Pnt2s(offsetX, offsetY));
				//endEditCP(Components.getValue(j), Component::PositionFieldMask);

				if (AxisIndex)
				{
					offsetX += -(Int64)offsetMinorAxis;
					offsetY += Components.getValue(j)->getSize()[AxisIndex] + gap[AxisIndex];
				}
				else
				{
					offsetX += Components.getValue(j)->getSize()[AxisIndex] + gap[AxisIndex];
					offsetY+= -(Int64)offsetMinorAxis;
				}
			}
			// translate to the next row
			if (AxisIndex)
			{
				offsetX += maxMinorAxis+gap[(AxisIndex+1)%2];
				offsetY += -(offsetMajorAxis+cumMajorAxis+(numGaps+1)*gap[AxisIndex]);
			}
			else
			{
				offsetX += -(offsetMajorAxis+cumMajorAxis+(numGaps+1)*gap[AxisIndex]);
				offsetY += maxMinorAxis+gap[(AxisIndex+1)%2];
			}
			cumMinorAxis += maxMinorAxis;
		}
	}
	if (getMinorAxisAlignment() != AXIS_MIN_ALIGNMENT)
	{
		Int32 displacement(borderSize[(AxisIndex+1)%2]-cumMinorAxis);
		Pnt2s offset;
		if (getMinorAxisAlignment() == AXIS_CENTER_ALIGNMENT)
			displacement /= 2; 
		for (UInt32 i = 0; i < Components.size(); ++i)
		{
			offset = Components.getValue(i)->getPosition();
			offset[(AxisIndex+1)%2] += displacement;
			//beginEditCP(Components.getValue(i), Component::PositionFieldMask);
				Components.getValue(i)->setPosition(offset);
			//endEditCP(Components.getValue(i), Component::PositionFieldMask);
		}
	}
    
	for(UInt32 i=0 ; i<Components.size(); ++i)
    {
        endEditCP(Components.getValue(i), Component::PositionFieldMask | Component::PositionFieldMask);
    }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FlowLayout::FlowLayout(void) :
    Inherited()
{
}

FlowLayout::FlowLayout(const FlowLayout &source) :
    Inherited(source)
{
}

FlowLayout::~FlowLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FlowLayout::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void FlowLayout::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FlowLayout NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGFLOWLAYOUTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFLOWLAYOUTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFLOWLAYOUTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

