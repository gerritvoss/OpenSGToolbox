/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Dynamics                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#define OSG_COMPILEDYNAMICSLIB

#include <OpenSG/OSGConfig.h>

#include "OSGFunctionComponentPanel.h"
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/UserInterface//OSGUIDrawUtils.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FunctionComponentPanel
A User Interface Panel that contains Function Components. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FunctionComponentPanel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void FunctionComponentPanel::updateLayout(void)
{
    //Do Nothing
}

void FunctionComponentPanel::mousePressed(const MouseEvent& e)
{
    if(getParentWindow() != NullFC && getParentWindow()->getDrawingSurface()!=NullFC&& getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC &&
        getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
    {
		
		bool isContained(false);
		for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
		{
			isContained = getChildren()[i]->isContained(e.getLocation(), true);
			if(isContained)
			{
				//Set The Active Component
				_ComponentMoveListener.setActiveComponent(getChildren()[i]);
				//Set the Initial Position
				_ComponentMoveListener.setInitialPosition(e.getLocation());
				
				//Attach Listeners
				getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseListener(&_ComponentMoveListener);
				getParentWindow()->getDrawingSurface()->getEventProducer()->addKeyListener(&_ComponentMoveListener);
				getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseMotionListener(&_ComponentMoveListener);
			}
		}
    }
    else
    {
        Inherited::mousePressed(e);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FunctionComponentPanel::FunctionComponentPanel(void) :
    Inherited(),
        _ComponentMoveListener(FunctionComponentPanelPtr(this))
{
}

FunctionComponentPanel::FunctionComponentPanel(const FunctionComponentPanel &source) :
    Inherited(source),
        _ComponentMoveListener(FunctionComponentPanelPtr(this))
{
}

FunctionComponentPanel::~FunctionComponentPanel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FunctionComponentPanel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & ChildrenFieldMask)
    {
        for(UInt32 i(0) ; i<getChildren().size() ; ++i)
        {
            beginEditCP(getChildren()[i], Component::PositionFieldMask | Component::SizeFieldMask);
                getChildren()[i]->setPosition(Pnt2f(0.0f,0.0f));
                getChildren()[i]->setSize(getChildren()[i]->getRequestedSize());
            endEditCP(getChildren()[i], Component::PositionFieldMask | Component::SizeFieldMask);
        }
    }
}

void FunctionComponentPanel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FunctionComponentPanel NI" << std::endl;
}


void FunctionComponentPanel::ComponentMoveListener::mouseReleased(const MouseEvent& e)
{
	detach();
}

void FunctionComponentPanel::ComponentMoveListener::keyPressed(const KeyEvent& e)
{
    //TODO:Implement
	if(e.getKey() == KeyEvent::KEY_ESCAPE)
	{
		detach();
		
		//Set the Active Component's Position back to it's initial position
	}
}

void FunctionComponentPanel::ComponentMoveListener::mouseDragged(const MouseEvent& e)
{
    //TODO:Implement
	//Move the Position of the Component based on the mouse position and it's initial position
}

void FunctionComponentPanel::ComponentMoveListener::detach(void)
{
    if(_FunctionComponentPanel->getParentWindow() != NullFC && _FunctionComponentPanel->getParentWindow()->getDrawingSurface()!=NullFC&& _FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
    {
		_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseListener(this);
		_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->removeKeyListener(this);
		_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(this);
    }
}

void FunctionComponentPanel::ComponentMoveListener::setActiveComponent(ComponentPtr TheComponent)
{
	_ActiveComponent = TheComponent;
	if(_ActiveComponent != NullFC)
	{
		_InitialComponentPosition = _ActiveComponent->getPosition();
	}
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
    static Char8 cvsid_hpp       [] = OSGFUNCTIONCOMPONENTPANELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFUNCTIONCOMPONENTPANELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFUNCTIONCOMPONENTPANELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

