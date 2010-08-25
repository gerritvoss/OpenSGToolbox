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

#include "OSGDefaultTreeCellEditor.h"
#include "OSGTree.h"
#include "OSGTextField.h"
#include "OSGStringUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDefaultTreeCellEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGDefaultTreeCellEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultTreeCellEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentTransitPtr DefaultTreeCellEditor::getTreeCellEditorComponent(Tree* const TheTree, const boost::any& Value, bool IsSelected, bool IsExpanded, UInt32 row)
{
    _EditingValue = Value;

    if(_EditingValue.empty()){
        return ComponentTransitPtr(NULL);
    }

    if(_EditingValue.type() == typeid(std::string))
    {
        //Use String Text Field As Editing Component
        std::string tempString;
        try
        {
            tempString = lexical_cast(_EditingValue);
        }
        catch (boost::bad_lexical_cast &)
        {
            //Could not convert to string
        }
        getDefaultStringEditor()->setText(tempString);
        getDefaultStringEditor()->selectAll();
        getDefaultStringEditor()->setCaretPosition(getDefaultStringEditor()->getText().size());

        _EditorActionConnection = getDefaultStringEditor()->connectActionPerformed(boost::bind(&DefaultTreeCellEditor::handleEditorAction, this, _1));
        _EditorFocusLostConnection = getDefaultStringEditor()->connectFocusLost(boost::bind(&DefaultTreeCellEditor::handleEditorFocusLost, this, _1));
        _EditorKeyPressedConnection = getDefaultStringEditor()->connectKeyPressed(boost::bind(&DefaultTreeCellEditor::handleEditorKeyPressed, this, _1));

        return ComponentTransitPtr(getDefaultStringEditor());
    }
    else
    {
        //Use Default Text Field As Editing Component
        std::string tempString;
        getDefaultEditor()->setText(tempString);
        getDefaultEditor()->selectAll();
        getDefaultEditor()->setCaretPosition(getDefaultEditor()->getText().size());

        _EditorActionConnection = getDefaultEditor()->connectActionPerformed(boost::bind(&DefaultTreeCellEditor::handleEditorAction, this, _1));
        _EditorFocusLostConnection = getDefaultEditor()->connectFocusLost(boost::bind(&DefaultTreeCellEditor::handleEditorFocusLost, this, _1));
        _EditorKeyPressedConnection = getDefaultEditor()->connectKeyPressed(boost::bind(&DefaultTreeCellEditor::handleEditorKeyPressed, this, _1));

        return ComponentTransitPtr(getDefaultEditor());
    }
}

ComponentTransitPtr DefaultTreeCellEditor::getCellEditor(const boost::any& Value, bool IsSelected)
{
    return getTreeCellEditorComponent(NULL, Value, IsSelected, false, 0);
}

void DefaultTreeCellEditor::cancelCellEditing(void)
{
    _EditorActionConnection.disconnect();
    _EditorFocusLostConnection.disconnect();
    _EditorKeyPressedConnection.disconnect();

    Inherited::cancelCellEditing();
}

boost::any DefaultTreeCellEditor::getCellEditorValue(void) const
{
    if(_EditingValue.type() == typeid(std::string))
    {
        _EditingValue = boost::any(getDefaultStringEditor()->getText());
    }
    else
    {
        _EditingValue = boost::any();
    }
    return _EditingValue;
}

bool DefaultTreeCellEditor::isCellEditable(EventDetails* const anEvent) const
{
    if(/*anEvent.getType() != MouseEventDetails::getClassType() ||*/
       (anEvent->getType().isDerivedFrom(MouseEventDetails::getClassType()) &&
        dynamic_cast<MouseEventDetails* const>(anEvent)->getClickCount() >= getClickCountToStart()))
    {
        return Inherited::isCellEditable(anEvent);
    }
    else
    {
        return false;
    }
}

bool DefaultTreeCellEditor::shouldSelectCell(EventDetails* const anEvent) const
{
    return Inherited::shouldSelectCell(anEvent);
}

bool DefaultTreeCellEditor::stopCellEditing(void)
{
    _EditorActionConnection.disconnect();
    _EditorFocusLostConnection.disconnect();
    _EditorKeyPressedConnection.disconnect();

    return Inherited::stopCellEditing();
}

ComponentTransitPtr DefaultTreeCellEditor::getComponent(void) const
{
    if(_EditingValue.type() == typeid(std::string))
    {
        return ComponentTransitPtr(getDefaultStringEditor());
    }
    else
    {
        return ComponentTransitPtr(getDefaultEditor());
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultTreeCellEditor::DefaultTreeCellEditor(void) :
    Inherited(),
        _EditingValue(new SFString())
{
}

DefaultTreeCellEditor::DefaultTreeCellEditor(const DefaultTreeCellEditor &source) :
    Inherited(source),
        _EditingValue(new SFString())

{
}

DefaultTreeCellEditor::~DefaultTreeCellEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultTreeCellEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DefaultTreeCellEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DefaultTreeCellEditor NI" << std::endl;
}

void DefaultTreeCellEditor::handleEditorAction(ActionEventDetails* const e)
{
    stopCellEditing();
}

void DefaultTreeCellEditor::handleEditorFocusLost(FocusEventDetails* const e)
{
    stopCellEditing();
}

void DefaultTreeCellEditor::handleEditorKeyPressed(KeyEventDetails* const e)
{
	if(e->getKey() == KeyEventDetails::KEY_ESCAPE ||
		e->getKey() == KeyEventDetails::KEY_CANCEL)
	{
		cancelCellEditing();
	}
}

OSG_END_NAMESPACE
