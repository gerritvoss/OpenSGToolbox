#include "OSGDefaultTableCellEditor.h"

#include "Background/OSGColorUIBackground.h"
#include "Border/OSGLineBorder.h"
#include "Border/OSGEmptyBorder.h"
#include "Component/Text/OSGTextField.h"

#include <OpenSG/Input/OSGMouseEvent.h>

OSG_BEGIN_NAMESPACE

ComponentPtr DefaultTableCellEditor::getTableCellEditorComponent(TablePtr table, SharedFieldPtr value, bool isSelected, UInt32 row, UInt32 column)
{
	if(value == NULL){
		return NullFC;
	}
	TextFieldPtr TheTextField = TextField::create();
	beginEditCP(TheTextField, TextField::TextFieldMask | TextField::PreferredSizeFieldMask | TextField::HorizontalAlignmentFieldMask | TextField::CaretPositionFieldMask);
		std::string tempString;
		if(value->getType() == SFString::getClassType())
		{
			tempString = dynamic_cast<SFString*>(value.get())->getValue();
		}
		else
		{
			value->getValueByStr(tempString);
		}
		TheTextField->setText(tempString);
		TheTextField->setPreferredSize(Vec2s(100,30));
		TheTextField->setHorizontalAlignment(0.5);
		TheTextField->selectAll();
		TheTextField->setCaretPosition(TheTextField->getText().size());
	endEditCP(TheTextField, TextField::TextFieldMask | TextField::PreferredSizeFieldMask | TextField::HorizontalAlignmentFieldMask | TextField::CaretPositionFieldMask);
	ColorUIBackgroundPtr tempBackground;
	tempBackground = ColorUIBackground::create();

	beginEditCP(TheTextField, TextField::BackgroundFieldMask);
		TheTextField->setBackground(tempBackground);
	endEditCP(TheTextField, TextField::BackgroundFieldMask);

	beginEditCP(tempBackground, ColorUIBackground::ColorFieldMask);
		//if(isSelected){
		//	tempBackground->setColor(Color4f(0.4, 0.4, 1.0, 1.0));
		//}
		//else{
			tempBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
		//}
	endEditCP(tempBackground, ColorUIBackground::ColorFieldMask);

	LineBorderPtr tempBorder;

	tempBorder = LineBorder::create();
	beginEditCP(tempBorder, LineBorder::ColorFieldMask);
		tempBorder->setColor(Color4f(0.0, 0.0, 1.0, 1.0));
	endEditCP(tempBorder, LineBorder::ColorFieldMask);

	beginEditCP(TheTextField, TextField::BorderFieldMask);
		TheTextField->setBorder(tempBorder);
	endEditCP(TheTextField, TextField::BorderFieldMask);

    _EditingTextField = TheTextField;
    _EditingTextField->addActionListener(this);
    _EditingTextField->addFocusListener(this);
    _EditingTextField->addKeyListener(this);
	return Component::Ptr::dcast(TheTextField);
}

void DefaultTableCellEditor::cancelCellEditing(void)
{
    if(_EditingTextField != NullFC)
    {
        _EditingTextField->removeActionListener(this);
        _EditingTextField->removeFocusListener(this);
        _EditingTextField->removeKeyListener(this);
    }
    AbstractCellEditor::cancelCellEditing();
    _EditingTextField = NullFC;
}

SharedFieldPtr DefaultTableCellEditor::getCellEditorValue(void) const
{
    _Value->setValue(_EditingTextField->getText());
    return SharedFieldPtr(_Value);
}

bool DefaultTableCellEditor::isCellEditable(const Event& anEvent) const
{
    if(/*anEvent.getType() != MouseEvent::getClassType() ||*/
       (anEvent.getType() == MouseEvent::getClassType() &&
        dynamic_cast<const MouseEvent&>(anEvent).getClickCount() >= _ClickCountToStart))
    {
        return AbstractCellEditor::isCellEditable(anEvent);
    }
    else
    {
        return false;
    }
}

bool DefaultTableCellEditor::shouldSelectCell(const Event& anEvent) const
{
    return AbstractCellEditor::shouldSelectCell(anEvent);
}

bool DefaultTableCellEditor::stopCellEditing(void)
{
    if(_EditingTextField != NullFC)
    {
        _EditingTextField->removeActionListener(this);
        _EditingTextField->removeFocusListener(this);
        _EditingTextField->removeKeyListener(this);
    }
    bool Return =  AbstractCellEditor::stopCellEditing();
    _EditingTextField = NullFC;
    return Return;
}

void DefaultTableCellEditor::actionPerformed(const ActionEvent& e)
{
    stopCellEditing();
}

void DefaultTableCellEditor::focusGained(const FocusEvent& e)
{
	//Do nothing
}

void DefaultTableCellEditor::focusLost(const FocusEvent& e)
{
    stopCellEditing();
}

void DefaultTableCellEditor::keyPressed(const KeyEvent& e)
{
	if(e.getKey() == KeyEvent::KEY_ESCAPE ||
		e.getKey() == KeyEvent::KEY_CANCEL)
	{
		cancelCellEditing();
	}
}

OSG_END_NAMESPACE
