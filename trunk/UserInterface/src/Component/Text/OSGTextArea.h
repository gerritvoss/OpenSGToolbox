/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#ifndef _OSGTEXTAREA_H_
#define _OSGTEXTAREA_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"


#include "OSGTextAreaBase.h"
#include <vector>
#include <string>
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/Input/OSGMouseAdapter.h>
#include <OpenSG/Input/OSGMouseMotionAdapter.h>
#include <OpenSG/Input/OSGKeyAdapter.h>

OSG_BEGIN_NAMESPACE

/*! \brief TextArea class. See \ref 
           PageUserInterfaceTextArea for a description.
*/


class OSG_USERINTERFACELIB_DLLMAPPING TextArea : public TextAreaBase
{
  private:

    typedef TextAreaBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
	struct TextLine{
		UInt32 _StartPosition;
		UInt32 _EndPosition;
		Real32 _VerticalOffset;
		Real32 _LeftHorizontalOffset;
		Real32 _RightHorizontalOffset;
	};

	virtual void keyTyped(const KeyEvent& e);
	virtual void mouseClicked(const MouseEvent& e);
	virtual void mousePressed(const MouseEvent& e);
	
	virtual void focusGained(const FocusEvent& e);
	virtual void focusLost(const FocusEvent& e);

    //Components that display logical rows or columns should compute the scroll increment that will completely expose one block of rows or columns, depending on the value of orientation.
    virtual Int32 getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);

    //Return true if a viewport should always force the height of this Scrollable to match the height of the viewport.
    virtual bool getScrollableTracksViewportHeight(void);

    //Return true if a viewport should always force the width of this Scrollable to match the width of the viewport.
    virtual bool getScrollableTracksViewportWidth(void);

    //Components that display logical rows or columns should compute the scroll increment that will completely expose one new row or column, depending on the value of orientation.
    virtual Int32 getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);

	virtual Int32 getCaretLine(void) const;
	virtual UInt32 numLines(void) const;
	virtual std::string getLine(UInt32 line) const;
	virtual std::string getWrappedLine(UInt32 line) const;

	virtual bool isLineVisible(const UInt32& line) const;
    virtual UInt32 numVisibleLines(void) const;

	virtual void scrollToLine(const UInt32& line);

    
    virtual void moveCaretToEndOfLine(void);
    virtual void moveCaretToBeginOfLine(void);
    
    void moveCaretLine(Int32 delta);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in TextAreaBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextArea(void);
    TextArea(const TextArea &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextArea(void); 

	virtual void drawInternal(const GraphicsPtr Graphics) const;
    /*! \}                                                                 */
    
	mutable Time _CurrentCaretBlinkElps;

	class CaretUpdateListener : public UpdateListener
	{
	public:
		CaretUpdateListener(TextAreaPtr TheTextArea);
        virtual void update(const UpdateEvent& e);
	private:
		TextAreaPtr _TextArea;
	};

	friend class CarentUpdateListener;

	CaretUpdateListener _CaretUpdateListener;

	class MouseDownListener : public MouseAdapter,public MouseMotionAdapter,public KeyAdapter
	{
	public :
		MouseDownListener(TextAreaPtr TheTextArea);
		
        virtual void keyTyped(const KeyEvent& e);

        virtual void mouseReleased(const MouseEvent& e);
        virtual void mouseDragged(const MouseEvent& e);
	protected :
		TextAreaPtr _TextArea;
	};

	friend class MouseDownListener;

	MouseDownListener _MouseDownListener;

    void mouseDraggedAfterArming(const MouseEvent& e);
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class TextAreaBase;

	Int32 findTextPosition(Pnt2f Input);
    static void initMethod(void);

	std::vector<TextLine> _LineContents;

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const TextArea &source);
};

typedef TextArea *TextAreaP;

OSG_END_NAMESPACE

#include "OSGTextAreaBase.inl"
#include "OSGTextArea.inl"

#define OSGTEXTAREA_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGTEXTAREA_H_ */
