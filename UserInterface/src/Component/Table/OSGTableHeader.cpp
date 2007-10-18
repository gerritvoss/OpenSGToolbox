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

#include "OSGTableHeader.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TableHeader
A UI Table Header. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TableHeader::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

TableColumnPtr TableHeader::columnAtPoint(const Pnt2s& point) const
{

    Int32 ColumnIndex = getColumnModel()->getColumnIndexAtX(point.x());
    if(ColumnIndex == -1)
    {
        return NullFC;
    }
    else
    {
        return getColumnModel()->getColumn(ColumnIndex);
    }
}


void TableHeader::setColumnModel(TableColumnModelPtr columnModel)
{
    if(_ColumnModel.get() != NULL)
    {
        _ColumnModel->removeColumnModelListener(_ColumnModelListener);
    }
    _ColumnModel = columnModel;
    updateColumnHeadersComponents();
    if(_ColumnModel.get() != NULL)
    {
        _ColumnModel->addColumnModelListener(_ColumnModelListener);
    }
}

void TableHeader::updateColumnHeadersComponents(void)
{

    std::vector<UInt32> SelectedColumns = _ColumnModel->getSelectedColumns();
    std::vector<UInt32>::iterator SearchItor;
    bool isSelected(false);
    beginEditCP(TableHeaderPtr(this) , ColumnHeadersFieldMask);
        getColumnHeaders().clear();
        for(UInt32 i(0) ; i<_ColumnModel->getColumnCount(); ++i)
        {
            SearchItor = std::find(SelectedColumns.begin(), SelectedColumns.end(), i);
            
            isSelected = (SearchItor != SelectedColumns.end());

            //TODO: Add Column Focusing
            getColumnHeaders().push_back(
            _DefaultTableHeaderRenderer->getTableCellRendererComponent(getTable(), _ColumnModel->getColumn(i)->getHeaderValue(), isSelected, false, 0, i)
            );
        }
    endEditCP(TableHeaderPtr(this) , ColumnHeadersFieldMask);

    
    //beginEditCP(TableHeaderPtr(this) , ChildrenFieldMask);
        getChildren().clear();

        //Add all of the Header Components
        for(UInt32 i(0); i<getColumnHeaders().size() ; ++i)
        {
            getChildren().push_back(getColumnHeaders()[i]);
        }

        //TODO: Add all of the Margin Components
        
    //endEditCP(TableHeaderPtr(this) , ChildrenFieldMask);
}

void TableHeader::updateLayout(void)
{
    updateColumnHeadersComponents();
	Pnt2s BorderTopLeft, BorderBottomRight;
	getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);
	
    UInt32 CumulativeWidth(0);
    UInt32 Height(0);
    
    //Use the Model to update the position and sizes of the Headers
    for(UInt32 i(0) ; i<getColumnHeaders().size() ; ++i)
    {
        beginEditCP(getColumnHeaders()[i], PositionFieldMask | SizeFieldMask);
            getColumnHeaders()[i]->setPosition( Pnt2s(BorderTopLeft.x() + CumulativeWidth, BorderTopLeft.y()) );
            getColumnHeaders()[i]->setSize( Vec2s(_ColumnModel->getColumn(i)->getWidth(), getColumnHeaders()[i]->getPreferredSize().y()) );
        endEditCP(getColumnHeaders()[i], PositionFieldMask | SizeFieldMask);

        Height = osgMax<UInt32>(Height, getColumnHeaders()[i]->getSize().y());
        CumulativeWidth += getColumnHeaders()[i]->getSize().x();

        //Add on the Margin
        if(i != getColumnHeaders().size()-1)
        {
            CumulativeWidth += _ColumnModel->getColumnMargin();
        }
    }
    
    //Use the Model to update the position and sizes of the Margins
    //Update My Preferred Size
	Pnt2s TopLeft, BottomRight;
	getBounds(TopLeft, BottomRight);

    Vec2s NewPreferredSize(CumulativeWidth + (BottomRight.x() - TopLeft.x() - BorderTopLeft.x() + BorderBottomRight.x()),
                               Height + (BottomRight.y() - TopLeft.y() - BorderTopLeft.y() + BorderBottomRight.y()));
    if(NewPreferredSize != getPreferredSize())
    {
        beginEditCP(TableHeaderPtr(this), PreferredSizeFieldMask);
            setPreferredSize(NewPreferredSize);
        endEditCP(TableHeaderPtr(this), PreferredSizeFieldMask);
    }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TableHeader::TableHeader(void) :
    Inherited(),
    _ColumnModelListener(new ColumnModelListener(this))
{
}

TableHeader::TableHeader(const TableHeader &source) :
    Inherited(source),
    _ColumnModel(source._ColumnModel),
    _DefaultTableHeaderRenderer(source._DefaultTableHeaderRenderer),
    _ColumnModelListener(new ColumnModelListener(this))
{
    if(_ColumnModel.get() != NULL)
    {
        _ColumnModel->addColumnModelListener(_ColumnModelListener);
    }
}

TableHeader::~TableHeader(void)
{
    if(_ColumnModel.get() != NULL)
    {
        _ColumnModel->removeColumnModelListener(_ColumnModelListener);
    }
}

/*----------------------------- class specific ----------------------------*/

void TableHeader::changed(BitVector whichField, UInt32 origin)
{   
    Inherited::changed(whichField, origin);
}

void TableHeader::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TableHeader NI" << std::endl;
}

/*----------------------------- Embeded Classes ---------------------------*/


		
void TableHeader::ColumnModelListener::columnAdded(const TableColumnModelEvent& e)
{
    //Update the ComponentPtr vector of the headers
    _TableHeader->updateLayout();
}

void TableHeader::ColumnModelListener::columnMarginChanged(const ChangeEvent& e)
{
    //This will require a layout update
    _TableHeader->updateLayout();
}

void TableHeader::ColumnModelListener::columnMoved(const TableColumnModelEvent& e)
{
    //Update the ComponentPtr vector of the headers
    _TableHeader->updateLayout();
}

void TableHeader::ColumnModelListener::columnRemoved(const TableColumnModelEvent& e)
{
    //Update the ComponentPtr vector of the headers
    _TableHeader->updateLayout();
}

void TableHeader::ColumnModelListener::columnSelectionChanged(const ListSelectionEvent& e)
{
    //Do nothing
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
    static Char8 cvsid_hpp       [] = OSGTABLEHEADERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTABLEHEADERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTABLEHEADERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

