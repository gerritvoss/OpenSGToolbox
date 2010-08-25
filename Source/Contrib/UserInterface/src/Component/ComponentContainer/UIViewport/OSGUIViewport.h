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

#ifndef _OSGUIVIEWPORT_H_
#define _OSGUIVIEWPORT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGUIViewportBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief UIViewport class. See \ref
           PageContribUserInterfaceUIViewport for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING UIViewport : public UIViewportBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef UIViewportBase Inherited;
    typedef UIViewport     Self;

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
    virtual void updateLayout(void);
    
    Vec2f getCorrectedViewSize(void) const;
	void updateViewComponentSize(void);

	void maximizeVisibility(const Pnt2f& TopLeft, const Pnt2f& BottomRight);
	void getViewBounds(Pnt2f& TopLeft, Pnt2f& BottomRight);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in UIViewportBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    UIViewport(void);
    UIViewport(const UIViewport &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~UIViewport(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    void produceStateChanged(void);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class UIViewportBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const UIViewport &source);
};

typedef UIViewport *UIViewportP;

OSG_END_NAMESPACE

#include "OSGUIViewportBase.inl"
#include "OSGUIViewport.inl"

#endif /* _OSGUIVIEWPORT_H_ */
