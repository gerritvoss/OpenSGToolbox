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
    dettachModelListener();

    Real32 Hue, Saturation, Value;
    getColorFromModel().getValuesHSV(Hue, Saturation, Value);
    Color4f TempColor(getColorFromModel());
    //Update the Hue Bounded Range
    Hue = osgClamp<Real32>(_HueModel->getMinimum(), Hue, _HueModel->getMaximum());
    if(static_cast<Int32>(Hue) != _HueModel->getValue())
    {
        //_HueModel->setValue(Hue);
    }
    _HueSliderTrackBackground->editMFColors()->clear();
    _HueSliderTrackBackground->editMFStops()->clear();
    //Red
    TempColor.setValuesHSV(0.0f, Saturation, Value);
    _HueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _HueSliderTrackBackground->editMFStops()->push_back(0.0);
    //Yellow
    TempColor.setValuesHSV(60.0f, Saturation, Value);
    _HueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _HueSliderTrackBackground->editMFStops()->push_back(0.166667);
    //Green
    TempColor.setValuesHSV(120.0f, Saturation, Value);
    _HueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _HueSliderTrackBackground->editMFStops()->push_back(0.333333);
    //Teal
    TempColor.setValuesHSV(180.0f, Saturation, Value);
    _HueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _HueSliderTrackBackground->editMFStops()->push_back(0.5);
    //Blue
    TempColor.setValuesHSV(240.0f, Saturation, Value);
    _HueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _HueSliderTrackBackground->editMFStops()->push_back(0.666667);
    //Purple
    TempColor.setValuesHSV(300.0f, Saturation, Value);
    _HueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _HueSliderTrackBackground->editMFStops()->push_back(0.833333);
    //Red
    TempColor.setValuesHSV(360.0f, Saturation, Value);
    _HueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _HueSliderTrackBackground->editMFStops()->push_back(1.0);

    //Update the Saturation Bounded Range
    //_SaturationModel->setValue(osgClamp(0.0f, Saturation, 1.0f) * _SaturationModel->getMaximum());
    _SaturationSliderTrackBackground->editMFColors()->clear();
    _SaturationSliderTrackBackground->editMFStops()->clear();
    TempColor.setValuesHSV(Hue, 0.0f, Value);
    _SaturationSliderTrackBackground->editMFColors()->push_back(TempColor);
    _SaturationSliderTrackBackground->editMFStops()->push_back(0.0);
    TempColor.setValuesHSV(Hue, 1.0f, Value);
    _SaturationSliderTrackBackground->editMFColors()->push_back(TempColor);
    _SaturationSliderTrackBackground->editMFStops()->push_back(1.0);

    //Update the Value Bounded Range
    //_ValueModel->setValue(osgClamp(0.0f, Value, 1.0f) * _ValueModel->getMaximum());
    _ValueSliderTrackBackground->editMFColors()->clear();
    _ValueSliderTrackBackground->editMFStops()->clear();
    TempColor.setValuesHSV(Hue, Saturation, 0.0f);
    _ValueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _ValueSliderTrackBackground->editMFStops()->push_back(0.0);
    TempColor.setValuesHSV(Hue, Saturation, 1.0f);
    _ValueSliderTrackBackground->editMFColors()->push_back(TempColor);
    _ValueSliderTrackBackground->editMFStops()->push_back(1.0);

    //Update the Alpha Bounded Range
    //_AlphaModel->setValue(osgClamp(0.0f, getColorFromModel().alpha(), 1.0f) * _AlphaModel->getMaximum());

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
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, HueLabel, 5, SpringLayoutConstraints::WEST_EDGE, HSVColorChooserPanelRefPtr(this));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, HueLabel, 5, SpringLayoutConstraints::NORTH_EDGE, HSVColorChooserPanelRefPtr(this));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, HueLabel, LayoutSpring::width(HueLabel));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, HueLabel, LayoutSpring::height(HueLabel));

	//Slider
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _HueSlider, 5, SpringLayoutConstraints::EAST_EDGE, HueLabel);
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _HueSlider, -5, SpringLayoutConstraints::WEST_EDGE, _HueSpinner);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _HueSlider, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, HueLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _HueSlider, LayoutSpring::height(_HueSlider));
	
	//Spinner
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _HueSpinner, -5, SpringLayoutConstraints::EAST_EDGE, HSVColorChooserPanelRefPtr(this));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _HueSpinner, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, HueLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _HueSpinner, LayoutSpring::width(_HueSpinner));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _HueSpinner, LayoutSpring::height(_HueSpinner));
	 
	//Saturation
	//Label
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, SaturationLabel, 5, SpringLayoutConstraints::WEST_EDGE, HSVColorChooserPanelRefPtr(this));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, SaturationLabel, 5, SpringLayoutConstraints::SOUTH_EDGE, HueLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, SaturationLabel, LayoutSpring::width(SaturationLabel));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, SaturationLabel, LayoutSpring::height(SaturationLabel));

	//Slider
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _SaturationSlider, 5, SpringLayoutConstraints::EAST_EDGE, SaturationLabel);
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _SaturationSlider, -5, SpringLayoutConstraints::WEST_EDGE, _SaturationSpinner);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _SaturationSlider, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, SaturationLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _SaturationSlider, LayoutSpring::height(_SaturationSlider));
	
	//Spinner
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _SaturationSpinner, -5, SpringLayoutConstraints::EAST_EDGE, HSVColorChooserPanelRefPtr(this));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _SaturationSpinner, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, SaturationLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _SaturationSpinner, LayoutSpring::width(_SaturationSpinner));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _SaturationSpinner, LayoutSpring::height(_SaturationSpinner));
	 
	//Value
	//Label
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, ValueLabel, 5, SpringLayoutConstraints::WEST_EDGE, HSVColorChooserPanelRefPtr(this));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, ValueLabel, 5, SpringLayoutConstraints::SOUTH_EDGE, SaturationLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, ValueLabel, LayoutSpring::width(ValueLabel));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, ValueLabel, LayoutSpring::height(ValueLabel));

	//Slider
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _ValueSlider, 5, SpringLayoutConstraints::EAST_EDGE, ValueLabel);
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _ValueSlider, -5, SpringLayoutConstraints::WEST_EDGE, _ValueSpinner);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _ValueSlider, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, ValueLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _ValueSlider, LayoutSpring::height(_ValueSlider));
	
	//Spinner
    HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _ValueSpinner, -5, SpringLayoutConstraints::EAST_EDGE, HSVColorChooserPanelRefPtr(this));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _ValueSpinner, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, ValueLabel);
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _ValueSpinner, LayoutSpring::width(_ValueSpinner));
	HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _ValueSpinner, LayoutSpring::height(_ValueSpinner));
	 
	if(getIncludeAlpha())
	{
		//Alpha
		//Label
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, AlphaLabel, 5, SpringLayoutConstraints::WEST_EDGE, HSVColorChooserPanelRefPtr(this));
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, AlphaLabel, 5, SpringLayoutConstraints::SOUTH_EDGE, ValueLabel);
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, AlphaLabel, LayoutSpring::width(AlphaLabel));
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, AlphaLabel, LayoutSpring::height(AlphaLabel));

		//Slider
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _AlphaSlider, 5, SpringLayoutConstraints::EAST_EDGE, AlphaLabel);
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _AlphaSlider, -5, SpringLayoutConstraints::WEST_EDGE, _AlphaSpinner);
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _AlphaSlider, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, AlphaLabel);
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _AlphaSlider, LayoutSpring::height(_AlphaSlider));
		
		//Spinner
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _AlphaSpinner, -5, SpringLayoutConstraints::EAST_EDGE, HSVColorChooserPanelRefPtr(this));
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _AlphaSpinner, 0, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, AlphaLabel);
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _AlphaSpinner, LayoutSpring::width(_AlphaSpinner));
		HSVPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _AlphaSpinner, LayoutSpring::height(_AlphaSpinner));
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
    Inherited(),
	_BoundedRangeSpinnerChangeListener(this)
{
}

HSVColorChooserPanel::HSVColorChooserPanel(const HSVColorChooserPanel &source) :
    Inherited(source),
	_BoundedRangeSpinnerChangeListener(this)
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

void HSVColorChooserPanel::BoundedRangeSpinnerChangeListener::stateChanged(const ChangeEventUnrecPtr e)
{
	//Update the Color Selected Model
	_HSVColorChooserPanel->updateColorSelectedModel();
}

OSG_END_NAMESPACE
