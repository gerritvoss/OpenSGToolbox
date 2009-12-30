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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGRGBColorChooserPanel.h"
#include "Component/Spinner/OSGSpinner.h"
#include "Component/Slider/OSGSlider.h"
#include "Component/Text/OSGLabel.h"
#include "Layout/OSGSpringLayout.h"
#include "Layout/OSGSpringLayoutConstraints.h"
#include "Layout/Spring/OSGLayoutSpring.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RGBColorChooserPanel
A UI RGBColorChooserPanel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RGBColorChooserPanel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


std::string RGBColorChooserPanel::getDisplayText(void) const
{
	if(getIncludeAlpha())
	{
		return std::string("RGBA");
	}
	else
	{
		return std::string("RGB");
	}
}

void RGBColorChooserPanel::updateChooser(void)
{
	dettachModelListener();

	Color4f ColorSelected(getColorFromModel());
	//Update the Red Bounded Range
    _RedModel->setValue(osgClamp(0.0f, getColorFromModel().red(), 1.0f) * 255);
	beginEditCP(_RedSliderTrackBackground, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask);
		_RedSliderTrackBackground->getColors().clear();
		_RedSliderTrackBackground->getStops().clear();
		_RedSliderTrackBackground->getColors().push_back(Color4f(0.0f,
			                                             ColorSelected.green(),
														 ColorSelected.blue(),
														 ColorSelected.alpha()));
		_RedSliderTrackBackground->getStops().push_back(0.0);
		_RedSliderTrackBackground->getColors().push_back(Color4f(1.0f,
			                                             ColorSelected.green(),
														 ColorSelected.blue(),
														 ColorSelected.alpha()));
		_RedSliderTrackBackground->getStops().push_back(1.0);
	endEditCP(_RedSliderTrackBackground, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask);

	//Update the Green Bounded Range
    _GreenModel->setValue(osgClamp(0.0f, getColorFromModel().green(), 1.0f) * 255);
	beginEditCP(_GreenSliderTrackBackground, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask);
		_GreenSliderTrackBackground->getColors().clear();
		_GreenSliderTrackBackground->getStops().clear();
		_GreenSliderTrackBackground->getColors().push_back(Color4f(ColorSelected.red(),
			                                             0.0f,
														 ColorSelected.blue(),
														 ColorSelected.alpha()));
		_GreenSliderTrackBackground->getStops().push_back(0.0);
		_GreenSliderTrackBackground->getColors().push_back(Color4f(ColorSelected.red(),
			                                             1.0f,
														 ColorSelected.blue(),
														 ColorSelected.alpha()));
		_GreenSliderTrackBackground->getStops().push_back(1.0);
	endEditCP(_GreenSliderTrackBackground, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask);

	//Update the Blue Bounded Range
    _BlueModel->setValue(osgClamp(0.0f, getColorFromModel().blue(), 1.0f) * 255);
	beginEditCP(_BlueSliderTrackBackground, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask);
		_BlueSliderTrackBackground->getColors().clear();
		_BlueSliderTrackBackground->getStops().clear();
		_BlueSliderTrackBackground->getColors().push_back(Color4f(ColorSelected.red(),
			                                             ColorSelected.green(),
														 0.0f,
														 ColorSelected.alpha()));
		_BlueSliderTrackBackground->getStops().push_back(0.0);
		_BlueSliderTrackBackground->getColors().push_back(Color4f(ColorSelected.red(),
			                                             ColorSelected.green(),
														 1.0f,
														 ColorSelected.alpha()));
		_BlueSliderTrackBackground->getStops().push_back(1.0);
	endEditCP(_BlueSliderTrackBackground, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask);

	//Update the Alpha Bounded Range
	_AlphaModel->setValue(osgClamp(0.0f, getColorFromModel().alpha(), 1.0f) * 255);
	
	if(getIncludeAlpha())
	{
		beginEditCP(_AlphaSliderTrackBackground, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask);
			_AlphaSliderTrackBackground->getColors().clear();
			_AlphaSliderTrackBackground->getStops().clear();
			_AlphaSliderTrackBackground->getColors().push_back(Color4f(ColorSelected.red(),
				                                             ColorSelected.green(),
															 ColorSelected.blue(),
															 0.0f));
		_AlphaSliderTrackBackground->getStops().push_back(0.0);
			_AlphaSliderTrackBackground->getColors().push_back(Color4f(ColorSelected.red(),
				                                             ColorSelected.green(),
															 ColorSelected.blue(),
															 1.0f));
		_AlphaSliderTrackBackground->getStops().push_back(1.0);
		endEditCP(_AlphaSliderTrackBackground, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask);
	}
	
	attachModelListener();
}

