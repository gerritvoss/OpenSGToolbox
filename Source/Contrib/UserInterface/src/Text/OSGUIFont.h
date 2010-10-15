/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#ifndef _OSGUIFONT_H_
#define _OSGUIFONT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGUIFontBase.h"
#include "OSGTextureObjChunk.h"

#include "OSGTextTXFFace.h"
#include "OSGTextLayoutParam.h"
#include "OSGTextLayoutResult.h"
#include "OSGTextTXFGlyph.h"
#include "OSGPathType.h"

OSG_BEGIN_NAMESPACE

/*! \brief UIFont class. See \ref
           PageContribUserInterfaceUIFont for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING UIFont : public UIFontBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef UIFontBase Inherited;
    typedef UIFont     Self;

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
    void layout(const std::string &utf8Text, const TextLayoutParam &param, TextLayoutResult &result);
    const TextTXFGlyph* getTXFGlyph(TextGlyph::Index glyphIndex);

	void getBounds(const std::string& Text, Pnt2f& TopLeft, Pnt2f& BottomRight);
	Vec2f getBounds(const std::string& Text);

    static FieldContainerTransitPtr createFont( const BoostPath& FilePath );

    static FieldContainerUnrecPtr loadFromFileHandler( const BoostPath& FilePath );
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in UIFontBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    UIFont(void);
    UIFont(const UIFont &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~UIFont(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
    TextTXFFaceRefPtr _face;
    void initText(void);

    friend class FieldContainer;
    friend class UIFontBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const UIFont &source);
};

typedef UIFont *UIFontP;

OSG_END_NAMESPACE

#include "OSGUIFontBase.inl"
#include "OSGUIFont.inl"

#endif /* _OSGUIFONT_H_ */
