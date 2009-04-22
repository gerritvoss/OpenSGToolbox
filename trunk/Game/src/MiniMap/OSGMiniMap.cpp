/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *					Authors: David Kabala, Eric Langkamp					 *
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
#include <OpenSG/UserInterface/OSGPanel.h>

#include "OSGMiniMap.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::MiniMap
A Minimap. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MiniMap::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec3f MiniMap::getMapSpace(const Vec3f& Position) const
{
    Vec3f TransformedPosition(Position);
    
    getTransformation()->transform(TransformedPosition);

    return TransformedPosition;
}

void MiniMap::mousePressed(const MouseEvent& e)
{
	produceLocationSelected();
	Inherited::mousePressed(e);
}

void MiniMap::removeMiniMapListener(MiniMapListenerPtr Listener)
{
   MiniMapListenerSetItor EraseIter(_MiniMapListeners.find(Listener));
   if(EraseIter != _MiniMapListeners.end())
   {
      _MiniMapListeners.erase(EraseIter);
   }
}

void MiniMap::updateOverlays(void)
{
	for(UInt32 i(0) ; i<getOverlays().size() ; ++i)
	{
		getOverlays(i)->update(MiniMapPtr(this),NullFC, Vec3f(0.0,0.0),Vec2f(0.0,0.0));
	}

	updateOverlayPanels();
	attachAllOverlays();
}

void MiniMap::updateOverlayPanels(void)
{
	Vec2f InsetsTopLeft, InsetsBottomRight;
	this->getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

	PanelPtr ThePanel;
	for(UInt32 i(0) ; i<getOverlays().size() ; ++i)
	{
		ThePanel = getOverlays(i)->getPanel();
		
		beginEditCP(ThePanel, Panel::PositionFieldMask | Panel::PreferredSizeFieldMask);
			ThePanel->setPosition(InsetsTopLeft);
			ThePanel->setPreferredSize(InsetsBottomRight - InsetsTopLeft);
		endEditCP(ThePanel, Panel::PositionFieldMask | Panel::PreferredSizeFieldMask);
	}
}

void MiniMap::attachAllOverlays(void)
{
	PanelPtr AddedPanel;
	beginEditCP(MiniMapPtr(this), MiniMap::ChildrenFieldMask);
		for(UInt32 i(0) ; i<getOverlays().size() ; ++i)
		{
			AddedPanel = getOverlays(i)->getPanel();
			
			if(getChildren().find(AddedPanel) == getChildren().end())
			{
				getChildren().push_back(AddedPanel);
			}
		}
	endEditCP(MiniMapPtr(this), MiniMap::ChildrenFieldMask);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void MiniMap::updateAllTransformations(void)
{
}

void MiniMap::locationSelected(const MiniMapEvent& e)
{
}

void MiniMap::produceLocationSelected(void)
{
	MiniMapEvent e(MiniMapPtr(this), getTimeStamp());
    locationSelected(e);
	MiniMapListenerSet Listeners(_MiniMapListeners);
    for(MiniMapListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->locationSelected(e);
    }
}

/*----------------------- constructors & destructors ----------------------*/

MiniMap::MiniMap(void) :
    Inherited(),
		_TransformationChangedListener(MiniMapPtr(this))
{
}

MiniMap::MiniMap(const MiniMap &source) :
    Inherited(source),
		_TransformationChangedListener(MiniMapPtr(this))
{
}

MiniMap::~MiniMap(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MiniMap::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if((whichField & TransformationFieldMask) &&
		getTransformation() != NullFC)
	{
		getTransformation()->addChangeListener(&_TransformationChangedListener);
	}
	
	if((whichField & TransformationFieldMask) ||
		(whichField & IndicatorsFieldMask) ||
		(whichField & ViewPointIndicatorFieldMask))
	{
		updateAllTransformations();
	}

	if((whichField & SizeFieldMask))
	{
		updateOverlayPanels();
	}
	if((whichField & OverlaysFieldMask))
	{
		updateOverlays();
	}
}

void MiniMap::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump MiniMap NI" << std::endl;
}


void MiniMap::TransformationChangedListener::stateChanged(const ChangeEvent& e)
{
	_MiniMap->updateAllTransformations();
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
    static Char8 cvsid_hpp       [] = OSGMINIMAPBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMINIMAPBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMINIMAPFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

