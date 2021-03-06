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

#ifndef _OSGUIRECTANGLEMOUSETRANSFORMFUNCTOR_H_
#define _OSGUIRECTANGLEMOUSETRANSFORMFUNCTOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGUIRectangleMouseTransformFunctorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief UIRectangleMouseTransformFunctor class. See \ref
           PageContribUserInterfaceUIRectangleMouseTransformFunctor for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING UIRectangleMouseTransformFunctor : public UIRectangleMouseTransformFunctorBase
{
  protected:
    friend class UIRectangle;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef UIRectangleMouseTransformFunctorBase Inherited;
    typedef UIRectangleMouseTransformFunctor     Self;

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

    virtual bool viewportToRenderingSurface(const Pnt2f& ViewportPoint,
                                            const Viewport* TheViewport,
                                            Pnt2f& Result) const;

    virtual bool renderingSurfaceToViewport(const Pnt2f& RenderingSurfacePoint,
                                            const Viewport* TheViewport,
                                            Pnt2f& Result) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in UIRectangleMouseTransformFunctorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    UIRectangleMouseTransformFunctor(void);
    UIRectangleMouseTransformFunctor(const UIRectangleMouseTransformFunctor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~UIRectangleMouseTransformFunctor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class UIRectangleMouseTransformFunctorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const UIRectangleMouseTransformFunctor &source);
};

typedef UIRectangleMouseTransformFunctor *UIRectangleMouseTransformFunctorP;

OSG_END_NAMESPACE

#include "OSGUIRectangle.h"

#include "OSGUIRectangleMouseTransformFunctorBase.inl"
#include "OSGUIRectangleMouseTransformFunctor.inl"

#endif /* _OSGUIRECTANGLEMOUSETRANSFORMFUNCTOR_H_ */
