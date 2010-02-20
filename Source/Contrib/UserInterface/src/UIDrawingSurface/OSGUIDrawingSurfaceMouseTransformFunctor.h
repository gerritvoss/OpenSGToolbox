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

#ifndef _OSGUIDRAWINGSURFACEMOUSETRANSFORMFUNCTOR_H_
#define _OSGUIDRAWINGSURFACEMOUSETRANSFORMFUNCTOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGUIDrawingSurfaceMouseTransformFunctorBase.h"
#include "OSGVector.h"
#include "OSGViewport.h"

OSG_BEGIN_NAMESPACE

/*! \brief UIDrawingSurfaceMouseTransformFunctor class. See \ref
           PageContribUserInterfaceUIDrawingSurfaceMouseTransformFunctor for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING UIDrawingSurfaceMouseTransformFunctor : public UIDrawingSurfaceMouseTransformFunctorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef UIDrawingSurfaceMouseTransformFunctorBase Inherited;
    typedef UIDrawingSurfaceMouseTransformFunctor     Self;

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
                                            Pnt2f& Result) const = 0;

    virtual bool renderingSurfaceToViewport(const Pnt2f& RenderingSurfacePoint,
                                            const Viewport* TheViewport,
                                            Pnt2f& Result) const = 0;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in UIDrawingSurfaceMouseTransformFunctorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    UIDrawingSurfaceMouseTransformFunctor(void);
    UIDrawingSurfaceMouseTransformFunctor(const UIDrawingSurfaceMouseTransformFunctor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~UIDrawingSurfaceMouseTransformFunctor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class UIDrawingSurfaceMouseTransformFunctorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const UIDrawingSurfaceMouseTransformFunctor &source);
};

typedef UIDrawingSurfaceMouseTransformFunctor *UIDrawingSurfaceMouseTransformFunctorP;

OSG_END_NAMESPACE

#include "OSGUIDrawingSurfaceMouseTransformFunctorBase.inl"
#include "OSGUIDrawingSurfaceMouseTransformFunctor.inl"

#endif /* _OSGUIDRAWINGSURFACEMOUSETRANSFORMFUNCTOR_H_ */
