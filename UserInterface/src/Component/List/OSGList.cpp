/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include <OpenSG/OSGConfig.h>

#include "OSGList.h"
#include "Component/OSGFrame.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::List
A UI List. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void List::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void List::selectionChanged(const ListSelectionEvent& e)
{
	beginEditCP(ListPtr(this), ChildrenFieldMask);
		for(UInt32 i(e.getFirstIndex()) ; i<=e.getLastIndex() ; ++i)
		{
			getChildren().setValue(
				getCellGenerator()->getListCellGeneratorComponent(ListPtr(this),getModel()->getElementAt(i),i,getSelectionModel()->isSelectedIndex(i),getChildren().getValue(i)->getFocused())
				,i);
		}
	endEditCP(ListPtr(this), ChildrenFieldMask);
}

void List::focusGained(const FocusEvent& e)
{
	//Find this component
	MFComponentPtr::iterator Child = getChildren().find(Component::Ptr::dcast(e.getSource()));
	if(Child != getChildren().end())
	{
		UInt32 index(0);
		for( ; index< getChildren().size(); ++index)
		{
			if((*Child) == getChildren().getValue(index))
			{
				break;
			}
		}
		(*Child)->removeFocusListener(this);
		beginEditCP(ListPtr(this), ChildrenFieldMask);
			(*Child) = getCellGenerator()->getListCellGeneratorComponent(ListPtr(this),getModel()->getElementAt(index),index,getSelectionModel()->isSelectedIndex(index),true);
		endEditCP(ListPtr(this), ChildrenFieldMask);
		(*Child)->takeFocus();
		(*Child)->addFocusListener(this);
	}
}

void List::focusLost(const FocusEvent& e)
{
	//Find this component
	MFComponentPtr::iterator Child = getChildren().find(Component::Ptr::dcast(e.getSource()));
	if(Child != getChildren().end())
	{
		UInt32 index(0);
		for( ; index< getChildren().size(); ++index)
		{
			if((*Child) == getChildren().getValue(index))
			{
				break;
			}
		}
		(*Child)->removeFocusListener(this);
		beginEditCP(ListPtr(this), ChildrenFieldMask);
			(*Child) = getCellGenerator()->getListCellGeneratorComponent(ListPtr(this),getModel()->getElementAt(index),index,getSelectionModel()->isSelectedIndex(index),false);
		endEditCP(ListPtr(this), ChildrenFieldMask);

		(*Child)->addFocusListener(this);
	}
}

void List::mousePressed(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
		isContained = isPointInComponent(e.getLocation(), getChildren().getValue(i));
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained);
		if(isContained)
		{
			//Give myself temporary focus
			takeFocus(true);
			if(!getChildren().getValue(i)->getType().isDerivedFrom(Container::getClassType()))
			{
				getChildren().getValue(i)->takeFocus();
				if(getParentFrame() != NullFC &&
				   getParentFrame()->getDrawingSurface() != NullFC &&
				   getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC)
				{
					if(getParentFrame()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
					{
						getSelectionModel()->setSelectionInterval(getSelectionModel()->getAnchorSelectionIndex(), i);
					}
					else if(getParentFrame()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
					{
						getSelectionModel()->removeSelectionInterval(i,i);// this toggles the interval
					}
					else
					{
						getSelectionModel()->setSelectionInterval(i,i);
					}
				}
			}
			getChildren().getValue(i)->mousePressed(e);
			break;
		}
    }
	if(isContained)
	{
		//Remove my temporary focus
		giveFocus(NullFC, false);
	}
	else
	{
		//Give myself permanent focus
		takeFocus();
	}
	Component::mousePressed(e);
}

