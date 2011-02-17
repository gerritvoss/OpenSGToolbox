/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
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

#ifndef _OSGSEARCHWINDOW_H_
#define _OSGSEARCHWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSearchWindowBase.h"
#include "OSGDefaultMutableComboBoxModelFields.h"
#include "OSGComboBoxFields.h"
#include "OSGCheckboxButtonFields.h"


OSG_BEGIN_NAMESPACE

/*! \brief SearchWindow class. See \ref
           PageContribTextDomSearchWindow for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING SearchWindow : public SearchWindowBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SearchWindowBase Inherited;
    typedef SearchWindow     Self;

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
    static SearchWindowTransitPtr create(const std::string& WindowTitle);
	
	std::string getSearchText(void);
	std::string getReplaceText(void);
	bool isCaseChecked(void);
	bool isWholeWordChecked(void);
	bool isUseRegExChecked(void);
	bool isSearchUpChecked(void);
	bool isWrapAroundChecked(void);
	
    /*=========================  PROTECTED  ===============================*/

  protected:

 	DefaultMutableComboBoxModelRefPtr _SearchComboBoxModel;
    ComboBoxRefPtr _SearchComboBox;

	DefaultMutableComboBoxModelRefPtr _ReplaceComboBoxModel;
    ComboBoxRefPtr _ReplaceComboBox;
	
	CheckboxButtonRefPtr _MatchCaseCheckboxButton;
	CheckboxButtonRefPtr _MatchWholeWordCheckboxButton;
	CheckboxButtonRefPtr _MatchUseRegExCheckboxButton;
	CheckboxButtonRefPtr _SearchUpCheckboxButton;
	CheckboxButtonRefPtr _WrapAroundCheckboxButton;

	void handleSearchButtonAction(ActionEventDetails* const details);
	void handleReplaceButtonAction(ActionEventDetails* const details);
	void handleReplaceAllButtonAction(ActionEventDetails* const details);
	void handleBookmarkAllButtonAction(ActionEventDetails* const details);


	boost::signals2::connection _SearchButtonActionConnection,
								_ReplaceButtonActionConnection,
								_ReplaceAllButtonActionConnection,
								_BookmarkAllButtonActionConnection;


	
    // Variables should all be in SearchWindowBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SearchWindow(void);
    SearchWindow(const SearchWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SearchWindow(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SearchWindowBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SearchWindow &source);
};

typedef SearchWindow *SearchWindowP;

OSG_END_NAMESPACE

#include "OSGSearchWindowBase.inl"
#include "OSGSearchWindow.inl"

#endif /* _OSGSEARCHWINDOW_H_ */
