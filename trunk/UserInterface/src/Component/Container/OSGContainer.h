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

#ifndef _OSGCONTAINER_H_
#define _OSGCONTAINER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGUserInterfaceDef.h"
#include "OSGUserInterfaceDef.h"

#include "OSGContainerBase.h"
#include <map>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING Container : public ContainerBase
{
  private:

    typedef ContainerBase Inherited;

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

    virtual Int32 getChildIndex(ComponentPtr Child);

    virtual void updateLayout(void);
	virtual Vec2f getContentRequestedSize(void) const;
	virtual Vec2f getBorderingLength(void) const;
	
	//Mouse Events
    virtual void mouseClicked(const MouseEventPtr e);
    virtual void mouseEntered(const MouseEventPtr e);
    virtual void mouseExited(const MouseEventPtr e);
    virtual void mousePressed(const MouseEventPtr e);
    virtual void mouseReleased(const MouseEventPtr e);

	//Mouse Motion Events
    virtual void mouseMoved(const MouseEventPtr e);
    virtual void mouseDragged(const MouseEventPtr e);

	//Mouse Wheel Events
    virtual void mouseWheelMoved(const MouseWheelEventPtr e);

    virtual void detachFromEventProducer(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ContainerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Container(void);
    Container(const Container &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Container(void); 

    /*! \}                                                                 */
	virtual void drawInternal(const GraphicsPtr Graphics) const;

	void checkMouseEnterExit(const InputEventPtr e, const Pnt2f& MouseLocation, ComponentPtr Comp, bool isMouseContained, ViewportPtr TheViewport);
	virtual void produceMouseExitOnComponent(const MouseEventPtr e, ComponentPtr Comp);
	virtual void produceMouseEnterOnComponent(const MouseEventPtr e, ComponentPtr Comp);
    void removeMousePresenceOnComponents(void);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ContainerBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Container &source);
};

typedef Container *ContainerP;

OSG_END_NAMESPACE

#include "OSGContainerBase.inl"
#include "OSGContainer.inl"

#define OSGCONTAINER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGCONTAINER_H_ */
