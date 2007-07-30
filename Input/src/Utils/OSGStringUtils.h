#ifndef _OPENSG_STRING_UTILS_H_
#define _OPENSG_STRING_UTILS_H_

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"

#include "Event/OSGKeyEvent.h"

OSG_BEGIN_NAMESPACE

bool OSG_INPUTLIB_DLLMAPPING isAlphabetKey(KeyEvent::Key k);
bool OSG_INPUTLIB_DLLMAPPING isNumericKey(KeyEvent::Key k);
bool OSG_INPUTLIB_DLLMAPPING isWordKey(KeyEvent::Key k);
bool OSG_INPUTLIB_DLLMAPPING isPunctuationKey(KeyEvent::Key k);
bool OSG_INPUTLIB_DLLMAPPING isWhitespaceKey(KeyEvent::Key k);

bool OSG_INPUTLIB_DLLMAPPING isAlphabetChar(UChar8 c);
bool OSG_INPUTLIB_DLLMAPPING isNumericChar(UChar8 c);
bool OSG_INPUTLIB_DLLMAPPING isWordChar(UChar8 c);
bool OSG_INPUTLIB_DLLMAPPING isPunctuationChar(UChar8 c);
bool OSG_INPUTLIB_DLLMAPPING isWhitespaceChar(UChar8 c);

OSG_END_NAMESPACE

#endif
