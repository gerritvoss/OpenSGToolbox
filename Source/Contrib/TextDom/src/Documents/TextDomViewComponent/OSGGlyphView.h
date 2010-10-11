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

#ifndef _OSGGLYPHVIEW_H_
#define _OSGGLYPHVIEW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGlyphViewBase.h"
#include "OSGGraphics.h"
#include "OSGDocumentElementAttributes.h"
#include "OSGPlainDocumentLeafElement.h"

OSG_BEGIN_NAMESPACE

/*! \brief GlyphView class. See \ref
           PageContribTextDomGlyphView for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING GlyphView : public GlyphViewBase
{
  protected:

	Element* _Element;
	Pnt2f _InitialPosition;
	Real32 _LineHeight;
	Real32 _LineWidth;
	UInt32 _Lines;
	bool _IsWordWrapEnabled;
	UInt32 _Location;
	UIFontRefPtr _Font;
	UInt32 _LineNumber;
	

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GlyphViewBase Inherited;
    typedef GlyphView     Self;

	void setElement(Element* const theElement);
	void setInitialPosition(const Pnt2f& init);
	void setLines(UInt32 lines);
	void setLineHeight(Real32 lineheight);
	void setLineWidth(Real32 lineWidth);
	void setCaretLocation(Int32 loc);
	void setFont(UIFont* const font);
	void setLineNumber(UInt32 lineNumber);


	virtual void drawView(Graphics * const TheGraphics, Real32 Opacity);

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

    // Variables should all be in GlyphViewBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GlyphView(void);
    GlyphView(const GlyphView &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GlyphView(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GlyphViewBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GlyphView &source);
};

typedef GlyphView *GlyphViewP;

OSG_END_NAMESPACE

#include "OSGGlyphViewBase.inl"
#include "OSGGlyphView.inl"

#endif /* _OSGGLYPHVIEW_H_ */
