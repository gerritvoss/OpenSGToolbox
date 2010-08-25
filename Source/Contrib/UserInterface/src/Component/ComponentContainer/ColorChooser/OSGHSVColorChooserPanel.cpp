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

#include "OSGHSVColorChooserPanel.h"
#include "OSGSpinner.h"
#include "OSGSlider.h"
#include "OSGLabel.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"
#include "OSGLayoutSpring.h"
#include "OSGGradientLayer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGHSVColorChooserPanelBase.cpp file.
// To modify it, please change the .fcd file (OSGHSVColorChooserPanel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void HSVColorChooserPanel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
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

    Real32 Hue, Saturation, Value;
    Color4f ColorSelected(getColorFromModel());
    ColorSelected.getValuesHSV(Hue, Saturation, Value);
    Color4f TempColor(getColorFromModel());
    //Update the Hue Bounded Range
    Hue = osgClamp<Real32>(_HueModel->getMinimum(), Hue, _HueModel->getMaximum());
    if(static_cast<Int32>(Hue) != _HueModel->getValue())
    {
        _HueModel->setValue(Hue);
    }
    _HueSliderTrackBackground->editMFColors()->clear();
    _HueSliderTrackBackground->editMFStops()->clear();
    //Red
    TempColor.setValuesHSV(0.0f, Saturation, Value);
	TempColor[3] = ColorSelected.alpha();
    _HueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _HueSliderTrackBackground->editMFStops()->push_back(0.0);
    //Yellow
    TempColor.setValuesHSV(60.0f, Saturation, Value);
	TempColor[3] = ColorSelected.alpha();
    _HueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _HueSliderTrackBackground->editMFStops()->push_back(0.166667);
    //Green
    TempColor.setValuesHSV(120.0f, Saturation, Value);
	TempColor[3] = ColorSelected.alpha();
    _HueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _HueSliderTrackBackground->editMFStops()->push_back(0.333333);
    //Teal
    TempColor.setValuesHSV(180.0f, Saturation, Value);
	TempColor[3] = ColorSelected.alpha();
    _HueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _HueSliderTrackBackground->editMFStops()->push_back(0.5);
    //Blue
    TempColor.setValuesHSV(240.0f, Saturation, Value);
	TempColor[3] = ColorSelected.alpha();
    _HueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _HueSliderTrackBackground->editMFStops()->push_back(0.666667);
    //Purple
    TempColor.setValuesHSV(300.0f, Saturation, Value);
	TempColor[3] = ColorSelected.alpha();
    _HueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _HueSliderTrackBackground->editMFStops()->push_back(0.833333);
    //Red
    TempColor.setValuesHSV(360.0f, Saturation, Value);
	TempColor[3] = ColorSelected.alpha();
    _HueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _HueSliderTrackBackground->editMFStops()->push_back(1.0);

    //Update the Saturation Bounded Range
	Saturation = osgClamp(0.0f, Saturation, 1.0f) * _SaturationModel->getMaximum();
    if(static_cast<Int32>(Saturation) != _SaturationModel->getValue())
    {
		_SaturationModel->setValue(Saturation);
	}
    _SaturationSliderTrackBackground->editMFColors()->clear();
    _SaturationSliderTrackBackground->editMFStops()->clear();
    TempColor.setValuesHSV(Hue, 0.0f, Value);
	TempColor[3] = ColorSelected.alpha();
    _SaturationSliderTrackBackground->editMFColors()->push_back(TempColor);
    _SaturationSliderTrackBackground->editMFStops()->push_back(0.0);
    TempColor.setValuesHSV(Hue, 1.0f, Value);
	TempColor[3] = ColorSelected.alpha();
    _SaturationSliderTrackBackground->editMFColors()->push_back(TempColor);
    _SaturationSliderTrackBackground->editMFStops()->push_back(1.0);

    //Update the Value Bounded Range
	Value = osgClamp(0.0f, Value, 1.0f) * _ValueModel->getMaximum();
    if(static_cast<Int32>(Value) != _ValueModel->getValue())
    {
		_ValueModel->setValue(Value);
	}
    _ValueSliderTrackBackground->editMFColors()->clear();
    _ValueSliderTrackBackground->editMFStops()->clear();
    TempColor.setValuesHSV(Hue, Saturation, 0.0f);
	TempColor[3] = ColorSelected.alpha();
    _ValueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _ValueSliderTrackBackground->editMFStops()->push_back(0.0);
    TempColor.setValuesHSV(Hue, Saturation, 1.0f);
	TempColor[3] = ColorSelected.alpha();
    _ValueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _ValueSliderTrackBackground->editMFStops()->push_back(1.0);

    //Update the Alpha Bounded Range
    Int32 Alpha = osgClamp(0.0f, ColorSelected.alpha(), 1.0f) * 255;
    if(static_cast<Int32>(Alpha) != _AlphaModel->getValue())
    {
        _AlphaModel->setValue(Alpha);
    }

    if(getIncludeAlpha())
    {
        _AlphaSliderTrackBackground->editMFColors()->clear();
        _AlphaSliderTrackBackground->editMFStops()->clear();
        _AlphaSliderTrackBackground->editMFColors()->push_back(Color4f(getColorFromModel().red(),
                                                                       getColorFromModel().green(),
                                                                       getColorFromModel().blue(),
                                                                       0.0f));
        _AlphaSliderTrackBackground->editMFStops()->push_back(0.0);
        _AlphaSliderTrackBackground->editMFColors()->push_back(Color4f(getColorFromModel().red(),
                                                                       getColorFromModel().green(),
                                                                       getColorFromModel().blue(),
                                                                       1.0f));
        _AlphaSliderTrackBackground->editMFStops()->push_back(1.0);
    }
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
    _HueSliderTrackBackground->setStartPosition(Vec2f(0.0f,0.0f));
    _HueSliderTrackBackground->setEndPosition(Vec2f(1.0f,0.0f));
	
	UIDrawObjectCanvasRefPtr HueSliderTrackCanvas = UIDrawObjectCanvas::create();
		HueSliderTrackCanvas->setPreferredSize(Vec2f(15,15));
		HueSliderTrackCanvas->setBorders(NULL);
		HueSliderTrackCanvas->setBackgrounds(_HueSliderTrackBackground);

	_HueSlider = Slider::create();
		_HueSlider->setDrawLabels(false);
		_HueSlider->setDrawMajorTicks(false);
		_HueSlider->setDrawMinorTicks(false);
        _HueSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);
		_HueSlider->setTrackDrawObject(HueSliderTrackCanvas);
    	_HueSlider->setRangeModel(_HueModel->getBoundedRangeModel());
	
	//Saturation
	_SaturationSliderTrackBackground = GradientLayer::create();
		_SaturationSliderTrackBackground->setStartPosition(Vec2f(0.0f,0.0f));
		_SaturationSliderTrackBackground->setEndPosition(Vec2f(1.0f,0.0f));
	
	UIDrawObjectCanvasRefPtr SaturationSliderTrackCanvas = UIDrawObjectCanvas::create();
		SaturationSliderTrackCanvas->setPreferredSize(Vec2f(15,15));
		SaturationSliderTrackCanvas->setBorders(NULL);
		SaturationSliderTrackCanvas->setBackgrounds(_SaturationSliderTrackBackground);

	_SaturationSlider = Slider::create();
		_SaturationSlider->setDrawLabels(false);
		_SaturationSlider->setDrawMajorTicks(false);
		_SaturationSlider->setDrawMinorTicks(false);
		_SaturationSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);
		_SaturationSlider->setTrackDrawObject(SaturationSliderTrackCanvas);
    	_SaturationSlider->setRangeModel(_SaturationModel->getBoundedRangeModel());
	
	//Value
	_ValueSliderTrackBackground = GradientLayer::create();
		_ValueSliderTrackBackground->setStartPosition(Vec2f(0.0f,0.0f));
		_ValueSliderTrackBackground->setEndPosition(Vec2f(1.0f,0.0f));
	
	UIDrawObjectCanvasRefPtr ValueSliderTrackCanvas = UIDrawObjectCanvas::create();
		ValueSliderTrackCanvas->setPreferredSize(Vec2f(15,15));
		ValueSliderTrackCanvas->setBorders(NULL);
		ValueSliderTrackCanvas->setBackgrounds(_ValueSliderTrackBackground);

	_ValueSlider = Slider::create();
		_ValueSlider->setDrawLabels(false);
		_ValueSlider->setDrawMajorTicks(false);
		_ValueSlider->setDrawMinorTicks(false);
		_ValueSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);
		_ValueSlider->setTrackDrawObject(ValueSliderTrackCanvas);
    	_ValueSlider->setRangeModel(_ValueModel->getBoundedRangeModel());
	
	if(getIncludeAlpha())
	{
		_AlphaSliderTrackBackground = GradientLayer::create();
			_AlphaSliderTrackBackground->setStartPosition(Vec2f(0.0f,0.0f));
			_AlphaSliderTrackBackground->setEndPosition(Vec2f(1.0f,0.0f));
		
		UIDrawObjectCanvasRefPtr AlphaSliderTrackCanvas = UIDrawObjectCanvas::create();
			AlphaSliderTrackCanvas->setPreferredSize(Vec2f(15,15));
			AlphaSliderTrackCanvas->setBorders(NULL);
			AlphaSliderTrackCanvas->setBackgrounds(_AlphaSliderTrackBackground);

		_AlphaSlider = Slider::create();
			_AlphaSlider->setDrawLabels(false);
			_AlphaSlider->setDrawMajorTicks(false);
			_AlphaSlider->setDrawMinorTicks(false);
			_AlphaSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);
			_AlphaSlider->setTrackDrawObject(AlphaSliderTrackCanvas);
		    _AlphaSlider->setRangeModel(_AlphaModel->getBoundedRangeModel());
	}

	//Labels
	LabelRefPtr HueLabel = Label::create();
		HueLabel->setText("Hue");
		HueLabel->setPreferredSize(Vec2f(50.0f, HueLabel->getPreferredSize().y()));
		HueLabel->setBackgrounds(NULL);
		HueLabel->setBorders(NULL);

	LabelRefPtr SaturationLabel = Label::create();
		SaturationLabel->setText("Saturation");
		SaturationLabel->setPreferredSize(Vec2f(50.0f, SaturationLabel->getPreferredSize().y()));
		SaturationLabel->setBackgrounds(NULL);
		SaturationLabel->setBorders(NULL);
	
	LabelRefPtr ValueLabel = Label::create();
		ValueLabel->setText("Value");
		ValueLabel->setPreferredSize(Vec2f(50.0f, ValueLabel->getPreferredSize().y()));
		ValueLabel->setBackgrounds(NULL);
		ValueLabel->setBorders(NULL);
	
	LabelRefPtr AlphaLabel = Label::create();
	if(getIncludeAlpha())
	{
			AlphaLabel->setText("Alpha");
			AlphaLabel->setPreferredSize(Vec2f(50.0f, AlphaLabel->getPreferredSize().y()));
			AlphaLabel->setBackgrounds(NULL);
			AlphaLabel->setBorders(NULL);
	}
	
	//Layout
	SpringLayoutRefPtr HSVPanelLayout = SpringLayout::create();
	   
	//Hue
	//Label
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, HueLabel, 5.0f, SpringLayoutConstraints::WEST_EDGE, this);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, HueLabel, 5.0f, SpringLayoutConstraints::NORTH_EDGE, this);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, HueLabel, LayoutSpringUnrecPtr(LayoutSpring::width(HueLabel)));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, HueLabel, LayoutSpringUnrecPtr(LayoutSpring::height(HueLabel)));

	//Slider
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _HueSlider, 5.0f, SpringLayoutConstraints::EAST_EDGE, HueLabel);
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _HueSlider, -5.0f, SpringLayoutConstraints::WEST_EDGE, _HueSpinner);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _HueSlider, 0.0f, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, HueLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _HueSlider, LayoutSpringUnrecPtr(LayoutSpring::height(_HueSlider)));
	
	//Spinner
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _HueSpinner, -5.0f, SpringLayoutConstraints::EAST_EDGE, this);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _HueSpinner, 0.0f, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, HueLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _HueSpinner, LayoutSpringUnrecPtr(LayoutSpring::width(_HueSpinner)));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _HueSpinner, LayoutSpringUnrecPtr(LayoutSpring::height(_HueSpinner)));
	 
	//Saturation
	//Label
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, SaturationLabel, 5.0f, SpringLayoutConstraints::WEST_EDGE, this);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, SaturationLabel, 5.0f, SpringLayoutConstraints::SOUTH_EDGE, HueLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, SaturationLabel, LayoutSpringUnrecPtr(LayoutSpring::width(SaturationLabel)));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, SaturationLabel, LayoutSpringUnrecPtr(LayoutSpring::height(SaturationLabel)));

	//Slider
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _SaturationSlider, 5.0f, SpringLayoutConstraints::EAST_EDGE, SaturationLabel);
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _SaturationSlider, -5.0f, SpringLayoutConstraints::WEST_EDGE, _SaturationSpinner);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _SaturationSlider, 0.0f, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, SaturationLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _SaturationSlider, LayoutSpringUnrecPtr(LayoutSpring::height(_SaturationSlider)));
	
	//Spinner
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _SaturationSpinner, -5.0f, SpringLayoutConstraints::EAST_EDGE, this);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _SaturationSpinner, 0.0f, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, SaturationLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _SaturationSpinner, LayoutSpringUnrecPtr(LayoutSpring::width(_SaturationSpinner)));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _SaturationSpinner, LayoutSpringUnrecPtr(LayoutSpring::height(_SaturationSpinner)));
	 
	//Value
	//Label
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, ValueLabel, 5.0f, SpringLayoutConstraints::WEST_EDGE, this);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, ValueLabel, 5.0f, SpringLayoutConstraints::SOUTH_EDGE, SaturationLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, ValueLabel, LayoutSpringUnrecPtr(LayoutSpring::width(ValueLabel)));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, ValueLabel, LayoutSpringUnrecPtr(LayoutSpring::height(ValueLabel)));

	//Slider
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _ValueSlider, 5.0f, SpringLayoutConstraints::EAST_EDGE, ValueLabel);
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _ValueSlider, -5.0f, SpringLayoutConstraints::WEST_EDGE, _ValueSpinner);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _ValueSlider, 0.0f, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, ValueLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _ValueSlider, LayoutSpringUnrecPtr(LayoutSpring::height(_ValueSlider)));
	
	//Spinner
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _ValueSpinner, -5.0f, SpringLayoutConstraints::EAST_EDGE, this);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _ValueSpinner, 0.0f, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, ValueLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _ValueSpinner, LayoutSpringUnrecPtr(LayoutSpring::width(_ValueSpinner)));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _ValueSpinner, LayoutSpringUnrecPtr(LayoutSpring::height(_ValueSpinner)));
	 
	if(getIncludeAlpha())
	{
		//Alpha
		//Label
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, AlphaLabel, 5.0f, SpringLayoutConstraints::WEST_EDGE, this);
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, AlphaLabel, 5.0f, SpringLayoutConstraints::SOUTH_EDGE, ValueLabel);
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, AlphaLabel, LayoutSpringUnrecPtr(LayoutSpring::width(AlphaLabel)));
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, AlphaLabel, LayoutSpringUnrecPtr(LayoutSpring::height(AlphaLabel)));

		//Slider
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _AlphaSlider, 5.0f, SpringLayoutConstraints::EAST_EDGE, AlphaLabel);
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _AlphaSlider, -5.0f, SpringLayoutConstraints::WEST_EDGE, _AlphaSpinner);
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _AlphaSlider, 0.0f, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, AlphaLabel);
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _AlphaSlider, LayoutSpringUnrecPtr(LayoutSpring::height(_AlphaSlider)));
		
		//Spinner
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _AlphaSpinner, -5.0f, SpringLayoutConstraints::EAST_EDGE, this);
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _AlphaSpinner, 0.0f, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, AlphaLabel);
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _AlphaSpinner, LayoutSpringUnrecPtr(LayoutSpring::width(_AlphaSpinner)));
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _AlphaSpinner, LayoutSpringUnrecPtr(LayoutSpring::height(_AlphaSpinner)));
	}

		clearChildren();
		pushToChildren(HueLabel);
		pushToChildren(_HueSlider);
		pushToChildren(_HueSpinner);
		pushToChildren(SaturationLabel);
		pushToChildren(_SaturationSlider);
		pushToChildren(_SaturationSpinner);
		pushToChildren(ValueLabel);
		pushToChildren(_ValueSlider);
		pushToChildren(_ValueSpinner);
		if(getIncludeAlpha())
		{
			pushToChildren(AlphaLabel);
		    pushToChildren(_AlphaSlider);
			pushToChildren(_AlphaSpinner);
		}
		setLayout(HSVPanelLayout);
}

