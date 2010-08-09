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

#include "OSGRGBColorChooserPanel.h"
#include "OSGSpinner.h"
#include "OSGSlider.h"
#include "OSGLabel.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"
#include "OSGLayoutSpring.h"
#include "OSGGradientLayer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGRGBColorChooserPanelBase.cpp file.
// To modify it, please change the .fcd file (OSGRGBColorChooserPanel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RGBColorChooserPanel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
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
    Int32 Red,Green,Blue,Alpha;

    Color4f ColorSelected(getColorFromModel());
    //Update the Red Bounded Range
    Red = osgClamp(0.0f, ColorSelected.red(), 1.0f) * 255;
    if(static_cast<Int32>(Red) != _RedModel->getValue())
    {
        _RedModel->setValue(Red);
    }
    _RedSliderTrackBackground->editMFColors()->clear();
    _RedSliderTrackBackground->editMFStops()->clear();
    _RedSliderTrackBackground->editMFColors()->push_back(Color4f(0.0f,
                                                                 ColorSelected.green(),
                                                                 ColorSelected.blue(),
                                                                 ColorSelected.alpha()));
    _RedSliderTrackBackground->editMFStops()->push_back(0.0);
    _RedSliderTrackBackground->editMFColors()->push_back(Color4f(1.0f,
                                                                 ColorSelected.green(),
                                                                 ColorSelected.blue(),
                                                                 ColorSelected.alpha()));
    _RedSliderTrackBackground->editMFStops()->push_back(1.0);

    //Update the Green Bounded Range
    Green = osgClamp(0.0f, ColorSelected.green(), 1.0f) * 255;
    if(static_cast<Int32>(Green) != _GreenModel->getValue())
    {
        _GreenModel->setValue(Green);
    }
    _GreenSliderTrackBackground->editMFColors()->clear();
    _GreenSliderTrackBackground->editMFStops()->clear();
    _GreenSliderTrackBackground->editMFColors()->push_back(Color4f(ColorSelected.red(),
                                                                   0.0f,
                                                                   ColorSelected.blue(),
                                                                   ColorSelected.alpha()));
    _GreenSliderTrackBackground->editMFStops()->push_back(0.0);
    _GreenSliderTrackBackground->editMFColors()->push_back(Color4f(ColorSelected.red(),
                                                                   1.0f,
                                                                   ColorSelected.blue(),
                                                                   ColorSelected.alpha()));
    _GreenSliderTrackBackground->editMFStops()->push_back(1.0);

    //Update the Blue Bounded Range
    Blue = osgClamp(0.0f, ColorSelected.blue(), 1.0f) * 255;
    if(static_cast<Int32>(Blue) != _BlueModel->getValue())
    {
        _BlueModel->setValue(Blue);
    }
    _BlueSliderTrackBackground->editMFColors()->clear();
    _BlueSliderTrackBackground->editMFStops()->clear();
    _BlueSliderTrackBackground->editMFColors()->push_back(Color4f(ColorSelected.red(),
                                                                  ColorSelected.green(),
                                                                  0.0f,
                                                                  ColorSelected.alpha()));
    _BlueSliderTrackBackground->editMFStops()->push_back(0.0);
    _BlueSliderTrackBackground->editMFColors()->push_back(Color4f(ColorSelected.red(),
                                                                  ColorSelected.green(),
                                                                  1.0f,
                                                                  ColorSelected.alpha()));
    _BlueSliderTrackBackground->editMFStops()->push_back(1.0);

    //Update the Alpha Bounded Range
    Alpha = osgClamp(0.0f, ColorSelected.alpha(), 1.0f) * 255;
    if(static_cast<Int32>(Alpha) != _AlphaModel->getValue())
    {
        _AlphaModel->setValue(Alpha);
    }

    if(getIncludeAlpha())
    {
        _AlphaSliderTrackBackground->editMFColors()->clear();
        _AlphaSliderTrackBackground->editMFStops()->clear();
        _AlphaSliderTrackBackground->editMFColors()->push_back(Color4f(ColorSelected.red(),
                                                                       ColorSelected.green(),
                                                                       ColorSelected.blue(),
                                                                       0.0f));
        _AlphaSliderTrackBackground->editMFStops()->push_back(0.0);
        _AlphaSliderTrackBackground->editMFColors()->push_back(Color4f(ColorSelected.red(),
                                                                       ColorSelected.green(),
                                                                       ColorSelected.blue(),
                                                                       1.0f));
        _AlphaSliderTrackBackground->editMFStops()->push_back(1.0);
    }
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
    _RedSliderTrackBackground->setStartPosition(Vec2f(0.0f,0.0f));
    _RedSliderTrackBackground->setEndPosition(Vec2f(1.0f,0.0f));

    UIDrawObjectCanvasRefPtr RedSliderTrackCanvas = UIDrawObjectCanvas::create();
    RedSliderTrackCanvas->setPreferredSize(Vec2f(15.0f,15.0f));
    RedSliderTrackCanvas->setBorders(NULL);
    RedSliderTrackCanvas->setBackgrounds(_RedSliderTrackBackground);

    _RedSlider = Slider::create();
    _RedSlider->setDrawLabels(false);
    _RedSlider->setDrawMajorTicks(false);
    _RedSlider->setDrawMinorTicks(false);
    _RedSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);
    _RedSlider->setTrackDrawObject(RedSliderTrackCanvas);
    _RedSlider->setRangeModel(_RedModel->getBoundedRangeModel());

    //Green
    _GreenSliderTrackBackground = GradientLayer::create();
    _GreenSliderTrackBackground->setStartPosition(Vec2f(0.0f,0.0f));
    _GreenSliderTrackBackground->setEndPosition(Vec2f(1.0f,0.0f));

    UIDrawObjectCanvasRefPtr GreenSliderTrackCanvas = UIDrawObjectCanvas::create();
    GreenSliderTrackCanvas->setPreferredSize(Vec2f(15.0f,15.0f));
    GreenSliderTrackCanvas->setBorders(NULL);
    GreenSliderTrackCanvas->setBackgrounds(_GreenSliderTrackBackground);

    _GreenSlider = Slider::create();
    _GreenSlider->setDrawLabels(false);
    _GreenSlider->setDrawMajorTicks(false);
    _GreenSlider->setDrawMinorTicks(false);
    _GreenSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);;
    _GreenSlider->setTrackDrawObject(GreenSliderTrackCanvas);
    _GreenSlider->setRangeModel(_GreenModel->getBoundedRangeModel());

    //Blue
    _BlueSliderTrackBackground = GradientLayer::create();
    _BlueSliderTrackBackground->setStartPosition(Vec2f(0.0f,0.0f));
    _BlueSliderTrackBackground->setEndPosition(Vec2f(1.0f,0.0f));

    UIDrawObjectCanvasRefPtr BlueSliderTrackCanvas = UIDrawObjectCanvas::create();
    BlueSliderTrackCanvas->setPreferredSize(Vec2f(15.0f,15.0f));
    BlueSliderTrackCanvas->setBorders(NULL);
    BlueSliderTrackCanvas->setBackgrounds(_BlueSliderTrackBackground);

    _BlueSlider = Slider::create();
    _BlueSlider->setDrawLabels(false);
    _BlueSlider->setDrawMajorTicks(false);
    _BlueSlider->setDrawMinorTicks(false);
    _BlueSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);;
    _BlueSlider->setTrackDrawObject(BlueSliderTrackCanvas);
    _BlueSlider->setRangeModel(_BlueModel->getBoundedRangeModel());

    if(getIncludeAlpha())
    {
        _AlphaSliderTrackBackground = GradientLayer::create();
        _AlphaSliderTrackBackground->setStartPosition(Vec2f(0.0f,0.0f));
        _AlphaSliderTrackBackground->setEndPosition(Vec2f(1.0f,0.0f));

        UIDrawObjectCanvasRefPtr AlphaSliderTrackCanvas = UIDrawObjectCanvas::create();
        AlphaSliderTrackCanvas->setPreferredSize(Vec2f(15.0f,15.0f));
        AlphaSliderTrackCanvas->setBorders(NULL);
        AlphaSliderTrackCanvas->setBackgrounds(_AlphaSliderTrackBackground);

        _AlphaSlider = Slider::create();
        _AlphaSlider->setDrawLabels(false);
        _AlphaSlider->setDrawMajorTicks(false);
        _AlphaSlider->setDrawMinorTicks(false);
        _AlphaSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);;
        _AlphaSlider->setTrackDrawObject(AlphaSliderTrackCanvas);
        _AlphaSlider->setRangeModel(_AlphaModel->getBoundedRangeModel());
    }

    //Labels
    LabelRefPtr RedLabel = Label::create();
    RedLabel->setText("Red");
    RedLabel->setPreferredSize(Vec2f(50.0f, RedLabel->getPreferredSize().y()));
    RedLabel->setBackgrounds(NULL);
    RedLabel->setBorders(NULL);

    LabelRefPtr GreenLabel = Label::create();
    GreenLabel->setText("Green");
    GreenLabel->setPreferredSize(Vec2f(50.0f, GreenLabel->getPreferredSize().y()));
    GreenLabel->setBackgrounds(NULL);
    GreenLabel->setBorders(NULL);

    LabelRefPtr BlueLabel = Label::create();
    BlueLabel->setText("Blue");
    BlueLabel->setPreferredSize(Vec2f(50.0f, BlueLabel->getPreferredSize().y()));
    BlueLabel->setBackgrounds(NULL);
    BlueLabel->setBorders(NULL);

    LabelRefPtr AlphaLabel = Label::create();
    if(getIncludeAlpha())
    {
        AlphaLabel->setText("Alpha");
        AlphaLabel->setPreferredSize(Vec2f(50.0f, AlphaLabel->getPreferredSize().y()));
        AlphaLabel->setBackgrounds(NULL);
        AlphaLabel->setBorders(NULL);
    }

    //Layout
    SpringLayoutRefPtr RGBPanelLayout = SpringLayout::create();

    //Red
    //Label
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, RedLabel, 5.0f, SpringLayoutConstraints::WEST_EDGE, this);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, RedLabel, 5.0f, SpringLayoutConstraints::NORTH_EDGE, this);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, RedLabel, LayoutSpringUnrecPtr(LayoutSpring::width(RedLabel)));
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, RedLabel, LayoutSpringUnrecPtr(LayoutSpring::height(RedLabel)));

    //Slider
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _RedSlider, 5.0f, SpringLayoutConstraints::EAST_EDGE, RedLabel);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _RedSlider, -5.0f, SpringLayoutConstraints::WEST_EDGE, _RedSpinner);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _RedSlider, 0.0f, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, RedLabel);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _RedSlider, LayoutSpringUnrecPtr(LayoutSpring::height(_RedSlider)));

    //Spinner
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _RedSpinner, -5.0f, SpringLayoutConstraints::EAST_EDGE, this);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _RedSpinner, 0.0f, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, RedLabel);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _RedSpinner, LayoutSpringUnrecPtr(LayoutSpring::width(_RedSpinner)));
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _RedSpinner, LayoutSpringUnrecPtr(LayoutSpring::height(_RedSpinner)));

    //Green
    //Label
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, GreenLabel, 5.0f, SpringLayoutConstraints::WEST_EDGE, this);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, GreenLabel, 5.0f, SpringLayoutConstraints::SOUTH_EDGE, RedLabel);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, GreenLabel, LayoutSpringUnrecPtr(LayoutSpring::width(GreenLabel)));
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, GreenLabel, LayoutSpringUnrecPtr(LayoutSpring::height(GreenLabel)));

    //Slider
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _GreenSlider, 5.0f, SpringLayoutConstraints::EAST_EDGE, GreenLabel);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _GreenSlider, -5.0f, SpringLayoutConstraints::WEST_EDGE, _GreenSpinner);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _GreenSlider, 0.0f, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, GreenLabel);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _GreenSlider, LayoutSpringUnrecPtr(LayoutSpring::height(_GreenSlider)));

    //Spinner
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _GreenSpinner, -5.0f, SpringLayoutConstraints::EAST_EDGE, this);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _GreenSpinner, 0.0f, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, GreenLabel);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _GreenSpinner, LayoutSpringUnrecPtr(LayoutSpring::width(_GreenSpinner)));
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _GreenSpinner, LayoutSpringUnrecPtr(LayoutSpring::height(_GreenSpinner)));

    //Blue
    //Label
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, BlueLabel, 5.0f, SpringLayoutConstraints::WEST_EDGE, this);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, BlueLabel, 5.0f, SpringLayoutConstraints::SOUTH_EDGE, GreenLabel);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, BlueLabel, LayoutSpringUnrecPtr(LayoutSpring::width(BlueLabel)));
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, BlueLabel, LayoutSpringUnrecPtr(LayoutSpring::height(BlueLabel)));

    //Slider
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _BlueSlider, 5.0f, SpringLayoutConstraints::EAST_EDGE, BlueLabel);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _BlueSlider, -5.0f, SpringLayoutConstraints::WEST_EDGE, _BlueSpinner);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _BlueSlider, 0.0f, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, BlueLabel);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _BlueSlider, LayoutSpringUnrecPtr(LayoutSpring::height(_BlueSlider)));

    //Spinner
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _BlueSpinner, -5.0f, SpringLayoutConstraints::EAST_EDGE, this);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _BlueSpinner, 0.0f, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, BlueLabel);
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _BlueSpinner, LayoutSpringUnrecPtr(LayoutSpring::width(_BlueSpinner)));
    RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _BlueSpinner, LayoutSpringUnrecPtr(LayoutSpring::height(_BlueSpinner)));

    if(getIncludeAlpha())
    {
        //Alpha
        //Label
        RGBPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, AlphaLabel, 5.0f, SpringLayoutConstraints::WEST_EDGE, this);
        RGBPanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, AlphaLabel, 5.0f, SpringLayoutConstraints::SOUTH_EDGE, BlueLabel);
        RGBPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, AlphaLabel, LayoutSpringUnrecPtr(LayoutSpring::width(AlphaLabel)));
        RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, AlphaLabel, LayoutSpringUnrecPtr(LayoutSpring::height(AlphaLabel)));

        //Slider
        RGBPanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _AlphaSlider, 5.0f, SpringLayoutConstraints::EAST_EDGE, AlphaLabel);
        RGBPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _AlphaSlider, -5.0f, SpringLayoutConstraints::WEST_EDGE, _AlphaSpinner);
        RGBPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _AlphaSlider, 0.0f, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, AlphaLabel);
        RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _AlphaSlider, LayoutSpringUnrecPtr(LayoutSpring::height(_AlphaSlider)));

        //Spinner
        RGBPanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _AlphaSpinner, -5, SpringLayoutConstraints::EAST_EDGE, this);
        RGBPanelLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _AlphaSpinner, 0.0f, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, AlphaLabel);
        RGBPanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _AlphaSpinner, LayoutSpringUnrecPtr(LayoutSpring::width(_AlphaSpinner)));
        RGBPanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, _AlphaSpinner, LayoutSpringUnrecPtr(LayoutSpring::height(_AlphaSpinner)));
    }

    clearChildren();
    pushToChildren(RedLabel);
    pushToChildren(_RedSlider);
    pushToChildren(_RedSpinner);
    pushToChildren(GreenLabel);
    pushToChildren(_GreenSlider);
    pushToChildren(_GreenSpinner);
    pushToChildren(BlueLabel);
    pushToChildren(_BlueSlider);
    pushToChildren(_BlueSpinner);
    if(getIncludeAlpha())
    {
        pushToChildren(AlphaLabel);
        pushToChildren(_AlphaSlider);
        pushToChildren(_AlphaSpinner);
    }
    setLayout(RGBPanelLayout);
}

