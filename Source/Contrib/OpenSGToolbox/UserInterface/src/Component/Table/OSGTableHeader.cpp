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
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include "Component/Container/Window/OSGInternalWindow.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include "Util/OSGUIDrawUtils.h"

#include "OSGTable.h"

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

TableColumnPtr TableHeader::columnAtPoint(const Pnt2f& point) const
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



void TableHeader::updateColumnHeadersComponents(void)
{
    if(getColumnModel() == NullFC) return;

    std::vector<UInt32> SelectedColumns = getColumnModel()->getSelectedColumns();
    std::vector<UInt32>::iterator SearchItor;
    bool isSelected(false);
    beginEditCP(TableHeaderPtr(this) , ColumnHeadersFieldMask);
        getColumnHeaders().clear();
        for(UInt32 i(0) ; i<getColumnModel()->getColumnCount(); ++i)
        {
            SearchItor = std::find(SelectedColumns.begin(), SelectedColumns.end(), i);
            
            isSelected = (SearchItor != SelectedColumns.end());

            //TODO: Add Column Focusing
            getColumnHeaders().push_back(
            _DefaultTableHeaderRenderer->getTableCellRendererComponent(getTable(), getColumnModel()->getColumn(i)->getHeaderValue(), isSelected, false, 0, i)
            );
        }
    endEditCP(TableHeaderPtr(this) , ColumnHeadersFieldMask);

    
    beginEditCP(TableHeaderPtr(this) , ChildrenFieldMask);
        getChildren().clear();

        //Add all of the Header Components
        for(UInt32 i(0); i<getColumnHeaders().size() ; ++i)
        {
            getChildren().push_back(getColumnHeaders()[i]);
        }

        //TODO: Add all of the Margin Components
        
    endEditCP(TableHeaderPtr(this) , ChildrenFieldMask);
}

void TableHeader::updateLayout(void)
{
	Pnt2f BorderTopLeft, BorderBottomRight;
	getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);
	
    UInt32 CumulativeWidth(0);
    UInt32 Height(0);
    
    //Use the Model to update the position and sizes of the Headers
    for(UInt32 i(0) ; i<getColumnHeaders().size() ; ++i)
    {
        beginEditCP(getColumnHeaders()[i], PositionFieldMask | SizeFieldMask);
            getColumnHeaders()[i]->setPosition( Pnt2f(BorderTopLeft.x() + CumulativeWidth, BorderTopLeft.y()) );
            getColumnHeaders()[i]->setSize( Vec2f(getColumnModel()->getColumn(i)->getWidth(), getColumnHeaders()[i]->getPreferredSize().y()) );
        endEditCP(getColumnHeaders()[i], PositionFieldMask | SizeFieldMask);

        Height = osgMax<UInt32>(Height, getColumnHeaders()[i]->getSize().y());
        CumulativeWidth += getColumnHeaders()[i]->getSize().x();

        //Add on the Margin
        if(i != getColumnHeaders().size()-1)
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
        beginEditCP(TableHeaderPtr(this), PreferredSizeFieldMask);
            setPreferredSize(NewPreferredSize);
        endEditCP(TableHeaderPtr(this), PreferredSizeFieldMask);
    }
}

void TableHeader::mouseExited(const MouseEventPtr e)
{
    if(getResizingAllowed())
    {
        checkMouseMargins(e);
    }
    Inherited::mouseExited(e);
}