void HSVColorChooserPanel::updateColorSelectedModel(void)
{
    if(getColorSelectionModel())
    {
	    Color4f TempColor;
	    TempColor.setValuesHSV(static_cast<Real32>(_HueModel->getValue()),
		    static_cast<Real32>(_SaturationModel->getValue())/static_cast<Real32>(_SaturationModel->getMaximum()),
		    static_cast<Real32>(_ValueModel->getValue())/static_cast<Real32>(_ValueModel->getMaximum()));
	    TempColor[3] = static_cast<Real32>(_AlphaModel->getValue())/static_cast<Real32>(_AlphaModel->getMaximum());

	    bool isValueAdjusting = _HueModel->getBoundedRangeModel()->getValueIsAdjusting() ||
		                        _SaturationModel->getBoundedRangeModel()->getValueIsAdjusting() ||
		                        _ValueModel->getBoundedRangeModel()->getValueIsAdjusting() ||
		                        _AlphaModel->getBoundedRangeModel()->getValueIsAdjusting();
	    getColorSelectionModel()->setSelectedColor(TempColor, isValueAdjusting);
    }
}

void HSVColorChooserPanel::attachModelListener(void)
{
    _HueModelStateChangedConnection = _HueModel->getSpinnerModel()->connectStateChanged(boost::bind(&HSVColorChooserPanel::handleControlStateChanged, this, _1));
    _SaturationModelStateChangedConnection = _SaturationModel->getSpinnerModel()->connectStateChanged(boost::bind(&HSVColorChooserPanel::handleControlStateChanged, this, _1));
    _ValueModelStateChangedConnection = _ValueModel->getSpinnerModel()->connectStateChanged(boost::bind(&HSVColorChooserPanel::handleControlStateChanged, this, _1));
    _AlphaModelStateChangedConnection = _AlphaModel->getSpinnerModel()->connectStateChanged(boost::bind(&HSVColorChooserPanel::handleControlStateChanged, this, _1));
}

