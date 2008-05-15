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

#include "OSGColorChooser.h"
#include "OSGAbstractColorChooserPanel.h"
#include "OSGDefaultColorSelectionModel.h"
#include "Component/Container/OSGTabPanel.h"
#include "Component/Text/OSGLabel.h"
#include "Background/OSGColorUIBackground.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ColorChooser
A UI ColorChooser. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ColorChooser::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void ColorChooser::updateLayout(void)
{
	Pnt2f InsetsTopLeft, InsetsBottomRight;
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

	ComponentPtr PreviewPanel;
	if(getPreviewPanel() != NullFC)
	{
		PreviewPanel = getPreviewPanel();
	}
	else
	{
		PreviewPanel = _DefaultPreviewPanel;
	}
	Pnt2f PreviewTopLeft(InsetsTopLeft.x(), InsetsBottomRight.y()), PreviewBottomRight(InsetsBottomRight);
	PreviewTopLeft.setValues(PreviewTopLeft.x(), InsetsBottomRight.y()-PreviewPanel->getPreferredSize().y());
	beginEditCP(PreviewPanel, Component::PositionFieldMask | Component::SizeFieldMask);
		PreviewPanel->setPosition(PreviewTopLeft);
		PreviewPanel->setSize(PreviewBottomRight - PreviewTopLeft);
	endEditCP(PreviewPanel, Component::PositionFieldMask | Component::SizeFieldMask);

	Pnt2f ChooserTopLeft(InsetsTopLeft),
		  ChooserBottomRight(InsetsBottomRight.x(), PreviewTopLeft.y());
	if(getInternalChooserPanels().size() > 1 &&
		_LayoutTabPanel != NullFC)
	{
		beginEditCP(_LayoutTabPanel, Component::PositionFieldMask | Component::SizeFieldMask);
			_LayoutTabPanel->setPosition(ChooserTopLeft);
			_LayoutTabPanel->setSize(ChooserBottomRight - ChooserTopLeft);
		endEditCP(_LayoutTabPanel, Component::PositionFieldMask | Component::SizeFieldMask);
	}
	else if(getInternalChooserPanels().size() == 1)
	{
		beginEditCP(getInternalChooserPanels().front(), Component::PositionFieldMask | Component::SizeFieldMask);
			getInternalChooserPanels().front()->setPosition(ChooserTopLeft);
			getInternalChooserPanels().front()->setSize(ChooserBottomRight - ChooserTopLeft);
		endEditCP(getInternalChooserPanels().front(), Component::PositionFieldMask | Component::SizeFieldMask);
	}

}

void ColorChooser::addChooserPanel(AbstractColorChooserPanelPtr panel)
{
	MFAbstractColorChooserPanelPtr::iterator SearchItor(getInternalChooserPanels().find(panel));

	if(SearchItor == getInternalChooserPanels().end())
	{
		panel->installChooserPanel(ColorChooserPtr(this));

		beginEditCP(ColorChooserPtr(this), InternalChooserPanelsFieldMask);
			getInternalChooserPanels().push_back(panel);
		endEditCP(ColorChooserPtr(this), InternalChooserPanelsFieldMask);
	}
}

