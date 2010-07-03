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

#include "OSGDefaultTableCellEditor.h"
#include "OSGColorLayer.h"
#include "OSGLineBorder.h"
#include "OSGEmptyBorder.h"
#include "OSGTextField.h"
#include "OSGStringUtils.h"
#include "OSGTable.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDefaultTableCellEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGDefaultTableCellEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultTableCellEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentTransitPtr DefaultTableCellEditor::getTableCellEditorComponent(Table* const table, const boost::any& value, bool isSelected, UInt32 row, UInt32 column)
{
    if(value.empty()){
        return ComponentTransitPtr(NULL);
    }
    TextFieldRefPtr TheTextField = TextField::create();
    std::string tempString;
    try
    {
        tempString = lexical_cast(value);
    }
    catch (boost::bad_lexical_cast &)
    {
        //Could not convert to string
    }
    TheTextField->setText(tempString);
    TheTextField->setPreferredSize(Vec2f(100,30));
    TheTextField->setAlignment(Vec2f(0.5,0.5));
    TheTextField->selectAll();
    TheTextField->setCaretPosition(TheTextField->getText().size());
    ColorLayerRefPtr tempBackground;
    tempBackground = ColorLayer::create();

    TheTextField->setBackground(tempBackground);

    //if(isSelected){
    //	tempBackground->setColor(Color4f(0.4, 0.4, 1.0, 1.0));
    //}
    //else{
    tempBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
    //}

    LineBorderRefPtr tempBorder;

    tempBorder = LineBorder::create();
    tempBorder->setColor(Color4f(0.0, 0.0, 1.0, 1.0));

    TheTextField->setBorder(tempBorder);

    setDefaultStringEditor(TheTextField);
    getDefaultStringEditor()->addActionListener(&_DefaultStringEditorListener);
    getDefaultStringEditor()->addFocusListener(&_DefaultStringEditorListener);
    getDefaultStringEditor()->addKeyListener(&_DefaultStringEditorListener);
    return ComponentTransitPtr(getDefaultStringEditor());
}

ComponentTransitPtr DefaultTableCellEditor::getCellEditor(const boost::any& Value, bool IsSelected)
{
    return getTableCellEditorComponent(NULL, Value, IsSelected, 0, 0);
}

void DefaultTableCellEditor::cancelCellEditing(void)
{
    if(getDefaultStringEditor() != NULL)
    {
        getDefaultStringEditor()->removeActionListener(&_DefaultStringEditorListener);
        getDefaultStringEditor()->removeFocusListener(&_DefaultStringEditorListener);
        getDefaultStringEditor()->removeKeyListener(&_DefaultStringEditorListener);
    }
    AbstractCellEditor::cancelCellEditing();
    setDefaultStringEditor(NULL);
}

boost::any DefaultTableCellEditor::getCellEditorValue(void) const
{
    _Value = getDefaultStringEditor()->getText();
    return boost::any(_Value);
}

bool DefaultTableCellEditor::isCellEditable(const EventUnrecPtr anEvent) const
{
    if(/*anEvent.getType() != MouseEvent::getClassType() ||*/
       (anEvent->getType().isDerivedFrom(MouseEvent::getClassType()) &&
        dynamic_pointer_cast<MouseEvent>(anEvent)->getClickCount() >= getClickCountToStart()))
    {
        return AbstractCellEditor::isCellEditable(anEvent);
    }
    else
    {
        return false;
    }
}

bool DefaultTableCellEditor::shouldSelectCell(const EventUnrecPtr anEvent) const
{
    return Inherited::shouldSelectCell(anEvent);
}

bool DefaultTableCellEditor::stopCellEditing(void)
{
    if(getDefaultStringEditor() != NULL)
    {
        getDefaultStringEditor()->removeActionListener(&_DefaultStringEditorListener);
        getDefaultStringEditor()->removeFocusListener(&_DefaultStringEditorListener);
        getDefaultStringEditor()->removeKeyListener(&_DefaultStringEditorListener);
    }
    bool Return =  AbstractCellEditor::stopCellEditing();
    setDefaultStringEditor(NULL);
    return Return;
}

void DefaultTableCellEditor::DefaultStringEditorListener::actionPerformed(const ActionEventUnrecPtr e)
{
    _DefaultTableCellEditor->stopCellEditing();
}

void DefaultTableCellEditor::DefaultStringEditorListener::focusGained(const FocusEventUnrecPtr e)
{
    //Do nothing
}

void DefaultTableCellEditor::DefaultStringEditorListener::focusLost(const FocusEventUnrecPtr e)
{
    _DefaultTableCellEditor->stopCellEditing();
}

void DefaultTableCellEditor::DefaultStringEditorListener::keyPressed(const KeyEventUnrecPtr e)
{
    if(e->getKey() == KeyEvent::KEY_ESCAPE ||
       e->getKey() == KeyEvent::KEY_CANCEL)
    {
        _DefaultTableCellEditor->cancelCellEditing();
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultTableCellEditor::DefaultTableCellEditor(void) :
    Inherited(),
        _DefaultStringEditorListener(this),
        _Value()
{
}

DefaultTableCellEditor::DefaultTableCellEditor(const DefaultTableCellEditor &source) :
    Inherited(source),
        _DefaultStringEditorListener(this),
        _Value()
{
}

DefaultTableCellEditor::~DefaultTableCellEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultTableCellEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DefaultTableCellEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DefaultTableCellEditor NI" << std::endl;
}

OSG_END_NAMESPACE
