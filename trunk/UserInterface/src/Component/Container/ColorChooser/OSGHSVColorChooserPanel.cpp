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

#include "OSGHSVColorChooserPanel.h"
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

/*! \class osg::HSVColorChooserPanel
A UI HSVColorChooserPanel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void HSVColorChooserPanel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


std::string HSVColorChooserPanel::getDisplayText(void) const
{
	if(getIncludeAlpha())
	{
		return std::string("HSVA");
	}
	else
	{
		return std::string("HSV");
	}
}

void HSVColorChooserPanel::updateChooser(void)
{
	dettachModelListener();

	Real32 Hue, Saturation, Value;
	getColorFromModel().getValuesHSV(Hue, Saturation, Value);
	Color4f TempColor(getColorFromModel());
	//Update the Hue Bounded Range
	_HueModel->setValue(osgClamp<Real32>(_HueModel->getMinimum(), Hue, _HueModel->getMaximum()));
	beginEditCP(_HueSliderTrackBackground, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask);
		_HueSliderTrackBackground->getColors().clear();
		_HueSliderTrackBackground->getStops().clear();
		//Red
		TempColor.setValuesHSV(0.0f, Saturation, Value);
		_HueSliderTrackBackground->getColors().push_back(TempColor);
		_HueSliderTrackBackground->getStops().push_back(0.0);
		//Yellow
		TempColor.setValuesHSV(60.0f, Saturation, Value);
		_HueSliderTrackBackground->getColors().push_back(TempColor);
		_HueSliderTrackBackground->getStops().push_back(0.166667);
		//Green
		TempColor.setValuesHSV(120.0f, Saturation, Value);
		_HueSliderTrackBackground->getColors().push_back(TempColor);
		_HueSliderTrackBackground->getStops().push_back(0.333333);
		//Teal
		TempColor.setValuesHSV(180.0f, Saturation, Value);
		_HueSliderTrackBackground->getColors().push_back(TempColor);
		_HueSliderTrackBackground->getStops().push_back(0.5);
		//Blue
		TempColor.setValuesHSV(240.0f, Saturation, Value);
		_HueSliderTrackBackground->getColors().push_back(TempColor);
		_HueSliderTrackBackground->getStops().push_back(0.666667);
		//Purple
		TempColor.setValuesHSV(300.0f, Saturation, Value);
		_HueSliderTrackBackground->getColors().push_back(TempColor);
		_HueSliderTrackBackground->getStops().push_back(0.833333);
		//Red
		TempColor.setValuesHSV(360.0f, Saturation, Value);
		_HueSliderTrackBackground->getColors().push_back(TempColor);
		_HueSliderTrackBackground->getStops().push_back(1.0);
	endEditCP(_HueSliderTrackBackground, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask);

	//Update the Saturation Bounded Range
    _SaturationModel->setValue(osgClamp(0.0f, Saturation, 1.0f) * _SaturationModel->getMaximum());
	beginEditCP(_SaturationSliderTrackBackground, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask);
		_SaturationSliderTrackBackground->getColors().clear();
		_SaturationSliderTrackBackground->getStops().clear();
		TempColor.setValuesHSV(Hue, 0.0f, Value);
		_SaturationSliderTrackBackground->getColors().push_back(TempColor);
		_SaturationSliderTrackBackground->getStops().push_back(0.0);
		TempColor.setValuesHSV(Hue, 1.0f, Value);
		_SaturationSliderTrackBackground->getColors().push_back(TempColor);
		_SaturationSliderTrackBackground->getStops().push_back(1.0);
	endEditCP(_SaturationSliderTrackBackground, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask);

	//Update the Value Bounded Range
    _ValueModel->setValue(osgClamp(0.0f, Value, 1.0f) * _ValueModel->getMaximum());
	beginEditCP(_ValueSliderTrackBackground, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask);
		_ValueSliderTrackBackground->getColors().clear();
		_ValueSliderTrackBackground->getStops().clear();
		TempColor.setValuesHSV(Hue, Saturation, 0.0f);
		_ValueSliderTrackBackground->getColors().push_back(TempColor);
		_ValueSliderTrackBackground->getStops().push_back(0.0);
		TempColor.setValuesHSV(Hue, Saturation, 1.0f);
		_ValueSliderTrackBackground->getColors().push_back(TempColor);
		_ValueSliderTrackBackground->getStops().push_back(1.0);
	endEditCP(_ValueSliderTrackBackground, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask);

	//Update the Alpha Bounded Range
	_AlphaModel->setValue(osgClamp(0.0f, getColorFromModel().alpha(), 1.0f) * _AlphaModel->getMaximum());
	
	if(getIncludeAlpha())
	{
		beginEditCP(_AlphaSliderTrackBackground, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask);
			_AlphaSliderTrackBackground->getColors().clear();
			_AlphaSliderTrackBackground->getStops().clear();
			_AlphaSliderTrackBackground->getColors().push_back(Color4f(getColorFromModel().red(),
				                                             getColorFromModel().green(),
															 getColorFromModel().blue(),
															 0.0f));
			_AlphaSliderTrackBackground->getStops().push_back(0.0);
			_AlphaSliderTrackBackground->getColors().push_back(Color4f(getColorFromModel().red(),
				                                             getColorFromModel().green(),
															 getColorFromModel().blue(),
															 1.0f));
			_AlphaSliderTrackBackground->getStops().push_back(1.0);
		endEditCP(_AlphaSliderTrackBackground, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask);
	}
	
	attachModelListener();
}

void HSVColorChooserPanel::buildChooser(void)
{
	//Bounded Range Models
    _HueModel->setMinimum(0);
    _HueModel->setMaximum(360);
	
    _SaturationModel->setMinimum(0);
    _SaturationModel->setMaximum(100);
	
    _ValueModel->setMinimum(0);
    _ValueModel->setMaximum(100);
	
    _AlphaModel->setMinimum(0);
    _AlphaModel->setMaximum(255);


	//Spinners
	_HueSpinner = Spinner::create();
	_HueSpinner->setModel(_HueModel->getSpinnerModel());
	
	_SaturationSpinner = Spinner::create();
    _SaturationSpinner->setModel(_SaturationModel->getSpinnerModel());
	
	_ValueSpinner = Spinner::create();
    _ValueSpinner->setModel(_ValueModel->getSpinnerModel());
	
	if(getIncludeAlpha())
	{
		_AlphaSpinner = Spinner::create();
		_AlphaSpinner->setModel(_AlphaModel->getSpinnerModel());
	}

	//Sliders
	_HueSliderTrackBackground = GradientLayer::create();
	beginEditCP(_HueSliderTrackBackground, GradientLayer::StartPositionFieldMask | GradientLayer::EndPositionFieldMask);
    _HueSliderTrackBackground->setStartPosition(Vec2f(0.0f,0.0f));
    _HueSliderTrackBackground->setEndPosition(Vec2f(1.0f,0.0f));
	endEditCP(_HueSliderTrackBackground, GradientLayer::StartPositionFieldMask | GradientLayer::EndPositionFieldMask);
	
	UIDrawObjectCanvasPtr HueSliderTrackCanvas = UIDrawObjectCanvas::create();
	beginEditCP(HueSliderTrackCanvas, UIDrawObjectCanvas::PreferredSizeFieldMask | UIDrawObjectCanvas::BordersFieldMask | UIDrawObjectCanvas::BackgroundsFieldMask);
		HueSliderTrackCanvas->setPreferredSize(Vec2f(15,15));
		HueSliderTrackCanvas->setBorders(NullFC);
		HueSliderTrackCanvas->setBackgrounds(_HueSliderTrackBackground);
	endEditCP(HueSliderTrackCanvas, UIDrawObjectCanvas::PreferredSizeFieldMask | UIDrawObjectCanvas::BordersFieldMask | UIDrawObjectCanvas::BackgroundsFieldMask);

	_HueSlider = Slider::create();
	beginEditCP(_HueSlider, Slider::DrawLabelsFieldMask | Slider::DrawMajorTicksFieldId | Slider::DrawMinorTicksFieldMask | Slider::OrientationFieldMask | Slider::TrackDrawObjectFieldMask | Slider::RangeModelFieldMask);
		_HueSlider->setDrawLabels(false);
		_HueSlider->setDrawMajorTicks(false);
		_HueSlider->setDrawMinorTicks(false);
        _HueSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);
		_HueSlider->setTrackDrawObject(HueSliderTrackCanvas);
    	_HueSlider->setRangeModel(_HueModel->getBoundedRangeModel());
	endEditCP(_HueSlider, Slider::DrawLabelsFieldMask | Slider::DrawMajorTicksFieldId | Slider::DrawMinorTicksFieldMask | Slider::OrientationFieldMask | Slider::TrackDrawObjectFieldMask | Slider::RangeModelFieldMask);
	
	//Saturation
	_SaturationSliderTrackBackground = GradientLayer::create();
	beginEditCP(_SaturationSliderTrackBackground, GradientLayer::StartPositionFieldMask | GradientLayer::EndPositionFieldMask);
		_SaturationSliderTrackBackground->setStartPosition(Vec2f(0.0f,0.0f));
		_SaturationSliderTrackBackground->setEndPosition(Vec2f(1.0f,0.0f));
	endEditCP(_SaturationSliderTrackBackground, GradientLayer::StartPositionFieldMask | GradientLayer::EndPositionFieldMask);
	
	UIDrawObjectCanvasPtr SaturationSliderTrackCanvas = UIDrawObjectCanvas::create();
	beginEditCP(SaturationSliderTrackCanvas, UIDrawObjectCanvas::PreferredSizeFieldMask | UIDrawObjectCanvas::BordersFieldMask | UIDrawObjectCanvas::BackgroundsFieldMask);
		SaturationSliderTrackCanvas->setPreferredSize(Vec2f(15,15));
		SaturationSliderTrackCanvas->setBorders(NullFC);
		SaturationSliderTrackCanvas->setBackgrounds(_SaturationSliderTrackBackground);
	endEditCP(SaturationSliderTrackCanvas, UIDrawObjectCanvas::PreferredSizeFieldMask | UIDrawObjectCanvas::BordersFieldMask | UIDrawObjectCanvas::BackgroundsFieldMask);

	_SaturationSlider = Slider::create();
	beginEditCP(_SaturationSlider, Slider::DrawLabelsFieldMask | Slider::DrawMajorTicksFieldId | Slider::DrawMinorTicksFieldMask | Slider::OrientationFieldMask | Slider::TrackDrawObjectFieldMask | Slider::RangeModelFieldMask);
		_SaturationSlider->setDrawLabels(false);
		_SaturationSlider->setDrawMajorTicks(false);
		_SaturationSlider->setDrawMinorTicks(false);
		_SaturationSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);
		_SaturationSlider->setTrackDrawObject(SaturationSliderTrackCanvas);
    	_SaturationSlider->setRangeModel(_SaturationModel->getBoundedRangeModel());
	endEditCP(_SaturationSlider, Slider::DrawLabelsFieldMask | Slider::DrawMajorTicksFieldId | Slider::DrawMinorTicksFieldMask | Slider::OrientationFieldMask | Slider::TrackDrawObjectFieldMask | Slider::RangeModelFieldMask);
	
	//Value
	_ValueSliderTrackBackground = GradientLayer::create();
	beginEditCP(_ValueSliderTrackBackground, GradientLayer::StartPositionFieldMask | GradientLayer::EndPositionFieldMask);
		_ValueSliderTrackBackground->setStartPosition(Vec2f(0.0f,0.0f));
		_ValueSliderTrackBackground->setEndPosition(Vec2f(1.0f,0.0f));
	endEditCP(_ValueSliderTrackBackground, GradientLayer::StartPositionFieldMask | GradientLayer::EndPositionFieldMask);
	
	UIDrawObjectCanvasPtr ValueSliderTrackCanvas = UIDrawObjectCanvas::create();
	beginEditCP(ValueSliderTrackCanvas, UIDrawObjectCanvas::PreferredSizeFieldMask | UIDrawObjectCanvas::BordersFieldMask | UIDrawObjectCanvas::BackgroundsFieldMask);
		ValueSliderTrackCanvas->setPreferredSize(Vec2f(15,15));
		ValueSliderTrackCanvas->setBorders(NullFC);
		ValueSliderTrackCanvas->setBackgrounds(_ValueSliderTrackBackground);
	endEditCP(ValueSliderTrackCanvas, UIDrawObjectCanvas::PreferredSizeFieldMask | UIDrawObjectCanvas::BordersFieldMask | UIDrawObjectCanvas::BackgroundsFieldMask);

	_ValueSlider = Slider::create();
	beginEditCP(_ValueSlider, Slider::DrawLabelsFieldMask | Slider::DrawMajorTicksFieldId | Slider::DrawMinorTicksFieldMask | Slider::OrientationFieldMask | Slider::TrackDrawObjectFieldMask | Slider::RangeModelFieldMask);
		_ValueSlider->setDrawLabels(false);
		_ValueSlider->setDrawMajorTicks(false);
		_ValueSlider->setDrawMinorTicks(false);
		_ValueSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);
		_ValueSlider->setTrackDrawObject(ValueSliderTrackCanvas);
    	_ValueSlider->setRangeModel(_ValueModel->getBoundedRangeModel());
	endEditCP(_ValueSlider, Slider::DrawLabelsFieldMask | Slider::DrawMajorTicksFieldId | Slider::DrawMinorTicksFieldMask | Slider::OrientationFieldMask | Slider::TrackDrawObjectFieldMask | Slider::RangeModelFieldMask);
	
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
			_AlphaSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);
			_AlphaSlider->setTrackDrawObject(AlphaSliderTrackCanvas);
		    _AlphaSlider->setRangeModel(_AlphaModel->getBoundedRangeModel());
		endEditCP(_AlphaSlider, Slider::DrawLabelsFieldMask | Slider::DrawMajorTicksFieldId | Slider::DrawMinorTicksFieldMask | Slider::OrientationFieldMask | Slider::TrackDrawObjectFieldMask | Slider::RangeModelFieldMask);
	}

	//Labels
	LabelPtr HueLabel = Label::create();
	beginEditCP(HueLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);
		HueLabel->setText("Hue");
		HueLabel->setPreferredSize(Vec2f(50.0f, HueLabel->getPreferredSize().y()));
		HueLabel->setBackgrounds(NullFC);
		HueLabel->setBorders(NullFC);
	endEditCP(HueLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);

	LabelPtr SaturationLabel = Label::create();
	beginEditCP(SaturationLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);
		SaturationLabel->setText("Saturation");
		SaturationLabel->setPreferredSize(Vec2f(50.0f, SaturationLabel->getPreferredSize().y()));
		SaturationLabel->setBackgrounds(NullFC);
		SaturationLabel->setBorders(NullFC);
	endEditCP(SaturationLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);
	
	LabelPtr ValueLabel = Label::create();
	beginEditCP(ValueLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);
		ValueLabel->setText("Value");
		ValueLabel->setPreferredSize(Vec2f(50.0f, ValueLabel->getPreferredSize().y()));
		ValueLabel->setBackgrounds(NullFC);
		ValueLabel->setBorders(NullFC);
	endEditCP(ValueLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);
	
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
	SpringLayoutPtr HSVPanelLayout = SpringLayout::create();
	   
	//Hue
	//Label
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, HueLabel, 5, SpringLayoutConstraints::WEST_EDGE, HSVColorChooserPanelPtr(this));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, HueLabel, 5, SpringLayoutConstraints::NORTH_EDGE, HSVColorChooserPanelPtr(this));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, HueLabel, LayoutSpring::width(HueLabel));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, HueLabel, LayoutSpring::height(HueLabel));

	//Slider
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _HueSlider, 5, SpringLayoutConstraints::EAST_EDGE, HueLabel);
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _HueSlider, -5, SpringLayoutConstraints::WEST_EDGE, _HueSpinner);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _HueSlider, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, HueLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _HueSlider, LayoutSpring::height(_HueSlider));
	
	//Spinner
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _HueSpinner, -5, SpringLayoutConstraints::EAST_EDGE, HSVColorChooserPanelPtr(this));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _HueSpinner, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, HueLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _HueSpinner, LayoutSpring::width(_HueSpinner));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _HueSpinner, LayoutSpring::height(_HueSpinner));
	 
	//Saturation
	//Label
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, SaturationLabel, 5, SpringLayoutConstraints::WEST_EDGE, HSVColorChooserPanelPtr(this));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, SaturationLabel, 5, SpringLayoutConstraints::SOUTH_EDGE, HueLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, SaturationLabel, LayoutSpring::width(SaturationLabel));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, SaturationLabel, LayoutSpring::height(SaturationLabel));

	//Slider
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _SaturationSlider, 5, SpringLayoutConstraints::EAST_EDGE, SaturationLabel);
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _SaturationSlider, -5, SpringLayoutConstraints::WEST_EDGE, _SaturationSpinner);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _SaturationSlider, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, SaturationLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _SaturationSlider, LayoutSpring::height(_SaturationSlider));
	
	//Spinner
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _SaturationSpinner, -5, SpringLayoutConstraints::EAST_EDGE, HSVColorChooserPanelPtr(this));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _SaturationSpinner, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, SaturationLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _SaturationSpinner, LayoutSpring::width(_SaturationSpinner));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _SaturationSpinner, LayoutSpring::height(_SaturationSpinner));
	 
	//Value
	//Label
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, ValueLabel, 5, SpringLayoutConstraints::WEST_EDGE, HSVColorChooserPanelPtr(this));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, ValueLabel, 5, SpringLayoutConstraints::SOUTH_EDGE, SaturationLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, ValueLabel, LayoutSpring::width(ValueLabel));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, ValueLabel, LayoutSpring::height(ValueLabel));

	//Slider
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _ValueSlider, 5, SpringLayoutConstraints::EAST_EDGE, ValueLabel);
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _ValueSlider, -5, SpringLayoutConstraints::WEST_EDGE, _ValueSpinner);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _ValueSlider, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, ValueLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _ValueSlider, LayoutSpring::height(_ValueSlider));
	
	//Spinner
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _ValueSpinner, -5, SpringLayoutConstraints::EAST_EDGE, HSVColorChooserPanelPtr(this));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _ValueSpinner, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, ValueLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _ValueSpinner, LayoutSpring::width(_ValueSpinner));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _ValueSpinner, LayoutSpring::height(_ValueSpinner));
	 
	if(getIncludeAlpha())
	{
		//Alpha
		//Label
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, AlphaLabel, 5, SpringLayoutConstraints::WEST_EDGE, HSVColorChooserPanelPtr(this));
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, AlphaLabel, 5, SpringLayoutConstraints::SOUTH_EDGE, ValueLabel);
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, AlphaLabel, LayoutSpring::width(AlphaLabel));
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, AlphaLabel, LayoutSpring::height(AlphaLabel));

		//Slider
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _AlphaSlider, 5, SpringLayoutConstraints::EAST_EDGE, AlphaLabel);
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _AlphaSlider, -5, SpringLayoutConstraints::WEST_EDGE, _AlphaSpinner);
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _AlphaSlider, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, AlphaLabel);
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _AlphaSlider, LayoutSpring::height(_AlphaSlider));
		
		//Spinner
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _AlphaSpinner, -5, SpringLayoutConstraints::EAST_EDGE, HSVColorChooserPanelPtr(this));
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _AlphaSpinner, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, AlphaLabel);
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _AlphaSpinner, LayoutSpring::width(_AlphaSpinner));
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _AlphaSpinner, LayoutSpring::height(_AlphaSpinner));
	}

	beginEditCP(HSVColorChooserPanelPtr(this) , HSVColorChooserPanel::ChildrenFieldMask | HSVColorChooserPanel::LayoutFieldMask);
		getChildren().clear();
		getChildren().push_back(HueLabel);
		getChildren().push_back(_HueSlider);
		getChildren().push_back(_HueSpinner);
		getChildren().push_back(SaturationLabel);
		getChildren().push_back(_SaturationSlider);
		getChildren().push_back(_SaturationSpinner);
		getChildren().push_back(ValueLabel);
		getChildren().push_back(_ValueSlider);
		getChildren().push_back(_ValueSpinner);
		if(getIncludeAlpha())
		{
			getChildren().push_back(AlphaLabel);
		    getChildren().push_back(_AlphaSlider);
			getChildren().push_back(_AlphaSpinner);
		}
		setLayout(HSVPanelLayout);
	endEditCP(HSVColorChooserPanelPtr(this) , HSVColorChooserPanel::ChildrenFieldMask | HSVColorChooserPanel::LayoutFieldMask);
}

void HSVColorChooserPanel::updateColorSelectedModel(void)
{
	Color4f TempColor(1.0,1.0,1.0,static_cast<Real32>(_AlphaModel->getValue())/static_cast<Real32>(_AlphaModel->getMaximum()));
	TempColor.setValuesHSV(static_cast<Real32>(_HueModel->getValue()),
		static_cast<Real32>(_SaturationModel->getValue())/static_cast<Real32>(_SaturationModel->getMaximum()),
		static_cast<Real32>(_ValueModel->getValue())/static_cast<Real32>(_ValueModel->getMaximum()));

	bool isValueAdjusting = _HueModel->getBoundedRangeModel()->getValueIsAdjusting() ||
		                    _SaturationModel->getBoundedRangeModel()->getValueIsAdjusting() ||
		                    _ValueModel->getBoundedRangeModel()->getValueIsAdjusting() ||
		                    _AlphaModel->getBoundedRangeModel()->getValueIsAdjusting();
	getColorSelectionModel()->setSelectedColor(TempColor, isValueAdjusting);
}

void HSVColorChooserPanel::attachModelListener(void)
{
	_HueModel->addChangeListener(&_BoundedRangeSpinnerChangeListener);
	_SaturationModel->addChangeListener(&_BoundedRangeSpinnerChangeListener);
	_ValueModel->addChangeListener(&_BoundedRangeSpinnerChangeListener);
	_AlphaModel->addChangeListener(&_BoundedRangeSpinnerChangeListener);
}

void HSVColorChooserPanel::dettachModelListener(void)
{
    if(_HueModel){ _HueModel->removeChangeListener(&_BoundedRangeSpinnerChangeListener);}
    if(_SaturationModel){ _SaturationModel->removeChangeListener(&_BoundedRangeSpinnerChangeListener);}
    if(_ValueModel){ _ValueModel->removeChangeListener(&_BoundedRangeSpinnerChangeListener);}
    if(_AlphaModel){ _AlphaModel->removeChangeListener(&_BoundedRangeSpinnerChangeListener);}
}

void HSVColorChooserPanel::init(void)
{
	_HueModel = new BoundedRangeSpinnerModel();
	_SaturationModel = new BoundedRangeSpinnerModel();
	_ValueModel = new BoundedRangeSpinnerModel();
	_AlphaModel = new BoundedRangeSpinnerModel();

	attachModelListener();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

HSVColorChooserPanel::HSVColorChooserPanel(void) :
    Inherited(),
	_BoundedRangeSpinnerChangeListener(HSVColorChooserPanelPtr(this))
{
}

HSVColorChooserPanel::HSVColorChooserPanel(const HSVColorChooserPanel &source) :
    Inherited(source),
	_BoundedRangeSpinnerChangeListener(HSVColorChooserPanelPtr(this))
{
    init();
}

HSVColorChooserPanel::~HSVColorChooserPanel(void)
{
	dettachModelListener();
}

/*----------------------------- class specific ----------------------------*/

void HSVColorChooserPanel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void HSVColorChooserPanel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump HSVColorChooserPanel NI" << std::endl;
}

void HSVColorChooserPanel::BoundedRangeSpinnerChangeListener::stateChanged(const ChangeEvent& e)
{
	//Update the Color Selected Model
	_HSVColorChooserPanel->updateColorSelectedModel();
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
    static Char8 cvsid_hpp       [] = OSGHSVCOLORCHOOSERPANELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGHSVCOLORCHOOSERPANELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGHSVCOLORCHOOSERPANELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE
