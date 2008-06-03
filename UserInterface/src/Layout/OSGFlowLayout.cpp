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

#include "OSGFlowLayout.h"
#include "Util/OSGUIDrawUtils.h"
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

Vec2f FlowLayout::getAppropriateComponentSize(ComponentPtr TheComponent)
{
    Vec2f ComponentSize(0.0f,0.0f);
    if(TheComponent != NullFC)
    {
        ComponentSize = TheComponent->getPreferredSize();
        if(ComponentSize.x() < TheComponent->getMinSize().x())
        {
            ComponentSize[0] = TheComponent->getMinSize()[0];
        }
        if(ComponentSize.y() < TheComponent->getMinSize().y())
        {
            ComponentSize[1] = TheComponent->getMinSize()[1];
        }
    }
    return ComponentSize;
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
	if(getOrientation() != HORIZONTAL_ORIENTATION ) AxisIndex = 1;
	Vec2f gap(getHorizontalGap(), getVerticalGap());
	UInt32 numGaps(0);
	/*!
	  When finding the cumMinor Axis, the gap is included, because there is
	  no count for how many stacks there are. When finding cumMajor, the
	  gap isn't included because the total distance relies on how many
	  components there are in that row/column.
	*/

	Pnt2f borderTopLeft, borderBottomRight;
	Container::Ptr::dcast(ParentComponent)->getInsideInsetsBounds(borderTopLeft, borderBottomRight);
	Vec2f borderSize(borderBottomRight-borderTopLeft);
	Real64 totalMajorAxis(borderSize[AxisIndex]);
	Real32 cumMajorAxis(0);
	Real32 maxMinorAxis(0);
	Real32 cumMinorAxis(0);
	Real32 prevComponent(0);
	Real64 offsetMajorAxis(0);
	Real64 offsetMinorAxis(0);
	Real64 offsetX(borderTopLeft.x());
	Real64 offsetY(borderTopLeft.y());
	bool firstOne = true;

	for(UInt32 i=0 ; i<Components.size(); ++i)
    {
        beginEditCP(Components[i], Component::PositionFieldMask | Component::SizeFieldMask);
    }

	for(UInt32 i=0 ; i<Components.size(); ++i)
	{
		// set the component to its preferred size
		//beginEditCP(Components[i], Component::SizeFieldMask);
			Components[i]->setSize(getAppropriateComponentSize(Components[i]));
		//endEditCP(Components[i], Component::SizeFieldMask);

		// if there is only one so far, then it can't draw it using cumMajorAxis
		// because it hasn't been set yet
		if (firstOne) // this one might draw it
		{
			firstOne = false;
			// if this is the last component or it is already too big for the
			// container, draw it centered on its line
			if (i == Components.size() || Components[i]->getSize()[AxisIndex] >= totalMajorAxis)
			{
				// find how far to translate to make it properly aligned
				offsetMajorAxis = getMajorAxisAlignment()*(totalMajorAxis - Components[i]->getSize()[AxisIndex]);

				if (AxisIndex)
				{
					offsetY+= offsetMajorAxis;
				}
				else
				{
					offsetX += offsetMajorAxis;
				}

				//beginEditCP(Components[i], Component::PositionFieldMask);
					Components[i]->setPosition(Pnt2f(offsetX, offsetY));
				//endEditCP(Components[i], Component::PositionFieldMask);

				// get to the next row
				if (AxisIndex)
				{
					offsetX += Components[i]->getSize()[(AxisIndex+1)%2]+gap[(AxisIndex+1)%2];
					offsetY += -offsetMajorAxis;
				}
				else
				{
					offsetX += -offsetMajorAxis;
					offsetY += Components[i]->getSize()[(AxisIndex+1)%2]+gap[(AxisIndex+1)%2];
				}
				// update cumMinorAxis, other values should still be at 0
                cumMinorAxis += Components[i]->getSize()[(AxisIndex+1)%2];
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
				maxMinorAxis = Components[i]->getSize()[(AxisIndex+1)%2];
				// update cumMajorAxis
				cumMajorAxis += Components[i]->getSize()[AxisIndex];
			}
		}
		else if (cumMajorAxis + Components[i]->getSize()[AxisIndex] + gap[AxisIndex]*(i-prevComponent) > totalMajorAxis) // this one draws up to i
		{
			// The numGaps is one less than the number of components being drawn, but it
			// is actually translates once for each component, so it must be compensated
			// when returning to the next row.
			numGaps = i-prevComponent-1;

			// find how far to translate to make it properly aligned
			offsetMajorAxis = getMajorAxisAlignment()*(totalMajorAxis - (cumMajorAxis+numGaps*gap[AxisIndex]));
			

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
				offsetMinorAxis = (maxMinorAxis-Components[j]->getSize()[(AxisIndex+1)%2])*getComponentAlignment();

				// translate to make it properly aligned
				if (AxisIndex)
				{	
					offsetX += offsetMinorAxis;
				}
				else
				{
					offsetY += offsetMinorAxis;
				}

				//beginEditCP(Components[j], Component::PositionFieldMask);
					Components[j]->setPosition(Pnt2f(offsetX, offsetY));
				//endEditCP(Components[j], Component::PositionFieldMask);

				// translate to next button
				if (AxisIndex)
				{
					offsetX+=-(Real64)offsetMinorAxis;
					offsetY+= Components[j]->getSize()[AxisIndex] + gap[AxisIndex];
				}
				else
				{
					offsetX+=Components[j]->getSize()[AxisIndex] + gap[AxisIndex];
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
			maxMinorAxis = Components[i]->getSize()[(AxisIndex+1)%2];
			prevComponent = i;
			cumMajorAxis = Components[i]->getSize()[AxisIndex];
		}
		else
		{
			// update the maxMinorAxis
			if (Components[i]->getSize()[(AxisIndex+1)%2] > maxMinorAxis)
				maxMinorAxis = Components[i]->getSize()[(AxisIndex+1)%2];
			// update cumMajorAxis
			cumMajorAxis += Components[i]->getSize()[AxisIndex];
		}
		if (i+1 == Components.size() && !firstOne) // if on the last one, draw the last buttons
		{
			numGaps = i-prevComponent;

			// find how far to translate to make it properly aligned
			offsetMajorAxis = getMajorAxisAlignment()*(totalMajorAxis - (cumMajorAxis+numGaps*gap[AxisIndex]));

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
				offsetMinorAxis = (maxMinorAxis-Components[j]->getSize()[(AxisIndex+1)%2])*getComponentAlignment();

				// translate to make it properly aligned
				if (AxisIndex)
				{
					offsetX += offsetMinorAxis;
				}
				else
				{
					offsetY += offsetMinorAxis;
				}
				//beginEditCP(Components[j], Component::PositionFieldMask);
					Components[j]->setPosition(Pnt2f(offsetX, offsetY));
				//endEditCP(Components[j], Component::PositionFieldMask);

				if (AxisIndex)
				{
					offsetX += -(Real64)offsetMinorAxis;
					offsetY += Components[j]->getSize()[AxisIndex] + gap[AxisIndex];
				}
				else
				{
					offsetX += Components[j]->getSize()[AxisIndex] + gap[AxisIndex];
					offsetY+= -(Real64)offsetMinorAxis;
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
	//Minor Axis Alignment
	Real32 displacement(borderSize[(AxisIndex+1)%2]-cumMinorAxis);
	Pnt2f offset;
	displacement *= getMinorAxisAlignment(); 
	for (UInt32 i = 0; i < Components.size(); ++i)
	{
		offset = Components[i]->getPosition();
		offset[(AxisIndex+1)%2] += displacement;
		//beginEditCP(Components[i], Component::PositionFieldMask);
			Components[i]->setPosition(offset);
		//endEditCP(Components[i], Component::PositionFieldMask);
	}
    
	for(UInt32 i=0 ; i<Components.size(); ++i)
    {
        endEditCP(Components[i], Component::PositionFieldMask | Component::SizeFieldMask);
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

