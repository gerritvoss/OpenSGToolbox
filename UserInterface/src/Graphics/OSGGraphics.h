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

#ifndef _OSGGRAPHICS_H_
#define _OSGGRAPHICS_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGUserInterfaceConfig.h"

#include <OpenSG/OSGMFVecTypes.h>
#include <OpenSG/OSGDrawAction.h>

#include "OSGGraphicsBase.h"
#include "Text/OSGFont.h"

OSG_BEGIN_NAMESPACE

class OSG_USER_INTERFACE_CLASS_API Graphics : public GraphicsBase
{
  private:

    typedef GraphicsBase Inherited;

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
	
	virtual void drawRect(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color4f& Color, const Real32& Opacity) const = 0;

	virtual void drawQuad(const Pnt2s& p1, const Pnt2s& p2, const Pnt2s& p3, const Pnt2s& p4, 
							const Color4f& c1, const Color4f& c2, const Color4f& c3, const Color4f& c4,
							const Real32& Opacity) const = 0;
	
	virtual void drawLine(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Real32& Width, const Color4f& Color, const Real32& Opacity) const = 0;
	
	virtual void drawPolygon(const MFPnt2s Verticies, const Color4f& Color, const Real32& Opacity) const = 0;
	
	virtual void drawDisc(const Pnt2s& Center, const Int16& Width, const Int16& Height, const Real32& StartAngleRad, const Real32& EndAngleRad, const UInt16& SubDivisions, const Color4f& Color, const Real32& Opacity) const = 0;
	
	virtual void drawArc(const Pnt2s& Center, const Int16& Width, const Int16& Height, const Real32& StartAngleRad, const Real32& EndAngleRad, const Real32& LineWidth, const UInt16& SubDivisions, const Color4f& Color, const Real32& Opacity) const = 0;

	virtual void drawLoweredBevel(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color4f& Color, const Int16& Width, const Real32& Opacity) const = 0;//Color was inconsistent so changed from color 3f to 4f

	virtual void drawRaisedBevel(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color4f& Color, const Int16& Width, const Real32& Opacity) const = 0;
	
	virtual void drawText(const Pnt2s& Position, const std::string& Text, const FontPtr TheFont, const Color4f& Color, const Real32& Opacity) const = 0;
   virtual Vec2s getTextBounds(const std::string& Text, const FontPtr TheFont) const = 0;

	virtual void preDraw() = 0;
	virtual void postDraw() = 0;

   DrawActionBase* getDrawAction(void) const;
   void setDrawAction(DrawActionBase* action);

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in GraphicsBase.
 	 mutable DrawActionBase *   	 _Action;
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Graphics(void);
    Graphics(const Graphics &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Graphics(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class GraphicsBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Graphics &source);
};

typedef Graphics *GraphicsP;

OSG_END_NAMESPACE

#include "OSGGraphicsBase.inl"
#include "OSGGraphics.inl"

#define OSGGRAPHICS_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGGRAPHICS_H_ */
