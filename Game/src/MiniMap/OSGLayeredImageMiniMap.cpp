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

#include "OSGLayeredImageMiniMap.h"
#include "MiniMap/Indicators/OSGMiniMapIndicator.h"
#include "MiniMap/Indicators/OSGMiniMapIndicatorComponentGenerator.h"

#include <OpenSG/Toolbox/OSGTextureUtils.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGImageComponent.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::LayeredImageMiniMap
A LayeredImageMiniMap. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LayeredImageMiniMap::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void LayeredImageMiniMap::updateAllTransformations(void)
{
	//Viewpoint Indicator
	Pnt3f p;
	Quaternion r;

	getViewPointIndicator()->getTransformation(p,r);
	
	getTransformation()->transform(p);
	getTransformation()->transform(r);


	ViewPointLocation.setValues(p.x(), p.y());
	ViewPointOrientation = r;

	//All other Indicators
	InidicatorLocations.resize(getIndicators().size());
	InidicatorOrientations.resize(getIndicators().size());
	for(UInt32 i(0) ; i<getIndicators().size() ; ++i)
	{
		getIndicators(i)->getTransformation(p,r);
		
		getTransformation()->transform(p);
		getTransformation()->transform(r);


		InidicatorLocations[i].setValues(p.x(), p.y());
		InidicatorOrientations[i] = r;
	}
	
    if(_RotatedIndicator != NullFC)
    {
        //Update Rotation Angle
        Vec3f MapXAxis(1.0f,0.0f,0.0f), ViewPointXAxis;
        ViewPointOrientation.multVec(MapXAxis,ViewPointXAxis);
        Quaternion Rot(MapXAxis, ViewPointXAxis);

        Vec3f Axis;
        Real32 Angle;
        Rot.getValueAsAxisRad(Axis,Angle);
        
        if(Axis.y()<0.0f)
        {
            Angle = -Angle;
        }

        if(getStationaryIndicator())
        {
        }
        else
        {
        beginEditCP(_RotatedIndicator, RotatedComponent::AngleFieldMask);
           _RotatedIndicator->setAngle(Angle);
        endEditCP(_RotatedIndicator, RotatedComponent::AngleFieldMask);

        //Update Rotated Component Position
        AbsoluteLayoutConstraintsPtr RotatedComponentConstraints = AbsoluteLayoutConstraints::Ptr::dcast(_RotatedIndicator->getConstraints());
        Pnt2f AlignedPosition = Pnt2f(ViewPointLocation.x()*getSize().x(),ViewPointLocation.y()*getSize().y()) - 0.5f*_RotatedIndicator->getSize();
        beginEditCP(RotatedComponentConstraints, AbsoluteLayoutConstraints::PositionFieldMask);
            RotatedComponentConstraints->setPosition(AlignedPosition);
        endEditCP(RotatedComponentConstraints, AbsoluteLayoutConstraints::PositionFieldMask);
        }
    }

	if(_MapImageComponent != NullFC)
	{
		//Update Map Image Component
		Pnt3f ViewPoint;
		Quaternion ViewOrientation;

		getViewPointIndicator()->getTransformation(ViewPoint,ViewOrientation);

		if(getLayerTextures().getSize() > 1)
		{
		   _DrawnLayerIndex = -1;
		   if(ViewPoint.y() < (getLayerDistances().getValue(0) + (getLayerDistances().getValue(1) * 0.5)))
		   {
			   _DrawnLayerIndex = 0;
		   }

		   UInt32 index = 1;
		   Real32 lowerDistance = getLayerDistances().getValue(0);

		   while(_DrawnLayerIndex == -1)
		   {
		       
			   if(getLayerTextures().size() > 2 && ViewPoint.y() >= (lowerDistance + (getLayerDistances().getValue(index) * 0.5)) && ViewPoint.y() < (lowerDistance + getLayerDistances().getValue(index) + (lowerDistance + (getLayerDistances().getValue(index + 1) * 0.5))))
			   {
				   _DrawnLayerIndex = index;
			   }
			   else if(getLayerTextures().getSize() > index + 2)
			   {
				   lowerDistance += getLayerDistances().getValue(index);
				   index++;
			   }
			   else
			   {
				   _DrawnLayerIndex = index + 1;
			   }
		   }
		}
		else
		{
		   _DrawnLayerIndex = 0;
		}
	
		beginEditCP(_MapImageComponent , ImageComponent::TextureFieldMask | ImageComponent::RolloverTextureFieldMask | ImageComponent::DisabledTextureFieldMask | ImageComponent::FocusedTextureFieldMask);
			_MapImageComponent->setTexture(getLayerTextures(_DrawnLayerIndex));
			_MapImageComponent->setRolloverTexture(getLayerTextures(_DrawnLayerIndex));
			_MapImageComponent->setDisabledTexture(getLayerTextures(_DrawnLayerIndex));
			_MapImageComponent->setFocusedTexture(getLayerTextures(_DrawnLayerIndex));
		endEditCP(_MapImageComponent , ImageComponent::TextureFieldMask | ImageComponent::RolloverTextureFieldMask | ImageComponent::DisabledTextureFieldMask | ImageComponent::FocusedTextureFieldMask);
	}
}


