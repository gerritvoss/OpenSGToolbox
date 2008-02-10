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

#ifndef _OSGGRAPHICS2D_H_
#define _OSGGRAPHICS2D_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGGraphics2DBase.h"

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING Graphics2D : public Graphics2DBase
{
  private:

    typedef Graphics2DBase Inherited;

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
	
	virtual void preDraw();
	virtual void postDraw();

	virtual void drawRect(const Pnt2f& TopLeft, const Pnt2f& BottomRight, const Color4f& Color, const Real32& Opacity) const;
	
	virtual void drawQuad(const Pnt2f& p1, const Pnt2f& p2, const Pnt2f& p3, const Pnt2f& p4, 
							const Color4f& c1, const Color4f& c2, const Color4f& c3, const Color4f& c4,
							const Real32& Opacity) const;
	
	virtual void drawQuad(const Pnt2f& p1, const Pnt2f& p2, const Pnt2f& p3, const Pnt2f& p4, 
							const Vec2f& t1, const Vec2f& t2, const Vec2f& t3, const Vec2f& t4,
							const TextureChunkPtr Texture,
							const Real32& Opacity) const;
	virtual void drawQuad(const Pnt2f& p1, const Pnt2f& p2, const Pnt2f& p3, const Pnt2f& p4, 
							const Vec2f& t1, const Vec2f& t2, const Vec2f& t3, const Vec2f& t4,
							const MaterialPtr Material,
							const Real32& Opacity) const;

	virtual void drawLine(const Pnt2f& TopLeft, const Pnt2f& BottomRight, const Real32& Width, const Color4f& Color, const Real32& Opacity) const;
	
	virtual void drawPolygon(const MFPnt2f Verticies, const Color4f& Color, const Real32& Opacity) const;
	
	virtual void drawDisc(const Pnt2f& Center, const Real32& Width, const Real32& Height, const Real32& StartAngleRad, const Real32& EndAngleRad, const UInt16& SubDivisions, const Color4f& CenterColor, const Color4f& OuterColor, const Real32& Opacity) const;
	
	virtual void drawComplexDisc(const Pnt2f& Center, const Real32& InnerRadius, const Real32& OuterRadius, const Real32& StartAngleRad, const Real32& EndAngleRad, const UInt16& SubDivisions, const Color4f& CenterColor, const Color4f& OuterColor, const Real32& Opacity) const;
	
	virtual void drawArc(const Pnt2f& Center, const Real32& Width, const Real32& Height, const Real32& StartAngleRad, const Real32& EndAngleRad, const Real32& LineWidth, const UInt16& SubDivisions, const Color4f& Color, const Real32& Opacity) const;
	
	virtual void drawText(const Pnt2f& Position, const std::string& Text, const UIFontPtr TheFont, const Color4f& Color, const Real32& Opacity) const;
	virtual void drawTextUnderline(const Pnt2f& Position, const std::string& Text, const UIFontPtr TheFont, const Color4f& Color, const Real32& Opacity) const;
   
	virtual Real32 getClipPlaneOffset(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in Graphics2DBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Graphics2D(void);
    Graphics2D(const Graphics2D &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Graphics2D(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class Graphics2DBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)
    void drawCharacters( const TextLayoutResult& layoutResult, const UIFontPtr TheFont) const;
    void operator =(const Graphics2D &source);
};

typedef Graphics2D *Graphics2DP;

OSG_END_NAMESPACE

#include "OSGGraphics2DBase.inl"
#include "OSGGraphics2D.inl"

#define OSGGRAPHICS2D_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGGRAPHICS2D_H_ */
