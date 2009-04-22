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
#include <OpenSG/UserInterface/OSGRotatedComponent.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGUIDrawUtils.h>
#include <OpenSG/Toolbox/OSGMathUtils.h>

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

            beginEditCP(getOverlayPanel(), Panel::LayoutFieldMask);
            getOverlayPanel()->setLayout(AbsoluteLayout::create());
            endEditCP(getOverlayPanel(), Panel::LayoutFieldMask);
		}

		Vec3f IndicatorDelta;
        Pnt2f ViewpointPos;
        Pnt2f IndicatorPos;
        ViewpointPos = TheMiniMap->getComponentSpace(TheMiniMap->getViewPointIndicator());
		for(UInt32 i(0) ; i<getIndicators().size() ; ++i)
		{
			//Calculate the Direction
            IndicatorPos = TheMiniMap->getComponentSpace(getIndicators(i));
			IndicatorDelta = IndicatorPos - ViewpointPos;
            IndicatorDelta.normalize();

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

                RotatedComponentPtr EmbededRotatedComponent = RotatedComponent::create();
                beginEditCP(EmbededRotatedComponent, RotatedComponent::InternalComponentFieldMask | RotatedComponent::ResizePolicyFieldMask | RotatedComponent::ConstraintsFieldMask);
                    EmbededRotatedComponent->setInternalComponent(TheComponent);
                    EmbededRotatedComponent->setResizePolicy(RotatedComponent::RESIZE_TO_MIN);
                    EmbededRotatedComponent->setConstraints(AbsoluteLayoutConstraints::create());
                endEditCP(EmbededRotatedComponent, RotatedComponent::InternalComponentFieldMask | RotatedComponent::ResizePolicyFieldMask | RotatedComponent::ConstraintsFieldMask);
    
				//Create the Component for this indicator
				beginEditCP(DirectionalIndicatorMiniMapOverlayPtr(this), IndicatorComponentsFieldMask);
					getIndicatorComponents().push_back(EmbededRotatedComponent);
				endEditCP(DirectionalIndicatorMiniMapOverlayPtr(this), IndicatorComponentsFieldMask);
			}
            //Determine if the Component is completely visible
            Pnt2f TopLeft,BottomRight;
            TheMiniMap->getBounds(TopLeft,BottomRight);
            beginEditCP(getIndicatorComponents(i), Component::VisibleFieldMask);
				getIndicatorComponents(i)->setVisible(!isContainedBounds(IndicatorPos,TopLeft,BottomRight));
			endEditCP(getIndicatorComponents(i), Component::VisibleFieldMask);


            Vec3f MapYAxis(0.0f,-1.0f,0.0f);
            Quaternion Rot(MapYAxis, IndicatorDelta);

            Vec3f Axis;
            Real32 IndicatorAngle;
            Rot.getValueAsAxisRad(Axis,IndicatorAngle);

            if(MapYAxis.cross(IndicatorDelta).z() > 0)
            {
                IndicatorAngle = -IndicatorAngle;
            }

            //Update the Component Rotation
            beginEditCP(getIndicatorComponents(i), RotatedComponent::AngleFieldMask);
                RotatedComponentPtr::dcast(getIndicatorComponents(i))->setAngle(IndicatorAngle);
            endEditCP(getIndicatorComponents(i), RotatedComponent::AngleFieldMask);

            Pnt2f Pos;
            Pnt2f p1((TopLeft + BottomRight)*0.5);
            Vec2f v1(IndicatorDelta);
            Real32 s_min(-1.0);
            Pnt2f Intersect_min;
            UInt8 Side(-1);
            if(IndicatorDelta.x() > 0)  //Right
            {
                Pnt2f p2(BottomRight.x(),TopLeft.y());
                Vec2f v2(0.0, BottomRight.y()-TopLeft.y());
                
                Real32 s,t;
                Pnt2f Intersect;
                if(intersectLines(p1,v1,p2,v2,s,t,Intersect) == 1 &&
                    s > 0.0 &&
                    t >= 0.0 &&
                    t <= 1.0 &&
                    (s_min < 0.0 || s < s_min) )
                {
                    s_min = s;
                    Intersect_min = Intersect;
                    Side = 0;
                }
            }
            if(IndicatorDelta.x() < 0)  //Left
            {
                Vec2f v2(0.0, BottomRight.y()-TopLeft.y());
                
                Real32 s,t;
                Pnt2f Intersect;
                if(intersectLines(p1,v1,TopLeft,v2,s,t,Intersect) == 1 &&
                    s > 0.0 &&
                    t >= 0.0 &&
                    t <= 1.0 &&
                    (s_min < 0.0 || s < s_min) )
                {
                    s_min = s;
                    Intersect_min = Intersect;
                    Side = 1;
                }
            }
            if(IndicatorDelta.y() < 0)  //Top
            {
                Vec2f v2(BottomRight.x()-TopLeft.x(),0.0);
                
                Real32 s,t;
                Pnt2f Intersect;
                if(intersectLines(p1,v1,TopLeft,v2,s,t,Intersect) == 1 &&
                    s > 0.0 &&
                    t >= 0.0 &&
                    t <= 1.0 &&
                    (s_min < 0.0 || s < s_min) )
                {
                    s_min = s;
                    Intersect_min = Intersect;
                    Side = 2;
                }
            }
            if(IndicatorDelta.y() > 0)  //Bottom
            {
                Pnt2f p2(TopLeft.x(),BottomRight.y());
                Vec2f v2(BottomRight.x()-TopLeft.x(), 0.0);
                
                Real32 s,t;
                Pnt2f Intersect;
                if(intersectLines(p1,v1,p2,v2,s,t,Intersect) == 1 &&
                    s > 0.0 &&
                    t >= 0.0 &&
                    t <= 1.0 &&
                    (s_min < 0.0 || s < s_min) )
                {
                    s_min = s;
                    Intersect_min = Intersect;
                    Side = 3;
                }
            }

            switch(Side)
            {
            case 0:   //Right
                Pos = calculateAlignment(Pnt2f(0.0,0.0),
                                         getOverlayPanel()->getSize(),
                                         getIndicatorComponents(i)->getSize(),
                                         (Intersect_min.y() - TopLeft.y())/(BottomRight.y()-TopLeft.y()),
                                         1.0f);
                break;
            case 1:   //Left
                Pos = calculateAlignment(Pnt2f(0.0,0.0),
                                         getOverlayPanel()->getSize(),
                                         getIndicatorComponents(i)->getSize(),
                                         (Intersect_min.y() - TopLeft.y())/(BottomRight.y()-TopLeft.y()),
                                         0.0f);
                break;
            case 2:   //Top
                Pos = calculateAlignment(Pnt2f(0.0,0.0),
                                         getOverlayPanel()->getSize(),
                                         getIndicatorComponents(i)->getSize(),
                                         0.0f,
                                         (Intersect_min.x() - TopLeft.x())/(BottomRight.x()-TopLeft.x()));
                break;
            case 3:   //Bottom
                Pos = calculateAlignment(Pnt2f(0.0,0.0),
                                         getOverlayPanel()->getSize(),
                                         getIndicatorComponents(i)->getSize(),
                                         1.0f,
                                         (Intersect_min.x() - TopLeft.x())/(BottomRight.x()-TopLeft.x()));
                break;
            }
			//Update the Component Position
            AbsoluteLayoutConstraintsPtr CompConstraints = AbsoluteLayoutConstraints::Ptr::dcast(getIndicatorComponents(i)->getConstraints());

			beginEditCP(CompConstraints, AbsoluteLayoutConstraints::PositionFieldMask);
				CompConstraints->setPosition(Pos);
			endEditCP(CompConstraints, AbsoluteLayoutConstraints::PositionFieldMask);
			
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

