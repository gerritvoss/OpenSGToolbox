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

#ifndef _OSGROTATEDCOMPONENT_H_
#define _OSGROTATEDCOMPONENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGRotatedComponentBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief RotatedComponent class. See \ref
           PageContribUserInterfaceRotatedComponent for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING RotatedComponent : public RotatedComponentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum ResizePolicy
    {
        NO_RESIZING   = 0 ,
        RESIZE_TO_MIN = 1,
        RESIZE_TO_MAX = 2
    };

    typedef RotatedComponentBase Inherited;
    typedef RotatedComponent     Self;

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
    
	//Mouse Events
    virtual void mouseClicked(const MouseEventUnrecPtr e);
    virtual void mouseEntered(const MouseEventUnrecPtr e);
    virtual void mouseExited(const MouseEventUnrecPtr e);
    virtual void mousePressed(const MouseEventUnrecPtr e);
    virtual void mouseReleased(const MouseEventUnrecPtr e);

	//Mouse Motion Events
    virtual void mouseMoved(const MouseEventUnrecPtr e);
    virtual void mouseDragged(const MouseEventUnrecPtr e);

	//Mouse Wheel Events
    virtual void mouseWheelMoved(const MouseWheelEventUnrecPtr e);

    virtual Pnt2f getParentToLocal(const Pnt2f& Location) const;

    virtual Pnt2f getLocalToParent(const Pnt2f& Location) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in RotatedComponentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    RotatedComponent(void);
    RotatedComponent(const RotatedComponent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RotatedComponent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	virtual void drawInternal(const GraphicsWeakPtr Graphics, Real32 Opacity = 1.0f) const;
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class RotatedComponentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const RotatedComponent &source);
};

typedef RotatedComponent *RotatedComponentP;

OSG_END_NAMESPACE

#include "OSGRotatedComponentBase.inl"
#include "OSGRotatedComponent.inl"

#endif /* _OSGROTATEDCOMPONENT_H_ */
