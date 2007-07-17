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

#include "OSGBoxLayout.h"
#include "Util/OSGUIDefines.h"

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

void BoxLayout::draw(const MFComponentPtr Components,const ComponentPtr ParentComponent, const GraphicsPtr TheGraphics) const
{
	/*!
      totalMajorAxis will be the sum of the MajorAxis of all of the
	  components, which is compared to MajorAxis, which is MajorAxis of the parent
	  component. These two variables will be used to determine the spacing of
	  each of the objects.
    */
	UInt32 AxisIndex(0);
	if(getAlignment() != HORIZONTAL_ALIGNMENT ) AxisIndex = 1;

	Pnt2s borderOffset;
	Vec2s borderSize;
	ParentComponent->getInsideBorderBounds(borderOffset, borderSize);
	UInt32 MajorAxis(borderSize[AxisIndex]);
	UInt32 totalMajorAxis(0);
	UInt32 largestMinorAxis(0);
	UInt32 spacing(0);
	UInt32 oddSpacing(0);
	Int64 transBack(0);
	UInt32 offsetMinorAxis(0);
	Vec2s size;

	/*!
	  This first sweep through the components sets each component to its
	  preferred size, gets a sum of all the MajorAxiss, and finds the
	  largest height.
    */
	for(UInt32 i=0 ; i<Components.size() ; ++i)
	{	// set the component to its preferred size
		beginEditCP(Components.getValue(i), Component::SizeFieldMask);
			Components.getValue(i)->setSize(Components.getValue(i)->getPreferredSize());
		endEditCP(Components.getValue(i), Component::SizeFieldMask);
		// get sum of all components
		totalMajorAxis += Components.getValue(i)->getSize()[AxisIndex];
		if (Components.getValue(i)->getSize()[(AxisIndex+1)%2] > largestMinorAxis)
			largestMinorAxis = Components.getValue(i)->getSize()[(AxisIndex+1)%2];
	}
	if(MajorAxis > totalMajorAxis)
	{
		spacing = (MajorAxis-totalMajorAxis)/(Components.size()+1);
		// in the case where there isn't equal spacing between each button,
		// translate more the first time to center the components
		oddSpacing = (MajorAxis - (spacing*(Components.size()+1)+totalMajorAxis))/2;
		if (AxisIndex) glTranslatef(0, oddSpacing, 0);
		else  glTranslatef(oddSpacing, 0, 0);
		transBack -= oddSpacing;
	}

	/*!
	  This second sweep through the components sets each component to the
	  matching highest height, then draws each component equally spaced apart
    */
	glTranslatef(borderOffset.x(), borderOffset.y(), 0);
	for(UInt32 i=0 ; i<Components.size() ; ++i)
	{	
		// for each individual button, keep track of the offsetMinorAxis in height
		// for use in keeping them vertically centered
		offsetMinorAxis = 0;
		// change the component's height only if necessary
		if (largestMinorAxis > Components.getValue(i)->getSize()[(AxisIndex+1)%2])
		{	
			if (largestMinorAxis <= Components.getValue(i)->getMaxSize()[(AxisIndex+1)%2])
			{	// for when the max height is larger than the largestMinorAxis
				if (AxisIndex) 
				{
					size[0] = largestMinorAxis;
					size[1] = Components.getValue(i)->getSize()[AxisIndex];
				}
				else 
				{
					size[0] = Components.getValue(i)->getSize()[AxisIndex];
					size[1] = largestMinorAxis;
				}
				beginEditCP(Components.getValue(i), Component::SizeFieldMask);
					Components.getValue(i)->setSize(size);
				endEditCP(Components.getValue(i), Component::SizeFieldMask);
			}
			else
			{	// in this case, max out the button to its max height
				if (AxisIndex) 
				{
					size[0] = Components.getValue(i)->getMaxSize()[(AxisIndex+1)%2];
					size[1] = Components.getValue(i)->getSize()[AxisIndex];
				}
				else 
				{
					size[0] = Components.getValue(i)->getSize()[AxisIndex];
					size[1] = Components.getValue(i)->getMaxSize()[(AxisIndex+1)%2];
				}
				beginEditCP(Components.getValue(i), Component::SizeFieldMask);
					Components.getValue(i)->setSize(size);
				endEditCP(Components.getValue(i), Component::SizeFieldMask);

				// find how far to translate to make this button properly aligned
				if (getMinorAxisAlignment() == AXIS_MIN_ALIGNMENT)
				{
					offsetMinorAxis = 0;
				} else if (getMinorAxisAlignment() == AXIS_CENTER_ALIGNMENT)
				{
					offsetMinorAxis = (largestMinorAxis - Components.getValue(i)->getMaxSize()[(AxisIndex+1)%2])/2;
				} else 
				{
					offsetMinorAxis = largestMinorAxis - Components.getValue(i)->getMaxSize()[(AxisIndex+1)%2];
				}
			}
		}
		if (AxisIndex) glTranslatef(offsetMinorAxis, spacing, 0);
		else glTranslatef(spacing, offsetMinorAxis, 0);
		Components.getValue(i)->draw(TheGraphics);
		if (AxisIndex) glTranslatef(-(Int64)offsetMinorAxis, Components.getValue(i)->getSize()[AxisIndex], 0);
		else glTranslatef(Components.getValue(i)->getSize()[AxisIndex], -(Int64)offsetMinorAxis, 0);
		transBack -= spacing;
		transBack -= Components.getValue(i)->getSize()[AxisIndex];
	}
	// now translate back to the original spot
	glTranslatef(-borderOffset.x(), -borderOffset.y(), 0);
	if (AxisIndex) glTranslatef(0, transBack, 0);
	else glTranslatef(transBack, 0, 0);
}

void BoxLayout::updateLayout(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
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

