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

#ifndef _OSGCOMPONENTCONTAINER_H_
#define _OSGCOMPONENTCONTAINER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGComponentContainerBase.h"
#include <map>

OSG_BEGIN_NAMESPACE

/*! \brief ComponentContainer class. See \ref
           PageContribUserInterfaceComponentContainer for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ComponentContainer : public ComponentContainerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ComponentContainerBase Inherited;
    typedef ComponentContainer     Self;

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
    virtual void getInsideInsetsBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
    virtual void setAllInsets(Real32 Inset);
	Real32 &getLeftInset (void);
	const Real32 &getLeftInset (void) const;
	Real32 &getRightInset (void);
	const Real32 &getRightInset (void) const;
	Real32 &getTopInset (void);
	const Real32 &getTopInset (void) const;
	Real32 &getBottomInset (void);
	const Real32 &getBottomInset (void) const;
	void setLeftInset ( const Real32 &value );
	void setRightInset ( const Real32 &value );
	void setTopInset ( const Real32 &value );
	void setBottomInset ( const Real32 &value );

    virtual Int32 getChildIndex(Component* const Child);

    virtual void updateLayout(void);
	virtual Vec2f getContentRequestedSize(void) const;
	virtual Vec2f getBorderingLength(void) const;
	
	//Mouse Events
    virtual void mouseClicked ( MouseEventDetails* const e);
    virtual void mouseEntered ( MouseEventDetails* const e);
    virtual void mouseExited  ( MouseEventDetails* const e);
    virtual void mousePressed ( MouseEventDetails* const e);
    virtual void mouseReleased( MouseEventDetails* const e);

	//Mouse Motion Events
    virtual void mouseMoved(MouseEventDetails* const e);
    virtual void mouseDragged(MouseEventDetails* const e);

	//Mouse Wheel Events
    virtual void mouseWheelMoved(MouseWheelEventDetails* const e);

    virtual void detachFromEventProducer(void);

    virtual void setParentWindow(InternalWindow* const parent);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ComponentContainerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ComponentContainer(void);
    ComponentContainer(const ComponentContainer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ComponentContainer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	virtual void drawInternal(Graphics* const Graphics, Real32 Opacity = 1.0f) const;

	void checkMouseEnterExit(InputEventDetails* const e, const Pnt2f& MouseLocation, Component* const Comp, bool isMouseContained, Viewport* const TheViewport);
	virtual void produceMouseExitOnComponent(MouseEventDetails* const e, Component* const Comp);
	virtual void produceMouseEnterOnComponent(MouseEventDetails* const e, Component* const Comp);
    void removeMousePresenceOnComponents(void);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ComponentContainerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ComponentContainer &source);
};

typedef ComponentContainer *ComponentContainerP;

OSG_END_NAMESPACE

#include "OSGLayout.h"

#include "OSGComponentContainerBase.inl"
#include "OSGComponentContainer.inl"

#endif /* _OSGCOMPONENTCONTAINER_H_ */
