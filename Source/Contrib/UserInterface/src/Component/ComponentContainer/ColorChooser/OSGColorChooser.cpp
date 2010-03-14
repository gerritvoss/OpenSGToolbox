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
		PreviewPanel->setPosition(PreviewTopLeft);
		PreviewPanel->setSize(PreviewBottomRight - PreviewTopLeft);

	Pnt2f ChooserTopLeft(InsetsTopLeft),
		  ChooserBottomRight(InsetsBottomRight.x(), PreviewTopLeft.y());
	if(getMFInternalChooserPanels()->size() > 1 &&
		_LayoutTabPanel != NULL)
	{
			_LayoutTabPanel->setPosition(ChooserTopLeft);
			_LayoutTabPanel->setSize(ChooserBottomRight - ChooserTopLeft);
	}
	else if(getMFInternalChooserPanels()->size() == 1)
	{
			editMFInternalChooserPanels()->front()->setPosition(ChooserTopLeft);
			editMFInternalChooserPanels()->front()->setSize(ChooserBottomRight - ChooserTopLeft);
	}

}

void ColorChooser::addChooserPanel(AbstractColorChooserPanelRefPtr panel)
{
	MFInternalChooserPanelsType::iterator
        SearchItor(editMFInternalChooserPanels()->find(panel));

	if(SearchItor == editMFInternalChooserPanels()->end())
	{
		panel->installChooserPanel(this);

			pushToInternalChooserPanels(panel);
	}
}

ColorChooser::ColorChooserPanelVector ColorChooser::getChooserPanels(void) const
{
	ColorChooserPanelVector Result;

	for(UInt32 i(0) ; i<getMFInternalChooserPanels()->size() ; ++i)
	{
		Result.push_back(getInternalChooserPanels(i));
	}

	return Result;
}

Color4f ColorChooser::getColor(void) const
{
	if(_SelectionModel != NULL)
	{
		return _SelectionModel->getSelectedColor();
	}
	else
	{
		return Color4f();
	}
}

ColorSelectionModelPtr ColorChooser::getSelectionModel(void)
{
	return _SelectionModel;
}

AbstractColorChooserPanelRefPtr ColorChooser::removeChooserPanel(AbstractColorChooserPanelRefPtr panel)
{
	MFInternalChooserPanelsType::iterator
        SearchItor(editMFInternalChooserPanels()->find(panel));

	if(SearchItor == editMFInternalChooserPanels()->end())
	{
		panel->uninstallChooserPanel(this);

        removeObjFromInternalChooserPanels(panel);

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
	for(UInt32 i(0) ; i<getMFInternalChooserPanels()->size() ; ++i)
	{
		if(std::find(panels.begin(), panels.end(), getInternalChooserPanels(i)) == panels.end())
		{
			RemovalVector.push_back(getInternalChooserPanels(i));
		}
	}
	for(UInt32 i(0) ; i<RemovalVector.size() ; ++i)
	{
		removeChooserPanel(RemovalVector[i]);
	}
}

void ColorChooser::setColor(const Color4f& color)
{
	if(_SelectionModel != NULL)
	{
		_SelectionModel->setSelectedColor(color,false);
	}
}

void ColorChooser::setSelectionModel(ColorSelectionModelPtr newModel)
{
	if(_SelectionModel != NULL)
	{
		_SelectionModel->removeChangeListener(&_ColorSelectedChangeListener);
	}
	_SelectionModel = newModel;
	if(_SelectionModel != NULL)
	{
		_SelectionModel->addChangeListener(&_ColorSelectedChangeListener);
		updateChoosers();
	}
}

void ColorChooser::updateChoosers(void)
{
		_DefaultPreviewPanelBackground->setColor(_SelectionModel->getSelectedColor());

	for(UInt32 i(0) ; i<getMFInternalChooserPanels()->size() ; ++i)
	{
		getInternalChooserPanels(i)->updateChooser();
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
	if(getMFInternalChooserPanels()->size() > 1)
	{
		if(_LayoutTabPanel == NULL)
		{
			_LayoutTabPanel = TabPanel::create();
		}

		_LayoutTabPanel->removeAllTabs();
		LabelRefPtr TabLabel;
		for(UInt32 i(0) ; i<getMFInternalChooserPanels()->size() ; ++i)
		{
			TabLabel = Label::create();
				TabLabel->setText(getInternalChooserPanels(i)->getDisplayText());
				TabLabel->setBorders(NULL);
				TabLabel->setBackgrounds(NULL);

			_LayoutTabPanel->addTab(TabLabel, getInternalChooserPanels(i));
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
	else if(getMFInternalChooserPanels()->size() == 1)
	{
		if(_LayoutTabPanel != NULL)
		{
			_LayoutTabPanel = NULL;
		}

			clearChildren();
			pushToChildren(getMFInternalChooserPanels()->front());
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

    _SelectionModel = ColorSelectionModelPtr(new DefaultColorSelectionModel()),
	_SelectionModel->addChangeListener(&_ColorSelectedChangeListener);

	createDefaultPanel();
	for(UInt32 i(0) ; i<getMFInternalChooserPanels()->size() ; ++i)
	{
        FieldContainerUnrecPtr FCCopy(getInternalChooserPanels(i)->shallowCopy());
		(*editMFInternalChooserPanels())[i] = dynamic_pointer_cast<AbstractColorChooserPanel>(FCCopy);
		getInternalChooserPanels(i)->installChooserPanel(this);
	}
	
	updateChildren();
}

void ColorChooser::onDestroy()
{
    if(_SelectionModel != NULL)
    {
        _SelectionModel->removeChangeListener(&_ColorSelectedChangeListener);
    }
}

/*----------------------- constructors & destructors ----------------------*/

ColorChooser::ColorChooser(void) :
    Inherited(),
		_SelectionModel(),
		_ColorSelectedChangeListener(this),
		_LayoutTabPanel(NULL)
{
}

ColorChooser::ColorChooser(const ColorChooser &source) :
    Inherited(source),
		_SelectionModel(),
		_ColorSelectedChangeListener(this),
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

	if((whichField & PreviewPanelFieldMask) || 
	   (whichField & InternalChooserPanelsFieldMask))
	{
		updateChildren();
	}

	if(whichField & InternalChooserPanelsFieldMask)
	{
		updateChoosers();
	}
}

void ColorChooser::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ColorChooser NI" << std::endl;
}

void ColorChooser::ColorSelectedChangeListener::stateChanged(const ChangeEventUnrecPtr e)
{
	_ColorChooser->updateChoosers();
}

OSG_END_NAMESPACE
