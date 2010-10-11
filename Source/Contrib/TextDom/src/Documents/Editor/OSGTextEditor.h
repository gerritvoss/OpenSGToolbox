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
#include "OSGAdvancedTextDomAreaFields.h"

#include "OSGLabelFields.h"
#include "OSGTextDomAreaFields.h"
#include "OSGListFields.h"
#include "OSGListSelectionModelFields.h"
#include "OSGDefaultListModelFields.h"
#include "OSGSplitPanelFields.h"
#include "OSGTabPanelFields.h"
#include "OSGSearchWindowFields.h"
#include "OSGScrollPanelFields.h"
#include "OSGActionEventDetailsFields.h"
#include "OSGSearchWindowEventDetailsFields.h"
#include "OSGTextAreaFields.h"
#include "OSGButtonFields.h"
#include "OSGPanelFields.h"
#include "OSGSpringLayoutFields.h"


OSG_BEGIN_NAMESPACE

/*! \brief TextEditor class. See \ref
           PageContribTextDomTextEditor for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING TextEditor : public TextEditorBase
{
  protected:

		SplitPanelRefPtr _DomAreaAndClipboard;
		SplitPanelRefPtr _InsideDomArea;

	    // Clipboard related
		ListRefPtr _TheClipboardList;
		DefaultListModelRefPtr _TheClipboardListModel;
		ListSelectionModelPtr _TheClipboardListSelectionModel;
		ScrollPanelRefPtr _TheClipboardScrollPanel;
		LabelRefPtr _TheClipboardLabel;
		PanelRefPtr _TheClipboardPanel;
		SpringLayoutRefPtr _TheClipboardPanelLayout;
		ButtonRefPtr _TheClipboardButton;

		void clipboardInitialization(void);
		void createDomArea(void);
		AdvancedTextDomAreaTransitPtr createDuplicate(AdvancedTextDomArea* const TheAdvancedTextDomArea);



		void updateLayout(bool isClipboardVisible);	// to update the layout of the editor(to show/hide the copy clipboard)
		void updateDomLayout(bool isSplit);	// to update the layout of the Document Area (to show/hide the second view)

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

		void actionPerformed(ActionEventDetails* const details);

		SearchWindowRefPtr _SearchDialog;

		void handleSearchButtonClicked(SearchWindowEventDetails* const details);
		void handleReplaceButtonClicked(SearchWindowEventDetails* const details);
		void handleReplaceAllButtonClicked(SearchWindowEventDetails* const details);
		void handleBookmarkAllButtonClicked(SearchWindowEventDetails* const details);

        boost::signals2::connection _SearchButtonClickedConnection,
                                    _ReplaceButtonClickedConnection,
                                    _ReplaceAllButtonClickedConnection,
                                    _BookmarkAllButtonClickedConnection;

	    void handleClipboardButtonAction(ActionEventDetails* const details);
        boost::signals2::connection _ClipboardButtonActionConnection;

		void handleCloseButtonAction(ActionEventDetails* const details);
        boost::signals2::connection _CloseButtonActionConnection;

        void saveFile(const BoostPath& file);

		virtual void keyTyped(KeyEventDetails* const details);

		virtual void mouseClicked(MouseEventDetails* const details);

    /*==========================  PUBLIC  =================================*/

  public:

	void loadFile(const BoostPath& file);

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
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

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
