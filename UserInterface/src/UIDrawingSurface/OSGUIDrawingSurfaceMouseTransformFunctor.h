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

#ifndef _OSGUIDRAWINGSURFACEMOUSETRANSFORMFUNCTOR_H_
#define _OSGUIDRAWINGSURFACEMOUSETRANSFORMFUNCTOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGViewport.h>

#include "OSGUIDrawingSurfaceMouseTransformFunctorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief UIDrawingSurfaceMouseTransformFunctor class. See \ref 
           PageUserInterfaceUIDrawingSurfaceMouseTransformFunctor for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING UIDrawingSurfaceMouseTransformFunctor : public UIDrawingSurfaceMouseTransformFunctorBase
{
  private:

    typedef UIDrawingSurfaceMouseTransformFunctorBase Inherited;

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
	virtual bool viewportToRenderingSurface(const Pnt2s& ViewportPoint,
		                                    ViewportPtr TheViewport,
		                                        Pnt2s& Result) const = 0;
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
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class UIDrawingSurfaceMouseTransformFunctorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const UIDrawingSurfaceMouseTransformFunctor &source);
};

typedef UIDrawingSurfaceMouseTransformFunctor *UIDrawingSurfaceMouseTransformFunctorP;

OSG_END_NAMESPACE

#include "OSGUIDrawingSurfaceMouseTransformFunctorBase.inl"
#include "OSGUIDrawingSurfaceMouseTransformFunctor.inl"

#define OSGUIDRAWINGSURFACEMOUSETRANSFORMFUNCTOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGUIDRAWINGSURFACEMOUSETRANSFORMFUNCTOR_H_ */
