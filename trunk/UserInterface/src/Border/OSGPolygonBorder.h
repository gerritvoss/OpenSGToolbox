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

#ifndef _OSGPOLYGONBORDER_H_
#define _OSGPOLYGONBORDER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGPolygonBorderBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PolygonBorder class. See \ref 
           PageUserInterfacePolygonBorder for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING PolygonBorder : public PolygonBorderBase
{
  private:

    typedef PolygonBorderBase Inherited;

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
    virtual void draw(const GraphicsPtr g, const Real32 x, const Real32 y , const Real32 Width, const Real32 Height, const Real32 Opacity, bool Clipping = true) const;
	virtual void activateInternalDrawConstraints(const GraphicsPtr g, const Real32& x, const Real32& y , const Real32& Width, const Real32& Height) const;
	virtual void deactivateInternalDrawConstraints(const GraphicsPtr g, const Real32& x, const Real32& y , const Real32& Width, const Real32& Height) const;
	virtual bool isContained(const Pnt2f& p, const Real32& x, const Real32& y , const Real32& Width, const Real32& Height) const;
	virtual void getInsets(Real32& Left, Real32& Right,Real32& Top,Real32& Bottom) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in PolygonBorderBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PolygonBorder(void);
    PolygonBorder(const PolygonBorder &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PolygonBorder(void); 

    /*! \}                                                                 */

	void scaleUp(Pnt2f& TheVector, const Vec2f& Scale) const;
	void scaleUp(Vec2f& TheVector, const Vec2f& Scale) const;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PolygonBorderBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PolygonBorder &source);
};

typedef PolygonBorder *PolygonBorderP;

OSG_END_NAMESPACE

#include "OSGPolygonBorderBase.inl"
#include "OSGPolygonBorder.inl"

#define OSGPOLYGONBORDER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGPOLYGONBORDER_H_ */
