/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
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

#define OSG_COMPILEGAMELIB

#include <OpenSG/OSGConfig.h>

#include "OSGDirectionalIndicatorMiniMapOverlay.h"
#include "OSGDirectionalIndicatorComponentGenerator.h"
#include "MiniMap/OSGMiniMap.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DirectionalIndicatorMiniMapOverlay
A MiniMapOverlay. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DirectionalIndicatorMiniMapOverlay::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DirectionalIndicatorMiniMapOverlay::update(MiniMapPtr TheMiniMap, PanelPtr OverlayPanel, const Vec2f& TopLeft, const Vec3f& BottomRight)
{
	if(!TheMiniMap->getLockMapOrientation())
	{
		if(getOverlayPanel() == NullFC)
		{
			beginEditCP(DirectionalIndicatorMiniMapOverlayPtr(this), OverlayPanelFieldMask);
				setOverlayPanel(Panel::createEmpty());
			endEditCP(DirectionalIndicatorMiniMapOverlayPtr(this), OverlayPanelFieldMask);
		}

		Vec3f IndicatorDelta;
		for(UInt32 i(0) ; i<getIndicators().size() ; ++i)
		{
			//Calculate the Direction
			IndicatorDelta = Vec3f(0.0,0.0,0.0);

			//Add Component if necissary
			if(getIndicatorComponents().size() < i+1)
			{
				ComponentPtr TheComponent;
				if(getDirectionComponentGenerator()->getType().isDerivedFrom(DirectionalIndicatorComponentGenerator::getClassType()))
				{
					TheComponent = DirectionalIndicatorComponentGenerator::Ptr::dcast(getDirectionComponentGenerator())->getDirectionalComponent(TheMiniMap, getIndicators(i), IndicatorDelta, false);
				}
				else
				{
					TheComponent = getDirectionComponentGenerator()->getComponent(TheMiniMap,boost::any(getIndicators(i)),0,0,false,false);
				}

				//Create the Component for this indicator
				beginEditCP(DirectionalIndicatorMiniMapOverlayPtr(this), IndicatorComponentsFieldMask);
					getIndicatorComponents().push_back(TheComponent);
				endEditCP(DirectionalIndicatorMiniMapOverlayPtr(this), IndicatorComponentsFieldMask);
			}

			//Update the Component Position and direction
			beginEditCP(getIndicatorComponents(i), Component::PositionFieldMask | Component::SizeFieldMask);
				getIndicatorComponents(i)->setPosition(Vec2f(0.0f,0.0f));
				getIndicatorComponents(i)->setSize(Vec2f(20.0,20.0));
			endEditCP(getIndicatorComponents(i), Component::PositionFieldMask | Component::SizeFieldMask);
			
		}

		//Add Components to the Panel
		beginEditCP(getOverlayPanel(), Panel::ChildrenFieldMask);
			getOverlayPanel()->getChildren().clear();
			for(UInt32 i(0) ; i<getIndicatorComponents().size() ; ++i)
			{
				getOverlayPanel()->getChildren().push_back(getIndicatorComponents(i));
			}
		endEditCP(getOverlayPanel(), Panel::ChildrenFieldMask);
	}
}

PanelPtr DirectionalIndicatorMiniMapOverlay::getPanel(void) const
{
    return getOverlayPanel();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DirectionalIndicatorMiniMapOverlay::DirectionalIndicatorMiniMapOverlay(void) :
    Inherited()
{
}

DirectionalIndicatorMiniMapOverlay::DirectionalIndicatorMiniMapOverlay(const DirectionalIndicatorMiniMapOverlay &source) :
    Inherited(source)
{
}

DirectionalIndicatorMiniMapOverlay::~DirectionalIndicatorMiniMapOverlay(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DirectionalIndicatorMiniMapOverlay::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DirectionalIndicatorMiniMapOverlay::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DirectionalIndicatorMiniMapOverlay NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDIRECTIONALINDICATORMINIMAPOVERLAYBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDIRECTIONALINDICATORMINIMAPOVERLAYBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDIRECTIONALINDICATORMINIMAPOVERLAYFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

