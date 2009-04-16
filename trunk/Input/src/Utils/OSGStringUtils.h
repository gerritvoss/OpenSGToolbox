/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Input                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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
