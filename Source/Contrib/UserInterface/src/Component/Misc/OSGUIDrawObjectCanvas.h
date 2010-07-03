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

#ifndef _OSGUIDRAWOBJECTCANVAS_H_
#define _OSGUIDRAWOBJECTCANVAS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGUIDrawObjectCanvasBase.h"
#include "OSGUIDrawObject.h"

OSG_BEGIN_NAMESPACE

/*! \brief UIDrawObjectCanvas class. See \ref
           PageContribUserInterfaceUIDrawObjectCanvas for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING UIDrawObjectCanvas : public UIDrawObjectCanvasBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef UIDrawObjectCanvasBase Inherited;
    typedef UIDrawObjectCanvas     Self;

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

	virtual void getDrawObjectBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
	virtual Vec2f getContentRequestedSize(void) const;
	virtual Vec2f getRequestedSize(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in UIDrawObjectCanvasBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    UIDrawObjectCanvas(void);
    UIDrawObjectCanvas(const UIDrawObjectCanvas &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~UIDrawObjectCanvas(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	virtual void drawInternal(Graphics* const Graphics, Real32 Opacity = 1.0f) const;
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class UIDrawObjectCanvasBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const UIDrawObjectCanvas &source);
};

typedef UIDrawObjectCanvas *UIDrawObjectCanvasP;

OSG_END_NAMESPACE

#include "OSGUIDrawObjectCanvasBase.inl"
#include "OSGUIDrawObjectCanvas.inl"

#endif /* _OSGUIDRAWOBJECTCANVAS_H_ */
