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

#include "OSGTableHeader.h"
#include "OSGUIDrawingSurface.h"
#include "OSGInternalWindow.h"
#include "OSGWindowEventProducer.h"
#include "OSGUIDrawUtils.h"

#include "OSGTable.h"

#include "OSGTableHeader.h"
#include "OSGTableColumnModelEventDetails.h"
#include "OSGTableModelEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTableHeaderBase.cpp file.
// To modify it, please change the .fcd file (OSGTableHeader.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TableHeader::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

TableColumn* TableHeader::columnAtPoint(const Pnt2f& point) const
{
    Int32 ColumnIndex = getColumnModel()->getColumnIndexAtX(point.x());
    if(ColumnIndex == -1)
    {
        return NULL;
    }
    else
    {
        return getColumnModel()->getColumn(ColumnIndex);
    }
}

Table* TableHeader::getTable(void) const
{
    return dynamic_cast<Table*> (_sfTable.getValue());
}

void TableHeader::updateColumnHeadersComponents(void)
{
    if(getColumnModel() == NULL) return;

    std::vector<UInt32> SelectedColumns = getColumnModel()->getSelectedColumns();
    std::vector<UInt32>::iterator SearchItor;
    bool isSelected(false);
        clearColumnHeaders();
        for(UInt32 i(0) ; i<getColumnModel()->getColumnCount(); ++i)
        {
            SearchItor = std::find(SelectedColumns.begin(), SelectedColumns.end(), i);
            
            isSelected = (SearchItor != SelectedColumns.end());

            //TODO: Add Column Focusing
            ComponentUnrecPtr NewComp(_DefaultTableHeaderRenderer->getTableCellRendererComponent(getTable(), getColumnModel()->getColumn(i)->getHeaderValue(), isSelected, false, 0, i));
            pushToColumnHeaders(NewComp);
        }

    
        clearChildren();

        //Add all of the Header Components
        for(UInt32 i(0); i<getMFColumnHeaders()->size() ; ++i)
        {
            pushToChildren(getColumnHeaders(i));
        }

        //TODO: Add all of the Margin Components
        
}

void TableHeader::updateLayout(void)
{
	Pnt2f BorderTopLeft, BorderBottomRight;
	getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);
	
    UInt32 CumulativeWidth(0);
    UInt32 Height(0);
    
    //Use the Model to update the position and sizes of the Headers
    for(UInt32 i(0) ; i<getMFColumnHeaders()->size() ; ++i)
    {
        getColumnHeaders(i)->setPosition( Pnt2f(BorderTopLeft.x() + CumulativeWidth, BorderTopLeft.y()) );
        getColumnHeaders(i)->setSize( Vec2f(getColumnModel()->getColumn(i)->getWidth(), getColumnHeaders(i)->getPreferredSize().y()) );

        Height = osgMax<UInt32>(Height, getColumnHeaders(i)->getSize().y());
        CumulativeWidth += getColumnHeaders(i)->getSize().x();

        //Add on the Margin
        if(i != getMFColumnHeaders()->size()-1)
        {
            CumulativeWidth += getColumnModel()->getColumnMargin();
        }
    }
    
    //Use the Model to update the position and sizes of the Margins
    //Update My Preferred Size
	Pnt2f TopLeft, BottomRight;
	getBounds(TopLeft, BottomRight);

    Vec2f NewPreferredSize(CumulativeWidth + (BottomRight.x() - TopLeft.x() - BorderBottomRight.x() + BorderTopLeft.x()),
                               Height + (BottomRight.y() - TopLeft.y() - BorderBottomRight.y() + BorderTopLeft.y()));
    if(NewPreferredSize != getPreferredSize())
    {
            setPreferredSize(NewPreferredSize);
    }
}

void TableHeader::mouseExited(MouseEventDetails* const e)
{
    if(getResizingAllowed())
    {
        checkMouseMargins(e);
    }
    Inherited::mouseExited(e);
}

