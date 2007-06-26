#include "OSGKeyEvent.h"


OSG_BEGIN_NAMESPACE

UChar8 KeyEvent::getCharFromKey(Key k, UInt32 Modifier)
{
   if( (Modifier & SHIFT) != SHIFT)
   {
      return getCharFromKey(k);
   }

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
      return NULL;
   }
}

UChar8 KeyEvent::getCharFromKey(Key k)
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

   case KEY_AMPERSAND:
      return '&';
   case KEY_APOSTROPHE:
      return '\'';
   case KEY_ASTERISK:
      return '*';
   case KEY_AT:
      return '@';
   case KEY_BACK_QUOTE:
      return '`';
   case KEY_BACK_SLASH:
      return '\\';
   case KEY_BRACE_LEFT:
      return '{';
   case KEY_BRACE_RIGHT:
      return '}';
   case KEY_CIRCUMFLEX:
      return '^';
   case KEY_CLOSE_BRACKET:
      return ']';
   case KEY_COLON:
      return ':';
   case KEY_COMMA:
      return ',';
   case KEY_DECIMAL:
      return '.';
   case KEY_DIVIDE:
      return '/';
   case KEY_DOLLAR:
      return '$';
   case KEY_EQUALS:
      return '=';
   case KEY_EXCLAMATION_MARK:
      return '!';
   case KEY_GREATER:
      return '>';
   case KEY_INVERTED_EXCLAMATION_MARK:
      return '¡';
   case KEY_LEFT_PARENTHESIS:
      return '(';
   case KEY_LESS:
      return '<';
   case KEY_MINUS:
      return '-';
   case KEY_MULTIPLY:
      return '*';
   case KEY_NUMBER_SIGN:
      return '#';
   case KEY_OPEN_BRACKET:
      return '[';
   case KEY_PERIOD:
      return '.';
   case KEY_PLUS:
      return '+';
   case KEY_QUOTE:
      return '"';
   case KEY_RIGHT_PARENTHESIS:
      return ')';
   case KEY_SEMICOLON:
      return ';';
   case KEY_SLASH:
      return '/';
   case KEY_SPACE:
      return ' ';
   case KEY_SUBTRACT:
      return '-';
   case KEY_TAB:
      return ' ';
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
      return NULL;
   }
}

OSG_END_NAMESPACE
