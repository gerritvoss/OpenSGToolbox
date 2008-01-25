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

#ifndef _OSGSPRINGLAYOUTCONSTRAINTS_H_
#define _OSGSPRINGLAYOUTCONSTRAINTS_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGSpringLayoutConstraintsBase.h"
#include "Layout/Spring/OSGLayoutSpringFields.h"

#include <deque>

OSG_BEGIN_NAMESPACE

/*! \brief SpringLayoutConstraints class. See \ref 
           PageUserInterfaceSpringLayoutConstraints for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING SpringLayoutConstraints : public SpringLayoutConstraintsBase
{
  private:

    typedef SpringLayoutConstraintsBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
      enum Edge {NO_EDGE, NORTH_EDGE, Y_EDGE, SOUTH_EDGE, X_EDGE, EAST_EDGE, WEST_EDGE, HORIZONTAL_CENTER_EDGE, VERTICAL_CENTER_EDGE, BASELINE_EDGE, WIDTH_EDGE, HEIGHT_EDGE};

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
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static  SpringLayoutConstraintsPtr create(LayoutSpringPtr XSpring, LayoutSpringPtr YSpring); 
    static  SpringLayoutConstraintsPtr create(LayoutSpringPtr XSpring, LayoutSpringPtr YSpring, LayoutSpringPtr WidthSpring, LayoutSpringPtr HeightSpring); 
    static  SpringLayoutConstraintsPtr create(ComponentPtr TheComponent); 
    
    /*! \}                                                                 */
    
    void setX(LayoutSpringPtr x);
    LayoutSpringPtr getX(void);
    
    void setY(LayoutSpringPtr y);
    LayoutSpringPtr getY(void);
    
    void setWidth(LayoutSpringPtr width);
    LayoutSpringPtr getWidth(void);
    
    void setHeight(LayoutSpringPtr height);
    LayoutSpringPtr getHeight(void);
    
    void setNorth(LayoutSpringPtr north);
    LayoutSpringPtr getNorth(void);
    
    void setEast(LayoutSpringPtr east);
    LayoutSpringPtr getEast(void);
    
    void setSouth(LayoutSpringPtr south);
    LayoutSpringPtr getSouth(void);
    
    void setWest(LayoutSpringPtr west);
    LayoutSpringPtr getWest(void);
    
    void setHorizontalCenter(LayoutSpringPtr horizontalCenter);
    LayoutSpringPtr getHorizontalCenter(void);
    
    void setVerticalCenter(LayoutSpringPtr verticalCenter);
    LayoutSpringPtr getVerticalCenter(void);

    void setBaseline(LayoutSpringPtr baseline);
    LayoutSpringPtr getBaseline(void);

    void setConstraint(UInt32 Edge, LayoutSpringPtr s);
    
    LayoutSpringPtr getConstraint(UInt32 Edge);
    
    void reset(void);
    
    std::deque<Edge> getHorizontalHistory(void) const;
    
    std::deque<Edge> getVerticalHistory(void) const;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SpringLayoutConstraintsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SpringLayoutConstraints(void);
    SpringLayoutConstraints(const SpringLayoutConstraints &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SpringLayoutConstraints(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
    
    std::deque<Edge> _HorizontalHistory,
                     _VerticalHistory;
  private:

    friend class FieldContainer;
    friend class SpringLayoutConstraintsBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SpringLayoutConstraints &source);
    
    LayoutSpringPtr sum(LayoutSpringPtr s1, LayoutSpringPtr s2);

    LayoutSpringPtr difference(LayoutSpringPtr s1, LayoutSpringPtr s2);

    LayoutSpringPtr scale(LayoutSpringPtr s, Real32 factor);
    
    Int32 getBaselineFromHeight(const Int32& height) const;

    Int32 getHeightFromBaseLine(const Int32& baseline) const;

    LayoutSpringPtr heightToRelativeBaseline(LayoutSpringPtr s);

    LayoutSpringPtr relativeBaselineToHeight(LayoutSpringPtr s);
    
    bool defined(const UInt32 Edge) const;
    
    void pushToHistory(Edge TheEdge, LayoutSpringPtr Value, bool isHorizontal);
};

typedef SpringLayoutConstraints *SpringLayoutConstraintsP;

OSG_END_NAMESPACE

#include "OSGSpringLayoutConstraintsBase.inl"
#include "OSGSpringLayoutConstraints.inl"

#define OSGSPRINGLAYOUTCONSTRAINTS_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGSPRINGLAYOUTCONSTRAINTS_H_ */
