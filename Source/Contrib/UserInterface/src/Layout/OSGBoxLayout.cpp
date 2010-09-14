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

#include "OSGBoxLayout.h"
#include "OSGUIDrawUtils.h"
#include "OSGComponentContainer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGBoxLayoutBase.cpp file.
// To modify it, please change the .fcd file (OSGBoxLayout.fcd) and
// regenerate the base file.
/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::BoxLayout
A UI BoxLayout. 
Based off of the Java.swing boxLayout, which bears the following description:

BoxLayout attempts to arrange components at their preferred MajorAxiss (for
horizontal layout) or heights (for vertical layout). For a horizontal layout,
if not all the components are the same height, BoxLayout attempts to make all
the components as high as the highest component. If that's not possible for a
particular component, then BoxLayout aligns that component vertically,
according to the component's Y alignment. By default, a component has a Y
alignment of 0.5, which means that the vertical center of the component
should have the same Y coordinate as the vertical centers of other components
with 0.5 Y alignment.

Similarly, for a vertical layout, BoxLayout attempts to make all components
in the column as wide as the widest component. If that fails, it aligns them
horizontally according to their X alignments. For PAGE_AXIS layout,
horizontal alignment is done based on the leading edge of the component. In
other words, an X alignment value of 0.0 means the left edge of a component
if the container's ComponentOrientation is left to right and it means the
right edge of the component otherwise. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BoxLayout::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void BoxLayout::updateLayout(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
	/*!
      totalMajorAxis will be the sum of the MajorAxis of all of the
	  components, which is compared to MajorAxis, which is MajorAxis of the parent
	  component. These two variables will be used to determine the spacing of
	  each of the objects.
    */
	UInt32 AxisIndex(0);
	if(getOrientation() != HORIZONTAL_ORIENTATION ) AxisIndex = 1;

	Pnt2f borderTopLeft, borderBottomRight;
	dynamic_cast<const ComponentContainer*>(ParentComponent)->getInsideInsetsBounds(borderTopLeft, borderBottomRight);
	Vec2f borderSize(borderBottomRight-borderTopLeft);
	Real32 MajorAxis(borderSize[AxisIndex]);
	Real32 totalMajorAxis(0);
	Real32 largestMinorAxis(0);
	Real32 spacing(0);
	Vec2f size;
	Vec2f offset(0,0);

	/*!
	  This first sweep through the components sets each component to its
	  preferred size, gets a sum of all the MajorAxes, and finds the
	  largest height.
    */
	for(UInt32 i=0 ; i<Components->size() ; ++i)
	{	// set the component to its preferred size
		// get sum of all components
		totalMajorAxis += (*Components)[i]->getPreferredSize()[AxisIndex];
		if ((*Components)[i]->getPreferredSize()[(AxisIndex+1)%2] > largestMinorAxis)
			largestMinorAxis = (*Components)[i]->getPreferredSize()[(AxisIndex+1)%2];
	}
	if(MajorAxis > totalMajorAxis)
	{
		spacing = (MajorAxis-totalMajorAxis)/(Components->size()+1);
		// in the case where there isn't equal spacing between each button,
		// translate more the first time to center the components
		if(spacing < getMajorAxisMinimumGap())
		{
			spacing = getMajorAxisMinimumGap();
		}
		if(spacing > getMajorAxisMaximumGap())
		{
			spacing = getMajorAxisMaximumGap();
		}
		borderTopLeft[AxisIndex] += (MajorAxis - (spacing*(Components->size()+1)+totalMajorAxis))*getMajorAxisAlignment() + spacing;
	}
	else
	{
		spacing = getMajorAxisMinimumGap();
	}


	if(getOrientation() == HORIZONTAL_ORIENTATION)
	{
		borderTopLeft = calculateAlignment(borderTopLeft, borderSize, Vec2f(0.0f,largestMinorAxis), getMinorAxisAlignment(), 0.0f);
	}
	else
	{
		borderTopLeft = calculateAlignment(borderTopLeft, borderSize, Vec2f(largestMinorAxis,0.0f), 0.0f, getMinorAxisAlignment());
	}

	/*!
	  This second sweep through the components sets each component to the
	  matching highest height, then positions each component equally spaced apart
    */
    Pnt2f Pos;
	for(UInt32 i=0; i<Components->size(); ++i)
	{	
		// for each individual button, keep track of the offsetMinorAxis in height
		// for use in keeping them vertically centered
		offset[(AxisIndex+1)%2] = 0;
		// change the component's height only if necessary
		if (largestMinorAxis > (*Components)[i]->getPreferredSize()[(AxisIndex+1)%2])
		{	
			if (largestMinorAxis <= (*Components)[i]->getMaxSize()[(AxisIndex+1)%2])
			{	// for when the max height is larger than the largestMinorAxis
				size[AxisIndex] = (*Components)[i]->getPreferredSize()[AxisIndex];
				size[(AxisIndex+1)%2] = largestMinorAxis;
			}
			else
			{	// in this case, max out the button to its max height
				size[AxisIndex] = (*Components)[i]->getPreferredSize()[AxisIndex];
				size[(AxisIndex+1)%2] = (*Components)[i]->getMaxSize()[(AxisIndex+1)%2];

				// find how far to set offset to make this button properly aligned
				if(getOrientation() == HORIZONTAL_ORIENTATION)
				{
					offset = Vec2f(calculateAlignment(Pnt2f(0,0), Vec2f(0.0f, largestMinorAxis), Vec2f(0.0f,(*Components)[i]->getMaxSize().y()), getComponentAlignment(), 0.0f));
				}
				else
				{
					offset = Vec2f(calculateAlignment(Pnt2f(0,0), Vec2f(largestMinorAxis,0.0f), Vec2f((*Components)[i]->getMaxSize().x(),0.0f), 0.0f, getComponentAlignment()));
				}
			}
		}
		else
		{
			size = (*Components)[i]->getPreferredSize();
		}
        if((*Components)[i]->getSize() != size)
        {
		    (*Components)[i]->setSize(size);
        }
        Pos = borderTopLeft + offset;
        if((*Components)[i]->getPosition() != Pos)
        {
		    (*Components)[i]->setPosition(Pos);
        }

		// now set offset for the next button
		offset[AxisIndex] += spacing + (*Components)[i]->getPreferredSize()[AxisIndex];
	}
}


