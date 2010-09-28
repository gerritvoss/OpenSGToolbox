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

#ifndef _OSGADVANCEDTEXTDOMAREA_H_
#define _OSGADVANCEDTEXTDOMAREA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAdvancedTextDomAreaBase.h"
#include "OSGScrollPanel.h"
#include "OSGTextDomArea.h"
#include "OSGUIFont.h"
#include "OSGDocumentModelChangedListener.h"

OSG_BEGIN_NAMESPACE

/*! \brief AdvancedTextDomArea class. See \ref
           PageContribTextDomAdvancedTextDomArea for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING AdvancedTextDomArea : public AdvancedTextDomAreaBase
{
  protected:

	
  	virtual Vec2f getPreferredScrollableViewportSize(void);
    virtual Int32 getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);
	virtual Vec2f getContentRequestedSize(void) const;
	void drawGutter(const GraphicsWeakPtr Graphics, Real32 Opacity) const;

	TextDomAreaRefPtr _TheTextDomArea;
	UIFontRefPtr _Font;
    /*==========================  PUBLIC  =================================*/

  public:

	void setTheTextDomArea(TextDomAreaRefPtr duplicatedTextDom);

	std::string getHighlightedString(void);
	virtual void updateLayout(void);
    void loadFile(BoostPath path);
	void drawInternal(const GraphicsWeakPtr Graphics, Real32 Opacity) const;
	AdvancedTextDomAreaRefPtr makeADuplicate();

    typedef AdvancedTextDomAreaBase Inherited;
    typedef AdvancedTextDomArea     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const AdvancedTextDomArea *source = NULL);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

	  void changedUpdate(const DocumentModelChangedEventUnrecPtr e);

	  class PreferredSizeChangedListener:public DocumentModelChangedListener
	  {

	  public:
			PreferredSizeChangedListener(AdvancedTextDomAreaRefPtr theAdvancedTextDomArea);

			virtual void changedUpdate(const DocumentModelChangedEventUnrecPtr e);
	  protected:
		  AdvancedTextDomAreaRefPtr _AdvancedTextDomArea;

	  };

	  PreferredSizeChangedListener _PreferredSizeChangedListener;
	/*! \}                                                                 */

    // Variables should all be in AdvancedTextDomAreaBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AdvancedTextDomArea(void);
    AdvancedTextDomArea(const AdvancedTextDomArea &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AdvancedTextDomArea(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AdvancedTextDomAreaBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AdvancedTextDomArea &source);
};

typedef AdvancedTextDomArea *AdvancedTextDomAreaP;

OSG_END_NAMESPACE

#include "OSGAdvancedTextDomAreaBase.inl"
#include "OSGAdvancedTextDomArea.inl"

#endif /* _OSGADVANCEDTEXTDOMAREA_H_ */
