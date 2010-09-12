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

#ifndef _OSGKEYEVENTDETAILS_H_
#define _OSGKEYEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGKeyEventDetailsBase.h"


OSG_BEGIN_NAMESPACE

/*! \brief KeyEventDetails class. See \ref
           PageSystemKeyEventDetails for a description.
*/

class OSG_SYSTEM_DLLMAPPING KeyEventDetails : public KeyEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef KeyEventDetailsBase Inherited;
    typedef KeyEventDetails     Self;

     enum KeyModifiers { KEY_MODIFIER_UNKNOWN     = 0,
                         KEY_MODIFIER_SHIFT       = 1,
                         KEY_MODIFIER_CONTROL     = 2,
                         KEY_MODIFIER_ALT         = 4,
                         KEY_MODIFIER_META        = 8,
                         KEY_MODIFIER_CAPS_LOCK   = 16,
                         KEY_MODIFIER_NUM_LOCK    = 32,
                         KEY_MODIFIER_SCROLL_LOCK = 64,
#ifdef __APPLE__
                         KEY_MODIFIER_COMMAND     = KEY_MODIFIER_META
#else
                         KEY_MODIFIER_COMMAND     = KEY_MODIFIER_CONTROL
#endif
     };
     enum Key
      {
         KEY_UNKNOWN = 0,

         KEY_BACK_SPACE = 8,
         KEY_TAB        = 9 ,


         KEY_ESCAPE     = 27 ,

         KEY_SPACE             = 32,
         KEY_EXCLAMATION_MARK  = 33 ,
         KEY_QUOTE             = 34 ,
         KEY_NUMBER_SIGN       = 35 ,
         KEY_DOLLAR            = 36 ,
         KEY_PERCENT           = 37 ,
         KEY_AMPERSAND         = 38 ,
         KEY_APOSTROPHE        = 39 ,
         KEY_LEFT_PARENTHESIS  = 40 ,
         KEY_RIGHT_PARENTHESIS = 41 ,
         KEY_ASTERISK          = 42 ,
         KEY_PLUS              = 43 ,
         KEY_COMMA             = 44,
         KEY_MINUS  = 45,
         KEY_PERIOD = 46 ,
         KEY_SLASH  = 47 ,
         KEY_0 = 48,
         KEY_1 = 49 ,
         KEY_2 = 50 ,
         KEY_3 = 51 ,
         KEY_4 = 52 ,
         KEY_5 = 53 ,
         KEY_6 = 54 ,
         KEY_7 = 55 ,
         KEY_8 = 56 ,
         KEY_9 = 57 ,
         KEY_COLON         = 58,
         KEY_SEMICOLON     = 59 ,
         KEY_LESS          = 60 ,
         KEY_EQUALS        = 61 ,
         KEY_GREATER       = 62 ,
         KEY_QUESTION_MARK = 63 ,
         KEY_AT            = 64 ,
         KEY_A = 65,
         KEY_B = 66,
         KEY_C = 67,
         KEY_D = 68,
         KEY_E = 69,
         KEY_F = 70,
         KEY_G = 71,
         KEY_H = 72,
         KEY_I = 73,
         KEY_J = 74,
         KEY_K = 75,
         KEY_L = 76,
         KEY_M = 77,
         KEY_N = 78,
         KEY_O = 79,
         KEY_P = 80,
         KEY_Q = 81,
         KEY_R = 82,
         KEY_S = 83,
         KEY_T = 84,
         KEY_U = 85,
         KEY_V = 86,
         KEY_W = 87,
         KEY_X = 88,
         KEY_Y = 89,
         KEY_Z = 90,
         KEY_OPEN_BRACKET  = 91,
         KEY_BACK_SLASH    = 92 ,
         KEY_CLOSE_BRACKET = 93 ,
         KEY_CIRCUMFLEX    = 94 ,
         KEY_UNDERSCORE    = 95 ,
         KEY_BACK_QUOTE    = 96 ,

         
         KEY_BRACE_LEFT  = 123,
         KEY_PIPE        = 124 ,
         KEY_BRACE_RIGHT = 125 ,
         KEY_TILDE       = 126 ,
         KEY_DELETE      = 127 ,

         KEY_INVERTED_EXCLAMATION_MARK,

         KEY_ALT           = 131,
         KEY_CONTROL       = 132 ,
         KEY_CAPS_LOCK     = 133 ,
         KEY_SCROLL_LOCK   = 134 ,
         KEY_NUM_LOCK      = 135 ,
         KEY_SHIFT         = 136 ,
         KEY_MENU          = 137 ,
         KEY_META          = 138 ,
         KEY_ENTER         = 139 ,

         KEY_CANCEL        = 140 ,
         KEY_CLEAR         = 141 ,
         KEY_COPY          = 142 ,
         KEY_CUT           = 143 ,
         KEY_END           = 144 ,
         KEY_INSERT        = 145 ,
         KEY_HOME          = 146 ,
         KEY_PAGE_DOWN     = 147 ,
         KEY_PAGE_UP       = 148 ,
         KEY_FIND          = 149 ,
         KEY_HELP          = 150 ,
         KEY_PASTE         = 151 ,
         KEY_PAUSE         = 152 ,
         KEY_PRINTSCREEN   = 153 ,
         KEY_STOP          = 154 ,
         KEY_UNDO          = 155 ,

         KEY_F1            = 156 ,
         KEY_F2            = 157 ,
         KEY_F3            = 158 ,
         KEY_F4            = 159 ,
         KEY_F5            = 160 ,
         KEY_F6            = 161 ,
         KEY_F7            = 162 ,
         KEY_F8            = 163 ,
         KEY_F9            = 164 ,
         KEY_F10           = 165 ,
         KEY_F11           = 166 ,
         KEY_F12           = 167 ,
         KEY_F13           = 168 ,
         KEY_F14           = 169 ,
         KEY_F15           = 170 ,
         KEY_F16           = 171 ,
         KEY_F17           = 172 ,
         KEY_F18           = 173 ,
         KEY_F19           = 174 ,
         KEY_F20           = 175 ,
         KEY_F21           = 176 ,
         KEY_F22           = 177 ,
         KEY_F23           = 178 ,
         KEY_F24           = 179 ,


         KEY_RIGHT         = 180 ,
         KEY_LEFT          = 181 ,
         KEY_UP            = 182 ,
         KEY_DOWN          = 183 ,

         KEY_MULTIPLY      = 184 ,
         KEY_DECIMAL       = 185 ,
         KEY_ADD           = 186 ,
         KEY_DIVIDE        = 187 ,
         KEY_SUBTRACT      = 188 ,
         KEY_KEYPAD_UP     = 189 ,
         KEY_KEYPAD_DOWN   = 190 ,
         KEY_KEYPAD_LEFT   = 191 ,
         KEY_KEYPAD_RIGHT  = 192 ,
         KEY_NONE          = 193 ,
         KEY_NUMPAD_0      = 194 ,
         KEY_NUMPAD_1      = 195 ,
         KEY_NUMPAD_2      = 196 ,
         KEY_NUMPAD_3      = 197 ,
         KEY_NUMPAD_4      = 198 ,
         KEY_NUMPAD_5      = 199 ,
         KEY_NUMPAD_6      = 200 ,
         KEY_NUMPAD_7      = 201 ,
         KEY_NUMPAD_8      = 202 ,
         KEY_NUMPAD_9      = 203 ,
         KEY_NUMPAD_EQUALS = 204 ,

#ifdef __APPLE__
                         KEY_COMMAND     = KEY_META,
#else
                         KEY_COMMAND     = KEY_CONTROL,
#endif
         KEY_UNDEFINED     = KEY_COMMAND+1
      };

	  enum KeyState
      {
		  KEY_STATE_UP      = 1,
		  KEY_STATE_DOWN    = 2 ,
		  KEY_STATE_TOGGLED = 3 
	  };

    struct ModifiedKey
    {
    public:
        UInt32 _Key;
        UInt32 _Modifiers;

        UInt64 getHashable(void) const;
    };

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

    static UInt64 getHashable(UInt32 TheKey, UInt32 Modifiers);
	static UChar8 getUpperLetterKey(UInt32 k, UInt32 Modifier);
	static UChar8 getLowerLetterKey(UInt32 k, UInt32 Modifier);
	static UChar8 getNonLetterKey(UInt32 k, UInt32 Modifier);
	static UChar8 getCharFromKey(UInt32 k, UInt32 Modifier);
    static std::string getStringFromKey(UInt32 k, UInt32 Modifier);
    static std::string getKeynameStringFromKey(UInt32 k, UInt32 Modifier);
	static std::string getStringFromNonDisplayedKey(UInt32 k, UInt32 Modifier);
	UChar8 getKeyChar(void) const;

    static  KeyEventDetailsTransitPtr create(FieldContainer* const Source,
                                             Time TimeStamp,
                                             UInt32 TheKey,
                                             UInt32 Modifiers,
                                             Window* const TheWindow);

    static  KeyEventDetailsTransitPtr create(KeyEventDetails* const Details,
                                             FieldContainer*  const NewSource);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in KeyEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    KeyEventDetails(void);
    KeyEventDetails(const KeyEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~KeyEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class KeyEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const KeyEventDetails &source);
};

typedef KeyEventDetails *KeyEventDetailsP;

bool OSG_SYSTEM_DLLMAPPING isAlphabetKey(KeyEventDetails::Key k);
bool OSG_SYSTEM_DLLMAPPING isNumericKey(KeyEventDetails::Key k);
bool OSG_SYSTEM_DLLMAPPING isWordKey(KeyEventDetails::Key k);
bool OSG_SYSTEM_DLLMAPPING isPunctuationKey(KeyEventDetails::Key k);
bool OSG_SYSTEM_DLLMAPPING isWhitespaceKey(KeyEventDetails::Key k);

OSG_END_NAMESPACE

#include "OSGWindow.h"            // Window type

#include "OSGKeyEventDetailsBase.inl"
#include "OSGKeyEventDetails.inl"

#endif /* _OSGKEYEVENTDETAILS_H_ */
