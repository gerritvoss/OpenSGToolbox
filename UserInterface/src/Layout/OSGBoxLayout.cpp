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
#include "OSGBoxLayout.h"
#include "OSGUserInterfaceDef.h"
#include "Util/OSGUIDrawUtils.h"
#include "Component/Container/OSGContainer.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::BoxLayout
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

void BoxLayout::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void BoxLayout::updateLayout(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
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
	Container::Ptr::dcast(ParentComponent)->getInsideInsetsBounds(borderTopLeft, borderBottomRight);
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
	for(UInt32 i=0 ; i<Components.size() ; ++i)
	{	// set the component to its preferred size
		// get sum of all components
		totalMajorAxis += Components[i]->getPreferredSize()[AxisIndex];
		if (Components[i]->getPreferredSize()[(AxisIndex+1)%2] > largestMinorAxis)
			largestMinorAxis = Components[i]->getPreferredSize()[(AxisIndex+1)%2];
	}
	if(MajorAxis > totalMajorAxis)
	{
		spacing = (MajorAxis-totalMajorAxis)/(Components.size()+1);
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
		borderTopLeft[AxisIndex] += (MajorAxis - (spacing*(Components.size()+1)+totalMajorAxis))*getMajorAxisAlignment() + spacing;
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
	for(UInt32 i=0; i<Components.size(); ++i)
	{	
		// for each individual button, keep track of the offsetMinorAxis in height
		// for use in keeping them vertically centered
		offset[(AxisIndex+1)%2] = 0;
		// change the component's height only if necessary
		if (largestMinorAxis > Components[i]->getPreferredSize()[(AxisIndex+1)%2])
		{	
			if (largestMinorAxis <= Components[i]->getMaxSize()[(AxisIndex+1)%2])
			{	// for when the max height is larger than the largestMinorAxis
				size[AxisIndex] = Components[i]->getPreferredSize()[AxisIndex];
				size[(AxisIndex+1)%2] = largestMinorAxis;
			}
			else
			{	// in this case, max out the button to its max height
				size[AxisIndex] = Components[i]->getPreferredSize()[AxisIndex];
				size[(AxisIndex+1)%2] = Components[i]->getMaxSize()[(AxisIndex+1)%2];

				// find how far to set offset to make this button properly aligned
				if(getOrientation() == HORIZONTAL_ORIENTATION)
				{
					offset = calculateAlignment(Pnt2s(0,0), Vec2f(0.0f, largestMinorAxis), Vec2f(0.0f,Components[i]->getMaxSize().y()), getComponentAlignment(), 0.0f);
				}
				else
				{
					offset = calculateAlignment(Pnt2s(0,0), Vec2f(largestMinorAxis,0.0f), Vec2f(Components[i]->getMaxSize().x(),0.0f), 0.0f, getComponentAlignment());
				}
			}
		}
		else
		{
			size = Components[i]->getPreferredSize();
		}
		beginEditCP(Components[i], Component::SizeFieldMask|Component::PositionFieldMask);
			Components[i]->setSize(size);
			Components[i]->setPosition(borderTopLeft + offset);
		endEditCP(Components[i], Component::SizeFieldMask|Component::PositionFieldMask);

		// now set offset for the next button
		offset[AxisIndex] += spacing + Components[i]->getPreferredSize()[AxisIndex];
	}
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

void BoxLayout::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void BoxLayout::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump BoxLayout NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGBOXLAYOUTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGBOXLAYOUTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGBOXLAYOUTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