void LayeredImageMiniMap::removeLayer(UInt32 index)
{
	if(index > getLayerTextures().size())
	{
		return;
	}

	MFTextureChunkPtr::iterator TexturesRemoveIter(getLayerTextures().begin());
	MFReal32::iterator DistancesRemoveIter(getLayerDistances().begin());

	for( UInt32 i(0) ; i<index; ++i)
	{
		++TexturesRemoveIter;
		++DistancesRemoveIter;
	}

	getLayerTextures().erase(TexturesRemoveIter);
    getLayerDistances().erase(DistancesRemoveIter);
}

void LayeredImageMiniMap::insertLayer(UInt32 index, Real32 DistanceFromPrevious, ImagePtr Image) // meant to insert new image at given index
{
	TextureChunkPtr Tex;
	Tex = createTexture(Image);
	
	if(index > getLayerTextures().size())
	{
		getLayerTextures().push_back(Tex);
		return;
	}

	MFTextureChunkPtr::iterator TexturesAddIter(getLayerTextures().begin());
	MFReal32::iterator DistancesAddIter(getLayerDistances().begin());

	for( UInt32 i(0) ; i<index; ++i)
	{
		++TexturesAddIter;
		++DistancesAddIter;
	}


	getLayerTextures().insert(TexturesAddIter, Tex);
    getLayerDistances().insert(DistancesAddIter, DistanceFromPrevious);
}


void LayeredImageMiniMap::setLayer(UInt32 index, Real32 DistanceFromPrevious, ImagePtr Image) // Overwrites the image at that location 
{
	if(index > getLayerTextures().size())
	{
		return;
	}
	
	beginEditCP(getLayerTextures()[index], TextureChunk::ImageFieldMask);
		getLayerTextures()[index]->setImage(Image);
	endEditCP(getLayerTextures()[index], TextureChunk::ImageFieldMask);
    
	beginEditCP(LayeredImageMiniMapPtr(this), LayerDistancesFieldMask);
        getLayerDistances()[index] = DistanceFromPrevious;
	endEditCP(LayeredImageMiniMapPtr(this), LayerDistancesFieldMask);
}

void LayeredImageMiniMap::insertLayer(ImagePtr Image, Real32 DistanceFromPrevious) // Image is pushed onto the back of the stack
{
	TextureChunkPtr Tex;
	Tex = createTexture(Image);

	beginEditCP(LayeredImageMiniMapPtr(this), LayerTexturesFieldMask | LayerDistancesFieldMask);
	    getLayerTextures().push_back(Tex);
	    getLayerDistances().push_back(DistanceFromPrevious);
	endEditCP(LayeredImageMiniMapPtr(this), LayerTexturesFieldMask | LayerDistancesFieldMask);
}

