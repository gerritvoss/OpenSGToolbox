/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#define OSG_COMPILEINPUTLIB

#include <OpenSG/OSGConfig.h>

#include "OSGKeyEvent.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::KeyEvent

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void KeyEvent::initMethod (void)
{
}

KeyEventPtr      KeyEvent::create(  FieldContainerPtr Source,
                                    Time TimeStamp,
                                    UInt32 TheKey,
                                    UInt32 Modifiers,
                                    WindowPtr TheWindow)
{
    KeyEventPtr TheEvent = KeyEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->setKey(TheKey);
    TheEvent->setModifiers(Modifiers);
    TheEvent->setWindow(TheWindow);

    return TheEvent;
}

std::string KeyEvent::getStringFromKey(UInt32 k, UInt32 Modifier)
{
    UChar8 ResultChar = getCharFromKey(k,Modifier);
    if(ResultChar != 0)
    {
        std::string Result("");
        Result += ResultChar;
		return Result;
    }
    else
    {
        return getStringFromNonDisplayedKey(k,Modifier);
    }
}

std::string KeyEvent::getKeynameStringFromKey(UInt32 k, UInt32 Modifier)
{
    UChar8 ResultChar = getCharFromKey(k,Modifier);
    if(ResultChar != 0)
    {
        std::string Result("");
        Result += ResultChar;
        return Result;
    }
    else
	{
		std::string Result("");
		switch(k)
		{
		case KEY_SPACE : 
			Result = "Space";
			break;
		case KEY_TAB :
			Result = "Tab";
			break;
		default:
			Result = getStringFromNonDisplayedKey(k,Modifier);
		}
        return Result;
    }
}

UInt64 KeyEvent::getHashable(UInt32 TheKey, UInt32 Modifiers)
{
    return (static_cast<UInt64>(Modifiers) << 32) | (static_cast<UInt64>(TheKey));
}

std::string KeyEvent::getStringFromNonDisplayedKey(UInt32 k, UInt32 Modifier)
{
    std::string Result("");

    switch(k)
    {
    case KEY_CANCEL:
        Result = "Cancel";
        break;
    case KEY_CAPS_LOCK:
        Result = "Capital Lock";
        break;
    case KEY_CLEAR:
        Result = "Clear";
        break;
    case KEY_CONTROL:
        Result = "Control";
        break;
    case KEY_COPY:
        Result = "Copy";
        break;
    case KEY_CUT:
        Result = "Cut";
        break;
    case KEY_DELETE:
        Result = "Delete";
        break;
    case KEY_DOWN:
        Result = "Down";
        break;
    case KEY_END:
        Result = "End";
        break;
    case KEY_ENTER:
        Result = "Enter";
        break;
    case KEY_ESCAPE:
        Result = "Escape";
        break;
	case KEY_TAB:
		Result = "Tab";
        break;
	case KEY_SPACE:
		Result = "Space";
        break;

    case KEY_F1:
        Result = "F1";
        break;
    case KEY_F2:
        Result = "F2";
        break;
    case KEY_F3:
        Result = "F3";
        break;
    case KEY_F4:
        Result = "F4";
        break;
    case KEY_F5:
        Result = "F5";
        break;
    case KEY_F6:
        Result = "F6";
        break;
    case KEY_F7:
        Result = "F7";
        break;
    case KEY_F8:
        Result = "F8";
        break;
    case KEY_F9:
        Result = "F9";
        break;
    case KEY_F10:
        Result = "F10";
        break;
    case KEY_F11:
        Result = "F11";
        break;
    case KEY_F12:
        Result = "F12";
        break;
    case KEY_F13:
        Result = "F13";
        break;
    case KEY_F14:
        Result = "F14";
        break;
    case KEY_F15:
        Result = "F15";
        break;
    case KEY_F16:
        Result = "F16";
        break;
    case KEY_F17:
        Result = "F17";
        break;
    case KEY_F18:
        Result = "F18";
        break;
    case KEY_F19:
        Result = "F19";
        break;
    case KEY_F20:
        Result = "F20";
        break;
    case KEY_F21:
        Result = "F21";
        break;
    case KEY_F22:
        Result = "F22";
        break;
    case KEY_F23:
        Result = "F23";
        break;
    case KEY_F24:
        Result = "F24";
        break;
        
    case KEY_FIND:
        Result = "Find";
        break;
    case KEY_HELP:
        Result = "Help";
        break;
    case KEY_HOME:
        Result = "Home";
        break;
    case KEY_INSERT:
        Result = "Insert";
        break;
    case KEY_KEYPAD_UP:
        Result = "Keypad Up";
        break;
    case KEY_KEYPAD_DOWN:
        Result = "Keypad Down";
        break;
    case KEY_KEYPAD_LEFT:
        Result = "Keypad Left";
        break;
    case KEY_KEYPAD_RIGHT:
        Result = "Keypad Right";
        break;
    case KEY_LEFT:
        Result = "Left";
        break;
    case KEY_MENU:
        Result = "Menu";
        break;
    case KEY_META:
        Result = "Meta";
        break;
    case KEY_NUM_LOCK:
        Result = "Number Lock";
        break;
    case KEY_PAGE_DOWN:
        Result = "Page Down";
        break;
    case KEY_PAGE_UP:
        Result = "Page Up";
        break;
    case KEY_PASTE:
        Result = "Paste";
        break;
    case KEY_PAUSE:
        Result = "Pause";
        break;
    case KEY_PRINTSCREEN:
        Result = "Print Screen";
        break;
    case KEY_RIGHT:
        Result = "Right";
        break;
    case KEY_SCROLL_LOCK:
        Result = "Scroll Lock";
        break;
    case KEY_SHIFT:
        Result = "Shift";
        break;
    case KEY_STOP:
        Result = "Stop";
        break;
    case KEY_UNDO:
        Result = "Undo";
        break;
    case KEY_UP:
        Result = "Up";
        break;

    default:
        break;
    }
    return Result;
}