void TableHeader::mousePressed(MouseEventDetails* const e)
{
    if(getResizingAllowed())
    {
		Pnt2f MousePosInComponent = ViewportToComponent(e->getLocation(), this, e->getViewport());
        UInt32 CumulativeHeaderWidth(0);
        for(UInt32 i(0) ; i<getMFColumnHeaders()->size() ; ++i)
        {
            CumulativeHeaderWidth += getColumnHeaders(i)->getSize().x();
            if(MousePosInComponent.x() >= CumulativeHeaderWidth - getResizingCursorDriftAllowance() &&
               MousePosInComponent.x() <= CumulativeHeaderWidth + getColumnModel()->getColumnMargin() + getResizingCursorDriftAllowance())
            {
                _ColBorderMouseDraggedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseDragged(boost::bind(&TableHeader::handleColBorderMouseDragged, this, _1));
                _ColBorderMouseReleasedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&TableHeader::mouseColBorderMouseReleased, this, _1));
                _ResizingColumn = i;
                return;
            }
            CumulativeHeaderWidth += getColumnModel()->getColumnMargin();
        }
    }
    Inherited::mousePressed(e);
}

void TableHeader::mouseMoved(MouseEventDetails* const e)
{
    if(getResizingAllowed())
    {
        checkMouseMargins(e);
    }
    Inherited::mouseMoved(e);
}

void TableHeader::checkMouseMargins(MouseEventDetails* const e)
{
    if(isContainedClipBounds(e->getLocation(), this))
    {
		Pnt2f MousePosInComponent = ViewportToComponent(e->getLocation(), this, e->getViewport());
        UInt32 CumulativeHeaderWidth(0);
        for(UInt32 i(0) ; i<getMFColumnHeaders()->size() ; ++i)
        {
            CumulativeHeaderWidth += getColumnHeaders(i)->getSize().x();
            if(MousePosInComponent.x() >= CumulativeHeaderWidth - getResizingCursorDriftAllowance() &&
               MousePosInComponent.x() <= CumulativeHeaderWidth + getColumnModel()->getColumnMargin() + getResizingCursorDriftAllowance())
            {
                getParentWindow()->getParentDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_RESIZE_W_TO_E);
                return;
            }
            CumulativeHeaderWidth += getColumnModel()->getColumnMargin();
        }
    }
    getParentWindow()->getParentDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_POINTER);
}

void TableHeader::detachFromEventProducer(void)
{
    Inherited::detachFromEventProducer();
    _ResizingColumn = -1;
    _ColBorderMouseDraggedConnection.disconnect();
    _ColBorderMouseReleasedConnection.disconnect();

}

