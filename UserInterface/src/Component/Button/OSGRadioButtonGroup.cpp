#include "OSGRadioButton.h"
#include "OSGRadioButtonGroup.h"
OSG_BEGIN_NAMESPACE

void RadioButtonGroup::addButton(RadioButtonPtr Button)
{
	_Buttons.push_back(Button);
	Button->addButtonSelectedListener(this);
}

void RadioButtonGroup::removeButton(RadioButtonPtr Button)
{
	std::vector<RadioButtonPtr>::iterator ButtonIter = std::find(_Buttons.begin(),_Buttons.end(),Button);
	if(ButtonIter != _Buttons.end())
	{
		_Buttons.erase(ButtonIter);
		Button->removeButtonSelectedListener(this);
	}
}

void RadioButtonGroup::removeButton(UInt32 Index)
{
	std::vector<RadioButtonPtr>::iterator ButtonIter = _Buttons.begin();
	for(Int32 i = 0; i < Index && ButtonIter != _Buttons.end(); i++)
	{
		++ButtonIter;
	}
	if(ButtonIter != _Buttons.end())
	{
		_Buttons.erase(ButtonIter);
		(*ButtonIter)->removeButtonSelectedListener(this);
	}
}
UInt32 RadioButtonGroup::getButtonCount(void) const
{
	return _Buttons.size();
}


bool RadioButtonGroup::isSelected(const RadioButtonPtr Button) const
{
	if(Button == _SelectedButton)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void RadioButtonGroup::setSelected(RadioButtonPtr Button, bool SelectedValue)
{
	beginEditCP(Button, ToggleButton::SelectedFieldMask);
		Button->setSelected(SelectedValue);
	endEditCP(Button, ToggleButton::SelectedFieldMask);
}

void RadioButtonGroup::buttonSelected(const ButtonSelectedEvent& e)
{
	RadioButtonPtr TheButton = RadioButton::Ptr::dcast(e.getSource());
	if(_SelectedButton != TheButton)
	{
		if(_SelectedButton != NullFC)
		{
			_SelectedButton->setSelected(false);
		}
	_SelectedButton = TheButton;
	}
}

void RadioButtonGroup::buttonDeselected(const ButtonSelectedEvent& e)
{
	if(_SelectedButton == RadioButton::Ptr::dcast(e.getSource()))
	{
		_SelectedButton = NullFC;
	}
}


OSG_END_NAMESPACE
