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

#ifndef _OSGROTATEDCOMPONENT_H_
#define _OSGROTATEDCOMPONENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGRotatedComponentBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief RotatedComponent class. See \ref 
           PageUserInterfaceRotatedComponent for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING RotatedComponent : public RotatedComponentBase
{
  private:

    typedef RotatedComponentBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
    enum ResizePolicy {NO_RESIZING = 0 , RESIZE_TO_MIN, RESIZE_TO_MAX};

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
                      
    virtual void updateLayout(void);
    
	//Mouse Events
    virtual void mouseClicked(const MouseEvent& e);
    virtual void mouseEntered(const MouseEvent& e);
    virtual void mouseExited(const MouseEvent& e);
    virtual void mousePressed(const MouseEvent& e);
    virtual void mouseReleased(const MouseEvent& e);

	//Mouse Motion Events
    virtual void mouseMoved(const MouseEvent& e);
    virtual void mouseDragged(const MouseEvent& e);

	//Mouse Wheel Events
    virtual void mouseWheelMoved(const MouseWheelEvent& e);

    virtual Pnt2f getParentToLocal(const Pnt2f& Location);

    /*! \}                                                                 */
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
	virtual void drawInternal(const GraphicsPtr Graphics) const;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class RotatedComponentBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const RotatedComponent &source);
};

typedef RotatedComponent *RotatedComponentP;

OSG_END_NAMESPACE

#include "OSGRotatedComponentBase.inl"
#include "OSGRotatedComponent.inl"

#define OSGROTATEDCOMPONENT_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGROTATEDCOMPONENT_H_ */
