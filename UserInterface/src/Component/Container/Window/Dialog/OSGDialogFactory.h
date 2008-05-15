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
#ifndef _OSG_DIALOG_FACTORY_H_
#define _OSG_DIALOG_FACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

//#include "Component/Container/Window/OSGInternalWindowFields.h"
#include "Component/Container/OSGContainerFields.h"
#include "OSGDialogWindowFields.h"

#include "Component/Text/OSGTextAreaFields.h"
#include "Event/OSGActionListener.h"

#include <vector>
#include <deque>
#include <map>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING DialogFactory
{
/*=========================  PUBLIC  ===============================*/
public:
	typedef std::deque<Color4f> ColorDeque;
	typedef std::vector<std::string> StringVector;
	
	typedef std::map<std::string, ColorDeque> ColorHistoryMap;
	typedef ColorHistoryMap::iterator ColorHistoryMapItor;
	typedef ColorHistoryMap::const_iterator ColorHistoryMapConstItor;

	void createColorHistory(const std::string& HistoryName);

	void removeColorHistory(const std::string& HistoryName);

	void pushToColorHistory(const std::string& HistoryName, const Color4f& TheColor);
	
	void popFromColorHistory(const std::string& HistoryName);

	void clearColorHistory(const std::string& HistoryName);

	ColorDeque getColorHistory(const std::string& HistoryName) const;

	StringVector getColorHistories(void) const;

	static DialogWindowPtr createMessageDialog(const std::string& Title, const std::string& Message, const std::string& ConfirmButtonText = std::string("Ok"));
    
    static ContainerPtr createMessagePanel(const std::string& Message, const std::string& ConfirmButtonText);
	
//	static InternalWindowPtr createOptionDialog(const std::string& Title, const std::string& Message, const std::vector<std::string>& OptionButtonsText);
    
    static ContainerPtr createOptionPanel(const std::string& Message, const std::vector<std::string>& OptionButtonsText);

	static void addButtonActionListener(const ActionListener& Listener, const int index);
	
	DialogWindowPtr createColorDialog(const std::string& Title, const Color4f& TheColor, const std::string& HistoryName);

    ContainerPtr createColorPanel(const Color4f& TheColor, const std::string& HistoryName);
	
    static DialogFactory* the(void);
private:

    DialogFactory(void);

	static TextAreaPtr createTransparentTextArea(const std::string& Message);

    static DialogFactory* _the;

	ColorHistoryMap _ColorHistory;
};
OSG_END_NAMESPACE

#include "OSGDialogFactory.inl"

#endif /* _OSG_DIALOG_FACTORY_H_ */
