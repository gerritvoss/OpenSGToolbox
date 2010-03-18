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

TableColumnRefPtr TableHeader::columnAtPoint(const Pnt2f& point) const
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
            pushToColumnHeaders(
            _DefaultTableHeaderRenderer->getTableCellRendererComponent(getTable(), getColumnModel()->getColumn(i)->getHeaderValue(), isSelected, false, 0, i)
            );
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

void TableHeader::mouseExited(const MouseEventUnrecPtr e)
{
    if(getResizingAllowed())
    {
        checkMouseMargins(e);
    }
    Inherited::mouseExited(e);
}

void TableHeader::mousePressed(const MouseEventUnrecPtr e)
{
    if(getResizingAllowed())
    {
		Pnt2f MousePosInComponent = ViewportToComponent(e->getLocation(), TableHeaderRefPtr(this), e->getViewport());
        UInt32 CumulativeHeaderWidth(0);
        for(UInt32 i(0) ; i<getMFColumnHeaders()->size() ; ++i)
        {
            CumulativeHeaderWidth += getColumnHeaders(i)->getSize().x();
            if(MousePosInComponent.x() >= CumulativeHeaderWidth - getResizingCursorDriftAllowance() &&
               MousePosInComponent.x() <= CumulativeHeaderWidth + getColumnModel()->getColumnMargin() + getResizingCursorDriftAllowance())
            {
                getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseMotionListener(&(_MarginDraggedListener));
                getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseListener(&(_MarginDraggedListener));
                _ResizingColumn = i;
                return;
            }
            CumulativeHeaderWidth += getColumnModel()->getColumnMargin();
        }
    }
    Inherited::mousePressed(e);
}

void TableHeader::mouseMoved(const MouseEventUnrecPtr e)
{
    if(getResizingAllowed())
    {
        checkMouseMargins(e);
    }
    Inherited::mouseMoved(e);
}

void TableHeader::checkMouseMargins(const MouseEventUnrecPtr e)
{
    if(isContainedClipBounds(e->getLocation(), TableHeaderRefPtr(this)))
    {
		Pnt2f MousePosInComponent = ViewportToComponent(e->getLocation(), TableHeaderRefPtr(this), e->getViewport());
        UInt32 CumulativeHeaderWidth(0);
        for(UInt32 i(0) ; i<getMFColumnHeaders()->size() ; ++i)
        {
            CumulativeHeaderWidth += getColumnHeaders(i)->getSize().x();
            if(MousePosInComponent.x() >= CumulativeHeaderWidth - getResizingCursorDriftAllowance() &&
               MousePosInComponent.x() <= CumulativeHeaderWidth + getColumnModel()->getColumnMargin() + getResizingCursorDriftAllowance())
            {
                getParentWindow()->getDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_RESIZE_W_TO_E);
                return;
            }
            CumulativeHeaderWidth += getColumnModel()->getColumnMargin();
        }
    }
    getParentWindow()->getDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_POINTER);
}

void TableHeader::detachFromEventProducer(void)
{
    Inherited::detachFromEventProducer();
    _MarginDraggedListener.disconnect();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void TableHeader::onCreate(const TableHeader * Id)
{
	Inherited::onCreate(Id);

    if(getColumnModel() != NULL)
    {
        getColumnModel()->addColumnModelListener(&_ColumnModelListener);
    }
}

void TableHeader::onDestroy()
{
    if(getColumnModel() != NULL)
    {
        getColumnModel()->removeColumnModelListener(&_ColumnModelListener);
    }
}

/*----------------------- constructors & destructors ----------------------*/

TableHeader::TableHeader(void) :
    Inherited(),
    _ColumnModelListener(this),
    _MarginDraggedListener(this)

{
}

TableHeader::TableHeader(const TableHeader &source) :
    Inherited(source),
    _DefaultTableHeaderRenderer(source._DefaultTableHeaderRenderer),
    _ColumnModelListener(this),
    _MarginDraggedListener(this)

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

    if(whichField & ColumnModelFieldMask)
    {
        //if(_ColumnModel.get() != NULL)
        //{
        //    getColumnModel()->removeColumnModelListener(&_ColumnModelListener);
        //}
        //_ColumnModel = columnModel;
        updateColumnHeadersComponents();
        if(getColumnModel() != NULL)
        {
            getColumnModel()->addColumnModelListener(&_ColumnModelListener);
        }
    }
}

void TableHeader::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TableHeader NI" << std::endl;
}
		
void TableHeader::ColumnModelListener::columnAdded(const TableColumnModelEventUnrecPtr e)
{
    //Update the ComponentRefPtr vector of the headers
    _TableHeader->updateColumnHeadersComponents();
}

void TableHeader::ColumnModelListener::columnMarginChanged(const ChangeEventUnrecPtr e)
{
    //This will require a layout update
    _TableHeader->updateLayout();
}

void TableHeader::ColumnModelListener::columnMoved(const TableColumnModelEventUnrecPtr e)
{
    //Update the ComponentRefPtr vector of the headers
    _TableHeader->updateColumnHeadersComponents();
}

void TableHeader::ColumnModelListener::columnRemoved(const TableColumnModelEventUnrecPtr e)
{
    //Update the ComponentRefPtr vector of the headers
    _TableHeader->updateColumnHeadersComponents();
}

void TableHeader::ColumnModelListener::columnSelectionChanged(const ListSelectionEventUnrecPtr e)
{
    _TableHeader->updateColumnHeadersComponents();
}

void TableHeader::MarginDraggedListener::mouseMoved(const MouseEventUnrecPtr e)
{
    //Do nothing
}

void TableHeader::MarginDraggedListener::mouseDragged(const MouseEventUnrecPtr e)
{
	if(e->getButton() == e->BUTTON1)
	{
		Pnt2f MousePosInComponent = ViewportToComponent(e->getLocation(), TableHeaderRefPtr(_TableHeader), e->getViewport());


        TableColumnRefPtr TheColumn(_TableHeader->getColumnModel()->getColumn(_TableHeader->_ResizingColumn));
        Real32 NewWidth(MousePosInComponent.x() - _TableHeader->getColumnHeaders(_TableHeader->_ResizingColumn)->getPosition().x());

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
        _TableHeader->updateLayout();
	}
}

void TableHeader::MarginDraggedListener::mouseClicked(const MouseEventUnrecPtr e)
{
    //Do nothing
}

void TableHeader::MarginDraggedListener::mouseEntered(const MouseEventUnrecPtr e)
{
    //Do nothing
}

void TableHeader::MarginDraggedListener::mouseExited(const MouseEventUnrecPtr e)
{
    //Do nothing
}

void TableHeader::MarginDraggedListener::mousePressed(const MouseEventUnrecPtr e)
{
    //Do nothing
}

void TableHeader::MarginDraggedListener::mouseReleased(const MouseEventUnrecPtr e)
{
	if(_TableHeader->getParentWindow() != NULL)
	{
        disconnect();
	}
}

void TableHeader::MarginDraggedListener::disconnect(void)
{
    _TableHeader->_ResizingColumn = -1;
    _TableHeader->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(&(_TableHeader->_MarginDraggedListener));
    _TableHeader->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseListener(&(_TableHeader->_MarginDraggedListener));
}

OSG_END_NAMESPACE
