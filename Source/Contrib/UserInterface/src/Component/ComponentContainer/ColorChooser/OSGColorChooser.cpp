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

#include "OSGColorChooser.h"
#include "OSGAbstractColorChooserPanel.h"
#include "OSGDefaultColorSelectionModel.h"
#include "OSGTabPanel.h"
#include "OSGLabel.h"
#include "OSGColorLayer.h"
#include "OSGDefaultColorSelectionModel.h"
#include "OSGFieldContainerFactory.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGColorChooserBase.cpp file.
// To modify it, please change the .fcd file (OSGColorChooser.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ColorChooser::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ColorChooser::updateLayout(void)
{
	Pnt2f InsetsTopLeft, InsetsBottomRight;
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

	ComponentRefPtr PreviewPanel;
	if(getPreviewPanel() != NULL)
	{
		PreviewPanel = getPreviewPanel();
	}
	else
	{
		PreviewPanel = _DefaultPreviewPanel;
	}
	Pnt2f PreviewTopLeft(InsetsTopLeft.x(), InsetsBottomRight.y()), PreviewBottomRight(InsetsBottomRight);
	PreviewTopLeft.setValues(PreviewTopLeft.x(), InsetsBottomRight.y()-PreviewPanel->getPreferredSize().y());
    if(PreviewPanel->getPosition() != PreviewTopLeft)
    {
		PreviewPanel->setPosition(PreviewTopLeft);
    }
       
    Vec2f Size; 
    Size = PreviewBottomRight - PreviewTopLeft;
    if(PreviewPanel->getSize() != Size)
    {
		PreviewPanel->setSize(Size);
    }

	Pnt2f ChooserTopLeft(InsetsTopLeft),
		  ChooserBottomRight(InsetsBottomRight.x(), PreviewTopLeft.y());
	if(_ColorChooserPanels.size() > 1 &&
		_LayoutTabPanel != NULL)
	{
        if(_LayoutTabPanel->getPosition() != ChooserTopLeft)
        {
			_LayoutTabPanel->setPosition(ChooserTopLeft);
        }
        Size = ChooserBottomRight - ChooserTopLeft;
        if(_LayoutTabPanel->getSize() != Size)
        {
			_LayoutTabPanel->setSize(Size);
        }
	}
	else if(_ColorChooserPanels.size() == 1)
	{
        if(_ColorChooserPanels.front()->getPosition() != ChooserTopLeft)
        {
			_ColorChooserPanels.front()->setPosition(ChooserTopLeft);
        }
        Size = ChooserBottomRight - ChooserTopLeft;
        if(_ColorChooserPanels.front()->getSize() != Size)
        {
			_ColorChooserPanels.front()->setSize(Size);
        }
	}

}

void ColorChooser::addChooserPanel(AbstractColorChooserPanel* const panel)
{
    panel->setInternalParentChooser(this);

    _ColorChooserPanels.push_back(panel);

	panel->installChooserPanel(this);
}

const ColorChooser::ColorChooserPanelVector& ColorChooser::getChooserPanels(void) const
{
	return _ColorChooserPanels;
}

Color4f ColorChooser::getColor(void) const
{
	if(getSelectionModel() != NULL)
	{
		return getSelectionModel()->getSelectedColor();
	}
	else
	{
		return Color4f();
	}
}

AbstractColorChooserPanel* ColorChooser::removeChooserPanel(AbstractColorChooserPanel* const panel)
{
    ColorChooserPanelVector::iterator SearchItor(std::find(_ColorChooserPanels.begin(), _ColorChooserPanels.end(),panel));
    if(SearchItor == _ColorChooserPanels.end())
	{
		panel->uninstallChooserPanel(this);

        panel->setInternalParentChooser(NULL);
        _ColorChooserPanels.erase(SearchItor);

		return panel;
	}
	else
	{
		return NULL;
	}
}

void ColorChooser::setChooserPanels(ColorChooserPanelVector panels)
{
	//Add all of the panels
	for(UInt32 i(0) ; i< panels.size() ; ++i)
	{
		addChooserPanel(panels[i]);
	}

	//Remove all of the panels not in
	ColorChooserPanelVector RemovalVector;
	for(UInt32 i(0) ; i<_ColorChooserPanels.size() ; ++i)
	{
		if(std::find(panels.begin(), panels.end(), _ColorChooserPanels[i]) == panels.end())
		{
			RemovalVector.push_back(_ColorChooserPanels[i]);
		}
	}
	for(UInt32 i(0) ; i<RemovalVector.size() ; ++i)
	{
		removeChooserPanel(RemovalVector[i]);
	}
}

void ColorChooser::setColor(const Color4f& color)
{
	if(getSelectionModel() != NULL)
	{
		getSelectionModel()->setSelectedColor(color,false);
	}
}

