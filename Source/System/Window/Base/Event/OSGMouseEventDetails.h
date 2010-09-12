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

#ifndef _OSGMOUSEEVENTDETAILS_H_
#define _OSGMOUSEEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMouseEventDetailsBase.h"
#include "OSGViewport.h"            // FieldContainer type

OSG_BEGIN_NAMESPACE

/*! \brief MouseEventDetails class. See \ref
           PageSystemMouseEventDetails for a description.
*/

class OSG_SYSTEM_DLLMAPPING MouseEventDetails : public MouseEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
     enum MouseButton {
         BUTTON1   = 0,
         BUTTON2   = 1,
         BUTTON3   = 2 ,
         BUTTON4   = 3 ,
         BUTTON5   = 4 ,
         BUTTON6   = 5 ,
         BUTTON7   = 6 ,
         BUTTON8   = 7 ,
         BUTTON9   = 8 ,
         BUTTON10  = 9 ,
         NO_BUTTON = 100
     };

    typedef MouseEventDetailsBase Inherited;
    typedef MouseEventDetails     Self;

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
    Pnt2f getLocationOnScreen(void) const;
    Real32 getX(void) const;
    Real32 getXOnScreen(void) const;
    Real32 getY(void) const;
    Real32 getYOnScreen(void) const;

    static  MouseEventDetailsTransitPtr create(FieldContainer* const Source,
                                               Time TimeStamp,
                                               UInt16 Button,
                                               UInt16 ClickCount,
                                               Pnt2f Location,
                                               Viewport* const TheViewport,
                                               Vec2f Delta = Vec2f(0.0f,0.0f)); 

    static  MouseEventDetailsTransitPtr create(MouseEventDetails* const Details,
                                               FieldContainer*    const NewSource);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MouseEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MouseEventDetails(void);
    MouseEventDetails(const MouseEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MouseEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MouseEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MouseEventDetails &source);
};

typedef MouseEventDetails *MouseEventDetailsP;

OSG_END_NAMESPACE

#include "OSGMouseEventDetailsBase.inl"
#include "OSGMouseEventDetails.inl"

#endif /* _OSGMOUSEEVENTDETAILS_H_ */
