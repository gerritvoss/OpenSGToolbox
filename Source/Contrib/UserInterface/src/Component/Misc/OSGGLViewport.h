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

#ifndef _OSGGLVIEWPORT_H_
#define _OSGGLVIEWPORT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGLViewportBase.h"
#include "OSGViewport.h"
#include "OSGRenderAction.h"
#include "OSGNavigator.h"
#include "OSGVector.h"

#include "OSGGLViewportBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief GLViewport class. See \ref
           PageContribUserInterfaceGLViewport for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING GLViewport : public GLViewportBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GLViewportBase Inherited;
    typedef GLViewport     Self;

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
    const Matrix& getViewMatrix(void);

    void showAll(void);
    void lookAt(const Pnt3f& From, const Pnt3f& At, const Vec3f& Up);
    void set(const Matrix& m);
    void setMode(Navigator::Mode TheMode);

    virtual void mousePressed(MouseEventDetails* const e);
    virtual void keyTyped(KeyEventDetails* const e);
    virtual void mouseWheelMoved(MouseWheelEventDetails* const e);

    void setMultipliers(Real32 YawMultiplier,Real32 PitchMultiplier,Real32 RollMultiplier);
    void setClamps(Vec2f YawClamp,Vec2f PitchClamp,Vec2f RollClamp);
    void setYaw(Real32 Yaw);
    void setRoll(Real32 Roll);
    void setPitch(Real32 Pitch);
    Real32 getYaw(void) const;
    Real32 getRoll(void) const;
    Real32 getPitch(void) const;

    void setOffset(const Vec3f& Offset);
    void setOffsetMultipliers(const Vec3f& OffsetMultipliers);
    void setMinOffset(const Vec3f& MinOffset);
    void setMaxOffset(const Vec3f& MaxOffset);
    const Vec3f& getOffset(void) const;
    const Vec3f& getOffsetMultipliers(void) const;
    const Vec3f& getMinOffset(void) const;
    const Vec3f& getMaxOffset(void) const;


    void updateNavigatorConnections(void);

    virtual void detachFromEventProducer(void);

    void copyView(const GLViewport& TheViewport);
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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	virtual void drawInternal(Graphics* const Graphics, Real32 Opacity = 1.0f) const;

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

	void handleNavMouseReleased(MouseEventDetails* const e);
	void handleNavMouseDragged(MouseEventDetails* const e);
	void handleNavKeyPressed(KeyEventDetails* const e);
    boost::signals2::connection _NavMouseReleasedConnection,
                                _NavMouseDraggedConnection,
                                _NavKeyPressedConnection;
    Matrix _InitialMat;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GLViewportBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GLViewport &source);
};

typedef GLViewport *GLViewportP;

OSG_END_NAMESPACE

#include "OSGGLViewportBase.inl"
#include "OSGGLViewport.inl"

#endif /* _OSGGLVIEWPORT_H_ */
