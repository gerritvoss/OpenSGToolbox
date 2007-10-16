#include "OSGDefaultTableCellEditor.h"

#include "Background/OSGColorUIBackground.h"
#include "Border/OSGLineBorder.h"
#include "Border/OSGEmptyBorder.h"
#include "Component/Text/OSGTextField.h"

OSG_BEGIN_NAMESPACE

ComponentPtr DefaultTableCellEditor::getTableCellEditorComponent(TablePtr table, Field* value, bool isSelected, UInt32 row, UInt32 column)
{
	if(value == NULL){
		return NullFC;
	}
	TextFieldPtr TheTextField = TextField::create();
	beginEditCP(TheTextField, TextField::TextFieldMask | TextField::PreferredSizeFieldMask);
		std::string tempString;
		if(value->getType() == SFString::getClassType())
		{
			tempString = dynamic_cast<SFString*>(value)->getValue();
		}
		else
		{
			value->getValueByStr(tempString);
		}
		TheTextField->setText(tempString);
		TheTextField->setPreferredSize(Vec2s(100,30));
	endEditCP(TheTextField, TextField::TextFieldMask | TextField::PreferredSizeFieldMask);
	ColorUIBackgroundPtr tempBackground;
	tempBackground = ColorUIBackground::create();

	beginEditCP(TheTextField, TextField::BackgroundFieldMask);
		TheTextField->setBackground(tempBackground);
	endEditCP(TheTextField, TextField::BackgroundFieldMask);

	beginEditCP(tempBackground, ColorUIBackground::ColorFieldMask);
		if(isSelected){
			tempBackground->setColor(Color4f(0.4, 0.4, 1.0, 1.0));
		}
		else{
			tempBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
		}
	endEditCP(tempBackground, ColorUIBackground::ColorFieldMask);

	EmptyBorderPtr tempBorder;

	tempBorder = EmptyBorder::create();
	beginEditCP(TheTextField, TextField::BorderFieldMask);
		TheTextField->setBorder(tempBorder);
	endEditCP(TheTextField, TextField::BorderFieldMask);

	return Component::Ptr::dcast(TheTextField);
}

void DefaultTableCellEditor::cancelCellEditing(void)
{
    //TODO: Implement
    AbstractCellEditor::cancelCellEditing();
}

Field* DefaultTableCellEditor::getCellEditorValue(void) const
{
    //TODO: Implement
    return NULL;
}

bool DefaultTableCellEditor::isCellEditable(const Event& anEvent) const
{
    //TODO: Implement
    return AbstractCellEditor::isCellEditable(anEvent);
}

bool DefaultTableCellEditor::shouldSelectCell(const Event& anEvent) const
{
    //TODO: Implement
    return AbstractCellEditor::shouldSelectCell(anEvent);
}

bool DefaultTableCellEditor::stopCellEditing(void)
{
    //TODO: Implement
    return AbstractCellEditor::stopCellEditing();
}

OSG_END_NAMESPACE
