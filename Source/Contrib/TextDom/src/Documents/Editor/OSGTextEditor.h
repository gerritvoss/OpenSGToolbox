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

#ifndef _OSGTEXTEDITOR_H_
#define _OSGTEXTEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTextEditorBase.h"
#include "OSGAdvancedTextDomArea.h"

#include "OSGScrollPanel.h"
#include "OSGGridBagLayout.h"
#include "OSGGridBagLayoutConstraints.h"
#include "OSGLabel.h"
#include "OSGScrollPanel.h"
#include "OSGTextDomArea.h"
#include "OSGTextArea.h"
#include "OSGFixedHeightLayoutManager.h"
#include "OSGFlowLayout.h"
#include "OSGPanel.h"
#include "OSGColorLayer.h"
#include "OSGLineBorder.h"
#include "OSGList.h"
#include "OSGListSelectionModel.h"
#include "OSGDefaultListSelectionModel.h"
#include "OSGDefaultListModel.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"
#include "OSGSplitPanel.h"
#include "OSGBorderLayout.h"
#include "OSGTabPanel.h"
#include "OSGInternalWindow.h"
#include "OSGSearchWindow.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/algorithm/string.hpp>


OSG_BEGIN_NAMESPACE

/*! \brief TextEditor class. See \ref
           PageContribTextDomTextEditor for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING TextEditor : public TextEditorBase
{
  protected:

		PanelRefPtr thePanel;
		SplitPanelRefPtr DomAreaAndClipboard;
		SplitPanelRefPtr InsideDomArea;

	    // Clipboard related
		ListRefPtr TheClipboardList;
		DefaultListModelRefPtr TheClipboardListModel;
		ListSelectionModelPtr TheClipboardListSelectionModel;
		ScrollPanelRefPtr TheClipboardScrollPanel;
		LabelRefPtr TheClipboardLabel;
		PanelRefPtr TheClipboardPanel;
		SpringLayoutRefPtr TheClipboardPanelLayout;

			
		void clipboardInitialization(void);
		void createDomArea(void);


		void updateLayout(bool isClipboardVisible);
		void updateDomLayout(bool isSplit);

		// Dom related
		TabPanelRefPtr    _LeftTabPanel;
		LabelRefPtr       _LeftTabPanelLabel;
		ScrollPanelRefPtr _LeftTabPanelContent;
		TextAreaRefPtr    _LeftTabPanelTextArea;
		TabPanelRefPtr    _RightTabPanel;
		LabelRefPtr       _RightTabPanelLabel;
		ScrollPanelRefPtr _RightTabPanelContent;
		TextAreaRefPtr    _RightTabPanelTextArea;
		void createLeftTabPanel(void);
		void createRightTabPanel(void);
		void createDefaultTabs(void);

		void actionPerformed(const ActionEventUnrecPtr e);

		SearchWindowRefPtr TheDialog;
		class TheSearchWindowListener: public SearchWindowListener 
		{
		public:

			TheSearchWindowListener(TextEditorRefPtr _TheTextEditor);
			~TheSearchWindowListener();
			
			virtual void dialogClosing(const SearchWindowEventUnrecPtr e);
			virtual void dialogClosed(const SearchWindowEventUnrecPtr e);
			virtual void searchButtonClicked(const SearchWindowEventUnrecPtr e);
			virtual void replaceButtonClicked(const SearchWindowEventUnrecPtr e);
			virtual void replaceAllButtonClicked(const SearchWindowEventUnrecPtr e);
			virtual void bookmarkAllButtonClicked(const SearchWindowEventUnrecPtr e);
   
		protected:

			TextEditorRefPtr _TheTextEditor;
		};

		TheSearchWindowListener _TheSearchWindowListener;
		bool _IsDialogClosed;
		void dialogClosed(const SearchWindowEventUnrecPtr e);
		void dialogClosing(const SearchWindowEventUnrecPtr e);
		void searchButtonClicked(const SearchWindowEventUnrecPtr e);
		void replaceButtonClicked(const SearchWindowEventUnrecPtr e);
		void replaceAllButtonClicked(const SearchWindowEventUnrecPtr e);
		void bookmarkAllButtonClicked(const SearchWindowEventUnrecPtr e);


		class CloseButtonListener:public ActionListener
		{
		  public:
			CloseButtonListener(TextEditorRefPtr TheTextEditor);
			~CloseButtonListener(void);

			virtual void actionPerformed(const ActionEventUnrecPtr e);
		  protected :
			TextEditorRefPtr _TextEditor;
		};

		CloseButtonListener _CloseButtonListener;

		void saveFile(BoostPath file);

		virtual void keyTyped(const KeyEventUnrecPtr e);

    /*==========================  PUBLIC  =================================*/

  public:

	  void loadNewFile(BoostPath file);
	  /// newly added////////////////////////////////////////////////////////////
/*		void addTab(void);
		void removeTab(UInt32);
		void setIsSplit(bool value);	
		bool getIsSplit(void);
		void init(void);
		void addTabWithText(BoostPath);
		void closeCurrentWindow(void);
		void saveTextFile(BoostPath);
		void setView(UInt32 Index);*/
	//////////////////////////////////////////////////////////////////////////////

    typedef TextEditorBase Inherited;
    typedef TextEditor     Self;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TextEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextEditor(void);
    TextEditor(const TextEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const TextEditor *source = NULL);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TextEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TextEditor &source);
};

typedef TextEditor *TextEditorP;

OSG_END_NAMESPACE

#include "OSGTextEditorBase.inl"
#include "OSGTextEditor.inl"

#endif /* _OSGTEXTEDITOR_H_ */
