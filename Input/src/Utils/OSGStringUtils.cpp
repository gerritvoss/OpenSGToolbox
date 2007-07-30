#include "OSGStringUtils.h"

OSG_BEGIN_NAMESPACE

bool isAlphabetKey(KeyEvent::Key k)
{
	if(k >= KeyEvent::KEY_A && k <= KeyEvent::KEY_Z)
	{
		return true;
	}
	return false;
}

bool isNumericKey(KeyEvent::Key k)
{
	if(k >= KeyEvent::KEY_0 && k <= KeyEvent::KEY_9)
	{
		return true;
	}
	return false;
}
bool isWordKey(KeyEvent::Key k)
{
	if(isAlphabetKey(k) || isNumericKey(k))
	{
		return true;
	}
	return false;
}
bool isPunctuationKey(KeyEvent::Key k)
{
	//TODO: Implement
	switch(k)
	{

	case KeyEvent::KEY_APOSTROPHE:
	case KeyEvent::KEY_AMPERSAND:
	case KeyEvent::KEY_ASTERISK:
	case KeyEvent::KEY_AT:
	case KeyEvent::KEY_BACK_QUOTE:
	case KeyEvent::KEY_BACK_SLASH:
	case KeyEvent::KEY_BRACE_LEFT:
	case KeyEvent::KEY_BRACE_RIGHT:
	case KeyEvent::KEY_CIRCUMFLEX:
	case KeyEvent::KEY_CLOSE_BRACKET:
	case KeyEvent::KEY_COLON:
	case KeyEvent::KEY_COMMA:
	case KeyEvent::KEY_DECIMAL:
	case KeyEvent::KEY_DIVIDE:
	case KeyEvent::KEY_DOLLAR:
	case KeyEvent::KEY_EQUALS:
	case KeyEvent::KEY_EXCLAMATION_MARK:
	case KeyEvent::KEY_GREATER:
	case KeyEvent::KEY_INVERTED_EXCLAMATION_MARK:
	case KeyEvent::KEY_LEFT_PARENTHESIS:
	case KeyEvent::KEY_LESS:
	case KeyEvent::KEY_MINUS:
	case KeyEvent::KEY_MULTIPLY:
	case KeyEvent::KEY_NUMBER_SIGN:
	case KeyEvent::KEY_OPEN_BRACKET:
	case KeyEvent::KEY_PERCENT:
	case KeyEvent::KEY_PERIOD:
	case KeyEvent::KEY_PIPE:
	case KeyEvent::KEY_PLUS:
	case KeyEvent::KEY_QUESTION_MARK:
	case KeyEvent::KEY_QUOTE:
	case KeyEvent::KEY_RIGHT_PARENTHESIS:
	case KeyEvent::KEY_SEMICOLON:
	case KeyEvent::KEY_SLASH:
	case KeyEvent::KEY_SUBTRACT:
	case KeyEvent::KEY_TILDE:
	case KeyEvent::KEY_UNDERSCORE:
		return true;
	}
	return false;
}
bool isWhitespaceKey(KeyEvent::Key k)
{	
	switch(k)
	{
	case KeyEvent::KEY_SPACE:
	case KeyEvent::KEY_TAB:
		return true;
	}
	return false;
}


bool isAlphabetChar(UChar8 c)
{
	if(c >= 65 && c <= 90 || c >= 97 && c <= 122)
	{
		return true;
	}
	return false;
}

bool isNumericChar(UChar8 c)
{
	if(c >= 48 && c <= 57)
	{
		return true;
	}
	return false;
}

bool isWordChar(UChar8 c)
{
	if(isAlphabetChar(c) || isNumericChar(c))
	{
		return true;
	}
	return false;
}

bool isPunctuationChar(UChar8 c)
{
	switch(c)
	{
	case '!': 
	case '~':
	case '`':
	case '@':
	case '#':
	case '$':
	case '%':
	case '^':
	case '&':
	case '*':
	case '(':
	case ')':
	case '-':
	case '_':
	case '+':
	case '=':
	case ':':
	case ';':
	case '\"':
	case '\'':
	case '[':
	case '{':
	case ']':
	case '}':
	case '|':
	case '\\':
	case '<':
	case '>':
	case '.':
	case '/':
	case ',':
	case '?':
			  return true;
	
	}
	return false;
}

bool isWhitespaceChar(UChar8 c)
{
	if(c == 0)
	{
		return true;
	}
	return false;
}

OSG_END_NAMESPACE
