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

#include "OSGTableColumn.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TableColumn
A UI Table Column.  	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TableColumn::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


EventConnection TableColumn::addFieldChangeListener(FieldChangeListenerPtr Listener)
{
   _FieldChangeListeners.insert(Listener);
   return EventConnection(
       boost::bind(&TableColumn::isFieldChangeListenerAttached, this, Listener),
       boost::bind(&TableColumn::removeFieldChangeListener, this, Listener));
}

void TableColumn::produceFieldChanged(Field* TheField, FieldDescription* TheDescription)
{
    //TODO: Implement
   //const FieldChangeEventPtr TheEvent = FieldChangeEvent::create(TableColumnPtr(this), getSystemTime(), TheField, TheDescription);
   //FieldChangeListenerSet FieldChangeListenerSet(_FieldChangeListeners);
   //for(FieldChangeListenerSetConstItor SetItor(FieldChangeListenerSet.begin()) ; SetItor != FieldChangeListenerSet.end() ; ++SetItor)
   //{
      //(*SetItor)->fieldChanged(TheEvent);
   //}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TableColumn::TableColumn(void) :
    Inherited(),
    _HeaderValue()
{
}

TableColumn::TableColumn(const TableColumn &source) :
    Inherited(source),
    _TableCellRenderer(source._TableCellRenderer),
    _HeaderCellRenderer(source._HeaderCellRenderer),
    _HeaderValue(source._HeaderValue)
{
}

TableColumn::~TableColumn(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TableColumn::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);


    //Produce a FieldChanged Event for each Field that was changed
    for(UInt32 i(0) ; i<getType().getNumFieldDescs() ; ++i)
    {
        if(getType().getFieldDescription(i) != NULL &&
            whichField & getType().getFieldDescription(i)->getFieldMask())
        {
            produceFieldChanged(getField(i), getType().getFieldDescription(i));
        }
    }
}

void TableColumn::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TableColumn NI" << std::endl;
}

OSG_END_NAMESPACE