ColorChooser::ColorChooserPanelVector ColorChooser::getChooserPanels(void) const
{
	ColorChooserPanelVector Result;

	for(UInt32 i(0) ; i<getInternalChooserPanels().size() ; ++i)
	{
		Result.push_back(getInternalChooserPanels()[i]);
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

AbstractColorChooserPanelPtr ColorChooser::removeChooserPanel(AbstractColorChooserPanelPtr panel)
{
	MFAbstractColorChooserPanelPtr::iterator SearchItor(getInternalChooserPanels().find(panel));

	if(SearchItor != getInternalChooserPanels().end())
	{
		panel->uninstallChooserPanel(ColorChooserPtr(this));

		beginEditCP(ColorChooserPtr(this), InternalChooserPanelsFieldMask);
			getInternalChooserPanels().erase(SearchItor);
		endEditCP(ColorChooserPtr(this), InternalChooserPanelsFieldMask);

		return panel;
	}
	else
	{
		return NullFC;
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
	for(UInt32 i(0) ; i<getInternalChooserPanels().size() ; ++i)
	{
		if(std::find(panels.begin(), panels.end(), getInternalChooserPanels()[i]) == panels.end())
		{
			RemovalVector.push_back(getInternalChooserPanels()[i]);
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
		_SelectionModel->setSelectedColor(color);
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
	beginEditCP(_DefaultPreviewPanelBackground, ColorUIBackground::ColorFieldMask);
		_DefaultPreviewPanelBackground->setColor(_SelectionModel->getSelectedColor());
	endEditCP(_DefaultPreviewPanelBackground, ColorUIBackground::ColorFieldMask);

	for(UInt32 i(0) ; i<getInternalChooserPanels().size() ; ++i)
	{
		getInternalChooserPanels()[i]->updateChooser();
	}
}

void ColorChooser::createDefaultPanel(void)
{
	_DefaultPreviewPanelBackground = ColorUIBackground::create();

	_DefaultPreviewPanel = Label::create();
	beginEditCP(_DefaultPreviewPanel, Label::BordersFieldMask | Label::BackgroundsFieldMask | Label::PreferredSizeFieldMask);
		_DefaultPreviewPanel->setPreferredSize(Vec2f(50.0f,50.0f));
		_DefaultPreviewPanel->setBorders(NullFC);
		_DefaultPreviewPanel->setBackgrounds(_DefaultPreviewPanelBackground);
	endEditCP(_DefaultPreviewPanel, Label::BordersFieldMask | Label::BackgroundsFieldMask | Label::PreferredSizeFieldMask);

}

void ColorChooser::updateChildren(void)
{
	if(getInternalChooserPanels().size() > 1)
	{
		if(_LayoutTabPanel == NullFC)
		{
			_LayoutTabPanel = TabPanel::create();
			addRefCP(_LayoutTabPanel);
		}

		_LayoutTabPanel->removeAllTabs();
		LabelPtr TabLabel;
		for(UInt32 i(0) ; i<getInternalChooserPanels().size() ; ++i)
		{
			TabLabel = Label::create();
			beginEditCP(TabLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
				TabLabel->setText(getInternalChooserPanels()[i]->getDisplayText());
				TabLabel->setBorders(NullFC);
				TabLabel->setBackgrounds(NullFC);
			endEditCP(TabLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);

			_LayoutTabPanel->addTab(TabLabel, getInternalChooserPanels()[i]);
		}

        _LayoutTabPanel->setSelectedIndex(0);

		beginEditCP(ColorChooserPtr(this), ColorChooser::ChildrenFieldMask);
			getChildren().clear();
			getChildren().push_back(_LayoutTabPanel);
			if(getPreviewPanel() != NullFC)
			{
				getChildren().push_back(getPreviewPanel());
			}
			else
			{
				getChildren().push_back(_DefaultPreviewPanel);
			}
		endEditCP(ColorChooserPtr(this), ColorChooser::ChildrenFieldMask);
	}
	else if(getInternalChooserPanels().size() == 1)
	{
		if(_LayoutTabPanel != NullFC)
		{
			subRefCP(_LayoutTabPanel);
			_LayoutTabPanel = NullFC;
		}

		beginEditCP(ColorChooserPtr(this), ColorChooser::ChildrenFieldMask);
			getChildren().clear();
			getChildren().push_back(getInternalChooserPanels().front());
			if(getPreviewPanel() != NullFC)
			{
				getChildren().push_back(getPreviewPanel());
			}
			else
			{
				getChildren().push_back(_DefaultPreviewPanel);
			}
		endEditCP(ColorChooserPtr(this), ColorChooser::ChildrenFieldMask);
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ColorChooser::ColorChooser(void) :
    Inherited(),
		_SelectionModel(new DefaultColorSelectionModel()),
		_ColorSelectedChangeListener(ColorChooserPtr(this)),
		_LayoutTabPanel(NullFC)
{
	_SelectionModel->addChangeListener(&_ColorSelectedChangeListener);
	createDefaultPanel();
}

ColorChooser::ColorChooser(const ColorChooser &source) :
    Inherited(source),
		_SelectionModel(new DefaultColorSelectionModel()),
		_ColorSelectedChangeListener(ColorChooserPtr(this)),
		_LayoutTabPanel(NullFC)
{
	_SelectionModel->addChangeListener(&_ColorSelectedChangeListener);
	createDefaultPanel();
	for(UInt32 i(0) ; i<getInternalChooserPanels().size() ; ++i)
	{
		getInternalChooserPanels()[i] = AbstractColorChooserPanel::Ptr::dcast(getInternalChooserPanels()[i]->shallowCopy());
		getInternalChooserPanels()[i]->installChooserPanel(ColorChooserPtr(this));
	}
	
	updateChildren();
}

ColorChooser::~ColorChooser(void)
{
	_SelectionModel->removeChangeListener(&_ColorSelectedChangeListener);
}

/*----------------------------- class specific ----------------------------*/

void ColorChooser::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

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


void ColorChooser::ColorSelectedChangeListener::stateChanged(const ChangeEvent& e)
{
	_ColorChooser->updateChoosers();
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
    static Char8 cvsid_hpp       [] = OSGCOLORCHOOSERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCOLORCHOOSERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCOLORCHOOSERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