void RGBColorChooserPanel::buildChooser(void)
{
	//Bounded Range Models
    _RedModel->setMinimum(0);
    _RedModel->setMaximum(255);
	
    _GreenModel->setMinimum(0);
    _GreenModel->setMaximum(255);
	
    _BlueModel->setMinimum(0);
    _BlueModel->setMaximum(255);
	
    _AlphaModel->setMinimum(0);
    _AlphaModel->setMaximum(255);


	//Spinners
	_RedSpinner = Spinner::create();
	_RedSpinner->setModel(_RedModel->getSpinnerModel());
	
	_GreenSpinner = Spinner::create();
    _GreenSpinner->setModel(_GreenModel->getSpinnerModel());
	
	_BlueSpinner = Spinner::create();
    _BlueSpinner->setModel(_BlueModel->getSpinnerModel());
	
	if(getIncludeAlpha())
	{
		_AlphaSpinner = Spinner::create();
		_AlphaSpinner->setModel(_AlphaModel->getSpinnerModel());
	}

	//Sliders
	_RedSliderTrackBackground = GradientLayer::create();
	beginEditCP(_RedSliderTrackBackground, GradientLayer::StartPositionFieldMask | GradientLayer::EndPositionFieldMask);
		_RedSliderTrackBackground->setStartPosition(Vec2f(0.0f,0.0f));
		_RedSliderTrackBackground->setEndPosition(Vec2f(1.0f,0.0f));
	endEditCP(_RedSliderTrackBackground, GradientLayer::StartPositionFieldMask | GradientLayer::EndPositionFieldMask);
	
	UIDrawObjectCanvasPtr RedSliderTrackCanvas = UIDrawObjectCanvas::create();
	beginEditCP(RedSliderTrackCanvas, UIDrawObjectCanvas::PreferredSizeFieldMask | UIDrawObjectCanvas::BordersFieldMask | UIDrawObjectCanvas::BackgroundsFieldMask);
		RedSliderTrackCanvas->setPreferredSize(Vec2f(15,15));
		RedSliderTrackCanvas->setBorders(NullFC);
		RedSliderTrackCanvas->setBackgrounds(_RedSliderTrackBackground);
	endEditCP(RedSliderTrackCanvas, UIDrawObjectCanvas::PreferredSizeFieldMask | UIDrawObjectCanvas::BordersFieldMask | UIDrawObjectCanvas::BackgroundsFieldMask);

	_RedSlider = Slider::create();
	beginEditCP(_RedSlider, Slider::DrawLabelsFieldMask | Slider::DrawMajorTicksFieldId | Slider::DrawMinorTicksFieldMask | Slider::OrientationFieldMask | Slider::TrackDrawObjectFieldMask | Slider::RangeModelFieldMask);
		_RedSlider->setDrawLabels(false);
		_RedSlider->setDrawMajorTicks(false);
		_RedSlider->setDrawMinorTicks(false);
		_RedSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);
		_RedSlider->setTrackDrawObject(RedSliderTrackCanvas);
        _RedSlider->setRangeModel(_RedModel->getBoundedRangeModel());
	endEditCP(_RedSlider, Slider::DrawLabelsFieldMask | Slider::DrawMajorTicksFieldId | Slider::DrawMinorTicksFieldMask | Slider::OrientationFieldMask | Slider::TrackDrawObjectFieldMask | Slider::RangeModelFieldMask);
	
	//Green
	_GreenSliderTrackBackground = GradientLayer::create();
	beginEditCP(_GreenSliderTrackBackground, GradientLayer::StartPositionFieldMask | GradientLayer::EndPositionFieldMask);
		_GreenSliderTrackBackground->setStartPosition(Vec2f(0.0f,0.0f));
		_GreenSliderTrackBackground->setEndPosition(Vec2f(1.0f,0.0f));
	endEditCP(_GreenSliderTrackBackground, GradientLayer::StartPositionFieldMask | GradientLayer::EndPositionFieldMask);
	
	UIDrawObjectCanvasPtr GreenSliderTrackCanvas = UIDrawObjectCanvas::create();
	beginEditCP(GreenSliderTrackCanvas, UIDrawObjectCanvas::PreferredSizeFieldMask | UIDrawObjectCanvas::BordersFieldMask | UIDrawObjectCanvas::BackgroundsFieldMask);
		GreenSliderTrackCanvas->setPreferredSize(Vec2f(15,15));
		GreenSliderTrackCanvas->setBorders(NullFC);
		GreenSliderTrackCanvas->setBackgrounds(_GreenSliderTrackBackground);
	endEditCP(GreenSliderTrackCanvas, UIDrawObjectCanvas::PreferredSizeFieldMask | UIDrawObjectCanvas::BordersFieldMask | UIDrawObjectCanvas::BackgroundsFieldMask);

	_GreenSlider = Slider::create();
	beginEditCP(_GreenSlider, Slider::DrawLabelsFieldMask | Slider::DrawMajorTicksFieldId | Slider::DrawMinorTicksFieldMask | Slider::OrientationFieldMask | Slider::TrackDrawObjectFieldMask | Slider::RangeModelFieldMask);
		_GreenSlider->setDrawLabels(false);
		_GreenSlider->setDrawMajorTicks(false);
		_GreenSlider->setDrawMinorTicks(false);
		_GreenSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);;
		_GreenSlider->setTrackDrawObject(GreenSliderTrackCanvas);
    	_GreenSlider->setRangeModel(_GreenModel->getBoundedRangeModel());
	endEditCP(_GreenSlider, Slider::DrawLabelsFieldMask | Slider::DrawMajorTicksFieldId | Slider::DrawMinorTicksFieldMask | Slider::OrientationFieldMask | Slider::TrackDrawObjectFieldMask | Slider::RangeModelFieldMask);
	
	//Blue
	_BlueSliderTrackBackground = GradientLayer::create();
	beginEditCP(_BlueSliderTrackBackground, GradientLayer::StartPositionFieldMask | GradientLayer::EndPositionFieldMask);
		_BlueSliderTrackBackground->setStartPosition(Vec2f(0.0f,0.0f));
		_BlueSliderTrackBackground->setEndPosition(Vec2f(1.0f,0.0f));
	endEditCP(_BlueSliderTrackBackground, GradientLayer::StartPositionFieldMask | GradientLayer::EndPositionFieldMask);
	
	UIDrawObjectCanvasPtr BlueSliderTrackCanvas = UIDrawObjectCanvas::create();
	beginEditCP(BlueSliderTrackCanvas, UIDrawObjectCanvas::PreferredSizeFieldMask | UIDrawObjectCanvas::BordersFieldMask | UIDrawObjectCanvas::BackgroundsFieldMask);
		BlueSliderTrackCanvas->setPreferredSize(Vec2f(15,15));
		BlueSliderTrackCanvas->setBorders(NullFC);
		BlueSliderTrackCanvas->setBackgrounds(_BlueSliderTrackBackground);
	endEditCP(BlueSliderTrackCanvas, UIDrawObjectCanvas::PreferredSizeFieldMask | UIDrawObjectCanvas::BordersFieldMask | UIDrawObjectCanvas::BackgroundsFieldMask);

	_BlueSlider = Slider::create();
	beginEditCP(_BlueSlider, Slider::DrawLabelsFieldMask | Slider::DrawMajorTicksFieldId | Slider::DrawMinorTicksFieldMask | Slider::OrientationFieldMask | Slider::TrackDrawObjectFieldMask | Slider::RangeModelFieldMask);
		_BlueSlider->setDrawLabels(false);
		_BlueSlider->setDrawMajorTicks(false);
		_BlueSlider->setDrawMinorTicks(false);
		_BlueSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);;
		_BlueSlider->setTrackDrawObject(BlueSliderTrackCanvas);
    	_BlueSlider->setRangeModel(_BlueModel->getBoundedRangeModel());
	endEditCP(_BlueSlider, Slider::DrawLabelsFieldMask | Slider::DrawMajorTicksFieldId | Slider::DrawMinorTicksFieldMask | Slider::OrientationFieldMask | Slider::TrackDrawObjectFieldMask | Slider::RangeModelFieldMask);
	
	if(getIncludeAlpha())
	{
		_AlphaSliderTrackBackground = GradientLayer::create();
		beginEditCP(_AlphaSliderTrackBackground, GradientLayer::StartPositionFieldMask | GradientLayer::EndPositionFieldMask);
			_AlphaSliderTrackBackground->setStartPosition(Vec2f(0.0f,0.0f));
			_AlphaSliderTrackBackground->setEndPosition(Vec2f(1.0f,0.0f));
		endEditCP(_AlphaSliderTrackBackground, GradientLayer::StartPositionFieldMask | GradientLayer::EndPositionFieldMask);
		
		UIDrawObjectCanvasPtr AlphaSliderTrackCanvas = UIDrawObjectCanvas::create();
		beginEditCP(AlphaSliderTrackCanvas, UIDrawObjectCanvas::PreferredSizeFieldMask | UIDrawObjectCanvas::BordersFieldMask | UIDrawObjectCanvas::BackgroundsFieldMask);
			AlphaSliderTrackCanvas->setPreferredSize(Vec2f(15,15));
			AlphaSliderTrackCanvas->setBorders(NullFC);
			AlphaSliderTrackCanvas->setBackgrounds(_AlphaSliderTrackBackground);
		endEditCP(AlphaSliderTrackCanvas, UIDrawObjectCanvas::PreferredSizeFieldMask | UIDrawObjectCanvas::BordersFieldMask | UIDrawObjectCanvas::BackgroundsFieldMask);

		_AlphaSlider = Slider::create();
		beginEditCP(_AlphaSlider, Slider::DrawLabelsFieldMask | Slider::DrawMajorTicksFieldId | Slider::DrawMinorTicksFieldMask | Slider::OrientationFieldMask | Slider::TrackDrawObjectFieldMask | Slider::RangeModelFieldMask);
			_AlphaSlider->setDrawLabels(false);
			_AlphaSlider->setDrawMajorTicks(false);
			_AlphaSlider->setDrawMinorTicks(false);
			_AlphaSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);;
			_AlphaSlider->setTrackDrawObject(AlphaSliderTrackCanvas);
    		_AlphaSlider->setRangeModel(_AlphaModel->getBoundedRangeModel());
		endEditCP(_AlphaSlider, Slider::DrawLabelsFieldMask | Slider::DrawMajorTicksFieldId | Slider::DrawMinorTicksFieldMask | Slider::OrientationFieldMask | Slider::TrackDrawObjectFieldMask | Slider::RangeModelFieldMask);
	}

	//Labels
	LabelPtr RedLabel = Label::create();
	beginEditCP(RedLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);
		RedLabel->setText("Red");
		RedLabel->setPreferredSize(Vec2f(50.0f, RedLabel->getPreferredSize().y()));
		RedLabel->setBackgrounds(NullFC);
		RedLabel->setBorders(NullFC);
	endEditCP(RedLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);

	LabelPtr GreenLabel = Label::create();
	beginEditCP(GreenLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);
		GreenLabel->setText("Green");
		GreenLabel->setPreferredSize(Vec2f(50.0f, GreenLabel->getPreferredSize().y()));
		GreenLabel->setBackgrounds(NullFC);
		GreenLabel->setBorders(NullFC);
	endEditCP(GreenLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);
	
	LabelPtr BlueLabel = Label::create();
	beginEditCP(BlueLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);
		BlueLabel->setText("Blue");
		BlueLabel->setPreferredSize(Vec2f(50.0f, BlueLabel->getPreferredSize().y()));
		BlueLabel->setBackgrounds(NullFC);
		BlueLabel->setBorders(NullFC);
	endEditCP(BlueLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);
	
	LabelPtr AlphaLabel = Label::create();
	if(getIncludeAlpha())
	{
		beginEditCP(AlphaLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);
			AlphaLabel->setText("Alpha");
			AlphaLabel->setPreferredSize(Vec2f(50.0f, AlphaLabel->getPreferredSize().y()));
			AlphaLabel->setBackgrounds(NullFC);
			AlphaLabel->setBorders(NullFC);
		endEditCP(AlphaLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);
	}
	
	//Layout
	SpringLayoutPtr RGBPanelLayout = SpringLayout::create();
	   
	//Red
	//Label
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, RedLabel, 5, SpringLayoutConstraints::WEST_EDGE, RGBColorChooserPanelPtr(this));
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, RedLabel, 5, SpringLayoutConstraints::NORTH_EDGE, RGBColorChooserPanelPtr(this));
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, RedLabel, LayoutSpring::width(RedLabel));
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, RedLabel, LayoutSpring::height(RedLabel));

	//Slider
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _RedSlider, 5, SpringLayoutConstraints::EAST_EDGE, RedLabel);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _RedSlider, -5, SpringLayoutConstraints::WEST_EDGE, _RedSpinner);
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _RedSlider, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, RedLabel);
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _RedSlider, LayoutSpring::height(_RedSlider));
	
	//Spinner
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _RedSpinner, -5, SpringLayoutConstraints::EAST_EDGE, RGBColorChooserPanelPtr(this));
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _RedSpinner, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, RedLabel);
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _RedSpinner, LayoutSpring::width(_RedSpinner));
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _RedSpinner, LayoutSpring::height(_RedSpinner));
	 
	//Green
	//Label
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, GreenLabel, 5, SpringLayoutConstraints::WEST_EDGE, RGBColorChooserPanelPtr(this));
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, GreenLabel, 5, SpringLayoutConstraints::SOUTH_EDGE, RedLabel);
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, GreenLabel, LayoutSpring::width(GreenLabel));
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, GreenLabel, LayoutSpring::height(GreenLabel));

	//Slider
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _GreenSlider, 5, SpringLayoutConstraints::EAST_EDGE, GreenLabel);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _GreenSlider, -5, SpringLayoutConstraints::WEST_EDGE, _GreenSpinner);
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _GreenSlider, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, GreenLabel);
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _GreenSlider, LayoutSpring::height(_GreenSlider));
	
	//Spinner
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _GreenSpinner, -5, SpringLayoutConstraints::EAST_EDGE, RGBColorChooserPanelPtr(this));
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _GreenSpinner, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, GreenLabel);
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _GreenSpinner, LayoutSpring::width(_GreenSpinner));
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _GreenSpinner, LayoutSpring::height(_GreenSpinner));
	 
	//Blue
	//Label
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, BlueLabel, 5, SpringLayoutConstraints::WEST_EDGE, RGBColorChooserPanelPtr(this));
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, BlueLabel, 5, SpringLayoutConstraints::SOUTH_EDGE, GreenLabel);
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, BlueLabel, LayoutSpring::width(BlueLabel));
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, BlueLabel, LayoutSpring::height(BlueLabel));

	//Slider
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _BlueSlider, 5, SpringLayoutConstraints::EAST_EDGE, BlueLabel);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _BlueSlider, -5, SpringLayoutConstraints::WEST_EDGE, _BlueSpinner);
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _BlueSlider, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, BlueLabel);
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _BlueSlider, LayoutSpring::height(_BlueSlider));
	
	//Spinner
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _BlueSpinner, -5, SpringLayoutConstraints::EAST_EDGE, RGBColorChooserPanelPtr(this));
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _BlueSpinner, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, BlueLabel);
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _BlueSpinner, LayoutSpring::width(_BlueSpinner));
	RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _BlueSpinner, LayoutSpring::height(_BlueSpinner));
	 
	if(getIncludeAlpha())
	{
		//Alpha
		//Label
		RGBPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, AlphaLabel, 5, SpringLayoutConstraints::WEST_EDGE, RGBColorChooserPanelPtr(this));
		RGBPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, AlphaLabel, 5, SpringLayoutConstraints::SOUTH_EDGE, BlueLabel);
		RGBPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, AlphaLabel, LayoutSpring::width(AlphaLabel));
		RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, AlphaLabel, LayoutSpring::height(AlphaLabel));

		//Slider
		RGBPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _AlphaSlider, 5, SpringLayoutConstraints::EAST_EDGE, AlphaLabel);
		RGBPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _AlphaSlider, -5, SpringLayoutConstraints::WEST_EDGE, _AlphaSpinner);
		RGBPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _AlphaSlider, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, AlphaLabel);
		RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _AlphaSlider, LayoutSpring::height(_AlphaSlider));
		
		//Spinner
		RGBPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _AlphaSpinner, -5, SpringLayoutConstraints::EAST_EDGE, RGBColorChooserPanelPtr(this));
		RGBPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _AlphaSpinner, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, AlphaLabel);
		RGBPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _AlphaSpinner, LayoutSpring::width(_AlphaSpinner));
		RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _AlphaSpinner, LayoutSpring::height(_AlphaSpinner));
	}

	beginEditCP(RGBColorChooserPanelPtr(this) , RGBColorChooserPanel::ChildrenFieldMask | RGBColorChooserPanel::LayoutFieldMask);
		getChildren().clear();
		getChildren().push_back(RedLabel);
		getChildren().push_back(_RedSlider);
		getChildren().push_back(_RedSpinner);
		getChildren().push_back(GreenLabel);
		getChildren().push_back(_GreenSlider);
		getChildren().push_back(_GreenSpinner);
		getChildren().push_back(BlueLabel);
		getChildren().push_back(_BlueSlider);
		getChildren().push_back(_BlueSpinner);
		if(getIncludeAlpha())
		{
			getChildren().push_back(AlphaLabel);
		    getChildren().push_back(_AlphaSlider);
			getChildren().push_back(_AlphaSpinner);
		}
		setLayout(RGBPanelLayout);
	endEditCP(RGBColorChooserPanelPtr(this) , RGBColorChooserPanel::ChildrenFieldMask | RGBColorChooserPanel::LayoutFieldMask);
}