void TableHeader::mousePressed(const MouseEventPtr e)
{
    if(getResizingAllowed())
    {
		Pnt2f MousePosInComponent = ViewportToComponent(e->getLocation(), TableHeaderPtr(this), e->getViewport());
        UInt32 CumulativeHeaderWidth(0);
        for(UInt32 i(0) ; i<getColumnHeaders().size() ; ++i)
        {
            CumulativeHeaderWidth += getColumnHeaders()[i]->getSize().x();
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

void TableHeader::mouseMoved(const MouseEventPtr e)
{
    if(getResizingAllowed())
    {
        checkMouseMargins(e);
    }
    Inherited::mouseMoved(e);
}

void TableHeader::checkMouseMargins(const MouseEventPtr e)
{
    if(isContainedClipBounds(e->getLocation(), TableHeaderPtr(this)))
    {
		Pnt2f MousePosInComponent = ViewportToComponent(e->getLocation(), TableHeaderPtr(this), e->getViewport());
        UInt32 CumulativeHeaderWidth(0);
        for(UInt32 i(0) ; i<getColumnHeaders().size() ; ++i)
        {
            CumulativeHeaderWidth += getColumnHeaders()[i]->getSize().x();
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
    if(getColumnModel() != NullFC)
    {
        getColumnModel()->addColumnModelListener(&_ColumnModelListener);
    }
}

TableHeader::~TableHeader(void)
{
    if(getColumnModel() != NullFC)
    {
        getColumnModel()->removeColumnModelListener(&_ColumnModelListener);
    }
}

/*----------------------------- class specific ----------------------------*/

void TableHeader::changed(BitVector whichField, UInt32 origin)
{   
    Inherited::changed(whichField, origin);

    if(whichField & ColumnModelFieldMask)
    {
        //if(_ColumnModel.get() != NULL)
        //{
        //    getColumnModel()->removeColumnModelListener(&_ColumnModelListener);
        //}
        //_ColumnModel = columnModel;
        updateColumnHeadersComponents();
        if(getColumnModel() != NullFC)
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

/*----------------------------- Embeded Classes ---------------------------*/


		
void TableHeader::ColumnModelListener::columnAdded(const TableColumnModelEventPtr e)
{
    //Update the ComponentPtr vector of the headers
    _TableHeader->updateColumnHeadersComponents();
}

void TableHeader::ColumnModelListener::columnMarginChanged(const ChangeEventPtr e)
{
    //This will require a layout update
    _TableHeader->updateLayout();
}

void TableHeader::ColumnModelListener::columnMoved(const TableColumnModelEventPtr e)
{
    //Update the ComponentPtr vector of the headers
    _TableHeader->updateColumnHeadersComponents();
}

void TableHeader::ColumnModelListener::columnRemoved(const TableColumnModelEventPtr e)
{
    //Update the ComponentPtr vector of the headers
    _TableHeader->updateColumnHeadersComponents();
}

void TableHeader::ColumnModelListener::columnSelectionChanged(const ListSelectionEventPtr e)
{
    _TableHeader->updateColumnHeadersComponents();
}

void TableHeader::MarginDraggedListener::mouseMoved(const MouseEventPtr e)
{
    //Do nothing
}

void TableHeader::MarginDraggedListener::mouseDragged(const MouseEventPtr e)
{
	if(e->getButton() == e->BUTTON1)
	{
		Pnt2f MousePosInComponent = ViewportToComponent(e->getLocation(), TableHeaderPtr(_TableHeader), e->getViewport());


        TableColumnPtr TheColumn(_TableHeader->getColumnModel()->getColumn(_TableHeader->_ResizingColumn));
        Real32 NewWidth(MousePosInComponent.x() - _TableHeader->getColumnHeaders()[_TableHeader->_ResizingColumn]->getPosition().x());

        if(NewWidth <= 0 || NewWidth < TheColumn->getMinWidth())
        {
            NewWidth = TheColumn->getMinWidth();
        }

        if(NewWidth > TheColumn->getMaxWidth())
        {
            NewWidth = TheColumn->getMaxWidth();
        }
        
		//Get the new desired center for this margin
        beginEditCP(TheColumn, TableColumn::WidthFieldMask);
	        TheColumn->setWidth(NewWidth);
        endEditCP(TheColumn, TableColumn::WidthFieldMask);
        _TableHeader->updateLayout();
	}
}

void TableHeader::MarginDraggedListener::mouseClicked(const MouseEventPtr e)
{
    //Do nothing
}

void TableHeader::MarginDraggedListener::mouseEntered(const MouseEventPtr e)
{
    //Do nothing
}

void TableHeader::MarginDraggedListener::mouseExited(const MouseEventPtr e)
{
    //Do nothing
}

void TableHeader::MarginDraggedListener::mousePressed(const MouseEventPtr e)
{
    //Do nothing
}

void TableHeader::MarginDraggedListener::mouseReleased(const MouseEventPtr e)
{
	if(_TableHeader->getParentWindow() != NullFC)
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

