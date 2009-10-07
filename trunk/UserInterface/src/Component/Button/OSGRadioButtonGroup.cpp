#include "OSGRadioButton.h"
#include "OSGRadioButtonGroup.h"
OSG_BEGIN_NAMESPACE

void RadioButtonGroup::addButton(RadioButtonPtr Button)
{
	_Buttons.push_back(Button);
    if(Button->getSelected())
    {
        if(_SelectedButton == NullFC)
        {
            _SelectedButton = Button;
        }
        else
        {
            beginEditCP(Button, RadioButton::SelectedFieldMask);
                Button->setSelected(false);
            endEditCP(Button, RadioButton::SelectedFieldMask);
        }
    }
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

void RadioButtonGroup::buttonSelected(const ButtonSelectedEventPtr e)
{
	RadioButtonPtr TheButton = RadioButton::Ptr::dcast(e->getSource());
    RadioButtonPtr PreviousSelected(_SelectedButton);
	if(_SelectedButton != TheButton)
	{
	    _SelectedButton = TheButton;
		if(PreviousSelected != NullFC)
		{
            beginEditCP(PreviousSelected, RadioButton::SelectedFieldMask);
			    PreviousSelected->setSelected(false);
            endEditCP(PreviousSelected, RadioButton::SelectedFieldMask);
		}
	}
}

void RadioButtonGroup::buttonDeselected(const ButtonSelectedEventPtr e)
{
	if(_SelectedButton == RadioButton::Ptr::dcast(e->getSource()))
	{
		_SelectedButton = NullFC;
	}
}


OSG_END_NAMESPACE