void ColorChooser::updateChoosers(void)
{
    _DefaultPreviewPanelBackground->setColor(getSelectionModel()->getSelectedColor());

    //dettach Models
	for(UInt32 i(0) ; i<_ColorChooserPanels.size() ; ++i)
	{
		_ColorChooserPanels[i]->dettachModelListener();
    }

	for(UInt32 i(0) ; i<_ColorChooserPanels.size() ; ++i)
	{
		_ColorChooserPanels[i]->updateChooser();
	}

	//commitChanges();

    //Reattach Model
	for(UInt32 i(0) ; i<_ColorChooserPanels.size() ; ++i)
	{
		_ColorChooserPanels[i]->attachModelListener();
    }
}

void ColorChooser::createDefaultPanel(void)
{
	_DefaultPreviewPanelBackground = ColorLayer::create();

	_DefaultPreviewPanel = Label::create();
	_DefaultPreviewPanel->setPreferredSize(Vec2f(50.0f,50.0f));
	_DefaultPreviewPanel->setBorders(NULL);
	_DefaultPreviewPanel->setBackgrounds(_DefaultPreviewPanelBackground);

}

void ColorChooser::updateChildren(void)
{
	if(_ColorChooserPanels.size() > 1)
	{
		if(_LayoutTabPanel == NULL)
		{
			_LayoutTabPanel = TabPanel::create();
		}

		_LayoutTabPanel->removeAllTabs();
		LabelRefPtr TabLabel;
		for(UInt32 i(0) ; i<_ColorChooserPanels.size() ; ++i)
		{
			TabLabel = Label::create();
			TabLabel->setText(_ColorChooserPanels[i]->getDisplayText());
			TabLabel->setBorders(NULL);
			TabLabel->setBackgrounds(NULL);

			_LayoutTabPanel->addTab(TabLabel, _ColorChooserPanels[i]);
		}

        _LayoutTabPanel->setSelectedIndex(0);

		clearChildren();
		pushToChildren(_LayoutTabPanel);
		if(getPreviewPanel() != NULL)
		{
			pushToChildren(getPreviewPanel());
		}
		else
		{
			pushToChildren(_DefaultPreviewPanel);
		}
	}
	else if(_ColorChooserPanels.size() == 1)
	{
		if(_LayoutTabPanel != NULL)
		{
			_LayoutTabPanel = NULL;
		}

		clearChildren();
		pushToChildren(_ColorChooserPanels.front());
		if(getPreviewPanel() != NULL)
		{
			pushToChildren(getPreviewPanel());
		}
		else
		{
			pushToChildren(_DefaultPreviewPanel);
		}
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void ColorChooser::onCreate(const ColorChooser * Id)
{
	Inherited::onCreate(Id);

    if(GlobalSystemState == Startup)
    {
        return;
    }

    DefaultColorSelectionModelUnrecPtr Model = DefaultColorSelectionModel::create();
    setSelectionModel(Model);
    _ColorSelectedStateChangedConnection = getSelectionModel()->connectStateChanged(boost::bind(&ColorChooser::handleColorSelectedStateChanged, this, _1));

	createDefaultPanel();

    FieldContainerType* type;
    for(UInt32 i(0) ; i<getMFChooserPanelTypeIds()->size(); ++i)
    {
        type = FieldContainerFactory::the()->findType(getChooserPanelTypeIds(i));
        if(type != NULL)
        {
            if(type->isDerivedFrom(AbstractColorChooserPanel::getClassType()))
            {
                AbstractColorChooserPanelRecPtr ColorPanel = dynamic_pointer_cast<AbstractColorChooserPanel>(type->createContainer());
                ColorPanel->setInternalParentChooser(this);
		        _ColorChooserPanels.push_back(ColorPanel);
            }
        }
	}
    for(UInt32 i(0) ; i<_ColorChooserPanels.size() ; ++i)
	{
        _ColorChooserPanels[i]->installChooserPanel(this);
    }
	
	updateChildren();
}

void ColorChooser::onDestroy()
{
}

void ColorChooser::resolveLinks(void)
{
    Inherited::resolveLinks();

    _LayoutTabPanel = NULL;

    _DefaultPreviewPanel = NULL;

    _DefaultPreviewPanelBackground = NULL;

    _ColorChooserPanels.clear();

    _ColorSelectedStateChangedConnection.disconnect();
}

/*----------------------- constructors & destructors ----------------------*/

ColorChooser::ColorChooser(void) :
    Inherited(),
		_LayoutTabPanel(NULL)
{
}

ColorChooser::ColorChooser(const ColorChooser &source) :
    Inherited(source),
		_LayoutTabPanel(NULL)
{
}

ColorChooser::~ColorChooser(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ColorChooser::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

	if(whichField & PreviewPanelFieldMask)
	{
        _ColorSelectedStateChangedConnection.disconnect();
        if(getSelectionModel())
        {
            _ColorSelectedStateChangedConnection = getSelectionModel()->connectStateChanged(boost::bind(&ColorChooser::handleColorSelectedStateChanged, this, _1));
	        updateChoosers();
        }
    }
	if(whichField & PreviewPanelFieldMask)
	{
		updateChildren();
	}
}

void ColorChooser::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ColorChooser NI" << std::endl;
}

void ColorChooser::handleColorSelectedStateChanged(ChangeEventDetails* const e)
{
	updateChoosers();
}

OSG_END_NAMESPACE