void RGBColorChooserPanel::updateColorSelectedModel(void)
{
	bool isValueAdjusting = _RedModel->getBoundedRangeModel()->getValueIsAdjusting() ||
		                    _GreenModel->getBoundedRangeModel()->getValueIsAdjusting() ||
		                    _BlueModel->getBoundedRangeModel()->getValueIsAdjusting() ||
		                    _AlphaModel->getBoundedRangeModel()->getValueIsAdjusting();
	getColorSelectionModel()->setSelectedColor(Color4f(static_cast<Real32>(_RedModel->getValue())/255.0f,
		                                               static_cast<Real32>(_GreenModel->getValue())/255.0f,
													   static_cast<Real32>(_BlueModel->getValue())/255.0f,
													   static_cast<Real32>(_AlphaModel->getValue())/255.0f),
													   isValueAdjusting);
}

void RGBColorChooserPanel::attachModelListener(void)
{
	_RedModel->addChangeListener(&_BoundedRangeSpinnerChangeListener);
	_GreenModel->addChangeListener(&_BoundedRangeSpinnerChangeListener);
	_BlueModel->addChangeListener(&_BoundedRangeSpinnerChangeListener);
	_AlphaModel->addChangeListener(&_BoundedRangeSpinnerChangeListener);
}

void RGBColorChooserPanel::dettachModelListener(void)
{
    if(_RedModel){ _RedModel->removeChangeListener(&_BoundedRangeSpinnerChangeListener);}
    if(_GreenModel){ _GreenModel->removeChangeListener(&_BoundedRangeSpinnerChangeListener);}
    if(_BlueModel){ _BlueModel->removeChangeListener(&_BoundedRangeSpinnerChangeListener);}
    if(_AlphaModel){ _AlphaModel->removeChangeListener(&_BoundedRangeSpinnerChangeListener);}
}

