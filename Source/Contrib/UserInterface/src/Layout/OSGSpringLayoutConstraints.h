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

#ifndef _OSGSPRINGLAYOUTCONSTRAINTS_H_
#define _OSGSPRINGLAYOUTCONSTRAINTS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSpringLayoutConstraintsBase.h"
#include "OSGLayoutSpring.h"
#include "OSGLayoutSpringFields.h"

#include <deque>

OSG_BEGIN_NAMESPACE

/*! \brief SpringLayoutConstraints class. See \ref
           PageContribUserInterfaceSpringLayoutConstraints for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING SpringLayoutConstraints : public SpringLayoutConstraintsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum Edge
    {
        NO_EDGE                = 0,
        NORTH_EDGE             = 1, 
        Y_EDGE                 = 2, 
        SOUTH_EDGE             = 3, 
        X_EDGE                 = 4, 
        EAST_EDGE              = 5, 
        WEST_EDGE              = 6, 
        HORIZONTAL_CENTER_EDGE = 7, 
        VERTICAL_CENTER_EDGE   = 8, 
        BASELINE_EDGE          = 9, 
        WIDTH_EDGE             = 10, 
        HEIGHT_EDGE            = 11
    };

    typedef SpringLayoutConstraintsBase Inherited;
    typedef SpringLayoutConstraints     Self;

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

    static  SpringLayoutConstraintsTransitPtr create(LayoutSpringRefPtr XSpring, LayoutSpringRefPtr YSpring); 
    static  SpringLayoutConstraintsTransitPtr create(LayoutSpringRefPtr XSpring, LayoutSpringRefPtr YSpring, LayoutSpringRefPtr WidthSpring, LayoutSpringRefPtr HeightSpring); 
    static  SpringLayoutConstraintsTransitPtr create(Component* const TheComponent); 
    
    
    void setX(LayoutSpringRefPtr x);
    LayoutSpringRefPtr getX(void);
    
    void setY(LayoutSpringRefPtr y);
    LayoutSpringRefPtr getY(void);
    
    void setWidth(LayoutSpringRefPtr width);
    LayoutSpringRefPtr getWidth(void);
    
    void setHeight(LayoutSpringRefPtr height);
    LayoutSpringRefPtr getHeight(void);
    
    void setNorth(LayoutSpringRefPtr north);
    LayoutSpringRefPtr getNorth(void);
    
    void setEast(LayoutSpringRefPtr east);
    LayoutSpringRefPtr getEast(void);
    
    void setSouth(LayoutSpringRefPtr south);
    LayoutSpringRefPtr getSouth(void);
    
    void setWest(LayoutSpringRefPtr west);
    LayoutSpringRefPtr getWest(void);
    
    void setHorizontalCenter(LayoutSpringRefPtr horizontalCenter);
    LayoutSpringRefPtr getHorizontalCenter(void);
    
    void setVerticalCenter(LayoutSpringRefPtr verticalCenter);
    LayoutSpringRefPtr getVerticalCenter(void);

    void setBaseline(LayoutSpringRefPtr baseline);
    LayoutSpringRefPtr getBaseline(void);

    void setConstraint(UInt32 Edge, LayoutSpringRefPtr s);
    
    LayoutSpringRefPtr getConstraint(UInt32 Edge);
    
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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
    std::deque<Edge> _HorizontalHistory,
                     _VerticalHistory;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SpringLayoutConstraintsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SpringLayoutConstraints &source);
    
    LayoutSpringRefPtr sum(LayoutSpringRefPtr s1, LayoutSpringRefPtr s2);

    LayoutSpringRefPtr difference(LayoutSpringRefPtr s1, LayoutSpringRefPtr s2);

    LayoutSpringRefPtr scale(LayoutSpringRefPtr s, Real32 factor);
    
    Real32 getBaselineFromHeight(const Real32& height) const;

    Real32 getHeightFromBaseLine(const Real32& baseline) const;

    LayoutSpringRefPtr heightToRelativeBaseline(LayoutSpringRefPtr s);

    LayoutSpringRefPtr relativeBaselineToHeight(LayoutSpringRefPtr s);
    
    bool defined(const UInt32 Edge) const;
    
    void pushToHistory(Edge TheEdge, LayoutSpringRefPtr Value, bool isHorizontal);
};

typedef SpringLayoutConstraints *SpringLayoutConstraintsP;

OSG_END_NAMESPACE

#include "OSGSpringLayoutConstraintsBase.inl"
#include "OSGSpringLayoutConstraints.inl"

#endif /* _OSGSPRINGLAYOUTCONSTRAINTS_H_ */
