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
#include <OpenSG/Input/OSGUpdateListener.h>

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
		Int32 _StartPosition;
		Int32 _EndPosition;
		Real32 _VerticalOffset;
		Real32 _LeftHorizontalOffset;
		Real32 _RightHorizontalOffset;
		std::string _Contents;
	};

	virtual void keyTyped(const KeyEvent& e);
	virtual void mouseClicked(const MouseEvent& e);
	virtual void mousePressed(const MouseEvent& e);
	virtual void mouseDragged(const MouseEvent& e);
	
	virtual void focusGained(const FocusEvent& e);
	virtual void focusLost(const FocusEvent& e);

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
