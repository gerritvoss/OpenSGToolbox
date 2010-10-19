/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)*
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

OSG_BEGIN_NAMESPACE

inline
bool SearchWindow::isSearchWindowListenerAttached(SearchWindowListenerPtr Listener) const
{
    return _SearchWindowListeners.find(Listener) != _SearchWindowListeners.end();
}

inline
bool SearchWindow::isEventListenerAttached(EventListenerPtr Listener) const
{
    return _EventListeners.find(Listener) != _EventListeners.end();
}

inline
ActionListener* SearchWindow::getSearchButtonListener(void)
{
    return &_SearchButtonListener;
}

inline
ActionListener* SearchWindow::getReplaceButtonListener(void)
{
    return &_ReplaceButtonListener;
}

inline
std::string SearchWindow::getSearchText(void)
{
	return (dynamic_pointer_cast<TextField>(this->_SearchComboBox->getEditor()->getEditorComponent())->getDrawnText());
}

inline
std::string SearchWindow::getReplaceText(void)
{
	return (dynamic_pointer_cast<TextField>(this->_ReplaceComboBox->getEditor()->getEditorComponent())->getDrawnText());
}

inline
bool SearchWindow::isCaseChecked(void)
{
	return _MatchCaseCheckboxButton->getSelected();
}

inline
bool SearchWindow::isWholeWordChecked(void)
{
	return _MatchWholeWordCheckboxButton->getSelected();
}

inline
bool SearchWindow::isUseRegExChecked(void)
{
	return _MatchUseRegExCheckboxButton->getSelected();
}

OSG_END_NAMESPACE