void RGBColorChooserPanel::updateColorSelectedModel(void)
{
    if(getColorSelectionModel())
    {
        bool isValueAdjusting = _RedModel->getBoundedRangeModel()->getValueIsAdjusting() ||
            _GreenModel->getBoundedRangeModel()->getValueIsAdjusting() ||
            _BlueModel->getBoundedRangeModel()->getValueIsAdjusting() ||
            _AlphaModel->getBoundedRangeModel()->getValueIsAdjusting();
        getColorSelectionModel()->setSelectedColor(Color4f(static_cast<Real32>(_RedModel->getValue())/static_cast<Real32>(_RedModel->getMaximum()),
                                                           static_cast<Real32>(_GreenModel->getValue())/static_cast<Real32>(_GreenModel->getMaximum()),
                                                           static_cast<Real32>(_BlueModel->getValue())/static_cast<Real32>(_BlueModel->getMaximum()),
                                                           static_cast<Real32>(_AlphaModel->getValue())/static_cast<Real32>(_AlphaModel->getMaximum())),
                                                   isValueAdjusting);
    }
}

void RGBColorChooserPanel::attachModelListener(void)
{
    _RedModelStateChangedConnection = _RedModel->getSpinnerModel()->connectStateChanged(boost::bind(&RGBColorChooserPanel::handleControlStateChanged, this, _1));
    _GreenModelStateChangedConnection = _GreenModel->getSpinnerModel()->connectStateChanged(boost::bind(&RGBColorChooserPanel::handleControlStateChanged, this, _1));
    _BlueModelStateChangedConnection = _BlueModel->getSpinnerModel()->connectStateChanged(boost::bind(&RGBColorChooserPanel::handleControlStateChanged, this, _1));
    _AlphaModelStateChangedConnection = _AlphaModel->getSpinnerModel()->connectStateChanged(boost::bind(&RGBColorChooserPanel::handleControlStateChanged, this, _1));
}

