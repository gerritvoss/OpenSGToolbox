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
#include "OSGDocument.h"
#include "OSGSearchWindowListener.h"
#include "OSGTextAreaFields.h"
#include "OSGButtonFields.h"
#include "OSGTextArea.h"
#include "OSGButton.h"
#include "OSGTextField.h"
#include "OSGFixedHeightLayoutManager.h"
#include "OSGComboBox.h"
#include "OSGDefaultMutableComboBoxModel.h"
#include "OSGCheckboxButton.h"
#include "OSGGridBagLayout.h"
#include "OSGGridBagLayoutConstraints.h"

#include <set>
#include <vector>

#include "OSGEventListener.h"

#include "OSGEventConnection.h"


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

	EventConnection addSearchWindowListener(SearchWindowListenerPtr Listener);
	bool isSearchWindowListenerAttached(SearchWindowListenerPtr Listener) const;
    void removeSearchWindowListener(SearchWindowListenerPtr Listener);

    EventConnection addEventListener(EventListenerPtr Listener);
	bool isEventListenerAttached(EventListenerPtr Listener) const;
    void removeEventListener(EventListenerPtr Listener);
	
	virtual void close(/*UInt32 intOption, std::string strInput, std::string replaceText*/);
    
	static SearchWindowUnrecPtr createDialog(const std::string& Title,
                                                  const std::vector<std::string>& InputValues);


	ActionListener* getSearchButtonListener(void);
    ActionListener* getReplaceButtonListener (void);

	std::string getSearchText(void);
	std::string getReplaceText(void);
	bool isCaseChecked(void);
	bool isWholeWordChecked(void);
	bool isUseRegExChecked(void);

    /*=========================  PROTECTED  ===============================*/

  protected:
	  
	DefaultMutableComboBoxModelRefPtr _SearchComboBoxModel;
    ComboBoxRefPtr _SearchComboBox;

	DefaultMutableComboBoxModelRefPtr _ReplaceComboBoxModel;
    ComboBoxRefPtr _ReplaceComboBox;
	
	CheckboxButtonRefPtr _MatchCaseCheckboxButton;
	CheckboxButtonRefPtr _MatchWholeWordCheckboxButton;
	CheckboxButtonRefPtr _MatchUseRegExCheckboxButton;

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

	
	void searchActionPerformed(const ActionEventUnrecPtr e);
	void replaceActionPerformed(const ActionEventUnrecPtr e);
	void replaceAllActionPerformed(const ActionEventUnrecPtr e);
	void bookmarkAllActionPerformed(const ActionEventUnrecPtr e);

    static void initMethod(InitPhase ePhase);

	class SearchButtonListener : public ActionListener
    {
      public :
        SearchButtonListener(SearchWindowRefPtr TheDialogWindow);
        virtual void actionPerformed(const ActionEventUnrecPtr e);
      protected :
        SearchWindowRefPtr _DialogWindow;
    };
    SearchButtonListener _SearchButtonListener;

    class ReplaceButtonListener : public ActionListener
    {
      public :
        ReplaceButtonListener(SearchWindowRefPtr TheDialogWindow);
        virtual void actionPerformed(const ActionEventUnrecPtr e);
      protected :
        SearchWindowRefPtr _DialogWindow;
    };
    ReplaceButtonListener _ReplaceButtonListener;

	class ReplaceAllButtonListener : public ActionListener
    {
      public :
        ReplaceAllButtonListener(SearchWindowRefPtr TheDialogWindow);
        virtual void actionPerformed(const ActionEventUnrecPtr e);
      protected :
        SearchWindowRefPtr _DialogWindow;
    };
    ReplaceAllButtonListener _ReplaceAllButtonListener;

	class BookmarkAllButtonListener : public ActionListener
    {
      public :
        BookmarkAllButtonListener(SearchWindowRefPtr TheDialogWindow);
        virtual void actionPerformed(const ActionEventUnrecPtr e);
      protected :
        SearchWindowRefPtr _DialogWindow;
    };
    BookmarkAllButtonListener _BookmarkAllButtonListener;




	typedef std::set<SearchWindowListenerPtr> SearchWindowListenerSet;
    typedef SearchWindowListenerSet::iterator SearchWindowListenerSetItor;
    typedef SearchWindowListenerSet::const_iterator SearchWindowListenerSetConstItor;
	
    SearchWindowListenerSet       _SearchWindowListeners;
	    
	typedef std::set<EventListenerPtr> EventListenerSet;
    typedef EventListenerSet::iterator EventListenerSetItor;
    typedef EventListenerSet::const_iterator EventListenerSetConstItor;
	
    EventListenerSet       _EventListeners;

	virtual void produceSearchWindowClosing(void);
    virtual void produceSearchWindowClosed(void);
	virtual void produceSearchButtonClicked(void);
	virtual void produceReplaceButtonClicked(void);
	virtual void produceReplaceAllButtonClicked(void);
	virtual void produceBookmarkAllButtonClicked(void);
			

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
