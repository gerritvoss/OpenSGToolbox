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

void List::focusGained(const FocusEvent& e)
{

}

void List::focusLost(const FocusEvent& e)
{
}

void List::setModel(ListModel* Model)
{
	beginEditCP(ListPtr(this), ChildrenFieldMask);
		getChildren().clear();
	endEditCP(ListPtr(this), ChildrenFieldMask);
	//Should through a ListDataEvent of removeInterval

	_Model = Model;
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
					getChildren().addValue(getCellGenerator()->getListCellGeneratorComponent(ListPtr(this),getModel()->getElementAt(i),i,false,false));
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