Vec2f BoxLayout::layoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent, SizeType TheSizeType) const
{
    Real32 MinorAxisMax(0.0f);
    Real32 MajorAxisSum(0.0f);
    
	UInt32 MajorAxisIndex(0);
	if(getOrientation() != HORIZONTAL_ORIENTATION ) MajorAxisIndex = 1;
    
	UInt32 MinorAxisIndex((MajorAxisIndex+1)%2);

    Vec2f ComponentSize;
    for(UInt32 i(0) ; i<Components->size() ; ++i)
    {
        ComponentSize = getComponentSize((*Components)[i],TheSizeType);
        if(ComponentSize[MinorAxisIndex] > MinorAxisMax)
        {
            MinorAxisMax = ComponentSize[MinorAxisIndex];
        }
        MajorAxisSum += ComponentSize[MajorAxisIndex];
    }

    Vec2f Result;
    Result[MajorAxisIndex] = MajorAxisSum;
    Result[MinorAxisIndex] = MinorAxisMax;
    return Result;
}

Vec2f BoxLayout::minimumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MIN_SIZE);
}

Vec2f BoxLayout::requestedContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, REQUESTED_SIZE);
}

Vec2f BoxLayout::preferredContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, PREFERRED_SIZE);
}

Vec2f BoxLayout::maximumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MAX_SIZE);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

BoxLayout::BoxLayout(void) :
    Inherited()
{
}

BoxLayout::BoxLayout(const BoxLayout &source) :
    Inherited(source)
{
}

BoxLayout::~BoxLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void BoxLayout::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & ( OrientationFieldMask |
                      MajorAxisAlignmentFieldMask |
                      MinorAxisAlignmentFieldMask |
                      ComponentAlignmentFieldMask |
                      MajorAxisMinimumGapFieldMask |
                      MajorAxisMaximumGapFieldMask))
    {
        updateParentContainers();
    }
}

void BoxLayout::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump BoxLayout NI" << std::endl;
}

OSG_END_NAMESPACE