void TableHeader::setColumnModel(TableColumnModel * const value)
{
    _ColumnAddedConnection.disconnect();
    _ColumnMarginChangedConnection.disconnect();
    _ColumnMovedConnection.disconnect();
    _ColumnRemovedConnection.disconnect();
    _ColumnSelectionChangedConnection.disconnect();

    updateColumnHeadersComponents();
    if(getColumnModel() != NULL)
    {
        _ColumnAddedConnection = getColumnModel()->connectColumnAdded(boost::bind(&TableHeader::handleColumnAdded, this, _1));
        _ColumnMarginChangedConnection = getColumnModel()->connectColumnMarginChanged(boost::bind(&TableHeader::handleColumnMarginChanged, this, _1));
        _ColumnMovedConnection = getColumnModel()->connectColumnMoved(boost::bind(&TableHeader::handleColumnMoved, this, _1));
        _ColumnRemovedConnection = getColumnModel()->connectColumnRemoved(boost::bind(&TableHeader::handleColumnRemoved, this, _1));
        _ColumnSelectionChangedConnection = getColumnModel()->connectColumnSelectionChanged(boost::bind(&TableHeader::handleColumnSelectionChanged, this, _1));
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void TableHeader::onCreate(const TableHeader * Id)
{
	Inherited::onCreate(Id);

    if(getColumnModel() != NULL)
    {
        _ColumnAddedConnection = getColumnModel()->connectColumnAdded(boost::bind(&TableHeader::handleColumnAdded, this, _1));
        _ColumnMarginChangedConnection = getColumnModel()->connectColumnMarginChanged(boost::bind(&TableHeader::handleColumnMarginChanged, this, _1));
        _ColumnMovedConnection = getColumnModel()->connectColumnMoved(boost::bind(&TableHeader::handleColumnMoved, this, _1));
        _ColumnRemovedConnection = getColumnModel()->connectColumnRemoved(boost::bind(&TableHeader::handleColumnRemoved, this, _1));
        _ColumnSelectionChangedConnection = getColumnModel()->connectColumnSelectionChanged(boost::bind(&TableHeader::handleColumnSelectionChanged, this, _1));
    }
}

void TableHeader::onDestroy()
{
    _ColumnAddedConnection.disconnect();
    _ColumnMarginChangedConnection.disconnect();
    _ColumnMovedConnection.disconnect();
    _ColumnRemovedConnection.disconnect();
    _ColumnSelectionChangedConnection.disconnect();
    _ColBorderMouseDraggedConnection.disconnect();
    _ColBorderMouseReleasedConnection.disconnect();
}

/*----------------------- constructors & destructors ----------------------*/

TableHeader::TableHeader(void) :
    Inherited()

{
}

TableHeader::TableHeader(const TableHeader &source) :
    Inherited(source),
    _DefaultTableHeaderRenderer(source._DefaultTableHeaderRenderer)

{
}

TableHeader::~TableHeader(void)
{
}

/*----------------------------- class specific ----------------------------*/


void TableHeader::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TableHeader::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TableHeader NI" << std::endl;
}
		
void TableHeader::handleColumnAdded(TableColumnModelEventDetails* const e)
{
    //Update the Component* vector of the headers
    updateColumnHeadersComponents();
}

void TableHeader::handleColumnMarginChanged(ChangeEventDetails* const e)
{
    //This will require a layout update
    updateLayout();
}

void TableHeader::handleColumnMoved(TableColumnModelEventDetails* const e)
{
    //Update the Component* vector of the headers
    updateColumnHeadersComponents();
}

void TableHeader::handleColumnRemoved(TableColumnModelEventDetails* const e)
{
    //Update the Component* vector of the headers
    updateColumnHeadersComponents();
}

void TableHeader::handleColumnSelectionChanged(ListSelectionEventDetails* const e)
{
    updateColumnHeadersComponents();
}

void TableHeader::handleColBorderMouseDragged(MouseEventDetails* const e)
{
	if(e->getButton() == MouseEventDetails::BUTTON1)
	{
		Pnt2f MousePosInComponent = ViewportToComponent(e->getLocation(), this, e->getViewport());


        TableColumnRefPtr TheColumn(getColumnModel()->getColumn(_ResizingColumn));
        Real32 NewWidth(MousePosInComponent.x() - getColumnHeaders(_ResizingColumn)->getPosition().x());

        if(NewWidth <= 0 || NewWidth < TheColumn->getMinWidth())
        {
            NewWidth = TheColumn->getMinWidth();
        }

        if(NewWidth > TheColumn->getMaxWidth())
        {
            NewWidth = TheColumn->getMaxWidth();
        }
        
		//Get the new desired center for this margin
	    TheColumn->setWidth(NewWidth);
        updateLayout();
	}
}

void TableHeader::mouseColBorderMouseReleased(MouseEventDetails* const e)
{
	if(getParentWindow() != NULL)
	{
        _ResizingColumn = -1;
        _ColBorderMouseDraggedConnection.disconnect();
        _ColBorderMouseReleasedConnection.disconnect();
	}
}

OSG_END_NAMESPACE