UChar8 KeyEvent::getCharFromKey(UInt32 k, UInt32 Modifier)
{
   if( ((Modifier & KEY_MODIFIER_SHIFT) != KEY_MODIFIER_SHIFT) ^
       ((Modifier & KEY_MODIFIER_CAPS_LOCK) != KEY_MODIFIER_CAPS_LOCK))
   {
      return getUpperLetterKey(k,Modifier);
   }
   else
   {
      return getLowerLetterKey(k,Modifier);
   }
}

UChar8 KeyEvent::getUpperLetterKey(UInt32 k, UInt32 Modifier)
{
   switch(k)
   {
   case KEY_A:
      return 'A';
   case KEY_B:
      return 'B';
   case KEY_C:
      return 'C';
   case KEY_D:
      return 'D';
   case KEY_E:
      return 'E';
   case KEY_F:
      return 'F';
   case KEY_G:
      return 'G';
   case KEY_H:
      return 'H';
   case KEY_I:
      return 'I';
   case KEY_J:
      return 'J';
   case KEY_K:
      return 'K';
   case KEY_L:
      return 'L';
   case KEY_M:
      return 'M';
   case KEY_N:
      return 'N';
   case KEY_O:
      return 'O';
   case KEY_P:
      return 'P';
   case KEY_Q:
      return 'Q';
   case KEY_R:
      return 'R';
   case KEY_S:
      return 'S';
   case KEY_T:
      return 'T';
   case KEY_U:
      return 'U';
   case KEY_V:
      return 'V';
   case KEY_W:
      return 'W';
   case KEY_X:
      return 'X';
   case KEY_Y:
      return 'Y';
   case KEY_Z:
      return 'Z';

   default:
      return getNonLetterKey(k,Modifier);
   }
}

UChar8 KeyEvent::getLowerLetterKey(UInt32 k, UInt32 Modifier)
{
   switch(k)
   {
   case KEY_A:
      return 'a';
   case KEY_B:
      return 'b';
   case KEY_C:
      return 'c';
   case KEY_D:
      return 'd';
   case KEY_E:
      return 'e';
   case KEY_F:
      return 'f';
   case KEY_G:
      return 'g';
   case KEY_H:
      return 'h';
   case KEY_I:
      return 'i';
   case KEY_J:
      return 'j';
   case KEY_K:
      return 'k';
   case KEY_L:
      return 'l';
   case KEY_M:
      return 'm';
   case KEY_N:
      return 'n';
   case KEY_O:
      return 'o';
   case KEY_P:
      return 'p';
   case KEY_Q:
      return 'q';
   case KEY_R:
      return 'r';
   case KEY_S:
      return 's';
   case KEY_T:
      return 't';
   case KEY_U:
      return 'u';
   case KEY_V:
      return 'v';
   case KEY_W:
      return 'w';
   case KEY_X:
      return 'x';
   case KEY_Y:
      return 'y';
   case KEY_Z:
      return 'z';
   default:
      return getNonLetterKey(k,Modifier);
   }
}