void List::keyTyped(const KeyEvent& e)
{
	bool noFocus = true;
	if (e.getKey() == KeyEvent::KEY_UP || e.getKey() == KeyEvent::KEY_DOWN || e.getKey() == KeyEvent::KEY_ENTER)
	{
		for(Int32 i(getChildren().size()-1) ; i>=0 && noFocus; --i)
		{
			if (getChildren().getValue(i)->getFocused())
			{
				noFocus = false; // this exits the loop
				UInt32 index(0);
				switch (e.getKey())
				{
					case KeyEvent::KEY_UP:
					case KeyEvent::KEY_DOWN:
						if (e.getKey() == KeyEvent::KEY_DOWN)
							index = (i+1) % getChildren().size();
						else
							index = (i-1+getChildren().size()) % getChildren().size();

						getChildren().getValue(index)->takeFocus();
						getSelectionModel()->setLeadSelectionIndex(index);
						if (e.getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
						{
							getSelectionModel()->setSelectionInterval(getSelectionModel()->getAnchorSelectionIndex(), index);
						}
						else
						{
							getSelectionModel()->setAnchorSelectionIndex(index);
						}
						break;
					
					case KeyEvent::KEY_ENTER: 
						if (e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
						{
							getSelectionModel()->removeSelectionInterval(i,i);// this toggles the interval
						}
						else
						{
							getSelectionModel()->setSelectionInterval(i, i);
						}
						break;
					default:
						break;
				}
			}
		}	
		if (noFocus)
		{
			UInt32 index(0);
			if (e.getKey() == KeyEvent::KEY_UP)
			{
				index = getChildren().size() - 1;
				getChildren().getValue(getChildren().size() - 1)->takeFocus();
			}
			else if (e.getKey() == KeyEvent::KEY_DOWN)
			{
				getChildren().getValue(0)->takeFocus();
			}
		}
	}
	Component::keyTyped(e);
}

void List::contentsChanged(ListDataEvent e)
{
	//TODO: Implement
	updateLayout();
}

void List::intervalAdded(ListDataEvent e)
{
	//TODO: Implement
	updateLayout();
}

void List::intervalRemoved(ListDataEvent e)
{
	//TODO: Implement
	updateLayout();
}

void List::setModel(ListModel* Model)
{
	beginEditCP(ListPtr(this), ChildrenFieldMask);
		getChildren().clear();
	endEditCP(ListPtr(this), ChildrenFieldMask);
	//Should through a ListDataEvent of removeInterval

	if(_Model != NULL)
	{
		_Model->removeListDataListener(this);
	}

	_Model = Model;

	if(_Model != NULL)
	{
		_Model->addListDataListener(this);
	}
}


void List::setSelectionModel(ListSelectionModel* SelectionModel)
{
	if(_SelectionModel != NULL)
	{
		_SelectionModel->removeListSelectionListener(this);
	}
   _SelectionModel = SelectionModel;
   
	if(_SelectionModel != NULL)
	{
		_SelectionModel->addListSelectionListener(this);
	}
}

void List::updateLayout(void)
{
    //Update Layout
	if(getModel() != NULL)
	{
		if(getModel()->getSize() != getChildren().size())
		{
			beginEditCP(ListPtr(this), ChildrenFieldMask);
				for(UInt32 i(0) ; i<getModel()->getSize() ; ++i )
				{
					getChildren().addValue(getCellGenerator()->getListCellGeneratorComponent(ListPtr(this),getModel()->getElementAt(i),i,getSelectionModel()->isSelectedIndex(i),false));
					getChildren().getValue(i)->addFocusListener(this);
				}
			endEditCP(ListPtr(this), ChildrenFieldMask);
		}
		Pnt2s Position(0,0);
		for(UInt32 i(0) ; i<getChildren().size() ; ++i )
		{
			beginEditCP(getChildren().getValue(i), PositionFieldMask | SizeFieldMask);
			   getChildren().getValue(i)->setPosition(Position);
			   getChildren().getValue(i)->setSize( Vec2s(getSize().x(), getChildren().getValue(i)->getPreferredSize().y()) );
			endEditCP(getChildren().getValue(i), PositionFieldMask | SizeFieldMask);

			Position[1] += getChildren().getValue(i)->getSize()[1];
		}
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

List::List(void) :
    Inherited(),
		_Model(NULL),
		_CellGenerator(NULL),
		_SelectionModel(NULL)
{
}

List::List(const List &source) :
    Inherited(source),
		_Model(source._Model),
		_CellGenerator(source._CellGenerator),
		_SelectionModel(source._SelectionModel)
{
}

List::~List(void)
{
}

/*----------------------------- class specific ----------------------------*/

void List::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void List::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump List NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGLISTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGLISTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGLISTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

