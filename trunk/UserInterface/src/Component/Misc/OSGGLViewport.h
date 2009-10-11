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

#ifndef _OSGGLVIEWPORT_H_
#define _OSGGLVIEWPORT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGNavigator.h>
#include <OpenSG/OSGVector.h>

#include "OSGGLViewportBase.h"
#include <OpenSG/Input/OSGMouseAdapter.h>
#include <OpenSG/Input/OSGMouseMotionAdapter.h>
#include <OpenSG/Input/OSGKeyAdapter.h>

OSG_BEGIN_NAMESPACE

/*! \brief GLViewport class. See \ref 
           PageUserInterfaceGLViewport for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING GLViewport : public GLViewportBase
{
  private:

    typedef GLViewportBase Inherited;

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

	void showAll(void);
    void lookAt(const Pnt3f& From, const Pnt3f& At, const Vec3f& Up);
	void set(const Matrix& m);
    void setMode(Navigator::Mode TheMode);

    virtual void mousePressed(const MouseEventPtr e);
	virtual void keyTyped(const KeyEventPtr e);
    virtual void mouseWheelMoved(const MouseWheelEventPtr e);
    
    void setMultipliers(Real32 YawMultiplier,Real32 PitchMultiplier,Real32 RollMultiplier);
    void setClamps(Vec2f YawClamp,Vec2f PitchClamp,Vec2f RollClamp);
    void setYaw(Real32 Yaw);
    void setRoll(Real32 Roll);
    void setPitch(Real32 Pitch);

    void setOffset(const Vec3f& Offset);
    void setOffsetMultipliers(const Vec3f& OffsetMultipliers);
    void setMinOffset(const Vec3f& MinOffset);
    void setMaxOffset(const Vec3f& MaxOffset);

	void updateNavigatorConnections(void);

    virtual void detachFromEventProducer(void);
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in GLViewportBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GLViewport(void);
    GLViewport(const GLViewport &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GLViewport(void); 

    /*! \}                                                                 */
	virtual void drawInternal(const GraphicsPtr Graphics) const;

    RenderAction* _Action;
	mutable Navigator _Navigator;
    Matrix _DefaultView;
    Real32 _Yaw, _Pitch, _Roll;
    Real32 _InitialYaw, _InitialPitch, _InitialRoll;
    Real32 _YawMultiplier, _PitchMultiplier, _RollMultiplier;
    Vec2f _YawClamp, _PitchClamp, _RollClamp;

    Vec3f _Offset;
    Vec3f _OffsetMultipliers;
    Vec3f _MinOffset;
    Vec3f _MaxOffset;

    Pnt2f _InitialMousePos;

    void updateView(void);

	class MouseControlListener : public MouseAdapter,public MouseMotionAdapter,public KeyAdapter
	{
	public :
		MouseControlListener(GLViewportPtr TheGLViewport);
		
		virtual void mouseReleased(const MouseEventPtr e);
		virtual void mouseDragged(const MouseEventPtr e);
		virtual void keyPressed(const KeyEventPtr e);

		void setInitialMat(const Matrix& Mat);
        void disconnect(void);
	protected :
		GLViewportPtr _GLViewport;
		Matrix _InitialMat;
	};

	friend class MouseControlListener;

	MouseControlListener _MouseControlListener;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class GLViewportBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const GLViewport &source);
};

typedef GLViewport *GLViewportP;

OSG_END_NAMESPACE

#include "OSGGLViewportBase.inl"
#include "OSGGLViewport.inl"

#define OSGGLVIEWPORT_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGGLVIEWPORT_H_ */