UChar8 KeyEvent::getNonLetterKey(UInt32 k, UInt32 Modifier)
{
   switch(k)
   {
   case KEY_NUMPAD_0:
      return '0';
   case KEY_NUMPAD_1:
      return '1';
   case KEY_NUMPAD_2:
      return '2';
   case KEY_NUMPAD_3:
      return '3';
   case KEY_NUMPAD_4:
      return '4';
   case KEY_NUMPAD_5:
      return '5';
   case KEY_NUMPAD_6:
      return '6';
   case KEY_NUMPAD_7:
      return '7';
   case KEY_NUMPAD_8:
      return '8';
   case KEY_NUMPAD_9:
      return '9';
      
   case KEY_SPACE:
      return ' ';
   case KEY_TAB:
      return ' ';
   case KEY_DIVIDE:
      return '/';
   case KEY_MULTIPLY:
      return '*';
   case KEY_SUBTRACT:
      return '-';
   case KEY_DECIMAL:
      return '.';
      
   case KEY_AMPERSAND:
      return '&';
   case KEY_ASTERISK:
      return '*';
   case KEY_AT:
      return '@';
   case KEY_BRACE_LEFT:
      return '{';
   case KEY_BRACE_RIGHT:
      return '}';
   case KEY_CIRCUMFLEX:
      return '^';
   case KEY_COLON:
      return ':';
   case KEY_DOLLAR:
      return '$';
   case KEY_EXCLAMATION_MARK:
      return '!';
   case KEY_GREATER:
      return '>';
   //case KEY_INVERTED_EXCLAMATION_MARK:
      //return '¡';
   case KEY_LEFT_PARENTHESIS:
      return '(';
   case KEY_LESS:
      return '<';
   case KEY_NUMBER_SIGN:
      return '#';
   case KEY_PLUS:
   case KEY_ADD:
      return '+';
   case KEY_QUOTE:
      return '"';
   case KEY_RIGHT_PARENTHESIS:
      return ')';
   case KEY_TILDE:
      return '~';
   case KEY_UNDERSCORE:
      return '_';
   case KEY_PERCENT:
      return '%';
   case KEY_QUESTION_MARK:
      return '?';
   case KEY_PIPE:
      return '|';
   default:
      if((Modifier & KEY_MODIFIER_SHIFT) != KEY_MODIFIER_SHIFT)
      {
         switch(k)
         {
         case KEY_0:
            return '0';
         case KEY_1:
            return '1';
         case KEY_2:
            return '2';
         case KEY_3:
            return '3';
         case KEY_4:
            return '4';
         case KEY_5:
            return '5';
         case KEY_6:
            return '6';
         case KEY_7:
            return '7';
         case KEY_8:
            return '8';
         case KEY_9:
            return '9';
            
         case KEY_APOSTROPHE:
            return '\'';
         case KEY_BACK_QUOTE:
            return '`';
         case KEY_CLOSE_BRACKET:
            return ']';
         case KEY_COMMA:
            return ',';
         case KEY_DECIMAL:
            return '.';
         case KEY_SLASH:
            return '/';
         case KEY_BACK_SLASH:
            return '\\';
         case KEY_EQUALS:
		 case KEY_NUMPAD_EQUALS:
            return '=';
         case KEY_MINUS:
            return '-';
         case KEY_OPEN_BRACKET:
            return '[';
         case KEY_PERIOD:
            return '.';
         case KEY_SEMICOLON:
            return ';';
         default:
            return 0;
         }
      }
      else
      {
         switch(k)
         {
         case KEY_0:
            return ')';
         case KEY_1:
            return '!';
         case KEY_2:
            return '@';
         case KEY_3:
            return '#';
         case KEY_4:
            return '$';
         case KEY_5:
            return '%';
         case KEY_6:
            return '^';
         case KEY_7:
            return '&';
         case KEY_8:
            return '*';
         case KEY_9:
            return '(';
            
         case KEY_APOSTROPHE:
            return '"';
         case KEY_BACK_QUOTE:
            return '~';
         case KEY_CLOSE_BRACKET:
            return '}';
         case KEY_COMMA:
            return '<';
         case KEY_SLASH:
            return '?';
         case KEY_BACK_SLASH:
            return '|';
         case KEY_EQUALS:
            return '+';
         case KEY_MINUS:
            return '_';
         case KEY_OPEN_BRACKET:
            return '{';
         case KEY_PERIOD:
            return '>';
         case KEY_SEMICOLON:
            return ':';
         default:
            return 0;
         }
      }
   }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

KeyEvent::KeyEvent(void) :
    Inherited()
{
}

KeyEvent::KeyEvent(const KeyEvent &source) :
    Inherited(source)
{
}

KeyEvent::~KeyEvent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void KeyEvent::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void KeyEvent::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump KeyEvent NI" << std::endl;
}


OSG_END_NAMESPACE