void HSVColorChooserPanel::dettachModelListener(void)
{
    _HueModelStateChangedConnection.disconnect();
    _SaturationModelStateChangedConnection.disconnect();
    _ValueModelStateChangedConnection.disconnect();
    _AlphaModelStateChangedConnection.disconnect();
}

void HSVColorChooserPanel::init(void)
{
    _HueModel = BoundedRangeSpinnerModelPtr(new BoundedRangeSpinnerModel());
	_SaturationModel = BoundedRangeSpinnerModelPtr(new BoundedRangeSpinnerModel());
	_ValueModel = BoundedRangeSpinnerModelPtr(new BoundedRangeSpinnerModel());
	_AlphaModel = BoundedRangeSpinnerModelPtr(new BoundedRangeSpinnerModel());

	attachModelListener();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

HSVColorChooserPanel::HSVColorChooserPanel(void) :
    Inherited()
{
}

HSVColorChooserPanel::HSVColorChooserPanel(const HSVColorChooserPanel &source) :
    Inherited(source)
{
    init();
}

HSVColorChooserPanel::~HSVColorChooserPanel(void)
{
	dettachModelListener();
}

/*----------------------------- class specific ----------------------------*/

void HSVColorChooserPanel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void HSVColorChooserPanel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump HSVColorChooserPanel NI" << std::endl;
}

void HSVColorChooserPanel::handleControlStateChanged(ChangeEventDetails* const e)
{
	//Update the Color Selected Model
	updateColorSelectedModel();
}

OSG_END_NAMESPACE
