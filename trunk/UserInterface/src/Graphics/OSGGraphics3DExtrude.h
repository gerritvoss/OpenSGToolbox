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

#ifndef _OSGGRAPHICS3DEXTRUDE_H_
#define _OSGGRAPHICS3DEXTRUDE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGGraphics3DExtrudeBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief Graphics3DExtrude class. See \ref 
           PageUserInterfaceGraphics3DExtrude for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING Graphics3DExtrude : public Graphics3DExtrudeBase
{
  private:

    typedef Graphics3DExtrudeBase Inherited;

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

    virtual void incrDrawBounderiesNesting(void);
    virtual void decrDrawBounderiesNestring(void);

    virtual void initAddDrawBounderies(void);
    virtual void uninitAddDrawBounderies(void);
    virtual void initRemoveDrawBounderies(void);
    virtual void uninitRemoveDrawBounderies(void);
    
    virtual void activateDrawBounderiesTest(void);
    virtual void deactivateDrawBounderiesTest(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in Graphics3DExtrudeBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Graphics3DExtrude(void);
    Graphics3DExtrude(const Graphics3DExtrude &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Graphics3DExtrude(void); 

    /*! \}                                                                 */

	static MaterialPtr createDefaultMaterial(void);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class Graphics3DExtrudeBase;

    static void initMethod(void);

    void drawCharacters( const TextLayoutResult& layoutResult, const UIFontPtr TheFont) const;

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Graphics3DExtrude &source);
};

typedef Graphics3DExtrude *Graphics3DExtrudeP;

OSG_END_NAMESPACE

#include "OSGGraphics3DExtrudeBase.inl"
#include "OSGGraphics3DExtrude.inl"

#define OSGGRAPHICS3DEXTRUDE_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGGRAPHICS3DEXTRUDE_H_ */