void LayeredImageMiniMap::drawInternal(const GraphicsPtr Graphics) const
{
	const_cast<LayeredImageMiniMap*>(this)->updateAllTransformations();

	Container::drawInternal(Graphics);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void LayeredImageMiniMap::setupDrawInternals(void)
{
	AbsoluteLayoutConstraintsPtr RotatedComponentConstraints = AbsoluteLayoutConstraints::create();

    if(getViewPointIndicator() != NullFC && getViewPointIndicator()->getGenerator() != NullFC)
    {
		if(getViewPointIndicator()->getGenerator()->getType().isDerivedFrom(MiniMapIndicatorComponentGenerator::getClassType()))
        {
            _ViewpointIndicatorComponent = MiniMapIndicatorComponentGenerator::Ptr::dcast(getViewPointIndicator()->getGenerator())->getMiniMapComponent(LayeredImageMiniMapPtr(this), false, false);
        }
        else
        {
            _ViewpointIndicatorComponent = getViewPointIndicator()->getGenerator()->getComponent(LayeredImageMiniMapPtr(this),SharedFieldPtr(), 0, 0,false, false);
        }
		beginEditCP(_ViewpointIndicatorComponent, Component::OpacityFieldMask);
			_ViewpointIndicatorComponent->setOpacity(getOpacity());
		endEditCP(_ViewpointIndicatorComponent, Component::OpacityFieldMask);
    }
	if(_MapImageComponent == NullFC && !_mfLayerTextures.empty())
	{
		//AbsoluteLayoutConstraintsPtr RotatedComponentConstraints = AbsoluteLayoutConstraints::create();

		_MapImageComponent = ImageComponent::create();
		Pnt2f TopLeft, BottomRight;
		getInsideBorderBounds(TopLeft, BottomRight);
		beginEditCP(_MapImageComponent, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask | Component::OpacityFieldMask);
			if(getLockMapOrientation())
			{
				//_MapImageComponent->setPreferredSize(getUnlockedMapSize());
			}
			else
			{
				_MapImageComponent->setPreferredSize(getSize());
			}
			_MapImageComponent->setScale(ImageComponent::SCALE_STRETCH);
			_MapImageComponent->setAlignment(Vec2f(0.5,0.5));
			_MapImageComponent->setOpacity(getOpacity());
		endEditCP(_MapImageComponent, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask | Component::OpacityFieldMask);
		/*_RotatedMap = RotatedComponent::create();
		beginEditCP(_RotatedMap, RotatedComponent::InternalComponentFieldMask | RotatedComponent::ResizePolicyFieldMask | RotatedComponent::ConstraintsFieldMask);
            _RotatedMap->setInternalComponent(_ViewpointIndicatorComponent);
            _RotatedMap->setResizePolicy(RotatedComponent::RESIZE_TO_MIN);
            _RotatedMap->setConstraints(RotatedComponentConstraints);
        endEditCP(_RotatedMap, RotatedComponent::InternalComponentFieldMask | RotatedComponent::ResizePolicyFieldMask | RotatedComponent::ConstraintsFieldMask);*/
		
	}

    _RotatedIndicator = RotatedComponent::create();
    beginEditCP(_RotatedIndicator, RotatedComponent::InternalComponentFieldMask | RotatedComponent::ResizePolicyFieldMask | RotatedComponent::ConstraintsFieldMask);
		if(!getLockMapOrientation())
		{
			_RotatedIndicator->setInternalComponent(_ViewpointIndicatorComponent);
		}
		else
		{
			_RotatedIndicator->setInternalComponent(_MapImageComponent);
		}
        _RotatedIndicator->setResizePolicy(RotatedComponent::RESIZE_TO_MIN);
        _RotatedIndicator->setConstraints(RotatedComponentConstraints);
    endEditCP(_RotatedIndicator, RotatedComponent::InternalComponentFieldMask | RotatedComponent::ResizePolicyFieldMask | RotatedComponent::ConstraintsFieldMask);

    AbsoluteLayoutPtr MiniMapLayout = AbsoluteLayout::create();
    beginEditCP(LayeredImageMiniMapPtr(this) , ChildrenFieldMask | LayoutFieldMask);
	    getChildren().clear();
		if(!getLockMapOrientation())
		{
			if(_MapImageComponent != NullFC)
			{
				getChildren().push_back(_MapImageComponent);
			}
		}
		else
		{
			if(_ViewpointIndicatorComponent != NullFC)
			{
				getChildren().push_back(_ViewpointIndicatorComponent);
			}
		}
		if(_RotatedIndicator != NullFC)
		{
			getChildren().push_back(_RotatedIndicator);
		}
        setLayout(MiniMapLayout);
    endEditCP(LayeredImageMiniMapPtr(this) , ChildrenFieldMask | LayoutFieldMask);
}
/*----------------------- constructors & destructors ----------------------*/

LayeredImageMiniMap::LayeredImageMiniMap(void) :
    Inherited()
{
}

LayeredImageMiniMap::LayeredImageMiniMap(const LayeredImageMiniMap &source) :
    Inherited(source)
{
}

LayeredImageMiniMap::~LayeredImageMiniMap(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LayeredImageMiniMap::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if((whichField & IndicatorsFieldMask) || 
	   (whichField & ViewPointIndicatorFieldMask) || 
	   (whichField & LayerTexturesFieldMask))
	{
		setupDrawInternals();
	}

	if((whichField & SizeFieldMask) && _MapImageComponent != NullFC)
	{
		if(!getLockMapOrientation())
		{
			beginEditCP(_MapImageComponent, ImageComponent::PreferredSizeFieldMask);
				_MapImageComponent->setPreferredSize(getSize());
			endEditCP(_MapImageComponent, ImageComponent::PreferredSizeFieldMask);
		}
	}

	if((whichField & OpacityFieldMask))
	{
		if(_MapImageComponent != NullFC)
		{
			beginEditCP(_MapImageComponent, OpacityFieldMask);
				_MapImageComponent->setOpacity(getOpacity());
			endEditCP(_MapImageComponent, OpacityFieldMask);
		}
		if(_ViewpointIndicatorComponent != NullFC)
		{
			beginEditCP(_ViewpointIndicatorComponent, OpacityFieldMask);
				_ViewpointIndicatorComponent->setOpacity(getOpacity());
			endEditCP(_ViewpointIndicatorComponent, OpacityFieldMask);
		}
	}
}

void LayeredImageMiniMap::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump LayeredImageMiniMap NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGLAYEREDIMAGEMINIMAPBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGLAYEREDIMAGEMINIMAPBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGLAYEREDIMAGEMINIMAPFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