void RGBColorChooserPanel::init(void)
{
	_RedModel = new BoundedRangeSpinnerModel();
	_GreenModel = new BoundedRangeSpinnerModel();
	_BlueModel = new BoundedRangeSpinnerModel();
	_AlphaModel = new BoundedRangeSpinnerModel();

	attachModelListener();
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RGBColorChooserPanel::RGBColorChooserPanel(void) :
    Inherited(),
	_BoundedRangeSpinnerChangeListener(RGBColorChooserPanelPtr(this))
{
}

RGBColorChooserPanel::RGBColorChooserPanel(const RGBColorChooserPanel &source) :
    Inherited(source),
	_BoundedRangeSpinnerChangeListener(RGBColorChooserPanelPtr(this))
{
    init();
}

RGBColorChooserPanel::~RGBColorChooserPanel(void)
{
	dettachModelListener();
}

/*----------------------------- class specific ----------------------------*/

void RGBColorChooserPanel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void RGBColorChooserPanel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump RGBColorChooserPanel NI" << std::endl;
}

void RGBColorChooserPanel::BoundedRangeSpinnerChangeListener::stateChanged(const ChangeEventPtr e)
{
	//Update the Color Selected Model
	_RGBColorChooserPanel->updateColorSelectedModel();
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
    static Char8 cvsid_hpp       [] = OSGRGBCOLORCHOOSERPANELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGRGBCOLORCHOOSERPANELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGRGBCOLORCHOOSERPANELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

