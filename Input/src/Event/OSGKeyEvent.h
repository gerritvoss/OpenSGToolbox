/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   contact: dkabala@vrac.iastate.edu                                       *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
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
#ifndef _OSGKEYEVENT_H_
#define _OSGKEYEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"

#include "Event/OSGInputEvent.h"

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGWindow.h>

OSG_BEGIN_NAMESPACE

class OSG_INPUTLIB_DLLMAPPING KeyEvent : public InputEvent
{
  /*=========================  PUBLIC  ===============================*/
  public:
     enum KeyModifiers { KEY_MODIFIER_SHIFT=1, KEY_MODIFIER_CONTROL=2, KEY_MODIFIER_ALT=4, KEY_MODIFIER_META=8, KEY_MODIFIER_CAPS_LOCK=16, KEY_MODIFIER_NUM_LOCK=32, KEY_MODIFIER_SCROLL_LOCK=64 };
     enum Key
      {
         KEY_0,
         KEY_1,
         KEY_2,
         KEY_3,
         KEY_4,
         KEY_5,
         KEY_6,
         KEY_7,
         KEY_8,
         KEY_9,
         KEY_ALT,
         KEY_ADD,
         KEY_AMPERSAND,
         KEY_APOSTROPHE,
         KEY_ASTERISK,
         KEY_AT,
         KEY_BACK_QUOTE,
         KEY_BACK_SLASH,
         KEY_BACK_SPACE,
         KEY_BRACE_LEFT,
         KEY_BRACE_RIGHT,
         KEY_CANCEL,
         KEY_CAPS_LOCK,
         KEY_CIRCUMFLEX,
         KEY_CLEAR,
         KEY_CLOSE_BRACKET,
         KEY_COLON,
         KEY_COMMA,
         KEY_CONTROL,
         KEY_COPY,
         KEY_CUT,
         KEY_DECIMAL,
         KEY_DELETE,
         KEY_DIVIDE,
         KEY_DOLLAR,
         KEY_DOWN,
         KEY_END,
         KEY_ENTER,
         KEY_EQUALS,
         KEY_ESCAPE,
         KEY_EXCLAMATION_MARK,
         KEY_F1,
         KEY_F2,
         KEY_F3,
         KEY_F4,
         KEY_F5,
         KEY_F6,
         KEY_F7,
         KEY_F8,
         KEY_F9,
         KEY_F10,
         KEY_F11,
         KEY_F12,
         KEY_F13,
         KEY_F14,
         KEY_F15,
         KEY_F16,
         KEY_F17,
         KEY_F18,
         KEY_F19,
         KEY_F20,
         KEY_F21,
         KEY_F22,
         KEY_F23,
         KEY_F24,
         KEY_FIND,
         KEY_GREATER,
         KEY_HELP,
         KEY_HOME,
         KEY_INSERT,
         KEY_INVERTED_EXCLAMATION_MARK,
         KEY_KEYPAD_UP,
         KEY_KEYPAD_DOWN,
         KEY_KEYPAD_LEFT,
         KEY_KEYPAD_RIGHT,
         KEY_LEFT,
         KEY_LEFT_PARENTHESIS,
         KEY_LESS,
         KEY_MENU,
         KEY_META,
         KEY_MINUS,
         KEY_MULTIPLY,
         KEY_NONE,
         KEY_NUM_LOCK,
         KEY_NUMBER_SIGN,
         KEY_NUMPAD_0,
         KEY_NUMPAD_1,
         KEY_NUMPAD_2,
         KEY_NUMPAD_3,
         KEY_NUMPAD_4,
         KEY_NUMPAD_5,
         KEY_NUMPAD_6,
         KEY_NUMPAD_7,
         KEY_NUMPAD_8,
         KEY_NUMPAD_9,
         KEY_NUMPAD_EQUALS,
         KEY_OPEN_BRACKET,
         KEY_PAGE_DOWN,
         KEY_PAGE_UP,
         KEY_PASTE,
         KEY_PAUSE,
         KEY_PERIOD,
         KEY_PERCENT,
         KEY_PIPE,
         KEY_PLUS,
         KEY_PRINTSCREEN,
         KEY_QUOTE,
         KEY_QUESTION_MARK,
         KEY_RIGHT,
         KEY_RIGHT_PARENTHESIS,
         KEY_SCROLL_LOCK,
         KEY_SEMICOLON,
         KEY_SHIFT,
         KEY_SLASH,
         KEY_SPACE,
         KEY_STOP,
         KEY_SUBTRACT,
         KEY_TAB,
         KEY_TILDE,
         KEY_UNDEFINED,
         KEY_UNDERSCORE,
         KEY_UNDO,
         KEY_UNKNOWN,
         KEY_UP,
         KEY_A,
         KEY_B,
         KEY_C,
         KEY_D,
         KEY_E,
         KEY_F,
         KEY_G,
         KEY_H,
         KEY_I,
         KEY_J,
         KEY_K,
         KEY_L,
         KEY_M,
         KEY_N,
         KEY_O,
         KEY_P,
         KEY_Q,
         KEY_R,
         KEY_S,
         KEY_T,
         KEY_U,
         KEY_V,
         KEY_W,
         KEY_X,
         KEY_Y,
         KEY_Z
      };
	  enum KeyState
      {
		  KEY_STATE_UP,
		  KEY_STATE_DOWN,
		  KEY_STATE_TOGGLED
	  };

    struct ModifiedKey
    {
    public:
        Key _Key;
        UInt32 _Modifiers;

        UInt64 getHashable(void) const;
    };

	Key getKey(void) const;
    static UInt64 getHashable(Key TheKey, UInt32 Modifiers);
	static UChar8 getUpperLetterKey(Key k, UInt32 Modifier);
	static UChar8 getLowerLetterKey(Key k, UInt32 Modifier);
	static UChar8 getNonLetterKey(Key k, UInt32 Modifier);
	static UChar8 getCharFromKey(Key k, UInt32 Modifier);
    static std::string getStringFromKey(Key k, UInt32 Modifier);
    static std::string getStringFromNonDisplayedKey(Key k, UInt32 Modifier);
	UInt32 getModifiers(void) const;
	UChar8 getKeyChar(void) const;

    WindowPtr getWindow(void) const;
    KeyEvent(FieldContainerPtr Source, Time TimeStamp, WindowEventProducerPtr Producer, Key TheKey, UInt32 Modifiers, WindowPtr TheWindow);
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);

  protected:
     Key _Key;
     UInt32 _Modifiers;
     WindowPtr _Window;
     
  private:
     static EventType _Type;
};

OSG_END_NAMESPACE

#include "OSGKeyEvent.inl"

#endif /* _OSGKEYEVENT_H_ */
