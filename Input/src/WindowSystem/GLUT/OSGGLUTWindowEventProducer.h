/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#ifndef _OSGGLUTWINDOWEVENTPRODUCER_H_
#define _OSGGLUTWINDOWEVENTPRODUCER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGGLUTWindowEventProducerBase.h"

OSG_BEGIN_NAMESPACE

class GLUTWindowEventProducer : public GLUTWindowEventProducerBase
{
  private:

    typedef GLUTWindowEventProducerBase Inherited;

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
    
    //Set the Window Position
    virtual void setPosition(Pnt2s Pos);

    //Set the Window Position
    virtual Pnt2s getPosition(void) const;

    //Set the Window size
    virtual void setSize(Vec2us Size);

    //Get the Window size
    virtual Vec2s getSize(void) const;

    //Focused
    //Set the Window Focus
    virtual void setFocused(bool Focused);

    //Get the Window Focus
    virtual bool getFocused(void) const;

    //Visible / Iconify / Normal
    //Set the Window Visible
    virtual void setVisible(bool Visible);

    //Get the Window Visible
    virtual bool getVisible(void) const;

    //Set the Window Iconify
    virtual void setIconify(bool Iconify);

    //Get the Window Iconify
    virtual bool getIconify(void) const;

    //Fullscreen
    virtual void setFullscreen(bool Fullscreen);

    //Get the Window Fullscreen
    virtual bool getFullscreen(void) const;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in GLUTWindowEventProducerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GLUTWindowEventProducer(void);
    GLUTWindowEventProducer(const GLUTWindowEventProducer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GLUTWindowEventProducer(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class GLUTWindowEventProducerBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const GLUTWindowEventProducer &source);
};

typedef GLUTWindowEventProducer *GLUTWindowEventProducerP;

OSG_END_NAMESPACE

#include "OSGGLUTWindowEventProducerBase.inl"
#include "OSGGLUTWindowEventProducer.inl"

#define OSGGLUTWINDOWEVENTPRODUCER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGGLUTWINDOWEVENTPRODUCER_H_ */
