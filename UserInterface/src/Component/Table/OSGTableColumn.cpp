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

void TableColumn::produceFieldChanged(Field* TheField, FieldDescription* TheDescription)
{
   FieldChangeEvent TheEvent(TableColumnPtr(this), getSystemTime(), TheField, TheDescription);
   FieldChangeListenerSet FieldChangeListenerSet(_FieldChangeListeners);
   for(FieldChangeListenerSetConstItor SetItor(FieldChangeListenerSet.begin()) ; SetItor != FieldChangeListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->fieldChanged(TheEvent);
   }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TableColumn::TableColumn(void) :
    Inherited(),
    _HeaderValue(NULL)
{
}

TableColumn::TableColumn(const TableColumn &source) :
    Inherited(source),
    _TableCellEditor(source._TableCellEditor),
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
        if(whichField & getType().getFieldDescription(i)->getFieldMask())
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
    static Char8 cvsid_hpp       [] = OSGTABLECOLUMNBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTABLECOLUMNBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTABLECOLUMNFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