void RGBColorChooserPanel::dettachModelListener(void)
{
    _RedModelStateChangedConnection.disconnect();
    _GreenModelStateChangedConnection.disconnect();
    _BlueModelStateChangedConnection.disconnect();
    _AlphaModelStateChangedConnection.disconnect();
}

void RGBColorChooserPanel::init(void)
{
    _RedModel   = BoundedRangeSpinnerModelPtr(new BoundedRangeSpinnerModel());
    _GreenModel = BoundedRangeSpinnerModelPtr(new BoundedRangeSpinnerModel());
    _BlueModel  = BoundedRangeSpinnerModelPtr(new BoundedRangeSpinnerModel());
    _AlphaModel = BoundedRangeSpinnerModelPtr(new BoundedRangeSpinnerModel());

    attachModelListener();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void RGBColorChooserPanel::resolveLinks(void)
{
    Inherited::resolveLinks();

    _RedSpinner = NULL;
    _GreenSpinner = NULL;
    _BlueSpinner = NULL;
    _AlphaSpinner = NULL;

    _RedSliderTrackBackground = NULL;
    _GreenSliderTrackBackground = NULL;
    _BlueSliderTrackBackground = NULL;
    _AlphaSliderTrackBackground = NULL;

    _RedSlider = NULL;
    _GreenSlider = NULL;
    _BlueSlider = NULL;
    _AlphaSlider = NULL;
}

/*----------------------- constructors & destructors ----------------------*/

RGBColorChooserPanel::RGBColorChooserPanel(void) :
    Inherited()
{
}

RGBColorChooserPanel::RGBColorChooserPanel(const RGBColorChooserPanel &source) :
    Inherited(source)
{
    init();
}

RGBColorChooserPanel::~RGBColorChooserPanel(void)
{
	dettachModelListener();
}

/*----------------------------- class specific ----------------------------*/

void RGBColorChooserPanel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void RGBColorChooserPanel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump RGBColorChooserPanel NI" << std::endl;
}

void RGBColorChooserPanel::handleControlStateChanged(ChangeEventDetails* const e)
{
	//Update the Color Selected Model
	updateColorSelectedModel();
}

OSG_END_NAMESPACE
